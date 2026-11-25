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
// In the .wv and .wx cases the 2*SEW source is loaded with SEW equal to
// its EEW, since RS5 loads still take EEW = SEW. TEST_CASE16 to
// TEST_CASE21 are RS5 .wv and .wx cases: LMUL > 1, vd = vs2, a .wx scalar
// truncated to SEW, masking across destination registers, a fractional
// LMUL and vl < VLMAX with the tail undisturbed.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vwaddu.vv v6, v2, v4");
  VSET(16, e16, m1);
  VCMP_U16(1, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);

  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vwaddu.vv v6, v2, v4");
  VSET(16, e32, m1);
  VCMP_U32(2, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vwaddu.vv v6, v2, v4");
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
  asm volatile("vwaddu.vv v6, v2, v4, v0.t");
  VSET(16, e16, m1);
  VCMP_U16(4, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.vv v6, v2, v4, v0.t");
  VSET(16, e32, m1);
  VCMP_U32(5, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwaddu.vv v6, v2, v4, v0.t");
  // VSET(16, e64, m1);
  // VCMP_U64(6, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);
}

void TEST_CASE3(void) {
  const uint32_t scalar = 5;

  VSET(16, e8, m1);
  VLOAD_8(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  asm volatile("vwaddu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(7, v6, 6, 259, 8, 257, 10, 255, 12, 253, 14, 251, 16, 249, 18, 247,
           20, 245);

  VSET(16, e16, m1);
  VLOAD_16(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  asm volatile("vwaddu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(8, v6, 6, 65539, 8, 65537, 10, 65535, 12, 65533, 14, 65531, 16,
           65529, 18, 65527, 20, 65525);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  // asm volatile("vwaddu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(9, v6, 6, 4294967299, 8, 4294967297, 10, 4294967295, 12, 4294967293,
  //          14, 4294967291, 16, 4294967289, 18, 4294967287, 20, 4294967285);
}

void TEST_CASE4(void) {
  const uint32_t scalar = 5;

  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e8, m1);
  VLOAD_8(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(10, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e16, m1);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(11, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);

  // VSET(16, e32, m1);
  // VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwaddu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(12, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);
}

void TEST_CASE5(void) {
  VSET(16, e16, m2);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vwaddu.wv v6, v2, v4");
  VSET(16, e16, m1);
  VCMP_U16(13, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);

  VSET(16, e32, m2);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET(16, e16, m1);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  asm volatile("vwaddu.wv v6, v2, v4");
  VSET(16, e32, m1);
  VCMP_U32(14, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);

  // VSET(16, e32, m1);
  // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // asm volatile("vwaddu.wv v6, v2, v4");
  // VSET(16, e64, m1);
  // VCMP_U64(15, v6, 2, 4, 6, 8, 10, 12, 14, 16, 2, 4, 6, 8, 10, 12, 14, 16);
}

void TEST_CASE6(void) {
  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e16, m2);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET(16, e8, m1);
  VLOAD_8(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.wv v6, v2, v4, v0.t");
  VSET(16, e16, m1);
  VCMP_U16(16, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e32, m2);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET(16, e16, m1);
  VLOAD_16(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.wv v6, v2, v4, v0.t");
  VSET(16, e32, m1);
  VCMP_U32(17, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);

  // VSET(16, e32, m1);
  // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwaddu.wv v6, v2, v4, v0.t");
  // VSET(16, e64, m1);
  // VCMP_U64(18, v6, 0, 4, 0, 8, 0, 12, 0, 16, 0, 4, 0, 8, 0, 12, 0, 16);
}

void TEST_CASE7(void) {
  const uint32_t scalar = 5;

  VSET(16, e16, m2);
  VLOAD_16(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  VSET(16, e8, m1);
  asm volatile("vwaddu.wx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(19, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);

  VSET(16, e32, m2);
  VLOAD_32(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  VSET(16, e16, m1);
  asm volatile("vwaddu.wx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(20, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);

  // VSET(16, e32, m1);
  // VLOAD_64(v2, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
  // asm volatile("vwaddu.wx v6, v2, %[A]" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(21, v6, 6, 3, 8, 1, 10, -1, 12, -3, 14, -5, 16, -7, 18, -9, 20, -11);
}

void TEST_CASE8(void) {
  const uint32_t scalar = 5;

  VSET(32, e8, m1);
  VCLEAR(v6);
  VSET(16, e16, m2);
  VLOAD_16(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET(16, e8, m1);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m1);
  VCMP_U16(22, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);

  VSET(32, e16, m1);
  VCLEAR(v6);
  VSET(16, e32, m2);
  VLOAD_32(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  VSET(16, e16, m1);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v6);
  asm volatile("vwaddu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e32, m1);
  VCMP_U32(23, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);

  // VSET(16, e32, m1);
  // VLOAD_64(v2, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v6);
  // asm volatile("vwaddu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  // VSET(16, e64, m1);
  // VCMP_U64(24, v6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 7, 0, 9, 0, 11, 0, 13);
}

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
  asm volatile("vwaddu.vv v8, v2, v4");
  VSET(32, e16, m4);
  VCMP_U16(25, v8, 0x00b2, 0x0138, 0x00e4, 0x00aa, 0x002e, 0x004b, 0x014b, 0x0102,
                   0x012b, 0x0026, 0x006d, 0x00fb, 0x00dd, 0x0138, 0x00f9, 0x0181,
                   0x0171, 0x00f0, 0x00a2, 0x0088, 0x0118, 0x00bf, 0x0114, 0x00fc,
                   0x0102, 0x0116, 0x0101, 0x00d1, 0x005f, 0x0163, 0x011a, 0x00f3);
}

// e16 sources with the sign bit set in some elements
void TEST_CASE10(void) {
  VSET(8, e16, m1);
  VLOAD_16(v2, 0xa637, 0x87cb, 0xfabb, 0xf132, 0x1cdf, 0x6848, 0x9ab8, 0x6ed8);
  VLOAD_16(v4, 0xbf70, 0x1235, 0xf1ae, 0x0b2f, 0xa200, 0xd9a8, 0x7004, 0xe655);
  asm volatile("vwaddu.vv v6, v2, v4");
  VSET(8, e32, m2);
  VCMP_U32(26, v6, 0x000165a7, 0x00009a00, 0x0001ec69, 0x0000fc61,
                   0x0000bedf, 0x000141f0, 0x00010abc, 0x0001552d);
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
  asm volatile("vwaddu.vx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m2);
  VCMP_U16(27, v6, 0x0000, 0x00f2, 0x0000, 0x00a3, 0x00e3, 0x0000, 0x0168, 0x0000,
                   0x0126, 0x008e, 0x0000, 0x0000, 0x0000, 0x0000, 0x012f, 0x0083);
}

// e16 .vx: the scalar is truncated to SEW (0x8001)
void TEST_CASE12(void) {
  const uint32_t scalar = 0xabcd8001;
  VSET(8, e16, m1);
  VLOAD_16(v2, 0x2457, 0x3bdb, 0xcd7a, 0x7320, 0xb684, 0x9f28, 0xc534, 0xc447);
  asm volatile("vwaddu.vx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(8, e32, m2);
  VCMP_U32(28, v6, 0x0000a458, 0x0000bbdc, 0x00014d7b, 0x0000f321,
                   0x00013685, 0x00011f29, 0x00014535, 0x00014448);
}

// The destination may overlap vs2 in its highest-numbered half
void TEST_CASE13(void) {
  VSET(16, e8, m1);
  VLOAD_8(v5, 0xca, 0xae, 0x5f, 0x18, 0xc6, 0xe8, 0xcc, 0x40,
              0x5a, 0x7c, 0x2e, 0xf0, 0xa0, 0xa5, 0x5e, 0x1f);
  VLOAD_8(v8, 0x04, 0x18, 0x52, 0x14, 0xe6, 0x48, 0x18, 0xbd,
              0x96, 0xf7, 0x28, 0xb0, 0x6c, 0x9d, 0x99, 0x28);
  asm volatile("vwaddu.vv v4, v5, v8");
  VSET(16, e16, m2);
  VCMP_U16(29, v4, 0x00ce, 0x00c6, 0x00b1, 0x002c, 0x01ac, 0x0130, 0x00e4, 0x00fd,
                   0x00f0, 0x0173, 0x0056, 0x01a0, 0x010c, 0x0142, 0x00f7, 0x0047);
}

// Fractional source (LMUL = 1/2): one destination register
void TEST_CASE14(void) {
  VSET(8, e8, mf2);
  VLOAD_8(v2, 0x78, 0xeb, 0x38, 0x0d, 0x28, 0x07, 0xb0, 0xb6);
  VLOAD_8(v4, 0x25, 0x28, 0x10, 0x02, 0x8b, 0x27, 0x95, 0x2b);
  asm volatile("vwaddu.vv v6, v2, v4");
  VSET(8, e16, m1);
  VCMP_U16(30, v6, 0x009d, 0x0113, 0x0048, 0x000f, 0x00b3, 0x002e, 0x0145, 0x00e1);
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
  asm volatile("vwaddu.vv v6, v2, v4");
  VSET(16, e16, m2);
  VCMP_U16(31, v6, 0x0069, 0x0161, 0x00df, 0x01f1, 0x00bb, 0xaaaa, 0xaaaa, 0xaaaa,
                   0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
}

// .wv with LMUL = 2: the 2*SEW source is a group of four registers (at
// VLEN = 128), read once for each destination register
void TEST_CASE16(void) {
  VSET(32, e16, m4);
  VLOAD_16(v8, 0x857f, 0xcda2, 0x4ec1, 0xdeeb, 0xfe51, 0xd266, 0x6f5d, 0x4d16,
               0xce2d, 0xcb36, 0xf9de, 0xbef9, 0x1c2a, 0xad49, 0x671d, 0x788b,
               0x68e0, 0x8958, 0xe572, 0x0544, 0xa668, 0xc39a, 0x30b3, 0x301d,
               0xd05a, 0xcbc8, 0xea3b, 0x7b8e, 0x03cd, 0x5519, 0x70e0, 0x198e);
  VSET(32, e8, m2);
  VLOAD_8(v4, 0xb9, 0x0c, 0xb4, 0xe8, 0x72, 0xc6, 0xa9, 0x93,
              0x69, 0xb0, 0xd8, 0xb9, 0xf5, 0x42, 0x58, 0x94,
              0xef, 0x73, 0xc1, 0xd9, 0xae, 0xbb, 0x2d, 0xc3,
              0x0b, 0x13, 0x31, 0x07, 0x5d, 0xf3, 0xe7, 0xe0);
  asm volatile("vwaddu.wv v12, v8, v4");
  VSET(32, e16, m4);
  VCMP_U16(32, v12, 0x8638, 0xcdae, 0x4f75, 0xdfd3, 0xfec3, 0xd32c, 0x7006, 0x4da9,
                    0xce96, 0xcbe6, 0xfab6, 0xbfb2, 0x1d1f, 0xad8b, 0x6775, 0x791f,
                    0x69cf, 0x89cb, 0xe633, 0x061d, 0xa716, 0xc455, 0x30e0, 0x30e0,
                    0xd065, 0xcbdb, 0xea6c, 0x7b95, 0x042a, 0x560c, 0x71c7, 0x1a6e);
}

// .wv with vd = vs2: they have the same EEW, so they may overlap
void TEST_CASE17(void) {
  VSET(16, e16, m2);
  VLOAD_16(v8, 0xd12c, 0x6cdf, 0x339a, 0x2ce0, 0x8db4, 0x2686, 0xef41, 0xb38c,
               0x86e1, 0x1fa4, 0x19ca, 0x253b, 0xa18c, 0x9832, 0x7fcd, 0xeea6);
  VSET(16, e8, m1);
  VLOAD_8(v4, 0xd9, 0x1c, 0x72, 0xd5, 0x17, 0xa6, 0x26, 0x01,
              0x96, 0x13, 0xb6, 0x7d, 0xee, 0x1c, 0x7d, 0xc1);
  asm volatile("vwaddu.wv v8, v8, v4");
  VSET(16, e16, m2);
  VCMP_U16(33, v8, 0xd205, 0x6cfb, 0x340c, 0x2db5, 0x8dcb, 0x272c, 0xef67, 0xb38d,
                   0x8777, 0x1fb7, 0x1a80, 0x25b8, 0xa27a, 0x984e, 0x804a, 0xef67);
}

// e16 .wx: the scalar is truncated to SEW (0x8001)
void TEST_CASE18(void) {
  const uint32_t scalar = 0xabcd8001;
  VSET(8, e32, m2);
  VLOAD_32(v2, 0x00516886, 0x005eab59, 0x0087fd4b, 0x0063c8ca,
               0x00b7ac7a, 0x002bcec5, 0x0007ef0a, 0x006a8077);
  VSET(8, e16, m1);
  asm volatile("vwaddu.wx v6, v2, %[A]" ::[A] "r"(scalar));
  VSET(8, e32, m2);
  VCMP_U32(34, v6, 0x0051e887, 0x005f2b5a, 0x00887d4c, 0x006448cb,
                   0x00b82c7b, 0x002c4ec6, 0x00086f0b, 0x006b0078);
}

// Masked .wx: the scalar is truncated to SEW (0x80), and the elements of
// the second destination register (at VLEN = 128) take their mask from the
// matching v0 bits
void TEST_CASE19(void) {
  const uint32_t scalar = 0x12345680;
  VSET(16, e16, m2);
  VCLEAR(v6);
  VLOAD_16(v2, 0x81c0, 0x35c3, 0xf43e, 0xe2c6, 0x319a, 0x4025, 0xc456, 0xf7f3,
               0xe087, 0x39fb, 0xb99c, 0xbe80, 0x2e1c, 0x66fd, 0xb967, 0xace5);
  VSET(16, e8, m1);
  VLOAD_8(v0, 0x5a, 0xc3);
  asm volatile("vwaddu.wx v6, v2, %[A], v0.t" ::[A] "r"(scalar));
  VSET(16, e16, m2);
  VCMP_U16(35, v6, 0x0000, 0x3643, 0x0000, 0xe346, 0x321a, 0x0000, 0xc4d6, 0x0000,
                   0xe107, 0x3a7b, 0x0000, 0x0000, 0x0000, 0x0000, 0xb9e7, 0xad65);
}

// Fractional LMUL = 1/2: the 2*SEW source and the destination are one
// register
void TEST_CASE20(void) {
  VSET(8, e16, m1);
  VLOAD_16(v2, 0xcd6d, 0xd4ff, 0xd916, 0x30bb, 0xc0fd, 0x9445, 0x443a, 0x5e69);
  VSET(8, e8, mf2);
  VLOAD_8(v4, 0xe0, 0xd3, 0xfc, 0xb3, 0x3f, 0x05, 0xd2, 0x62);
  asm volatile("vwaddu.wv v6, v2, v4");
  VSET(8, e16, m1);
  VCMP_U16(36, v6, 0xce4d, 0xd5d2, 0xda12, 0x316e, 0xc13c, 0x944a, 0x450c, 0x5ecb);
}

// .wv with vl < VLMAX and tu: only the body is written
void TEST_CASE21(void) {
  VSET(16, e16, m2);
  VLOAD_16(v6, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa,
               0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
  VLOAD_16(v2, 0x191a, 0x743c, 0xbdee, 0x7eb0, 0x5060, 0xe865, 0xc41e, 0xc4df,
               0x51f0, 0xe2d8, 0xf974, 0x8b05, 0x38e1, 0x3cd0, 0xeac7, 0x991b);
  VSET(16, e8, m1);
  VLOAD_8(v4, 0xc7, 0x79, 0xc7, 0xa4, 0xc3, 0x84, 0x03, 0x54,
              0xa4, 0x47, 0x60, 0x47, 0x43, 0xb9, 0x76, 0x36);
  asm volatile("vsetivli t0, 5, e8, m1, tu, mu" ::: "t0");
  asm volatile("vwaddu.wv v6, v2, v4");
  VSET(16, e16, m2);
  VCMP_U16(37, v6, 0x19e1, 0x74b5, 0xbeb5, 0x7f54, 0x5123, 0xaaaa, 0xaaaa, 0xaaaa,
                   0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
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
  TEST_CASE11();
  TEST_CASE12();
  TEST_CASE13();
  TEST_CASE14();
  TEST_CASE15();
  TEST_CASE16();
  TEST_CASE17();
  TEST_CASE18();
  TEST_CASE19();
  TEST_CASE20();
  TEST_CASE21();

  EXIT_CHECK();
}
