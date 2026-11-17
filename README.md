# RS5

**RS5** is a parameterizable, 4-stage pipelined RISC-V processor written in SystemVerilog, developed at the [Hardware Design Support Group (GAPH)](https://nsesd.pucrs.br/), PUCRS, Brazil.

[![RISCOF Passing](https://img.shields.io/badge/RISCOF-Passing-blue)](riscof/README.md)
[![FPGA: Nexys A7](https://img.shields.io/badge/FPGA-Nexys%20A7-brightgreen)](proto/RS5)
[![FPGA: NetFPGA SUME](https://img.shields.io/badge/FPGA-NetFPGA%20SUME-brightgreen)](proto/RS5_SUME)
[![Silicon Proven](https://img.shields.io/badge/Silicon-Proven-blue)](https://www.linkedin.com/feed/update/urn:li:activity:7470952399667425280/)


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## Table of Contents

- [RS5](#rs5)
  - [Table of Contents](#table-of-contents)
  - [Feature overview](#feature-overview)
  - [Simulation Quick Start](#simulation-quick-start)
    - [Requirements](#requirements)
    - [Build the test application](#build-the-test-application)
    - [Simulate with Verilator](#simulate-with-verilator)
    - [Simulate with Modelsim/Questa](#simulate-with-modelsimquesta)
    - [Simulate with Xcelium](#simulate-with-xcelium)
    - [Vector regression tests](#vector-regression-tests)
  - [FPGA Prototyping](#fpga-prototyping)
    - [Prototyping steps](#prototyping-steps)
  - [Architectural compliance (RISCOF)](#architectural-compliance-riscof)
  - [Tutorials (in Portuguese)](#tutorials-in-portuguese)
  - [Cite this work](#cite-this-work)
  - [Acknowledgements](#acknowledgements)

---

## Feature overview

| Feature | Details |
|---|---|
| Base ISA | RV32I |
| Privilege modes | Machine mode (M-mode) and User mode (U-mode) |
| Interrupt controller | optional [SiFive-compliant](https://github.com/riscv/riscv-plic-spec) [PLIC](rtl/plic.sv) |
| Machine timer | optional [mtimer](rtl/rtc.sv) |

| Extension type | Available extensions |
|---|---|
| Integer extensions | Zicond; Zicsr (always enabled); Zihpm |
| Multiply/divide extensions | M or Zmmul (multiply subset) |
| Atomic extensions | A, Zalrsc (conditional subset), or Zaamo (AMO subset) |
| Compressed extensions | C and Zcb (additional compressed) |
| Cryptography | Zkne (AES), Zbkb (bit-manip), Zknh (SHA2), Xkyber(Kyber) |
| Vector extension | Zve32x and Zvl64b subsets (configurable VLEN, LLEN) |
| Non-standard | Xosvm (offset and size virtual memory support) |

| Parameter | Details |
|---|---|
| Branch prediction | Optional static branch prediction for immediate branches at decode stage |
| Data forwarding | Optional forwarding from execution result or memory read. Register writeback is always forwarded. |
| Instruction buffering | Optionally fetches while pipeline is stalled |

Optional features are configurable through parameters in [rtl/RS5.sv](rtl/RS5.sv).
See [docs/README.md](docs/README.md) for details on the core implementation, parameters and extensions.

---

## Simulation Quick Start

### Requirements

It is possible to evaluate RS5 using only open source tools:

- [Verilator](https://verilator.org)
- [RISC-V toolchain](https://github.com/gaph-pucrs/Memphis-V/blob/master/docs/riscv.md)

RS5 also supports simulation with the following commercial tools:
- Modelsim/Questa
- Xcelium

### Build the test application

The default test application is a set of tests from the [riscv-arch-test](https://github.com/riscv/riscv-arch-test).
You need to build the application before running the simulation:

```bash
make -C app/baremetal/tests/riscv-tests
```

Applications are grouped in [app/](app/) by build system, then by purpose (`tests`, `benchmarks`, `crypto`, `examples`):
`app/newlib` holds the applications built with newlib through `app/newlib/common/common.mk`, and `app/baremetal` holds the ones without a C library.

### Simulate with Verilator

This verilates and runs the default application.
Results are written to `sim/results/Output.txt` (simulation output) and `sim/results/Report.txt` (profiling).

```bash
make -C sim
```

### Simulate with Modelsim/Questa

```bash
cd sim
vsim -c -do sim.do
```

To load another program, set `BIN_FILE` before running `sim.do`:

```bash
vsim -c -do "set BIN_FILE ../app/baremetal/tests/vector-tests/test.bin; do sim.do"
```

### Simulate with Xcelium

```bash
cd sim
xrun -f sim.xrun
```

### Simulation monitors

The testbench binds optional monitors, selected at compile time:

| Flag        | Output                                         | Default |
|-------------|------------------------------------------------|---------|
| `DEBUG`     | Register bank and memory access logs (`debug/`) | off     |
| `LOCKSTEP`  | sail-riscv 0.7 instruction trace (`debug/`)     | off     |
| `PROFILING` | HPM counters report (`results/`)                | on      |

```bash
make -C sim LOCKSTEP=1 DEBUG=1                         # Verilator
vsim -c -do "set LOCKSTEP 1; set PROFILING 0; do sim.do" # Questa
xrun -f sim.xrun +define+LOCKSTEP                      # Xcelium (PROFILING is on in sim.xrun)
```

The testbench's `VEnable`, `VLEN`, `LLEN` and `BIN_FILE` (the program to load) are parameters, so you can override them without editing the testbench:

```bash
xrun -f sim.xrun -defparam testbench.VEnable=1 -defparam testbench.BIN_FILE=\"../app/baremetal/tests/vector-tests/test.bin\"
```

With Verilator, pass them through the Makefile:

```bash
make -C sim VENABLE=1 VLEN=256 BIN_FILE=../app/baremetal/tests/vector-tests/test.bin
```

### Vector regression tests

[sim/vector_regression.py](sim/vector_regression.py) (Python 3, standard library only) builds each test in [app/baremetal/tests/vector-tests/operations](app/baremetal/tests/vector-tests/operations) and [mem_operations](app/baremetal/tests/vector-tests/mem_operations) once and simulates it with Xcelium on every `VLEN` x `LLEN` x `BUS_WIDTH` configuration: `VLEN` 128, 256 and 512, `LLEN` 32, 64 and 128 and `BUS_WIDTH` 32, 64 and 128 by default (27 configurations).
With `--fast` it runs only three configurations (`VLEN`/`LLEN`/`BUS_WIDTH`): 256/32/32, 256/32/64 and 256/64/32.
The configurations of a test run in parallel, each with its own Xcelium library (`sim/xcelium_vlen<V>_llen<L>_bus<B>.d`).
The tests in [class_disabled](app/baremetal/tests/vector-tests/class_disabled) also run on every configuration, with all vector class parameters set to 0.
Each log goes to `app/baremetal/tests/vector-tests/results/vlen<V>_llen<L>_bus<B>/passed` or `.../failed`, and the script ends with a pass/fail count per configuration.
A simulation that runs longer than `SIM_TIMEOUT` seconds (300 by default) is killed and counted as failed.

The expected results do not depend on `VLEN`: compares stop at `vl`, and reductions, mask compares and `vslide1down` recompute the expected value from their sources and `vl` (see [test/vector_macros.h](app/baremetal/tests/vector-tests/test/vector_macros.h)).
The golden vectors are written for `VLEN = 512`, so a smaller `VLEN` checks fewer elements.

Before running the script, build the tests with **GCC 13**, or turn off auto-vectorization.
Newer GCC releases auto-vectorize the test code with RVV instructions, which changes the code under test and breaks the tests.
If you use a newer GCC, add `-fno-tree-vectorize` to `GCC_RISCV` in [app/baremetal/tests/vector-tests/Makefile](app/baremetal/tests/vector-tests/Makefile).
Check your version with `riscv64-elf-gcc --version`.
The script sets `VEnable`, `VLEN`, `LLEN`, `BUS_WIDTH` and the vector test binary on the xrun command line, so [sim/testbench.sv](sim/testbench.sv) needs no editing.

Then run:

```bash
cd sim                                                   # or run it from any folder
./vector_regression.py                                   # full matrix
./vector_regression.py --fast                            # 3 configurations
VLENS=512 LLENS=32 BUS_WIDTHS=32 ./vector_regression.py  # a single configuration
```

---

## FPGA Prototyping

The [proto/](proto/) folder provides projects for prototyping targeting the **Nexys A7** and the **NetFPGA SUME** boards.

The FPGA environment contains peripherals and a BRAM.
Peripherals include a UART, real-time clock, PLIC, and a mapped button interrupt.

<p align="center">
    <img src="docs/assets/RS5_Environment.png" alt="FPGA Environment Diagram">
</p>

### Prototyping steps

1. Compile the desired application (e.g., `make -C app/baremetal/benchmarks/coremark`).
2. Generate the BRAM initialisation file (.coe):
   ```bash
   cd proto
   ./init_mem.py ../app/baremetal/benchmarks/coremark
   ```
3. Open [proto/RS5/RS5.xpr](proto/RS5/RS5.xpr) (for Nexys A7) or [proto/RS5_SUME](proto/RS5_SUME/RS5.xpr) in Vivado. Right click on BRAM and select the option **Reset output products** in Vivado whenever the `.coe` file is regenerated.
4. Run synthesis, implementation, and generate the bitstream.
5. Program the device. Capture serial output at 115200 baud:
   ```bash
   tio /dev/ttyUSB1 -b 115200 --map ICRNL,INLCRNL
   ```

---

## Architectural compliance (RISCOF)

Compliance testing against the RISC-V formal spec is available in [riscof/](riscof/).
See [riscof/README.md](riscof/README.md) for setup.

---

## Tutorials (in Portuguese)

These tutorials present an overview of RS5, including adding instructions to the pipeline and configuring peripherals. These tutorials were adapted from their presentation at [INOVA-ME](https://www.inf.ufrgs.br/inova-me/) 2025.

<p align="center">
    <a href="docs/tutorials/RS5_1.pdf"><img src="docs/assets/rs5_1.png" height="100"/></a>
    <a href="docs/tutorials/RS5_2.pdf"><img src="docs/assets/rs5_2.png" height="100"/></a>
    <a href="docs/tutorials/RS5_3.pdf"><img src="docs/assets/rs5_3.png" height="100"/></a>
</p>

---

## Cite this work

RS5 was presented at LASCAS'2024. Please cite this work when referring to RS5.

```
Nunes, W. A., Dal Zotto, A. E., Borges, C. d.S., and Moraes, F. G. (2024). RS5: An Integrated Hardware and Software Ecosystem for RISC-V Embedded Systems. In IEEE Latin America Symposium on Circuits and Systems (LASCAS), pages 1--5. https://doi.org/10.1109/LASCAS60203.2024.10506171.
```

---

## Acknowledgements

Other work were published regarding RS5 implementation:

* Vector extensions
    ```
    Nunes, W. A., dos Santos, A. V. C., and Moraes, F. G. (2025). Accelerating Machine Learning with RISC-V Vector Extension and Auto-Vectorization Techniques. In IEEE International Symposium on Circuits and Systems (ISCAS), pages 1--5. https://doi.org/10.1109/ISCAS56072.2025.11043225.
    ```
* Zkne implementation
    ```
    Gewehr, C. G. de A., and Moraes, F. G. (2023). Improving the Efficiency of Cryptography Algorithms on Resource-Constrained Embedded Systems via RISC-V Instruction Set Extensions. In SBC/SBMicro/IEEE/ACM Symposium on Integrated Circuits and Systems Design (SBCCI), pages 1--5. https://doi.org/10.1109/SBCCI60457.2023.10261964.
    ```
* Initial RS5 design
    ```
    Nunes, W. A. (2022). PUC-RS5: A RISC-V processor core for embedded uses. Bachelor's thesis, Pontifical Catholic University of Rio Grande do Sul. https://repositorio.pucrs.br/dspace/handle/10923/26400.
    ```
