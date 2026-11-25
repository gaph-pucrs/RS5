// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include "vector_macros.h"

// Naive test
void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, -7, 8, 1, 9, 3, 4, 5, -6, 7, 8);
  VLOAD_8(v2, -1);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredmax.vs v3, v1, v2");
  RED_CHECK(1, 8, RED_OP_MAX, 0, v3);

  VSET(16, e16, m1);
  VLOAD_16(v1, -1, 2, -3, 4, 5, 6, 7, 8, 1, 2, 3, -4, 5, 6, 7, 8);
  VLOAD_16(v2, 9);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredmax.vs v3, v1, v2");
  RED_CHECK(2, 16, RED_OP_MAX, 0, v3);

  VSET(16, e32, m1);
  VLOAD_32(v1, 9, 2, 3, -4, 5, 6, 7, 8, 1, 2, 3, 4, -5, 6, 7, 8);
  VLOAD_32(v2, 1);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredmax.vs v3, v1, v2");
  RED_CHECK(3, 32, RED_OP_MAX, 0, v3);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, -1, 2, 3, -4, 5, 6, 7, 9, 1, 2, 3, 4, 5, 6, 7, -8);
  // VLOAD_64(v2, -1);
  // asm volatile("vredmax.vs v3, v1, v2");
  // VCMP_U64(4, v3, 9);
}

// Masked naive test
void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v0, 0x03, 0x00);
  VLOAD_8(v1, -1, 2, 3, -4, 5, 6, 7, 9, 1, -2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1);
  VLOAD_8(v3, 1);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredmax.vs v3, v1, v2, v0.t");
  RED_CHECK(5, 8, RED_OP_MAX, 1, v3);

  VSET(16, e16, m1);
  VLOAD_8(v0, 0x00, 0xc0);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, -7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 9);
  VLOAD_16(v3, 1);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredmax.vs v3, v1, v2, v0.t");
  RED_CHECK(6, 16, RED_OP_MAX, 1, v3);

  VSET(16, e32, m1);
  VLOAD_8(v0, 0x00, 0xc0);
  VLOAD_32(v1, -1, 2, 3, 4, 5, 6, 7, -8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1);
  VLOAD_32(v3, 1);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredmax.vs v3, v1, v2, v0.t");
  RED_CHECK(7, 32, RED_OP_MAX, 1, v3);

  // VSET(16, e64, m1);
  // VLOAD_8(v0, 0xaa, 0x55);
  // VLOAD_64(v1, 1, -2, 3, 4, 5, 6, -7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 4);
  // VLOAD_64(v3, 1);
  // asm volatile("vredmax.vs v3, v1, v2, v0.t");
  // VCMP_U64(8, v3, 8);
}

void TEST_CASE3(void) {
  VSET(32, e32, m2);
  VLOAD_32(v6, 9, 2, 3, -4, 5, 6, 7, 8, 1, 2, 3, 4, -5, 6, 7, 8,
               9, 2, 3, -4, 5, 6, 7, 8, 1, 2, 3, 4, -5, 6, 7, 80);
  VLOAD_32(v8, 1);
  RED_SAVE(32, v4, v6, v8);
  asm volatile("vredmax.vs v4, v6, v8");
  RED_CHECK(9, 32, RED_OP_MAX, 0, v4);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();

  EXIT_CHECK();
}
