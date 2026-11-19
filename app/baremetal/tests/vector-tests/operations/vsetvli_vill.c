// Copyright 2026 GAPH - PUCRS
// SPDX-License-Identifier: SHL-0.51
//
// vtype.vill with ELEN = 32 (Zve32x conformance baseline, P0):
//  - vtype resets with vill = 1 and vl = 0
//  - SEW = 64, LMUL = 100 (reserved), SEW > LMUL * ELEN and reserved vtype
//    bits set vill, vl = 0 and write 0 to rd
//  - with vill = 1, instructions that depend on vtype trap; vset{i}vl{i},
//    whole register loads/stores and vmv<nr>r do not

#include <stdint.h>

#include "vector_macros.h"

#define VILL 0x80000000ul

static void check_vill(int casenum, unsigned long rd, int expect_vill) {
  unsigned long vtype, vl;
  read_vtype(vtype);
  read_vl(vl);
  printf("Checking vill #%d...\n", casenum);
  if (expect_vill ? (vtype != VILL || vl != 0 || rd != 0) : (vtype & VILL)) {
    printf("FAILED. vtype = %lx, vl = %lx, rd = %lx.\n", vtype, vl, rd);
    num_failed++;
  } else
    printf("PASSED.\n");
}

#define VSETVL_CHECK(casenum, avl, vtype_value, expect_vill)                  \
  do {                                                                         \
    unsigned long rd;                                                          \
    asm volatile("vsetvl %0, %1, %2" : "=r"(rd) : "r"(avl), "r"(vtype_value)); \
    check_vill(casenum, rd, expect_vill);                                      \
  } while (0)

#define VSETVLI_CHECK(casenum, cfg, expect_vill)                               \
  do {                                                                         \
    unsigned long rd;                                                          \
    asm volatile("vsetvli %0, %1, " cfg : "=r"(rd) : "r"(16));                 \
    check_vill(casenum, rd, expect_vill);                                      \
  } while (0)

// Reset state, before any vset{i}vl{i}
void TEST_CASE1(void) {
  check_vill(1, 0, 1);
  // vadd.vv v1, v2, v3 depends on vtype
  EXPECT_ILLEGAL(2, 0x022180d7);
  // vmv2r.v v2, v4 and vl1re8.v v1, (a0) do not
  // RVV 1.0 lists whole-register moves among the instructions that do not depend on vtype;
  // Sail 0.12 follows the later text that drops them and traps when vill is set
  SKIP_ON_SAIL(EXPECT_LEGAL(3, 0x9e40b157));
  EXPECT_LEGAL(4, 0x02850087);
}

// Unsupported SEW/LMUL combinations
void TEST_CASE2(void) {
  VSETVLI_CHECK(5, "e64, m1, ta, ma", 1);
  VSETVLI_CHECK(6, "e8, mf8, ta, ma", 1);
  VSETVLI_CHECK(7, "e16, mf4, ta, ma", 1);
  VSETVLI_CHECK(8, "e32, mf2, ta, ma", 1);
  VSETVLI_CHECK(9, "e8, mf4, ta, ma", 0);
  VSETVLI_CHECK(10, "e16, mf2, ta, ma", 0);
  VSETVLI_CHECK(11, "e32, m8, ta, ma", 0);
  // LMUL = 100 is reserved
  VSETVL_CHECK(12, 16, 0x04ul, 1);
  // SEW = 128
  VSETVL_CHECK(13, 16, 0x20ul, 1);
}

// Reserved vtype bits
void TEST_CASE3(void) {
  unsigned long rd;
  VSETVL_CHECK(14, 16, 0x100ul, 1);
  VSETVL_CHECK(15, 16, 0x40000000ul, 1);
  // vill written by software
  VSETVL_CHECK(16, 16, 0x80000000ul, 1);
  // vsetvli a1, a2, zimm = 0x100
  asm volatile("li a2, 16\n\t.word 0x100675d7\n\tmv %0, a1" : "=r"(rd)::"a1", "a2");
  check_vill(17, rd, 1);
  // vsetvli a1, a2, zimm = 0x400
  asm volatile("li a2, 16\n\t.word 0x400675d7\n\tmv %0, a1" : "=r"(rd)::"a1", "a2");
  check_vill(18, rd, 1);
  // vsetivli a1, 4, zimm = 0x100
  asm volatile(".word 0xd00275d7\n\tmv %0, a1" : "=r"(rd)::"a1");
  check_vill(19, rd, 1);
}

// With vill = 1, instructions that depend on vtype trap
void TEST_CASE4(void) {
  VSETVLI_CHECK(20, "e64, m1, ta, ma", 1);
  EXPECT_ILLEGAL(21, 0x022180d7); // vadd.vv v1, v2, v3
  EXPECT_ILLEGAL(22, 0x422025d7); // vmv.x.s a1, v2
  EXPECT_ILLEGAL(23, 0x02050087); // vle8.v v1, (a0)
  EXPECT_ILLEGAL(24, 0x02b50087); // vlm.v v1, (a0)
  EXPECT_ILLEGAL(25, 0x02b500a7); // vsm.v v1, (a0)
  SKIP_ON_SAIL(EXPECT_LEGAL(26, 0x9e40b157)); // vmv2r.v v2, v4 (Sail traps, see case 3)
  EXPECT_LEGAL(27, 0x22850107);   // vl2re8.v v2, (a0)
  EXPECT_LEGAL(28, 0x028500a7);   // vs1r.v v1, (a0)
  // vsetvli clears vill
  VSETVLI_CHECK(29, "e8, m1, ta, ma", 0);
  EXPECT_LEGAL(30, 0x022180d7);   // vadd.vv v1, v2, v3
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}
