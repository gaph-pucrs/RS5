// Copyright 2026 GAPH - PUCRS
// SPDX-License-Identifier: SHL-0.51
//
// Mask-producing compares and the bits they must not change (Zve32x
// conformance baseline, P0). The destination is a single mask register:
//  - masked-off body elements keep the old destination bit (mask undisturbed
//    is always a valid choice for vma)
//  - tail bits (element index >= vl) keep the old destination bit (tail
//    undisturbed is always a valid choice for the agnostic mask tail)
// The expected register is computed here from the inputs and compared with the
// whole destination register (vs1r.v).

#include <stdint.h>
#include <string.h>

#include "vector_macros.h"

#define VLENB_MAX 64 // VLEN = 512

static uint8_t src1[2 * VLENB_MAX] __attribute__((aligned(64)));
static uint8_t src2[2 * VLENB_MAX] __attribute__((aligned(64)));
static uint8_t mask[VLENB_MAX] __attribute__((aligned(64)));
static uint8_t old_vd[VLENB_MAX] __attribute__((aligned(64)));
static uint8_t got[VLENB_MAX] __attribute__((aligned(64)));
static uint8_t expected[VLENB_MAX] __attribute__((aligned(64)));

static unsigned long vlenb(void) {
  unsigned long v;
  asm volatile("csrr %0, vlenb" : "=r"(v));
  return v;
}

static int bit(const uint8_t *m, unsigned i) { return (m[i / 8] >> (i % 8)) & 1; }

static void set_bit(uint8_t *m, unsigned i, int b) {
  m[i / 8] = (m[i / 8] & ~(1u << (i % 8))) | ((b & 1) << (i % 8));
}

// Element i of an SEW-bit vector stored little-endian in buf
static uint32_t elem(const uint8_t *buf, unsigned i, unsigned sew) {
  uint32_t v = 0;
  for (unsigned b = 0; b < sew / 8; b++)
    v |= (uint32_t)buf[i * (sew / 8) + b] << (8 * b);
  return v;
}

// Reference for vmseq: old destination outside the active body elements
static void reference(unsigned vl, unsigned sew, int masked, const uint8_t *v0) {
  memcpy(expected, old_vd, vlenb());
  for (unsigned i = 0; i < vl; i++)
    if (!masked || bit(v0, i))
      set_bit(expected, i, elem(src1, i, sew) == elem(src2, i, sew));
}

static void fill_inputs(unsigned seed) {
  for (unsigned i = 0; i < 2 * VLENB_MAX; i++) {
    src1[i] = (uint8_t)(i * 7 + seed);
    // Every third byte equal, so compares see both outcomes at every SEW
    src2[i] = (i % 3 == 0) ? src1[i] : (uint8_t)(src1[i] ^ (1u << (i % 8)));
  }
  for (unsigned i = 0; i < VLENB_MAX; i++) {
    mask[i] = (uint8_t)(0xA5 ^ (i * 29 + seed));
    old_vd[i] = (uint8_t)(0x3C + i * 11 + seed);
  }
}

static void check(int casenum) {
  printf("Checking the results of the test case %d:\n", casenum);
  for (unsigned i = 0; i < vlenb(); i++) {
    if (got[i] != expected[i]) {
      printf("Byte %d FAILED. Got %x, expected %x.\n", i, got[i], expected[i]);
      num_failed++;
      return;
    }
  }
  printf("PASSED.\n");
}

// vmseq.vv v4, v8, v12[, v0.t] with v4 holding old_vd
#define CMP_CASE(casenum, vl_value, sew_str, lmul_str, sew, masked, insn)      \
  do {                                                                         \
    fill_inputs(casenum);                                                      \
    asm volatile("vl1re8.v v0, (%0)" ::"r"(mask));                             \
    asm volatile("vl1re8.v v4, (%0)" ::"r"(old_vd));                           \
    asm volatile("vl2re8.v v8, (%0)" ::"r"(src1));                             \
    asm volatile("vl2re8.v v12, (%0)" ::"r"(src2));                            \
    asm volatile("vsetvli zero, %0, " sew_str ", " lmul_str ", ta, mu" ::"r"(  \
        vl_value));                                                            \
    asm volatile(insn);                                                        \
    asm volatile("vs1r.v v4, (%0)" ::"r"(got) : "memory");                     \
    reference(current_vl(), sew, masked, mask);                                    \
    check(casenum);                                                            \
  } while (0)

// vmseq.vv v0, v8, v12, v0.t: v0 is both the mask and the destination
#define CMP_V0_CASE(casenum, vl_value, sew_str, lmul_str, sew)                 \
  do {                                                                         \
    fill_inputs(casenum);                                                      \
    memcpy(old_vd, mask, VLENB_MAX);                                           \
    asm volatile("vl1re8.v v0, (%0)" ::"r"(mask));                             \
    asm volatile("vl2re8.v v8, (%0)" ::"r"(src1));                             \
    asm volatile("vl2re8.v v12, (%0)" ::"r"(src2));                            \
    asm volatile("vsetvli zero, %0, " sew_str ", " lmul_str ", ta, mu" ::"r"(  \
        vl_value));                                                            \
    asm volatile("vmseq.vv v0, v8, v12, v0.t");                                \
    asm volatile("vs1r.v v0, (%0)" ::"r"(got) : "memory");                     \
    reference(current_vl(), sew, 1, mask);                                         \
    check(casenum);                                                            \
  } while (0)

// Unmasked: the tail keeps the old destination
void TEST_CASE1(void) {
  CMP_CASE(1, 16, "e8", "m1", 8, 0, "vmseq.vv v4, v8, v12");
  CMP_CASE(2, 13, "e16", "m1", 16, 0, "vmseq.vv v4, v8, v12");
  CMP_CASE(3, 7, "e32", "m1", 32, 0, "vmseq.vv v4, v8, v12");
}

// Masked: inactive body elements and the tail keep the old destination
void TEST_CASE2(void) {
  CMP_CASE(4, 16, "e8", "m1", 8, 1, "vmseq.vv v4, v8, v12, v0.t");
  CMP_CASE(5, 31, "e16", "m1", 16, 1, "vmseq.vv v4, v8, v12, v0.t");
  CMP_CASE(6, 9, "e32", "m1", 32, 1, "vmseq.vv v4, v8, v12, v0.t");
}

// LMUL = 2: two source registers per destination mask register
void TEST_CASE3(void) {
  CMP_CASE(7, 100, "e8", "m2", 8, 1, "vmseq.vv v4, v8, v12, v0.t");
  CMP_CASE(8, 40, "e16", "m2", 16, 1, "vmseq.vv v4, v8, v12, v0.t");
  CMP_CASE(9, 20, "e32", "m2", 32, 0, "vmseq.vv v4, v8, v12");
}

// vd = v0, masked (legal for mask-producing instructions)
void TEST_CASE4(void) {
  CMP_V0_CASE(10, 16, "e8", "m1", 8);
  CMP_V0_CASE(11, 100, "e8", "m2", 8);
  CMP_V0_CASE(12, 40, "e16", "m2", 16);
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
