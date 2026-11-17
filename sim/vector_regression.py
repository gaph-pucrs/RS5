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

Requirements (see "Vector regression tests" in README.md):
  - VEnable and the program are set on the xrun command line, so testbench.sv
    needs no editing
  - Compile with GCC 13, or add -fno-tree-vectorize to GCC_RISCV in
    app/baremetal/tests/vector-tests/Makefile. Newer GCC auto-vectorizes the
    tests and breaks them.
"""

import argparse
import os
import shutil
import signal
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

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
    """Simulate the current test.bin on one configuration and file the log."""
    output_file = RESULTS_FOLDER / config / f"{Path(filename).stem}.txt"
    command = ["xrun", "-f", "sim.xrun",
               "-xmlibdirname", f"xcelium_{config}.d", "-l", f"xrun.{config}.log",
               "-defparam", "testbench.VEnable=1", *params, *extra,
               "-gpg", f'testbench.BIN_FILE => "{BIN_FILE}"']

    with open(output_file, "w") as output:
        # A new session lets a timeout kill xrun together with the simulator it starts
        process = subprocess.Popen(command, stdout=output, stderr=subprocess.STDOUT,
                                   start_new_session=True)
        try:
            process.wait(timeout=sim_timeout)
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGTERM)
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()

    log = output_file.read_text(errors="replace")
    verdict = "passed" if f"PASSED: test/{filename}!" in log else "failed"
    shutil.move(output_file, RESULTS_FOLDER / config / verdict / output_file.name)


def run_test(file, configs, extra, sim_timeout):
    """Build one test and simulate it on every configuration in parallel."""
    filename = file.name
    shutil.copy(file, DESTINATION_FOLDER / filename)
    subprocess.run(["make", "-C", str(TESTS_FOLDER), "clean", "all"], stdout=subprocess.DEVNULL)

    with ThreadPoolExecutor(max_workers=len(configs)) as pool:
        jobs = [pool.submit(run_config, config, params, filename, extra, sim_timeout)
                for config, params in configs]
        for job in jobs:
            job.result()

    (DESTINATION_FOLDER / filename).unlink()
    print(f"{filename} done", flush=True)


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

    for folder in SOURCE_FOLDERS:
        for file in sorted(folder.glob("*.c")):
            run_test(file, configs, [], sim_timeout)

    for file in sorted((TESTS_FOLDER / "class_disabled").glob("*.c")):
        run_test(file, configs, CLASS_OFF, sim_timeout)

    print()
    for config, _ in configs:
        passed = len(list((RESULTS_FOLDER / config / "passed").iterdir()))
        failed = len(list((RESULTS_FOLDER / config / "failed").iterdir()))
        print(f"{config}  Passed: {passed}  Failed: {failed}")
    for config, _ in configs:
        failed = sorted(path.name for path in (RESULTS_FOLDER / config / "failed").iterdir())
        if failed:
            print(f"{config} failed:", *failed)
    return 0


if __name__ == "__main__":
    sys.exit(main())
