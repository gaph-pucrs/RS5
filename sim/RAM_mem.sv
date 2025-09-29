/*!\file ram.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  OCtober 2023
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
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

`include "../rtl/RS5_pkg.sv"

module RAM_mem
    import RS5_pkg::*;
#(
`ifndef SYNTH
    parameter        DEBUG      = 0,
    parameter string DEBUG_PATH = "./debug/",
`endif
    parameter int    MEM_WIDTH  = 65536,
    parameter int    BUS_WIDTH  = 32,
    parameter string BIN_FILE   = "../app/berkeley_suite/test.bin"
)
(
    input  logic                             clk,

    input  logic                             enA_i,
    input  logic [BUS_WIDTH/8-1:0]           weA_i,
    input  logic [($clog2(MEM_WIDTH) - 1):0] addrA_i,
    input  logic [BUS_WIDTH-1:0]             dataA_i,
    output logic [BUS_WIDTH-1:0]             dataA_o,

    input  logic                             enB_i,
    input  logic [BUS_WIDTH/8-1:0]           weB_i,
    input  logic [($clog2(MEM_WIDTH) - 1):0] addrB_i,
    input  logic [BUS_WIDTH  -1:0]           dataB_i,
    output logic [BUS_WIDTH  -1:0]           dataB_o
);

    reg [7:0] RAM [0:MEM_WIDTH-1];
    int fd;
`ifndef SYNTH
    int fd_r_a, fd_r_b, fd_w_a, fd_w_b;
`endif

    initial begin
        fd = $fopen (BIN_FILE, "r");
        if (fd == '0) begin
            $display("[%d] [RAM_mem] ERROR: %s not found.", $time(), BIN_FILE);
            $finish();
        end

        void'($fread(RAM, fd));

    `ifndef SYNTH
        if (DEBUG) begin
            fd_r_a = $fopen ({DEBUG_PATH, "_A_reads.txt"}, "w");
            fd_r_b = $fopen ({DEBUG_PATH, "_B_reads.txt"}, "w");
            fd_w_a = $fopen ({DEBUG_PATH, "_A_writes.txt"}, "w");
            fd_w_b = $fopen ({DEBUG_PATH, "_B_writes.txt"}, "w");
        end
    `endif
    end

    /* Write */
    always_ff @(posedge clk) begin
        if (enA_i == 1'b1) begin
            for (int i = 0; i < (BUS_WIDTH/8); i++) begin
                if (weA_i[i] == 1'b1) begin                                 // Store Word(4 bytes)
            /* verilator lint_off WIDTHEXPAND */
                    RAM[addrA_i+i] <= dataA_i[(8*i)+:8];
            /* verilator lint_on  WIDTHEXPAND */
                end
            end

        `ifndef SYNTH
            if (DEBUG) begin
                if (weA_i != '0) begin
                    $fwrite(fd_w_a,"[%0d] ", $time);
                    for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                        if (weA_i[i] == 1'b1) begin
                            $fwrite(fd_w_a,"%h ", dataA_i[(8*i)+:8]);
                        end
                        else begin
                            $fwrite(fd_w_a,"-- ");
                        end
                    end
                    $fwrite(fd_w_a," --> 0x%4h\n", addrA_i);
                end
            end
        `endif
        end

        if (enB_i == 1'b1) begin
            for (int i = 0; i < (BUS_WIDTH/8); i++) begin
                if (weB_i[i] == 1'b1) begin                                 // Store Word(4 bytes)
                /* verilator lint_off WIDTHEXPAND */
                    RAM[addrB_i+i] <= dataB_i[(8*i)+:8];
                /* verilator lint_on  WIDTHEXPAND */
                end
            end

        `ifndef SYNTH
            if (DEBUG) begin
                if (weB_i != '0) begin
                    $fwrite(fd_w_b,"[%0d] ", $time);
                    for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                        if (weB_i[i] == 1'b1) begin
                            $fwrite(fd_w_b,"%h ", dataB_i[(8*i)+:8]);
                        end
                        else begin
                            $fwrite(fd_w_b,"-- ");
                        end
                    end
                    $fwrite(fd_w_b," --> 0x%4h\n", addrB_i);
                end
            end
        `endif
        end
    end

    /* Read */
    always_ff @(posedge clk) begin
        if (enA_i == 1'b1) begin
            if (weA_i == '0) begin
                for (int i = 0; i < (BUS_WIDTH/8); i++) begin
                /* verilator lint_off WIDTHEXPAND */
                    dataA_o[(8*i)+:8] <= RAM[addrA_i+i];
                /* verilator lint_on  WIDTHEXPAND */
                end

            `ifndef SYNTH
                if (DEBUG) begin
                    if (addrA_i != '0) begin
                        $fwrite(fd_r_a,"[%0d] ", $time);
                        for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                        /* verilator lint_off WIDTHEXPAND */
                            $fwrite(fd_r_a,"%h ", RAM[addrA_i+i]);
                        /* verilator lint_on  WIDTHEXPAND */
                        end
                        $fwrite(fd_r_a," <-- 0x%4h\n", addrA_i);
                    end
                end
            `endif
            end
        end

        if (enB_i == 1'b1) begin
            if (weB_i == '0) begin
                for (int i = 0; i < (BUS_WIDTH/8); i++) begin
                /* verilator lint_off WIDTHEXPAND */
                    dataB_o[(8*i)+:8] <= RAM[addrB_i+i];
                /* verilator lint_on  WIDTHEXPAND */
                end

            `ifndef SYNTH
                if (DEBUG) begin
                    if (addrB_i != '0) begin
                        $fwrite(fd_r_b,"[%0d] ", $time);
                        for (int i = (BUS_WIDTH/8)-1; i >= 0; i--) begin
                        /* verilator lint_off WIDTHEXPAND */
                            $fwrite(fd_r_b,"%h ", RAM[addrB_i+i]);
                        /* verilator lint_on  WIDTHEXPAND */
                        end
                        $fwrite(fd_r_b," <-- 0x%4h\n", addrB_i);
                    end
                end
            `endif
            end
        end
    end

endmodule
