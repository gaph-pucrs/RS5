# Vector instructions for the lmfrnet-8b RVV kernels

The RVV kernels of lmfrnet-8b need a few instructions that RS5 doesn't implement yet, so
the app only has scalar kernels for now (`src/cnn_common_vector.h` is an `#error` stub).
This lists what the vector kernels would use and why.

W8A8 is shown: int8 weights and activations, int16 accumulators. W16A16 uses the same
instructions at e16 → e32.

## What RS5 has today

- For widening, `rtl/RS5_pkg.sv` lists only `VWMUL`, `VWMULU` and `VWMULSU`. There is no
  `vwmacc` and no `vwadd`.
- There are no narrowing instructions (`vnsrl`, `vnsra`, `vnclip`).
- Searching `rtl/` for `vxrm`/`vxsat` finds nothing, so the fixed-point CSRs don't exist.

## Instructions to add

| Instruction | Used in | Why | Without it, using existing instructions |
|---|---|---|---|
| **`vwmacc.vx`** | conv, fc | Adds int8 pixel × int8 weights into an int16 accumulator in one instruction. It's `.vx` because the kernel broadcasts one input pixel over the `C_out` weights, the same pattern as the `vmacc.vx` in `../lmfrnet/src/cnn_common_vector.h`. | `vwmul.vx` into a temporary e16 group, then `vadd.vv`. That works, but it takes two instructions and an extra register group per MAC. |
| **`vnclip.wx`** | conv, fc (requantize) | Narrows the int16 accumulator to int8 in one instruction: shift right, round as set by `vxrm`, saturate. This is what `requant` in `src/cnn_common_scalar.h` computes. It's `.wx` because the shift is per layer (`params->shift`), held in a scalar register. | None. RS5 has no narrowing instruction, so e16 results can't become e8 elements. |
| **`vxrm` CSR** | requantize, pools | Selects the rounding `vnclip` applies. It's set once to RDN (round down) with `csrwi vxrm, 2`: the bias already holds the rounding term 2^(s−1) (`quantize.py`), so a plain shift rounds to nearest. | — |
| **`vxsat` CSR** | — | The specification requires `vnclip` to set this flag when it saturates. The kernels never read it. | — |
| `vnsrl.wi` / `vnsrl.wx` *(optional)* | avg_pool (`>> 2`), gap (`>> 4`) | Narrows the e16 pool sum back to int8. The inputs come after ReLU and are ≥ 0, so a logical shift is exactly the floor the Python model uses. It doesn't saturate, and doesn't need to: the average of values ≤ 127 is ≤ 127. | `vnclip.wi`/`.wx`, already needed for the convs: with `vxrm` = RDN it floors too, and its saturation never triggers here. |
| `vwaddu.vv` / `vwaddu.wv` *(optional)* | avg_pool, gap | Sums int8 values into e16 directly: 4 values of up to 127 don't fit in int8. | `vwmulu.vx` by 1 (exists) to widen each load, then `vadd.vv` at e16: one extra instruction per load. Pools are cheap compared with the convs. |

## Already in RS5

- `vsetvli`
- `vle8.v`, `vle16.v`, `vse8.v`: the LSU decodes EW8/EW16 (`rtl/vector/vectorLSU.sv:94-95`)
- `vmax.vx v, v, x0` for ReLU (`VMAX`)
- `vwmul.vx`

Not checked: whether every ALU operation works at SEW = 8.

## Summary

- **Minimum to add:** `vwmacc.vx`, and `vnclip` (`.wx` for the convs, `.wi`/`.wx` for the
  pools) with the `vxrm`/`vxsat` CSRs.
- **Optional:** `vnsrl`, `vwaddu`.
- `vwmacc` could be replaced by `vwmul` + `vadd`. `vnclip` can't be replaced.
- `mhpmcounter27` counts `vmacc`-type instructions. It would need to count `vwmacc` (or
  `vwmul` + `vadd`) so the `vmac` column of the per-layer stats keeps its meaning.
