// vfirst.m: index of the first set mask bit among the first vl elements, or -1.
// Written for VLEN = 512.

#include "vector_macros.h"

#define XCHECK(casenum, got, exp)                                          \
  do {                                                                     \
    printf("Checking the results of the test case %d:\n", casenum);        \
    if ((got) != (exp)) {                                                  \
      printf("FAILED. Got %ld, expected %ld.\n", (long)(got), (long)(exp)); \
      num_failed++;                                                        \
    } else                                                                 \
      printf("PASSED.\n");                                                 \
  } while (0)

static long first(void)   { long r; asm volatile("vfirst.m %0, v2" : "=r"(r)); return r; }
static long first_m(void) { long r; asm volatile("vfirst.m %0, v2, v0.t" : "=r"(r)); return r; }

void TEST_CASE1(void) {
  VSET(2, e8, m1);
  VLOAD_8(v2, 0x10, 0x01);
  VSET(16, e8, m1);
  XCHECK(1, first(), 4);
  // The first set bit is beyond vl
  VSET(4, e8, m1);
  XCHECK(2, first(), -1);
  VSET(2, e8, m1);
  VLOAD_8(v2, 0x00, 0x00);
  VSET(16, e8, m1);
  XCHECK(3, first(), -1);
}

void TEST_CASE2(void) {
  VSET(2, e8, m1);
  VLOAD_8(v2, 0x13, 0x01);
  VLOAD_8(v0, 0xfc, 0xff);
  VSET(16, e8, m1);
  XCHECK(4, first_m(), 4);
  VSET(2, e8, m1);
  VLOAD_8(v0, 0x00, 0x01);
  VSET(16, e8, m1);
  XCHECK(5, first_m(), 8);
}

// A bit near the end of a 512-bit mask register
void TEST_CASE3(void) {
  VSET(16, e32, m1);
  VLOAD_32(v2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00001000, 0x80000000);
  VSET(512, e8, m8);
  XCHECK(6, first(), 460);
  VSET(460, e8, m8);
  XCHECK(7, first(), -1);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  EXIT_CHECK();
}
