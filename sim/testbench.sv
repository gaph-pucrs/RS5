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
`include "../rtl/adder.sv"
`include "../rtl/branch.sv"
`include "../rtl/bypass.sv"
`include "../rtl/logic.sv"
`include "../rtl/memory.sv"
`include "../rtl/shift.sv"
`include "../rtl/execute.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decoder.sv"
`include "../rtl/operandFetch.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/PUCRS-RV.sv"
`include "./ram.sv"

import my_pkg::*;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// CPU TESTBENCH IMPLEMENTATION //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module PUCRS_RV_tb ();

int    fd;                                                      // Variable for file descriptor handle
logic [31:0]  Wr_address, Wr_data, instruction, read_address, i_address, write_address, data_read, data_rd, data_write;
logic  clk, rstCPU, read;
logic [3:0] write;
byte char;

////////////////////////////////////////////////////// Clock generator //////////////////////////////////////////////////////////////////////////////
  always begin
    #1.0 clk = 1;
    #1.0 clk = 0;
  end

////////////////////////////////////////////////////// RAM INSTANTIATION ///////////////////////////////////////////////////////////////////////
	RAM_mem #(32'h00000000) RAM_MEM(.clock(clk), .rst(rstCPU), .write_enable(write), .read_enable(read), .i_address(i_address), 
            .read_address(read_address), .write_address(Wr_address), .Wr_data(Wr_data), .data_read(data_rd), .instruction(instruction));

// data memory signals --------------------------------------------------------
  always_comb
    if(write!=0) begin
        Wr_address <= write_address;                            // Wr_address - write_address
        Wr_data <= data_write;                                  // Wr_data - data_write
        $fdisplay(fd,"[%0d] Write: %h in address %d(%h)  write %04b", $time, data_write, write_address, write_address, write);
    end else begin 
        Wr_data <= 32'h00000000;
        Wr_address<=32'h00000000;
    end
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  always_comb
    if(read==1) begin
        if(read_address==32'h80006000)
            data_read <= $time/1000;
        else 
            data_read <= data_rd; 
        if(read_address!=0 && data_read!=0)
            $fdisplay(fd,"[%0d] Read: %h from address %d(%h)) ", $time,  data_read, read_address, read_address);
    end else
        data_read <= 'Z; 		                                // data_cpu

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Memory Mapped regs ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  always @(posedge clk) begin
    if((write_address == 32'h80004000 | write_address == 32'h80001000) & write!=0) begin
        char <= data_write[7:0];
        $write("%c",char);
    end

    if(write_address==32'h80000000) begin
        $display("# %t END OF SIMULATION",$time);
        $finish;
    end
  end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// CPU INSTANTIATION ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PUCRS_RV dut (.clk(clk), .reset(rstCPU), .instruction(instruction), .i_address(i_address), .read(read), .read_address(read_address),
             .DATA_in(data_read), .DATA_out(data_write), .write_address(write_address), .write(write));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// RESET CPU ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //always #1000000000
    //    $display("%d elapsed", $time);

    initial begin
        rstCPU = 0;                                         // RESET for CPU initialization
        fd = $fopen ("memDebug.txt", "w");
        #30 rstCPU = 1;                                     // Hold state for 30 ns
    end
endmodule
