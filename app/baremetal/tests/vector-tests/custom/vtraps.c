// Illegal vector instructions must raise an illegal-instruction exception
// (mcause = 2) and must not execute. Legal instructions must not trap.
// The test installs its own trap handler, which counts traps, records mcause
// and returns to the next instruction.

#include <stdint.h>

#include "vector_macros.h"

volatile unsigned long trap_count;
volatile unsigned long trap_cause;

void vtrap_handler(void);
asm(
    ".align 2\n"
    "vtrap_handler:\n"
    "  addi sp, sp, -16\n"
    "  sw   t0, 0(sp)\n"
    "  sw   t1, 4(sp)\n"
    "  csrr t0, mcause\n"
    "  la   t1, trap_cause\n"
    "  sw   t0, 0(t1)\n"
    "  la   t1, trap_count\n"
    "  lw   t0, 0(t1)\n"
    "  addi t0, t0, 1\n"
    "  sw   t0, 0(t1)\n"
    "  csrr t0, mepc\n"
    "  addi t0, t0, 4\n"
    "  csrw mepc, t0\n"
    "  lw   t0, 0(sp)\n"
    "  lw   t1, 4(sp)\n"
    "  addi sp, sp, 16\n"
    "  mret\n");

#define ILLEGAL_INSTRUCTION 2

#define EXPECT_TRAP(casenum, insn, ...)                                              \
  do {                                                                               \
    trap_count = 0;                                                                  \
    trap_cause = 0;                                                                  \
    asm volatile(insn __VA_ARGS__);                                                  \
    printf("Checking trap #%d...\n", casenum);                                      \
    if (trap_count != 1 || trap_cause != ILLEGAL_INSTRUCTION) {                      \
      printf("FAILED. traps = %lu, mcause = %lu\n", trap_count, trap_cause);        \
      num_failed++;                                                                  \
    } else                                                                           \
      printf("PASSED.\n");                                                           \
  } while (0)

#define EXPECT_NO_TRAP(casenum, insn, ...)                                           \
  do {                                                                               \
    trap_count = 0;                                                                  \
    asm volatile(insn __VA_ARGS__);                                                  \
    printf("Checking no trap #%d...\n", casenum);                                   \
    if (trap_count != 0) {                                                           \
      printf("FAILED. traps = %lu, mcause = %lu\n", trap_count, trap_cause);        \
      num_failed++;                                                                  \
    } else                                                                           \
      printf("PASSED.\n");                                                           \
  } while (0)

static uint8_t buf[256] __attribute__((aligned(4)));

// Encodings that are not standard or not implemented
void TEST_CASE1(void) {
  VSET(4, e32, m1);
  EXPECT_TRAP(1, ".word 0x022190d7");  // vfadd.vv v1, v2, v3 (OPFVV)
  EXPECT_TRAP(2, ".word 0x9e860257");  // vsmul.vv v4, v8, v12 (ran as vmv<nr>r)
  EXPECT_TRAP(3, ".word 0x0e860257");  // vrsub.vv: reserved form
  EXPECT_TRAP(4, ".word 0x5e160257");  // vmv.v.v with vs2 != 0: reserved
  EXPECT_TRAP(5, ".word 0x9e813257");  // vmv3r.v: nr must be 1/2/4/8
}

// Loads and stores outside Zve32x
void TEST_CASE2(void) {
  VSET(4, e32, m1);
  EXPECT_TRAP(6, "mv a0, %0\n .word 0x22050207" ::"r"(buf) : "a0");  // vlseg2e8.v v4, (a0)
  EXPECT_TRAP(7, "mv a0, %0\n .word 0x02057207" ::"r"(buf) : "a0");  // vle64.v v4, (a0)
  EXPECT_TRAP(8, "mv a0, %0\n .word 0x00052207" ::"r"(buf) : "a0");  // flw f4, 0(a0)
  EXPECT_TRAP(9, "mv a0, %0\n .word 0x12050207" ::"r"(buf) : "a0");  // vle8 with mew = 1
  EXPECT_NO_TRAP(10, "vle8.v v4, (%0)" ::"r"(buf));
}

// vill: SEW = 64 is not supported, vl becomes 0, and instructions that
// depend on vtype trap until the next valid vsetvl
void TEST_CASE3(void) {
  unsigned long vl_rd = 99, vtype, vl;
  asm volatile("vsetivli %0, 4, e64, m1, ta, ma" : "=r"(vl_rd));
  read_vtype(vtype);
  read_vl(vl);
  printf("Checking vill #11...\n");
  if (vtype != 0x80000000 || vl != 0 || vl_rd != 0) {
    printf("FAILED. vtype = %lx, vl = %lu, rd = %lu\n", vtype, vl, vl_rd);
    num_failed++;
  } else
    printf("PASSED.\n");

  EXPECT_TRAP(12, "vadd.vv v1, v2, v3");
  EXPECT_TRAP(13, "vle32.v v4, (%0)" ::"r"(buf));
  EXPECT_TRAP(14, "vmv.x.s t0, v4" ::: "t0");
  // Whole-register moves, loads and stores do not depend on vtype
  EXPECT_NO_TRAP(15, "vmv1r.v v1, v2");
  EXPECT_NO_TRAP(16, "vl1re8.v v4, (%0)" ::"r"(buf));
  EXPECT_NO_TRAP(17, "vs1r.v v4, (%0)" ::"r"(buf));

  // A valid vsetvli clears vill
  VSET(4, e32, m1);
  EXPECT_NO_TRAP(18, "vadd.vv v1, v2, v3");
}

// Reserved vtype values set vill
void TEST_CASE4(void) {
  unsigned long vtype;
  // Reserved bits in the vsetvl operand
  asm volatile("li t1, 0x110\n vsetvl t0, zero, t1" ::: "t0", "t1");  // bit 8 set, e32
  read_vtype(vtype);
  printf("Checking vill #19...\n");
  if (vtype != 0x80000000) {
    printf("FAILED. vtype = %lx\n", vtype);
    num_failed++;
  } else
    printf("PASSED.\n");

  // Reserved LMUL (vlmul = 100)
  asm volatile("li t1, 0x14\n vsetvl t0, zero, t1" ::: "t0", "t1");
  read_vtype(vtype);
  printf("Checking vill #20...\n");
  if (vtype != 0x80000000) {
    printf("FAILED. vtype = %lx\n", vtype);
    num_failed++;
  } else
    printf("PASSED.\n");

  VSET(4, e32, m1);
}

// Widening needs 2*SEW <= ELEN
void TEST_CASE5(void) {
  VSET(4, e32, m1);
  EXPECT_TRAP(21, "vwmul.vv v4, v8, v12");
  VSET(4, e16, m1);
  EXPECT_NO_TRAP(22, "vwmul.vv v4, v8, v12");
}

// Extensions need EEW = SEW/f >= 8
void TEST_CASE6(void) {
  VSET(4, e8, m1);
  EXPECT_TRAP(23, "vsext.vf2 v4, v8");
  VSET(4, e16, m1);
  EXPECT_TRAP(24, "vzext.vf4 v4, v8");
  EXPECT_NO_TRAP(25, "vzext.vf2 v4, v8");
}

int main(void) {
  INIT_CHECK();
  enable_vec();

  asm volatile("la t0, vtrap_handler\n csrw mtvec, t0" ::: "t0");

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  TEST_CASE5();
  TEST_CASE6();

  EXIT_CHECK();
}
