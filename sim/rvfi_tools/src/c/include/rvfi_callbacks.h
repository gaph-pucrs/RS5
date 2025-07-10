#ifndef RVFI_CALLBACKS_H
#define RVFI_CALLBACKS_H

#include "rvfi_tools.h"

void rvfi_tools_perfcount_cb_clock_cycles(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_cmprss_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_unknown_insn_retired(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_stall_cycles(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_arith(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_shift(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_bitwise(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_mult(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_div(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_total_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_fwd_static_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_bwd_static_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_fwd_reg_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_bwd_reg_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_misaligned_jumps(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_total_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_taken_fwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_not_taken_fwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_taken_bwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_not_taken_bwd_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_misaligned_branches(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_total_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_byte_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_halfword_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_misaligned_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_word_loads(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_total_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_byte_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_halfword_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_word_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);
void rvfi_tools_perfcount_cb_misaligned_stores(rvfi_performance_counter_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* op, void* local_ctx);

#endif
