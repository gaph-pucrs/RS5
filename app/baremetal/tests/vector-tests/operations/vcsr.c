// Copyright 2026 GAPH - PUCRS
// SPDX-License-Identifier: SHL-0.51
//
// Vector CSRs and mstatus.VS (Zve32x conformance baseline, P0):
//  - vxrm, vxsat and vcsr are read/write and vcsr aliases {vxrm, vxsat}
//  - vstart is writable, a vector instruction with vstart != 0 traps, and
//    vset{i}vl{i} executes and clears it
//  - mstatus.VS goes to Dirty (and SD to 1) after a vector instruction or a
//    write to a vector CSR
//  - with mstatus.VS = Off, vector instructions and vector CSR accesses trap

#include <stdint.h>

#include "vector_macros.h"

#define MSTATUS_SD (1ul << 31)

#define CHECK_EQ(casenum, got, expected)                                     \
  do {                                                                       \
    printf("Checking #%d...\n", casenum);                                    \
    if ((got) != (expected)) {                                               \
      printf("FAILED. Got %lx, expected %lx.\n", (unsigned long)(got),       \
             (unsigned long)(expected));                                     \
      num_failed++;                                                          \
    } else                                                                   \
      printf("PASSED.\n");                                                   \
  } while (0)

static inline unsigned long read_mstatus(void) {
  unsigned long v;
  asm volatile("csrr %0, mstatus" : "=r"(v));
  return v;
}

// vxrm, vxsat and vcsr
void TEST_CASE1(void) {
  unsigned long v;
  asm volatile("csrw vcsr, zero");
  asm volatile("csrwi vxrm, 3");
  asm volatile("csrr %0, vcsr" : "=r"(v));
  CHECK_EQ(1, v, 6);
  asm volatile("csrwi vxsat, 1");
  asm volatile("csrr %0, vcsr" : "=r"(v));
  CHECK_EQ(2, v, 7);
  asm volatile("csrwi vcsr, 5");
  asm volatile("csrr %0, vxrm" : "=r"(v));
  CHECK_EQ(3, v, 2);
  asm volatile("csrr %0, vxsat" : "=r"(v));
  CHECK_EQ(4, v, 1);
  // Only the implemented bits are kept
  asm volatile("csrw vcsr, %0" ::"r"(0xfffffff8ul));
  asm volatile("csrr %0, vcsr" : "=r"(v));
  CHECK_EQ(5, v, 0);
  asm volatile("csrw vxrm, %0" ::"r"(0xfffffffeul));
  asm volatile("csrr %0, vxrm" : "=r"(v));
  CHECK_EQ(6, v, 2);
  asm volatile("csrw vcsr, zero");
}

// vstart
void TEST_CASE2(void) {
  unsigned long v, traps_before;
  VSET(16, e8, m1);
  asm volatile("csrwi vstart, 1");
  asm volatile("csrr %0, vstart" : "=r"(v));
  CHECK_EQ(7, v, 1);
  // vadd.vv v1, v2, v3 with vstart != 0 is illegal
  EXPECT_ILLEGAL(8, 0x022180d7);
  // vle8.v v1, (a0) as well
  EXPECT_ILLEGAL(9, 0x02050087);
  // vsetvli executes and clears vstart
  traps_before = trap_save[1];
  VSET(16, e8, m1);
  asm volatile("csrr %0, vstart" : "=r"(v));
  CHECK_EQ(10, v, 0);
  CHECK_EQ(11, trap_save[1], traps_before);
}

// mstatus.VS and mstatus.SD
void TEST_CASE3(void) {
  unsigned long v;
  // Back to Initial
  asm volatile("csrc mstatus, %0" ::"r"(MSTATUS_VS));
  asm volatile("csrs mstatus, %0" ::"r"(MSTATUS_VS & (MSTATUS_VS >> 1)));
  v = read_mstatus();
  CHECK_EQ(12, v & (MSTATUS_VS | MSTATUS_SD), 0x200);
  // A vector instruction makes the state Dirty
  VSET(16, e8, m1);
  v = read_mstatus();
  CHECK_EQ(13, v & (MSTATUS_VS | MSTATUS_SD), MSTATUS_VS | MSTATUS_SD);
  // So does a write to a vector CSR
  asm volatile("csrc mstatus, %0" ::"r"(MSTATUS_VS));
  asm volatile("csrs mstatus, %0" ::"r"(MSTATUS_VS & (MSTATUS_VS >> 1)));
  asm volatile("csrwi vxrm, 1");
  v = read_mstatus();
  CHECK_EQ(14, v & (MSTATUS_VS | MSTATUS_SD), MSTATUS_VS | MSTATUS_SD);
  asm volatile("csrw vcsr, zero");
}

// With mstatus.VS = Off, vector instructions and vector CSRs are illegal.
// Nothing else runs while VS is Off, so the C code cannot emit a vector
// instruction in between; the trap handler records each trap.
void TEST_CASE4(void) {
  unsigned long traps_before = trap_save[1];
  unsigned long vs_off_mcause_or = 0, vs_off_mcause_and = ~0ul;
  unsigned long traps, v;
  asm volatile("csrc mstatus, %0" ::"r"(MSTATUS_VS));
#define VS_OFF_STEP(insn)                                                    \
  asm volatile(insn ::: "t0", "memory");                                     \
  vs_off_mcause_or |= trap_save[2];                                          \
  vs_off_mcause_and &= trap_save[2];
  VS_OFF_STEP("vsetvli t0, zero, e8, m1, ta, ma")
  VS_OFF_STEP(".word 0x022180d7") // vadd.vv v1, v2, v3
  VS_OFF_STEP("csrr t0, vl")
  VS_OFF_STEP("csrr t0, vtype")
  VS_OFF_STEP("csrr t0, vlenb")
  VS_OFF_STEP("csrr t0, vstart")
  VS_OFF_STEP("csrw vxrm, zero")
  VS_OFF_STEP("csrr t0, vxsat")
  VS_OFF_STEP("csrr t0, vcsr")
#undef VS_OFF_STEP
  traps = trap_save[1] - traps_before;
  asm volatile("csrs mstatus, %0" ::"r"(MSTATUS_VS & (MSTATUS_VS >> 1)));
  traps_expected = trap_save[1];
  CHECK_EQ(15, traps, 9);
  // Every trap was an illegal instruction (mcause = 2)
  CHECK_EQ(16, vs_off_mcause_or, 2);
  CHECK_EQ(17, vs_off_mcause_and, 2);
  // VS is not changed by the trapped instructions
  v = read_mstatus();
  CHECK_EQ(18, v & MSTATUS_VS, 0x200);
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
