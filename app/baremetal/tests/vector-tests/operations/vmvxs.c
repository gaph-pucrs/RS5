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
  scalar_8b = 0;
  VSET(16, e8, m1);
  VLOAD_8(v1, 55 << 0, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.x.s %0, v1" : "=r"(scalar_8b));
  XCMP(1, scalar_8b, 55 << 0);

  scalar_16b = 0;
  VSET(16, e16, m1);
  VLOAD_16(v1, 55 << 8, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.x.s %0, v1" : "=r"(scalar_16b));
  XCMP(2, scalar_16b, 55 << 8);

  scalar_32b = 0;
  VSET(16, e32, m1);
  VLOAD_32(v1, 55 << 16, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.x.s %0, v1" : "=r"(scalar_32b));
  XCMP(3, scalar_32b, 55 << 16);

  // scalar_64b = 0;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 55 << 30, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vmv.x.s %0, v1" : "=r"(scalar_64b));
  // XCMP(4, scalar_64b, 55 << 30);
}

// Check special cases
void TEST_CASE2() {
  // scalar_64b = 0;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 55 << 30, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VSET(16, e64, m8);
  // asm volatile("vmv.x.s %0, v1" : "=r"(scalar_64b));
  // XCMP(5, scalar_64b, 55 << 30);

  // scalar_64b = 0;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 55 << 30, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VSET_ZERO(e64, m1);
  // asm volatile("vmv.x.s %0, v1" : "=r"(scalar_64b));
  // XCMP(6, scalar_64b, 55 << 30);

  // scalar_64b = 0;
  // VSET(16, e64, m1);
  // VLOAD_64(v1, 55 << 30, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VSET_ZERO(e64, m8);
  // asm volatile("vmv.x.s %0, v1" : "=r"(scalar_64b));
  // XCMP(7, scalar_64b, 55 << 30);
}

// vmv.x.s sign-extends SEW < XLEN elements into the full 32-bit register
void TEST_CASE3() {
  unsigned long r;
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x85, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.x.s %0, v1" : "=r"(r));
  XCMP(5, r, 0xffffff85);

  VSET(16, e16, m1);
  VLOAD_16(v1, 0x8001, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.x.s %0, v1" : "=r"(r));
  XCMP(6, r, 0xffff8001);

  VLOAD_16(v1, 0x7001, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vmv.x.s %0, v1" : "=r"(r));
  XCMP(7, r, 0x00007001);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();

  EXIT_CHECK();
}
