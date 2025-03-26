#include "riscv-disas.h"

#include <dis-asm.h>

typedef struct {
  char *insn_buffer;
  bool reenter;
} stream_state;


static int dis_fprintf_styled(void *stream, enum disassembler_style style, const char *fmt, ...) {
  stream_state *ss = (stream_state *)stream;

  va_list arg;
  va_start(arg, fmt);
  if (!ss->reenter) {
    vasprintf(&ss->insn_buffer, fmt, arg);
    asprintf(&ss->insn_buffer, "%s\t", ss->insn_buffer);
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

static void print_address (bfd_vma vma, struct disassemble_info *inf) {
  dis_fprintf_styled(inf->stream, dis_style_address, "0x%x", vma);
}

char* disassemble_to_string(uint8_t *input_buffer, uint64_t pc) {
    char* disassembled = NULL;
    stream_state ss = {};

    disassemble_info disasm_info = {};
    init_disassemble_info(&disasm_info, &ss, NULL, dis_fprintf_styled);
    disasm_info.arch = bfd_arch_riscv;
    disasm_info.mach = bfd_mach_riscv32;
    disasm_info.read_memory_func = buffer_read_memory;
    disasm_info.print_address_func = print_address; 
    disasm_info.buffer = input_buffer;
    disasm_info.buffer_vma = pc;
    disasm_info.buffer_length = 4;
    disassemble_init_for_target(&disasm_info);

    disassembler_ftype disasm;
    disasm = disassembler(bfd_arch_riscv, false, bfd_mach_riscv32, NULL);

    size_t insn_size = disasm(pc, &disasm_info);

    asprintf(&disassembled, "%s", ss.insn_buffer);

    return disassembled;
}

const struct riscv_opcode* disasm_inst(char *buf, size_t buflen, uint64_t pc, insn_t inst) {
  const struct riscv_opcode *op;
  static const struct riscv_opcode *riscv_hash[OP_MASK_OP + 1];
  static bool init = false;

#define OP_HASH_IDX(i) ((i) & (riscv_insn_length (i) == 2 ? 0x3 : OP_MASK_OP))

  if (!init) {
    for (op = riscv_opcodes; op->name; op++)
      if (!riscv_hash[OP_HASH_IDX (op->match)])
        riscv_hash[OP_HASH_IDX (op->match)] = op;
    init = true;
  }

  op = riscv_hash[OP_HASH_IDX (inst)];

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

  strcpy(buf, disassemble_to_string(inst_buf, pc));

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

