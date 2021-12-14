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
import my_pkg::*;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// ASSYNC RAM MEMORY IMPLEMENTATION ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

module RAM_mem #(parameter startaddress = 32'h00000000)(
    input logic clock,
    input logic rst,
    input logic [31:0] i_address, 
    output logic [31:0] instruction,
    input logic [3:0] write_enable,
    input logic [31:0] write_address,
    input logic [31:0] Wr_data,
    input logic read_enable,
    input logic [31:0] read_address,
    output logic [31:0] data_read);

    bit [7:0] RAM [0:65535];
    
    logic [31:0] W_tmp_address, R_tmp_address, INST_tmp_address;
    logic [15:0] W_low_address, R_low_address, INST_low_address;
    int W_low_address_int, R_low_address_int, INST_low_address_int;
    int fd, r;

    assign W_tmp_address = write_address - startaddress;        //  Address offset 
    assign W_low_address = W_tmp_address[15:0];                 // Considers only the less significant half
    assign W_low_address_int = W_low_address;                   // convert to integer

    assign R_tmp_address = read_address - startaddress;         //  Address offset 
    assign R_low_address = R_tmp_address[15:0];                 // Considers only the less significant half
    assign R_low_address_int = R_low_address;                   // convert to integer

    assign INST_tmp_address = i_address - startaddress;         //  Address offset 
    assign INST_low_address = INST_tmp_address[15:0];           // Considers only the less significant half
    assign INST_low_address_int = INST_low_address;   

    initial begin
        fd = $fopen ("../bin/test.bin", "r");

        r = $fread(RAM, fd);
        $display("read %d elements \n", r);
    end

////////////////////////////////////////////////////////////// Writes in memory ASYNCHRONOUSLY //////////////////////////////////////////////////////
    always @(write_enable or W_low_address) begin               // Sensitivity list 
        if(write_enable!=0 && W_low_address_int>=0 && W_low_address_int<=(MEMORY_SIZE-3)) begin // Check address range and write signals
                if(write_enable[3]==1)                                          // Store Word(4 bytes)
                    RAM[W_low_address_int+3] <= Wr_data[31:24];
                if(write_enable[2]==1)                                          // Store Word(4 bytes)
                    RAM[W_low_address_int+2] <= Wr_data[23:16];
                if(write_enable[1]==1)                                          // Store Half(2 bytes)
                    RAM[W_low_address_int+1] <= Wr_data[15:8];
                if(write_enable[0]==1)                                          // Store Byte(1 byte)
                    RAM[W_low_address_int]   <= Wr_data[7:0];
        end
    end

////////////////////////////////////////////////////////////// Read DATA from memory /////////////////////////////////////////////////////////////////////
    always @(read_enable or R_low_address or INST_low_address) begin
        if(read_enable==1 && R_low_address_int>=0 && R_low_address_int<=(MEMORY_SIZE-3)) begin // Check address range and read signals
            data_read[31:24] <= RAM[R_low_address_int+3];
            data_read[23:16] <= RAM[R_low_address_int+2];
            data_read[15:8] <= RAM[R_low_address_int+1];
            data_read[7:0] <= RAM[R_low_address_int];
            //$display("%t diparou o processo %h is %d", $time, low_address_int, RAM[low_address_int]);
        end
    end

////////////////////////////////////////////////////////////// Read INSTRUCTION from memory /////////////////////////////////////////////////////////////////////
    always @( rst | INST_low_address) begin
        if(rst==1 && INST_low_address_int>=0 && INST_low_address_int<=(MEMORY_SIZE-3)) begin // Check address range and read signals
            instruction[31:24] <= RAM[INST_low_address_int+3];
            instruction[23:16] <= RAM[INST_low_address_int+2];
            instruction[15:8] <= RAM[INST_low_address_int+1];
            instruction[7:0] <= RAM[INST_low_address_int];
        end
    end
endmodule

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

////////////////////////////////////////////////////// MEM INSTANTIATION ///////////////////////////////////////////////////////////////////////
	RAM_mem #(32'h00000000) RAM_MEM(.clock(clk), .write_enable(write), .read_enable(read), .rst(rstCPU), .i_address(i_address), 
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
