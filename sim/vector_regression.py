#!/usr/bin/env python3
"""Vector regression tests.

Usage: ./vector_regression.py [--fast] [--vlen N...] [--llen N...]
                               [--bus-width N...] [-k PATTERN]... [-j N]
       ./vector_regression.py --sail [--fast] [--vlen N...] [-k PATTERN]... [-j N]

Every test is simulated on each VLEN x LLEN x BUS_WIDTH configuration:
  - default: VLENS="128 256 512", LLENS="32 64 128" and BUS_WIDTHS="32 64 128"
    (27 configurations); override them from the environment, e.g.
    VLENS=512 LLENS=32 BUS_WIDTHS=32 ./vector_regression.py, or with
    --vlen, --llen and --bus-width, e.g. --vlen 512 --llen 32 64
  - --fast: only the 3 configurations in FAST_CONFIGS (VLEN, LLEN, BUS_WIDTH)
-k PATTERN runs only the tests whose name (with or without .c) matches the
glob PATTERN, e.g. -k vmseq -k 'vl*'; it can be given more than once.

--sail runs the tests on the Sail RISC-V reference model (sail_riscv_sim,
module sail-riscv/0.12, or the path in $SAIL_RISCV_SIM) instead of RS5. The
model is configured as Zve32x by sim/sail_zve32x.json; each VLEN is one
configuration, sail_vlen<V> (--fast: VLEN = 256), and LLEN and BUS_WIDTH do
not apply. The tests are built with make TARGET=sail, which skips the checks
marked SKIP_ON_SAIL, and class_disabled/ does not run, since the model has no
vector class parameters.

The regression runs in two steps, both spread over -j/--jobs parallel jobs
(default: the number of CPUs, at most 64):
  1. every test is built in its own folder,
     app/baremetal/tests/vector-tests/build/<rs5|sail>/<test>/, which keeps its
     test.bin and test.lst; at the same time every configuration is elaborated once
     into its own Xcelium library, xcelium_vlen<V>_llen<L>_bus<B>.d, and
     xcelium_vlen<V>_llen<L>_bus<B>_classoff.d for the tests in class_disabled/,
     which run with every vector class parameter set to 0, and
     xcelium_vlen<V>_llen<L>_bus<B>_multicycle.d, where the reduction tests
     (MULTICYCLE_TESTS) run a second time with VMultiCycleReductions = 1 and
     their results are filed as <test>@multicycle (with --sail, a Sail
     configuration with that VLEN is written instead);
  2. every (test, configuration) pair is simulated from that snapshot
     (xrun -R), with the program given as +BIN_FILE=<path> (with --sail, by
     sail_riscv_sim on the test's test.axf).
Results are saved per configuration in
  app/baremetal/tests/vector-tests/results/<configuration>/{passed,failed}/<test>.txt
A simulation that runs longer than SIM_TIMEOUT seconds (300 by default) is
killed and counted as failed, so a hung test does not stop the regression.
A test that does not build is not simulated: the compiler output is saved as
its log in every configuration and the test counts as failed.
The summary gives the reason of each failure: BUILD (the test does not
compile), TIMEOUT, TRAP (unexpected trap), CHECK (a test case got a wrong
result) or SIM (the simulation ended without a verdict, e.g. an Xcelium error).
The exit status is 1 when any test fails, 0 otherwise.

Requirements (see "Vector regression tests" in README.md):
  - VEnable, the configuration and the program are set on the xrun command
    line, so testbench.sv needs no editing
  - Compile with GCC 13, or add -fno-tree-vectorize to GCC_RISCV in
    app/baremetal/tests/vector-tests/Makefile. Newer GCC auto-vectorizes the
    tests and breaks them.
"""

import argparse
import fnmatch
import os
import re
import shutil
import signal
import subprocess
import sys
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import NamedTuple

SIM_FOLDER = Path(__file__).resolve().parent

# VLEN, LLEN, BUS_WIDTH
FAST_CONFIGS = [
    (256, 32, 32),
    (256, 32, 64),
    (256, 64, 32),
]

TESTS_FOLDER = Path("../app/baremetal/tests/vector-tests")
SOURCE_FOLDERS = [TESTS_FOLDER / "operations", TESTS_FOLDER / "mem_operations"]
SUPPORT_FOLDER = TESTS_FOLDER / "test"  # headers and sources shared by every test
BUILD_FILES = ["Makefile", "test.S", "rs5.ld", "sail.ld"]
BUILD_FOLDER = TESTS_FOLDER / "build"
RESULTS_FOLDER = TESTS_FOLDER / "results"
SAIL_CONFIG = Path("sail_zve32x.json")  # VLEN = 512; vlen_exp is rewritten per VLEN

# Tests in class_disabled/ run with every vector class parameter set to 0
CLASS_PARAMETERS = [
    "VLogicEnable", "VMinMaxEnable", "VMergeEnable", "VDivEnable",
    "VRedLogicEnable", "VRedMinMaxEnable", "VRedSumEnable", "VCarryEnable",
]
CLASS_OFF = [arg for name in CLASS_PARAMETERS for arg in ("-defparam", f"testbench.{name}=0")]

# Snapshot variants: "" is the default configuration, "classoff" has every vector
# class parameter set to 0, and "multicycle" has the multi-cycle reductions
VARIANT_PARAMS = {
    "": [],
    "classoff": CLASS_OFF,
    "multicycle": ["-defparam", "testbench.VMultiCycleReductions=1"],
}
# Tests of SOURCE_FOLDERS that also run on the multicycle snapshot
MULTICYCLE_TESTS = ["vred*.c", "vwred*.c"]

# Process groups of the running builds and simulations, killed on Ctrl-C
running = set()
running_lock = threading.Lock()


class Test(NamedTuple):
    file: Path
    variant: str  # snapshot variant, a key of VARIANT_PARAMS

    @property
    def name(self):
        """Name of the test in the results: the multicycle run gets a suffix."""
        return self.file.stem + ("@multicycle" if self.variant == "multicycle" else "")


class Config(NamedTuple):
    name: str
    params: tuple  # xrun arguments, or (Sail configuration file,) for the model
    model: str = "rs5"  # "rs5" or "sail"


class Result(NamedTuple):
    config: str
    test: str
    reason: str  # "" when the test passed
    detail: str


def first_line(log, pattern):
    """First line of log that matches pattern, or ""."""
    match = re.search(f"^.*(?:{pattern}).*$", log, re.MULTILINE)
    return match.group(0).strip() if match else ""


def failure_reason(log, filename, timed_out, sim_timeout):
    """(reason, detail) of a simulation log; reason is "" when the test passed."""
    if timed_out:
        return "TIMEOUT", f"killed after {sim_timeout} s"
    if f"PASSED: test/{filename}!" in log:
        return "", ""
    trap = first_line(log, r"unexpected trap\(s\)")
    if trap:
        return "TRAP", trap
    if f"ERROR: test/{filename} failed" in log:
        # The first wrong result and the test case it belongs to
        failed = re.search(r"^.*FAILED.*$", log, re.MULTILINE)
        if not failed:
            return "CHECK", first_line(log, "ERROR: test/")
        cases = re.findall(r"^(Checking .*?)(?::|\.\.\.)?$", log[:failed.start()], re.MULTILINE)
        line = failed.group(0).strip()
        return "CHECK", f"{cases[-1]}: {line}" if cases else line
    error = first_line(log, r"\*[EF],|[Ee]xception|[Ee]rror")
    return "SIM", error or "no PASSED or ERROR line in the log"


def env_list(name, default):
    """Integers from a space-separated environment variable."""
    return [int(value) for value in os.environ.get(name, default).split()]


def selected(file, patterns):
    """True if no pattern was given or the test name matches one of them."""
    return not patterns or any(fnmatch.fnmatch(file.name, pattern) or
                               fnmatch.fnmatch(file.stem, pattern) for pattern in patterns)


def make_config(vlen, llen, bus):
    return Config(f"vlen{vlen}_llen{llen}_bus{bus}",
                  ("-defparam", f"testbench.VLEN={vlen}",
                   "-defparam", f"testbench.LLEN={llen}",
                   "-defparam", f"testbench.BUS_WIDTH={bus}"))


def make_sail_config(vlen):
    folder = BUILD_FOLDER / "sail"
    return Config(f"sail_vlen{vlen}", (str(folder / f"sail_zve32x_vlen{vlen}.json"),), "sail")


def write_sail_config(config, vlen):
    """Write the Sail configuration of one VLEN; return "" or the error."""
    if vlen < 32 or vlen & (vlen - 1):
        return f"VLEN = {vlen} is not a power of 2 of at least 32"
    text = SAIL_CONFIG.read_text()
    text, count = re.subn(r'"vlen_exp": \d+', f'"vlen_exp": {vlen.bit_length() - 1}', text)
    if count != 1:
        return f"no single vlen_exp in {SAIL_CONFIG}"
    path = Path(config.params[0])
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)
    return ""


def library(config, variant):
    """Xcelium library of the snapshot of a configuration."""
    return f"xcelium_{config.name}{'_' + variant if variant else ''}.d"


def kill(process, sig):
    """Send sig to the process group of process, if it still exists."""
    try:
        os.killpg(process.pid, sig)
    except ProcessLookupError:
        pass


def run(command, output, timeout=None):
    """Run command in its own process group, writing to output; return (timed out, exit status)."""
    # A new session lets a timeout or Ctrl-C kill xrun together with the simulator it starts
    process = subprocess.Popen(command, stdout=output, stderr=subprocess.STDOUT,
                               start_new_session=True)
    with running_lock:
        running.add(process)
    timed_out = False
    try:
        process.wait(timeout=timeout)
    except subprocess.TimeoutExpired:
        timed_out = True
        kill(process, signal.SIGTERM)
        try:
            process.wait(timeout=10)
        except subprocess.TimeoutExpired:
            kill(process, signal.SIGKILL)
            process.wait()
    finally:
        with running_lock:
            running.discard(process)
    return timed_out, process.returncode


def build(test, model):
    """Build a test for RS5 or Sail in its own folder; return (built, compiler output)."""
    folder = BUILD_FOLDER / model / test.file.stem
    shutil.rmtree(folder, ignore_errors=True)
    (folder / "test").mkdir(parents=True)
    for name in BUILD_FILES:
        shutil.copy(TESTS_FOLDER / name, folder / name)
    for support in SUPPORT_FOLDER.iterdir():
        if support.suffix in (".h", ".c", ".S"):
            shutil.copy(support, folder / "test" / support.name)
    shutil.copy(test.file, folder / "test" / test.file.name)

    log = folder / "build.log"
    with open(log, "w") as output:
        _, returncode = run(["make", "-C", str(folder), f"TARGET={model}", "all"], output)
    return returncode == 0, log.read_text(errors="replace")


def elaborate(config, variant):
    """Elaborate the snapshot of a configuration; return "" or the elaboration error."""
    lib = library(config, variant)
    log = f"xrun.{lib.removeprefix('xcelium_').removesuffix('.d')}.log"
    command = ["xrun", "-f", "sim.xrun", "-elaborate", "-xmlibdirname", lib, "-l", log,
               "-defparam", "testbench.VEnable=1", *config.params,
               *VARIANT_PARAMS[variant]]
    _, returncode = run(command, subprocess.DEVNULL)
    if returncode == 0:
        return ""
    return first_line(Path(log).read_text(errors="replace"), r"\*[EF],") or f"see sim/{log}"


def simulate(test, config, sim_timeout, sail_sim):
    """Simulate a built test on one configuration, file the log, return its Result."""
    output_file = RESULTS_FOLDER / config.name / f"{test.name}.txt"
    folder = BUILD_FOLDER / config.model / test.file.stem
    if config.model == "sail":
        command = [sail_sim, "--config", config.params[0], str(folder / "test.axf")]
    else:
        command = ["xrun", "-R", "-xmlibdirname", library(config, test.variant), "-l", "/dev/null",
                   f"+BIN_FILE={folder / 'test.bin'}"]
    with open(output_file, "w") as output:
        timed_out, _ = run(command, output, sim_timeout)

    log = output_file.read_text(errors="replace")
    reason, detail = failure_reason(log, test.file.name, timed_out, sim_timeout)
    verdict = "failed" if reason else "passed"
    shutil.move(output_file, RESULTS_FOLDER / config.name / verdict / output_file.name)
    return Result(config.name, test.name, reason, detail)


def run_regression(pool, tests, configs, sim_timeout, sail_sim, vlens):
    """Build, elaborate (or write the Sail configurations) and simulate; return the Results."""
    model = configs[0].model
    # One build per file: the multicycle run of a test uses the build of its default run
    builds = {}
    for test in tests:
        if test.file not in builds:
            builds[test.file] = pool.submit(build, test, model)
    if model == "sail":
        snapshots = {(config, ""): pool.submit(write_sail_config, config, vlen)
                     for config, vlen in zip(configs, vlens)}
    else:
        snapshots = {(config, variant): pool.submit(elaborate, config, variant)
                     for config in configs for variant in sorted({test.variant for test in tests})}

    for (config, variant), snapshot in snapshots.items():
        error = snapshot.result()
        if error:
            target = library(config, variant) if config.model == "rs5" else config.params[0]
            print(f"{target}: setup failed: {error}", flush=True)

    results = []
    simulations = {}
    for test in tests:
        built, output = builds[test.file].result()
        if not built:
            for config in configs:
                (RESULTS_FOLDER / config.name / "failed" / f"{test.name}.txt").write_text(output)
            print(f"{test.name} build failed", flush=True)
            error = first_line(output, "error") or "make failed"
            results += [Result(config.name, test.name, "BUILD", error) for config in configs]
            continue
        simulations[test] = []
        for config in configs:
            error = snapshots[(config, test.variant)].result()
            if error:
                log = RESULTS_FOLDER / config.name / "failed" / f"{test.name}.txt"
                log.write_text(f"Setup of {config.name} failed: {error}\n")
                results.append(Result(config.name, test.name, "SIM", f"setup: {error}"))
            else:
                simulations[test].append(pool.submit(simulate, test, config, sim_timeout, sail_sim))

    for test, jobs in simulations.items():
        results += [job.result() for job in jobs]
        print(f"{test.name} done", flush=True)
    return results


def main():
    parser = argparse.ArgumentParser(description="Vector regression tests.")
    parser.add_argument("--fast", action="store_true",
                        help="run only the configurations in FAST_CONFIGS")
    parser.add_argument("--vlen", type=int, nargs="+", metavar="N",
                        help="VLEN values (default: $VLENS or 128 256 512)")
    parser.add_argument("--llen", type=int, nargs="+", metavar="N",
                        help="LLEN values (default: $LLENS or 32 64 128)")
    parser.add_argument("--bus-width", type=int, nargs="+", metavar="N",
                        help="BUS_WIDTH values (default: $BUS_WIDTHS or 32 64 128)")
    parser.add_argument("-k", dest="patterns", action="append", default=[], metavar="PATTERN",
                        help="run only the tests whose name matches this glob (repeatable)")
    parser.add_argument("-j", "--jobs", type=int, default=min(64, os.cpu_count() or 1),
                        metavar="N", help="parallel builds and simulations (default: %(default)s)")
    parser.add_argument("--sail", action="store_true",
                        help="run on the Sail reference model (Zve32x) instead of RS5")
    args = parser.parse_args()
    if args.fast and (args.vlen or args.llen or args.bus_width):
        parser.error("--fast cannot be combined with --vlen, --llen or --bus-width")
    if args.sail and (args.llen or args.bus_width):
        parser.error("--llen and --bus-width do not apply to --sail")
    sail_sim = os.environ.get("SAIL_RISCV_SIM", "sail_riscv_sim")
    if args.sail and not shutil.which(sail_sim):
        parser.error(f"{sail_sim} not found: module load sail-riscv/0.12, or set SAIL_RISCV_SIM")
    if args.jobs < 1:
        parser.error("--jobs must be at least 1")

    os.chdir(SIM_FOLDER)
    sim_timeout = int(os.environ.get("SIM_TIMEOUT", "300"))

    if args.fast:
        triples = FAST_CONFIGS
    else:
        triples = [(vlen, llen, bus)
                   for vlen in args.vlen or env_list("VLENS", "128 256 512")
                   for llen in args.llen or env_list("LLENS", "32 64 128")
                   for bus in args.bus_width or env_list("BUS_WIDTHS", "32 64 128")]
    if args.sail:
        # Only VLEN applies to the model
        vlens = sorted({vlen for vlen, _, _ in triples})
        configs = [make_sail_config(vlen) for vlen in vlens]
    else:
        vlens = []
        configs = [make_config(*triple) for triple in triples]

    tests = [Test(file, "") for folder in SOURCE_FOLDERS for file in sorted(folder.glob("*.c"))]
    if not args.sail:
        tests += [Test(file, "classoff") for file in sorted((TESTS_FOLDER / "class_disabled").glob("*.c"))]
        tests += [Test(test.file, "multicycle") for test in list(tests)
                  if test.variant == "" and any(fnmatch.fnmatch(test.file.name, pattern)
                                                for pattern in MULTICYCLE_TESTS)]
    tests = [test for test in tests if selected(test.file, args.patterns)]
    if not tests:
        parser.error(f"no test matches {' '.join(args.patterns)}")

    for config in configs:
        if args.patterns:
            # Keep the logs of the tests that do not run now
            for test in tests:
                for verdict in ("passed", "failed"):
                    (RESULTS_FOLDER / config.name / verdict / f"{test.name}.txt").unlink(missing_ok=True)
        else:
            shutil.rmtree(RESULTS_FOLDER / config.name, ignore_errors=True)
        (RESULTS_FOLDER / config.name / "passed").mkdir(parents=True, exist_ok=True)
        (RESULTS_FOLDER / config.name / "failed").mkdir(parents=True, exist_ok=True)

    pool = ThreadPoolExecutor(max_workers=args.jobs)
    try:
        results = run_regression(pool, tests, configs, sim_timeout, sail_sim, vlens)
    except KeyboardInterrupt:
        pool.shutdown(wait=False, cancel_futures=True)
        with running_lock:
            for process in running:
                kill(process, signal.SIGKILL)
        print("\nInterrupted", file=sys.stderr)
        return 130
    pool.shutdown()

    print()
    for config in configs:
        passed = sum(1 for result in results if result.config == config.name and not result.reason)
        failed = sum(1 for result in results if result.config == config.name and result.reason)
        print(f"{config.name}  Passed: {passed}  Failed: {failed}")

    failures = sorted((result for result in results if result.reason),
                      key=lambda result: (result.test, result.config))
    if failures:
        print("\nFailures:")
        for result in failures:
            print(f"  {result.config}  {result.test}  {result.reason}: {result.detail}")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
