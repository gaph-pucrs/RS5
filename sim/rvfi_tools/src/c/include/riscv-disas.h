#ifndef RISCV_DISASSEMBLER_H
#define RISCV_DISASSEMBLER_H

// config.h from libffd, required for including libbfd headers
#include "config.h" // FIXME: We shouldn't have to include this, find some other way

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

typedef struct {
  char *insn_buffer;
  bool reenter;
} stream_state;

static const struct riscv_opcode *riscv_hash[OP_MASK_OP + 1];

#define OP_HASH_IDX(i) ((i) & (riscv_insn_length (i) == 2 ? 0x3 : OP_MASK_OP))

#define aout_symbol(asymbol) ((aout_symbol_type *)(&(asymbol)->the_bfd))

const struct riscv_opcode* disasm_inst(char *buf, size_t buflen, disassemble_info* disasm_info, uint64_t pc, insn_t inst);  // TODO: use ISA as an argument
int dis_fprintf_styled(void *stream, enum disassembler_style style, const char *fmt, ...) ;
void print_address (bfd_vma vma, disassemble_info *inf);
int get_symtab (bfd *abfd, asymbol** symtab);
void init_hashtable();

#endif