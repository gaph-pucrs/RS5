/*!\file bypass.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  September 2021
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Bypass Module of Execute Unit.
 *
 * \detailed
 * Bypass is a module that composes the Execute unit of the PUCRS-RV 
 * processor and is responsible for Bypassing the operands in some 
 * operations such as LUI and NOP.
 */

import my_pkg::*;

module bypassUnit(                    // LUI, NOP and INVALID
    input logic         clk,
    input logic [31:0]  opA,
    output logic [31:0] result_out);

    always @(posedge clk)
        result_out <= opA;

endmodule

