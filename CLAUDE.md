# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

RS5 is a parameterizable, pipelined RV32 RISC-V core in SystemVerilog (GAPH/PUCRS). Optional ISA extensions (M/Zmmul, A/Zaamo/Zalrsc, C/Zcb, Zicond, Zihpm, Zbkb, Zkne, Zknh, Xkyber, Zve32x vector, Xosvm) are all selected by parameters on the top-level `rtl/RS5.sv`. Detailed per-parameter/extension docs live in `docs/README.md`.

`RingBuffer/` is a git submodule (used for the instruction queue) — run `git submodule update --init` if it is empty.

## Git

**Never commit.** The user makes all commits. Use git only to explore or debug (`status`, `diff`, `log`, `blame`, `show`, …). Don't stage or commit changes, and don't run commands that rewrite history or the working tree.

## Environment setup

Tools are not on the default `PATH`; load them with environment modules. Shell state does not persist between Bash tool calls, so put the loads in the same command that needs them. `module` only works in a login bash, so wrap the command: `bash -lc 'module load verilator; source /opt/rh/gcc-toolset-15/enable; make -C sim'`.

```bash
module load xcelium                         # xrun
module load questa                          # vsim
module load verilator && source /opt/rh/gcc-toolset-15/enable   # Verilator needs the newer GCC
module load riscv64-elf                     # riscv64-elf-gcc toolchain
```

Python: `source ~/lmfrnet/bin/activate` provides a venv that includes torchvision. If you need a different environment, you can create a venv at the project root. `.gitignore` doesn't list a venv directory, so tell the user if you create one.

## Commands

Toolchain: `riscv64-elf-*` (RISCOF accepts a different triple via `TRIPLET=`), Verilator with C++ coroutine support.

```bash
# Build an application (produces <app>.bin / .lst / .elf in the app dir)
make -C app/riscv-tests            # default test program used by the testbench
make -C app/coremark               # any app/<name> works the same way

# Simulate with Verilator (verilate + run); output in sim/results/Output.txt, profiling in sim/results/Report.txt
make -C sim
make -C sim lint                   # lint only (note: does not pass -I../rtl/vector or RingBuffer include dirs)
make -C sim clean

# Commercial simulators
cd sim && vsim -c -do sim.do       # Questa/Modelsim
cd sim && xrun -f sim.xrun         # Xcelium

# Architectural compliance (requires sail-riscv + riscof in a venv)
make -C riscof                     # baseline ISA (RV32IMZicsr_Zihpm)
make -C riscof extensions          # all supported extensions except RVV
make -C riscof all
BRANCHPRED=0 FORWARDING=0 IQUEUE_SIZE=1 DELAY_CYCLES=3 make -C riscof   # vary core config
```

Running a different program in simulation: the testbench does not take a command-line argument — edit `BIN_FILE` (and core config localparams such as `VEnable`, `VLEN`, extension enables) at the top of `sim/testbench.sv`, then `make -C sim`.

Vector-specific flows (both use Xcelium):
- `app/vector-tests` must be built with GCC < 14 (`module load riscv64-elf/13.2.0`): GCC 14+ auto-vectorizes the tests' own C code and most of them fail. Run them at VLEN 512 (the testbench default). Expected on HEAD: 67/69 pass (`operations` + `mem_operations`); `vsetvl` and `vsetvli` fail.
- `sim/vector_regression.sh` — builds each test in `app/vector-tests/operations` one at a time and sorts outputs into `results/passed|failed` by grepping for `PASSED: test/<file>!`.
- `sim/vector_benchmarks.py` — sweeps `BUS_WIDTH` × `VLEN` over `app/vector-benchmarks/*`.

## Architecture

### RTL (`rtl/`)
- `RS5_pkg.sv` — shared enums and the packed structs passed between pipeline stages (`decode_ctrl_t`, `exec_ctrl_t`, `wb_ctrl_t`, …). Decoding produces per-unit control fields in these structs rather than a single global "instruction operation" enum (that was removed in a recent refactor) — follow the struct-based pattern when adding instructions.
- `RS5.sv` — top level: parameters, instantiates `fetch` → `decode` (+ `regbank`) → `execute` → `mem_access` → `retire`, plus `CSRBank` and optional `mmu`s (Xosvm).
- `execute.sv` hosts the ALU/branch logic and instantiates the extension units (`mul`, `div`, `amo`/`lrsc`, `aes_unit`, `sha2_unit`, `xkyber`, `vectorUnit`). `rtl/vector/` holds the vector lanes, LSU, regbank, reductions, slides.
- `decompresser.sv` expands C/Zcb instructions in fetch; `plic.sv` and `rtc.sv` are optional peripherals instantiated outside the core (testbench/FPGA top).
- `rtl/rtl.f` is the file list used by external flows; keep it updated when adding RTL files.

**Stall vs. hold** (central to pipeline control):
- `stall` is an external input — the data bus is busy; it freezes the pipeline (fetch can still proceed into the IQUEUE buffer). The vector unit (`vectorUnit` and everything under `rtl/vector/` except `vectorCSRs`) also holds all of its state while `stall` is high, and blocks the vector regbank write. Every new vector flop needs the same `else if (stall)` hold. `div` (scalar and vector lanes) holds on `stall` too. `mul` only holds its last cycle by default (scalar pipeline); vector lanes instantiate it with `FREEZE_ON_STALL = 1` so it holds everything. The scalar regbank write in `retire` is *not* gated by stall, so the bus must hold the read data during a stall (the testbench and the SoC `dig_top` do).
- `hold` is internal, driven by `execute` — multi-cycle extension units (mul/div, AMO, crypto, vector) assert it to freeze fetch/decode while they finish.
- Data/control hazards and busy instruction memory insert bubbles instead.

### Simulation environment (`sim/`)
`testbench.sv` instantiates RS5, `RAM_mem.sv`, `plic`, and `rtc`, and decodes a simple memory map by `mem_address[31:28]`: `0x2…` RTC, `0x4…` PLIC, `0x8…` testbench MMIO. Writes to `0x80001000`/`0x80004000` print a char, `0x80002000` prints an integer, and a write to `0x80000000` ends the simulation. Software in `app/` relies on these addresses.

`RAM_DELAY_CYCLES` > 0 stalls **every** RAM request for that many cycles (modeled on the SoC's `axil2axi4` bridge), and the testbench holds the read data during the stall. `0` never stalls. `app/vector-stall-test` (vector loads/stores) and `app/vector-stall-ops-test` (multiply, reductions, slides, divide) run under stall and print `Passed.`/`Failed.`. A RAM stall can only start on an instruction's first cycle (the request on the bus comes from the previous instruction). `STALL_INJECT` > 0 also stalls 1-4 cycles on about 1 in N cycles, independent of requests, which is what stalls multi-cycle vector operations mid-way; run the stall tests with it (e.g. 5) too.

### Software (`app/`)
Most apps include `app/common/common.mk`, setting `ARCH` (e.g. `rv32im_zicsr_zkne_zknh`) and `MEM_SIZE` before the include. The `-march` string drives C defines (e.g. `zbkb` → native intrinsics vs. emulation, `_xkyber` → `KYBER_ISE` and is stripped from the gcc `-march`). `app/common/` holds `crt0.S`, `link.ld`, newlib stubs, and shared crypto libs. Stamp files force a rebuild when `ARCH`/`MEM_SIZE` change. `app/riscv-tests` has its own standalone Makefile.

With a `zve32x` `ARCH`, GCC emits its own RVV code, including for plain array initializers (block moves). A test that must exercise only its inline-asm vector instructions needs `CFLAGS += -fno-tree-vectorize -mstringop-strategy=scalar` after the include (see `app/vector-stall-test/Makefile`). Check the `.lst` to confirm.

### Other
- `riscof/` — RISCOF plugin for RS5 (`rs5/riscof_rs5.py`, `riscof_tb.sv`) and sail reference; ISA configs in `rs5/*.yaml`. The Verilator model is built once and reused across tests.
- `proto/` — Vivado projects for Nexys A7 (`RS5/`) and NetFPGA SUME (`RS5_SUME/`); `proto/init_mem.py ../app/<name>` generates the BRAM `.coe` (reset BRAM output products in Vivado after regenerating).
- `synthesis/` — ASIC logical synthesis / power analysis scripts.
