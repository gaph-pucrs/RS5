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
    parameter int    MEM_WIDTH  = 65536,
    parameter int    BUS_WIDTH  = 32,
    parameter string BIN_FILE   = "../app/baremetal/tests/riscv-tests/test.bin"
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

    initial begin
        int fd;
        fd = $fopen (BIN_FILE, "r");
        if (fd == '0) begin
            $display("[%d] [RAM_mem] ERROR: %s not found.", $time(), BIN_FILE);
            $finish();
        end

        void'($fread(RAM, fd));
        $fclose(fd);
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
        end
    end

    always_ff @(posedge clk) begin
        if (enB_i == 1'b1) begin
            for (int i = 0; i < (BUS_WIDTH/8); i++) begin
                if (weB_i[i] == 1'b1) begin                                 // Store Word(4 bytes)
                    /* verilator lint_off WIDTHEXPAND */
                    RAM[addrB_i+i] <= dataB_i[(8*i)+:8];
                    /* verilator lint_on  WIDTHEXPAND */
                end
            end
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
            end
        end
    end

    always_ff @(posedge clk) begin
        if (enB_i == 1'b1) begin
            if (weB_i == '0) begin
                for (int i = 0; i < (BUS_WIDTH/8); i++) begin
                /* verilator lint_off WIDTHEXPAND */
                    dataB_o[(8*i)+:8] <= RAM[addrB_i+i];
                /* verilator lint_on  WIDTHEXPAND */
                end
            end
        end
    end

endmodule
