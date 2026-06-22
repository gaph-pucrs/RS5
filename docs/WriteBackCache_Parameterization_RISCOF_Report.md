# Write-Back Cache: Bus-Width Parameterization & RISCOF Validation

**Author:** Lucas Motta Damo
**Date:** 2026-06-21
**Branch:** `cached` (work staged for a local RS5 branch)
**Modules:** `CacheControllers/rtl/DMWBCtrl.sv`, `riscof/riscof_tb.sv`

This is the follow-up to [WriteBackCache_Report.md](WriteBackCache_Report.md). It
covers two things: making the cache's data buses parameterizable, and validating
the write-back data cache against the RISCOF architectural-compliance suite for
the **I, M, C, A** subsets.

---

## Part 1 — Parameterizable data bus widths

### Motivation

The vector unit will eventually want to read and write **entire cache lines** in
a single core access, and a wider cache↔memory bus lets a line be filled/evicted
in fewer beats. To enable that without disturbing the scalar core, the two data
interfaces of `DMWBCtrl` are now independently parameterizable:

| Parameter    | Default | Scope                                             |
|--------------|---------|---------------------------------------------------|
| `DATA_WIDTH` | 32      | core ↔ cache-controller, and the cache SRAM word  |
| `MEM_WIDTH`  | 32      | cache-controller ↔ main memory (transfer/beat)    |

All byte-enable and data ports scale automatically (`we_i`, `cache_we_o`,
`mem_we_o` become `WIDTH/8` bits; `data_*`, `cache_data_*`, `mem_data_*` become
`WIDTH` bits). `DATA_WIDTH` is an integer multiple of `MEM_WIDTH`
(`DATA_WIDTH == MEM_WIDTH` for the scalar default of 32/32).

### How a line moves now

A line is transferred as `BEATS_PER_LINE = LINE_BYTES / (MEM_WIDTH/8)` beats of
`MEM_WIDTH` bits. When a cache word is wider than a beat, `BEATS_PER_WORD =
DATA_WIDTH / MEM_WIDTH` consecutive beats fill it, each landing in its own byte
**lane** of the word:

```
                DATA_WIDTH cache word (e.g. 64b)
        ┌───────────────────────┬───────────────────────┐
        │   beat 1 (MEM_WIDTH)  │   beat 0 (MEM_WIDTH)   │
        └───────────────────────┴───────────────────────┘
            lane_byte = 4              lane_byte = 0
```

The FSM is unchanged in shape from the original (IDLE → EVICT_READ/WRITE →
FILL_REQ/WRITE); it now iterates over `BEATS_PER_LINE` beats instead of words,
and the cache-side write uses an indexed part-select to place each beat in the
right lane:

```systemverilog
cache_we_o[lane_byte +: MEM_BYTES] = '1;          // enable just this lane
cache_data_o[lane_bit  +: MEM_WIDTH] = mem_data_i; // place the beat
...
mem_data_o = cache_data_i[lane_bit +: MEM_WIDTH];  // evict the beat's lane
```

For the default 32/32 these reduce to full-width assignments, so the generated
logic is identical to before.

### Verification of the parameterization

**1. Lint / elaboration** — Verilator `-Wall` clean for every configuration tried:

| `DATA_WIDTH` | `MEM_WIDTH` | `BEATS_PER_WORD` | Lint |
|---|---|---|---|
| 32 | 32 | 1 | clean |
| 512 | 512 | 1 (whole line in 1 beat) | clean |
| 512 | 32 | 16 | clean |
| 256 | 32 | 8 | clean |
| 128 | 64 | 2 | clean |
| 64 | 32 | 2 | clean |
| 32 | 16 | — (narrow mem) | clean |
| 32 | 8 | — (narrow mem) | clean |

**2. Default functional equivalence** — with 32/32 the local riscv-tests suite
still passes **65/65**, with the same 32 main-memory writes as before the change
(bit-identical behaviour).

**3. Multi-beat functional test** — a standalone self-checking testbench
(`sim/tb_dmwb_unit.sv`) drives cold misses, dirty hits and conflict evictions,
then reads an evicted address back so the value must travel **cache → main
memory → cache** across every beat lane. It passes for all of:

```
DATA=32 MEM=32  PASS      DATA=64  MEM=32  PASS
DATA=32 MEM=16  PASS      DATA=128 MEM=32  PASS
DATA=32 MEM=8   PASS      DATA=64  MEM=16  PASS
```

This is the path the scalar suites cannot reach (they only use 32/32), so it is
what gives confidence in the wide-bus datapath ahead of vector integration.

> Note: a non-default width also requires the cache SRAM and main-memory models
> instantiated around the controller to be widened to match (`DATA_WIDTH` and
> `MEM_WIDTH` respectively). The unit test does this; the system testbenches keep
> 32/32 until the vector unit is wired in.

---

## Part 2 — RISCOF validation (I / M / C / A)

### Setup

| Component | Version |
|-----------|---------|
| RISCOF | 1.25.3 |
| Reference model (Sail) | `sail-riscv` 0.7 (`riscv_sim_rv32d`) |
| Toolchain | `riscv64-elf` GCC 14.2.0 |
| Simulator | Verilator 5.028 (GCC-toolset-14 for coroutines) |
| Arch-test suite | `riscv-arch-test` v3.9.1 |

A focused ISA config was added — `riscof/rs5/imca.yaml` (`RV32IMACUZicsr`) and
`riscof/imca.ini` — so the run targets exactly the requested I, M, C, A subsets
(plus the privileged/CSR tests that the `Zicsr`/U baseline pulls in).

### Putting the cache under test

Out of the box, `riscof/riscof_tb.sv` wired the core's data port straight to RAM —
the cache was never in the loop. Two changes fix that:

1. **Insert the data cache.** `DMWBCtrl` + a cache SRAM now sit on the data path
   (the `0x8…` RAM region); the controller's main-memory port drives a dedicated
   RAM port, and the memory-latency handshake (`DELAY_CYCLES`) was re-keyed off
   the controller's `mem_ce` instead of the core's request. Instruction fetches
   keep their own RAM port and bypass the cache (read-only path). The plugin's
   Verilator command (`riscof/rs5/riscof_rs5.py`) gained `-ICacheControllers/rtl`.

2. **Make the signature dump cache-coherent — the key fix.** RISCOF compares a
   *signature* region that the test writes to memory. With a **write-back** cache,
   those stores stay **dirty in the cache** and may never reach RAM, so the
   stock dump (which reads `RAM_MEM.RAM[]` directly) would read stale memory and
   every store-producing test would fail. The fix reads each signature word
   through a coherent view — the cache copy when the line is resident, otherwise
   main memory:

   ```systemverilog
   if (dcache_ctrl.entries[ix].valid && dcache_ctrl.entries[ix].tag == tg)
       return <word from cache SRAM>;   // dirty/clean cached copy
   else
       return <word from main memory>;  // already written back
   ```

This is the "bug" that had to be fixed for the subsets to work: it is inherent to
testing a write-back cache against a memory-dump-based signature check.

### Results — 100 / 100 pass, 0 fail

`RAM_DELAY_CYCLES = 0`, dual-port memory, branch-prediction + forwarding on:

| Subset | Tests | Result |
|--------|------:|--------|
| RV32I  (`rv32i_m/I`)        | 39 | ✅ all pass |
| RV32M  (`rv32i_m/M`)        |  8 | ✅ all pass |
| RV32C  (`rv32i_m/C`)        | 29 | ✅ all pass |
| RV32A  (`rv32i_m/A`)        |  9 | ✅ all pass |
| Privilege/CSR (`rv32i_m/privilege`) | 15 | ✅ all pass |
| **Total** | **100** | **✅ 100 / 100** |

Under memory latency (`DELAY_CYCLES = 2`): **100 / 100 pass** (re-run of the
same suite, exercising the multi-cycle evict/fill handshake).

### Proof the cache was actually exercised

To rule out the cache being silently bypassed, one test (`I/add-01`) was re-run
with the coherence fix reverted to a plain RAM-only dump:

| Signature dump | vs Sail reference |
|----------------|-------------------|
| Cache-coherent (shipped) | **identical** → test passes |
| Plain RAM-only           | **differs on 1176 lines** |

The entire signature was stale in RAM — it lived dirty in the write-back cache —
which both proves the data cache is in the path and confirms the coherence fix is
load-bearing.

### Reproducing

```sh
source ~/.local/riscof-venv/bin/activate         # riscof installed here
module load verilator riscv64-elf/14.2.0 sail-riscv/0.7
source /opt/rh/gcc-toolset-14/enable
export TRIPLET=riscv64-elf BRANCHPRED=1 FORWARDING=1 DUALPORT_MEM=1 IQUEUE_SIZE=2 DELAY_CYCLES=0
cd riscof
riscof arch-test --clone --get-version 3.9.1
riscof run --suite=riscv-arch-test/riscv-test-suite \
           --env=riscv-arch-test/riscv-test-suite/env \
           --work-dir=/tmp/imca_work --no-browser --config=imca.ini
```

---

## Possible improvements

1. **Pipeline the multi-beat fill/eviction.** As in the first report, each beat
   still costs a request/answer pair; with `BEATS_PER_WORD > 1` the eviction also
   re-reads the same cache word once per lane. A streaming scheme (keep `mem_ce`
   high, two-pointer issue/commit, latch the evicted word once) would cut wide
   evictions to ~1 beat/cycle.
2. **A real wide-bus system testbench.** The system TBs stay 32/32; widening the
   cache-SRAM and main-memory models (and adding a wide vector master) would let
   the riscv-tests / RISCOF flows run end-to-end at, say, 512/512 — true
   line-granular validation rather than the focused unit test.
3. **`Zifencei` / cache flush for self-modifying tests.** The instruction path
   bypasses the cache today, so `fence.i` tests pass trivially; a unified or
   coherent I/D cache would need an explicit flush.
4. **Drive RISCOF from the Makefile.** Add an `imca` target (alongside
   `baseline`/`extensions`) and an env switch to select the cache controller, so
   the cached configuration is a first-class, reproducible CI flow.
5. **Latency sweep in CI.** Run RISCOF across `DELAY_CYCLES ∈ {0,2,5,…}` to keep
   the evict/fill handshake covered as the controller evolves.
