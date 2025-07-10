// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  const uint64_t scalar = 40;

  VSET(16, e8, m1);
  VLOAD_8(v2, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8,
          -25, 99);
  VCLEAR(v1);
  asm volatile("vmsgt.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(1, v1, 0x99, 0x99);

  VSET(16, e16, m1);
  VLOAD_16(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VCLEAR(v1);
  asm volatile("vmsgt.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(2, v1, 0x99, 0x99);

  VSET(16, e32, m1);
  VLOAD_32(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VCLEAR(v1);
  asm volatile("vmsgt.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(3, v1, 0x99, 0x99);

  // VSET(16, e64, m1);
  // VLOAD_64(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
  //          12345, -8, -25, 199);
  // VCLEAR(v1);
  // asm volatile("vmsgt.vx v1, v2, %[A]" ::[A] "r"(scalar));
  // VSET(2, e8, m1);
  // VCMP_U8(4, v1, 0x99, 0x99);
};

void TEST_CASE2(void) {
  const uint64_t scalar = 40;

  VSET(16, e8, m1);
  VLOAD_8(v2, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8,
          -25, 99);
  VLOAD_8(v0, 0xCC, 0xCC);
  VCLEAR(v1);
  asm volatile("vmsgt.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(5, v1, 0x88, 0x88);

  VSET(16, e16, m1);
  VLOAD_16(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VLOAD_8(v0, 0xCC, 0xCC);
  VCLEAR(v1);
  asm volatile("vmsgt.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(6, v1, 0x88, 0x88);

  VSET(16, e32, m1);
  VLOAD_32(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VLOAD_8(v0, 0xCC, 0xCC);
  VCLEAR(v1);
  asm volatile("vmsgt.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(2, e8, m1);
  VCMP_U8(7, v1, 0x88, 0x88);

  // VSET(16, e64, m1);
  // VLOAD_64(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
  //          12345, -8, -25, 199);
  // VLOAD_8(v0, 0xCC, 0xCC);
  // VCLEAR(v1);
  // asm volatile("vmsgt.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  // VSET(2, e8, m1);
  // VCMP_U8(8, v1, 0x88, 0x88);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8,
          -25, 99);
  VCLEAR(v1);
  asm volatile("vmsgt.vi v1, v2, 15");
  VSET(2, e8, m1);
  VCMP_U8(9, v1, 0x99, 0x99);

  VSET(16, e16, m1);
  VLOAD_16(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VCLEAR(v1);
  asm volatile("vmsgt.vi v1, v2, 15");
  VSET(2, e8, m1);
  VCMP_U8(10, v1, 0x99, 0x99);

  VSET(16, e32, m1);
  VLOAD_32(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VCLEAR(v1);
  asm volatile("vmsgt.vi v1, v2, 15");
  VSET(2, e8, m1);
  VCMP_U8(11, v1, 0x99, 0x99);

  // VSET(16, e64, m1);
  // VLOAD_64(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
  //          12345, -8, -25, 199);
  // VCLEAR(v1);
  // asm volatile("vmsgt.vi v1, v2, 15");
  // VSET(2, e8, m1);
  // VCMP_U8(12, v1, 0x99, 0x99);
};

void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8, -25, 99, 123, -8,
          -25, 99);
  VLOAD_8(v0, 0x88, 0x88);
  VCLEAR(v1);
  asm volatile("vmsgt.vi v1, v2, 15, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(13, v1, 0x88, 0x88);

  VSET(16, e16, m1);
  VLOAD_16(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VLOAD_8(v0, 0x88, 0x88);
  VCLEAR(v1);
  asm volatile("vmsgt.vi v1, v2, 15, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(14, v1, 0x88, 0x88);

  VSET(16, e32, m1);
  VLOAD_32(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  VLOAD_8(v0, 0x88, 0x88);
  VCLEAR(v1);
  asm volatile("vmsgt.vi v1, v2, 15, v0.t");
  VSET(2, e8, m1);
  VCMP_U8(15, v1, 0x88, 0x88);

  // VSET(16, e64, m1);
  // VLOAD_64(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
  //          12345, -8, -25, 199);
  // VLOAD_8(v0, 0x88, 0x88);
  // VCLEAR(v1);
  // asm volatile("vmsgt.vi v1, v2, 15, v0.t");
  // VSET(2, e8, m1);
  // VCMP_U8(16, v1, 0x88, 0x88);
};

void TEST_CASE5(void) {
  VSET(32, e32, m2);
  VLOAD_32(v2, 12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199,
           12345, -8, -25, 199, 12345, -8, -25, 199, 12345, -8, -25, 199,
           12345, -8, -25, 199);
  asm volatile("vmsgt.vi v1, v2, 15");
  VSET(4, e8, m1);
  VCMP_U8(17, v1, 0x99, 0x99, 0x99, 0x99);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();

  EXIT_CHECK();
}
