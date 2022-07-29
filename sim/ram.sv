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
    int fd_i, fd_r, fd_w;

    assign W_tmp_address[31:2] = write_address[31:2] - startaddress[31:2];//  Address offset
    assign W_tmp_address[1:0] = '0;
    assign W_low_address_int = W_tmp_address[15:0];                     // convert to integer

    assign R_tmp_address[31:2] = read_address[31:2] - startaddress[31:2];//  Address offset
    assign R_tmp_address[1:0] = '0;
    assign R_low_address_int = R_tmp_address;                           // convert to integer
    //assign R_low_address_int[15:2] = R_tmp_address[15:2];               // convert to integer

    assign INST_tmp_address = i_address - startaddress;                 // Address offset
    assign INST_low_address_int = INST_tmp_address[15:0];               // convert to integer

    initial begin
        fd = $fopen ("/home/williannunes/pucrs-rv/bin/test.bin", "r");
        //fd = $fopen ("/home/williannunes/pucrs-rv/app/assembly/asm.bin", "r");

        r = $fread(RAM, fd);
        $display("read %d elements \n", r);

        fd_i = $fopen ("./debug/instructions.txt", "w");
        fd_r = $fopen ("./debug/reads.txt", "w");
        fd_w = $fopen ("./debug/writes.txt", "w");
    end

////////////////////////////////////////////////////////////// Writes in memory  //////////////////////////////////////////////////////
    always @(posedge clock)
        if(write_enable!=0 && W_low_address_int>=0 && W_low_address_int<=(MEMORY_SIZE-3) && write_address[31]!=1) begin
            if(write_enable[3]==1)                                  // Store Word(4 bytes)
                RAM[W_low_address_int+3] <= Wr_data[31:24];
            if(write_enable[2]==1)                                  // Store Word(4 bytes)
                RAM[W_low_address_int+2] <= Wr_data[23:16];
            if(write_enable[1]==1)                                  // Store Half(2 bytes)
                RAM[W_low_address_int+1] <= Wr_data[15:8];
            if(write_enable[0]==1)                                  // Store Byte(1 byte)
                RAM[W_low_address_int]   <= Wr_data[7:0];

            if(write_enable[3]==1) $fwrite(fd_w,"%h ", Wr_data[31:24]); else $fwrite(fd_w,"-- ");
            if(write_enable[2]==1) $fwrite(fd_w,"%h ", Wr_data[23:16]); else $fwrite(fd_w,"-- ");
            if(write_enable[1]==1) $fwrite(fd_w,"%h ", Wr_data[15:8]);  else $fwrite(fd_w,"-- ");
            if(write_enable[0]==1) $fwrite(fd_w,"%h ", Wr_data[7:0]);   else $fwrite(fd_w,"-- ");
            
            $fwrite(fd_w,"[%0d] ", $time);
            $fwrite(fd_w,"to address %8h\n", W_low_address_int);
        end

////////////////////////////////////////////////////////////// Read DATA from memory /////////////////////////////////////////////////////////////////////
    always @(posedge clock)
        if(read_enable==1 && R_low_address_int>=0 && R_low_address_int<=(MEMORY_SIZE-3)) begin
            data_read[31:24] <= RAM[R_low_address_int+3];
            data_read[23:16] <= RAM[R_low_address_int+2];
            data_read[15:8]  <= RAM[R_low_address_int+1];
            data_read[7:0]   <= RAM[R_low_address_int];
        
            if(R_low_address_int!=0)
                $fwrite(fd_r,"[%0d] Read: %h %h %h %h from addr %8h\n", $time, RAM[R_low_address_int+3], RAM[R_low_address_int+2], RAM[R_low_address_int+1], RAM[R_low_address_int], R_low_address_int);
        
        end else
            data_read <= 'Z;

////////////////////////////////////////////////////////////// Read INSTRUCTION from memory /////////////////////////////////////////////////////////////////////
    always @(posedge clock)
        if(INST_low_address_int>=0 && INST_low_address_int<=(MEMORY_SIZE-3)) begin
            instruction[31:24] <= RAM[INST_low_address_int+3];
            instruction[23:16] <= RAM[INST_low_address_int+2];
            instruction[15:8]  <= RAM[INST_low_address_int+1];
            instruction[7:0]   <= RAM[INST_low_address_int];

            $fwrite(fd_i,"[%0d] %h -> %h %h %h %h \n", $time, INST_low_address_int, RAM[INST_low_address_int+3], RAM[INST_low_address_int+2], RAM[INST_low_address_int+1], RAM[INST_low_address_int]);
        end
endmodule
