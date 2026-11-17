#!/usr/bin/env python3
"""Vector regression tests.

Usage: ./vector_regression.py [--fast]

Every test is compiled once and simulated on each VLEN x LLEN x BUS_WIDTH
configuration:
  - default: VLENS="128 256 512", LLENS="32 64 128" and BUS_WIDTHS="32 64 128"
    (27 configurations); override them from the environment, e.g.
    VLENS=512 LLENS=32 BUS_WIDTHS=32 ./vector_regression.py
  - --fast: only the 3 configurations in FAST_CONFIGS (VLEN, LLEN, BUS_WIDTH)
The configurations of one test run in parallel, each with its own Xcelium
library (xcelium_vlen<V>_llen<L>_bus<B>.d). Results are saved per
configuration in
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
  - VEnable and the program are set on the xrun command line, so testbench.sv
    needs no editing
  - Compile with GCC 13, or add -fno-tree-vectorize to GCC_RISCV in
    app/baremetal/tests/vector-tests/Makefile. Newer GCC auto-vectorizes the
    tests and breaks them.
"""

import argparse
import os
import re
import shutil
import signal
import subprocess
import sys
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
DESTINATION_FOLDER = TESTS_FOLDER / "test"
RESULTS_FOLDER = TESTS_FOLDER / "results"
BIN_FILE = TESTS_FOLDER / "test.bin"

# Tests in class_disabled/ run with every vector class parameter set to 0
CLASS_PARAMETERS = [
    "VLogicEnable", "VMinMaxEnable", "VMergeEnable", "VDivEnable",
    "VRedLogicEnable", "VRedMinMaxEnable", "VRedSumEnable",
]
CLASS_OFF = [arg for name in CLASS_PARAMETERS for arg in ("-defparam", f"testbench.{name}=0")]


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


def config_name(vlen, llen, bus):
    return f"vlen{vlen}_llen{llen}_bus{bus}"


def config_params(vlen, llen, bus):
    return ["-defparam", f"testbench.VLEN={vlen}",
            "-defparam", f"testbench.LLEN={llen}",
            "-defparam", f"testbench.BUS_WIDTH={bus}"]


def run_config(config, params, filename, extra, sim_timeout):
    """Simulate the current test.bin on one configuration, file the log, return its Result."""
    output_file = RESULTS_FOLDER / config / f"{Path(filename).stem}.txt"
    command = ["xrun", "-f", "sim.xrun",
               "-xmlibdirname", f"xcelium_{config}.d", "-l", f"xrun.{config}.log",
               "-defparam", "testbench.VEnable=1", *params, *extra,
               "-gpg", f'testbench.BIN_FILE => "{BIN_FILE}"']

    timed_out = False
    with open(output_file, "w") as output:
        # A new session lets a timeout kill xrun together with the simulator it starts
        process = subprocess.Popen(command, stdout=output, stderr=subprocess.STDOUT,
                                   start_new_session=True)
        try:
            process.wait(timeout=sim_timeout)
        except subprocess.TimeoutExpired:
            timed_out = True
            os.killpg(process.pid, signal.SIGTERM)
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()

    log = output_file.read_text(errors="replace")
    reason, detail = failure_reason(log, filename, timed_out, sim_timeout)
    verdict = "failed" if reason else "passed"
    shutil.move(output_file, RESULTS_FOLDER / config / verdict / output_file.name)
    return Result(config, filename, reason, detail)


def run_test(file, configs, extra, sim_timeout):
    """Build one test, simulate it on every configuration in parallel, return the Results."""
    filename = file.name
    shutil.copy(file, DESTINATION_FOLDER / filename)
    build = subprocess.run(["make", "-C", str(TESTS_FOLDER), "clean", "all"],
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    if build.returncode != 0:
        for config, _ in configs:
            (RESULTS_FOLDER / config / "failed" / f"{file.stem}.txt").write_text(build.stdout)
        (DESTINATION_FOLDER / filename).unlink()
        print(f"{filename} build failed", flush=True)
        error = first_line(build.stdout, "error") or "make failed"
        return [Result(config, filename, "BUILD", error) for config, _ in configs]

    with ThreadPoolExecutor(max_workers=len(configs)) as pool:
        jobs = [pool.submit(run_config, config, params, filename, extra, sim_timeout)
                for config, params in configs]
        results = [job.result() for job in jobs]

    (DESTINATION_FOLDER / filename).unlink()
    print(f"{filename} done", flush=True)
    return results


def main():
    parser = argparse.ArgumentParser(description="Vector regression tests.")
    parser.add_argument("--fast", action="store_true",
                        help="run only the configurations in FAST_CONFIGS")
    args = parser.parse_args()

    os.chdir(SIM_FOLDER)
    sim_timeout = int(os.environ.get("SIM_TIMEOUT", "300"))

    if args.fast:
        triples = FAST_CONFIGS
    else:
        triples = [(vlen, llen, bus)
                   for vlen in env_list("VLENS", "128 256 512")
                   for llen in env_list("LLENS", "32 64 128")
                   for bus in env_list("BUS_WIDTHS", "32 64 128")]

    # (folder name, xrun arguments) of each configuration
    configs = [(config_name(*triple), config_params(*triple)) for triple in triples]
    for config, _ in configs:
        shutil.rmtree(RESULTS_FOLDER / config, ignore_errors=True)
        (RESULTS_FOLDER / config / "passed").mkdir(parents=True)
        (RESULTS_FOLDER / config / "failed").mkdir(parents=True)

    results = []
    for folder in SOURCE_FOLDERS:
        for file in sorted(folder.glob("*.c")):
            results += run_test(file, configs, [], sim_timeout)

    for file in sorted((TESTS_FOLDER / "class_disabled").glob("*.c")):
        results += run_test(file, configs, CLASS_OFF, sim_timeout)

    print()
    for config, _ in configs:
        passed = sum(1 for result in results if result.config == config and not result.reason)
        failed = sum(1 for result in results if result.config == config and result.reason)
        print(f"{config}  Passed: {passed}  Failed: {failed}")

    failures = [result for result in results if result.reason]
    if failures:
        print("\nFailures:")
        for result in failures:
            print(f"  {result.config}  {result.test}  {result.reason}: {result.detail}")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
