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
`include "../rtl/decoder.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
`include "../rtl/PUCRS-RV.sv"
`include "./ram.sv"

import my_pkg::*;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// CPU TESTBENCH IMPLEMENTATION //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module PUCRS_RV_tb ();

logic         clk=1, rstCPU;
logic [31:0]  i_address, instruction;
logic         read;
logic [31:0]  read_address, data_read, write_address, data_write;
logic [3:0]   write, w_en;
byte          char;
logic [31:0]  Rd_data, Wr_address, Wr_data;
logic [31:0]  IRQ;

////////////////////////////////////////////////////// Clock generator //////////////////////////////////////////////////////////////////////////////
    always begin
        #1.0 clk = 0;
        #1.0 clk = 1;
    end

////////////////////////////////////////////////////// TIMER generator //////////////////////////////////////////////////////////////////////////////
integer TIMER;
    always @(negedge rstCPU or posedge clk) begin
        if(!rstCPU)
            TIMER <= 0;
        else begin
            TIMER <= TIMER + 1;
            if(TIMER % 500 == 0)
                IRQ[7] <= 1;
        end
    end
////////////////////////////////////////////////////// data memory signals //////////////////////////////////////////////////////////////////////////
  always_comb
    if(write!=0) begin
        if(write_address <= 32'h0000FFFF)
          w_en <= write;
        Wr_address <= write_address;                            // Wr_address - write_address
        Wr_data <= data_write;                                  // Wr_data - data_write
    end else begin 
        w_en <= 4'h0;
        Wr_data <= 32'h00000000;
        Wr_address<=32'h00000000;
    end

    always_comb
        if(read == 1)
            if(read_address == 32'h80006000)
                data_read <= $time/1000;
            else 
                data_read <= Rd_data;
        else
            data_read <= 'Z;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Memory Mapped regs ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk) begin
        if((write_address == 32'h80004000 || write_address == 32'h80001000) && write!=0) begin
            char <= data_write[7:0];
            $write("%c",char);

        end else if(write_address == 32'h80000007)
            IRQ[7] <= 'Z;

        else if(write_address==32'h80000000) begin
            $display("# %t END OF SIMULATION",$time);
            $finish;
        end
    end

////////////////////////////////////////////////////// RAM INSTANTIATION ///////////////////////////////////////////////////////////////////////
    RAM_mem RAM_MEM(.clk(clk), .rst(rstCPU), .w_en(w_en), .r_en(read), .i_addr(i_address[15:0]), 
                    .r_addr(read_address[15:0]), .w_addr(Wr_address[15:0]), .w_data(Wr_data), .r_data(Rd_data), .i_data(instruction)
                    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// CPU INSTANTIATION ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    PUCRS_RV dut (
            .clk(clk), .reset(rstCPU), .instruction(instruction), .i_address(i_address), .read(read), .read_address(read_address),
            .DATA_in(data_read), .DATA_out(data_write), .write_address(write_address), .write(write),
            .IRQ(IRQ)
        );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// RESET CPU ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    initial begin
        rstCPU = 0;                                         // RESET for CPU initialization
        IRQ <= '0;
        
        #100 rstCPU = 1;                                     // Hold state for 100 ns

        #300
        IRQ[11] <= 1;
        #70
        IRQ[11] <= 0;
        #30
        IRQ[3] <= 1;
        #70
        IRQ[3] <= 0;
        #30
        IRQ[7] <= 1;
        #70
        IRQ[7] <= 0;
        #70
        IRQ[7] <= 'Z;
    end

endmodule
