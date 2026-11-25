// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>
//
// RS5 port: e64 cases commented out (ELEN = 32), including every vzext.vf8,
// which needs SEW = 64. TEST_CASE7 to TEST_CASE12 are RS5 cases: LMUL > 1,
// a fractional source read in parts, the destination overlapping the
// highest-numbered part of the source, vl < VLMAX with the tail undisturbed
// and a fractional destination. The RS5 cases load each source with SEW
// equal to its EEW: RS5 loads and stores still take EEW = SEW.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e16, m1);
  VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  asm volatile("vzext.vf2 v2, v1");
  VCMP_U16(1, v2, 1, 2, 253, 252, 5, 6, 249, 248, 255, 254, 3, 4, 251, 250, 7,
           8);

  VSET(16, e32, m1);
  VLOAD_16(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  asm volatile("vzext.vf2 v2, v1");
  VCMP_U32(2, v2, 1, 2, 65533, 65532, 5, 6, 65529, 65528, 65535, 65534, 3, 4,
           65531, 65530, 7, 8);

  // VSET(16, e64, m1);
  // VLOAD_32(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  // asm volatile("vzext.vf2 v2, v1");
  // VCMP_U64(3, v2, 1, 2, 4294967293, 4294967292, 5, 6, 4294967289, 4294967288,
  //          4294967295, 4294967294, 3, 4, 4294967291, 4294967290, 7, 8);
}

void TEST_CASE2(void) {
  VSET(16, e16, m1);
  VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vzext.vf2 v2, v1, v0.t");
  VCMP_U16(4, v2, 0, 2, 0, 252, 0, 6, 0, 248, 0, 254, 0, 4, 0, 250, 0, 8);

  VSET(16, e32, m1);
  VLOAD_16(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vzext.vf2 v2, v1, v0.t");
  VCMP_U32(5, v2, 0, 2, 0, 65532, 0, 6, 0, 65528, 0, 65534, 0, 4, 0, 65530, 0,
           8);

  // VSET(16, e64, m1);
  // VLOAD_32(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v2);
  // asm volatile("vzext.vf2 v2, v1, v0.t");
  // VCMP_U64(6, v2, 0, 2, 0, 4294967292, 0, 6, 0, 4294967288, 0, 4294967294, 0, 4,
  //          0, 4294967290, 0, 8);
}

void TEST_CASE3(void) {
  VSET(16, e32, m1);
  VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  asm volatile("vzext.vf4 v2, v1");
  VCMP_U32(7, v2, 1, 2, 253, 252, 5, 6, 249, 248, 255, 254, 3, 4, 251, 250, 7,
           8);

  // VSET(16, e64, m1);
  // VLOAD_16(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  // asm volatile("vzext.vf4 v2, v1");
  // VCMP_U64(8, v2, 1, 2, 65533, 65532, 5, 6, 65529, 65528, 65535, 65534, 3, 4,
  //          65531, 65530, 7, 8);
}

void TEST_CASE4(void) {
  VSET(16, e32, m1);
  VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v2);
  asm volatile("vzext.vf4 v2, v1, v0.t");
  VCMP_U32(9, v2, 0, 2, 0, 252, 0, 6, 0, 248, 0, 254, 0, 4, 0, 250, 0, 8);

  // VSET(16, e64, m1);
  // VLOAD_16(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  // VLOAD_8(v0, 0xAA, 0xAA);
  // VCLEAR(v2);
  // asm volatile("vzext.vf4 v2, v1, v0.t");
  // VCMP_U64(10, v2, 0, 2, 0, 65532, 0, 6, 0, 65528, 0, 65534, 0, 4, 0, 65530, 0,
  //          8);
}

// void TEST_CASE5(void) {
//   VSET(16, e64, m1);
//   VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
//   asm volatile("vzext.vf8 v2, v1");
//   VCMP_U64(11, v2, 1, 2, 253, 252, 5, 6, 249, 248, 255, 254, 3, 4, 251, 250, 7,
//            8);
// }

// void TEST_CASE6(void) {
//   VSET(16, e64, m1);
//   VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v2);
//   asm volatile("vzext.vf8 v2, v1, v0.t");
//   VCMP_U64(12, v2, 0, 2, 0, 252, 0, 6, 0, 248, 0, 254, 0, 4, 0, 250, 0, 8);
// }

// LMUL = 4: one source register is read once for each of the four
// destination registers (at VLEN = 128), each time a different quarter
void TEST_CASE7(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  VSET(16, e32, m4);
  asm volatile("vzext.vf4 v4, v1");
  VCMP_U32(13, v4, 1, 2, 253, 252, 5, 6, 249, 248, 255, 254, 3, 4, 251, 250, 7,
           8);

  // Source group of two registers, each read for two destination registers
  VSET(16, e16, m2);
  VLOAD_16(v2, 0x8000, 0x7fff, 0xffff, 0x0001, 0x1234, 0xfedc, 0x0000, 0x8001,
               0x4000, 0xc000, 0x00ff, 0xff00, 0x5555, 0xaaaa, 0x0f0f, 0xf0f0);
  VSET(16, e32, m4);
  asm volatile("vzext.vf2 v4, v2");
  VCMP_U32(14, v4, 0x8000, 0x7fff, 0xffff, 0x0001, 0x1234, 0xfedc, 0x0000, 0x8001,
                   0x4000, 0xc000, 0x00ff, 0xff00, 0x5555, 0xaaaa, 0x0f0f, 0xf0f0);
}

// LMUL = 2 masked: the elements in the second destination register take
// their mask from the matching v0 bits
void TEST_CASE8(void) {
  VSET(16, e8, m1);
  VLOAD_8(v1, 1, 2, -3, -4, 5, 6, -7, -8, -1, -2, 3, 4, -5, -6, 7, 8);
  VLOAD_8(v0, 0x5A, 0xC3);
  VSET(16, e16, m2);
  VCLEAR(v2);
  asm volatile("vzext.vf2 v2, v1, v0.t");
  VCMP_U16(15, v2, 0, 2, 0, 252, 5, 0, 249, 0, 255, 254, 0, 0, 0, 0, 7, 8);
}

// Fractional source (EMUL = 1/2): both destination registers (at VLEN = 128)
// come from the same source register, one quarter each
void TEST_CASE9(void) {
  VSET(8, e8, m1);
  VLOAD_8(v1, 0x80, 0x7f, 0xff, 0x01, 0xfe, 0x00, 0x81, 0x40);
  VSET(8, e32, m2);
  asm volatile("vzext.vf4 v2, v1");
  VCMP_U32(16, v2, 0x80, 0x7f, 0xff, 0x01, 0xfe, 0x00, 0x81, 0x40);
}

// The destination may overlap the highest-numbered part of the source
void TEST_CASE10(void) {
  VSET(16, e8, m1);
  VLOAD_8(v3, 0x80, 0x7f, 0xff, 0x01, 0xfe, 0x00, 0x81, 0x40,
              0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
  VSET(16, e16, m2);
  asm volatile("vzext.vf2 v2, v3");
  VCMP_U16(17, v2, 0x80, 0x7f, 0xff, 0x01, 0xfe, 0x00, 0x81, 0x40,
                   0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);

  VSET(16, e8, m1);
  VLOAD_8(v7, 0x80, 0x7f, 0xff, 0x01, 0xfe, 0x00, 0x81, 0x40,
              0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
  VSET(16, e32, m4);
  asm volatile("vzext.vf4 v4, v7");
  VCMP_U32(18, v4, 0x80, 0x7f, 0xff, 0x01, 0xfe, 0x00, 0x81, 0x40,
                   0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
}

// vl < VLMAX with tu: only the body is written
void TEST_CASE11(void) {
  VSET(8, e16, m1);
  VLOAD_16(v2, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
  VSET(8, e8, m1);
  VLOAD_8(v1, 0x81, 0x7f, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05);
  asm volatile("vsetivli t0, 3, e16, m1, tu, mu" ::: "t0");
  asm volatile("vzext.vf2 v2, v1");
  VSET(8, e16, m1);
  VCMP_U16(19, v2, 0x0081, 0x007f, 0x00ff, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa);
}

// Fractional destination (LMUL = 1/2): the source is the low quarter of
// its register
void TEST_CASE12(void) {
  VSET(4, e8, mf4);
  VLOAD_8(v1, 0x80, 0x7f, 0xff, 0x01);
  VSET(4, e16, mf2);
  asm volatile("vzext.vf2 v2, v1");
  VCMP_U16(20, v2, 0x0080, 0x007f, 0x00ff, 0x0001);
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
  TEST_CASE7();
  TEST_CASE8();
  TEST_CASE9();
  TEST_CASE10();
  TEST_CASE11();
  TEST_CASE12();

  EXIT_CHECK();
}
