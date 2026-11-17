#!/usr/bin/env python3
"""Vector regression tests.

Usage: ./vector_regression.py [--fast] [--vlen N...] [--llen N...]
                               [--bus-width N...] [-k PATTERN]... [-j N]

Every test is simulated on each VLEN x LLEN x BUS_WIDTH configuration:
  - default: VLENS="128 256 512", LLENS="32 64 128" and BUS_WIDTHS="32 64 128"
    (27 configurations); override them from the environment, e.g.
    VLENS=512 LLENS=32 BUS_WIDTHS=32 ./vector_regression.py, or with
    --vlen, --llen and --bus-width, e.g. --vlen 512 --llen 32 64
  - --fast: only the 3 configurations in FAST_CONFIGS (VLEN, LLEN, BUS_WIDTH)
-k PATTERN runs only the tests whose name (with or without .c) matches the
glob PATTERN, e.g. -k vmseq -k 'vl*'; it can be given more than once.

The regression runs in two steps, both spread over -j/--jobs parallel jobs
(default: the number of CPUs, at most 64):
  1. every test is built in its own folder,
     app/baremetal/tests/vector-tests/build/<test>/, which keeps its test.bin
     and test.lst; at the same time every configuration is elaborated once
     into its own Xcelium library, xcelium_vlen<V>_llen<L>_bus<B>.d, and
     xcelium_vlen<V>_llen<L>_bus<B>_classoff.d for the tests in class_disabled/,
     which run with every vector class parameter set to 0;
  2. every (test, configuration) pair is simulated from that snapshot
     (xrun -R), with the program given as +BIN_FILE=<path>.
Results are saved per configuration in
  app/baremetal/tests/vector-tests/results/vlen<V>_llen<L>_bus<B>/{passed,failed}/<test>.txt
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
BUILD_FILES = ["Makefile", "test.S", "rs5.ld"]
BUILD_FOLDER = TESTS_FOLDER / "build"
RESULTS_FOLDER = TESTS_FOLDER / "results"

# Tests in class_disabled/ run with every vector class parameter set to 0
CLASS_PARAMETERS = [
    "VLogicEnable", "VMinMaxEnable", "VMergeEnable", "VDivEnable",
    "VRedLogicEnable", "VRedMinMaxEnable", "VRedSumEnable",
]
CLASS_OFF = [arg for name in CLASS_PARAMETERS for arg in ("-defparam", f"testbench.{name}=0")]

# Process groups of the running builds and simulations, killed on Ctrl-C
running = set()
running_lock = threading.Lock()


class Test(NamedTuple):
    file: Path
    classoff: bool  # runs with every vector class parameter set to 0


class Config(NamedTuple):
    name: str
    params: tuple  # xrun arguments


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
    error = first_line(log, r"\*[EF],")
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


def library(config, classoff):
    """Xcelium library of the snapshot of a configuration."""
    return f"xcelium_{config.name}{'_classoff' if classoff else ''}.d"


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


def build(test):
    """Build a test in its own folder; return (built, compiler output)."""
    folder = BUILD_FOLDER / test.file.stem
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
        _, returncode = run(["make", "-C", str(folder), "all"], output)
    return returncode == 0, log.read_text(errors="replace")


def elaborate(config, classoff):
    """Elaborate the snapshot of a configuration; return "" or the elaboration error."""
    lib = library(config, classoff)
    log = f"xrun.{lib.removeprefix('xcelium_').removesuffix('.d')}.log"
    command = ["xrun", "-f", "sim.xrun", "-elaborate", "-xmlibdirname", lib, "-l", log,
               "-defparam", "testbench.VEnable=1", *config.params,
               *(CLASS_OFF if classoff else [])]
    _, returncode = run(command, subprocess.DEVNULL)
    if returncode == 0:
        return ""
    return first_line(Path(log).read_text(errors="replace"), r"\*[EF],") or f"see sim/{log}"


def simulate(test, config, sim_timeout):
    """Simulate a built test on one configuration, file the log, return its Result."""
    output_file = RESULTS_FOLDER / config.name / f"{test.file.stem}.txt"
    bin_file = BUILD_FOLDER / test.file.stem / "test.bin"
    command = ["xrun", "-R", "-xmlibdirname", library(config, test.classoff), "-l", "/dev/null",
               f"+BIN_FILE={bin_file}"]
    with open(output_file, "w") as output:
        timed_out, _ = run(command, output, sim_timeout)

    log = output_file.read_text(errors="replace")
    reason, detail = failure_reason(log, test.file.name, timed_out, sim_timeout)
    verdict = "failed" if reason else "passed"
    shutil.move(output_file, RESULTS_FOLDER / config.name / verdict / output_file.name)
    return Result(config.name, test.file.name, reason, detail)


def run_regression(pool, tests, configs, sim_timeout):
    """Build, elaborate and simulate; return the Results."""
    builds = {test: pool.submit(build, test) for test in tests}
    snapshots = {(config, classoff): pool.submit(elaborate, config, classoff)
                 for config in configs for classoff in sorted({test.classoff for test in tests})}

    for (config, classoff), snapshot in snapshots.items():
        error = snapshot.result()
        if error:
            print(f"{library(config, classoff)} elaboration failed: {error}", flush=True)

    results = []
    simulations = {}
    for test, job in builds.items():
        built, output = job.result()
        if not built:
            for config in configs:
                (RESULTS_FOLDER / config.name / "failed" / f"{test.file.stem}.txt").write_text(output)
            print(f"{test.file.name} build failed", flush=True)
            error = first_line(output, "error") or "make failed"
            results += [Result(config.name, test.file.name, "BUILD", error) for config in configs]
            continue
        simulations[test] = []
        for config in configs:
            error = snapshots[(config, test.classoff)].result()
            if error:
                log = RESULTS_FOLDER / config.name / "failed" / f"{test.file.stem}.txt"
                log.write_text(f"Elaboration of {library(config, test.classoff)} failed: {error}\n")
                results.append(Result(config.name, test.file.name, "SIM", f"elaboration: {error}"))
            else:
                simulations[test].append(pool.submit(simulate, test, config, sim_timeout))

    for test, jobs in simulations.items():
        results += [job.result() for job in jobs]
        print(f"{test.file.name} done", flush=True)
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
    args = parser.parse_args()
    if args.fast and (args.vlen or args.llen or args.bus_width):
        parser.error("--fast cannot be combined with --vlen, --llen or --bus-width")
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
    configs = [make_config(*triple) for triple in triples]

    tests = [Test(file, False) for folder in SOURCE_FOLDERS for file in sorted(folder.glob("*.c"))]
    tests += [Test(file, True) for file in sorted((TESTS_FOLDER / "class_disabled").glob("*.c"))]
    tests = [test for test in tests if selected(test.file, args.patterns)]
    if not tests:
        parser.error(f"no test matches {' '.join(args.patterns)}")

    for config in configs:
        if args.patterns:
            # Keep the logs of the tests that do not run now
            for test in tests:
                for verdict in ("passed", "failed"):
                    (RESULTS_FOLDER / config.name / verdict / f"{test.file.stem}.txt").unlink(missing_ok=True)
        else:
            shutil.rmtree(RESULTS_FOLDER / config.name, ignore_errors=True)
        (RESULTS_FOLDER / config.name / "passed").mkdir(parents=True, exist_ok=True)
        (RESULTS_FOLDER / config.name / "failed").mkdir(parents=True, exist_ok=True)

    pool = ThreadPoolExecutor(max_workers=args.jobs)
    try:
        results = run_regression(pool, tests, configs, sim_timeout)
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
