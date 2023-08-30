/*!\file ram.sv
 * RS5 VERSION - 1.0 - Public Release
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
 * RAM implementation for RS5 simulation.
 *
 * \detailed
 * RAM implementation for RS5 simulation.
 */

//////////////////////////////////////////////////////////////////////////////
// RAM MEMORY
//////////////////////////////////////////////////////////////////////////////

module RAM_mem 
    import RS5_pkg::*;
(
    input  logic clk,

    input  logic [15:0] instruction_address_i, 
    output logic [31:0] instruction_o,

    input  logic operation_enable_i,
    input  logic [3:0] write_enable_i,
    input  logic [15:0] data_address_i,
    input  logic [31:0] data_i,
    output logic [31:0] data_o
);

    reg [7:0] RAM [0:65535];
    int fd, r;
    int fd_i, fd_r, fd_w;

    initial begin
        fd = $fopen ("./ram.bin", "r");

        r = $fread(RAM, fd);
        $display("read %d elements \n", r);

        fd_i = $fopen ("./debug/instructions.txt", "w");
        fd_r = $fopen ("./debug/reads.txt", "w");
        fd_w = $fopen ("./debug/writes.txt", "w");
    end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// DATA MEMORY ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always_ff @(posedge clk) begin
        if (operation_enable_i) begin
            ///////////////////////////// Writes  ///////////////////////////////////////////
            if (write_enable_i != '0) begin
                if (write_enable_i[3]) begin                                 // Store Word(4 bytes)
                    RAM[data_address_i+3] <= data_i[31:24];
                end 
                if (write_enable_i[2]) begin                                 // Store Word(4 bytes)
                    RAM[data_address_i+2] <= data_i[23:16];
                end
                if (write_enable_i[1]) begin                                 // Store Half(2 bytes)
                    RAM[data_address_i+1] <= data_i[15:8];
                end
                if (write_enable_i[0]) begin                                 // Store Byte(1 byte)
                    RAM[data_address_i]   <= data_i[7:0];
                end

                $fwrite(fd_w,"[%0d] ", $time);
                if (write_enable_i[3]) $fwrite(fd_w,"%h ", data_i[31:24]); else $fwrite(fd_w,"-- ");
                if (write_enable_i[2]) $fwrite(fd_w,"%h ", data_i[23:16]); else $fwrite(fd_w,"-- ");
                if (write_enable_i[1]) $fwrite(fd_w,"%h ", data_i[15:8]);  else $fwrite(fd_w,"-- ");
                if (write_enable_i[0]) $fwrite(fd_w,"%h ", data_i[7:0]);   else $fwrite(fd_w,"-- ");
                $fwrite(fd_w," --> 0x%4h\n", data_address_i);
            //////////////////////////// Reads //////////////////////////////////////////////
            end 
            else begin
                data_o[31:24] <= RAM[data_address_i+3];
                data_o[23:16] <= RAM[data_address_i+2];
                data_o[15:8]  <= RAM[data_address_i+1];
                data_o[7:0]   <= RAM[data_address_i];

                if (data_address_i != '0) begin
                    $fwrite(fd_r,"[%0d] %h %h %h %h <-- 0x%4h\n", 
                        $time, RAM[data_address_i+3], RAM[data_address_i+2], RAM[data_address_i+1], RAM[data_address_i], data_address_i);
                end
            end
        end 
        else begin
            data_o <= '0;
        end
    end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// INSTRUCTION MEMORY /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always_ff @(posedge clk) begin
        instruction_o[31:24] <= RAM[instruction_address_i+3];
        instruction_o[23:16] <= RAM[instruction_address_i+2];
        instruction_o[15:8]  <= RAM[instruction_address_i+1];
        instruction_o[7:0]   <= RAM[instruction_address_i];

        $fwrite(fd_i,"[%0d] %h -> %h %h %h %h \n", 
            $time, instruction_address_i, RAM[instruction_address_i+3], RAM[instruction_address_i+2], RAM[instruction_address_i+1], RAM[instruction_address_i]);
    end
endmodule
