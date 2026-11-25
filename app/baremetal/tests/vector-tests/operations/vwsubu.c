// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>
//
// RS5 port: e64 cases commented out (ELEN = 32), 32-bit scalar. TEST_CASE9
// to TEST_CASE15 are RS5 cases: LMUL > 1, e16 sources with the sign bit
// set, a .vx scalar truncated to SEW, masking across destination
// registers, vd overlapping the high half of vs2, a fractional source and
// vl < VLMAX with the tail undisturbed. As in vwmul.c, the masked cases
// first clear the whole destination (16 elements of 2*SEW), so that the
// masked-off elements compare equal at VLEN > 128.
// The .wv and .wx cases (TEST_CASE5 to TEST_CASE8) are commented out:
// RS5 does not implement those forms yet.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
  asm volatile("vwsubu.vv v6, v2, v4");
  VSET(16, e16, m1);
  VCMP_U16(1, v6, -7, -5, -3, -1, 1, 3, 5, 7, -7, -5, -3, -1, 1, 3, 5, 7);

  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
  asm volatile("vwsubu.vv v6, v2, v4");
  VSET(16, e32, m1);
  VCMP_U32(2, v6, -7, -5, -3, -1, 1, 3, 5, 7, -7, -5, -3, -1, 1, 3, 5, 7);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
  // asm volatile("vwsubu.vv v6, v2, v4");
  // VSET(16, e64, m1);
  // VCMP_U64(3, v6, -7, -5, -3, -1, 1, 3, 5, 7, -7, -5, -3, -1, 1, 3, 5, 7);
}

void TEST_CASE2(void) {
  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwsubu.vv v6, v2, v4, v0.t");
  VSET(16, e16, m1);
  VCMP_U16(4, v6, 0, -5, 0, -1, 0, 3, 0, 7, 0, -5, 0, -1, 0, 3, 0, 7);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwsubu.vv v6, v2, v4, v0.t");
  VSET(16, e32, m1);
  VCMP_U32(5, v6, 0, -5, 0, -1, 0, 3, 0, 7, 0, -5, 0, -1, 0, 3, 0, 7);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwsubu.vv v6, v2, v4, v0.t");
  // VSET(16, e64, m1);
  // VCMP_U64(6, v6, 0, -5, 0, -1, 0, 3, 0, 7, 0, -5, 0, -1, 0, 3, 0, 7);
}

void TEST_CASE3(void) {
  const uint32_t scalar = 5;

  VSET(16, e8, m1);
  VLOAD_8(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  asm volatile("vwsubu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(7, v6, -4, 249, -2, 247, 0, 245, 2, 243, 4, 241, 6, 239, 8, 237, 10,
           235);

  VSET(16, e16, m1);
  VLOAD_16(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  asm volatile("vwsubu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(8, v6, -4, 65529, -2, 65527, 0, 65525, 2, 65523, 4, 65521, 6, 65519,
           8, 65517, 10, 65515);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  // asm volatile("vwsubu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(9, v6, -4, 4294967289, -2, 4294967287, 0, 4294967285, 2, 4294967283,
  //          4, 4294967281, 6, 4294967279, 8, 4294967277, 10, 4294967275);
}

void TEST_CASE4(void) {
  const uint32_t scalar = 5;

  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwsubu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(10, v6, 0, -3, 0, -1, 0, 1, 0, 3, 0, -3, 0, -1, 0, 1, 0, 3);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwsubu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(11, v6, 0, -3, 0, -1, 0, 1, 0, 3, 0, -3, 0, -1, 0, 1, 0, 3);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwsubu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(12, v6, 0, -3, 0, -1, 0, 1, 0, 3, 0, -3, 0, -1, 0, 1, 0, 3);
}

// void TEST_CASE5(void) {
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
//   asm volatile("vwsubu.wv v6, v2, v4");
//   VSET(16, e16, m1);
//   VCMP_U16(13, v6, -7, -5, -3, -1, 1, 3, 5, 7, -7, -5, -3, -1, 1, 3, 5, 7);
//
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_16(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
//   asm volatile("vwsubu.wv v6, v2, v4");
//   VSET(16, e32, m1);
//   VCMP_U32(14, v6, -7, -5, -3, -1, 1, 3, 5, 7, -7, -5, -3, -1, 1, 3, 5, 7);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_32(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
//   // asm volatile("vwsubu.wv v6, v2, v4");
//   // VSET(16, e64, m1);
//   // VCMP_U64(15, v6, -7, -5, -3, -1, 1, 3, 5, 7, -7, -5, -3, -1, 1, 3, 5, 7);
// }

// void TEST_CASE6(void) {
//   VSET(32, e8, m1);
//   VCLEAR(v6);
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwsubu.wv v6, v2, v4, v0.t");
//   VSET(16, e16, m1);
//   VCMP_U16(16, v6, 0, -5, 0, -1, 0, 3, 0, 7, 0, -5, 0, -1, 0, 3, 0, 7);
//
//   VSET(32, e16, m1);
//   VCLEAR(v6);
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_16(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwsubu.wv v6, v2, v4, v0.t");
//   VSET(16, e32, m1);
//   VCMP_U32(17, v6, 0, -5, 0, -1, 0, 3, 0, 7, 0, -5, 0, -1, 0, 3, 0, 7);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_32(v4, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1);
//   // VLOAD_8(v0, 0xAA, 0xAA);
//   // VCLEAR(v6);
//   // asm volatile("vwsubu.wv v6, v2, v4, v0.t");
//   // VSET(16, e64, m1);
//   // VCMP_U64(18, v6, 0, -5, 0, -1, 0, 3, 0, 7, 0, -5, 0, -1, 0, 3, 0, 7);
// }

// void TEST_CASE7(void) {
//   const uint32_t scalar = 5;
//
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
//   asm volatile("vwsubu.wx v6, v2, %[A]" ::[A] "r"(scalar));
//   VSET(16, e16, m1);
//   VCMP_U16(19, v6, -4, -7, -2, -9, 0, -11, 2, -13, 4, -15, 6, -17, 8, -19, 10,
//            -21);
//
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
//   asm volatile("vwsubu.wx v6, v2, %[A]" ::[A] "r"(scalar));
//   VSET(16, e32, m1);
//   VCMP_U32(20, v6, -4, -7, -2, -9, 0, -11, 2, -13, 4, -15, 6, -17, 8, -19, 10,
//            -21);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
//   // asm volatile("vwsubu.wx v6, v2, %[A]" ::[A] "r"(scalar));
//   // VSET(16, e64, m1);
//   // VCMP_U64(21, v6, -4, -7, -2, -9, 0, -11, 2, -13, 4, -15, 6, -17, 8, -19, 10,
//   //          -21);
// }

// void TEST_CASE8(void) {
//   const uint32_t scalar = 5;
//
//   VSET(32, e8, m1);
//   VCLEAR(v6);
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwsubu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VSET(16, e16, m1);
//   VCMP_U16(22, v6, 0, -3, 0, -1, 0, 1, 0, 3, 0, -3, 0, -1, 0, 1, 0, 3);
//
//   VSET(32, e16, m1);
//   VCLEAR(v6);
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwsubu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VSET(16, e32, m1);
//   VCMP_U32(23, v6, 0, -3, 0, -1, 0, 1, 0, 3, 0, -3, 0, -1, 0, 1, 0, 3);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_8(v0, 0xAA, 0xAA);
//   // VCLEAR(v6);
//   // asm volatile("vwsubu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
//   // VSET(16, e64, m1);
//   // VCMP_U64(24, v6, 0, -3, 0, -1, 0, 1, 0, 3, 0, -3, 0, -1, 0, 1, 0, 3);
// }

// LMUL = 2: e8 sources of two registers, e16 destination of four (at
// VLEN = 128); each source register is read for two destination registers
void TEST_CASE9(void) {
  VSET(32, e8, m2);
  VLOAD_8(v2, 0xaa, 0x9e, 0xa1, 0x2b, 0x21, 0x08, 0x50, 0xd1,
              0x2d, 0x1a, 0x50, 0x2c, 0xa7, 0xcb, 0x39, 0xf1,
              0xe6, 0x93, 0x25, 0x5b, 0xc3, 0x6b, 0xa9, 0x1f,
              0x95, 0xcb, 0xdf, 0x78, 0x35, 0xaa, 0x5f, 0x1b);
  VLOAD_8(v4, 0x08, 0x9a, 0x43, 0x7f, 0x0d, 0x43, 0xfb, 0x31,
              0xfe, 0x0c, 0x1d, 0xcf, 0x36, 0x6d, 0xc0, 0x90,
              0x8b, 0x5d, 0x7d, 0x2d, 0x55, 0x54, 0x6b, 0xdd,
              0x6d, 0x4b, 0x22, 0x59, 0x2a, 0xb9, 0xbb, 0xd8);
  asm volatile("vwsubu.vv v8, v2, v4");
  VSET(32, e16, m4);
  VCMP_U16(25, v8, 0x00a2, 0x0004, 0x005e, 0xffac, 0x0014, 0xffc5, 0xff55, 0x00a0,
                   0xff2f, 0x000e, 0x0033, 0xff5d, 0x0071, 0x005e, 0xff79, 0x0061,
                   0x005b, 0x0036, 0xffa8, 0x002e, 0x006e, 0x0017, 0x003e, 0xff42,
                   0x0028, 0x0080, 0x00bd, 0x001f, 0x000b, 0xfff1, 0xffa4, 0xff43);
}

// e16 sources with the sign bit set in some elements
void TEST_CASE10(void) {
  VSET(8, e16, m1);
  VLOAD_16(v2, 0xa637, 0x87cb, 0xfabb, 0xf132, 0x1cdf, 0x6848, 0x9ab8, 0x6ed8);
  VLOAD_16(v4, 0xbf70, 0x1235, 0xf1ae, 0x0b2f, 0xa200, 0xd9a8, 0x7004, 0xe655);
  asm volatile("vwsubu.vv v6, v2, v4");
  VSET(8, e32, m2);
  VCMP_U32(26, v6, 0xffffe6c7, 0x00007596, 0x0000090d, 0x0000e603,
                   0xffff7adf, 0xffff8ea0, 0x00002ab4, 0xffff8883);
}

// Masked .vx: the scalar is truncated to SEW (0x80) before it is extended,
// and the elements of the second destination register (at VLEN = 128) take
// their mask from the matching v0 bits
void TEST_CASE11(void) {
  const uint32_t scalar = 0x12345680;
  VSET(16, e16, m2);
  VCLEAR(v6);
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x1d, 0x72, 0x87, 0x23, 0x63, 0xc8, 0xe8, 0xcb,
              0xa6, 0x0e, 0x42, 0xad, 0x3e, 0xbb, 0xaf, 0x03);
  VLOAD_8(v0, 0x5a, 0xc3);
  asm volatile("vwsubu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m2);
  VCMP_U16(27, v6, 0x0000, 0xfff2, 0x0000, 0xffa3, 0xffe3, 0x0000, 0x0068, 0x0000,
                   0x0026, 0xff8e, 0x0000, 0x0000, 0x0000, 0x0000, 0x002f, 0xff83);
}

// e16 .vx: the scalar is truncated to SEW (0x8001)
void TEST_CASE12(void) {
  const uint32_t scalar = 0xabcd8001;
  VSET(8, e16, m1);
  VLOAD_16(v2, 0x2457, 0x3bdb, 0xcd7a, 0x7320, 0xb684, 0x9f28, 0xc534, 0xc447);
  asm volatile("vwsubu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(8, e32, m2);
  VCMP_U32(28, v6, 0xffffa456, 0xffffbbda, 0x00004d79, 0xfffff31f,
                   0x00003683, 0x00001f27, 0x00004533, 0x00004446);
}

// The destination may overlap vs2 in its highest-numbered half
void TEST_CASE13(void) {
  VSET(16, e8, m1);
  VLOAD_8(v5, 0xca, 0xae, 0x5f, 0x18, 0xc6, 0xe8, 0xcc, 0x40,
              0x5a, 0x7c, 0x2e, 0xf0, 0xa0, 0xa5, 0x5e, 0x1f);
  VLOAD_8(v8, 0x04, 0x18, 0x52, 0x14, 0xe6, 0x48, 0x18, 0xbd,
              0x96, 0xf7, 0x28, 0xb0, 0x6c, 0x9d, 0x99, 0x28);
  asm volatile("vwsubu.vv v4, v5, v8");
  VSET(16, e16, m2);
  VCMP_U16(29, v4, 0x00c6, 0x0096, 0x000d, 0x0004, 0xffe0, 0x00a0, 0x00b4, 0xff83,
                   0xffc4, 0xff85, 0x0006, 0x0040, 0x0034, 0x0008, 0xffc5, 0xfff7);
}

// Fractional source (LMUL = 1/2): one destination register
void TEST_CASE14(void) {
  VSET(8, e8, mf2);
  VLOAD_8(v2, 0x78, 0xeb, 0x38, 0x0d, 0x28, 0x07, 0xb0, 0xb6);
  VLOAD_8(v4, 0x25, 0x28, 0x10, 0x02, 0x8b, 0x27, 0x95, 0x2b);
  asm volatile("vwsubu.vv v6, v2, v4");
  VSET(8, e16, m1);
  VCMP_U16(30, v6, 0x0053, 0x00c3, 0x0028, 0x000b, 0xff9d, 0xffe0, 0x001b, 0x008b);
}

// vl < VLMAX with tu: only the body is written
void TEST_CASE15(void) {
  VSET(16, e16, m2);
  VLOAD_16(v6, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa,
               0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x5e, 0x92, 0x03, 0xfe, 0xac, 0x87, 0xe1, 0xa8,
              0x00, 0xd3, 0x00, 0x35, 0x30, 0x6f, 0xf8, 0x5e);
  VLOAD_8(v4, 0x0b, 0xcf, 0xdc, 0xf3, 0x0f, 0xa7, 0xc5, 0x1d,
              0xb4, 0x42, 0xec, 0x77, 0x93, 0x58, 0xa8, 0x79);
  asm volatile("vsetivli t0, 5, e8, m1, tu, mu" ::: "t0");
  asm volatile("vwsubu.vv v6, v2, v4");
  VSET(16, e16, m2);
  VCMP_U16(31, v6, 0x0053, 0xffc3, 0xff27, 0x000b, 0x009d, 0xaaaa, 0xaaaa, 0xaaaa,
                   0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  // TEST_CASE5();
  // TEST_CASE6();
  // TEST_CASE7();
  // TEST_CASE8();
  TEST_CASE9();
  TEST_CASE10();
  TEST_CASE11();
  TEST_CASE12();
  TEST_CASE13();
  TEST_CASE14();
  TEST_CASE15();

  EXIT_CHECK();
}
