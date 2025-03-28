#ifndef RISCV_DISASSEMBLER_H
#define RISCV_DISASSEMBLER_H

#include "config.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <dis-asm.h>
#include <opcode/riscv.h>

typedef struct aout_symbol
{
  asymbol symbol;
  short addr;
  char other;
  unsigned char type;
} aout_symbol_type;

#define aout_symbol(asymbol) ((aout_symbol_type *)(&(asymbol)->the_bfd))

const struct riscv_opcode* disasm_inst(char *buf, size_t buflen, uint64_t pc, insn_t inst);  // TODO: use ISA as an argument
int get_symtab (bfd *abfd, asymbol** symtab);

#endif