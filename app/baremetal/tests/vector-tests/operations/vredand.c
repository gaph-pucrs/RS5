// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include "vector_macros.h"

// Naive test
void TEST_CASE1(void) {
  VSET(12, e8, m1);
  VLOAD_8(v1, 0xff, 0xf1, 0xf0, 0xff, 0xf1, 0xf0, 0xff, 0xf1, 0xf0, 0xff, 0xf1,
          0xf0);
  VLOAD_8(v2, 0xf0);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredand.vs v3, v1, v2");
  RED_CHECK(1, 8, RED_OP_AND, 0, v3);

  VSET(12, e16, m1);
  VLOAD_16(v1, 0xffff, 0x0301, 0xf1f0, 0xffff, 0x0101, 0xf7f0, 0xffff, 0x0701,
           0xfff0, 0xffff, 0x0101, 0xf1f0);
  VLOAD_16(v2, 0xefff);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredand.vs v3, v1, v2");
  RED_CHECK(2, 16, RED_OP_AND, 0, v3);

  VSET(12, e32, m1);
  VLOAD_32(v1, 0xffffffff, 0x100ff001, 0xf0f0f0f0, 0xffffffff, 0x100ff001,
           0xf0f0f0f0, 0xffffffff, 0x100ff001, 0xf0f0f0f0, 0xffffffff,
           0x100ff001, 0xf0f0f0f0);
  VLOAD_32(v2, 0x00f010f0);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredand.vs v3, v1, v2");
  RED_CHECK(3, 32, RED_OP_AND, 0, v3);

  // VSET(12, e64, m1);
  // VLOAD_64(v1, 0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0,
  //          0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0,
  //          0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0,
  //          0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0);
  // VLOAD_64(v2, 0xfffffffffffffff7);
  // asm volatile("vredand.vs v3, v1, v2");
  // VCMP_U64(4, v3, 0x1000000000000000);
}

// Masked naive test
void TEST_CASE2(void) {
  VSET(12, e8, m1);
  VLOAD_8(v0, 0xf7, 0xff);
  VLOAD_8(v1, 0xff, 0xf1, 0xff, 0x00, 0xf1, 0xf0, 0xff, 0xf1, 0xf0, 0xff, 0xf1,
          0xf0);
  VLOAD_8(v2, 0xf0);
  VLOAD_8(v3, 1);
  RED_SAVE(8, v3, v1, v2);
  asm volatile("vredand.vs v3, v1, v2, v0.t");
  RED_CHECK(5, 8, RED_OP_AND, 1, v3);

  VSET(12, e16, m1);
  VLOAD_8(v0, 0x00, 0x08);
  VLOAD_16(v1, 0xffff, 0x0301, 0xf1f0, 0xffff, 0x0101, 0xf7f0, 0xffff, 0x9701,
           0xfff0, 0xffff, 0x0101, 0xf1f0);
  VLOAD_16(v2, 0xefff);
  VLOAD_16(v3, 1);
  RED_SAVE(16, v3, v1, v2);
  asm volatile("vredand.vs v3, v1, v2, v0.t");
  RED_CHECK(6, 16, RED_OP_AND, 1, v3);

  VSET(12, e32, m1);
  VLOAD_8(v0, 0xfe, 0xff);
  VLOAD_32(v1, 0x00000000, 0x100ff001, 0xf0f0f0f0, 0xffffffff, 0x100ff001,
           0xf0f0f0f0, 0xffffffff, 0x100ff001, 0xf0f0f0f0, 0xffffffff,
           0x100ff001, 0xf0f0f0f0);
  VLOAD_32(v2, 0x00f010f0);
  VLOAD_32(v3, 1);
  RED_SAVE(32, v3, v1, v2);
  asm volatile("vredand.vs v3, v1, v2, v0.t");
  RED_CHECK(7, 32, RED_OP_AND, 1, v3);

  // VSET(12, e64, m1);
  // VLOAD_8(v0, 0xaa, 0x55);
  // VLOAD_64(v1, 0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0,
  //          0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0,
  //          0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0,
  //          0xffffffffffffffff, 0x1000000000000001, 0xf0f0f0f0f0f0f0f0);
  // VLOAD_64(v2, 0xfffffffffffffff7);
  // VLOAD_64(v3, 1);
  // asm volatile("vredand.vs v3, v1, v2, v0.t");
  // VCMP_U64(8, v3, 0x1000000000000000);
}

void TEST_CASE3(void) {
  VSET(32, e32, m2);
  VLOAD_32(v6, 0xffffffff, 0x100ff001, 0xf0f0f0f0, 0xffffffff, 0x100ff001,
           0xf0f0f0f0, 0xffffffff, 0x100ff001, 0xf0f0f0f0, 0xffffffff,
           0x100ff001, 0xf0f0f0f0,
           0xffffffff, 0x100ff001, 0xf0f0f0f0, 0xffffffff, 0x100ff001,
           0xf0f0f0f0, 0xffffffff, 0x100f0001, 0xf0f0f0f0, 0xffffffff,
           0x100ff001, 0xf0f0f0f0);
  VLOAD_32(v8, 0x00f010f0);
  RED_SAVE(32, v4, v6, v8);
  asm volatile("vredand.vs v4, v6, v8");
  RED_CHECK(9, 32, RED_OP_AND, 0, v4);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();

  EXIT_CHECK();
}
