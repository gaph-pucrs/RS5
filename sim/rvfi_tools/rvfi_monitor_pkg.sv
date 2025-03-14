package rvfi_monitor_pkg;

// SV equivalent of
// typedef struct {
//     // rvfi_valid is implicit
//     uint64_t rvfi_order;
//     uint32_t rvfi_insn;
//     uint8_t rvfi_trap;
//     uint8_t rvfi_halt;
//     uint8_t rvfi_intr;
//     uint8_t rvfi_mode;
//     uint8_t rvfi_ixl;
//     uint8_t rvfi_rs1_addr;
//     uint8_t rvfi_rs2_addr;
//     uint8_t rvfi_rd_addr;
//     rv_xlen_t rvfi_rs1_rdata;
//     rv_xlen_t rvfi_rs2_rdata;
//     rv_xlen_t rvfi_rd_wdata;
//     uint32_t rvfi_pc_rdata;
//     uint32_t rvfi_pc_wdata;
//     uint32_t rvfi_mem_addr;
//     uint8_t rvfi_mem_rmask;
//     uint8_t rvfi_mem_wmask;
//     rv_xlen_t rvfi_mem_rdata;
//     rv_xlen_t rvfi_mem_wdata;
// } rvfi_trace_t;
// as defined in rvfi_tools.h

// FIXME: Considering only XLEN = 32 for now
typedef struct {
// rvfi_valid is implicit
    longint rvfi_order;
    int rvfi_insn;
    byte rvfi_trap;
    byte rvfi_halt;
    byte rvfi_intr;
    byte rvfi_mode;
    byte rvfi_ixl;
    byte rvfi_rs1_addr;
    byte rvfi_rs2_addr;
    byte rvfi_rd_addr;
    int rvfi_rs1_rdata;
    int rvfi_rs2_rdata;
    int rvfi_rd_wdata;
    int rvfi_pc_rdata;
    int rvfi_pc_wdata;
    int rvfi_mem_addr;
    byte rvfi_mem_rmask;
    byte rvfi_mem_wmask;
    int rvfi_mem_rdata;
    int rvfi_mem_wdata;
} rvfi_trace_t;

typedef enum int {
    rv32,
    rv64,
    rv128
} rv_isa;

typedef struct {
    string function_name;
    int start_pc;
    int ret_pc;
    chandle counters;
} counter_info_t;

typedef struct {

    rv_isa isa;

    int en_tracer;
    int en_profiler;
    int en_checker;

    string tracer_log_file_name;
    string profiler_log_file_name;
    string symbol_table_file_name;
    string symbol_watchlist_file_name;

    chandle tracer_log_file;
    chandle profiler_log_file;
    chandle symbol_table_file;
    chandle symbol_watchlist_file;

    chandle symbol_table_hash_table;
    chandle performance_counters;
    chandle counter_stack;

    counter_info_t last_counter_state;

} rvfi_monitor_context;

endpackage
