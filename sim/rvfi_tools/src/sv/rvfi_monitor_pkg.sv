package rvfi_monitor_pkg;

// SV equivalent of
// typedef struct {
//     uint64_t rvfi_order;
//     rv_ilen_t rvfi_insn;
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
//     rv_xlen_t rvfi_pc_rdata;
//     rv_xlen_t rvfi_pc_wdata;
//     rv_xlen_t rvfi_mem_addr;
//     uint8_t rvfi_mem_rmask;
//     uint8_t rvfi_mem_wmask;
//     rv_xlen_t rvfi_mem_rdata;
//     rv_xlen_t rvfi_mem_wdata;
//     uint8_t rvfi_valid;
// } rvfi_trace_t;
// as defined in rvfi_tools.h

// FIXME: Considering only XLEN = 32 for now
typedef struct {
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
    byte rvfi_valid;
} rvfi_trace_t;

// Equivalent to bfd_march_riscv32 and bfd_march_riscv64
typedef enum longint {
    rv32 = 132,
    rv64 = 164
} rv_isa;

endpackage
