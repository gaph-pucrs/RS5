// TODO uncomment TEST_CASE13 and TEST_CASE 15 after issue of vl=0 and
// non-zero vstart is resolved
// TODO uncomment TEST_CASE2 after issue of exception is resolved

#include "long_array.h"
#include "vector_macros.h"
#define AXI_DWIDTH 128
// Exception Handler for rtl

void mtvec_handler(void) {
  asm volatile("csrr t0, mcause"); // Read mcause

  // Read mepc
  asm volatile("csrr t1, mepc");

  // Increment return address by 4
  asm volatile("addi t1, t1, 4");
  asm volatile("csrw mepc, t1");

  // Filter with mcause and handle here

  asm volatile("mret");
}
// Exception Handler for spike
void handle_trap(void) {
  // Read mepc
  asm volatile("csrr t1, mepc");

  // Increment return address by 4
  asm volatile("addi t1, t1, 4");
  asm volatile("csrw mepc, t1");

  asm volatile("lw ra, 8(sp)");
  asm volatile("lw sp, 16(sp)");
  asm volatile("lw gp, 24(sp)");
  asm volatile("lw tp, 32(sp)");
  asm volatile("lw t0, 40(sp)");
  asm volatile("lw t0, 40(sp)");
  asm volatile("lw t1, 48(sp)");
  asm volatile("lw t2, 56(sp)");
  asm volatile("lw s0, 64(sp)");
  asm volatile("lw s1, 72(sp)");
  asm volatile("lw a0, 80(sp)");
  asm volatile("lw a1, 88(sp)");
  asm volatile("lw a2, 96(sp)");
  asm volatile("lw a3, 104(sp)");
  asm volatile("lw a4, 112(sp)");
  asm volatile("lw a5, 120(sp)");
  asm volatile("lw a6, 128(sp)");
  asm volatile("lw a7, 136(sp)");
  asm volatile("lw s2, 144(sp)");
  asm volatile("lw s3, 152(sp)");
  asm volatile("lw s4, 160(sp)");
  asm volatile("lw s5, 168(sp)");
  asm volatile("lw s6, 176(sp)");
  asm volatile("lw s7, 184(sp)");
  asm volatile("lw s8, 192(sp)");
  asm volatile("lw s9, 200(sp)");
  asm volatile("lw s10, 208(sp)");
  asm volatile("lw s11, 216(sp)");
  asm volatile("lw t3, 224(sp)");
  asm volatile("lw t4, 232(sp)");
  asm volatile("lw t5, 240(sp)");
  asm volatile("lw t6, 248(sp)");

  // Read mcause
  asm volatile("csrr t3, mcause");

  asm volatile("addi sp, sp, 272");

  // Filter with mcause and handle here

  asm volatile("mret");
}

static volatile uint32_t ALIGNED_I32[16]
    __attribute__((aligned(AXI_DWIDTH))) = {
        0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
        0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301, 0xab8b9148,
        0x90318509, 0x31897598, 0x83195999, 0x89139848};

//**********Checking functionality of vle32********//
void TEST_CASE1(void) {
  VSET(15, e32, m1);
  asm volatile("vle32.v v0, (%0)" ::"r"(&ALIGNED_I32[1]));
  VCMP_U32(1, v0, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
           0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301,
           0xab8b9148, 0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

//******Checking functionality of  with illegal destination register
// specifier for EMUL********//
// In this test case EMUL=2 and register is v1 which will cause illegal
// instruction exception and set mcause = 2
void TEST_CASE2(void) {
  // uint8_t mcause;
  // VSET(15, e64, m4);
  // asm volatile("vle32.v v1, (%0)" ::"r"(&ALIGNED_I32[1]));
  // asm volatile("addi %[A], t3, 0" : [A] "=r"(mcause));
  // XCMP(2, mcause, 2);
}

//*******Checking functionality of vle32 with different values of masking
// register******//
void TEST_CASE3(void) {
  VSET(16, e32, m1);
  VCLEAR(v3);
  VLOAD_8(v0, 0xFF, 0xFF);
  asm volatile("vle32.v v3, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VCMP_U32(3, v3, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7,
           0x38197598, 0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee,
           0x90139301, 0xab8b9148, 0x90318509, 0x31897598, 0x83195999,
           0x89139848);
}

void TEST_CASE4(void) {
  VSET(16, e32, m1);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0x00, 0x00);
  asm volatile("vle32.v v3, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VCMP_U32(4, v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE5(void) {
  VSET(16, e32, m1);
  VCLEAR(v3);
  VLOAD_32(v3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  asm volatile("vle32.v v3, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VCMP_U32(5, v3, 1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598, 7, 0x81937598, 9,
           0x3eeeeeee, 11, 0xab8b9148, 13, 0x31897598, 15, 0x89139848);
}

//******Checking functionality with different combinations of vta and vma*****//
// **** It uses undisturbed policy for tail agnostic and mask agnostic****//
void TEST_CASE6(void) {
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vle32.v v4, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VSET(16, e32, m1);
  VCMP_U32(6, v4, 1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598, 7, 0x81937598, 9,
           0x3eeeeeee, 11, 0xab8b9148, 13, 14, 15, 16);
}

void TEST_CASE7(void) {
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, ta, mu" : [A] "=r"(avl));
  asm volatile("vle32.v v4, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VSET(16, e32, m1);
  VCMP_U32(7, v4, 1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598, 7, 0x81937598, 9,
           0x3eeeeeee, 11, 0xab8b9148, 13, 14, 15, 16);
}

void TEST_CASE8(void) {
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, tu, ma" : [A] "=r"(avl));
  asm volatile("vle32.v v4, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VSET(16, e32, m1);
  VCMP_U32(8, v4, 1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598, 7, 0x81937598, 9,
           0x3eeeeeee, 11, 0xab8b9148, 13, 14, 15, 16);
}

void TEST_CASE9(void) {
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VLOAD_8(v0, 0xAA, 0xAA);
  __asm__ volatile("vsetivli %[A], 12, e32, m1, tu, mu" : [A] "=r"(avl));
  asm volatile("vle32.v v4, (%0), v0.t" ::"r"(&ALIGNED_I32[0]));
  VSET(16, e32, m1);
  VCMP_U32(9, v4, 1, 0xf9aa71f0, 3, 0x99991348, 5, 0x38197598, 7, 0x81937598, 9,
           0x3eeeeeee, 11, 0xab8b9148, 13, 14, 15, 16);
}

//*******Checking functionality if encoded EEW is not supported for given SEW
// and LMUL values because EMUL become out of range*****//
// This test case cover corner case for EEW = 32.If LMUL is changed to
// mf8 and SEW is changed to e64 it will give error because emul become less
// than 1/8 (EMUL = 1/16) But it does not support this configuration because
// SEW/LMUL > ELEN
void TEST_CASE10(void) {
  // VSET(15, e32, mf2);
  // asm volatile("vle32.v v5, (%0)" ::"r"(&ALIGNED_I32[1]));
  // VCMP_U32(10, v5, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
  //          0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301,
  //          0xab8b9148, 0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

// This test case execute upper bound case of EMUL (8)
// If LMUL is changed to m8 or m4 it will give error because emul become greater
// than
// 8
// (EMUL = 16)

void TEST_CASE11(void) {
  // VSET(16, e8, m2);
  // asm volatile("vle32.v v8, (%0)" ::"r"(&ALIGNED_I32[0]));
  // VCMP_U32(11, v8, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7,
  //          0x38197598, 0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee,
  //          0x90139301, 0xab8b9148, 0x90318509, 0x31897598, 0x83195999,
  //          0x89139848);
}

//******Checking functionality with different values of vl******//
void TEST_CASE12(void) {
  VSET(16, e32, m1);
  VLOAD_32(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VSET(16, e32, m1);
  asm volatile("vle32.v v6, (%0)" ::"r"(&ALIGNED_I32[0]));
  VSET(16, e32, m1);
  VCMP_U32(12, v6, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7,
           0x38197598, 0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee,
           0x90139301, 0xab8b9148, 0x90318509, 0x31897598, 0x83195999,
           0x89139848);
}

void TEST_CASE13(void) {
  uint64_t avl;
  VSET(16, e32, m1);
  VLOAD_32(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  __asm__ volatile("vsetivli %[A], 0, e16, m1, ta, ma" : [A] "=r"(avl));
  asm volatile("vle32.v v6, (%0)" ::"r"(&ALIGNED_I32[0]));
  VSET(16, e32, m1);
  VCMP_U32(13, v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
}

void TEST_CASE14(void) {
  VCLEAR(v6);
  VSET(32, e16, m1);
  VLOAD_32(v6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  VSET(13, e32, m1);
  asm volatile("vle32.v v6, (%0)" ::"r"(&ALIGNED_I32[0]));
  VSET(32, e16, m1);
  VCMP_U32(14, v6, 0x9fe41920, 0xf9aa71f0, 0xa11a9384, 0x99991348, 0x9fa831c7,
           0x38197598, 0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee,
           0x90139301, 0xab8b9148, 0x90318509, 14, 15, 16);
}

//******Checking functionality with different vstart value*****//
void TEST_CASE15(void) {
  // VSET(16, e32, m1);
  // VLOAD_32(v7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  // write_csr(vstart, 2);
  // asm volatile("vle32.v v7, (%0)" ::"r"(&ALIGNED_I32[0]));
  // VSET(15, e32, m1);
  // VCMP_U32(16, v7, 1, 2, 0xa11a9384, 0x99991348, 0x9fa831c7, 0x38197598,
  //          0x18931795, 0x81937598, 0x18747547, 0x3eeeeeee, 0x90139301,
  //          0xab8b9148, 0x90318509, 0x31897598, 0x83195999, 0x89139848);
}

//****Checking functionality with different values of EMUL and
// large number of elements *******//

void TEST_CASE16(void) {
  VSET(128, e32, m8);
  asm volatile("vle32.v v8, (%0)" ::"r"(&LONG_I32[0]));
  LVCMP_U32(16, v8, 128, LONG_I32);
}

void TEST_CASE17(void) {
  VSET(64, e32, m4);
  asm volatile("vle32.v v12, (%0)" ::"r"(&LONG_I32[0]));
  LVCMP_U32(17, v12, 64, LONG_I32);
}

void TEST_CASE18(void) {
  VSET(32, e32, m2);
  asm volatile("vle32.v v14, (%0)" ::"r"(&LONG_I32[0]));
  LVCMP_U32(18, v14, 32, LONG_I32);
}

void TEST_CASE19(void) {
  VSET(26, e32, m2);
  asm volatile("vle32.v v16, (%0)" ::"r"(&LONG_I32[0]));
  LVCMP_U32(19, v16, 26, LONG_I32);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  printf("*****Running tests for vle32.v*****\n");
  TEST_CASE1();
  // TEST_CASE2();
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
  // TEST_CASE13();
  TEST_CASE14();
  // TEST_CASE15();
  TEST_CASE16();
  TEST_CASE17();
  TEST_CASE18();
  TEST_CASE19();
  EXIT_CHECK();
}
