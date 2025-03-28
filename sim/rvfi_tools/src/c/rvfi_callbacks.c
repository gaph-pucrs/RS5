#include "rvfi_callbacks.h"

void rvfi_tools_perfcount_cb_clock_cycles(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* decoded_instruction) {

    static uint64_t running_clock_cycle_count = 0;

    self->val += (current_clock_cycle - running_clock_cycle_count);
    running_clock_cycle_count = current_clock_cycle;

}

// TODO: Consider machines capable of retiring multiple instruction per cycle
void rvfi_tools_perfcount_cb_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* decoded_instruction) {
    self->val += 1;
}

void rvfi_tools_perfcount_cb_cmprss_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* decoded_instruction) {
    if (decoded_instruction->insn_class == INSN_CLASS_C)
        self->val += 1;
}

void rvfi_tools_perfcount_cb_unkwown_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* decoded_instruction) {
    if (decoded_instruction->match == 0 && decoded_instruction->mask == 0) 
        self->val += 1;
}

// TODO: Consider WFI instruction and multicycle instructions
void rvfi_tools_perfcount_cb_stall_cycles(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* decoded_instruction) {

    static uint64_t last_clock_cycle = 0;

    self->val += current_clock_cycle - last_clock_cycle - 1;
    last_clock_cycle = current_clock_cycle;

}

// These are instructions than generally re-use the same ALU adder (add, sub and set-less-than)
void rvfi_tools_perfcount_cb_arith(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_AUIPC:
        case MATCH_ADD:
        case MATCH_SUB:
        case MATCH_ADDI:
        case MATCH_ADDW:
        case MATCH_SUBW:
        case MATCH_ADDIW:
        case MATCH_SLT:
        case MATCH_SLTU:
        case MATCH_SLTI:
        case MATCH_SLTIU:
        case MATCH_C_ADD:
        case MATCH_C_SUB:
        case MATCH_C_ADDI:
        case MATCH_C_ADDIW:
        case MATCH_C_ADDI16SP:
        case MATCH_C_ADDI4SPN:
        case MATCH_AMOADD_W:
        case MATCH_AMOMIN_W:
        case MATCH_AMOMAX_W:
        case MATCH_AMOMINU_W:
        case MATCH_AMOMAXU_W:
        case MATCH_AMOADD_D:
        case MATCH_AMOMIN_D:
        case MATCH_AMOMAX_D:
        case MATCH_AMOMINU_D:
        case MATCH_AMOMAXU_D:
            self->val += 1;

        default:
            break;
    }

}

// Shifts/rotates
void rvfi_tools_perfcount_cb_shift(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_SLLI:
        case MATCH_SRLI:
        case MATCH_SRAI:
        case MATCH_SLL:
        case MATCH_SRL:
        case MATCH_SRA:
        case MATCH_ROR:
        case MATCH_RORI:
            self->val += 1;

        default:
            break;
    }

}

// Bitwise logical ops
void rvfi_tools_perfcount_cb_bitwise(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_AND:
        case MATCH_ANDI:
        case MATCH_OR:
        case MATCH_ORI:
        case MATCH_XOR:
        case MATCH_XORI:
        case MATCH_C_NOT:
        case MATCH_C_ANDI:
        case MATCH_C_OR:
        case MATCH_C_XOR:
        case MATCH_AMOXOR_W:
        case MATCH_AMOOR_W:
        case MATCH_AMOAND_W:
        case MATCH_AMOXOR_D:
        case MATCH_AMOOR_D:
        case MATCH_AMOAND_D:
        case MATCH_ANDN:
        case MATCH_ORN:
        case MATCH_XNOR:
            self->val += 1;

        default:
            break;
    }

}

// Multiplications
void rvfi_tools_perfcount_cb_mult(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_MUL:
        case MATCH_MULH:
        case MATCH_MULHSU:
        case MATCH_MULHU:
        case MATCH_MULW:
            self->val += 1;

        default:
            break;
    }

}

// Divisions/remainer
void rvfi_tools_perfcount_cb_div(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_DIV:
        case MATCH_DIVU:
        case MATCH_REM:
        case MATCH_REMU:
        case MATCH_DIVW:
        case MATCH_DIVUW:
        case MATCH_REMW:
        case MATCH_REMUW:
            self->val += 1;

        default:
            break;
    }
}

void rvfi_tools_perfcount_cb_fwd_static_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_JAL:
        case MATCH_C_JAL:
        case MATCH_C_J:
            if (rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_bwd_static_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_JAL:
        case MATCH_C_JAL:
        case MATCH_C_J:
            if (rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_fwd_reg_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_JALR:
        case MATCH_C_JALR:
        case MATCH_C_JR:
            if (rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_bwd_reg_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_JALR:
        case MATCH_C_JALR:
        case MATCH_C_JR:
            if (rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_taken_fwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

// size_t inst_length(rv_inst inst);
    switch (op->match) {
        case MATCH_BEQ:
        case MATCH_BNE:
        case MATCH_BLT:
        case MATCH_BGE:
        case MATCH_BLTU:
        case MATCH_BGEU:
        case MATCH_C_BEQZ:
        case MATCH_C_BNEZ:
            if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_taken_bwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_BEQ:
        case MATCH_BNE:
        case MATCH_BLT:
        case MATCH_BGE:
        case MATCH_BLTU:
        case MATCH_BGEU:
        case MATCH_C_BEQZ:
        case MATCH_C_BNEZ:
            if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_not_taken_fwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_BEQ:
        case MATCH_BNE:
        case MATCH_BLT:
        case MATCH_BGE:
        case MATCH_BLTU:
        case MATCH_BGEU:
        case MATCH_C_BEQZ:
        case MATCH_C_BNEZ:
            if (rvfi_trace->rvfi_pc_wdata == (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_not_taken_bwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    switch (op->match) {
        case MATCH_BEQ:
        case MATCH_BNE:
        case MATCH_BLT:
        case MATCH_BGE:
        case MATCH_BLTU:
        case MATCH_BGEU:
        case MATCH_C_BEQZ:
        case MATCH_C_BNEZ:
            if (rvfi_trace->rvfi_pc_wdata == (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_byte_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    // TODO: AMO conditional load/store
    switch (op->match) {
        case MATCH_LB:
        case MATCH_LBU:
            self->val += 1;

    }

}

void rvfi_tools_perfcount_cb_halfword_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    // TODO: AMO conditional load/store
    switch (op->match) {
        case MATCH_LH:
        case MATCH_LHU:
            self->val += 1;

    }

}

void rvfi_tools_perfcount_cb_word_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    // TODO: AMO conditional load/store
    switch (op->match) {
        case MATCH_LW:
        case MATCH_LWU:
        case MATCH_C_LW:
        case MATCH_C_FLW:
        case MATCH_C_FLDSP:
        case MATCH_C_LWSP:
        case MATCH_C_FLWSP:
            self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_byte_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    // TODO: AMO conditional load/store
    switch (op->match) {
        case MATCH_SB:
            self->val += 1;
    }
}

void rvfi_tools_perfcount_cb_halfword_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    // TODO: AMO conditional load/store
    switch (op->match) {
        case MATCH_SH:
            self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_word_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op) {

    // TODO: AMO conditional load/store
    switch (op->match) {
        case MATCH_SW:
        case MATCH_C_SW:
        case MATCH_C_FSW:
        case MATCH_C_SWSP:
        case MATCH_C_FSWSP:
            self->val += 1;

    }
}
