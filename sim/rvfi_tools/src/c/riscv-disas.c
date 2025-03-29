#include "riscv-disas.h"

#include <dis-asm.h>


int dis_fprintf_styled(void *stream, enum disassembler_style style, const char *fmt, ...) {
  stream_state* ss = (stream_state *)stream;

  va_list arg;
  va_start(arg, fmt);
  if (!ss->reenter) {
    vasprintf(&ss->insn_buffer, fmt, arg);
    asprintf(&ss->insn_buffer, "%-6s", ss->insn_buffer);
    ss->reenter = true;
  } else {
    char *tmp;
    vasprintf(&tmp, fmt, arg);

    char *tmp2;
    asprintf(&tmp2, "%s%s", ss->insn_buffer, tmp);
    free(ss->insn_buffer);
    free(tmp);
    ss->insn_buffer = tmp2;
  }
  va_end(arg);

  return 0;
}

void print_address (bfd_vma vma, disassemble_info *inf) {
  dis_fprintf_styled(inf->stream, dis_style_address, "0x%x", vma);
}

void disassemble_to_string(disassemble_info* disasm_info, uint8_t* input_buffer, char* out_buf, uint64_t pc) {

    stream_state* ss = (stream_state *)(disasm_info->stream);
    disasm_info->buffer = input_buffer;
    disasm_info->buffer_vma = pc;
    disasm_info->buffer_length = 4;

    disassemble_init_for_target(disasm_info);

    disassembler_ftype disasm;
    disasm = disassembler(bfd_arch_riscv, false, bfd_mach_riscv32, NULL);

    size_t insn_size = disasm(pc, disasm_info);

    sprintf(out_buf, "%s", ss->insn_buffer);
    free(ss->insn_buffer);

}

void init_hashtable() {
  const struct riscv_opcode *op;
  for (op = riscv_opcodes; op->name; op++)
    if (!riscv_hash[OP_HASH_IDX (op->match)])
      riscv_hash[OP_HASH_IDX (op->match)] = op;
}

const struct riscv_opcode* disasm_inst(char *buf, size_t buflen, disassemble_info* disasm_info, uint64_t pc, insn_t inst) {

  const struct riscv_opcode *op = riscv_hash[OP_HASH_IDX (inst)];

  for (; op->name; op++)
	{
	  if (op->pinfo == INSN_MACRO)
	    continue;
	  if (!op->match_func(op, inst))
	    continue;

    break;
  }

  uint8_t inst_buf[4] = {0};

  *(uint32_t *)inst_buf = inst;

  disassemble_to_string(disasm_info, inst_buf, buf, pc);

  return op;
}

int get_symtab (bfd *abfd, asymbol** symtab) {
  int symcount = 0;
  if (!(bfd_get_file_flags(abfd) & HAS_SYMS))
    return NULL;


  symcount = bfd_canonicalize_symtab (abfd, symtab);
  if (symcount < 0)
    {
      free (symtab);
      symtab = NULL;
      symcount = 0;
    }
  return symcount;
}

