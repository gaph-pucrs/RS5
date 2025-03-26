import rvfi_monitor_pkg::*;

module rvfi_monitor #(
    parameter string MONITOR_PREFIX = "RVFI_MONITOR",
    parameter rv_isa ISA = rv32,
    parameter int ENABLE_TRACER = 1'b1,
    parameter int ENABLE_PROFILER = 1'b1,
    parameter int ENABLE_CHECKER = 1'b1,
    parameter string TRACER_LOG_FILE_NAME = "rvfi_tracer_log.txt",
    parameter string PROFILER_LOG_FILE_NAME = "rvfi_profiler_log.txt",
    parameter string SYMBOL_TABLE_FILE_NAME = "aes128_nist_enc_test.elf",
    parameter string SYMBOL_WATCHLIST_FILE_NAME = "rvfi_profiler_watchlist.txt"
) (

    input logic rvfi_ext_clk,
    input logic rvfi_ext_reset_n,

    input logic       rvfi_valid,
    input logic[63:0] rvfi_order,
    input logic[31:0] rvfi_insn,
    input logic       rvfi_trap,
    input logic       rvfi_halt,
    input logic       rvfi_intr,
    input logic[ 1:0] rvfi_mode,
    input logic[ 1:0] rvfi_ixl,
    input logic[ 4:0] rvfi_rs1_addr,
    input logic[ 4:0] rvfi_rs2_addr,
    input logic[31:0] rvfi_rs1_rdata,
    input logic[31:0] rvfi_rs2_rdata,
    input logic[ 4:0] rvfi_rd_addr,
    input logic[31:0] rvfi_rd_wdata,
    input logic[31:0] rvfi_pc_rdata,
    input logic[31:0] rvfi_pc_wdata,
    input logic[31:0] rvfi_mem_addr,
    input logic[ 3:0] rvfi_mem_rmask,
    input logic[ 3:0] rvfi_mem_wmask,
    input logic[31:0] rvfi_mem_rdata,
    input logic[31:0] rvfi_mem_wdata

);

    chandle ctx;

    import "DPI" function chandle rvfi_monitor_init(string monitor_prefix, longint march, int en_tracer, int en_profiler, int en_checker, string tracer_log_file_name, string profiler_log_file_name, string symbol_table_file_name, string symbol_watchlist_file_name);
    import "DPI" function void rvfi_monitor_add_default_performance_counters(chandle ctx);
    import "DPI" function void rvfi_monitor_step(chandle ctx, rvfi_trace_t rvfi_trace, longint current_clock_cycle);
    import "DPI" function void rvfi_monitor_final(chandle ctx);

    longint cycle_counter;

    always_ff @(posedge rvfi_ext_clk or negedge rvfi_ext_reset_n) begin

        if (!rvfi_ext_reset_n)
            cycle_counter <= 0;

        else
            cycle_counter <= cycle_counter + 1;

    end

    initial begin

        $timeformat(-9, 2, " ns");

        ctx = rvfi_monitor_init(MONITOR_PREFIX, ISA, ENABLE_TRACER, ENABLE_PROFILER, ENABLE_CHECKER, TRACER_LOG_FILE_NAME, PROFILER_LOG_FILE_NAME, SYMBOL_TABLE_FILE_NAME, SYMBOL_WATCHLIST_FILE_NAME);
        rvfi_monitor_add_default_performance_counters(ctx);

        forever begin

            @(posedge rvfi_ext_clk);

            if (rvfi_valid) begin

                rvfi_trace_t rvfi_trace;

                rvfi_trace = '{
                    rvfi_order:rvfi_order,
                    rvfi_insn:rvfi_insn,
                    rvfi_trap:rvfi_trap,
                    rvfi_halt:rvfi_halt,
                    rvfi_intr:rvfi_intr,
                    rvfi_mode:rvfi_mode,
                    rvfi_ixl:rvfi_ixl,
                    rvfi_rs1_addr:rvfi_rs1_addr,
                    rvfi_rs2_addr:rvfi_rs2_addr,
                    rvfi_rd_addr:rvfi_rd_addr,
                    rvfi_rs1_rdata:rvfi_rs1_rdata,
                    rvfi_rs2_rdata:rvfi_rs2_rdata,
                    rvfi_rd_wdata:rvfi_rd_wdata,
                    rvfi_pc_rdata:rvfi_pc_rdata,
                    rvfi_pc_wdata:rvfi_pc_wdata,
                    rvfi_mem_addr:rvfi_mem_addr,
                    rvfi_mem_rmask:rvfi_mem_rmask,
                    rvfi_mem_wmask:rvfi_mem_wmask,
                    rvfi_mem_rdata:rvfi_mem_rdata,
                    rvfi_mem_wdata:rvfi_mem_wdata
                };

                rvfi_monitor_step(ctx, rvfi_trace, cycle_counter);

            end

        end

    end

    final begin
        rvfi_monitor_final(ctx);
    end

endmodule
