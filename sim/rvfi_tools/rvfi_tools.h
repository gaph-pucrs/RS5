#ifndef RVFI_TOOLS_H
#define RVFI_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "riscv-disas.h"
// #include "uthash.h"
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
    uint32_t rvfi_pc_rdata;
    uint32_t rvfi_pc_wdata;
    uint32_t rvfi_mem_addr;
    uint8_t rvfi_mem_rmask;
    uint8_t rvfi_mem_wmask;
    rv_xlen_t rvfi_mem_rdata;
    rv_xlen_t rvfi_mem_wdata;
} rvfi_trace_t;

typedef struct {
    uint32_t is_watched;
    uint32_t is_function;
    uint32_t times_called;
    // uint32_t* start_cycles;
    GArray* start_cycles;
    // uint32_t* end_cycles;
    GArray* end_cycles;
    // uint32_t key;  // PC of the first instruction
    char function_name[200];
} symbol_info_t;

struct rvfi_perf_count_t;

typedef void (*rvfi_tools_counter_cb_t)(struct rvfi_perf_count_t* self, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle, rv_decode decoded_instruction);

typedef struct rvfi_perf_count_t {
    char name[100];
    uint64_t val;
    rvfi_tools_counter_cb_t update;
} rvfi_performance_counter_t;

typedef struct {
    char* function_name;
    uint32_t start_pc;
    uint32_t ret_pc;
    uint64_t* counters;
} counter_info_t;

// From riscv-dis.c

typedef struct {
    const int op;
    const rvc_constraint *constraints;
} rv_comp_data;

typedef struct {
    const char * const name;
    const rv_codec codec;
    const char * const format;
    const rv_comp_data *pseudo;
    const short decomp_rv32;
    const short decomp_rv64;
    const short decomp_rv128;
    const short decomp_data;
} rv_opcode_data;

extern rv_opcode_data *opcode_data;
// extern char rv_ireg_name_sym[32][5];
static const char rv_ireg_name_sym[32][5] = {
    "zero", "ra",   "sp",   "gp",   "tp",   "t0",   "t1",   "t2",
    "s0",   "s1",   "a0",   "a1",   "a2",   "a3",   "a4",   "a5",
    "a6",   "a7",   "s2",   "s3",   "s4",   "s5",   "s6",   "s7",
    "s8",   "s9",   "s10",  "s11",  "t3",   "t4",   "t5",   "t6",
};

// #if !defined(DISASSEMBLY_BACKEND)
// #define DISASSEMBLY_BACKEND RISCV_DIS
// #endif

// #if DISASSEMBLY_BACKEND == RISCV_DIS

// #define MATCH_MEM_INSN(op)
//     switch (op) {\
//         case rv_op_lb:\
//         case rv_op_lh:\
//         case rv_op_lw:\
//         case rv_op_lbu:\
//         case rv_op_lhu:\
//         case rv_op_sb:\
//         case rv_op_sh:\
//         case rv_op_sw:\
//         case rv_op_lwu:\
//         case rv_op_ld:\
//         case rv_op_sd:\
//         case rv_op_ldu:\
//         case rv_op_lq:\
//         case rv_op_sq:\
//         case rv_op_c_fld:\
//         case rv_op_c_lw:\
//         case rv_op_c_flw:\
//         case rv_op_c_fsd:\
//         case rv_op_c_sw:\
//         case rv_op_c_fsw:\
//         case rv_op_c_fldsp:\
//         case rv_op_c_lwsp:\
//         case rv_op_c_flwsp:\
//         case rv_op_c_fsdsp:\
//         case rv_op_c_swsp:\
//         case rv_op_c_fswsp:\
//         case rv_op_c_ld:\
//         case rv_op_c_sd:\
//         case rv_op_c_ldsp:\
//         case rv_op_c_sdsp:\
//         case rv_op_c_lq:\
//         case rv_op_c_sq:\
//         case rv_op_c_lqsp:\
//         case rv_op_c_sqsp:

// #endif

    // uint64_t rvfi_order;
    // uint32_t rvfi_insn;
    // uint8_t rvfi_trap;
    // uint8_t rvfi_halt;
    // uint8_t rvfi_intr;
    // uint8_t rvfi_mode;
    // uint8_t rvfi_ixl;
    // uint8_t rvfi_rs1_addr;
    // uint8_t rvfi_rs2_addr;
    // uint8_t rvfi_rd_addr;
    // rv_xlen_t rvfi_rs1_rdata;
    // rv_xlen_t rvfi_rs2_rdata;
    // rv_xlen_t rvfi_rd_wdata;
    // uint32_t rvfi_pc_rdata;
    // uint32_t rvfi_pc_wdata;
    // uint32_t rvfi_mem_addr;
    // uint8_t rvfi_mem_rmask;
    // uint8_t rvfi_mem_wmask;
    // rv_xlen_t rvfi_mem_rdata;
    // rv_xlen_t rvfi_mem_wdata;

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
