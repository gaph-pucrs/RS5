#include <test_utils.h>

#include <sys/asm.h>
#include <stdio.h>
#include <stdint.h>
#include "simple_system_common.h"

#define TEST_RORI(IMM)                                      \
  do {                                                      \
    __asm__ volatile (                                      \
      "mv x28, %1        \n"                                \
      "rori x30, x28, " #IMM " \n"                          \
      "mv %0, x30        \n"                                \
      : "=r"(result)                                        \
      : "r"(value)                                          \
      : "x28", "x30"                                        \
    );                                                      \
    printf("imm = %2d -> result = %08x\n", IMM, result);    \
  } while (0)

int main(void)
{
  int result = 0;
  int value  = 0x12345678;

  puts("Initial value:");
  puthex(value);
  puts("\n");

  // Loop “manual” mas gerado de forma limpa
  for (int i = 0; i < 32; i++)
  {
    switch (i)
    {
      case 0:  TEST_RORI(0); break;
      case 1:  TEST_RORI(1); break;
      case 2:  TEST_RORI(2); break;
      case 3:  TEST_RORI(3); break;
      case 4:  TEST_RORI(4); break;
      case 5:  TEST_RORI(5); break;
      case 6:  TEST_RORI(6); break;
      case 7:  TEST_RORI(7); break;
      case 8:  TEST_RORI(8); break;
      case 9:  TEST_RORI(9); break;
      case 10: TEST_RORI(10); break;
      case 11: TEST_RORI(11); break;
      case 12: TEST_RORI(12); break;
      case 13: TEST_RORI(13); break;
      case 14: TEST_RORI(14); break;
      case 15: TEST_RORI(15); break;
      case 16: TEST_RORI(16); break;
      case 17: TEST_RORI(17); break;
      case 18: TEST_RORI(18); break;
      case 19: TEST_RORI(19); break;
      case 20: TEST_RORI(20); break;
      case 21: TEST_RORI(21); break;
      case 22: TEST_RORI(22); break;
      case 23: TEST_RORI(23); break;
      case 24: TEST_RORI(24); break;
      case 25: TEST_RORI(25); break;
      case 26: TEST_RORI(26); break;
      case 27: TEST_RORI(27); break;
      case 28: TEST_RORI(28); break;
      case 29: TEST_RORI(29); break;
      case 30: TEST_RORI(30); break;
      case 31: TEST_RORI(31); break;
    }
  }

  return 0;
}