/*!\file ram.sv
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
 * RAM implementation for pucrs-rv simulation.
 *
 * \detailed
 * RAM implementation for pucrs-rv simulation.
 */

`timescale 1ns/1ps
import my_pkg::*;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// SYNC RAM MEMORY IMPLEMENTATION ////////////////////////////////////////////////////////////
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
    int W_low_address_int, R_low_address_int, INST_low_address_int;
    int fd, r;
    int fd_i, fd_d;

    assign W_tmp_address = write_address - startaddress;                //  Address offset
    assign W_low_address_int = W_tmp_address[15:0];                     // convert to integer

    assign R_tmp_address = read_address - startaddress;                 //  Address offset
    assign R_low_address_int = R_tmp_address[15:0];                     // convert to integer

    assign INST_tmp_address = i_address - startaddress;                 // Address offset
    assign INST_low_address_int = INST_tmp_address[15:0];               // convert to integer

    initial begin
        fd = $fopen ("/home/williannunes/pucrs-rv/bin/test.bin", "r");

        r = $fread(RAM, fd);
        $display("read %d elements \n", r);

        fd_i = $fopen ("./debug/instructions.txt", "w");
        fd_d = $fopen ("./debug/reads.txt", "w");
    end

////////////////////////////////////////////////////////////// Writes in memory  //////////////////////////////////////////////////////
    always @(negedge clock)
        if(write_enable!=0 && W_low_address_int>=0 && W_low_address_int<=(MEMORY_SIZE-3)) begin
                if(write_enable[3]==1)                                  // Store Word(4 bytes)
                    RAM[W_low_address_int+3] <= Wr_data[31:24];
                if(write_enable[2]==1)                                  // Store Word(4 bytes)
                    RAM[W_low_address_int+2] <= Wr_data[23:16];
                if(write_enable[1]==1)                                  // Store Half(2 bytes)
                    RAM[W_low_address_int+1] <= Wr_data[15:8];
                if(write_enable[0]==1)                                  // Store Byte(1 byte)
                    RAM[W_low_address_int]   <= Wr_data[7:0];
        end

////////////////////////////////////////////////////////////// Read DATA from memory /////////////////////////////////////////////////////////////////////
    always @(posedge clock)
        if(read_enable==1 && R_low_address_int>=0 && R_low_address_int<=(MEMORY_SIZE-3)) begin
            data_read[31:24] <= RAM[R_low_address_int+3];
            data_read[23:16] <= RAM[R_low_address_int+2];
            data_read[15:8]  <= RAM[R_low_address_int+1];
            data_read[7:0]   <= RAM[R_low_address_int];

            $fwrite(fd_d,"Read: %8h -> %8h\n", R_low_address_int, data_read);
        end

////////////////////////////////////////////////////////////// Read INSTRUCTION from memory /////////////////////////////////////////////////////////////////////
    always @(rst or negedge clock)
        if(rst==0)
            instruction <= '0;
        else if(rst==1 && INST_low_address_int>=0 && INST_low_address_int<=(MEMORY_SIZE-3)) begin
            instruction[31:24] <= RAM[INST_low_address_int+3];
            instruction[23:16] <= RAM[INST_low_address_int+2];
            instruction[15:8]  <= RAM[INST_low_address_int+1];
            instruction[7:0]   <= RAM[INST_low_address_int];

            $fwrite(fd_i,"%8h -> %8h\n", INST_low_address_int, instruction);
        end
endmodule
