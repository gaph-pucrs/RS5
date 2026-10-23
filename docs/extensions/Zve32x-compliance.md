# RS5 Zve32x Compliance Gaps

On the `pqc-rvv` branch, RS5's vector unit implements 68 of the roughly 120 Zve32x operations. Every vector encoding it does not implement now raises an illegal-instruction exception instead of running as a different instruction or as a no-op.
What is still missing is mostly fixed-point arithmetic, widening add/subtract, carry and mask-logic instructions, and segment loads/stores.

The first version of this document (2026-10-19) was written from the RTL of the `vkeccak` branch. This version describes `pqc-rvv` (2026-10-23), where every item listed as fixed has a test in `app/baremetal/tests/vector-tests` that passes in Verilator at VLEN 512.

- [Fixed on this branch](#fixed-on-this-branch)
- [Missing instructions](#missing-instructions)
- [Other gaps](#other-gaps)
- [What to implement](#what-to-implement)
- [Implemented today](#implemented-today)

## Fixed on this branch

These encodings used to execute as another instruction, with no trap. Each one is now either implemented or illegal.

| Instruction | Before | Now |
| --- | --- | --- |
| `vcpop.m`, `vfirst.m` | ran as `vmv.x.s` (vs1 not checked) | implemented |
| `vsmul.vv` / `vsmul.vx` | ran as `vmv<nr>r.v` (funct3 not checked) | illegal (`vmv<nr>r` is OPIVI only, nr = 1/2/4/8) |
| `vlseg`/`vsseg` and other segment forms | ran as the single-field load/store (nf not checked) | illegal |
| `vle<eew>ff.v` | ran as `vle<eew>.v` | unchanged: same result unless an element after the first faults, since `vl` is never trimmed |
| Reserved forms (`vrsub.vv`, `vmsgt.vv`, `vminu.vi`, reductions in OPMVX, `vmv.v.*` with vs2 ≠ 0, …) | executed | illegal: each funct6 is valid only in the forms the spec defines |
| `vle64`/`vse64`, `mew = 1`, scalar FP loads/stores (`flw`, …) on LOAD-FP/STORE-FP | ran as vector loads/stores | illegal |
| `vmerge.vvm/.vxm/.vim` | wrote only the mask-active elements, so inactive elements kept the old `vd` | writes every body element, with `v0` selecting the source |
| `vmv.x.s` at SEW 8/16 | zero-extended element 0 | sign-extends, as the spec requires |

vtype checks:

- `vsetvl{i}` sets `vill` (and `vl = 0`, also in `rd`) for SEW = 64, reserved SEW and LMUL encodings, reserved `vtype` bits, and SEW > LMUL × ELEN.
- While `vill = 1`, every vector instruction that depends on `vtype` traps. `vset*`, whole-register loads/stores and `vmv<nr>r.v` don't depend on it and still run.
- Instruction/vtype combinations the hardware can't run also trap:
  - widening or narrowing with SEW = 32 or LMUL = 8
  - `vzext`/`vsext` with EEW = SEW/f < 8
  - `vrgatherei16` with EMUL > 8

**The thesis said this already worked.** Nunes's master's thesis (PUCRS, 2025, section 5.1) says that for an instruction outside the RS5 subset, "the RS5 will decode it as invalid and raise an exception".
- **Before this branch, the RTL never did that.** At the thesis date (commit 715ba37, 2025-03-05), `decode.sv` already turned an unknown vector op into VNOP.
- **Simulation only printed a warning.** That was `$display("INVALID VECTOR INST!!!")`, added in d54727a (2024-07-06). Commit 24ec73a (2026-07-18) removed it.
- **One case did trap:** with `VEnable = 0`, OP-V, LOAD-FP and STORE-FP decode as INVALID.

Source: [rtl/decode.sv](../../rtl/decode.sv), [rtl/vector/vectorCSRs.sv](../../rtl/vector/vectorCSRs.sv), [rtl/vectorUnit.sv](../../rtl/vectorUnit.sv) (`illegal_o`) and [rtl/execute.sv](../../rtl/execute.sv). Tests: `custom/vtraps.c`, `operations/vmerge.c`, `operations/vmvxs.c`.

## Missing instructions

Zve32x requires every RVV 1.0 integer instruction for SEW 8, 16 and 32, plus all load/store forms. These are not implemented and raise an illegal-instruction exception.

| Group | Instructions | Forms |
| --- | --- | --- |
| Segment loads/stores | `vlseg<nf>e`, `vsseg<nf>e`, `vlsseg`, `vssseg`, `vluxseg`, `vloxseg`, `vsuxseg`, `vsoxseg` | nf 2–8, EEW 8/16/32 |
| Widening add/subtract | `vwaddu`, `vwadd`, `vwsubu`, `vwsub` | `.vv` `.vx` `.wv` `.wx` |
| Add/subtract with carry | `vadc`, `vmadc`, `vsbc`, `vmsbc` | `.vvm` `.vxm` `.vim`, and `vmadc`/`vmsbc` without carry `.vv` `.vx` `.vi` |
| Widening multiply-add | `vwmaccu`, `vwmacc`, `vwmaccsu`, `vwmaccus` | `.vv` `.vx` (`vwmaccus` only `.vx`) |
| Saturating add/subtract | `vsaddu`, `vsadd`, `vssubu`, `vssub` | `.vv` `.vx`, add also `.vi` |
| Averaging add/subtract | `vaaddu`, `vaadd`, `vasubu`, `vasub` | `.vv` `.vx` |
| Fractional multiply | `vsmul` | `.vv` `.vx` |
| Narrowing clip | `vnclipu`, `vnclip` | `.wv` `.wx` `.wi` |
| Widening reductions | `vwredsumu`, `vwredsum` | `.vs` |
| Mask logic | `vmand`, `vmnand`, `vmandn`, `vmor`, `vmnor`, `vmorn`, `vmxor`, `vmxnor` | `.mm` |
| Mask set-before/including/only-first | `vmsbf.m`, `vmsif.m`, `vmsof.m` | |
| Mask prefix sum | `viota.m` | |

## Other gaps

- **No `vstart`.** It reads as 0 and vector instructions are never interrupted midway, so it is never needed. A write to it is ignored instead of resuming from that element.
- **`vxsat` is never set by hardware.** The CSR exists and can be read and written, but no implemented instruction saturates.
- **Register-group alignment is not checked.** A `vd`/`vs` that is not a multiple of LMUL, or an illegal overlap, is a reserved encoding. RS5 runs it instead of trapping. The spec allows that, but traps would make such bugs visible.
- **Fault-only-first loads never trim `vl`.** They run as plain unit-stride loads, so a fault on an element after the first is not turned into a shorter `vl`.
- **Tail and mask-off elements are always left undisturbed.** That is allowed for both the agnostic and undisturbed policies.

## What to implement

1. Decoder correctness
    - [x] Raise illegal instruction for unknown funct6, reserved formats and OPFVV/OPFVF
    - [x] Check vs1 on OPMVV funct6 `010000` (`vmv.x.s` vs `vcpop.m` / `vfirst.m`)
    - [x] Decode `vmv<nr>r.v` only for OPIVI
    - [x] Trap on nf ≠ 0 until segment loads exist, and on EEW = 64 loads/stores
2. vtype checks
    - [x] Set `vill` for SEW = 64 and for reserved LMUL
    - [x] Trap on any vector instruction that depends on vtype while `vill = 1`
3. Integer arithmetic
    - [x] `vzext`/`vsext` vf2/vf4
    - [ ] Widening add/subtract
    - [ ] `vadc`, `vmadc`, `vsbc`, `vmsbc`
    - [x] Narrowing shifts `vnsrl`, `vnsra`
    - [ ] Widening multiply-add `vwmacc*`
4. Fixed-point
    - [x] `vxrm`, `vxsat`, `vcsr` CSRs
    - [x] Scaling shifts `vssrl`, `vssra`
    - [ ] Saturating, averaging, `vsmul`, `vnclip(u)`
5. Reductions and masks
    - [ ] `vwredsum(u)`
    - [x] `vcpop.m`, `vfirst.m`, `vid.v`
    - [ ] Mask logic `.mm`, `vmsbf`/`vmsif`/`vmsof`, `viota.m`
6. Permutation
    - [x] `vslideup`/`vslidedown` by any offset (`.vx`, `.vi`)
    - [x] `vrgather`, `vrgatherei16`
    - [x] `vcompress.vm`
7. Loads and stores
    - [ ] Segment loads/stores, all addressing modes
    - [ ] Fault-only-first `vle<eew>ff.v`, with vl trimming on a fault

## Implemented today

RS5 implements these 68 operations (`iTypeVector_e` in [rtl/RS5_pkg.sv](../../rtl/RS5_pkg.sv)), plus loads and stores.

| Group | Instructions |
| --- | --- |
| Configuration | `vsetvli`, `vsetivli`, `vsetvl` |
| Loads/stores | unit-stride `vle`/`vse` 8/16/32, strided `vlse`/`vsse`, indexed ordered and unordered, whole-register `vl<n>re`/`vs<n>r`, mask `vlm.v`/`vsm.v`, fault-only-first (as unit-stride) |
| Add/subtract | `vadd`, `vsub`, `vrsub` |
| Logic and shifts | `vand`, `vor`, `vxor`, `vsll`, `vsrl`, `vsra` |
| Compares | `vmseq`, `vmsne`, `vmsltu`, `vmslt`, `vmsleu`, `vmsle`, `vmsgtu`, `vmsgt` |
| Min/max | `vminu`, `vmin`, `vmaxu`, `vmax` |
| Multiply | `vmul`, `vmulh`, `vmulhu`, `vmulhsu`, `vwmul`, `vwmulu`, `vwmulsu` |
| Divide | `vdivu`, `vdiv`, `vremu`, `vrem` |
| Multiply-add | `vmacc`, `vnmsac`, `vmadd`, `vnmsub` |
| Reductions | `vredsum`, `vredand`, `vredor`, `vredxor`, `vredminu`, `vredmin`, `vredmaxu`, `vredmax` |
| Moves and merge | `vmv.v.*`, `vmerge`, `vmv.x.s`, `vmv.s.x`, `vmv<nr>r.v` |
| Extension and narrowing | `vzext.vf2/vf4`, `vsext.vf2/vf4`, `vnsrl`, `vnsra` (`.wv` `.wx` `.wi`) |
| Fixed point | `vssrl`, `vssra` (`.vv` `.vx` `.vi`), with `vxrm`/`vxsat`/`vcsr` |
| Mask and index | `vcpop.m`, `vfirst.m`, `vid.v` |
| Slides | `vslide1up.vx`, `vslide1down.vx`, `vslideup`/`vslidedown` (`.vx` `.vi`) |
| Gather and compress | `vrgather` (`.vv` `.vx` `.vi`), `vrgatherei16.vv`, `vcompress.vm` |

`vrgather`, `vrgatherei16`, `vslideup`, `vslidedown` and `vcompress` run in a serial engine ([rtl/vector/vectorPermute.sv](../../rtl/vector/vectorPermute.sv)) that moves one element per cycle. The `PERMUTE_PARALLEL` parameter is reserved for a whole-register version.
