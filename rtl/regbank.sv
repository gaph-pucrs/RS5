/*!\file regbank.sv
 * RS5 VERSION - 1.1 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Defines a Regbank with 32 regs of 32 bits.
 *
 * \detailed
 * The Register Bank is composed by 32 registers of 32 bits each.
 * It has two read ports and one write port, the registers are indexed by
 * direct codification . The ZERO(0) register is read-only and holds the
 * value 0 and the other 31 registers are read-write registers.
 */

`include "RS5_pkg.sv"

module regbank
    import RS5_pkg::*;
#(
`ifndef SYNTH
    parameter bit    DEBUG    = 1'b0,
    parameter string DBG_FILE = "./debug/regBank.txt"
`endif
)
(
    input   logic         clk,
    input   logic         reset_n,

    input   logic [4:0]   rs1,
    input   logic [4:0]   rs2,
    input   logic [4:0]   rd,
    input   logic         enable,
    input   logic [31:0]  data_i,
    output  logic [31:0]  data1_o,
    output  logic [31:0]  data2_o
);

    logic [31:0] regfile [31:0];

//////////////////////////////////////////////////////////////////////////////
// Output assignment
//////////////////////////////////////////////////////////////////////////////

    assign  data1_o = regfile[rs1],
            data2_o = regfile[rs2];

//////////////////////////////////////////////////////////////////////////////
// Reset and Write control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            for (int i = 0; i < 32; i++)
                regfile[i] <= '0;
        end
        else if (enable == 1'b1 && rd != '0) begin
            regfile[rd] <= data_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// DEBUG
//////////////////////////////////////////////////////////////////////////////
`ifndef SYNTH
    if (DEBUG) begin : gen_reg_dbg
        int fd;

    initial begin
        fd = $fopen (DBG_FILE, "w");
        if (fd == 0) begin
            $display("Error opening file %s", DBG_FILE);
        end
    end

        always_ff @(posedge clk) begin
            $fwrite(fd,"[%0d] %02d - %8h \t %02d - %8h\n", $time(), rs1, data1_o, rs2, data2_o);
            if (rd != '0 && enable == 1'b1) begin
                $fwrite(fd,"[%0d] --------------------------------- %02d - %8h\n", $time, rd, data_i);
            end
        end
    end
`endif

endmodule
