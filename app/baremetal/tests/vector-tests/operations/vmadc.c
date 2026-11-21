// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>
//
// RS5 port: e64 cases commented out (ELEN = 32), 32-bit scalar, and the mask
// results checked with CMP_SAVE/VMCMP_MASK as in the compare tests, so the
// check does not depend on VLEN. TEST_CASE7 to TEST_CASE10 are RS5 cases:
// carry-out at element boundaries, vd = v0 with LMUL = 2, the scalar and
// immediate forms, and vl < VLMAX.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff,
          8, 0x81);
  VLOAD_8(v2, 4, 8, 12, 0x80, 4, 8, 12, 0x80, 4, 8, 12, 0x80, 4, 8, 12, 0x80);
  VLOAD_8(v0, 0xDD, 0xDD);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(1, v3, 0xAA, 0xAA);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8,
           0x8001, 16, 0xffff, 8, 0x8001);
  VLOAD_16(v2, 4, 8, 12, 0x8000, 4, 8, 12, 0x8000, 4, 8, 12, 0x8000, 4, 8, 12,
           0x8000);
  VLOAD_8(v0, 0xDD, 0xDD);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(2, v3, 0xAA, 0xAA);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001, 16,
           0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001);
  VLOAD_32(v2, 4, 8, 12, 0x80000000, 4, 8, 12, 0x80000000, 4, 8, 12, 0x80000000,
           4, 8, 12, 0x80000000);
  VLOAD_8(v0, 0xDD, 0xDD);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(3, v3, 0xAA, 0xAA);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xffffffffffffffff, 8, 0x8000000000000001, 16,
//         0xffffffffffffffff, 8, 0x8000000000000001, 16, 0xffffffffffffffff, 8,
//         0x8000000000000001, 16, 0xffffffffffffffff, 8, 0x8000000000000001);
//VLOAD_64(v2, 4, 8, 12, 0x8000000000000000, 4, 8, 12, 0x8000000000000000, 4, 8,
//         12, 0x8000000000000000, 4, 8, 12, 0x8000000000000000);
//VLOAD_8(v0, 0xDD, 0xDD);
//asm volatile("vmadc.vvm v3, v1, v2, v0");
//VSET(2, e8, m1);
//VCMP_U8(4, v3, 0xAA, 0xAA);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff,
          8, 0x81);
  VLOAD_8(v2, 4, 8, 12, 0x80, 4, 8, 12, 0x80, 4, 8, 12, 0x80, 4, 8, 12, 0x80);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(5, v3, 0xAA, 0xAA);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8,
           0x8001, 16, 0xffff, 8, 0x8001);
  VLOAD_16(v2, 4, 8, 12, 0x8000, 4, 8, 12, 0x8000, 4, 8, 12, 0x8000, 4, 8, 12,
           0x8000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(6, v3, 0xAA, 0xAA);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001, 16,
           0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001);
  VLOAD_32(v2, 4, 8, 12, 0x80000000, 4, 8, 12, 0x80000000, 4, 8, 12, 0x80000000,
           4, 8, 12, 0x80000000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(7, v3, 0xAA, 0xAA);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xffffffffffffffff, 8, 0x8000000000000001, 16,
//         0xffffffffffffffff, 8, 0x8000000000000001, 16, 0xffffffffffffffff, 8,
//         0x8000000000000001, 16, 0xffffffffffffffff, 8, 0x8000000000000001);
//VLOAD_64(v2, 4, 8, 12, 0x8000000000000000, 4, 8, 12, 0x8000000000000000, 4, 8,
//         12, 0x8000000000000000, 4, 8, 12, 0x8000000000000000);
//asm volatile("vmadc.vv v3, v1, v2");
//VSET(2, e8, m1);
//VCMP_U8(8, v3, 0xAA, 0xAA);
};

void TEST_CASE3(void) {
  const uint32_t scalar = 0x80008080;

  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff,
          8, 0x81);
  VLOAD_8(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(9, v3, 0xAA, 0xAA);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8,
           0x8001, 16, 0xffff, 8, 0x8001);
  VLOAD_16(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(10, v3, 0xAA, 0xAA);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001, 16,
           0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001);
  VLOAD_32(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(11, v3, 0xAA, 0xAA);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xffffffffffffffff, 8, 0x8000000000000001, 16,
//         0xffffffffffffffff, 8, 0x8000000000000001, 16, 0xffffffffffffffff, 8,
//         0x8000000000000001, 16, 0xffffffffffffffff, 8, 0x8000000000000001);
//VLOAD_64(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
//asm volatile("vmadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
//VSET(2, e8, m1);
//VCMP_U8(12, v3, 0xAA, 0xAA);
};

void TEST_CASE4(void) {
  const uint32_t scalar = 0x80008080;

  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff,
          8, 0x81);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(13, v3, 0xAA, 0xAA);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8,
           0x8001, 16, 0xffff, 8, 0x8001);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(14, v3, 0xAA, 0xAA);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001, 16,
           0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(15, v3, 0xAA, 0xAA);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xffffffffffffffff, 8, 0x8000000000000001, 16,
//         0xffffffffffffffff, 8, 0x8000000000000001, 16, 0xffffffffffffffff, 8,
//         0x8000000000000001, 16, 0xffffffffffffffff, 8, 0x8000000000000001);
//asm volatile("vmadc.vx v3, v1, %[A]" ::[A] "r"(scalar));
//VSET(2, e8, m1);
//VCMP_U8(16, v3, 0xAA, 0xAA);
};

void TEST_CASE5(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff,
          8, 0x81);
  VLOAD_8(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vim v3, v1, 10, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(17, v3, 0x22, 0x22);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8,
           0x8001, 16, 0xffff, 8, 0x8001);
  VLOAD_16(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vim v3, v1, 10, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(18, v3, 0x22, 0x22);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001, 16,
           0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001);
  VLOAD_32(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vim v3, v1, 10, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(19, v3, 0x22, 0x22);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xffffffffffffffff, 8, 0x8000000000000001, 16,
//         0xffffffffffffffff, 8, 0x8000000000000001, 16, 0xffffffffffffffff, 8,
//         0x8000000000000001, 16, 0xffffffffffffffff, 8, 0x8000000000000001);
//VLOAD_64(v0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1);
//asm volatile("vmadc.vim v3, v1, 10, v0");
//VSET(2, e8, m1);
//VCMP_U8(20, v3, 0x22, 0x22);
};

void TEST_CASE6(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff, 8, 0x81, 16, 0xff,
          8, 0x81);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vi v3, v1, 10");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(21, v3, 0x22, 0x22);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8, 0x8001, 16, 0xffff, 8,
           0x8001, 16, 0xffff, 8, 0x8001);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vi v3, v1, 10");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(22, v3, 0x22, 0x22);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001, 16,
           0xffffffff, 8, 0x80000001, 16, 0xffffffff, 8, 0x80000001);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vi v3, v1, 10");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(23, v3, 0x22, 0x22);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xffffffffffffffff, 8, 0x8000000000000001, 16,
//         0xffffffffffffffff, 8, 0x8000000000000001, 16, 0xffffffffffffffff, 8,
//         0x8000000000000001, 16, 0xffffffffffffffff, 8, 0x8000000000000001);
//asm volatile("vmadc.vi v3, v1, 10");
//VSET(2, e8, m1);
//VCMP_U8(24, v3, 0x22, 0x22);
};

// The carry-out of each element, with and without carry-in, at every SEW.
// A carry across a byte inside an element is not a carry-out.
void TEST_CASE7(void) {
  VSET(2, e8, m1);
  VLOAD_8(v0, 0x6d, 0x6d);
  VSET(16, e8, m1);
  VLOAD_8(v1, 0xff, 0x01, 0xff, 0x00, 0x80, 0x7f, 0xfe, 0x01,
              0xff, 0x01, 0xff, 0x00, 0x80, 0x7f, 0xfe, 0x01);
  VLOAD_8(v2, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x01, 0x00,
              0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x01, 0x00);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(25, v3, 0x75, 0x75);
  VSET(16, e8, m1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(26, v3, 0x11, 0x11);

  VSET(16, e16, m1);
  VLOAD_16(v1, 0xffff, 0x0001, 0x00ff, 0x0000, 0x8000, 0x7fff, 0xfffe, 0x0001,
               0xffff, 0x0001, 0x00ff, 0x0000, 0x8000, 0x7fff, 0xfffe, 0x0001);
  VLOAD_16(v2, 0x0001, 0x0001, 0x0000, 0x0000, 0x8000, 0x8000, 0x0001, 0x0000,
               0x0001, 0x0001, 0x0000, 0x0000, 0x8000, 0x8000, 0x0001, 0x0000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(27, v3, 0x71, 0x71);
  VSET(16, e16, m1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(28, v3, 0x11, 0x11);

  VSET(16, e32, m2);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0x00ffffff, 0x0000ffff,
               0x80000000, 0x7fffffff, 0xfffffffe, 0x00000001,
               0xffffffff, 0x00000001, 0x00ffffff, 0x0000ffff,
               0x80000000, 0x7fffffff, 0xfffffffe, 0x00000001);
  VLOAD_32(v4, 0x00000001, 0x00000001, 0x00000000, 0x00000000,
               0x80000000, 0x80000000, 0x00000001, 0x00000000,
               0x00000001, 0x00000001, 0x00000000, 0x00000000,
               0x80000000, 0x80000000, 0x00000001, 0x00000000);
  VCLEAR(v8);
  CMP_SAVE(v8);
  asm volatile("vmadc.vvm v8, v2, v4, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(29, v8, 0x71, 0x71);
  VSET(16, e32, m2);
  VCLEAR(v8);
  CMP_SAVE(v8);
  asm volatile("vmadc.vv v8, v2, v4");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(30, v8, 0x11, 0x11);
}

// vd = v0 with LMUL = 2: v0 is the carry-in and the destination. Even
// elements carry out their v0 bit (0xff + 0x00 + c), odd ones always carry
// (0x80 + 0x80 + c), so the result is the old v0 | 0xaa
void TEST_CASE8(void) {
  VSET(32, e8, m2);
  VLOAD_8(v2, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80,
              0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80,
              0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80);
  VLOAD_8(v4, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
              0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
              0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80);
  VSET(4, e8, m1);
  VLOAD_8(v0, 0x0f, 0xf0, 0x33, 0xcc);
  CMP_SAVE(v0);
  VSET(32, e8, m2);
  asm volatile("vmadc.vvm v0, v2, v4, v0");
  CMP_VL();
  VSET(4, e8, m1);
  VMCMP_MASK(31, v0, 0xaf, 0xfa, 0xbb, 0xee);
}

// Immediate (sign-extended) and scalar (truncated to SEW) forms
void TEST_CASE9(void) {
  // a + 0xff carries out unless a = 0
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x00, 0x01, 0xff, 0x80, 0x00, 0x01, 0xff, 0x80,
              0x00, 0x01, 0xff, 0x80, 0x00, 0x01, 0xff, 0x80);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vi v3, v1, -1");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(32, v3, 0xee, 0xee);

  // a + 0xff + c with c = 0, 0, 1, 0
  const uint32_t scalar = 0x123456ff;
  VSET(2, e8, m1);
  VLOAD_8(v0, 0x44, 0x44);
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x00, 0x01, 0x00, 0x80, 0x00, 0x01, 0x00, 0x80,
              0x00, 0x01, 0x00, 0x80, 0x00, 0x01, 0x00, 0x80);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(33, v3, 0xee, 0xee);
}

// vl < VLMAX: the mask bits past vl keep the old destination
void TEST_CASE10(void) {
  const uint32_t a = 0xff, b = 0x01;
  VSET(16, e8, m1);
  asm volatile("vmv.v.x v1, %[A]" ::[A] "r"(a));
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(b));
  VCLEAR(v3);
  VSET(5, e8, m1);
  CMP_SAVE(v3);
  asm volatile("vmadc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(34, v3, 0xff, 0xff);
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
  TEST_CASE7();
  TEST_CASE8();
  TEST_CASE9();
  TEST_CASE10();

  EXIT_CHECK();
}
