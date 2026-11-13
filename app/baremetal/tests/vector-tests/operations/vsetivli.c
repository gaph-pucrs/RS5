// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>

#include "vector_macros.h"

//***********LMUL = 1**********//
void TEST_CASE1(void) {
  unsigned long avl, vtype,
      vl; // Declaring avl,vtype and vl variables to pass for comparison
  unsigned long vlmul = 0;    // Setting value of vlmul
  unsigned long vsew = 0;     // Setting value of vsew
  unsigned long vta = 1;      // Setting value of vta
  unsigned long vma = 1;      // Setting value of vma
  unsigned long golden_vtype; // Declaring variable to use as a reference value
  vtype(golden_vtype, vlmul, vsew, vta,
        vma); // Setting up reference variable golden_vtype by assigning
              // different fields of configurations
  __asm__ volatile("vsetivli %[A], 30, e8, m1, ta, ma"
                   : [A] "=r"(avl)); // Executing vsetivli instruction
  read_vtype(vtype);                 // Reading vtype CSR
  read_vl(vl);                       // Reading vl CSR
  check_vtype_vl(
      1, vtype, golden_vtype, avl, vl, vsew,
      vlmul); // Passsing actual values and reference values for comparison
}

void TEST_CASE2(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 0;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 20, e16, m1,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(2, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE3(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 0;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],10, e32, m1,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(3, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE4(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 0;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],16, e64, m1,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(4, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

/////////////////////////////////////////////////////////////////////////////////

//***********LMUL = 2**********//
void TEST_CASE5(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 1;
  unsigned long vsew = 0;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],30, e8, m2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(5, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE6(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 1;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],20, e16, m2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(6, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE7(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 1;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],10, e32, m2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(7, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE8(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 1;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],16, e64, m2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(8, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

///////////////////////////////////////////////////////////////////////////

//***********LMUL = 4**********//

void TEST_CASE9(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 2;
  unsigned long vsew = 0;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],30, e8, m4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(9, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE10(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 2;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],20, e16, m4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(10, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE11(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 2;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],10, e32, m4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(11, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE12(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 2;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],10, e64, m4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(12, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

/////////////////////////////////////////////////////////////////////////////////

//***********LMUL = 8**********//

void TEST_CASE13(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 3;
  unsigned long vsew = 0;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 30, e8, m8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(13, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE14(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 3;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 20, e16, m8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(14, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE15(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 3;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],10, e32, m8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(15, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE16(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 3;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 10, e64, m8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(16, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

/////////////////////////////////////////////////////////////////////////////////

//***********LMUL = 1/8**********//

void TEST_CASE17(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 5;
  unsigned long vsew = 0;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 10, e8, mf8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(17, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE18(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 5;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 10, e16,mf8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(18, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE19(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 5;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 5, e32, mf8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(19, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE20(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 5;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],7, e64, mf8,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(20, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

///////////////////////////////////////////////////////////////////////////

//***********LMUL = 1/4**********//

void TEST_CASE21(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 6;
  unsigned long vsew = 0;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 10, e8, mf4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(21, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE22(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 6;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 10, e16, mf4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(22, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE23(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 6;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],5, e32, mf4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(23, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE24(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 6;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],15, e64, mf4,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(24, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

/////////////////////////////////////////////////////////////////////////////////

//***********LMUL = 1/2**********//

void TEST_CASE25(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 7;
  unsigned long vsew = 0;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A],20, e8, mf2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(25, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE26(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 7;
  unsigned long vsew = 1;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 20, e16, mf2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(26, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE27(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 7;
  unsigned long vsew = 2;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 20, e32, mf2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(27, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

void TEST_CASE28(void) {
  unsigned long avl, vtype, vl;
  unsigned long vlmul = 7;
  unsigned long vsew = 3;
  unsigned long vta = 1;
  unsigned long vma = 1;
  unsigned long golden_vtype;
  vtype(golden_vtype, vlmul, vsew, vta, vma);
  __asm__ volatile("vsetivli %[A], 30, e64, mf2,ta,ma" : [A] "=r"(avl));
  read_vtype(vtype);
  read_vl(vl);
  check_vtype_vl(28, vtype, golden_vtype, avl, vl, vsew, vlmul);
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  printf("************* Running Test for vsetivli *************\n");
  TEST_CASE1();
  TEST_CASE2();
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
  TEST_CASE13();
  TEST_CASE14();
  TEST_CASE15();
  TEST_CASE16();
  TEST_CASE17();
  TEST_CASE18();
  TEST_CASE19();
  TEST_CASE20();
  TEST_CASE21();
  TEST_CASE22();
  TEST_CASE23();
  TEST_CASE24();
  TEST_CASE25();
  TEST_CASE26();
  TEST_CASE27();
  TEST_CASE28();

  EXIT_CHECK();
}
