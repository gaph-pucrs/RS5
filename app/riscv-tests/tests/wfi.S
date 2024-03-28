# See LICENSE for license details.

#*****************************************************************************
# wfi.S
#-----------------------------------------------------------------------------
#
# Test wait-for-interrupt instruction.
#

#include "encoding.h"
#include "riscv_test.h"
#include "test_macros.h"
#define sstatus mstatus
#define sie mie
#define sip mip
#define SSTATUS_SIE MSTATUS_MIE
#define SIP_SSIP MIP_MSIP

RVTEST_RV32U
RVTEST_CODE_BEGIN

  # Make sure wfi doesn't halt the hart, even if interrupts are disabled
  csrc sstatus, SSTATUS_SIE
  csrs sie, SIP_SSIP
  csrs sip, SIP_SSIP
  wfi

  RVTEST_PASS

  TEST_PASSFAIL

RVTEST_CODE_END

  .data
RVTEST_DATA_BEGIN

  TEST_DATA

RVTEST_DATA_END