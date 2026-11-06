# LMFRNet W8A8

LMFRNet with 8-bit weights and activations and 16-bit accumulators, from
**lmfrnet-utils/quantize.py**. The same sources also build W16A16 (16-bit values,
32-bit accumulators) with `PRECISION=w16a16`. The model, kernels and layer order are the
same as **../lmfrnet**; what changes is the arithmetic of each conv/fc:

```
acc = bias + sum(x * w)                          int16 (W16A16: int32), wrapping
out = sat8(acc >> s)                             s = <layer>_SHIFT in quant_shifts.h
then ReLU (except fc)
```

The bias holds the rounding term `2^(s-1)`, so `acc >> s` rounds to nearest.

Only the scalar kernels exist. The RVV ones need `vwmacc.vx` and `vnclip` (with the
`vxrm` CSR), which RS5 doesn't implement yet, so `VEn=1` stops with an `#error`.

## Generating the headers

This app reuses the venv, the CIFAR-10 download and the lmfrnet-utils submodule of
**../lmfrnet**, so run **../lmfrnet/setup.sh** first. Then:

```sh
./setup.sh [w8a8|w16a16]
```

writes `params/`, `dataset/`, `quant_shifts.h` and `golden.txt` (the checksums of image1
computed by the Python integer model). Building against headers of the other precision
stops with a `_Static_assert`.

## Running natively (NO_RISCV)

```sh
make check-native [PRECISION=w16a16]
```

Builds **src/lmfrnet.c** with the host gcc, runs image1, and compares its per-layer
checksums with `golden.txt`. `make run-native` prints the whole output. After switching
`PRECISION`, run `make clean-native` and `./setup.sh` with the same precision.

## Running on RS5

```sh
make [PRECISION=w16a16]
```

builds the scalar RV32 binary; its checksums must match the native run.
