// Copyright 2022 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include "vector_macros.h"

int8_t scalar_8b;
int16_t scalar_16b;
int32_t scalar_32b;
int64_t scalar_64b;

void TEST_CASE1() {
  scalar_8b = 55 << 0;
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.s.x v1, %0" ::"r"(scalar_8b));
  VCMP_I8(1, v1, scalar_8b);

  scalar_16b = 55 << 8;
  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.s.x v1, %0" ::"r"(scalar_16b));
  VCMP_I16(2, v1, scalar_16b);

  scalar_32b = 55 << 16;
  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.s.x v1, %0" ::"r"(scalar_32b));
  VCMP_I32(3, v1, scalar_32b);

  // scalar_64b = 55 << 32;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vmv.s.x v1, %0" ::"r"(scalar_64b));
  // VCMP_I64(4, v1, scalar_64b);
}

// Check special cases
void TEST_CASE2() {
  // scalar_64b = 55 << 32;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VSET(16, e64, m8);
  // asm volatile("vmv.s.x v1, %0" ::"r"(scalar_64b));
  // VSET(1, e64, m1);
  // VCMP_I64(5, v1, scalar_64b);

  // scalar_64b = 55 << 32;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VSET_ZERO(e64, m1);
  // asm volatile("vmv.s.x v1, %0" ::"r"(scalar_64b));
  // VSET(1, e64, m1);
  // VCMP_I64(6, v1, 1);

  // scalar_64b = 55 << 32;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VSET_ZERO(e64, m8);
  // asm volatile("vmv.s.x v1, %0" ::"r"(scalar_64b));
  // VSET(1, e64, m1);
  // VCMP_I64(7, v1, 1);
}

void TEST_CASE3() {
  scalar_32b = 55 << 16;
  VSET(32, e32, m2);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.s.x v2, %0" ::"r"(scalar_32b));
  VCMP_I32(8, v2, scalar_32b);
  VCMP_I32(9, v2, scalar_32b);
}

// RS5: with vl = 0, vmv.s.x does not write the destination
void TEST_CASE4() {
  uint32_t scalar = 0xdeadbeef;

  VSET(16, e8, m1);
  VLOAD_8(v1, 0x55, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET_ZERO(e8, m1);
  asm volatile("vmv.s.x v1, %0" ::"r"(scalar));
  VSET(16, e8, m1);
  VCMP_U8(10, v1, 0x55, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);

  VSET(16, e16, m1);
  VLOAD_16(v1, 0x5555, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET_ZERO(e16, m1);
  asm volatile("vmv.s.x v1, %0" ::"r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(11, v1, 0x5555, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);

  VSET(16, e32, m1);
  VLOAD_32(v1, 0x55555555, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET_ZERO(e32, m1);
  asm volatile("vmv.s.x v1, %0" ::"r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(12, v1, 0x55555555, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}
