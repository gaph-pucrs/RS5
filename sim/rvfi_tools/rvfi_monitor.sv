import rvfi_monitor_pkg::*;

module rvfi_monitor #(
    parameter bit ENABLE_TRACER = 1'b1,
    parameter bit ENABLE_PROFILER = 1'b1
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

    int enable_tracer, enable_profiler, enable_checker;
    string tracer_log_file_name, profiler_log_file_name, symbol_table_file_name, symbol_watchlist_file_name;

    import "DPI" function void rvfi_monitor_init(int enable_tracer, int enable_profiler, int enable_checker, string tracer_log_file_name, string profiler_log_file_name, string symbol_table_file_name, string symbol_watchlist_file_name);
    import "DPI" function void rvfi_monitor_step(rvfi_trace_t rvfi_trace, longint current_clock_cycle);
    import "DPI" function void rvfi_monitor_final();

    longint cycle_counter;

    always_ff @(posedge rvfi_ext_clk or negedge rvfi_ext_reset_n) begin

        if (!rvfi_ext_reset_n)
            cycle_counter <= 0;

        else
            cycle_counter <= cycle_counter + 1;

    end

    initial begin

        $timeformat(-9, 2, " ns");

        enable_tracer = 1;

        if ($test$plusargs("RVFI_ENABLE_TRACER"))
            $value$plusargs("RVFI_ENABLE_TRACER=%s", enable_tracer);

        $display("[RVFI_MONITOR] Enable tracer = <%d>", enable_tracer);

        enable_profiler = 1;

        if ($test$plusargs("RVFI_ENABLE_PROFILER"))
            $value$plusargs("RVFI_ENABLE_PROFILER=%s", enable_profiler);

        $display("[RVFI_MONITOR] Enable profiler = <%d>", enable_profiler);

        enable_checker = 0;
        $display("[RVFI_MONITOR] Enable checker = <%d>", enable_checker);

        tracer_log_file_name = "rvfi_tracer_log.txt";

        if ($test$plusargs("RVFI_TRACER_LOG_FILE"))
            $value$plusargs("RVFI_TRACER_LOG_FILE=%s", tracer_log_file_name);

        $display("[RVFI_MONITOR] Writing tracer log to <%s>", tracer_log_file_name);

        profiler_log_file_name = "rvfi_profiler_log.txt";

        if ($test$plusargs("RVFI_PROFILER_LOG_FILE"))
            $value$plusargs("RVFI_PROFILER_LOG_FILE=%s", profiler_log_file_name);

        $display("[RVFI_MONITOR] Writing profiler log to <%s>", profiler_log_file_name);

        symbol_table_file_name = "rvfi_profiler_symbol_table.txt";

        if ($test$plusargs("RVFI_PROFILER_SYMBOL_LIST_FILE"))
            $value$plusargs("RVFI_PROFILER_SYMBOL_LIST_FILE=%s", symbol_table_file_name);

        $display("[RVFI_MONITOR] Reading symbol list from <%s>", symbol_table_file_name);

        symbol_watchlist_file_name = "rvfi_profiler_watchlist.txt";

        if ($test$plusargs("RVFI_PROFILER_WATCHLIST_FILE"))
            $value$plusargs("RVFI_PROFILER_WATCHLIST_FILE=%s", symbol_watchlist_file_name);

        $display("[RVFI_MONITOR] Reading function watchlist from <%s>", symbol_watchlist_file_name);

        rvfi_monitor_init(enable_tracer, enable_profiler, enable_checker, tracer_log_file_name, profiler_log_file_name, symbol_table_file_name, symbol_watchlist_file_name);

        forever begin

            @(posedge rvfi_ext_clk);

                if (rvfi_valid) begin

                    rvfi_trace_t rvfi_trace;

                    rvfi_trace = '{
                        rvfi_order:0,
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

                    rvfi_monitor_step(rvfi_trace, cycle_counter);

                end

        end

    end

    final begin
        rvfi_monitor_final();
    end

endmodule
