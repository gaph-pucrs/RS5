// Copyright 2026 GAPH - PUCRS
// SPDX-License-Identifier: SHL-0.51
//
// Illegal-instruction tests for the Zve32x conformance baseline (P0).
// Each case executes one raw instruction word and checks that it raised an
// illegal-instruction trap (mcause = 2, mtval = the instruction) or, for the
// legal cases, that it did not trap. The trap handler lives in test.S.

#include <stdint.h>

#include "vector_macros.h"

// Reserved and unsupported encodings, rejected by the decoder
void TEST_CASE1(void) {
  VSET(16, e8, m1);
  EXPECT_ILLEGAL(1, 0x362180d7); // OPIVV funct6 001101 (unassigned)
  EXPECT_ILLEGAL(2, 0x0e2180d7); // vrsub.vv (no .vv form)
  EXPECT_ILLEGAL(3, 0x1221b0d7); // vminu.vi (no .vi form)
  EXPECT_ILLEGAL(4, 0x6a21b0d7); // vmsltu.vi (no .vi form)
  EXPECT_ILLEGAL(5, 0x7a2180d7); // vmsgtu.vv (no .vv form)
  EXPECT_ILLEGAL(6, 0x0225e0d7); // vredsum.vx (no .vx form)
  EXPECT_ILLEGAL(7, 0xfe21b0d7); // OPIVI funct6 111111 (unassigned)
  EXPECT_ILLEGAL(8, 0x3a21a0d7); // vslide1up.vv (no .vv form)
  EXPECT_ILLEGAL(9, 0x4220a5d7); // vmv.x.s with vs1 != 0
  EXPECT_ILLEGAL(10, 0x402025d7); // vmv.x.s with vm = 0
  EXPECT_ILLEGAL(11, 0x4225e0d7); // vmv.s.x with vs2 != 0
  EXPECT_ILLEGAL(12, 0x5e2180d7); // vmv.v.v with vs2 != 0
  EXPECT_ILLEGAL(13, 0x9e413157); // vmv<nr>r.v with nr = 3
  EXPECT_ILLEGAL(14, 0x9e20b0d7); // vmv2r.v v1, v2 (vd not aligned)
  EXPECT_ILLEGAL(15, 0x9e30b157); // vmv2r.v v2, v3 (vs2 not aligned)
  EXPECT_ILLEGAL(16, 0x9c2030d7); // vmv1r.v with vm = 0
  EXPECT_ILLEGAL(17, 0x9e2000d7); // vmv1r.v as .vv
  EXPECT_ILLEGAL(18, 0x82d675d7); // vsetvl with funct7 != 1000000
  EXPECT_ILLEGAL(19, 0x00110057); // vadd.vv v0, v1, v2, v0.t (vd = v0)
  EXPECT_ILLEGAL(20, 0x5c110057); // vmerge.vvm v0, v1, v2, v0 (vd = v0)
  EXPECT_ILLEGAL(21, 0x00052087); // flw (LOAD-FP width 010)
  EXPECT_ILLEGAL(22, 0x00152027); // fsw (STORE-FP width 010)
  EXPECT_ILLEGAL(23, 0x00053087); // fld (LOAD-FP width 011)
  EXPECT_ILLEGAL(24, 0x00051087); // LOAD-FP width 001
  EXPECT_ILLEGAL(25, 0x00054087); // LOAD-FP width 100
  EXPECT_ILLEGAL(26, 0x02057087); // vle64.v (EEW = 64)
  EXPECT_ILLEGAL(27, 0x020570a7); // vse64.v (EEW = 64)
  EXPECT_ILLEGAL(28, 0x12050087); // vle8.v with mew = 1
  EXPECT_ILLEGAL(29, 0x22050107); // vlseg2e8.v (segment, until P8)
  EXPECT_ILLEGAL(30, 0x2ab50107); // vlsseg2e8.v (segment, until P8)
  EXPECT_ILLEGAL(31, 0x22050127); // vsseg2e8.v (segment, until P8)
  EXPECT_ILLEGAL(32, 0x03050087); // vle8ff.v (fault-only-first, until P8)
  EXPECT_ILLEGAL(33, 0x02150087); // unit-stride load lumop 00001
  EXPECT_ILLEGAL(34, 0x030500a7); // unit-stride store sumop 10000
  EXPECT_ILLEGAL(35, 0x42850207); // vl3re8.v (nf = 2)
  EXPECT_ILLEGAL(36, 0x22850087); // vl2re8.v v1 (vd not aligned)
  EXPECT_ILLEGAL(37, 0x00850087); // vl1re8.v with vm = 0
  EXPECT_ILLEGAL(38, 0x028550a7); // vs1r.v with width 101
  EXPECT_ILLEGAL(39, 0x228500a7); // vs2r.v v1 (vs3 not aligned)
  EXPECT_ILLEGAL(40, 0x02b55087); // vlm.v with width 101
  EXPECT_ILLEGAL(41, 0x00b50087); // vlm.v with vm = 0
  EXPECT_ILLEGAL(42, 0x22b50107); // vlm.v with nf = 1
  EXPECT_ILLEGAL(43, 0x00050007); // vle8.v v0, (a0), v0.t (vd = v0)
  EXPECT_ILLEGAL(44, 0x04250007); // vluxei8.v v0, (a0), v2, v0.t (vd = v0)
  EXPECT_LEGAL(45, 0x022180d7); // vadd.vv v1, v2, v3
  EXPECT_LEGAL(46, 0x60110057); // vmseq.vv v0, v1, v2, v0.t (mask dest)
  EXPECT_LEGAL(47, 0x00802057); // vredsum.vs v0, v8, v0, v0.t (reduction)
  EXPECT_LEGAL(48, 0x422025d7); // vmv.x.s a1, v2
  EXPECT_LEGAL(49, 0x4205e0d7); // vmv.s.x v1, a1
  EXPECT_LEGAL(50, 0x9e40b157); // vmv2r.v v2, v4
  EXPECT_LEGAL(51, 0x02050087); // vle8.v v1, (a0)
  EXPECT_LEGAL(52, 0x00050087); // vle8.v v1, (a0), v0.t
  EXPECT_LEGAL(53, 0x00050027); // vse8.v v0, (a0), v0.t (store data v0)
  EXPECT_LEGAL(54, 0x22850107); // vl2re8.v v2, (a0)
  EXPECT_LEGAL(55, 0x028500a7); // vs1r.v v1, (a0)
  EXPECT_LEGAL(56, 0x02b50087); // vlm.v v1, (a0)
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();

  EXIT_CHECK();
}
