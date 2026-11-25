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
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vwadd.vv v6, v2, v4");
  VSET(16, e16, m1);
  VCMP_U16(1, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);

  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vwadd.vv v6, v2, v4");
  VSET(16, e32, m1);
  VCMP_U32(2, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vwadd.vv v6, v2, v4");
  // VSET(16, e64, m1);
  // VCMP_U64(3, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);
}

void TEST_CASE2(void) {
  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwadd.vv v6, v2, v4, v0.t");
  VSET(16, e16, m1);
  VCMP_U16(4, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwadd.vv v6, v2, v4, v0.t");
  VSET(16, e32, m1);
  VCMP_U32(5, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwadd.vv v6, v2, v4, v0.t");
  // VSET(16, e64, m1);
  // VCMP_U64(6, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);
}

void TEST_CASE3(void) {
  const uint32_t scalar = 5;

  VSET(16, e8, m1);
  VLOAD_8(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  asm volatile("vwadd.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(7, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);

  VSET(16, e16, m1);
  VLOAD_16(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  asm volatile("vwadd.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(8, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  // asm volatile("vwadd.vx v6, v2, %[A]" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(9, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);
}

void TEST_CASE4(void) {
  const uint32_t scalar = 5;

  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwadd.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(10, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwadd.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(11, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwadd.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(12, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);
}

// void TEST_CASE5(void) {
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   asm volatile("vwadd.wv v6, v2, v4");
//   VSET(16, e16, m1);
//   VCMP_U16(13, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);
//
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   asm volatile("vwadd.wv v6, v2, v4");
//   VSET(16, e32, m1);
//   VCMP_U32(14, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // asm volatile("vwadd.wv v6, v2, v4");
//   // VSET(16, e64, m1);
//   // VCMP_U64(15, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);
// }

// void TEST_CASE6(void) {
//   VSET(32, e8, m1);
//   VCLEAR(v6);
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwadd.wv v6, v2, v4, v0.t");
//   VSET(16, e16, m1);
//   VCMP_U16(16, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);
//
//   VSET(32, e16, m1);
//   VCLEAR(v6);
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwadd.wv v6, v2, v4, v0.t");
//   VSET(16, e32, m1);
//   VCMP_U32(17, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_8(v0, 0xAA, 0xAA);
//   // VCLEAR(v6);
//   // asm volatile("vwadd.wv v6, v2, v4, v0.t");
//   // VSET(16, e64, m1);
//   // VCMP_U64(18, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);
// }

// void TEST_CASE7(void) {
//   const uint32_t scalar = 5;
//
//   VSET(16, e8, m1);
//   VLOAD_16(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
//   asm volatile("vwadd.wx v6, v2, %[A]" ::[A] "r"(scalar));
//   VSET(16, e16, m1);
//   VCMP_U16(19, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);
//
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
//   asm volatile("vwadd.wx v6, v2, %[A]" ::[A] "r"(scalar));
//   VSET(16, e32, m1);
//   VCMP_U32(20, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
//   // asm volatile("vwadd.wx v6, v2, %[A]" ::[A] "r"(scalar));
//   // VSET(16, e64, m1);
//   // VCMP_U64(21, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);
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
//   asm volatile("vwadd.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VSET(16, e16, m1);
//   VCMP_U16(22, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);
//
//   VSET(32, e16, m1);
//   VCLEAR(v6);
//   VSET(16, e16, m1);
//   VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v6);
//   asm volatile("vwadd.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VSET(16, e32, m1);
//   VCMP_U32(23, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);
//
//   // VSET(16, e32, m1);
//   // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//   // VLOAD_8(v0, 0xAA, 0xAA);
//   // VCLEAR(v6);
//   // asm volatile("vwadd.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
//   // VSET(16, e64, m1);
//   // VCMP_U64(24, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);
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
  asm volatile("vwadd.vv v8, v2, v4");
  VSET(32, e16, m4);
  VCMP_U16(25, v8, 0xffb2, 0xff38, 0xffe4, 0x00aa, 0x002e, 0x004b, 0x004b, 0x0002,
                   0x002b, 0x0026, 0x006d, 0xfffb, 0xffdd, 0x0038, 0xfff9, 0xff81,
                   0xff71, 0xfff0, 0x00a2, 0x0088, 0x0018, 0x00bf, 0x0014, 0xfffc,
                   0x0002, 0x0016, 0x0001, 0x00d1, 0x005f, 0xff63, 0x001a, 0xfff3);
}

// e16 sources with the sign bit set in some elements
void TEST_CASE10(void) {
  VSET(8, e16, m1);
  VLOAD_16(v2, 0xa637, 0x87cb, 0xfabb, 0xf132, 0x1cdf, 0x6848, 0x9ab8, 0x6ed8);
  VLOAD_16(v4, 0xbf70, 0x1235, 0xf1ae, 0x0b2f, 0xa200, 0xd9a8, 0x7004, 0xe655);
  asm volatile("vwadd.vv v6, v2, v4");
  VSET(8, e32, m2);
  VCMP_U32(26, v6, 0xffff65a7, 0xffff9a00, 0xffffec69, 0xfffffc61,
                   0xffffbedf, 0x000041f0, 0x00000abc, 0x0000552d);
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
  asm volatile("vwadd.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m2);
  VCMP_U16(27, v6, 0x0000, 0xfff2, 0x0000, 0xffa3, 0xffe3, 0x0000, 0xff68, 0x0000,
                   0xff26, 0xff8e, 0x0000, 0x0000, 0x0000, 0x0000, 0xff2f, 0xff83);
}

// e16 .vx: the scalar is truncated to SEW (0x8001)
void TEST_CASE12(void) {
  const uint32_t scalar = 0xabcd8001;
  VSET(8, e16, m1);
  VLOAD_16(v2, 0x2457, 0x3bdb, 0xcd7a, 0x7320, 0xb684, 0x9f28, 0xc534, 0xc447);
  asm volatile("vwadd.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(8, e32, m2);
  VCMP_U32(28, v6, 0xffffa458, 0xffffbbdc, 0xffff4d7b, 0xfffff321,
                   0xffff3685, 0xffff1f29, 0xffff4535, 0xffff4448);
}

// The destination may overlap vs2 in its highest-numbered half
void TEST_CASE13(void) {
  VSET(16, e8, m1);
  VLOAD_8(v5, 0xca, 0xae, 0x5f, 0x18, 0xc6, 0xe8, 0xcc, 0x40,
              0x5a, 0x7c, 0x2e, 0xf0, 0xa0, 0xa5, 0x5e, 0x1f);
  VLOAD_8(v8, 0x04, 0x18, 0x52, 0x14, 0xe6, 0x48, 0x18, 0xbd,
              0x96, 0xf7, 0x28, 0xb0, 0x6c, 0x9d, 0x99, 0x28);
  asm volatile("vwadd.vv v4, v5, v8");
  VSET(16, e16, m2);
  VCMP_U16(29, v4, 0xffce, 0xffc6, 0x00b1, 0x002c, 0xffac, 0x0030, 0xffe4, 0xfffd,
                   0xfff0, 0x0073, 0x0056, 0xffa0, 0x000c, 0xff42, 0xfff7, 0x0047);
}

// Fractional source (LMUL = 1/2): one destination register
void TEST_CASE14(void) {
  VSET(8, e8, mf2);
  VLOAD_8(v2, 0x78, 0xeb, 0x38, 0x0d, 0x28, 0x07, 0xb0, 0xb6);
  VLOAD_8(v4, 0x25, 0x28, 0x10, 0x02, 0x8b, 0x27, 0x95, 0x2b);
  asm volatile("vwadd.vv v6, v2, v4");
  VSET(8, e16, m1);
  VCMP_U16(30, v6, 0x009d, 0x0013, 0x0048, 0x000f, 0xffb3, 0x002e, 0xff45, 0xffe1);
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
  asm volatile("vwadd.vv v6, v2, v4");
  VSET(16, e16, m2);
  VCMP_U16(31, v6, 0x0069, 0xff61, 0xffdf, 0xfff1, 0xffbb, 0xaaaa, 0xaaaa, 0xaaaa,
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
