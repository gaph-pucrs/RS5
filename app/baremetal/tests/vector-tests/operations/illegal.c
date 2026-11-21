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
  // vsmul.vv v1, v2, v0 (vmv<nr>r has no .vv form): RS5 does not implement vsmul yet
  SKIP_ON_SAIL(EXPECT_ILLEGAL(17, 0x9e2000d7));
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
  // Segments and fault-only-first are legal in Zve32x and run on Sail; RS5 traps until they are implemented
  SKIP_ON_SAIL(EXPECT_ILLEGAL(29, 0x22050107)); // vlseg2e8.v
  SKIP_ON_SAIL(EXPECT_ILLEGAL(30, 0x2ab50107)); // vlsseg2e8.v
  SKIP_ON_SAIL(EXPECT_ILLEGAL(31, 0x22050127)); // vsseg2e8.v
  SKIP_ON_SAIL(EXPECT_ILLEGAL(32, 0x03050087)); // vle8ff.v
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
  // vredsum.vs v0, v8, v0, v0.t: RVV 1.0 lets a masked reduction write its scalar
  // result to v0; Sail 0.12 traps
  SKIP_ON_SAIL(EXPECT_LEGAL(47, 0x00802057));
  EXPECT_LEGAL(48, 0x422025d7); // vmv.x.s a1, v2
  EXPECT_LEGAL(49, 0x4205e0d7); // vmv.s.x v1, a1
  EXPECT_LEGAL(50, 0x9e40b157); // vmv2r.v v2, v4
  EXPECT_LEGAL(51, 0x02050087); // vle8.v v1, (a0)
  EXPECT_LEGAL(52, 0x00050087); // vle8.v v1, (a0), v0.t
  EXPECT_LEGAL(53, 0x00050027); // vse8.v v0, (a0), v0.t (store data v0)
  EXPECT_LEGAL(54, 0x22850107); // vl2re8.v v2, (a0)
  EXPECT_LEGAL(55, 0x028500a7); // vs1r.v v1, (a0)
  EXPECT_LEGAL(56, 0x02b50087); // vlm.v v1, (a0)
  EXPECT_ILLEGAL(57, 0x422180d7); // vadc.vvm with vm = 1 (reserved)
  EXPECT_ILLEGAL(58, 0x4a2180d7); // vsbc.vvm with vm = 1 (reserved)
  EXPECT_ILLEGAL(59, 0x4822b0d7); // vsbc.vim (no .vi form)
  EXPECT_ILLEGAL(60, 0x40110057); // vadc.vvm v0, v1, v2, v0 (vd = v0)
  EXPECT_ILLEGAL(61, 0x48110057); // vsbc.vvm v0, v1, v2, v0 (vd = v0)
  EXPECT_LEGAL(62, 0x402180d7); // vadc.vvm v1, v2, v3, v0
  EXPECT_LEGAL(63, 0x4025c0d7); // vadc.vxm v1, v2, a1, v0
  EXPECT_LEGAL(64, 0x4022b0d7); // vadc.vim v1, v2, 5, v0
  EXPECT_LEGAL(65, 0x482180d7); // vsbc.vvm v1, v2, v3, v0
  EXPECT_LEGAL(66, 0x4825c0d7); // vsbc.vxm v1, v2, a1, v0
  EXPECT_ILLEGAL(67, 0x4e22b0d7); // vmsbc.vi (no .vi form)
  EXPECT_ILLEGAL(68, 0x4c22b0d7); // vmsbc.vim (no .vi form)
  EXPECT_LEGAL(69, 0x44110057); // vmadc.vvm v0, v1, v2, v0 (mask dest)
  EXPECT_LEGAL(70, 0x462180d7); // vmadc.vv v1, v2, v3
  EXPECT_LEGAL(71, 0x4622b0d7); // vmadc.vi v1, v2, 5
  EXPECT_LEGAL(72, 0x4425c0d7); // vmadc.vxm v1, v2, a1, v0
  EXPECT_LEGAL(73, 0x4c2180d7); // vmsbc.vvm v1, v2, v3, v0
  EXPECT_LEGAL(74, 0x4e25c0d7); // vmsbc.vx v1, v2, a1
}

// Reserved register groups and SEW/LMUL, rejected by the vector unit with
// the current vtype
void TEST_CASE2(void) {
  VSET(16, e32, m1);
  EXPECT_ILLEGAL(101, 0xee432157); // vwmul.vv v2, v4, v6 (widening with SEW = 32)
  VSET(16, e8, m8);
  EXPECT_ILLEGAL(102, 0xee042857); // vwmul.vv v16, v0, v8 (widening with LMUL = 8)
  VSET(16, e8, m2);
  EXPECT_ILLEGAL(103, 0x022200d7); // vadd.vv v1, v2, v4 (vd not aligned)
  EXPECT_ILLEGAL(104, 0x02320157); // vadd.vv v2, v3, v4 (vs2 not aligned)
  EXPECT_ILLEGAL(105, 0x02428157); // vadd.vv v2, v4, v5 (vs1 not aligned)
  EXPECT_ILLEGAL(106, 0x0245c1d7); // vadd.vx v3, v4, a1 (vd not aligned)
  EXPECT_LEGAL(107, 0x0245c157); // vadd.vx v2, v4, a1
  EXPECT_ILLEGAL(108, 0xee852157); // vwmul.vv v2, v8, v10 (vd not aligned to 4)
  EXPECT_ILLEGAL(109, 0xee442257); // vwmul.vv v4, v4, v8 (vs2 in low half of vd)
  EXPECT_ILLEGAL(110, 0xee822257); // vwmul.vv v4, v8, v4 (vs1 in low half of vd)
  EXPECT_LEGAL(111, 0xee642257); // vwmul.vv v4, v6, v8 (vs2 in high half of vd)
  EXPECT_LEGAL(112, 0xee852257); // vwmul.vv v4, v8, v10
  // Reserved overlaps: RS5 traps, Sail does not check them, and RVV 1.0 allows both
  SKIP_ON_SAIL(EXPECT_ILLEGAL(113, 0x622201d7)); // vmseq.vv v3, v2, v4 (vd inside vs2 group)
  SKIP_ON_SAIL(EXPECT_ILLEGAL(114, 0x622202d7)); // vmseq.vv v5, v2, v4 (vd inside vs1 group)
  EXPECT_LEGAL(115, 0x62220157); // vmseq.vv v2, v2, v4 (vd = lowest of vs2)
  EXPECT_LEGAL(116, 0x622200d7); // vmseq.vv v1, v2, v4
  EXPECT_ILLEGAL(117, 0x0230a0d7); // vredsum.vs v1, v3, v1 (vs2 not aligned)
  EXPECT_LEGAL(118, 0x0221a0d7); // vredsum.vs v1, v2, v3
  EXPECT_ILLEGAL(119, 0x5e018157); // vmv.v.v v2, v3 (vs1 not aligned)
  EXPECT_ILLEGAL(120, 0x5e05c1d7); // vmv.v.x v3, a1 (vd not aligned)
  EXPECT_LEGAL(121, 0x423025d7); // vmv.x.s a1, v3 (ignores LMUL)
  EXPECT_LEGAL(122, 0x4205e1d7); // vmv.s.x v3, a1 (ignores LMUL)
  EXPECT_ILLEGAL(123, 0x3a25e157); // vslide1up.vx v2, v2, a1 (vd overlaps vs2)
  EXPECT_ILLEGAL(124, 0x3a45e257); // vslide1up.vx v4, v4, a1 (vd overlaps vs2)
  EXPECT_LEGAL(125, 0x3a45e157); // vslide1up.vx v2, v4, a1
  EXPECT_LEGAL(126, 0x3e25e157); // vslide1down.vx v2, v2, a1
  EXPECT_ILLEGAL(127, 0x02050087); // vle8.v v1, (a0) (vd not aligned)
  EXPECT_LEGAL(128, 0x02050107); // vle8.v v2, (a0)
  EXPECT_ILLEGAL(129, 0x020501a7); // vse8.v v3, (a0) (vs3 not aligned)
  EXPECT_ILLEGAL(130, 0x0ab50187); // vlse8.v v3, (a0), a1 (vd not aligned)
  EXPECT_ILLEGAL(131, 0x06350107); // vluxei8.v v2, (a0), v3 (index not aligned)
  EXPECT_ILLEGAL(132, 0x06250187); // vluxei8.v v3, (a0), v2 (vd not aligned)
  EXPECT_LEGAL(133, 0x02b50087); // vlm.v v1, (a0) (mask load)
  EXPECT_LEGAL(134, 0x028500a7); // vs1r.v v1, (a0) (whole register)
  EXPECT_LEGAL(135, 0x9e3030d7); // vmv1r.v v1, v3 (whole register)
  VSET(16, e8, mf2);
  EXPECT_ILLEGAL(136, 0xee42a257); // vwmul.vv v4, v4, v5 (overlap, source EMUL < 1)
  EXPECT_LEGAL(137, 0xee532257); // vwmul.vv v4, v5, v6
  VSET(16, e8, m2);
  EXPECT_ILLEGAL(138, 0x402200d7); // vadc.vvm v1, v2, v4, v0 (vd not aligned)
  EXPECT_ILLEGAL(139, 0x40320157); // vadc.vvm v2, v3, v4, v0 (vs2 not aligned)
  EXPECT_ILLEGAL(140, 0x48428157); // vsbc.vvm v2, v4, v5, v0 (vs1 not aligned)
  EXPECT_LEGAL(141, 0x40430157); // vadc.vvm v2, v4, v6, v0
  EXPECT_LEGAL(142, 0x48430157); // vsbc.vvm v2, v4, v6, v0
  EXPECT_ILLEGAL(143, 0x463200d7); // vmadc.vv v1, v3, v4 (vs2 not aligned)
  EXPECT_ILLEGAL(144, 0x4c2280d7); // vmsbc.vvm v1, v2, v5, v0 (vs1 not aligned)
  // Reserved overlaps, as in cases 113 and 114: RS5 traps, Sail does not check them
  SKIP_ON_SAIL(EXPECT_ILLEGAL(145, 0x462201d7)); // vmadc.vv v3, v2, v4 (vd inside vs2 group)
  SKIP_ON_SAIL(EXPECT_ILLEGAL(146, 0x4c2202d7)); // vmsbc.vvm v5, v2, v4, v0 (vd inside vs1 group)
  EXPECT_LEGAL(147, 0x46220157); // vmadc.vv v2, v2, v4 (vd = lowest of vs2)
  EXPECT_LEGAL(148, 0x4e220157); // vmsbc.vv v2, v2, v4 (vd = lowest of vs2)
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();

  EXIT_CHECK();
}
