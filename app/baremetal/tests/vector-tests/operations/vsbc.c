// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>
//
// RS5 port: e64 cases commented out (ELEN = 32), 32-bit scalar. TEST_CASE3 to
// TEST_CASE5 are RS5 cases: borrow at element boundaries, v0 bits past the
// first register (LMUL = 2) and vl < VLMAX with the tail undisturbed.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsbc.vvm v3, v1, v2, v0");
  VCMP_U8(1, v3, -7, -6, -3, -2, 1, 2, 5, 6, 0, -1, 0, -1, 0, -1, 0, -1);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsbc.vvm v3, v1, v2, v0");
  VCMP_U16(2, v3, -7, -6, -3, -2, 1, 2, 5, 6, 0, -1, 0, -1, 0, -1, 0, -1);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_32(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsbc.vvm v3, v1, v2, v0");
  VCMP_U32(3, v3, -7, -6, -3, -2, 1, 2, 5, 6, 0, -1, 0, -1, 0, -1, 0, -1);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_64(v2, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // asm volatile("vsbc.vvm v3, v1, v2, v0");
  // VCMP_U64(4, v3, -7, -6, -3, -2, 1, 2, 5, 6, 0, -1, 0, -1, 0, -1, 0, -1);
};

void TEST_CASE2(void) {
  const uint32_t scalar = 5;

  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U8(5, v3, -4, -4, -2, -2, 0, 0, 2, 2, -4, -4, -2, -2, 0, 0, 2, 2);

  VSET(16, e16, m1);
  VLOAD_16(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U16(6, v3, -4, -4, -2, -2, 0, 0, 2, 2, -4, -4, -2, -2, 0, 0, 2, 2);

  VSET(16, e32, m1);
  VLOAD_32(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U32(7, v3, -4, -4, -2, -2, 0, 0, 2, 2, -4, -4, -2, -2, 0, 0, 2, 2);

  // VSET(16, e64, m1);
  // VLOAD_64(v1, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // asm volatile("vsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  // VCMP_U64(8, v3, -4, -4, -2, -2, 0, 0, 2, 2, -4, -4, -2, -2, 0, 0, 2, 2);
};

// The borrow-in enters each element on its own and never crosses into the
// next element, at every SEW
void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x00, 0x01, 0x00, 0x05, 0x80, 0x7f, 0x00, 0xff,
              0x00, 0x01, 0x00, 0x05, 0x80, 0x7f, 0x00, 0xff);
  VLOAD_8(v2, 0x00, 0x01, 0x01, 0x07, 0x01, 0x80, 0xff, 0xff,
              0x00, 0x01, 0x01, 0x07, 0x01, 0x80, 0xff, 0xff);
  VLOAD_8(v0, 0x6d, 0x6d);
  asm volatile("vsbc.vvm v3, v1, v2, v0");
  VCMP_U8(9, v3, 0xff, 0x00, 0xfe, 0xfd, 0x7f, 0xfe, 0x00, 0x00,
                 0xff, 0x00, 0xfe, 0xfd, 0x7f, 0xfe, 0x00, 0x00);

  VSET(16, e16, m1);
  VLOAD_16(v1, 0x0000, 0x0001, 0x0100, 0x0005, 0x8000, 0x7fff, 0x0000, 0xffff,
               0x0000, 0x0001, 0x0100, 0x0005, 0x8000, 0x7fff, 0x0000, 0xffff);
  VLOAD_16(v2, 0x0000, 0x0001, 0x0001, 0x0007, 0x0001, 0x8000, 0xffff, 0xffff,
               0x0000, 0x0001, 0x0001, 0x0007, 0x0001, 0x8000, 0xffff, 0xffff);
  VLOAD_8(v0, 0x6d, 0x6d);
  asm volatile("vsbc.vvm v3, v1, v2, v0");
  VCMP_U16(10, v3, 0xffff, 0x0000, 0x00fe, 0xfffd, 0x7fff, 0xfffe, 0x0000, 0x0000,
                   0xffff, 0x0000, 0x00fe, 0xfffd, 0x7fff, 0xfffe, 0x0000, 0x0000);

  VSET(16, e32, m2);
  VLOAD_32(v2, 0x00000000, 0x00000001, 0x01000000, 0x00000005,
               0x80000000, 0x7fffffff, 0x00000000, 0xffffffff,
               0x00000000, 0x00000001, 0x01000000, 0x00000005,
               0x80000000, 0x7fffffff, 0x00000000, 0xffffffff);
  VLOAD_32(v4, 0x00000000, 0x00000001, 0x00000001, 0x00000007,
               0x00000001, 0x80000000, 0xffffffff, 0xffffffff,
               0x00000000, 0x00000001, 0x00000001, 0x00000007,
               0x00000001, 0x80000000, 0xffffffff, 0xffffffff);
  VLOAD_8(v0, 0x6d, 0x6d);
  asm volatile("vsbc.vvm v6, v2, v4, v0");
  VCMP_U32(11, v6, 0xffffffff, 0x00000000, 0x00fffffe, 0xfffffffd,
                   0x7fffffff, 0xfffffffe, 0x00000000, 0x00000000,
                   0xffffffff, 0x00000000, 0x00fffffe, 0xfffffffd,
                   0x7fffffff, 0xfffffffe, 0x00000000, 0x00000000);

  // The scalar is truncated to SEW: a - 0x0001 - borrow
  const uint32_t scalar = 0xabcd0001;
  VSET(16, e16, m1);
  VLOAD_16(v1, 0x0000, 0x0001, 0x0001, 0x8000, 0x0000, 0x0001, 0x0001, 0x8000,
               0x0000, 0x0001, 0x0001, 0x8000, 0x0000, 0x0001, 0x0001, 0x8000);
  VLOAD_8(v0, 0x55, 0x55);
  asm volatile("vsbc.vxm v3, v1, %[A], v0" ::[A] "r"(scalar));
  VCMP_U16(12, v3, 0xfffe, 0x0000, 0xffff, 0x7fff, 0xfffe, 0x0000, 0xffff, 0x7fff,
                   0xfffe, 0x0000, 0xffff, 0x7fff, 0xfffe, 0x0000, 0xffff, 0x7fff);
}

// LMUL = 2: elements past the first register take their borrow from the
// matching v0 bits (bits 16 to 31 at VLEN = 128)
void TEST_CASE4(void) {
  const uint32_t a = 0x10, b = 0x01;
  VSET(4, e8, m1);
  VLOAD_8(v0, 0x0f, 0xf0, 0x33, 0xcc);
  VSET(32, e8, m2);
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(a));
  asm volatile("vmv.v.x v4, %[A]" ::[A] "r"(b));
  asm volatile("vsbc.vvm v6, v2, v4, v0");
  VCMP_U8(13, v6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f,
                  0x0f, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e,
                  0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
                  0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e);
}

// vl < VLMAX with tu: only the body is written
void TEST_CASE5(void) {
  const uint32_t b = 0x10;
  VSET(16, e8, m1);
  VLOAD_8(v1, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
              0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f);
  VLOAD_8(v3, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
              0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa);
  asm volatile("vmv.v.x v2, %[A]" ::[A] "r"(b));
  VLOAD_8(v0, 0xff, 0xff);
  asm volatile("vsetivli t0, 5, e8, m1, tu, mu" ::: "t0");
  asm volatile("vsbc.vvm v3, v1, v2, v0");
  VSET(16, e8, m1);
  VCMP_U8(14, v3, 0x0f, 0x10, 0x11, 0x12, 0x13, 0xaa, 0xaa, 0xaa,
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

  EXIT_CHECK();
}
