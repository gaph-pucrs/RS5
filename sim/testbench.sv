/*!\file testbench.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  October 2023
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Testbench for RS5 simulation.
 *
 * \detailed
 * Testbench for RS5 simulation.de
 */

`include "../rtl/RS5_pkg.sv"

//////////////////////////////////////////////////////////////////////////////
// CPU TESTBENCH
//////////////////////////////////////////////////////////////////////////////

module testbench
    import RS5_pkg::*;
(
);
    timeunit 1ns; timeprecision 1ns;

//////////////////////////////////////////////////////////////////////////////
// PARAMETERS FOR CORE INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    localparam mul_e         MULEXT          = MUL_M;
    localparam atomic_e      AMOEXT          = AMO_A;
    localparam bit           COMPRESSED      = 1'b1;
    localparam bit           USE_XOSVM       = 1'b0;
    localparam bit           USE_ZIHPM       = 1'b1;
    localparam bit           USE_ZKNE        = 1'b1;
    localparam bit           VEnable         = 1'b0;
    localparam int           VLEN            = 256;
    localparam bit           BRANCHPRED      = 1'b1;

`ifndef SYNTH
    // localparam bit           PROFILING       = 1'b1;
    localparam bit           PROFILING       = 1'b0;
    localparam bit           DEBUG           = 1'b0;
    localparam bit           ENABLE_TRACER   = 1'b1;
    localparam bit           ENABLE_PROFILER = 1'b1;
`endif

    localparam int           MEM_WIDTH       = 65_536;
    // localparam string        BIN_FILE        = "../app/riscv-tests/test.bin";
    localparam string        BIN_FILE        = "../app/aes-test/aes128_nist_enc_test.bin";

    localparam int           i_cnt = 1;

///////////////////////////////////////// Clock generator //////////////////////////////

    logic        clk=1;

    always begin
        #5.0 clk <= 0;
        #5.0 clk <= 1;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// RESET CPU ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic reset_n;

    initial begin
        reset_n = 0;                                          // RESET for CPU initialization

        #100 reset_n = 1;                                     // Hold state for 100 ns
    end

//////////////////////////////////////////////////////////////////////////////
// TB SIGNALS
//////////////////////////////////////////////////////////////////////////////

    /* Number of used bits is defined by the memory size */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0]            instruction_address;
    /* verilator lint_on UNUSEDSIGNAL */

    /* RTC is 64 bits but the bus is 32 bits */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [63:0]            data_rtc;
    /* verilator lint_on UNUSEDSIGNAL */

    logic                   interrupt_ack;
    logic [63:0]            mtime;
    logic [31:0]            instruction;
    logic                   enable_ram, enable_rtc, enable_plic, enable_tb;
    logic                   mem_operation_enable;
    logic [31:0]            mem_address, mem_data_read, mem_data_write;
    logic [3:0]             mem_write_enable;
    byte                    char;
    logic [31:0]            data_ram, data_plic, data_tb;
    logic                   enable_tb_r, enable_rtc_r, enable_plic_r;
    logic                   mti, mei;
    logic [31:0]            irq;

    assign irq = {20'h0, mei, 3'h0, mti, 7'h0};

    `ifdef RVFI
    logic                    rvfi_valid;
    logic [63:0]             rvfi_order;
    logic [31:0]             rvfi_insn;
    logic                    rvfi_trap;
    logic                    rvfi_halt;
    logic                    rvfi_intr;
    logic [ 1:0]             rvfi_mode;
    logic [ 1:0]             rvfi_ixl;
    logic [ 4:0]             rvfi_rs1_addr;
    logic [ 4:0]             rvfi_rs2_addr;
    logic [31:0]             rvfi_rs1_rdata;
    logic [31:0]             rvfi_rs2_rdata;
    logic [ 4:0]             rvfi_rd_addr;
    logic [31:0]             rvfi_rd_wdata;
    logic [31:0]             rvfi_pc_rdata;
    logic [31:0]             rvfi_pc_wdata;
    logic [31:0]             rvfi_mem_addr;
    logic [ 3:0]             rvfi_mem_rmask;
    logic [ 3:0]             rvfi_mem_wmask;
    logic [31:0]             rvfi_mem_rdata;
    logic [31:0]             rvfi_mem_wdata;
    `endif


//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (mem_operation_enable) begin
            if (mem_address[31:28] < 4'h2) begin
                enable_ram  = 1'b1;
                enable_rtc  = 1'b0;
                enable_plic = 1'b0;
                enable_tb   = 1'b0;
            end
            else if (mem_address[31:28] < 4'h3) begin
                enable_ram  = 1'b0;
                enable_rtc  = 1'b1;
                enable_plic = 1'b0;
                enable_tb   = 1'b0;
            end
            else if (mem_address[31:28] < 4'h8) begin
                enable_ram  = 1'b0;
                enable_rtc  = 1'b0;
                enable_plic = 1'b1;
                enable_tb   = 1'b0;
            end
            else begin
                enable_ram  = 1'b0;
                enable_rtc  = 1'b0;
                enable_plic = 1'b0;
                enable_tb   = 1'b1;
            end
        end
        else begin
            enable_ram  = 1'b0;
            enable_rtc  = 1'b0;
            enable_plic = 1'b0;
            enable_tb   = 1'b0;
        end
    end

    always_ff @(posedge clk) begin
        enable_tb_r     <= enable_tb;
        enable_rtc_r    <= enable_rtc;
        enable_plic_r   <= enable_plic;
    end

    always_comb begin
        if (enable_tb_r) begin
            mem_data_read = data_tb;
        end
        else if (enable_rtc_r) begin
            mem_data_read = data_rtc[31:0];
        end
        else if (enable_plic_r) begin
            mem_data_read = data_plic;
        end
        else begin
            mem_data_read = data_ram;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CPU
//////////////////////////////////////////////////////////////////////////////

    RS5 #(
    `ifndef SYNTH
	    .DEBUG      (DEBUG          ),
	    .PROFILING  (PROFILING      ),
    `endif
        .Environment(ASIC           ),
        .MULEXT     (MULEXT         ),
        .AMOEXT     (AMOEXT         ),
        .COMPRESSED (COMPRESSED     ),
        .VEnable    (VEnable        ),
        .VLEN       (VLEN           ),
        .XOSVMEnable(USE_XOSVM      ),
        .ZIHPMEnable(USE_ZIHPM      ),
        .ZKNEEnable (USE_ZKNE       ),
        .BRANCHPRED (BRANCHPRED     )
    ) dut (

        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset_i            (1'b0),
        .stall                  (1'b0),

        `ifdef RVFI
        .rvfi_valid(rvfi_valid),
        .rvfi_order(rvfi_order),
        .rvfi_insn(rvfi_insn),
        .rvfi_trap(rvfi_trap),
        .rvfi_halt(rvfi_halt),
        .rvfi_intr(rvfi_intr),
        .rvfi_mode(rvfi_mode),
        .rvfi_ixl(rvfi_ixl),
        .rvfi_rs1_addr(rvfi_rs1_addr),
        .rvfi_rs2_addr(rvfi_rs2_addr),
        .rvfi_rs1_rdata(rvfi_rs1_rdata),
        .rvfi_rs2_rdata(rvfi_rs2_rdata),
        .rvfi_rd_addr(rvfi_rd_addr),
        .rvfi_rd_wdata(rvfi_rd_wdata),
        .rvfi_pc_rdata(rvfi_pc_rdata),
        .rvfi_pc_wdata(rvfi_pc_wdata),
        .rvfi_mem_addr(rvfi_mem_addr),
        .rvfi_mem_rmask(rvfi_mem_rmask),
        .rvfi_mem_wmask(rvfi_mem_wmask),
        .rvfi_mem_rdata(rvfi_mem_rdata),
        .rvfi_mem_wdata(rvfi_mem_wdata),
        `endif

        .instruction_i          (instruction),
        .mem_data_i             (mem_data_read),
        .mtime_i                (mtime),
        .irq_i                  (irq),
        .instruction_address_o  (instruction_address),
        .mem_operation_enable_o (mem_operation_enable),
        .mem_write_enable_o     (mem_write_enable),
        .mem_address_o          (mem_address),
        .mem_data_o             (mem_data_write),
        .interrupt_ack_o        (interrupt_ack)

    );

//////////////////////////////////////////////////////////////////////////////
// RAM
//////////////////////////////////////////////////////////////////////////////

    RAM_mem #(
    `ifndef SYNTH
        .DEBUG     (DEBUG     ),
        .DEBUG_PATH("./debug/"),
    `endif
        .MEM_WIDTH(MEM_WIDTH  ),
        .BIN_FILE (BIN_FILE   )
    ) RAM_MEM (
        .clk        (clk),

        .enA_i      (1'b1),
        .weA_i      (4'h0),
        .addrA_i    (instruction_address[($clog2(MEM_WIDTH) - 1):0]),
        .dataA_i    (32'h00000000),
        .dataA_o    (instruction),

        .enB_i      (enable_ram),
        .weB_i      (mem_write_enable),
        .addrB_i    (mem_address[($clog2(MEM_WIDTH) - 1):0]),
        .dataB_i    (mem_data_write),
        .dataB_o    (data_ram)
    );

//////////////////////////////////////////////////////////////////////////////
// PLIC
//////////////////////////////////////////////////////////////////////////////

    /* Bits depending on connected peripherals */
    /* verilator lint_off UNUSED */
    logic [i_cnt:1] iack_periph;
    /* verilator lint_on UNUSED */

    plic #(
        .i_cnt(i_cnt)
    ) plic1 (
        .clk     (clk),
        .reset_n (reset_n),
        .en_i    (enable_plic),
        .we_i    (mem_write_enable),
        .addr_i  (mem_address[23:0]),
        .data_i  (mem_data_write),
        .data_o  (data_plic),
        .irq_i   ('0),
        .iack_i  (interrupt_ack),
        .iack_o  (iack_periph),
        .irq_o   (mei)
    );

//////////////////////////////////////////////////////////////////////////////
// RTC
//////////////////////////////////////////////////////////////////////////////

    rtc rtc(
        .clk        (clk),
        .reset_n    (reset_n),
        .en_i       (enable_rtc),
        .addr_i     (mem_address[3:0]),
        .we_i       ({4'h0, mem_write_enable}),
        .data_i     ({32'h0, mem_data_write}),
        .data_o     (data_rtc),
        .mti_o      (mti),
        .mtime_o    (mtime)
    );

//////////////////////////////////////////////////////////////////////////////
// Memory Mapped regs
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (enable_tb) begin
            // OUTPUT REG
            if ((mem_address == 32'h80004000 || mem_address == 32'h80001000) && mem_write_enable != '0) begin
                char <= mem_data_write[7:0];
                $write("%c",char);
                $fflush();
            end
            // END REG
            if (mem_address == 32'h80000000 && mem_write_enable != '0) begin
                $display("# %t END OF SIMULATION",$time);
                $finish;
            end
        end
        else begin
            data_tb <= '0;
        end
    end

    `ifdef RVFI
    rvfi_monitor #(
        .ENABLE_TRACER(ENABLE_TRACER),
        .ENABLE_PROFILER(ENABLE_PROFILER)
    ) u_rvfi_monitor (

        .rvfi_ext_clk(clk),
        .rvfi_ext_reset_n(reset_n),

        .rvfi_valid(rvfi_valid),
        .rvfi_order(rvfi_order),
        .rvfi_insn(rvfi_insn),
        .rvfi_trap(rvfi_trap),
        .rvfi_halt(rvfi_halt),
        .rvfi_intr(rvfi_intr),
        .rvfi_mode(rvfi_mode),
        .rvfi_ixl(rvfi_ixl),
        .rvfi_rs1_addr(rvfi_rs1_addr),
        .rvfi_rs2_addr(rvfi_rs2_addr),
        .rvfi_rs1_rdata(rvfi_rs1_rdata),
        .rvfi_rs2_rdata(rvfi_rs2_rdata),
        .rvfi_rd_addr(rvfi_rd_addr),
        .rvfi_rd_wdata(rvfi_rd_wdata),
        .rvfi_pc_rdata(rvfi_pc_rdata),
        .rvfi_pc_wdata(rvfi_pc_wdata),
        .rvfi_mem_addr(rvfi_mem_addr),
        .rvfi_mem_rmask(rvfi_mem_rmask),
        .rvfi_mem_wmask(rvfi_mem_wmask),
        .rvfi_mem_rdata(rvfi_mem_rdata),
        .rvfi_mem_wdata(rvfi_mem_wdata)

    );
    `endif

endmodule
