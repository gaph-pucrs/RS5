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
    parameter int         DELAY_CYCLES     = 0
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
// Data cache (direct-mapped write-back) + RAM
//
// The data port is served through the DMWBCtrl write-back cache so the suite
// exercises the controller. Instruction fetches use a dedicated RAM port and
// bypass the cache (read-only path). Because written data may linger dirty in
// the cache, the signature dump below reads each word through a cache-coherent
// view (cache copy if resident, otherwise main memory).
//////////////////////////////////////////////////////////////////////////////

    localparam int ADDR_BITS    = $clog2(MEM_WIDTH);
    localparam int DCACHE_WIDTH = 12;
    localparam int DCACHE_OFF_W = 6;
    localparam int TAG_BITS     = ADDR_BITS    - DCACHE_WIDTH;
    localparam int IDX_BITS     = DCACHE_WIDTH - DCACHE_OFF_W;

    /* Core <-> data cache */
    logic        dcache_busy;
    logic [31:0] dcache_dataR;
    assign stall    = dcache_busy && enable_ram;
    assign data_ram = dcache_dataR;
    assign busy     = 1'b0;                 // dedicated instruction port

    /* Data cache <-> cache SRAM */
    logic                    dcache_ce;
    logic [3:0]              dcache_we;
    logic [DCACHE_WIDTH-1:0] dcache_addr;
    logic [31:0]             dcache_sram_rdata;
    logic [31:0]             dcache_sram_wdata;

    /* Data cache <-> main memory (RAM port B) */
    logic                 dmem_ce;
    logic [3:0]           dmem_we;
    logic [ADDR_BITS-1:0] dmem_addr;
    logic [31:0]          dmem_dataW;
    logic                 dmem_busy;

    DMWBCtrl #(
        .ADDR_WIDTH  (ADDR_BITS   ),
        .CACHE_WIDTH (DCACHE_WIDTH),
        .OFFSET_WIDTH(DCACHE_OFF_W)
    ) dcache_ctrl (
        .clk         (clk),
        .rst_n       (reset_n),
        .ce_i        (enable_ram),
        .we_i        (mem_write_enable),
        .address_i   (mem_address[ADDR_BITS-1:0]),
        .data_i      (mem_data_write),
        .data_o      (dcache_dataR),
        .busy_o      (dcache_busy),
        .cache_ce_o  (dcache_ce),
        .cache_we_o  (dcache_we),
        .cache_addr_o(dcache_addr),
        .cache_data_i(dcache_sram_rdata),
        .cache_data_o(dcache_sram_wdata),
        .mem_ce_o    (dmem_ce),
        .mem_we_o    (dmem_we),
        .mem_addr_o  (dmem_addr),
        .mem_data_i  (data_ram_raw),
        .mem_data_o  (dmem_dataW),
        .mem_busy_i  (dmem_busy)
    );

    RAM_mem #(
        .MEM_WIDTH(1 << DCACHE_WIDTH),
        .BIN_FILE ("")
    ) dcache_sram (
        .clk    (clk),
        .enA_i  (dcache_ce),
        .weA_i  (dcache_we),
        .addrA_i(dcache_addr),
        .dataA_i(dcache_sram_wdata),
        .dataA_o(dcache_sram_rdata),
        .enB_i  (1'b0),
        .weB_i  ('0),
        .addrB_i('0),
        .dataB_i('0),
        /* verilator lint_off PINCONNECTEMPTY */
        .dataB_o(/* Unconnected */)
        /* verilator lint_on PINCONNECTEMPTY */
    );

    logic                 enA;
    logic [3:0]           weA;
    logic [ADDR_BITS-1:0] addrA;
    logic [31:0]          dataAi;
    logic [31:0]          dataAo;

    logic                 enB;
    logic [3:0]           weB;
    logic [ADDR_BITS-1:0] addrB;
    logic [31:0]          dataBi;
    logic [31:0]          dataBo;
    logic [31:0]          data_ram_raw;

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

    /* Memory delay handshake, keyed off the cache's main-memory requests */
    logic enable_ram_delayed;
    initial begin
        dmem_busy          = 1'b0;
        enable_ram_delayed = 1'b0;

        forever begin
            @(negedge clk iff dmem_ce);
            dmem_busy = 1'b1;
            repeat (DELAY_CYCLES) @(negedge clk);
            dmem_busy = 1'b0;
            enable_ram_delayed = 1'b1;
            @(negedge clk iff !dmem_ce);
            enable_ram_delayed = 1'b0;
        end
    end

    /* Port A: instruction fetch (direct).  Port B: cache memory traffic. */
    assign enA          = instruction_enable;
    assign weA          = 4'h0;
    assign addrA        = instruction_address[ADDR_BITS-1:0];
    assign dataAi       = 32'h00000000;
    assign instruction  = dataAo;

    assign enB          = enable_ram_delayed;
    assign weB          = dmem_we;
    assign addrB        = dmem_addr;
    assign dataBi       = dmem_dataW;
    assign data_ram_raw = dataBo;

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

    /* Cache-coherent signature read: a word is taken from the cache SRAM when it
     * is currently resident (valid tag), otherwise from main memory. This is the
     * value the core would observe, so it captures still-dirty write-back data. */
    function automatic logic [31:0] sig_word(input logic [31:0] a);
        logic [ADDR_BITS-1:0]    ma;
        logic [TAG_BITS-1:0]     tg;
        logic [IDX_BITS-1:0]     ix;
        logic [DCACHE_WIDTH-1:0] cb;
        ma = a[ADDR_BITS-1:0];
        tg = ma[ADDR_BITS-1 -: TAG_BITS];
        ix = ma[DCACHE_WIDTH-1 -: IDX_BITS];
        cb = ma[DCACHE_WIDTH-1:0];
        if (dcache_ctrl.entries[ix].valid && dcache_ctrl.entries[ix].tag == tg)
            return {dcache_sram.RAM[cb+3], dcache_sram.RAM[cb+2],
                    dcache_sram.RAM[cb+1], dcache_sram.RAM[cb+0]};
        else
            return {RAM_MEM.RAM[ma+3], RAM_MEM.RAM[ma+2],
                    RAM_MEM.RAM[ma+1], RAM_MEM.RAM[ma+0]};
    endfunction

    final begin
        for (int i = SIG_START; i < SIG_END; i=i+4)
            $fwrite(fd, "%x\n", sig_word(i[31:0]));
        $fclose(fd);
        $display("# %t END OF SIMULATION",$time);
    end

endmodule
