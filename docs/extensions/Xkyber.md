# Xkyber

Xkyber is a RISC-V ISA extension for **Kyber** lattice-based cryptography acceleration.
This extension provides tightly-coupled instructions for the core arithmetic and sampling primitives of the CRYSTALS-Kyber / ML-KEM (FIPS 203) key-encapsulation mechanism, operating over the ring **Z_q** with **q = 3329**, targeted at embedded RISC-V harts that need hardware-accelerated post-quantum cryptography without a dedicated cryptographic coprocessor.

## Overview

Xkyber adds six custom instructions, split into two classes:

- **Single-cycle, dual-lane instructions** — `KYBER.ADD`, `KYBER.SUB`, `KYBER.CBD2`, `KYBER.CBD3` — each operate on two 12-bit ring coefficients packed into one 32-bit register, and complete in the same cycle as an ordinary ALU instruction.
- **Multi-cycle, scalar instructions** — `KYBER.MUL`, `KYBER.COMPRESS` — operate on a single coefficient, reuse the hart's 16×16 multiplier over several cycles, and assert a hold signal that stalls the pipeline until the result is ready.

All arithmetic is performed modulo the Kyber prime **q = 3329**.

## Coefficient Encoding

Xkyber packs two ring coefficients ("lanes") into a single 32-bit register so that dual-lane instructions can process two coefficients per issue.

|  FIELD  | 31:28 |    27:16    | 15:12 |    11:0    |
| ------- | ----- | ----------- | ----- | ---------- |
| CONTENT |   0   | HIGH (coef) |   0   | LOW (coef) |
|   SIZE  |   4   |     12      |   4   |     12     |

Each lane holds an unsigned value in the range `[0, q-1]`. The 4-bit gaps at `[31:28]` and `[15:12]` act as guard bits so that dual-lane addition/subtraction can be carried out with a single ordinary 32-bit adder without inter-lane carry/borrow, since `2*(q-1) < 2^13`.

For the scalar instructions (`KYBER.MUL`, `KYBER.COMPRESS`) only the LOW lane (`rd[11:0]`) carries a defined result; the HIGH lane and guard bits are reserved for these two instructions.

## Instruction Encoding

Note: the reference implementation exposes an already-decoded operator signal rather than raw instruction bits. The encoding below is one consistent mapping of that decode onto the RISC-V `custom-0` opcode space.

All Xkyber instructions use the R-type format under the `custom-0` opcode (`0001011`), with `funct3` selecting the operation:

|  FIELD  | 31:25  | 24:20 | 19:15 | 14:12  | 11:7 |  6:0   |
| ------- | ------ | ----- | ----- | ------ | ---- | ------ |
| CONTENT | funct7 |  rs2  |  rs1  | funct3 |  rd  | opcode |

| funct3 | Mnemonic         |
| ------ | ---------------- |
| `000`  | `KYBER.ADD`      |
| `001`  | `KYBER.SUB`      |
| `010`  | `KYBER.MUL`      |
| `011`  | `KYBER.COMPRESS` |
| `100`  | `KYBER.CBD2`     |
| `101`  | `KYBER.CBD3`     |

`opcode = 0001011` (`custom-0`) for every Xkyber instruction.

For `KYBER.ADD`, `KYBER.SUB`, `KYBER.MUL`, `KYBER.CBD2` and `KYBER.CBD3`, `rs2` supplies the second source register and `funct7` is reserved (should be `0000000`). `KYBER.COMPRESS` instead repurposes the `rs2` field as a 5-bit immediate, the same way `slli`/`srli` repurpose it as `shamt`.

## Instructions

### KYBER.ADD

Dual-lane modular addition.

```
rd[27:16] = (rs1[27:16] + rs2[27:16]) mod q
rd[11:0]  = (rs1[11:0]  + rs2[11:0])  mod q
```

Completes in a single cycle; does not assert the hold signal.

### KYBER.SUB

Dual-lane modular subtraction.

```
rd[27:16] = (rs1[27:16] - rs2[27:16]) mod q
rd[11:0]  = (rs1[11:0]  - rs2[11:0])  mod q
```

Negative intermediate results are corrected back into `[0, q-1]` by conditionally adding `q` to each lane. Completes in a single cycle.

### KYBER.MUL

Scalar modular multiplication using Barrett reduction.

```
rd[11:0] = (rs1[11:0] * rs2[11:0]) mod q
```

Only the LOW lane of `rs1`/`rs2` is read as the operand; the HIGH lane is not used. Only `rd[11:0]` is defined on completion, `rd[31:12]` is unspecified.

Since no single-cycle 32×32 multiplier is assumed, `KYBER.MUL` reuses the hart's 16×16 multiplier over multiple cycles to build the full product, then reduces it modulo `q` using the Barrett constant `⌊2^24 / q⌋ = 5039`. The instruction asserts the hold signal, stalling the pipeline until the internal reduction pipeline reaches its final stage (on the order of 9–10 cycles in the reference implementation).

### KYBER.COMPRESS

Scalar Kyber `Compress_q(x, d)` function, used when serializing ciphertext and public-key coefficients into fewer bits.

```
rd[11:0] = round((2^d / q) * rs1[11:0]) mod 2^d
```

`d` is supplied as a 5-bit immediate in the `rs2` field position; the values defined by ML-KEM/Kyber for ciphertext and public-key compression are `1`, `4`, `5`, `10` and `11`. The instruction is implemented as a fixed-point multiply by the precomputed reciprocal `⌊2^24 / q⌋` (12 bits of fractional precision, constant `0xB760`), followed by round-to-nearest and masking to `d` bits. Like `KYBER.MUL`, it reuses the shared multiplier over multiple cycles and asserts the hold signal until the result is valid.

If `d` is not one of the values above, the reference implementation masks the result to 12 bits (i.e. no masking is applied) rather than raising a fault; software should not rely on this behavior for out-of-range `d`.

### KYBER.CBD2 / KYBER.CBD3

Dual-lane centered binomial distribution (CBD) sampling, used to sample Kyber's secret and error polynomials.

```
KYBER.CBD2 (eta = 2):
  rd[27:16] = CBD_2(rs1, high lane) mod q
  rd[11:0]  = CBD_2(rs1, low lane)  mod q

KYBER.CBD3 (eta = 3):
  rd[27:16] = CBD_3(rs1, high lane) mod q
  rd[11:0]  = CBD_3(rs1, low lane)  mod q
```

Where `CBD_eta(x) = popcount(a) - popcount(b)`, with `a` and `b` the two `eta`-bit halves of a `2*eta`-bit pseudorandom group taken from `rs1` (one group per lane, per Kyber's `CBD_eta` sampling algorithm). The signed difference (range `[-eta, +eta]`) is centered into `[0, q-1]` by conditionally adding `q`. Both instructions complete in a single cycle and do not assert the hold signal.

## Pipeline Interaction

`KYBER.MUL` and `KYBER.COMPRESS` are the only multi-cycle Xkyber instructions: while either is in flight, the extension asserts a hold signal to the issuing hart, stalling the pipeline until the internal reduction/compression state machine reaches its final stage and the result is latched into `rd`. All other Xkyber instructions (`KYBER.ADD`, `KYBER.SUB`, `KYBER.CBD2`, `KYBER.CBD3`) behave like ordinary single-cycle ALU instructions and never stall the pipeline.
