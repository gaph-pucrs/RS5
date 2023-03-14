/*!\file testbench.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  December 2021
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Testbench for pucrs-rv simulation.
 *
 * \detailed
 * Testbench for pucrs-rv simulation.
 */

`timescale 1ns/1ps

`include "../rtl/pkg.sv"
`include "../rtl/xus.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decode.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
`include "../rtl/PUC_RS5.sv"
`include "./ram.sv"

import my_pkg::*;

//////////////////////////////////////////////////////////////////////////////
// CPU TESTBENCH
//////////////////////////////////////////////////////////////////////////////

module PUC_RS5_tb ();

logic         clk = 1, rstCPU;
logic [31:0]  instruction_address, instruction;
logic         enable_ram, enable_tb;
logic [31:0]  mem_address, mem_data_read, mem_data_write;
logic [3:0]   mem_write_enable;
byte          char;
logic [31:0]  data_ram, data_tb;
logic [31:0]  IRQ;
logic interrupt_ack;
logic enable_tb_r;

//////////////////////////////////////////////////////////////////////////////
// Clock generator
//////////////////////////////////////////////////////////////////////////////

    always begin
        #5.0 clk = 0;
        #5.0 clk = 1;
    end

//////////////////////////////////////////////////////////////////////////////
// CPU INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    PUC_RS5 dut (
        .clk(clk), 
        .reset(rstCPU), 
        .stall(1'b0),
        .instruction_i(instruction), 
        .mem_data_i(mem_data_read), 
        .IRQ_i(IRQ),
        .instruction_address_o(instruction_address), 
        .mem_operation_enable_o(mem_operation_enable), 
        .mem_write_enable_o(mem_write_enable),
        .mem_address_o(mem_address),
        .mem_data_o(mem_data_write),
        .interrupt_ack_o(interrupt_ack)
    );

//////////////////////////////////////////////////////////////////////////////
// RAM INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    RAM_mem RAM_MEM(
        .clk(clk), 
        .instruction_address_i(instruction_address[15:0]), 
        .instruction_o(instruction),
        .operation_enable_i(enable_ram), 
        .write_enable_i(mem_write_enable), 
        .data_address_i(mem_address[15:0]), 
        .data_i(mem_data_write), 
        .data_o(data_ram)
    );

    assign enable_tb = (mem_address > 32'h0000FFFF && mem_operation_enable) 
                        ? 1 
                        : 0;

    assign enable_ram = (mem_address <= 32'h0000FFFF && mem_operation_enable) 
                        ? 1 
                        : 0;

    assign mem_data_read = (enable_tb_r) 
                        ? data_tb 
                        : data_ram;
    
    always @(posedge clk) begin
        enable_tb_r <= enable_tb;
    end


//////////////////////////////////////////////////////////////////////////////
// Memory Mapped regs
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk) begin
        if (enable_tb == 1) begin
            // OUTPUT REG
            if ((mem_address == 32'h80004000 || mem_address == 32'h80001000) && mem_write_enable != 0) begin
                char <= mem_data_write[7:0];
                $write("%c",char);
            end
            // END REG
            if (mem_address == 32'h80000000 && mem_write_enable != 0) begin
                $display("# %t END OF SIMULATION",$time);
                $finish;
            end
            // TIMER REG
            if (mem_address == 32'h80006000 && mem_write_enable == 0) begin
                data_tb <= $time/1000;
            end
        end 
        else begin
            data_tb <= '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// TIMER generator
//////////////////////////////////////////////////////////////////////////////

integer TIMER;

    always @(posedge clk or negedge rstCPU) begin
        if (rstCPU == 0) begin
            TIMER <= 0;
        end
        else begin
            TIMER <= TIMER + 1;
//            if(TIMER % 500 == 0)
//                IRQ[7] <= 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// RESET CPU
//////////////////////////////////////////////////////////////////////////////

    initial begin
        rstCPU = 1;                                          // RESET for CPU initialization
        IRQ <= '0;
        
        #100 rstCPU = 0;                                     // Hold state for 100 ns
    end

endmodule
