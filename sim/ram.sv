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

module RAM_mem (
    input logic clk,
    input logic rst,
    input logic [15:0] i_addr, 
    output logic [31:0] i_data,
    input logic [3:0] w_en,
    input logic [15:0] w_addr,
    input logic [31:0] w_data,
    input logic r_en,
    input logic [15:0] r_addr,
    output logic [31:0] r_data
);

    reg [7:0] RAM [0:65535];

    int fd, r;
    int fd_i, fd_r, fd_w;

    initial begin
        fd = $fopen ("/home/williannunes/pucrs-rv/bin/test.bin", "r");

        r = $fread(RAM, fd);
        $display("read %d elements \n", r);

        fd_i = $fopen ("./debug/instructions.txt", "w");
        fd_r = $fopen ("./debug/reads.txt", "w");
        fd_w = $fopen ("./debug/writes.txt", "w");
    end

////////////////////////////////////////////////////////////// Writes data in memory  //////////////////////////////////////////////////////
    always @(posedge clk)
        if(w_en!=0) begin
            if(w_en[3]==1)                                  // Store Word(4 bytes)
                RAM[w_addr+3] <= w_data[31:24];
            if(w_en[2]==1)                                  // Store Word(4 bytes)
                RAM[w_addr+2] <= w_data[23:16];
            if(w_en[1]==1)                                  // Store Half(2 bytes)
                RAM[w_addr+1] <= w_data[15:8];
            if(w_en[0]==1)                                  // Store Byte(1 byte)
                RAM[w_addr]   <= w_data[7:0];

            $fwrite(fd_w,"[%0d] ", $time);
            if(w_en[3]==1) $fwrite(fd_w,"%h ", w_data[31:24]); else $fwrite(fd_w,"-- ");
            if(w_en[2]==1) $fwrite(fd_w,"%h ", w_data[23:16]); else $fwrite(fd_w,"-- ");
            if(w_en[1]==1) $fwrite(fd_w,"%h ", w_data[15:8]);  else $fwrite(fd_w,"-- ");
            if(w_en[0]==1) $fwrite(fd_w,"%h ", w_data[7:0]);   else $fwrite(fd_w,"-- ");
            $fwrite(fd_w," --> 0x%4h\n", w_addr);
        end

////////////////////////////////////////////////////////////// Read DATA from memory /////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if(r_en==1) begin
            r_data[31:24] <= RAM[r_addr+3];
            r_data[23:16] <= RAM[r_addr+2];
            r_data[15:8]  <= RAM[r_addr+1];
            r_data[7:0]   <= RAM[r_addr];
        
            if(r_addr!=0)
                $fwrite(fd_r,"[%0d] %h %h %h %h <-- 0x%4h\n", $time, RAM[r_addr+3], RAM[r_addr+2], RAM[r_addr+1], RAM[r_addr], r_addr);
        
        end else
            r_data <= 'Z;

////////////////////////////////////////////////////////////// Read instructions from memory /////////////////////////////////////////////////////////////////////
    always @(posedge clk) begin
        i_data[31:24] <= RAM[i_addr+3];
        i_data[23:16] <= RAM[i_addr+2];
        i_data[15:8]  <= RAM[i_addr+1];
        i_data[7:0]   <= RAM[i_addr];

        $fwrite(fd_i,"[%0d] %h -> %h %h %h %h \n", $time, i_addr, RAM[i_addr+3], RAM[i_addr+2], RAM[i_addr+1], RAM[i_addr]);
    end
endmodule
