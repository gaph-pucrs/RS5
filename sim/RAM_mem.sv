/*!\file ram.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  OCtober 2023
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
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
#(
    parameter int    MEM_WIDTH  = 65536,
    parameter string BIN_FILE   = "../app/berkeley_suite/test.bin",
    parameter        DEBUG      = 0,
    parameter string DEBUG_FILE = "./debug/"
)
(
    input  logic                             clk,

    input  logic                             enA_i,
    input  logic [ 3:0]                      weA_i,
    input  logic [($clog2(MEM_WIDTH) - 1):0] addrA_i,
    input  logic [31:0]                      dataA_i,
    output logic [31:0]                      dataA_o,

    input  logic                             enB_i,
    input  logic [ 3:0]                      weB_i,
    input  logic [($clog2(MEM_WIDTH) - 1):0] addrB_i,
    input  logic [31:0]                      dataB_i,
    output logic [31:0]                      dataB_o
);

    reg [7:0] RAM [0:MEM_WIDTH-1];
    int fd, r;
    int fd_r_a, fd_r_b, fd_w_a, fd_w_b;

    initial begin
        fd = $fopen (BIN_FILE, "r");

        r = $fread(RAM, fd);
        $display("read %d elements", r);

        if (DEBUG) begin
            fd_r_a = $fopen ({DEBUG_FILE, "_A_reads.txt"}, "w");
            fd_r_b = $fopen ({DEBUG_FILE, "_B_reads.txt"}, "w");
            fd_w_a = $fopen ({DEBUG_FILE, "_A_writes.txt"}, "w");
            fd_w_b = $fopen ({DEBUG_FILE, "_B_writes.txt"}, "w");
        end

    end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// A PORT /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always_ff @(posedge clk) begin
        if (enA_i == 1'b1) begin
            ///////////////////////////// Writes  ///////////////////////////////////////////
            if (weA_i != '0) begin
                if (weA_i[3] == 1'b1) begin                                 // Store Word(4 bytes)
                    RAM[addrA_i+3] <= dataA_i[31:24];
                end 
                if (weA_i[2] == 1'b1) begin                                 // Store Word(4 bytes)
                    RAM[addrA_i+2] <= dataA_i[23:16];
                end
                if (weA_i[1] == 1'b1) begin                                 // Store Half(2 bytes)
                    RAM[addrA_i+1] <= dataA_i[15:8];
                end
                if (weA_i[0] == 1'b1) begin                                 // Store Byte(1 byte)
                    RAM[addrA_i]   <= dataA_i[7:0];
                end

                if (DEBUG) begin
                    $fwrite(fd_w_a,"[%0d] ", $time);
                    if (weA_i[3] == 1'b1) $fwrite(fd_w_a,"%h ", dataA_i[31:24]); else $fwrite(fd_w_a,"-- ");
                    if (weA_i[2] == 1'b1) $fwrite(fd_w_a,"%h ", dataA_i[23:16]); else $fwrite(fd_w_a,"-- ");
                    if (weA_i[1] == 1'b1) $fwrite(fd_w_a,"%h ", dataA_i[15:8 ]); else $fwrite(fd_w_a,"-- ");
                    if (weA_i[0] == 1'b1) $fwrite(fd_w_a,"%h ", dataA_i[ 7:0 ]); else $fwrite(fd_w_a,"-- ");
                    $fwrite(fd_w_a," --> 0x%4h\n", addrA_i);
                end
            end 
            // Reads 
            else begin
                dataA_o[31:24] <= RAM[addrA_i+3];
                dataA_o[23:16] <= RAM[addrA_i+2];
                dataA_o[15:8]  <= RAM[addrA_i+1];
                dataA_o[7:0]   <= RAM[addrA_i];

                if (DEBUG) begin
                    if (addrA_i != '0) begin
                        $fwrite(fd_r_a,"[%0d] %h %h %h %h <-- 0x%4h\n", 
                            $time, RAM[addrA_i+3], RAM[addrA_i+2], RAM[addrA_i+1], RAM[addrA_i], addrA_i);
                    end
                end
            end
        end 
        else begin
            dataA_o <= '0;
        end
    end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// B PORT /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always_ff @(posedge clk) begin
        if (enB_i == 1'b1) begin
            ///////////////////////////// Writes  ///////////////////////////////////////////
            if (weB_i != '0) begin
                if (weB_i[3] == 1'b1) begin                                 // Store Word(4 bytes)
                    RAM[addrB_i+3] <= dataB_i[31:24];
                end 
                if (weB_i[2] == 1'b1) begin                                 // Store Word(4 bytes)
                    RAM[addrB_i+2] <= dataB_i[23:16];
                end
                if (weB_i[1] == 1'b1) begin                                 // Store Half(2 bytes)
                    RAM[addrB_i+1] <= dataB_i[15:8];
                end
                if (weB_i[0] == 1'b1) begin                                 // Store Byte(1 byte)
                    RAM[addrB_i]   <= dataB_i[7:0];
                end

                if (DEBUG) begin
                    $fwrite(fd_w_b,"[%0d] ", $time);
                    if (weB_i[3] == 1'b1) $fwrite(fd_w_b,"%h ", dataB_i[31:24]); else $fwrite(fd_w_b,"-- ");
                    if (weB_i[2] == 1'b1) $fwrite(fd_w_b,"%h ", dataB_i[23:16]); else $fwrite(fd_w_b,"-- ");
                    if (weB_i[1] == 1'b1) $fwrite(fd_w_b,"%h ", dataB_i[15:8]);  else $fwrite(fd_w_b,"-- ");
                    if (weB_i[0] == 1'b1) $fwrite(fd_w_b,"%h ", dataB_i[7:0]);   else $fwrite(fd_w_b,"-- ");
                    $fwrite(fd_w_b," --> 0x%4h\n", addrB_i);
                end
            end 
            // Reads 
            else begin
                dataB_o[31:24] <= RAM[addrB_i+3];
                dataB_o[23:16] <= RAM[addrB_i+2];
                dataB_o[15:8]  <= RAM[addrB_i+1];
                dataB_o[7:0]   <= RAM[addrB_i];

                if (DEBUG) begin
                    if (addrB_i != '0) begin
                        $fwrite(fd_r_b,"[%0d] %h %h %h %h <-- 0x%4h\n", 
                            $time, RAM[addrB_i+3], RAM[addrB_i+2], RAM[addrB_i+1], RAM[addrB_i], addrB_i);
                    end
                end
            end
        end 
        else begin
            dataB_o <= '0;
        end
    end

endmodule
