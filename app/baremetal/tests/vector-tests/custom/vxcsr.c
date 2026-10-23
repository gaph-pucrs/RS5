// vxrm, vxsat and vcsr: field widths, the vcsr view of both fields, and the
// set/clear CSR forms.

#include <stdint.h>

#include "vector_macros.h"

#define CHECK(casenum, got, exp)                                    \
  do {                                                              \
    printf("Checking CSR #%d...\n", casenum);                       \
    if ((got) != (exp)) {                                           \
      printf("FAILED. Got %lx, expected %lx.\n", (unsigned long)(got), (unsigned long)(exp)); \
      num_failed++;                                                 \
    } else                                                          \
      printf("PASSED.\n");                                          \
  } while (0)

static unsigned long rd_vxrm(void)  { unsigned long v; asm volatile("csrr %0, vxrm"  : "=r"(v)); return v; }
static unsigned long rd_vxsat(void) { unsigned long v; asm volatile("csrr %0, vxsat" : "=r"(v)); return v; }
static unsigned long rd_vcsr(void)  { unsigned long v; asm volatile("csrr %0, vcsr"  : "=r"(v)); return v; }

int main(void) {
  INIT_CHECK();
  enable_vec();

  // Only the low bits are kept
  asm volatile("li t0, 0xff\n csrw vxrm, t0" ::: "t0");
  CHECK(1, rd_vxrm(), 3);
  asm volatile("li t0, 0xff\n csrw vxsat, t0" ::: "t0");
  CHECK(2, rd_vxsat(), 1);
  CHECK(3, rd_vcsr(), 7);

  // vcsr writes both fields: vcsr[2:1] = vxrm, vcsr[0] = vxsat
  asm volatile("csrwi vcsr, 4");
  CHECK(4, rd_vxrm(), 2);
  CHECK(5, rd_vxsat(), 0);
  CHECK(6, rd_vcsr(), 4);

  // Set and clear forms
  asm volatile("csrsi vxrm, 1");
  CHECK(7, rd_vxrm(), 3);
  asm volatile("csrci vxrm, 2");
  CHECK(8, rd_vxrm(), 1);
  asm volatile("csrsi vxsat, 1");
  CHECK(9, rd_vcsr(), 3);
  asm volatile("csrwi vcsr, 0");
  CHECK(10, rd_vcsr(), 0);

  // A vxrm write takes effect on the very next vector instruction
  unsigned long r;
  VSET(1, e8, m1);
  VLOAD_8(v2, 3);
  asm volatile("csrwi vxrm, 0\n vssrl.vi v1, v2, 1\n vmv.x.s %0, v1" : "=r"(r));  // 3/2 rnu -> 2
  CHECK(11, r & 0xff, 2);
  asm volatile("csrwi vxrm, 2\n vssrl.vi v1, v2, 1\n vmv.x.s %0, v1" : "=r"(r));  // 3/2 rdn -> 1
  CHECK(12, r & 0xff, 1);

  EXIT_CHECK();
}
