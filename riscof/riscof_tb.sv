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

`include "RS5_pkg.sv"

//////////////////////////////////////////////////////////////////////////////
// CPU TESTBENCH
//////////////////////////////////////////////////////////////////////////////

module riscof_tb
    import RS5_pkg::*;
#(
    parameter logic[31:0] SIG_START        = 0,
    parameter logic[31:0] SIG_END          = 0,
    parameter logic[31:0] TOHOST_ADDR      = 0,
    parameter string      SIG_PATH         = "",
    parameter bit         MEnable          = 1'b0,
    parameter bit         AEnable          = 1'b0,
    parameter bit         COMPRESSED       = 1'b0,
    parameter bit         ZICONDEnable     = 1'b0,
    parameter bit         HPMCOUNTEREnable = 1'b0,
    parameter bit         ZKNEEnable       = 1'b0,
    parameter bit         ZCBEnable        = 1'b0,
    parameter int         IQUEUE_SIZE      = 2,
    parameter bit         BRANCHPRED       = 1'b0,
    parameter bit         FORWARDING       = 1'b0,
    parameter bit         DUALPORT_MEM     = 1'b1,
    parameter int         RAM_DELAY_CYCLES = 1
)
(
);
    timeunit 1ns; timeprecision 1ns;

//////////////////////////////////////////////////////////////////////////////
// PARAMETERS FOR CORE INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    localparam string   BIN_FILE  = "test.bin";
    localparam int      MEM_WIDTH = 2_097_152;
    localparam int      i_cnt     = 1;
    localparam bit      USE_XOSVM = 1'b0;
    localparam bit      VEnable   = 1'b0;
    localparam bit      PROFILING = 1'b0;
    localparam bit      DEBUG     = 1'b0;
    localparam mul_e    MULEXT    = MEnable ? MUL_M : MUL_OFF;
    localparam atomic_e AMOEXT    = AEnable ? AMO_A : AMO_OFF;

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

//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    assign enable_rtc  = (mem_address[31:28] == 4'h2) && mem_operation_enable;
    assign enable_plic = (mem_address[31:28] == 4'h4) && mem_operation_enable;
    assign enable_ram  = (mem_address[31:28] == 4'h8) && mem_operation_enable;

    always_ff @(posedge clk) begin
        enable_rtc_r    <= enable_rtc;
        enable_plic_r   <= enable_plic;
    end

    always_comb begin
        if (enable_rtc_r) begin
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

    logic busy;
    logic stall;
    logic instruction_enable;

    RS5 #(
    `ifndef SYNTH
	    .DEBUG      (DEBUG          ),
	    .PROFILING  (PROFILING      ),
    `endif
        .Environment     (ASIC            ),
        .MULEXT          (MULEXT          ),
        .AMOEXT          (AMOEXT          ),
        .START_ADDR      (32'h80000000    ),
        .COMPRESSED      (COMPRESSED      ),
        .VEnable         (VEnable         ),
        .XOSVMEnable     (USE_XOSVM       ),
        .ZKNEEnable      (ZKNEEnable      ),
        .ZICONDEnable    (ZICONDEnable    ),
        .ZCBEnable       (ZCBEnable       ),
        .HPMCOUNTEREnable(HPMCOUNTEREnable),
        .IQUEUE_SIZE     (IQUEUE_SIZE     ),
        .BRANCHPRED      (BRANCHPRED      ),
        .FORWARDING      (FORWARDING      )
    ) dut (
        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset_i            (1'b0),
        .stall                  (stall),
        .busy_i                 (busy),
        .instruction_i          (instruction),
        .mem_data_i             (mem_data_read),
        .mtime_i                (mtime),
        .tip_i                  (mti),
        .eip_i                  (mei),
        .imem_operation_enable_o(instruction_enable),
        .instruction_address_o  (instruction_address),
        .dmem_operation_enable_o(mem_operation_enable),
        .mem_write_enable_o     (mem_write_enable),
        .mem_address_o          (mem_address),
        .mem_data_o             (mem_data_write),
        .interrupt_ack_o        (interrupt_ack)
    );


//////////////////////////////////////////////////////////////////////////////
// RAM
//////////////////////////////////////////////////////////////////////////////

    logic                             enA;
    logic [3:0]                       weA;
    logic [($clog2(MEM_WIDTH) - 1):0] addrA;
    logic [31:0]                      dataAi;
    logic [31:0]                      dataAo;

    logic                             enB;
    logic [3:0]                       weB;
    logic [($clog2(MEM_WIDTH) - 1):0] addrB;
    logic [31:0]                      dataBi;
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0]                      dataBo;
    /* verilator lint_on UNUSEDSIGNAL */

    RAM_mem #(
    `ifndef SYNTH
        .DEBUG     (DEBUG     ),
        .DEBUG_PATH("./debug/"),
    `endif
        .MEM_WIDTH(MEM_WIDTH  ),
        .BIN_FILE (BIN_FILE   )
    ) RAM_MEM (
        .clk        (clk),

        .enA_i      (enA),
        .weA_i      (weA),
        .addrA_i    (addrA),
        .dataA_i    (dataAi),
        .dataA_o    (dataAo),

        .enB_i      (enB),
        .weB_i      (weB),
        .addrB_i    (addrB),
        .dataB_i    (dataBi),
        .dataB_o    (dataBo)
    );

    logic enable_ram_delayed;
    initial begin
        stall = 1'b0;
        enable_ram_delayed = 1'b0;

        forever begin
            // 1. Wait for enable_ram to go high
            @(negedge clk iff enable_ram);

            // 2. Assert stall
            stall = 1'b1;

            // 3. Wait for some cycles (to simulate delay)
            repeat (RAM_DELAY_CYCLES) @(negedge clk);

            // 4. Deassert stall, assert delayed signal
            stall = 1'b0;
            enable_ram_delayed = 1'b1;

            // 5. Wait for enable_ram to go low to finish
            @(negedge clk iff !enable_ram);
            enable_ram_delayed = 1'b0;
        end
    end

    if (DUALPORT_MEM) begin : dual_port
        assign enA         = instruction_enable;
        assign weA         = 4'h0;
        assign addrA       = instruction_address[($clog2(MEM_WIDTH) - 1):0];
        assign dataAi      = 32'h00000000;
        assign instruction = dataAo;

        assign enB         = enable_ram_delayed;
        assign weB         = mem_write_enable;
        assign addrB       = mem_address[($clog2(MEM_WIDTH) - 1):0];
        assign dataBi      = mem_data_write;
        assign data_ram    = dataBo;

        assign busy        = 1'b0;
    end
    else begin : single_port
        assign enA         = enable_ram_delayed || instruction_enable;
        assign weA         = enable_ram_delayed ? mem_write_enable : 4'h0;
        assign addrA       = enable_ram_delayed ? mem_address[($clog2(MEM_WIDTH) - 1):0] : instruction_address[($clog2(MEM_WIDTH) - 1):0];
        assign dataAi      = mem_data_write;
        assign instruction = dataAo;
        assign data_ram    = dataAo;

        assign enB         = 1'b0;
        assign weB         = 4'h0000;
        assign addrB       = '0;
        assign dataBi      = 32'h00000000;

        assign busy        = enable_ram;
    end

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

    int fd;

    always_ff @(posedge clk) begin
        if (mem_address == TOHOST_ADDR && mem_write_enable != '0)
            $finish();
    end

    initial begin
        fd = $fopen(SIG_PATH, "w");
        #10ms;
        $finish();
    end

    final begin
        for (int i = SIG_START; i < SIG_END; i=i+4)
            $fwrite(fd, "%x\n", {RAM_MEM.RAM[i+3],RAM_MEM.RAM[i+2],RAM_MEM.RAM[i+1],RAM_MEM.RAM[i]});
        $fclose(fd);
        $display("# %t END OF SIMULATION",$time);
    end

endmodule
