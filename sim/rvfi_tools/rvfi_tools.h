#ifndef RVFI_TOOLS_H
#define RVFI_TOOLS_H

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "riscv-disas.h"
#include "glib.h"

#ifdef RV64
typedef uint64_t rv_xlen_t;
#else
typedef uint32_t rv_xlen_t;
#endif

typedef struct {
    // rvfi_valid is implicit
    uint64_t rvfi_order;
    uint32_t rvfi_insn;
    uint8_t rvfi_trap;
    uint8_t rvfi_halt;
    uint8_t rvfi_intr;
    uint8_t rvfi_mode;
    uint8_t rvfi_ixl;
    uint8_t rvfi_rs1_addr;
    uint8_t rvfi_rs2_addr;
    uint8_t rvfi_rd_addr;
    rv_xlen_t rvfi_rs1_rdata;
    rv_xlen_t rvfi_rs2_rdata;
    rv_xlen_t rvfi_rd_wdata;
    rv_xlen_t rvfi_pc_rdata;
    rv_xlen_t rvfi_pc_wdata;
    rv_xlen_t rvfi_mem_addr;
    uint8_t rvfi_mem_rmask;
    uint8_t rvfi_mem_wmask;
    rv_xlen_t rvfi_mem_rdata;
    rv_xlen_t rvfi_mem_wdata;
} rvfi_trace_t;

typedef struct {
    char function_name[200];
    uint32_t is_watched;
    uint32_t is_function;
    uint32_t times_called;
    // GArray* start_cycles;
    // GArray* end_cycles;
} symbol_info_t;

typedef struct {
    char* function_name;
    uint32_t call_id;
    uint64_t start_cycle;
    uint64_t end_cycle;
    double start_time;
    double end_time;
    // char start_time_string[100];
    // char end_time_string[100];
} call_info_t;

struct rvfi_perf_count_t;

typedef void (*rvfi_tools_counter_cb_t)(struct rvfi_perf_count_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, const struct riscv_opcode* decoded_instruction);

typedef struct rvfi_perf_count_t {
    char name[100];
    uint64_t val;
    rvfi_tools_counter_cb_t update;
} rvfi_performance_counter_t;

typedef struct {
    char* function_name;
    uint32_t start_pc;
    uint32_t ret_pc;
    // uint64_t* counters;
    GArray* counters;
} counter_info_t;

typedef struct {

    char* monitor_prefix;
    char* time_unit_suffix;

    unsigned long march;

    int en_tracer;
    int en_profiler;
    int en_checker;

    char* tracer_log_file_name;
    char* profiler_log_file_name;
    char* profiler_call_graph_file_name;
    char* symbol_table_file_name;
    char* symbol_watchlist_file_name;

    FILE* tracer_log_file;
    FILE* profiler_log_file;
    FILE* profiler_call_graph_file;
    FILE* symbol_table_file;
    FILE* symbol_watchlist_file;

    GHashTable* symbol_table_hash_table;
    GArray* performance_counters;
    GPtrArray* counter_stack;
    GNode* current_call_node;

    // counter_info_t* counter_stack_top;

    int n_counters;

} rvfi_monitor_context;

static const char rv_ireg_name_sym[32][5] = {
    "zero", "ra",   "sp",   "gp",   "tp",   "t0",   "t1",   "t2",
    "s0",   "s1",   "a0",   "a1",   "a2",   "a3",   "a4",   "a5",
    "a6",   "a7",   "s2",   "s3",   "s4",   "s5",   "s6",   "s7",
    "s8",   "s9",   "s10",  "s11",  "t3",   "t4",   "t5",   "t6",
};

#define RVFI_PRINT_TRACE(trace) do {\
    printf("rvfi_order = %d\n", trace.rvfi_order);\
    printf("rvfi_insn = %d\n", trace.rvfi_insn);\
    printf("rvfi_trap = %d\n", trace.rvfi_trap);\
    printf("rvfi_halt = %d\n", trace.rvfi_halt);\
    printf("rvfi_intr = %d\n", trace.rvfi_intr);\
    printf("rvfi_mode = %d\n", trace.rvfi_mode);\
    printf("rvfi_ixl = %d\n", trace.rvfi_ixl);\
    printf("rvfi_rs1_addr = %d\n", trace.rvfi_rs1_addr);\
    printf("rvfi_rs1_addr = %d\n", trace.rvfi_rs2_addr);\
    printf("rvfi_rd_addr = %d\n", trace.rvfi_rd_addr);\
    printf("rvfi_rs1_rdata = %d\n", trace.rvfi_rs1_rdata);\
    printf("rvfi_rs2_rdata = %d\n", trace.rvfi_rs2_rdata);\
    printf("rvfi_rd_wdata = %d\n", trace.rvfi_rd_wdata);\
    printf("rvfi_pc_rdata = %d\n", trace.rvfi_pc_rdata);\
    printf("rvfi_pc_wdata = %d\n", trace.rvfi_pc_wdata);\
    printf("rvfi_mem_addr = %d\n", trace.rvfi_mem_addr);\
    printf("rvfi_mem_rmask = %d\n", trace.rvfi_mem_rmask);\
    printf("rvfi_mem_rmask = %d\n", trace.rvfi_mem_wmask);\
    printf("rvfi_mem_rdata = %d\n", trace.rvfi_mem_rdata);\
    printf("rvfi_mem_wdata = %d\n", trace.rvfi_mem_wdata);\
} while (0)

#endif

rvfi_monitor_context* rvfi_monitor_init(char* monitor_prefix, char* time_unit_suffix, unsigned long isa, int en_tracer, int en_profiler, int en_checker);
void rvfi_monitor_add_counter(rvfi_monitor_context* ctx, rvfi_performance_counter_t ctr);
void rvfi_monitor_add_default_performance_counters(rvfi_monitor_context* ctx);
void rvfi_monitor_push_counters_to_stack(rvfi_monitor_context *ctx, symbol_info_t *current_symbol, const rvfi_trace_t *rvfi_trace);
void rvfi_monitor_step(rvfi_monitor_context* ctx, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, char* time_string, double time_float);
void rvfi_monitor_final(rvfi_monitor_context* ctx);

void rvfi_monitor_print_call_graph(rvfi_monitor_context* ctx, GNode* call_node, int indent_level);
void _debug_hash_table_iterator(gpointer key, gpointer value, gpointer user_data);
