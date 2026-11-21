// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>
//
// RS5 port: e64 cases commented out (ELEN = 32), 32-bit scalar. TEST_CASE4 to
// TEST_CASE6 are RS5 cases: carry at element boundaries, v0 bits past the
// first register (LMUL = 2) and vl < VLMAX with the tail undisturbed.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_8(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VCMP_U8(1, v3, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_16(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VCMP_U16(2, v3, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  VLOAD_32(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VCMP_U32(3, v3, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, -7, 7);
  // VLOAD_64(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, -8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // asm volatile("vadc.vvm v3, v1, v2, v0");
  // VCMP_U64(4, v3, 9, 10, 9, 10, 9, 10, 9, 10, 2, 5, 6, 9, 10, 13, 0, 0);
};

void TEST_CASE2(void) {
  const uint32_t scalar = 5;

  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U8(5, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U16(6, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U32(7, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // asm volatile("vadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  // VCMP_U64(8, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v3, v1, 5, v0");
  VCMP_U8(9, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v3, v1, 5, v0");
  VCMP_U16(10, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vadc.vim v3, v1, 5, v0");
  VCMP_U32(11, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // asm volatile("vadc.vim v3, v1, 5, v0");
  // VCMP_U64(12, v3, 6, 8, 8, 10, 10, 12, 12, 14, 6, 8, 8, 10, 10, 12, 12, 14);
};

// The carry-in enters each element on its own and never crosses into the next
// element, at every SEW
void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 0xff, 0x01, 0xff, 0x00, 0x80, 0x7f, 0xfe, 0x01,
              0xff, 0x01, 0xff, 0x00, 0x80, 0x7f, 0xfe, 0x01);
  VLOAD_8(v2, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x01, 0x00,
              0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x01, 0x00);
  VLOAD_8(v0, 0x6d, 0x6d);
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VCMP_U8(13, v3, 0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
                  0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01);

  VSET(16, e16, m1);
  VLOAD_16(v1, 0xffff, 0x0001, 0x00ff, 0x0000, 0x8000, 0x7fff, 0xfffe, 0x0001,
               0xffff, 0x0001, 0x00ff, 0x0000, 0x8000, 0x7fff, 0xfffe, 0x0001);
  VLOAD_16(v2, 0x0001, 0x0001, 0x0000, 0x0000, 0x8000, 0x8000, 0x0001, 0x0000,
               0x0001, 0x0001, 0x0000, 0x0000, 0x8000, 0x8000, 0x0001, 0x0000);
  VLOAD_8(v0, 0x6d, 0x6d);
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VCMP_U16(14, v3, 0x0001, 0x0002, 0x0100, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001,
                   0x0001, 0x0002, 0x0100, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001);

  VSET(16, e32, m2);
  VLOAD_32(v2, 0xffffffff, 0x00000001, 0x00ffffff, 0x0000ffff,
               0x80000000, 0x7fffffff, 0xfffffffe, 0x00000001,
               0xffffffff, 0x00000001, 0x00ffffff, 0x0000ffff,
               0x80000000, 0x7fffffff, 0xfffffffe, 0x00000001);
  VLOAD_32(v4, 0x00000001, 0x00000001, 0x00000000, 0x00000000,
               0x80000000, 0x80000000, 0x00000001, 0x00000000,
               0x00000001, 0x00000001, 0x00000000, 0x00000000,
               0x80000000, 0x80000000, 0x00000001, 0x00000000);
  VLOAD_8(v0, 0x6d, 0x6d);
  asm volatile("vadc.vvm v6, v2, v4, v0");
  VCMP_U32(15, v6, 0x00000001, 0x00000002, 0x01000000, 0x00010000,
                   0x00000000, 0x00000000, 0x00000000, 0x00000001,
                   0x00000001, 0x00000002, 0x01000000, 0x00010000,
                   0x00000000, 0x00000000, 0x00000000, 0x00000001);

  // The immediate is sign-extended to SEW: a + 0xffff + carry
  VSET(16, e16, m1);
  VLOAD_16(v1, 0x0000, 0x0001, 0x0001, 0x8000, 0x0000, 0x0001, 0x0001, 0x8000,
               0x0000, 0x0001, 0x0001, 0x8000, 0x0000, 0x0001, 0x0001, 0x8000);
  VLOAD_8(v0, 0x55, 0x55);
  asm volatile("vadc.vim v3, v1, -1, v0");
  VCMP_U16(16, v3, 0x0000, 0x0000, 0x0001, 0x7fff, 0x0000, 0x0000, 0x0001, 0x7fff,
                   0x0000, 0x0000, 0x0001, 0x7fff, 0x0000, 0x0000, 0x0001, 0x7fff);

  // The scalar is truncated to SEW: a + 0xff + carry
  const uint32_t scalar = 0x123456ff;
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x00, 0x01, 0x01, 0x80, 0x00, 0x01, 0x01, 0x80,
              0x00, 0x01, 0x01, 0x80, 0x00, 0x01, 0x01, 0x80);
  VLOAD_8(v0, 0x55, 0x55);
  asm volatile("vadc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U8(17, v3, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0x7f,
                  0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x01, 0x7f);
}

// LMUL = 2: elements past the first register take their carry from the
// matching v0 bits (bits 16 to 31 at VLEN = 128)
void TEST_CASE5(void) {
  const uint32_t a = 0x10, b = 0x01;
  VSET(4, e8, m1);
  VLOAD_8(v0, 0x0f, 0xf0, 0x33, 0xcc);
  VSET(32, e8, m2);
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(a));
  asm volatile("vmv.v.x v4, %[A]" ::[A] "r"(b));
  asm volatile("vadc.vvm v6, v2, v4, v0");
  VCMP_U8(18, v6, 0x12, 0x12, 0x12, 0x12, 0x11, 0x11, 0x11, 0x11,
                  0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12,
                  0x12, 0x12, 0x11, 0x11, 0x12, 0x12, 0x11, 0x11,
                  0x11, 0x11, 0x12, 0x12, 0x11, 0x11, 0x12, 0x12);
}

// vl < VLMAX with tu: only the body is written
void TEST_CASE6(void) {
  const uint32_t b = 0x10;
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v3, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
              0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa);
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(b));
  VLOAD_8(v0, 0xff, 0xff);
  asm volatile("vsetivli t0, 5, e8, m1, tu, mu" ::: "t0");
  asm volatile("vadc.vvm v3, v1, v2, v0");
  VSET(16, e8, m1);
  VCMP_U8(19, v3, 0x12, 0x13, 0x14, 0x15, 0x16, 0xaa, 0xaa, 0xaa,
                  0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa);
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
