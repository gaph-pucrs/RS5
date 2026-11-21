// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>
//
// RS5 port: e64 cases commented out (ELEN = 32), 32-bit scalar, and the mask
// results checked with CMP_SAVE/VMCMP_MASK as in the compare tests, so the
// check does not depend on VLEN. TEST_CASE5 to TEST_CASE8 are RS5 cases:
// borrow-out at element boundaries, vd = v0 with LMUL = 2, the scalar and
// immediate forms, and vl < VLMAX.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xef, 10, 0xff, 16, 0xef, 10, 0xff, 16, 0xef, 10, 0xff, 16,
          0xef, 10, 0xff);
  VLOAD_8(v2, 4, 0xef, 12, 0x80, 4, 0xef, 12, 0x80, 4, 0xef, 12, 0x80, 4, 0xef,
          12, 0x80);
  VLOAD_8(v0, 0x99, 0x99);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(1, v3, 0x44, 0x44);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xbeef, 10, 0xffff, 16, 0xbeef, 10, 0xffff, 16, 0xbeef, 10,
           0xffff, 16, 0xbeef, 10, 0xffff);
  VLOAD_16(v2, 4, 0xbeef, 12, 0x8000, 4, 0xbeef, 12, 0x8000, 4, 0xbeef, 12,
           0x8000, 4, 0xbeef, 12, 0x8000);
  VLOAD_8(v0, 0x99, 0x99);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(2, v3, 0x44, 0x44);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xdeadbeef, 10, 0xffffffff, 16, 0xdeadbeef, 10, 0xffffffff,
           16, 0xdeadbeef, 10, 0xffffffff, 16, 0xdeadbeef, 10, 0xffffffff);
  VLOAD_32(v2, 4, 0xdeadbeef, 12, 0x80000000, 4, 0xdeadbeef, 12, 0x80000000, 4,
           0xdeadbeef, 12, 0x80000000, 4, 0xdeadbeef, 12, 0x80000000);
  VLOAD_8(v0, 0x99, 0x99);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(3, v3, 0x44, 0x44);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xdeadbeefdeadbeef, 10, 0xffffffffffffffff, 16,
//         0xdeadbeefdeadbeef, 10, 0xffffffffffffffff, 16, 0xdeadbeefdeadbeef,
//         10, 0xffffffffffffffff, 16, 0xdeadbeefdeadbeef, 10,
//         0xffffffffffffffff);
//VLOAD_64(v2, 4, 0xdeadbeefdeadbeef, 12, 0x8000000000000000, 4,
//         0xdeadbeefdeadbeef, 12, 0x8000000000000000, 4, 0xdeadbeefdeadbeef,
//         12, 0x8000000000000000, 4, 0xdeadbeefdeadbeef, 12,
//         0x8000000000000000);
//VLOAD_8(v0, 0x99, 0x99);
//asm volatile("vmsbc.vvm v3, v1, v2, v0");
//VSET(2, e8, m1);
//VCMP_U8(4, v3, 0x44, 0x44);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 16, 0xef, 10, 0xff, 16, 0xef, 10, 0xff, 16, 0xef, 10, 0xff, 16,
          0xef, 10, 0xff);
  VLOAD_8(v2, 4, 0xef, 12, 0x80, 4, 0xef, 12, 0x80, 4, 0xef, 12, 0x80, 4, 0xef,
          12, 0x80);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(5, v3, 0x44, 0x44);

  VSET(16, e16, m1);
  VLOAD_16(v1, 16, 0xbeef, 10, 0xffff, 16, 0xbeef, 10, 0xffff, 16, 0xbeef, 10,
           0xffff, 16, 0xbeef, 10, 0xffff);
  VLOAD_16(v2, 4, 0xbeef, 12, 0x8000, 4, 0xbeef, 12, 0x8000, 4, 0xbeef, 12,
           0x8000, 4, 0xbeef, 12, 0x8000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(6, v3, 0x44, 0x44);

  VSET(16, e32, m1);
  VLOAD_32(v1, 16, 0xdeadbeef, 10, 0xffffffff, 16, 0xdeadbeef, 10, 0xffffffff,
           16, 0xdeadbeef, 10, 0xffffffff, 16, 0xdeadbeef, 10, 0xffffffff);
  VLOAD_32(v2, 4, 0xdeadbeef, 12, 0x80000000, 4, 0xdeadbeef, 12, 0x80000000, 4,
           0xdeadbeef, 12, 0x80000000, 4, 0xdeadbeef, 12, 0x80000000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(7, v3, 0x44, 0x44);

//VSET(16, e64, m1);
//VLOAD_64(v1, 16, 0xdeadbeefdeadbeef, 10, 0xffffffffffffffff, 16,
//         0xdeadbeefdeadbeef, 10, 0xffffffffffffffff, 16, 0xdeadbeefdeadbeef,
//         10, 0xffffffffffffffff, 16, 0xdeadbeefdeadbeef, 10,
//         0xffffffffffffffff);
//VLOAD_64(v2, 4, 0xdeadbeefdeadbeef, 12, 0x8000000000000000, 4,
//         0xdeadbeefdeadbeef, 12, 0x8000000000000000, 4, 0xdeadbeefdeadbeef,
//         12, 0x8000000000000000, 4, 0xdeadbeefdeadbeef, 12,
//         0x8000000000000000);
//asm volatile("vmsbc.vv v3, v1, v2");
//VSET(2, e8, m1);
//VCMP_U8(8, v3, 0x44, 0x44);
};

void TEST_CASE3(void) {
  const uint32_t scalar = 20;

  VSET(16, e8, m1);
  VLOAD_8(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
  VLOAD_8(v0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(9, v3, 0x22, 0x22);

  VSET(16, e16, m1);
  VLOAD_16(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
  VLOAD_16(v0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(10, v3, 0x22, 0x22);

  VSET(16, e32, m1);
  VLOAD_32(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
  VLOAD_32(v0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(11, v3, 0x22, 0x22);

//VSET(16, e64, m1);
//VLOAD_64(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
//VLOAD_64(v0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0);
//asm volatile("vmsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
//VSET(2, e8, m1);
//VCMP_U8(12, v3, 0x22, 0x22);
};

void TEST_CASE4(void) {
  const uint32_t scalar = 20;

  VSET(16, e8, m1);
  VLOAD_8(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(13, v3, 0x22, 0x22);

  VSET(16, e16, m1);
  VLOAD_16(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(14, v3, 0x22, 0x22);

  VSET(16, e32, m1);
  VLOAD_32(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(15, v3, 0x22, 0x22);

//VSET(16, e64, m1);
//VLOAD_64(v1, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25, 20, 10, 30, 25);
//asm volatile("vmsbc.vx v3, v1, %[A]" ::[A] "r"(scalar));
//VSET(2, e8, m1);
//VCMP_U8(16, v3, 0x22, 0x22);
};

// The borrow-out of each element, with and without borrow-in, at every SEW.
// A borrow across a byte inside an element is not a borrow-out.
void TEST_CASE5(void) {
  VSET(2, e8, m1);
  VLOAD_8(v0, 0x6d, 0x6d);
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x00, 0x01, 0x02, 0x05, 0x80, 0x7f, 0x00, 0x00,
              0x00, 0x01, 0x02, 0x05, 0x80, 0x7f, 0x00, 0x00);
  VLOAD_8(v2, 0x00, 0x01, 0x01, 0x07, 0x01, 0x80, 0xff, 0x01,
              0x00, 0x01, 0x01, 0x07, 0x01, 0x80, 0xff, 0x01);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(17, v3, 0xe9, 0xe9);
  VSET(16, e8, m1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(18, v3, 0xe8, 0xe8);

  VSET(16, e16, m1);
  VLOAD_16(v1, 0x0000, 0x0001, 0x0100, 0x0005, 0x8000, 0x7fff, 0x0000, 0x0000,
               0x0000, 0x0001, 0x0100, 0x0005, 0x8000, 0x7fff, 0x0000, 0x0000);
  VLOAD_16(v2, 0x0000, 0x0001, 0x0001, 0x0007, 0x0001, 0x8000, 0xffff, 0x0001,
               0x0000, 0x0001, 0x0001, 0x0007, 0x0001, 0x8000, 0xffff, 0x0001);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vvm v3, v1, v2, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(19, v3, 0xe9, 0xe9);
  VSET(16, e16, m1);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(20, v3, 0xe8, 0xe8);

  VSET(16, e32, m2);
  VLOAD_32(v2, 0x00000000, 0x00000001, 0x01000000, 0x00000005,
               0x80000000, 0x7fffffff, 0x00000000, 0x00000000,
               0x00000000, 0x00000001, 0x01000000, 0x00000005,
               0x80000000, 0x7fffffff, 0x00000000, 0x00000000);
  VLOAD_32(v4, 0x00000000, 0x00000001, 0x00000001, 0x00000007,
               0x00000001, 0x80000000, 0xffffffff, 0x00000001,
               0x00000000, 0x00000001, 0x00000001, 0x00000007,
               0x00000001, 0x80000000, 0xffffffff, 0x00000001);
  VCLEAR(v8);
  CMP_SAVE(v8);
  asm volatile("vmsbc.vvm v8, v2, v4, v0");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(21, v8, 0xe9, 0xe9);
  VSET(16, e32, m2);
  VCLEAR(v8);
  CMP_SAVE(v8);
  asm volatile("vmsbc.vv v8, v2, v4");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(22, v8, 0xe8, 0xe8);
}

// vd = v0 with LMUL = 2: v0 is the borrow-in and the destination. Even
// elements borrow out their v0 bit (0 - 0 - b), odd ones always borrow
// (0 - 1 - b), so the result is the old v0 | 0xaa
void TEST_CASE6(void) {
  const uint32_t a = 0x00;
  VSET(32, e8, m2);
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(a));
  VLOAD_8(v4, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
              0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01,
              0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01);
  VSET(4, e8, m1);
  VLOAD_8(v0, 0x0f, 0xf0, 0x33, 0xcc);
  CMP_SAVE(v0);
  VSET(32, e8, m2);
  asm volatile("vmsbc.vvm v0, v2, v4, v0");
  CMP_VL();
  VSET(4, e8, m1);
  VMCMP_MASK(23, v0, 0xaf, 0xfa, 0xbb, 0xee);
}

// Scalar forms (truncated to SEW)
void TEST_CASE7(void) {
  const uint32_t scalar = 0xabcd0001;
  // a - 0x0001 borrows out only for a = 0
  VSET(16, e16, m1);
  VLOAD_16(v1, 0x0000, 0x0001, 0x0002, 0x8000, 0x0000, 0x0001, 0x0002, 0x8000,
               0x0000, 0x0001, 0x0002, 0x8000, 0x0000, 0x0001, 0x0002, 0x8000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vx v3, v1, %[A]" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(24, v3, 0x11, 0x11);

  // a - 0x0001 - b with b = 0, 1, 1, 0
  VSET(2, e8, m1);
  VLOAD_8(v0, 0x66, 0x66);
  VSET(16, e16, m1);
  VLOAD_16(v1, 0x0000, 0x0001, 0x0001, 0x8000, 0x0000, 0x0001, 0x0001, 0x8000,
               0x0000, 0x0001, 0x0001, 0x8000, 0x0000, 0x0001, 0x0001, 0x8000);
  VCLEAR(v3);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(25, v3, 0x77, 0x77);
}

// vl < VLMAX: the mask bits past vl keep the old destination
void TEST_CASE8(void) {
  const uint32_t a = 0x00, b = 0x01;
  VSET(16, e8, m1);
  asm volatile("vmv.v.x v1, %[A]" ::[A] "r"(a));
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(b));
  VCLEAR(v3);
  VSET(5, e8, m1);
  CMP_SAVE(v3);
  asm volatile("vmsbc.vv v3, v1, v2");
  CMP_VL();
  VSET(2, e8, m1);
  VMCMP_MASK(26, v3, 0xff, 0xff);
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

  EXIT_CHECK();
}
