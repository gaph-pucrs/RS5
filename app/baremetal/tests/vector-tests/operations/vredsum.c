// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include "vector_macros.h"

// Naive test
void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(1, 8, RED_OP_SUM, 0, v3);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 1);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(2, 16, RED_OP_SUM, 0, v3);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(3, 32, RED_OP_SUM, 0, v3);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 1);
  // asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U64(4, v3, 73);
}

// Masked naive test
void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1);
  VLOAD_8(v3, 1);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2, v0.t");
  RED_CHECK(5, 8, RED_OP_SUM, 1, v3);

  VSET(16, e16, m1);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 1);
  VLOAD_16(v3, 1);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2, v0.t");
  RED_CHECK(6, 16, RED_OP_SUM, 1, v3);

  VSET(16, e32, m1);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1);
  VLOAD_32(v3, 1);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2, v0.t");
  RED_CHECK(7, 32, RED_OP_SUM, 1, v3);

  // VSET(16, e64, m1);
  // VLOAD_8(v0, 0xaa, 0x55);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 1);
  // VLOAD_64(v3, 1);
  // asm volatile("vredsum.vs v3, v1, v2, v0.t");
  // VCMP_U64(8, v3, 37);
}

// Are we respecting the undisturbed tail policy?
void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(9, 8, RED_OP_SUM, 0, v3);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(10, 16, RED_OP_SUM, 0, v3);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(11, 32, RED_OP_SUM, 0, v3);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U64(12, v3, 73, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
}

// Odd number of elements, undisturbed policy
void TEST_CASE4(void) {
  VSET(1024, e8, m1);
  VSET(15, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  RED_CHECK(13, 8, RED_OP_SUM, 0, v3);

  VSET(1, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U16(14, v3, 2, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 0);
  RED_CHECK(14, 16, RED_OP_SUM, 0, v3);

  VSET(3, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U32(15, v3, 7, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 0);
  RED_CHECK(15, 32, RED_OP_SUM, 0, v3);

  // VSET(7, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U64(16, v3, 29, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);

  // VSET(15, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vredsum.vs v3, v1, v2");
  // VCMP_U64(17, v3, 65, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
}

// Odd number of elements, undisturbed policy, and mask
void TEST_CASE5(void) {
  VSET(15, e8, m1);
  VLOAD_8(v0, 0x00, 0x40);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 0);
  VLOAD_8(v2, 100, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 0);
  VLOAD_8(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 0);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2, v0.t");
  RED_CHECK(18, 8, RED_OP_SUM, 1, v3);

  VSET(1, e16, m1);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2, v0.t");
  // VCMP_U16(19, v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_CHECK(19, 16, RED_OP_SUM, 1, v3);

  VSET(3, e32, m1);
  VLOAD_8(v0, 0xaa, 0x55);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2, v0.t");
  // VCMP_U32(20, v3, 3, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  RED_CHECK(20, 32, RED_OP_SUM, 1, v3);

  VSET(32, e32, m2);
  VLOAD_32(v6, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v8, 1);
  RED_SAVE(32, v4, v6, v8);
  asm volatile("vredsum.vs v4, v6, v8");
  RED_CHECK(21, 32, RED_OP_SUM, 0, v4);
}

// RS5: with vl = 0 a reduction does not write the destination
void TEST_CASE6(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 1);
  VLOAD_8(v3, 0x55);
  VSET_ZERO(e8, m1);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  VSET(16, e8, m1);
  RED_CHECK(22, 8, RED_OP_SUM, 0, v3);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 1);
  VLOAD_16(v3, 0x5555);
  VSET_ZERO(e16, m1);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  VSET(16, e16, m1);
  RED_CHECK(23, 16, RED_OP_SUM, 0, v3);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 1);
  VLOAD_32(v3, 0x55555555);
  VSET_ZERO(e32, m1);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredsum.vs v3, v1, v2");
  VSET(16, e32, m1);
  RED_CHECK(24, 32, RED_OP_SUM, 0, v3);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();
  TEST_CASE6();

  EXIT_CHECK();
}
