/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// SRV TESTBENCH //////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Developed By: Willian Analdo Nunes /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// PUCRS, Porto Alegre, 2020      /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
`timescale 1ns/1ps
`include "./rtl/pkg.sv"
`include "./rtl/adder.sv"
`include "./rtl/branchUnit.sv"
`include "./rtl/bypassUnit.sv"
`include "./rtl/logicUnit.sv"
`include "./rtl/memoryUnit.sv"
`include "./rtl/shiftUnit.sv"
`include "./rtl/execute.sv"
`include "./rtl/fetch.sv"
`include "./rtl/decoder.sv"
`include "./rtl/operandFetch.sv"
`include "./rtl/retire.sv"
`include "./rtl/regbank.sv"
`include "./rtl/SRV.sv"
import my_pkg::*;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// ASSYNC RAM MEMORY IMPLEMENTATION ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

module RAM_mem #(parameter startaddress = 32'h00000000)(
    input logic clock,
    input logic rst,
    input logic [31:0] i_address, 
    output logic [31:0] instruction,
    input logic write_enable,
    input logic [1:0] size,
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

    assign W_tmp_address = write_address - startaddress;            //  Address offset 
    assign W_low_address = W_tmp_address[15:0];                 // Considers only the less significant half
    assign W_low_address_int = W_low_address;                   // convert to integer

    assign R_tmp_address = read_address - startaddress;            //  Address offset 
    assign R_low_address = R_tmp_address[15:0];                 // Considers only the less significant half
    assign R_low_address_int = R_low_address;                   // convert to integer

    assign INST_tmp_address = i_address - startaddress;            //  Address offset 
    assign INST_low_address = INST_tmp_address[15:0];                 // Considers only the less significant half
    assign INST_low_address_int = INST_low_address;   

    initial begin
        fd = $fopen ("./BerkeleySuite.bin", "r");
        fd = $fopen ("./test_hanoi.bin", "r");
        //fd = $fopen ("./coremark.bin", "r");
        //fd = $fopen ("./coremarkDEBUG.bin", "r");

        r = $fread(RAM, fd);
        $display("read %d elements \n", r);
    end

////////////////////////////////////////////////////////////// Writes in memory ASYNCHRONOUSLY //////////////////////////////////////////////////////
    always @(write_enable or W_low_address) begin               // Sensitivity list 
        if(write_enable==1 && W_low_address_int>=0 && W_low_address_int<=(MEMORY_SIZE-3)) begin // Check address range and write signals
                if(size==2'b11) begin                                 // Store Word(4 bytes)
                    RAM[W_low_address_int+3] <= Wr_data[31:24];
                    RAM[W_low_address_int+2] <= Wr_data[23:16];
                    RAM[W_low_address_int+1] <= Wr_data[15:8];
                    RAM[W_low_address_int] <= Wr_data[7:0];
                end else if(size==2'b10) begin                        // Store Half(2 bytes)
                    RAM[W_low_address_int+1] <= Wr_data[15:8];
                    RAM[W_low_address_int] <= Wr_data[7:0];
                end else begin                                  // Store Byte(1 byte)
                    RAM[W_low_address_int] <= Wr_data[7:0];
                end
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
        if(rst==0 && INST_low_address_int>=0 && INST_low_address_int<=(MEMORY_SIZE-3)) begin // Check address range and read signals
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
module SRV_tb ();

int    fd;                                          // Variable for file descriptor handle
logic [31:0]  Wr_address, Wr_data, instruction, read_address, i_address, write_address, data_read, data_rd, data_write;
logic  clk, rstCPU, read, write;
logic [1:0] size;
byte char;

////////////////////////////////////////////////////// Clock generator //////////////////////////////////////////////////////////////////////////////
  always begin
    #1.0 clk = 1;
    #1.0 clk = 0;
  end

////////////////////////////////////////////////////// MEM INSTANTIATION ///////////////////////////////////////////////////////////////////////
	RAM_mem #(32'h00000000) RAM_MEM(.clock(clk), .write_enable(write), .read_enable(read), .rst(!rstCPU), .size(size), .i_address(i_address), 
            .read_address(read_address), .write_address(Wr_address), .Wr_data(Wr_data), .data_read(data_rd), .instruction(instruction));

// data memory signals --------------------------------------------------------
  always_comb
    if(write==1) begin
        Wr_address <= write_address;                // Wr_address - write_address
        Wr_data <= data_write;                      // Wr_data - data_write
        $fdisplay(fd,"[%0d] Write: %h in address %d(%h) size: %0d  write %0d", $time, Wr_data, write_address, write_address, size, write);
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
        $fdisplay(fd,"[%0d]Read: %h from address %d(%h)) ", $time,  data_read, read_address, read_address);
    end else
        data_read <= 'Z; 		// data_cpu

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Memory Mapped regs ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  always @(posedge clk) begin
    if((write_address == 32'h80004000 | write_address == 32'h80001000) & write==1) begin
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

    SRV dut (.clk(clk), .reset(rstCPU), .instruction(instruction), .i_address(i_address), .read(read), .read_address(read_address),
             .DATA_in(data_read), .DATA_out(data_write), .write_address(write_address), .write(write), .size(size));

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