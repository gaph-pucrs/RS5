// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include "vector_macros.h"

// Bigger LMUL tests
void TEST_CASE1(void) {
  VSET(16, e8, m2);
  VLOAD_8(v8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v16, 1);
  asm volatile("vredsum.vs v16, v8, v16");
  VCMP_U8(1, v16, 73);

  VSET(16, e16, m4);
  VLOAD_16(v8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v16, 1);
  asm volatile("vredsum.vs v24, v8, v16");
  VCMP_U16(2, v24, 73);

  VSET(16, e32, m8);
  VLOAD_32(v8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v16, 1);
  asm volatile("vredsum.vs v3, v24, v16");
  VCMP_U32(3, v24, 73);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 1);
  // asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U64(4, v3, 73);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();

  EXIT_CHECK();
}
