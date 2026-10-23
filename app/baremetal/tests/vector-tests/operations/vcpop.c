// vcpop.m: count of set mask bits among the first vl elements, masked and
// unmasked. Written for VLEN = 512.

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

static unsigned long cpop(void)   { unsigned long r; asm volatile("vcpop.m %0, v2" : "=r"(r)); return r; }
static unsigned long cpop_m(void) { unsigned long r; asm volatile("vcpop.m %0, v2, v0.t" : "=r"(r)); return r; }

void TEST_CASE1(void) {
  VSET(2, e8, m1);
  VLOAD_8(v2, 0xb5, 0x0f);
  VSET(16, e8, m1);
  XCHECK(1, cpop(), 9);
  // Only the first vl bits count
  VSET(10, e8, m1);
  XCHECK(2, cpop(), 7);
  VSET(0, e8, m1);
  XCHECK(3, cpop(), 0);
}

void TEST_CASE2(void) {
  VSET(2, e8, m1);
  VLOAD_8(v2, 0xb5, 0x0f);
  VLOAD_8(v0, 0xf0, 0xff);
  VSET(16, e8, m1);
  XCHECK(4, cpop_m(), 7);
  VSET(2, e8, m1);
  VLOAD_8(v0, 0x00, 0x00);
  VSET(16, e8, m1);
  XCHECK(5, cpop_m(), 0);
}

// A whole 512-bit mask register (e8, m8 gives vl = 512)
void TEST_CASE3(void) {
  VSET(16, e32, m1);
  VLOAD_32(v2, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
           0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000001);
  VSET(512, e8, m8);
  XCHECK(6, cpop(), 482);
  VSET(300, e8, m8);
  XCHECK(7, cpop(), 300);
}

int main(void) {
  INIT_CHECK();
  enable_vec();
  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  EXIT_CHECK();
}
