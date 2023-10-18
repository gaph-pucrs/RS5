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
 * Testbench for RS5 simulation.
 */

`timescale 1ns/1ps

`include "../rtl/RS5_pkg.sv"
`include "../rtl/mmu.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decode.sv"
`include "../rtl/muldiv.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
`include "../rtl/RS5.sv"
`include "../rtl/plic.sv"
`include "../rtl/rtc.sv"
`include "./RAM_mem.sv"

//////////////////////////////////////////////////////////////////////////////
// CPU TESTBENCH
//////////////////////////////////////////////////////////////////////////////

module testbench
    import RS5_pkg::*;
    (
        input logic clk_i,
        input logic rst_i
    );

//////////////////////////////////////////////////////////////////////////////
// PARAMETERS FOR CORE INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    localparam int           MEM_WIDTH = 65536;
    localparam string        BIN_FILE = "../app/berkeley_suite/test.bin";
    
    localparam int           i_cnt = 1;

//////////////////////////////////////////////////////////////////////////////
// TB SIGNALS
//////////////////////////////////////////////////////////////////////////////

    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0]            instruction_address;
    logic                   interrupt_ack;
    logic [63:0]            mtime;
    logic [63:0]            data_rtc;
    /* verilator lint_on UNUSEDSIGNAL */
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
    
    always_ff @(posedge clk_i) begin
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

    RS5 dut (
        .clk                    (clk_i), 
        .reset                  (rst_i), 
        .stall                  (1'b0),
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
        .MEM_WIDTH(MEM_WIDTH),
        .BIN_FILE(BIN_FILE)
    ) RAM_MEM (
        .clk        (clk_i), 

        .enA_i      (1'b1), 
        .weA_i      (4'h0), 
        .addrA_i    (instruction_address[15:0]), 
        .dataA_i    (32'h00000000), 
        .dataA_o    (instruction),

        .enB_i      (enable_ram), 
        .weB_i      (mem_write_enable), 
        .addrB_i    (mem_address[15:0]), 
        .dataB_i    (mem_data_write), 
        .dataB_o    (data_ram)
    );

//////////////////////////////////////////////////////////////////////////////
// PLIC
//////////////////////////////////////////////////////////////////////////////

    plic #(
        .i_cnt(i_cnt)
    ) plic1 (
        .clk    (clk_i),
        .reset  (rst_i),
        .en_i   (enable_plic),
        .we_i   (mem_write_enable),
        .addr_i (mem_address[23:0]),
        .data_i (mem_data_write),
        .data_o (data_plic),     
        .irq_i  ('0),
        .iack_i (interrupt_ack),
        /* verilator lint_off PINCONNECTEMPTY */
        .iack_o (),
        /* verilator lint_on PINCONNECTEMPTY */
        .irq_o  (mei)
    );

//////////////////////////////////////////////////////////////////////////////
// RTC
//////////////////////////////////////////////////////////////////////////////

    rtc rtc(
        .clk        (clk_i),
        .reset      (rst_i), 
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

    always_ff @(posedge clk_i) begin
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

endmodule
