# RISCOF

The RISC-V Compatibility Framework is a python based framework which enables testing of a RISC-V target (hard or soft implementations) against a standard RISC-V golden reference model using a suite of RISC-V architectural assembly tests.

## About

This folder contains configuration files and scripts to validate RS5 with RISCOF.
The scripts run a suite of ISA tests both with [sail-riscv](https://github.com/riscv/sail-riscv) and RS5.
The suite results present a report of what instructions pass/fail the test.

## Prerequisites

Some applications are needed to run RISCOF:
* riscv64-elf toolchain: the toolchain to build the tests.
* [sail-riscv](https://github.com/riscv/sail-riscv): the golden reference model;
* [verilator](https://www.veripool.org/verilator): SystemVerilog simulator for RS5;
* [RISCOF](https://riscof.readthedocs.io/en/stable/): the RISC-V Compatibility Framework.

### riscv64-elf toolchain

This is the same toolchain used to build RS5 [applications](/app/).
If your distro doesn't provide the riscv64-elf toolchain with multilib support for RV32I, 
you can follow [this tutorial](https://github.com/gaph-pucrs/Memphis-V/blob/master/docs/riscv.md) for manually building and installing the toolchain.
If your distro provides a different triple name, e.g., riscv64-unknown-elf, you can change by defining the `TRIPLET` environment variable before running the scripts in this directory.

### sail-riscv

[Sail](https://github.com/rems-project/sail) is a language for defining the instruction-set architecture (ISA) semantics of processors.
RISC-V has its formal description in Sail ([sail-riscv](https://github.com/riscv/sail-riscv)).
It is recommended to install the binary distribution of sail-riscv to avoid numerous dependencies of building sail and sail-riscv. 
To install sail-riscv:
1. Download and extract the binaries to a destination. Here a local installation is done in ~/.local/sail_riscv-Linux-x86_64
```
wget https://github.com/riscv/sail-riscv/releases/download/0.7/sail_riscv-Linux-x86_64.tar.gz -O sail-riscv.tar.gz
tar xvf sail-riscv.tar.gz -C ~/.local/
rm sail-riscv.tar.gz
```
2. Export the sail-riscv binaries to PATH. Here it is done persistently in .bashrc.
```
echo -e "# sail-riscv\nPATH=$HOME/.local/sail_riscv/bin:\${PATH}\n" >> ~/.bashrc
```

### verilator

This is the recommended simulator for RS5 [sim](/sim/).
Most distros provide a verilator package, but it needs C++ coroutine support.
If you encounter problems when verilating, follow (the verilator docs guide)[https://verilator.org/guide/latest/install.html#detailed-build-instructions] to build verilator with a recent toolchain (e.g. GCC11+).
It will also need the recent toolchain to build the verilated RS5 model.

### RISCOF

RISCOF is a python package with numerous dependencies. 
Therefore, it is recommended to create a virtual env and install RISCOF via pip.
To install RISCOF:
1. Create the virtual env and activate it. Activation is needed for every new terminal.
```
python -m venv ~/.local/riscof
source ~/.local/riscof/bin/activate
```
2. Install RISCOF (only needed once).
```
pip install riscof
```

## Running RISCOF

This folder provides a Makefile to automatically run RISCOF with the correct arguments.
`make baseline` runs RISCOF with a a *baseline* ISA (RV32IMZicsr_Zihpm).
This is also the *default* behavior of `make`.

To test the complete instruction set supported by RS5, run `make extensions`.
Currently, this tests all extensios except the RVV subsets.
To test both *baseline* and *extensions* instruction sets, run `make all`.

Note that running `make` will download or update the (test suite)[https://github.com/riscv-non-isa/riscv-arch-test] automatically.

Variations to core implementation are controlled by environment variables.
By default, branch prediction (`BRANCHPRED`), forwarding (`FORWARDING`), and dual port memory (`DUALPORT_MEM`) are enabled, and the instruction queue size (`IQUEUE_SIZE`) is 2.
It is also possible to increase the memory latency with the variable `DELAY_CYCLES`, which is 0 by default.
To control its behavior, run make with the environment variables defined to enable/disable the features.
E.g., run *extensions* with branch prediction and without forwarding:
```
BRANCHPRED=1 FORWARDING=0 make extensions
```

The `WORK_DIR` controls the base output directory of tests.
*baseline* outputs to `$WORK_DIR/baseline_work`, and *extensions* outputs to `$WORK_DIR/extensions_work`.
The default is `.`, but you may need to change if you do not want a lot of files being generated in this
repo's folder.
E.g., to change `WORK_DIR` to `/tmp`:
```
WORK_DIR=/tmp make
```

At the end of the suite, a `report.html` is generated at the `WORK_DIR/<isa>_work`.
To view the report in browser, run `make report-baseline` or `make report-extensions`.
It is also possible to open both reports with `make report-all`.
This report contains the tests that passed and failed.
When a test fails, it shows the lines where its dumped memory contents differ.
To see more details of the test, check the `WORK_DIR/<isa>_work/rv32i_m` folder containing the desired test.
The `ref` subfolder contains a `.disass` file with the disassembled test binary, and a `.log` with an step-by-step execution log by the gold model.
Both `ref` and `dut` folders contain a `.signature` that holds the test output and must match for the test to pass.
