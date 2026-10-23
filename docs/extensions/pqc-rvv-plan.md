# Plan: RVV Instructions for ML-KEM and ML-DSA

This plan adds the standard RVV instructions that the existing RVV code for ML-KEM and ML-DSA uses and RS5 lacks. It also adds the illegal-instruction traps and the fixed-point CSRs needed to test them safely.
The scope is fixed by what the code actually uses: [PQRV](https://github.com/Ji-Peng/PQRV) (`ntt/kyber/ntt_rvv_vlen{128,256}.S`, `ntt/dilithium/ntt_rvv_vlen128.S`) and [mlkem-native](https://github.com/pq-code-package/mlkem-native/tree/main/mlkem/src/native/riscv64) (`rv64v_poly.c`).
ELEN stays 32. Zvkb is out of scope.

Work happens on the local branch `pqc-rvv`, created from `vkeccak`. Each step ends with a one-line commit once its tests pass.

- [Status](#status)
- [What the PQC code needs](#what-the-pqc-code-needs)
- [Design decisions](#design-decisions)
- [Steps](#steps)
- [Test strategy](#test-strategy)
- [Not in scope](#not-in-scope)

## Status

Steps 0–8 are done (2026-10-23). All vector tests pass in Verilator at VLEN 512 (81 tests), `riscv-tests` pass, and PQRV's ML-KEM and ML-DSA kernels match the reference at VLEN 128.

| Kernel (VLEN 128) | Reference | RVV on RS5 |
| --- | --- | --- |
| ML-KEM NTT | 53,467 cycles | 3,701 cycles |
| ML-KEM rejection sampling (504 bytes) | 5,631 cycles | 2,530 cycles |
| ML-DSA NTT | 57,433 cycles | 9,839 cycles |

Changes from the plan:

- **Two RS5 bugs outside the plan were fixed.** `vmerge` wrote only the mask-active elements, which broke the ML-KEM CBD sampler and would have broken the NTTs. `vmv.x.s` zero-extended SEW 8/16 elements instead of sign-extending them. Each has its own commit and test.
- **Step 7 became two apps,** `pqc-rvv-kyber` and `pqc-rvv-dilithium`, because PQRV's Kyber and Dilithium kernels define the same symbols. Besides the NTT product, they check rejection sampling, CBD, reduction and the order conversions.
- **Several unit tests are generated** from a Python model of the spec instead of being ported from Ara (`vssra`/`vssrl` cases 7+, `vext`, `vnarrow`, `vpermute`, `vmerge`). They cover every rounding mode, LMUL up to 8 and the allowed register overlaps, which Ara's tests don't.
- **Test fixes:**
  - The `vsetvl` tests used 64-bit variables with 32-bit asm operands, and assumed `vl` = AVL at any VLEN.
  - The whole-register tests set e64 just to shrink `vl`.
  - The vector test harness now prints unexpected traps instead of restarting the program.
- **`make -C sim lint` was broken** (missing include paths and a fatal timescale warning) and now passes.
- **Not done:** the optional Genus area comparison.

## What the PQC code needs

Instruction variants that appear in the code above and are missing or wrong on RS5:

| Instruction | Variants used | Used by | RS5 today |
| --- | --- | --- | --- |
| `vrgather` | `.vv` | PQRV Kyber/Dilithium NTT (51 / 16 uses), mlkem-native (12) | missing |
| `vrgatherei16` | `.vv` | mlkem-native (8) | missing |
| `vslideup`, `vslidedown` | `.vx` | mlkem-native | missing |
| `vcompress` | `.vm` | PQRV rejection sampling (7), mlkem-native | missing |
| `vcpop` | `.m` | PQRV rejection sampling (7), mlkem-native | decodes as `vmv.x.s` |
| `vid` | `.v` | mlkem-native (6) | missing |
| `vsext` | `.vf2` | PQRV CBD sampling (8) | missing |
| `vnsrl` (`vncvt.x.x.w`), `vnsra` | `.wx` | mlkem-native | missing |
| `vssra` | `.vi`, with `csrwi vxrm, 0` | PQRV Kyber Barrett reduction | missing, no `vxrm` |

Everything else in this code RS5 already has: `vle8/16/32`, `vse*`, whole-register loads/stores, `vadd`, `vsub`, `vand`, `vxor`, `vor`, shifts, `vmul`, `vmulh`, `vwmul`, `vmerge`, `vmseq`, `vmsltu`, `vmv.s.x` and `vmv.v.v`.

Each new instruction is added with all its standard variants (`.vv`/`.vx`/`.vi`, `.wv`/`.wx`/`.wi`, `vf2`/`vf4`, masked forms). The extra forms cost little and keep the decoder honest. `vfirst.m` is added next to `vcpop.m` because both share the same hardware and the same misdecode.

Encodings, checked by assembling with GCC 16.1 (opcode OP-V `1010111`):

| Instruction | funct6 | funct3 categories | Other fields |
| --- | --- | --- | --- |
| `vrgather` | `001100` | OPIVV, OPIVX, OPIVI | |
| `vrgatherei16` | `001110` | OPIVV | shares funct6 with `vslideup` |
| `vslideup` | `001110` | OPIVX, OPIVI | OPMVX `001110` is `vslide1up` |
| `vslidedown` | `001111` | OPIVX, OPIVI | OPMVX `001111` is `vslide1down` |
| `vcompress` | `010111` | OPMVV | vm = 1 only |
| `vcpop.m` / `vfirst.m` / `vmv.x.s` | `010000` | OPMVV | vs1 = `10000` / `10001` / `00000` |
| `vmv.s.x` | `010000` | OPMVX | vs2 = `00000` |
| `vid.v` | `010100` | OPMVV | vs1 = `10001`, vs2 = `00000` |
| `vzext.vf4`/`vsext.vf4`/`vzext.vf2`/`vsext.vf2` | `010010` | OPMVV | vs1 = `00100`/`00101`/`00110`/`00111` |
| `vnsrl` / `vnsra` | `101100` / `101101` | OPIVV, OPIVX, OPIVI | `.wv` / `.wx` / `.wi` |
| `vssrl` / `vssra` | `101010` / `101011` | OPIVV, OPIVX, OPIVI | |
| `vmv<nr>r.v` | `100111` | OPIVI only | OPIVV/OPIVX `100111` is `vsmul`, which runs as `vmv<nr>r` today |
| CSRs | — | — | `vxsat` = 0x009, `vxrm` = 0x00A, `vcsr` = 0x00F |

## Design decisions

1. **Permutations use one serial engine.** `vrgather`, `vrgatherei16`, `vslideup`, `vslidedown` and `vcompress` all run in a new module, `vectorPermute.sv`, that moves one element per cycle. A parameter (`PERMUTE_PARALLEL`) is reserved for a later parallel version. Only the serial mode is implemented; setting the parameter is an elaboration error.
   - The engine uses the register file's two read ports in a 2-stage pipeline. Stage 1 reads the index source (`vs1` group or mask register) and computes the source element number. Stage 2 reads the `vs2` register that holds that element. The writeback stage then writes one element with byte enables. Throughput is one element per cycle after a 2-cycle fill.
   - The spec reserves overlap between `vd` and the source groups for these instructions. So element-by-element writes cannot corrupt a source, and no buffer is needed.
   - Slides go through the same engine: `vslideup` = gather of `i − OFFSET` for `i ≥ OFFSET`, and `vslidedown` = gather of `i + OFFSET`, with zero past VLMAX. This replaces the parallel byte rotator from [elen64-plan.md](elen64-plan.md) with something much smaller, at the cost of `vl` cycles per slide. Slides are rare in the PQC code.
2. **`vid`, `vzext`/`vsext`, `vnsrl`/`vnsra`, `vssrl`/`vssra` are parallel** and go through the existing per-register pipeline:
   - `vid` is computed in the ALU from the register index.
   - The extensions remap the `vs2` read address (`rs2 + (r >> log2 f)`) and pick a chunk of the source register.
   - Narrowing iterates over the `2·LMUL` source registers and writes half of a destination register per step, using byte write enables, so no accumulation buffer is needed.
   - The fixed-point shifts are lane-local, next to the existing shifter.
3. **`vcpop.m`/`vfirst.m` return a scalar** through the existing `res_scalar_o` path, like `vmv.x.s`. The source is the `vs2` mask register latched in `first_operand`, ANDed with `v0` when masked and limited to the first `vl` bits.
4. **Traps:**
   - Decode marks a vector instruction illegal when its funct6/funct3 combination is not implemented or a required field is wrong. Examples: `vm` must be 1 for `vcompress`, `vmv<nr>r` and `vmv.x.s`; `vs2` must be 0 for `vid` and `vmv.v.*`; `simm` must be 0/1/3/7 for `vmv<nr>r`. FP categories, segment loads/stores (nf ≠ 0 outside whole-register), mew = 1 and EEW = 64 are also illegal, as are LOAD-FP/STORE-FP widths that are scalar FP (`flw`, …).
   - The execute stage adds a vector exception from the vector unit for:
     - `vill = 1` on any instruction that depends on `vtype`. `vset*`, whole-register loads/stores and `vmv<nr>r` don't depend on it.
     - Instruction/vtype combinations the spec reserves and RS5 can't run: widening at SEW = 32 or LMUL = 8, narrowing at SEW = 32 or LMUL = 8, `vf2` at SEW = 8, `vf4` at SEW ≤ 16, and `vrgatherei16` with EMUL > 8.
   - `vsetvl{i}` sets `vill` for SEW = 64, reserved SEW, reserved LMUL, reserved `vtype` bits, and SEW/LMUL > ELEN (already handled).
5. **CSRs:** `vxrm` (2 bits) and `vxsat` (1 bit) live in `CSRBank.sv`, with `vcsr` as the {`vxrm`, `vxsat`} view. `vxrm` is wired to the vector unit. Nothing in scope writes `vxsat` from hardware (no saturating instructions), but it must read and write correctly.
6. **No change to timing of existing instructions.** New logic is added beside the existing paths and selected by the operation. The one shared change is the regbank write mux, which also takes the permute engine's writes.
7. **The new ALU-side operations don't start the lanes.** `vid`, the extensions and narrowing are excluded from `enable_lane`, so configurations with `LLEN > 32` don't spend `LLEN/32` idle cycles on them.
8. **Unsigned immediates:** `vssrl`, `vssra`, `vnsrl` and `vnsra` use the zero-extended immediate, like `vsll`/`vsrl`/`vsra` (`imm_replicated` in `vectorUnit.sv`). The engine reads the `vslide*`/`vrgather` `uimm` straight from the instruction.

## Steps

Each step lists the RTL changes, the tests and the commit. A step is done when its new tests and the whole existing vector regression pass in Verilator at VLEN 512, plus a spot run at VLEN 128.

### Step 0: Test infrastructure and baseline

- `sim/RAM_mem.sv`: accept `+BIN=<path>` at run time, with `BIN_FILE` as the default. One Verilator build can then run every test.
- `app/baremetal/tests/vector-tests/Makefile`: add `-fno-tree-vectorize` so GCC ≥ 14 doesn't auto-vectorize the test bodies. The regression script already documents this need.
- New `sim/vector_regression_verilator.sh`: verilate once for a given `VLEN`, then for each test in `operations/` and `mem_operations/`, build it and run with `+BIN=`. Record passed/failed like `vector_regression.sh`.
- Run the baseline on the new branch before any RTL change, and record pre-existing failures in the step's commit message, if any.
- Commit: "Add a Verilator vector regression with a run-time program path".

### Step 1: Illegal-instruction traps and vill

- `RS5_pkg.sv`: widen `iTypeVector_e` to 7 bits. Add the new operations (`VRGATHER`, `VRGATHEREI16`, `VSLIDEUP`, `VSLIDEDOWN`, `VCOMPRESS`, `VCPOP`, `VFIRST`, `VID`, `VZEXT`, `VSEXT`, `VNSRL`, `VNSRA`, `VSSRL`, `VSSRA`) and the CSR addresses `VXSAT`, `VXRM`, `VCSR`. The new operations decode only in their own steps; step 1 adds the enum entries so the validity logic can be written once.
- `decode.sv`:
  - Per-category decode for OPIVV/OPIVX/OPIVI/OPMVV/OPMVX (validity table from the spec) and the field checks listed in the design decisions.
  - Fix the `vcpop`/`vfirst` → `vmv.x.s` and `vsmul` → `vmv<nr>r` misdecodes (they become illegal until step 3).
  - Memory-op validity: nf, mew, width, lumop/sumop.
  - `vector_invalid` feeds `invalid_inst`, and `ctrl.is_vector` is cleared for illegal instructions.
- `vectorCSRs.sv`: extend `cfg_error` (SEW = 64, reserved SEW/LMUL, reserved `vtype` bits). Expose `vill`.
- `vectorUnit.sv`: `illegal_o` for vill and reserved combinations. Gate all internal enables with `!illegal_o`.
- `execute.sv`: OR `illegal_o` into `raise_exception` and the ILLEGAL_INSTRUCTION code. Gate the vector scalar writeback (`write_enable` for `is_vector`) with `!raise_exception`.
- Tests:
  - New `custom/vtraps.c` installs an `mtvec` handler that records `mcause`/`mtval` and skips the instruction. It checks traps for an FP vector op, `vsmul`, a segment load, `vle64`, `vill` after `vsetvli e64`, and narrowing at SEW = 32.
  - It also checks that `vsetvli e64` gives `vtype` = 0x80000000 and `vl` = 0.
  - Full regression to confirm no legal instruction now traps.
- Commit: "Trap on illegal vector instructions and vill".

### Step 2: vxrm/vxsat/vcsr and vssrl/vssra

- `CSRBank.sv`: `vxrm`/`vxsat` registers (only when `VEnable`), `vcsr` read/write as `{vxrm, vxsat}`, and the `vxrm_o` output. `RS5.sv`, `execute.sv`, `vectorUnit.sv` and `vectorALU.sv` pass `vxrm` to the lanes.
- `vectorLane.sv`: `vssrl`/`vssra` per SEW (8/16/32), with the shift amount's low log2(SEW) bits. The rounding increment follows `vxrm`:
  - rnu: v[d−1]
  - rne: v[d−1] & (v[d−2:0] ≠ 0 | v[d])
  - rdn: 0
  - rod: !v[d] & (v[d−1:0] ≠ 0), ORed into the LSB
  - d = 0 means no rounding.
- `decode.sv`: decode `VSSRL`/`VSSRA` for OPIVV/OPIVX/OPIVI. Shift immediates are zero-extended, like `vsll`.
- Tests: port Ara `vssra.c`/`vssrl.c` (drop e64, add LMUL = 2). Add a CSR read/write test for `vxrm`/`vxsat`/`vcsr` and a check that `csrwi vxrm, 0` takes effect on the next instruction.
- Commit: "Add vxrm/vxsat/vcsr and vssrl/vssra".

### Step 3: vid, vcpop.m, vfirst.m

- `vid.v`: ALU result element i = `cycle_count_r · (VLEN/SEW) + i` per SEW, registered like the lane results. Masked-off elements are left alone by the existing write enable.
- `vcpop.m`/`vfirst.m`: in `vectorUnit.sv`, popcount and priority encoder over `first_operand & (vm ? '1 : v0_mask) & (bit index < vl)`. The scalar result is written in the EXEC cycle like `vmv.x.s` (one EXEC cycle, `vlmul_effective = LMUL_1`). `vfirst` returns −1 when no bit is set.
- Tests: port Ara `vid.c`, `vcpop.c`, `vfirst.c`, with masked cases and `vl` below VLMAX. Add a `vid` case at LMUL = 4.
- Commit: "Add vid, vcpop.m and vfirst.m".

### Step 4: vzext/vsext (vf2, vf4)

- `vectorUnit.sv`:
  - For these ops, `vs2_addr = rs2 + (cycle_count >> log2 f)`.
  - The register count is LMUL (destination).
  - Illegal when SEW/f < 8 (from step 1).
- `vectorALU.sv`: extension block. Chunk `c = cycle_count_r & (f−1)` selects VLEN/f bits of `first_operand`. Each EEW = SEW/f element is zero- or sign-extended to SEW. The result is registered and selected by `vector_operation_r`.
- Tests: port Ara `vzext.c`/`vsext.c` (drop e64 destinations), and add LMUL = 2/4 cases where one source register feeds several destination registers.
- Commit: "Add vzext and vsext".

### Step 5: vnsrl/vnsra (.wv, .wx, .wi)

- `vectorUnit.sv`:
  - The register count is `2·LMUL` source registers (`vlmul_effective` doubled; LMUL = 8 is illegal).
  - Source register j: `vs2_addr = rs2 + j`, `vs1_addr = rs1 + (j >> 1)` for `.wv`, and destination `rd + (j >> 1)`.
  - Elements per step = VLEN/(2·SEW). This needs the `total_elements_processed` step size per operation, so `vector_process_done` counts source registers correctly.
  - Write enable: byte half `(j & 1)` of the destination register. For each element k in that half, the global index is `g = j·VLEN/(2·SEW) + k`, written when `g < vl` and (`vm` or `v0[g]`). It is computed from `vl` and `v0_mask` directly, not from `mask_sew*`.
- `vectorALU.sv`: narrowing block. Each 2·SEW element of `first_operand` is shifted right (logical or arithmetic) by `shift[log2(2·SEW)−1:0]`. The amount comes from:
  - `.wv`: element `(j & 1)·VLEN/(2·SEW) + k` of `second_operand`.
  - `.wx`/`.wi`: the replicated scalar or immediate.
  The result is truncated to SEW and placed in half `(j & 1)` of the result.
- Tests:
  - Port Ara `vnsrl.c`/`vnsra.c`. Keep the SEW 8/16 cases, and rebuild the SEW = 32 cases with 64-bit sources written as pairs of 32-bit loads.
  - Add `vncvt.x.x.w`, masked cases, and LMUL = 2/4 cases that cross register halves.
- Commit: "Add vnsrl and vnsra".

### Step 6: Serial permutation engine

- New `rtl/vector/vectorPermute.sv`, with parameter `PERMUTE_PARALLEL` (only 0 implemented). It holds:
  - the element counters `i` (destination, or source for `vcompress`) and `k` (`vcompress` write pointer)
  - a stage-1 register (source element number, valid, in-range, write enable)
  - a stage-2/writeback register (`vd` address, byte enables, data replicated to the element slot)
  - a done flag
- Source element number:
  - `vrgather.vv`: element i of the `vs1` group (EEW = SEW).
  - `vrgatherei16.vv`: element i of the `vs1` group read as EEW = 16. EMUL = 16/SEW·LMUL, so the index register is `rs1 + i / (VLEN/16)`.
  - `.vx`/`.vi`: `x[rs1]` / `uimm`.
  - `vslideup`: i − OFFSET; elements with i < OFFSET are skipped, and the counter starts at OFFSET.
  - `vslidedown`: i + OFFSET.
  - `vcompress`: the next j with `vs1[j]` set (`vs1` is a single mask register, latched once).
  - A source element number ≥ VLMAX writes 0 (gather, slidedown).
  - Masked forms skip elements with `v0[i] = 0`. `vcompress` must be unmasked.
- `vectorUnit.sv`:
  - New state `V_PERM`. `hold_o` stays high until the engine finishes.
  - In `V_PERM`, the regbank read addresses come from the engine.
  - The regbank write inputs (`enable`, `vd_addr`, `result`) are muxed between the existing writeback registers and the engine's. The hazard check uses the muxed signals.
  - Illegal: `vcompress` with vm = 0, and `vrgatherei16` with EMUL > 8 (step 1).
  - Scalar `x[rs1]` is latched at the start.
- `rtl/rtl.f` and the `read_hdl` list in `synthesis/run_logical_synthesis.tcl` get the new file, as `CLAUDE.md` requires.
- Tests:
  - Port Ara `vrgather.c` (`.vv`/`.vx`/`.vi`, adding `vrgatherei16` cases), `vslideup.c`, `vslidedown.c` and `vcompress.c`.
  - Add LMUL = 2/4/8 cases, index ≥ VLMAX, offset ≥ vl, masked cases, `vl` below VLMAX, and a back-to-back case where the next instruction reads `vd`, to exercise the writeback hazard.
- Commit: "Add a serial permutation engine for vrgather, vslideup/down and vcompress". If the engine and the instructions don't land together, split into two commits.

### Step 7: PQC integration test

- New app `app/newlib/tests/pqc-rvv-ntt`, built with `ARCH = rv32imc_zicsr_zve32x`. It contains:
  - PQRV's `ntt/kyber/ntt_rvv_vlen128.S` and `consts_vlen128.c`, plus `ntt/dilithium/ntt_rvv_vlen128.S` and its constants.
  - The scalar reference code for the same functions.
  - A test driver that runs the RVV NTT → pointwise multiply → inverse NTT against a schoolbook multiply mod (xⁿ + 1, q) on fixed inputs, and the rejection sampler (`vmsltu`/`vcpop`/`vcompress`) against a C version.
- Run at VLEN = 128 (the `vlen128` code assumes it). The app must not change the testbench default in a commit.
- Note the cycle counts from `mcycle` against the scalar reference.
- Commit: "Add an ML-KEM/ML-DSA NTT test using PQRV's RVV code".

### Step 8: Wrap-up

- Full regression at VLEN 128, 256 and 512. Verilator lint (`make -C sim lint`).
- Update `docs/extensions/Zve32x-compliance.md` (the decode fixes, traps, new instructions) and `CLAUDE.md` (the Verilator regression command).
- Optional, if time allows: a Genus run at VLEN 256 for area against the `vkeccak` baseline.
- Commit: "Document the new vector instructions and regression".

## Test strategy

- **Unit tests:** the Ara-derived tests already in `vector-tests/operations` use `VSET`/`VLOAD_*`/`VCMP_*` macros and print `PASSED: test/<name>.c!`. New tests follow the same pattern. Ara's upstream tests for every new instruction are the starting point (drop e64, add LMUL > 1 and masked cases).
- **Regression:** every step reruns the whole suite. A step is not committed with a new failure.
- **Configurations:** VLEN 512 (what the existing tests need), plus VLEN 128 for the PQC test and a spot check of the new tests.
- **Ground truth:** expected values come from the spec. When a test case is unclear, a Spike run (`module load riscv-isa-sim`) can settle it.

## Not in scope

- ELEN = 64, Zvkb, the parallel permutation version (parameter reserved), segment loads/stores (now illegal instead of misdecoded), `viota`, mask-logical instructions, the remaining fixed-point instructions (`vsadd`, `vsmul`, `vnclip`, …), carry instructions, and register-group alignment checks (reserved encodings, which RS5 does not trap on).
- Changes to the per-instruction overhead (see the improvements discussion); timing of existing instructions stays as it is.
