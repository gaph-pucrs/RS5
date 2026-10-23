// vid.v: element indices, masked, across LMUL > 1 register groups and at each SEW.
// Written for VLEN = 512.

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  __asm__ volatile("vid.v v1");
  VCMP_U8(1, v1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
}

// Masked: inactive elements keep their old value
void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v0, 0x55, 0x0f);
  VLOAD_8(v1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99);
  __asm__ volatile("vid.v v1, v0.t");
  VCMP_U8(2, v1, 0, 99, 2, 99, 4, 99, 6, 99, 8, 9, 10, 11, 99, 99, 99, 99);
}

// e16, m4: 32 elements per register, so v5 starts at index 32
void TEST_CASE3(void) {
  VSET(64, e16, m4);
  __asm__ volatile("vid.v v4");
  VSET(16, e16, m1);
  VCMP_U16(3, v4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  VCMP_U16(4, v5, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47);
}

// e32, m2 with vl = 20: v3 holds indices 16..19 and keeps its tail
void TEST_CASE4(void) {
  VSET(16, e32, m1);
  VLOAD_32(v3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7);
  VSET(20, e32, m2);
  __asm__ volatile("vid.v v2");
  VSET(16, e32, m1);
  VCMP_U32(5, v2, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  VCMP_U32(6, v3, 16, 17, 18, 19, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7);
}

// e8, m8: the last register of the group (v15) starts at index 7 * 64
void TEST_CASE5(void) {
  VSET(512, e8, m8);
  __asm__ volatile("vid.v v8");
  VSET(16, e16, m1);
  // indices 448, 449, ... wrap to 8 bits: 0xc0, 0xc1, ... read as 16-bit pairs
  VCMP_U16(7, v15, 0xc1c0, 0xc3c2, 0xc5c4, 0xc7c6, 0xc9c8, 0xcbca, 0xcdcc, 0xcfce,
           0xd1d0, 0xd3d2, 0xd5d4, 0xd7d6, 0xd9d8, 0xdbda, 0xdddc, 0xdfde);
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
