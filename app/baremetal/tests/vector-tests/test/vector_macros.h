// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>

#ifndef __VECTOR_MACROS_H__
#define __VECTOR_MACROS_H__

#include <stdint.h>
#include "dataset.h"
//#include "rvv_debug_macros.h"
#include "encoding.h"
//#include "float_conversion.h"

#ifdef __SPIKE__
#include <stdio.h>

// We need to activate the FP and V extensions manually
#define enable_vec() do { asm volatile ("csrs mstatus, %[bits];" :: [bits] "r" (MSTATUS_VS & (MSTATUS_VS >> 1))); } while (0);
#else
#include "printf.h"

// The FP and V extensions are activated in the crt0 script
#define enable_vec()
#endif

/**************
 *  Counters  *
 **************/

// Counter for how many tests have failed
static int num_failed;
// Pointer to the current test case
static int test_case;

// Filled by the trap handler in test.S: { t1 spill, count, mcause, mepc, mtval }
extern volatile unsigned long trap_save[5];
// Number of traps the test expected so far; any other trap fails the test
static unsigned long traps_expected;

/************
 *  Macros  *
 ************/

#define read_vtype(buf) do { asm volatile ("csrr %[BUF], vtype" : [BUF] "=r" (buf)); } while (0);
#define read_vl(buf)    do { asm volatile ("csrr %[BUF], vl" : [BUF] "=r" (buf)); } while (0);
#define read_vxsat(buf) do { asm volatile ("csrr %[BUF], vxsat" : [BUF] "=r" (buf)); } while (0);
#define reset_vxsat     do { asm volatile ("csrw vxsat, %0" :: "rK"(0)); } while (0);
#define set_vxrm(val) do { asm volatile ("csrw vxrm, %0" :: "rK"(val)); } while (0);

#define vtype(golden_vtype, vlmul, vsew, vta, vma) (golden_vtype = vlmul << 0 | vsew << 3 | vta << 6 | vma << 7)

// Computes VLMAX = LMUL * VLEN / SEW from vlenb, so the expected vl does not
// depend on the VLEN the tests were written for (Ara assumes a larger VLEN).
static inline unsigned long vlmax_of(unsigned long vsew, unsigned long vlmul) {
  unsigned long vlenb;
  asm volatile ("csrr %[BUF], vlenb" : [BUF] "=r" (vlenb));
  unsigned long vlmax = (vlenb * 8) >> (3 + vsew);
  return (vlmul < 4) ? (vlmax << vlmul) : (vlmax >> (8 - vlmul));
}

// Checking vtype and vl value which is set by configuration setting instructions
// by comparing with golden_vtype value used as a reference. Also check for
// illegal values of vlmul and vsew. With ELEN = 32, SEW > 32 is illegal and a
// fractional LMUL needs SEW <= LMUL * ELEN: mf8 is never legal, mf4 only with
// e8 and mf2 with e8 and e16. LMUL = 100 is reserved.
#define check_vtype_vl(casenum, vtype, golden_vtype, avl, vl, vsew, vlmul)                                                     \
  printf("Checking vtype and vl #%d...\n", casenum); \
  if (avl > vlmax_of(vsew, vlmul)) avl = vlmax_of(vsew, vlmul); \
  if((vsew > 2) || vlmul==4 || vlmul==5 || (vlmul==6 && vsew > 0) || (vlmul==7 && vsew > 1)){   \
  if((vtype != 0x80000000) || (vl != 0)){    \
  printf("FAILED. Got vtype = %lx, expected vtype = 80000000. avl = %lx, vl = %lx.\n", vtype,avl, vl);     \
  num_failed++;                                            \
  return;                                                  \
  }}                                                        \
  else if (vtype != golden_vtype || avl != vl) {                                                                        \
    printf("FAILED. Got vtype = %lx, expected vtype = %lx. avl = %lx, vl = %lx.\n", vtype, golden_vtype, avl, vl); \
    num_failed++;                                                                                                  \
    return;                                                                                                        \
  }                                                                                                                \
  printf("PASSED.\n");

// Buffer used as the base address (a0) of the memory instructions below
static unsigned char illegal_buf[256] __attribute__((aligned(64)));

// Executes one raw instruction word with a0 = illegal_buf. The encoding may
// write a1. EXPECT_ILLEGAL checks that exactly one illegal-instruction trap
// was taken and that mtval holds the instruction; EXPECT_LEGAL checks that
// no trap was taken.
#define EXEC_WORD(word) \
  asm volatile("mv a0, %0\n\t.word " #word :: "r"(illegal_buf) : "a0", "a1", "memory")

#define EXPECT_ILLEGAL(casenum, word)                                               \
  do {                                                                              \
    unsigned long traps_before = trap_save[1];                                      \
    EXEC_WORD(word);                                                                \
    printf("Checking illegal instruction #%d...\n", casenum);                       \
    if (trap_save[1] != traps_before + 1 || trap_save[2] != 2 ||                    \
        trap_save[4] != (word)) {                                                   \
      printf("FAILED. traps = %lu, mcause = %lx, mtval = %lx.\n",                   \
             trap_save[1] - traps_before, trap_save[2], trap_save[4]);              \
      num_failed++;                                                                 \
    }                                                                               \
    else                                                                            \
      printf("PASSED.\n");                                                          \
    traps_expected = trap_save[1];                                                  \
  } while (0)

#define EXPECT_LEGAL(casenum, word)                                                 \
  do {                                                                              \
    unsigned long traps_before = trap_save[1];                                      \
    EXEC_WORD(word);                                                                \
    printf("Checking legal instruction #%d...\n", casenum);                         \
    if (trap_save[1] != traps_before) {                                             \
      printf("FAILED. Trapped with mcause = %lx, mtval = %lx.\n",                   \
             trap_save[2], trap_save[4]);                                           \
      num_failed++;                                                                 \
    }                                                                               \
    else                                                                            \
      printf("PASSED.\n");                                                          \
    traps_expected = trap_save[1];                                                  \
  } while (0)

#define check_vxsat(casenum, vxsat, golden_vxsat)                                                                  \
  printf("Checking vxsat #%d...\n", casenum);                                                               \
  if (vxsat != golden_vxsat) {                                                                        \
    printf("FAILED. Got vxsat = %lx, expected vxsat = %lx.\n", vxsat, golden_vxsat); \
    num_failed++;                                                                                                  \
    return;                                                                                                        \
  }                                                                                                                \
  printf("PASSED.\n");

// In order to avoid that scalar loads run ahead of vector stores,
// we use an instruction to ensure that all vector stores have been
// committed before continuing with scalar memory operations.
#define MEMORY_BARRIER // asm volatile ("fence");

// Zero-initialized variables can be problematic on bare-metal.
// Therefore, initialize them during runtime.
#define INIT_CHECK()  \
  num_failed = 0;     \
  test_case  = 0;     \
  traps_expected = trap_save[1];     \

// Check at the final of the execution whether all the tests passed or not.
// Returns the number of failed tests.
#define EXIT_CHECK()                                                \
  do {                                                              \
    MEMORY_BARRIER;                                                 \
    VCLEAR_BANK();                                                    \
    if (trap_save[1] != traps_expected) {                           \
      printf("FAILED. %lu unexpected trap(s), last mcause = %lx, mepc = %lx.\n", \
             trap_save[1] - traps_expected, trap_save[2], trap_save[3]); \
      num_failed++;                                                 \
    }                                                               \
    if (num_failed > 0) {                                           \
      printf("ERROR: %s failed %d tests!\n", __FILE__, num_failed); \
      return num_failed;                                            \
    }                                                               \
    else {                                                          \
      printf("PASSED: %s!\n", __FILE__);                            \
      return 0;                                                     \
    }                                                               \
  } while(0);                                                       \

// Check the result against a scalar golden value
#define XCMP(casenum,act,exp)                                           \
  printf("Checking the results of the test case %d:\n", casenum);       \
  if (act != exp) {                                                     \
    printf("Index %d FAILED. Got %d, expected %d.\n", casenum, act, exp);\
    num_failed++;                                                       \
    return;                                                             \
  }                                                                     \
  printf("PASSED.\n");                                                  \

// Current vl. The golden vectors are written for VLEN = 512; with a smaller
// VLEN, vl is capped at VLMAX and only the first vl elements are compared.
static inline unsigned long current_vl(void) {
  unsigned long vl;
  asm volatile ("csrr %[VL], vl" : [VL] "=r" (vl));
  return vl;
}

// Optional extra bound for the next compare: LIMIT_TO_VL() right after the
// instruction under test, when the compare itself runs with another vtype
// or LIMIT_TO_REG(sew) to bound it to the elements of one vector register.
static unsigned long vcmp_limit = ~0ul;
static inline unsigned long current_vlenb(void);
#define LIMIT_TO_VL()       (vcmp_limit = current_vl())
#define LIMIT_TO_REG(sew)   (vcmp_limit = current_vlenb() * 8 / (sew))

static inline unsigned long min_vl(unsigned long n) {
  unsigned long vl = current_vl();
  if (vl > vcmp_limit) vl = vcmp_limit;
  vcmp_limit = ~0ul;
  return (n < vl) ? n : vl;
}

// Check the results against a vector of golden values, up to vl elements
#define VCMP(T,str,casenum,vexp,act...)                                               \
  T vact[] = {act};                                                                   \
  printf("Checking the results of the test case %d:\n", casenum);                     \
  MEMORY_BARRIER;                                                                     \
  unsigned long vcmp_n = min_vl(sizeof(vact)/sizeof(T));                             \
  for (unsigned int i = 0; i < vcmp_n; i++) {                                         \
    if (vexp[i] != vact[i]) {                                                         \
      printf("Index %d FAILED. Got "#str", expected "#str".\n", i, vexp[i], vact[i]); \
      num_failed++;                                                                   \
      return;                                                                         \
    }                                                                                 \
  }                                                                                   \
  printf("PASSED.\n");

//Macro used to compare large number of elements, up to vl elements
#define LVCMP(T,str,casenum,elements, vexp ,vact)                                     \
  printf("Checking the results of the test case %d:\n",casenum);                      \
  MEMORY_BARRIER;                                                                     \
  unsigned long vcmp_n = min_vl(elements);                                           \
  for (unsigned int i = 0; i < vcmp_n; i++) {                                         \
    if (vexp[i] != vact[i]) {                                                         \
      printf("Index %d FAILED. Got "#str", expected "#str".\n", i, vexp[i], vact[i]); \
      num_failed++;                                                                   \
      return;                                                                         \
    }                                                                                 \
  }                                                                                   \
  printf("PASSED.\n");


/***********************************************************************
 *  VLEN-independent checks for reductions, compares and vslide1down    *
 ***********************************************************************/

// Largest vector register group the tests use: LMUL = 8 at VLEN = 512
#define VREG_GROUP_MAX_BYTES 512
#define VREG_MAX_BYTES       64

static uint8_t chk_src2[VREG_GROUP_MAX_BYTES] __attribute__((aligned(64)));
static uint8_t chk_src1[VREG_MAX_BYTES] __attribute__((aligned(64)));
static uint8_t chk_v0[VREG_MAX_BYTES] __attribute__((aligned(64)));
static uint8_t chk_old[VREG_MAX_BYTES] __attribute__((aligned(64)));
static uint8_t chk_got[VREG_GROUP_MAX_BYTES] __attribute__((aligned(64)));
static unsigned long chk_vl;

static inline unsigned long current_vlenb(void) {
  unsigned long vlenb;
  asm volatile ("csrr %[B], vlenb" : [B] "=r" (vlenb));
  return vlenb;
}

// Element i of an SEW-bit little-endian vector in memory, zero-extended
static inline uint32_t chk_elem(const uint8_t *buf, unsigned long i, unsigned sew) {
  uint32_t v = 0;
  for (unsigned b = 0; b < sew / 8; b++)
    v |= (uint32_t)buf[i * (sew / 8) + b] << (8 * b);
  return v;
}

static inline int32_t chk_signed(uint32_t v, unsigned sew) {
  return (sew == 32) ? (int32_t)v : (int32_t)(v << (32 - sew)) >> (32 - sew);
}

static inline int chk_bit(const uint8_t *m, unsigned long i) { return (m[i / 8] >> (i % 8)) & 1; }

typedef enum { RED_OP_SUM, RED_OP_AND, RED_OP_OR, RED_OP_XOR,
               RED_OP_MIN, RED_OP_MINU, RED_OP_MAX, RED_OP_MAXU } red_op_t;

// Reference reduction of vs1[0] and the active elements of vs2 below vl
static inline uint32_t red_reference(red_op_t op, unsigned sew, int masked) {
  uint32_t mask = (sew == 32) ? 0xffffffffu : ((1u << sew) - 1);
  uint32_t acc = chk_elem(chk_src1, 0, sew);
  for (unsigned long i = 0; i < chk_vl; i++) {
    if (masked && !chk_bit(chk_v0, i))
      continue;
    uint32_t x = chk_elem(chk_src2, i, sew);
    switch (op) {
      case RED_OP_SUM:  acc = acc + x; break;
      case RED_OP_AND:  acc = acc & x; break;
      case RED_OP_OR:   acc = acc | x; break;
      case RED_OP_XOR:  acc = acc ^ x; break;
      case RED_OP_MIN:  acc = (chk_signed(x, sew) < chk_signed(acc, sew)) ? x : acc; break;
      case RED_OP_MAX:  acc = (chk_signed(x, sew) > chk_signed(acc, sew)) ? x : acc; break;
      case RED_OP_MINU: acc = (x < acc) ? x : acc; break;
      case RED_OP_MAXU: acc = (x > acc) ? x : acc; break;
    }
    acc &= mask;
  }
  return acc;
}

// Saves the sources, v0, the old destination and vl right before a reduction
#define RED_SAVE(sew, vd, vs2, vs1)                                                   \
  do {                                                                                \
    chk_vl = current_vl();                                                            \
    asm volatile("vse" #sew ".v " #vs2 ", (%0)" ::"r"(chk_src2) : "memory");          \
    asm volatile("vs1r.v " #vs1 ", (%0)" ::"r"(chk_src1) : "memory");                 \
    asm volatile("vs1r.v v0, (%0)" ::"r"(chk_v0) : "memory");                         \
    asm volatile("vs1r.v " #vd ", (%0)" ::"r"(chk_old) : "memory");                   \
  } while (0)

// Element 0 of vd must hold the reference (or stay unchanged with vl = 0);
// the other elements keep the old destination
#define RED_CHECK(casenum, sew, op, masked, vd)                                       \
  do {                                                                                \
    asm volatile("vs1r.v " #vd ", (%0)" ::"r"(chk_got) : "memory");                   \
    uint32_t red_exp = chk_vl ? red_reference(op, sew, masked) : chk_elem(chk_old, 0, sew); \
    printf("Checking the results of the test case %d:\n", casenum);                   \
    if (chk_elem(chk_got, 0, sew) != red_exp) {                                       \
      printf("Index 0 FAILED. Got %x, expected %x.\n", chk_elem(chk_got, 0, sew), red_exp); \
      num_failed++;                                                                   \
      return;                                                                         \
    }                                                                                 \
    for (unsigned long i = sew / 8; i < current_vlenb(); i++) {                       \
      if (chk_got[i] != chk_old[i]) {                                                 \
        printf("Byte %d FAILED. Got %x, expected %x.\n", i, chk_got[i], chk_old[i]);  \
        num_failed++;                                                                 \
        return;                                                                       \
      }                                                                               \
    }                                                                                 \
    printf("PASSED.\n");                                                              \
  } while (0)

// Mask-producing compares: CMP_SAVE keeps the old destination before the
// compare and CMP_VL takes its vl right after it. VMCMP_MASK then checks the
// golden bits (written for 8 * nbytes elements) below that vl and the old
// destination above it.
#define CMP_SAVE(vd) asm volatile("vs1r.v " #vd ", (%0)" ::"r"(chk_old) : "memory")
#define CMP_VL()     (chk_vl = current_vl())

#define VMCMP_MASK(casenum, vd, golden...)                                            \
  do {                                                                                \
    uint8_t cmp_golden[] = {golden};                                                  \
    asm volatile("vs1r.v " #vd ", (%0)" ::"r"(chk_got) : "memory");                   \
    printf("Checking the results of the test case %d:\n", casenum);                   \
    for (unsigned long i = 0; i < 8 * sizeof(cmp_golden); i++) {                     \
      int exp = (i < chk_vl) ? chk_bit(cmp_golden, i) : chk_bit(chk_old, i);          \
      if (chk_bit(chk_got, i) != exp) {                                               \
        printf("Bit %d FAILED. Got %d, expected %d.\n", i, chk_bit(chk_got, i), exp); \
        num_failed++;                                                                 \
        return;                                                                       \
      }                                                                               \
    }                                                                                 \
    printf("PASSED.\n");                                                              \
  } while (0)

// vslide1down: with chk_vl the vl of the slide (CMP_VL() right after it),
// elements below vl - 1 match the golden vector, written for VLEN = 512, and
// element vl - 1 holds the scalar when it is active. Checked up to the
// current vl.
#define VSLIDE1DOWN_CMP(casenum, T, sew, vd, scalar, masked, golden...)               \
  do {                                                                                \
    T sld_golden[] = {golden};                                                        \
    unsigned long sld_n = (current_vl() < chk_vl) ? current_vl() : chk_vl;            \
    asm volatile("vs1r.v v0, (%0)" ::"r"(chk_v0) : "memory");                         \
    asm volatile("vse" #sew ".v " #vd ", (%0)" ::"r"(chk_got) : "memory");            \
    printf("Checking the results of the test case %d:\n", casenum);                   \
    for (unsigned long i = 0; i < sld_n; i++) {                                       \
      int sld_last = (i == chk_vl - 1) && (!(masked) || chk_bit(chk_v0, i));          \
      T exp = sld_last ? (T)(scalar) : sld_golden[i];                                 \
      if (((T *)chk_got)[i] != exp) {                                                 \
        printf("Index %d FAILED. Got %x, expected %x.\n", i, ((T *)chk_got)[i], exp); \
        num_failed++;                                                                 \
        return;                                                                       \
      }                                                                               \
    }                                                                                 \
    printf("PASSED.\n");                                                              \
  } while (0)

// Check the results against an in-memory vector of golden values
#define VMCMP(T,str,casenum,vexp,vgold,size)                                          \
  printf("Checking the results of the test case %d:\n", casenum);                     \
  MEMORY_BARRIER;                                                                     \
  for (unsigned int i = 0; i < size; i++) {                                           \
    if (vexp[i] != vgold[i]) {                                                        \
      printf("Index %d FAILED. Got "#str", expected "#str".\n", i, vexp[i], vgold[i]);\
      num_failed++;                                                                   \
      return;                                                                         \
    }                                                                                 \
  }                                                                                   \
  printf("PASSED.\n");

// Macros to set vector length, type and multiplier
// Don't use this to set VL == 0 since the compiler puts rs1 == x0
#define VSET(VLEN,VTYPE,LMUL)                                                          \
  do {                                                                                 \
  asm volatile ("vsetvli t0, %[A]," #VTYPE "," #LMUL ", ta, ma \n" :: [A] "r" (VLEN)); \
  } while(0)

// Macros to set vector length equal to zero
#define VSET_ZERO(VTYPE,LMUL)                                                              \
  do {                                                                                     \
    int vset_zero_buf;                                                                     \
    asm volatile("li %0, 0" : "=r" (vset_zero_buf));                                       \
    asm volatile("vsetvli x0, %0," #VTYPE "," #LMUL ", ta, ma \n" :: "r" (vset_zero_buf)); \
  } while(0)

#define VSETMAX(VTYPE,LMUL)                                                            \
  do {                                                                                 \
  int64_t scalar = -1;                                                                 \
  asm volatile ("vsetvli t1, %[A]," #VTYPE "," #LMUL", ta, ma \n":: [A] "r" (scalar)); \
  } while(0)

// Macro to load a vector register with data from the stack
#define VLOAD(datatype,loadtype,vreg,vec...)                                \
  do {                                                                      \
    volatile datatype V ##vreg[] = {vec};                                   \
    MEMORY_BARRIER;                                                         \
    asm volatile ("vl"#loadtype".v "#vreg", (%0)  \n":: [V] "r"(V ##vreg)); \
  } while(0)

// Macro to store a vector register into the pointer vec
#define VSTORE(T, storetype, vreg, vec)                                   \
  do {                                                                    \
    T* vec ##_t = (T*) vec;                                               \
    asm volatile ("vs"#storetype".v "#vreg", (%0)\n" : "+r" (vec ##_t));  \
    MEMORY_BARRIER;                                                       \
  } while(0)

// Macro to reset the whole register back to zero
/*#define VCLEAR(register)                                                                          \
  do {                                                                                            \
    MEMORY_BARRIER;                                                                               \
    uint64_t vtype; uint64_t vl; uint64_t vlmax;                                                  \
    asm volatile("csrr %[vtype], vtype" : [vtype] "=r" (vtype));                                  \
    asm volatile("csrr %[vl], vl" : [vl] "=r" (vl));                                              \
    asm volatile("vsetvl %[vlmax], zero, %[vtype]" : [vlmax] "=r" (vlmax) : [vtype] "r" (vtype)); \
    asm volatile("vmv.v.i "#register", 0");                                                       \
    asm volatile("vsetvl zero, %[vl], %[vtype]" :: [vl] "r" (vl), [vtype] "r" (vtype));           \
  } while(0)
*/

#define VCLEAR(register)                                                                          \
  do {                                                                                            \
    MEMORY_BARRIER;                                                                               \
    const uint32_t scalar = 0;                                                                    \
    asm volatile("vand.vx "#register", "#register", %[A]" ::[A] "r"(scalar));                                       \
  } while(0)
// Macro to initialize a vector with progressive values from a counter
#define INIT_MEM_CNT(vec_name, size) \
  counter = 0;                          \
  for (int i = 0 ; i < size; i++) {     \
    vec_name[i] = counter;              \
    counter++;                          \
  }                                     \

#define VCLEAR_BANK()                                                                             \
  do {                                                                                            \
    MEMORY_BARRIER;                                                                               \
    const uint32_t scalar = 0;                                                                    \
    asm volatile("vsetvli t0, x0, e32, m8, ta, ma");                                              \
    asm volatile("vmv.v.i v0,  0");                                                               \
    asm volatile("vmv.v.i v8,  0");                                                               \
    asm volatile("vmv.v.i v16, 0");                                                               \
    asm volatile("vmv.v.i v24, 0");                                                               \
  } while(0)

// Macro to initialize a vector with zeroes
// The vector is initialized on the stack, use this function with caution
// Easy to go in the UART address space
#define INIT_MEM_ZEROES(vec_name, size) \
  for (int i = 0 ; i < size; i++) {        \
    vec_name[i] = 0;                       \
  }                                        \

/***************************
 *  Type-dependant macros  *
 ***************************/

// Vector comparison
#define VCMP_U64(casenum,vect,act...) {VSTORE_U64(vect); VCMP(uint64_t,%x,casenum,Ru64,act)}
#define VCMP_U32(casenum,vect,act...) {VSTORE_U32(vect); VCMP(uint32_t,%x,casenum,Ru32,act)}
#define VCMP_U16(casenum,vect,act...) {VSTORE_U16(vect); VCMP(uint16_t,%x,casenum,Ru16,act)}
#define VCMP_U8(casenum,vect,act...)  {VSTORE_U8(vect) ; VCMP(uint8_t, %x,casenum, Ru8,act)}

#define LVCMP_U8(casenum,vect,vl,act)   {VSTORE_L8(vect); LVCMP(uint8_t, %x,casenum,vl, Lu8, act)}
#define LVCMP_U16(casenum,vect,vl,act)  {VSTORE_L16(vect); LVCMP(uint16_t, %x,casenum,vl,Lu16,act)}
#define LVCMP_U32(casenum,vect,vl,act)  {VSTORE_L32(vect); LVCMP(uint32_t, %x,casenum,vl,Lu32,act)}
#define LVCMP_U64(casenum,vect,vl,act)  {VSTORE_L64(vect); LVCMP(uint64_t, %x,casenum,vl,Lu64,act)}

#define VVCMP_U64(casenum,ptr64,act...) {VCMP(uint64_t,%x,casenum,ptr64,act)}
#define VVCMP_U32(casenum,ptr32,act...) {VCMP(uint32_t,%x,casenum,ptr32,act)}
#define VVCMP_U16(casenum,ptr16,act...) {VCMP(uint16_t,%x,casenum,ptr16,act)}
#define VVCMP_U8(casenum,ptr8,act...)   {VCMP(uint8_t, %x,casenum,ptr8, act)}

#define LVVCMP_U64(casenum,ptr64,vl,act) {LVCMP(uint64_t,%x,casenum,vl, ptr64,act)}
#define LVVCMP_U32(casenum,ptr32,vl,act) {LVCMP(uint32_t,%x,casenum,vl, ptr32,act)}
#define LVVCMP_U16(casenum,ptr16,vl,act) {LVCMP(uint16_t,%x,casenum,vl, ptr16,act)}
#define LVVCMP_U8(casenum,ptr8,vl,act)   {LVCMP(uint8_t, %x,casenum,vl, ptr8, act)}

#define VCMP_I64(casenum,vect,act...) {VSTORE_I64(vect); VCMP(int64_t,%ld, casenum,Ri64,act)}
#define VCMP_I32(casenum,vect,act...) {VSTORE_I32(vect); VCMP(int32_t,%d,  casenum,Ri32,act)}
#define VCMP_I16(casenum,vect,act...) {VSTORE_I16(vect); VCMP(int16_t,%hd, casenum,Ri16,act)}
#define VCMP_I8(casenum,vect,act...)  {VSTORE_I8(vect);  VCMP(int8_t, %hhd,casenum,Ri8, act)}

// Vector load
#define VLOAD_64(vreg,vec...) VLOAD(uint64_t,e64,vreg,vec)
#define VLOAD_32(vreg,vec...) VLOAD(uint32_t,e32,vreg,vec)
#define VLOAD_16(vreg,vec...) VLOAD(uint16_t,e16,vreg,vec)
#define VLOAD_8(vreg,vec...)  VLOAD(uint8_t, e8, vreg,vec)

// Vector store
#define VSTORE_U64(vreg) VSTORE(uint64_t,e64,vreg,Ru64)
#define VSTORE_U32(vreg) VSTORE(uint32_t,e32,vreg,Ru32)
#define VSTORE_U16(vreg) VSTORE(uint16_t,e16,vreg,Ru16)
#define VSTORE_U8(vreg)  VSTORE(uint8_t ,e8 ,vreg,Ru8 )

#define VSTORE_L64(vreg) VSTORE(uint64_t,e64,vreg,Lu64)
#define VSTORE_L32(vreg) VSTORE(uint32_t,e32,vreg,Lu32)
#define VSTORE_L16(vreg) VSTORE(uint16_t,e16,vreg,Lu16)
#define VSTORE_L8(vreg)  VSTORE(uint8_t ,e8 ,vreg,Lu8 )

#define VSTORE_I64(vreg) VSTORE(int64_t,e64,vreg,Ri64)
#define VSTORE_I32(vreg) VSTORE(int32_t,e32,vreg,Ri32)
#define VSTORE_I16(vreg) VSTORE(int16_t,e16,vreg,Ri16)
#define VSTORE_I8(vreg)  VSTORE(int8_t ,e8 ,vreg,Ri8 )

#endif // __VECTOR_MACROS_H__
