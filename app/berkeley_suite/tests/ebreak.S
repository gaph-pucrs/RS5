# See LICENSE for license details.

#*****************************************************************************
# ebreak.S
#-----------------------------------------------------------------------------
#
# Test syscall trap.
#

#include "encoding.h"
#include "riscv_test.h"
#include "test_macros.h"
#define __MACHINE_MODE

RVTEST_RV32U
RVTEST_CODE_BEGIN

#ifdef __MACHINE_MODE
  #define sscratch mscratch
  #define sstatus mstatus
  #define scause mcause
  #define stvec mtvec
  #define sepc mepc
  #define sret mret
  #define stvec_handler_ebreak mtvec_handler_ebreak
#endif

  la t0, stvec_handler_ebreak    # Grava o endereço do rótulo trap_handler
  csrw mtvec, t0                 # no registrador mtvec

  li TESTNUM, 2

do_break:
  ebreak
  j fail

  TEST_PASSFAIL

  .align 2
  .global stvec_handler_ebreak
stvec_handler_ebreak:
  li t1, CAUSE_BREAKPOINT
  csrr t0, scause
  # Check if CLIC mode
  csrr t2, stvec
  andi t2, t2, 2
  # Skip masking if non-CLIC mode
  beqz t2, skip_mask 
  andi t0, t0, 255
skip_mask:
  bne t0, t1, fail
  la t1, do_break
  csrr t0, sepc
  bne t0, t1, fail
  j pass

RVTEST_CODE_END

  .data
RVTEST_DATA_BEGIN

  TEST_DATA

RVTEST_DATA_END
