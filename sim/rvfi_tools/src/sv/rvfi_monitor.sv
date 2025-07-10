import rvfi_monitor_pkg::*;

module rvfi_monitor #(
    parameter string MONITOR_PREFIX = "rvfi_monitor",
    parameter int MAX_RETIRE = 1,
    parameter string TIME_UNIT = "ns",
    parameter rv_isa ISA = rv32,
    parameter int ENABLE_TRACER = 1'b1,
    parameter int ENABLE_PROFILER = 1'b1,
    parameter int ENABLE_CHECKER = 1'b0
) (

    input logic rvfi_ext_clk,
    input logic rvfi_ext_reset_n,

    input logic       rvfi_valid[MAX_RETIRE],
    input logic[63:0] rvfi_order[MAX_RETIRE],
    input logic[31:0] rvfi_insn[MAX_RETIRE],
    input logic       rvfi_trap[MAX_RETIRE],
    input logic       rvfi_halt[MAX_RETIRE],
    input logic       rvfi_intr[MAX_RETIRE],
    input logic[ 1:0] rvfi_mode[MAX_RETIRE],
    input logic[ 1:0] rvfi_ixl[MAX_RETIRE],
    input logic[ 4:0] rvfi_rs1_addr[MAX_RETIRE],
    input logic[ 4:0] rvfi_rs2_addr[MAX_RETIRE],
    input logic[31:0] rvfi_rs1_rdata[MAX_RETIRE],
    input logic[31:0] rvfi_rs2_rdata[MAX_RETIRE],
    input logic[ 4:0] rvfi_rd_addr[MAX_RETIRE],
    input logic[31:0] rvfi_rd_wdata[MAX_RETIRE],
    input logic[31:0] rvfi_pc_rdata[MAX_RETIRE],
    input logic[31:0] rvfi_pc_wdata[MAX_RETIRE],
    input logic[31:0] rvfi_mem_addr[MAX_RETIRE],
    input logic[ 3:0] rvfi_mem_rmask[MAX_RETIRE],
    input logic[ 3:0] rvfi_mem_wmask[MAX_RETIRE],
    input logic[31:0] rvfi_mem_rdata[MAX_RETIRE],
    input logic[31:0] rvfi_mem_wdata[MAX_RETIRE]

);

    int time_unit_lut[string] = '{"s": 0, "ms": -3, "us": -6, "ns": -9, "ps": -12, "fs":-15};

    chandle ctx;

    import "DPI" function chandle rvfi_monitor_init(string monitor_prefix, string elf_file_name, string watchlist_file_name, string output_dir, string time_unit, longint march, int max_retire, int en_tracer, int en_profiler, int en_checker);
    import "DPI" function void rvfi_monitor_add_default_performance_counters(chandle ctx);
    // import "DPI" function void rvfi_monitor_step(chandle ctx, rvfi_trace_t rvfi_trace, longint current_clock_cycle, string time_string, real time_float);
    import "DPI" function void rvfi_monitor_step(chandle ctx, rvfi_trace_t rvfi_trace_array[MAX_RETIRE], longint current_clock_cycle, string time_string, real time_float);
    import "DPI" function void rvfi_monitor_final(chandle ctx);

    longint cycle_counter;

    always_ff @(posedge rvfi_ext_clk or negedge rvfi_ext_reset_n) begin

        if (!rvfi_ext_reset_n)
            cycle_counter <= 0;

        else
            cycle_counter <= cycle_counter + 1;

    end

    initial begin

        string time_string;
        realtime time_float;

        string elf_file_name;
        string watchlist_file_name;
        string output_dir;

        elf_file_name = {MONITOR_PREFIX, "_profiler_elf.elf"};
        $value$plusargs({MONITOR_PREFIX, "_profiler_elf_file_name=%s"}, elf_file_name);
        $display("Monitor <%s> ELF file is <%s>", MONITOR_PREFIX, elf_file_name);

        watchlist_file_name = {MONITOR_PREFIX, "_profiler_watchlist.txt"};
        // watchlist_file_name = "";
        $value$plusargs({MONITOR_PREFIX, "_profiler_watchlist_file_name=%s"}, watchlist_file_name);

        if (watchlist_file_name == "")
            $display("Monitor <%s> was not provided a watchlist file, call graph will be generated considering all functions in the input ELF file <%s> symbol table", MONITOR_PREFIX, elf_file_name);
        else
            $display("Monitor <%s> symbol watchlist file is <%s>", MONITOR_PREFIX, watchlist_file_name);

        output_dir = elf_file_name.substr(0, elf_file_name.len()-5);
        $value$plusargs({MONITOR_PREFIX, "_output_dir=%s"}, output_dir);
        $display("Monitor <%s> output directory is <%s>", MONITOR_PREFIX, output_dir);

        // Create out dir if it doesnt exist
        $system($sformatf("mkdir -p %s", output_dir));

        $timeformat(time_unit_lut[TIME_UNIT], 3, TIME_UNIT, 0);

        ctx = rvfi_monitor_init(MONITOR_PREFIX, elf_file_name, watchlist_file_name, output_dir, TIME_UNIT, ISA, MAX_RETIRE, ENABLE_TRACER, ENABLE_PROFILER, ENABLE_CHECKER);
        rvfi_monitor_add_default_performance_counters(ctx);

        forever begin

            @(posedge rvfi_ext_clk);

            if (rvfi_valid != '{default: '0}) begin

                // rvfi_trace_t rvfi_trace;
                rvfi_trace_t rvfi_trace_array[MAX_RETIRE];

                for (int i = 0; i < MAX_RETIRE; i++)
                    rvfi_trace_array[i] = '{
                        rvfi_valid:rvfi_valid[i],
                        rvfi_order:rvfi_order[i],
                        rvfi_insn:rvfi_insn[i],
                        rvfi_trap:rvfi_trap[i],
                        rvfi_halt:rvfi_halt[i],
                        rvfi_intr:rvfi_intr[i],
                        rvfi_mode:rvfi_mode[i],
                        rvfi_ixl:rvfi_ixl[i],
                        rvfi_rs1_addr:rvfi_rs1_addr[i],
                        rvfi_rs2_addr:rvfi_rs2_addr[i],
                        rvfi_rd_addr:rvfi_rd_addr[i],
                        rvfi_rs1_rdata:rvfi_rs1_rdata[i],
                        rvfi_rs2_rdata:rvfi_rs2_rdata[i],
                        rvfi_rd_wdata:rvfi_rd_wdata[i],
                        rvfi_pc_rdata:rvfi_pc_rdata[i],
                        rvfi_pc_wdata:rvfi_pc_wdata[i],
                        rvfi_mem_addr:rvfi_mem_addr[i],
                        rvfi_mem_rmask:rvfi_mem_rmask[i],
                        rvfi_mem_wmask:rvfi_mem_wmask[i],
                        rvfi_mem_rdata:rvfi_mem_rdata[i],
                        rvfi_mem_wdata:rvfi_mem_wdata[i]
                    };

                time_string = $sformatf("%t", $realtime);
                time_float = $realtime;

                // rvfi_monitor_step(ctx, rvfi_trace, cycle_counter, time_string, time_float);
                rvfi_monitor_step(ctx, rvfi_trace_array, cycle_counter, time_string, time_float);

            end

        end

    end

    final begin
        rvfi_monitor_final(ctx);
    end

endmodule
