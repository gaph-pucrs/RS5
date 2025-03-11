#include "rvfi_callbacks.h"

void rvfi_tools_perfcount_cb_clock_cycles(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    static uint64_t running_clock_cycle_count = 0;

    self->val += (current_clock_cycle - running_clock_cycle_count);
    running_clock_cycle_count = current_clock_cycle;

}

// TODO: Consider machines capable of retiring multiple instruction per cycle
void rvfi_tools_perfcount_cb_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {
    self->val += 1;
}

void rvfi_tools_perfcount_cb_cmprss_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {
    if ((decoded_instruction.inst & 0x3) != 0x3)
        self->val += 1;
}

void rvfi_tools_perfcount_cb_unkwown_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {
    if (decoded_instruction.op == rv_op_illegal)
        self->val += 1;
}

// TODO: Consider WFI instruction and multicycle instructions
void rvfi_tools_perfcount_cb_stall_cycles(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    static uint64_t last_clock_cycle = 0;

    self->val += current_clock_cycle - last_clock_cycle - 1;
    last_clock_cycle = current_clock_cycle;

}

// These are instructions than generally re-use the same ALU adder (add, sub and set-less-than)
void rvfi_tools_perfcount_cb_arith(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_auipc:
        case rv_op_add:
        case rv_op_sub:
        case rv_op_addi:
        case rv_op_addw:
        case rv_op_subw:
        case rv_op_addiw:
        case rv_op_addd:
        case rv_op_subd:
        case rv_op_addid:
        case rv_op_slt:
        case rv_op_sltu:
        case rv_op_slti:
        case rv_op_sltiu:
        case rv_op_c_add:
        case rv_op_c_sub:
        case rv_op_c_addi:
        case rv_op_c_addiw:
        case rv_op_c_addi16sp:
        case rv_op_c_addi4spn:
        case rv_op_amoadd_w:
        case rv_op_amomin_w:
        case rv_op_amomax_w:
        case rv_op_amominu_w:
        case rv_op_amomaxu_w:
        case rv_op_amoadd_d:
        case rv_op_amomin_d:
        case rv_op_amomax_d:
        case rv_op_amominu_d:
        case rv_op_amomaxu_d:
        case rv_op_amoadd_q:
        case rv_op_amomin_q:
        case rv_op_amomax_q:
        case rv_op_amominu_q:
        case rv_op_amomaxu_q:
            self->val += 1;

        default:
            break;
    }

}

// Shifts/rotates
void rvfi_tools_perfcount_cb_shift(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_slli:
        case rv_op_srli:
        case rv_op_srai:
        case rv_op_sll:
        case rv_op_srl:
        case rv_op_sra:
        // FIXME: Michael Clark's disassembler does not support bitmanip rotates (ror/rori)
        // case rv_op_ror:
        // case rv_op_rori:
            self->val += 1;

        default:
            break;
    }

}

// Bitwise logical ops
void rvfi_tools_perfcount_cb_bitwise(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_and:
        case rv_op_andi:
        case rv_op_or:
        case rv_op_ori:
        case rv_op_xor:
        case rv_op_xori:
        case rv_op_not:
        case rv_op_c_andi:
        case rv_op_c_or:
        case rv_op_c_xor:
        case rv_op_amoxor_w:
        case rv_op_amoor_w:
        case rv_op_amoand_w:
        case rv_op_amoxor_d:
        case rv_op_amoor_d:
        case rv_op_amoand_d:
        case rv_op_amoxor_q:
        case rv_op_amoor_q:
        case rv_op_amoand_q:
        // FIXME: Michael Clark's disassembler does not support bitmanip bitwise with negated operand (andn/orn/xnor)
        // case rv_op_andn:
        // case rv_op_orn:
        // case rv_op_xnor:
            self->val += 1;

        default:
            break;
    }

}

// Multiplications
void rvfi_tools_perfcount_cb_mult(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_mul:
        case rv_op_mulh:
        case rv_op_mulhsu:
        case rv_op_mulhu:
        case rv_op_mulw:
        case rv_op_muld:
            self->val += 1;

        default:
            break;
    }

}

// Divisions/remainer
void rvfi_tools_perfcount_cb_div(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_div:
        case rv_op_divu:
        case rv_op_rem:
        case rv_op_remu:
        case rv_op_divw:
        case rv_op_divuw:
        case rv_op_remw:
        case rv_op_remuw:
        case rv_op_divd:
        case rv_op_divud:
        case rv_op_remd:
        case rv_op_remud:
            self->val += 1;

        default:
            break;
    }
}

void rvfi_tools_perfcount_cb_fwd_static_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_j:
        case rv_op_jal:
        case rv_op_c_jal:
        case rv_op_c_j:
            if (rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_bwd_static_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_j:
        case rv_op_jal:
        case rv_op_c_jal:
        case rv_op_c_j:
            if (rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_fwd_reg_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_jr:
        case rv_op_ret:
        case rv_op_jalr:
        case rv_op_c_jalr:
        case rv_op_c_jr:
            if (rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_bwd_reg_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_jr:
        case rv_op_ret:
        case rv_op_jalr:
        case rv_op_c_jalr:
        case rv_op_c_jr:
            if (rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_taken_fwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

// size_t inst_length(rv_inst inst);
    switch (op) {
        case rv_op_beq:
        case rv_op_bne:
        case rv_op_blt:
        case rv_op_bge:
        case rv_op_bltu:
        case rv_op_bgeu:
        case rv_op_beqz:
        case rv_op_bnez:
        case rv_op_blez:
        case rv_op_bgez:
        case rv_op_bltz:
        case rv_op_bgtz:
        case rv_op_ble:
        case rv_op_bleu:
        case rv_op_bgt:
        case rv_op_bgtu:
        case rv_op_c_beqz:
        case rv_op_c_bnez:
            if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + inst_length((rv_inst) rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_taken_bwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_beq:
        case rv_op_bne:
        case rv_op_blt:
        case rv_op_bge:
        case rv_op_bltu:
        case rv_op_bgeu:
        case rv_op_beqz:
        case rv_op_bnez:
        case rv_op_blez:
        case rv_op_bgez:
        case rv_op_bltz:
        case rv_op_bgtz:
        case rv_op_ble:
        case rv_op_bleu:
        case rv_op_bgt:
        case rv_op_bgtu:
        case rv_op_c_beqz:
        case rv_op_c_bnez:
            if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + inst_length((rv_inst) rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;

        default:
            break;
    }

}

void rvfi_tools_perfcount_cb_not_taken_fwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_beq:
        case rv_op_bne:
        case rv_op_blt:
        case rv_op_bge:
        case rv_op_bltu:
        case rv_op_bgeu:
        case rv_op_beqz:
        case rv_op_bnez:
        case rv_op_blez:
        case rv_op_bgez:
        case rv_op_bltz:
        case rv_op_bgtz:
        case rv_op_ble:
        case rv_op_bleu:
        case rv_op_bgt:
        case rv_op_bgtu:
        case rv_op_c_beqz:
        case rv_op_c_bnez:
            if (rvfi_trace->rvfi_pc_wdata == (rvfi_trace->rvfi_pc_rdata + inst_length((rv_inst) rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata > rvfi_trace->rvfi_pc_rdata)
                self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_not_taken_bwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    switch (op) {
        case rv_op_beq:
        case rv_op_bne:
        case rv_op_blt:
        case rv_op_bge:
        case rv_op_bltu:
        case rv_op_bgeu:
        case rv_op_beqz:
        case rv_op_bnez:
        case rv_op_blez:
        case rv_op_bgez:
        case rv_op_bltz:
        case rv_op_bgtz:
        case rv_op_ble:
        case rv_op_bleu:
        case rv_op_bgt:
        case rv_op_bgtu:
        case rv_op_c_beqz:
        case rv_op_c_bnez:
            if (rvfi_trace->rvfi_pc_wdata == (rvfi_trace->rvfi_pc_rdata + inst_length((rv_inst) rvfi_trace->rvfi_pc_rdata)) && rvfi_trace->rvfi_pc_wdata < rvfi_trace->rvfi_pc_rdata)
                self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_byte_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    // TODO: AMO conditional load/store
    switch (op) {
        case rv_op_lb:
        case rv_op_lbu:
            self->val += 1;

    }

}

void rvfi_tools_perfcount_cb_halfword_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    // TODO: AMO conditional load/store
    switch (op) {
        case rv_op_lh:
        case rv_op_lhu:
            self->val += 1;

    }

}

void rvfi_tools_perfcount_cb_word_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    // TODO: AMO conditional load/store
    switch (op) {
        case rv_op_lw:
        case rv_op_lwu:
        case rv_op_c_lw:
        case rv_op_c_flw:
        case rv_op_c_fldsp:
        case rv_op_c_lwsp:
        case rv_op_c_flwsp:
            self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_byte_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    // TODO: AMO conditional load/store
    switch (op) {
        case rv_op_sb:
            self->val += 1;
    }
}

void rvfi_tools_perfcount_cb_halfword_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    // TODO: AMO conditional load/store
    switch (op) {
        case rv_op_sh:
            self->val += 1;
    }

}

void rvfi_tools_perfcount_cb_word_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction) {

    rv_op op = (rv_op) decoded_instruction.op;

    // TODO: AMO conditional load/store
    switch (op) {
        case rv_op_sw:
        case rv_op_c_sw:
        case rv_op_c_fsw:
        case rv_op_c_swsp:
        case rv_op_c_fswsp:
            self->val += 1;

    }
}
