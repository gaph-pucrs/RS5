// Copyright 2026 GAPH - PUCRS
// SPDX-License-Identifier: SHL-0.51
//
// Runs with every vector class parameter of the existing instructions set to
// 0 (see vector_regression.py). Instructions of a disabled class must raise
// an illegal-instruction trap; the remaining ones must still execute.

#include <stdint.h>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  EXPECT_ILLEGAL(1, 0x262180d7); // vand.vv v1, v2, v3 (VLogicEnable)
  EXPECT_ILLEGAL(2, 0x2a21b0d7); // vor.vi v1, v2, 3 (VLogicEnable)
  EXPECT_ILLEGAL(3, 0x2e25c0d7); // vxor.vx v1, v2, a1 (VLogicEnable)
  EXPECT_ILLEGAL(4, 0x122180d7); // vminu.vv v1, v2, v3 (VMinMaxEnable)
  EXPECT_ILLEGAL(5, 0x1e25c0d7); // vmax.vx v1, v2, a1 (VMinMaxEnable)
  EXPECT_ILLEGAL(6, 0x5c2180d7); // vmerge.vvm v1, v2, v3, v0 (VMergeEnable)
  EXPECT_ILLEGAL(7, 0x8221a0d7); // vdivu.vv v1, v2, v3 (VDivEnable)
  EXPECT_ILLEGAL(8, 0x8e25e0d7); // vrem.vx v1, v2, a1 (VDivEnable)
  EXPECT_ILLEGAL(9, 0x0621a0d7); // vredand.vs v1, v2, v3 (VRedLogicEnable)
  EXPECT_ILLEGAL(10, 0x0e21a0d7); // vredxor.vs v1, v2, v3 (VRedLogicEnable)
  EXPECT_ILLEGAL(11, 0x1221a0d7); // vredminu.vs v1, v2, v3 (VRedMinMaxEnable)
  EXPECT_ILLEGAL(12, 0x1e21a0d7); // vredmax.vs v1, v2, v3 (VRedMinMaxEnable)
  EXPECT_ILLEGAL(13, 0x0221a0d7); // vredsum.vs v1, v2, v3 (VRedSumEnable)
  EXPECT_LEGAL(14, 0x022180d7); // vadd.vv v1, v2, v3
  EXPECT_LEGAL(15, 0x5e0180d7); // vmv.v.v v1, v3
  EXPECT_LEGAL(16, 0x9621a0d7); // vmul.vv v1, v2, v3
  EXPECT_ILLEGAL(17, 0x402180d7); // vadc.vvm v1, v2, v3, v0 (VCarryEnable)
  EXPECT_ILLEGAL(18, 0x4825c0d7); // vsbc.vxm v1, v2, a1, v0 (VCarryEnable)
  EXPECT_ILLEGAL(19, 0x442180d7); // vmadc.vvm v1, v2, v3, v0 (VCarryEnable)
  EXPECT_ILLEGAL(20, 0x4e2180d7); // vmsbc.vv v1, v2, v3 (VCarryEnable)
  EXPECT_ILLEGAL(21, 0xc62180d7); // vwredsum.vs v1, v2, v3 (VRedSumEnable)
  EXPECT_ILLEGAL(22, 0xc22180d7); // vwredsumu.vs v1, v2, v3 (VRedSumEnable)
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();

  EXIT_CHECK();
}
