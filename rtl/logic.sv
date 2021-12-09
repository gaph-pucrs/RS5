/*!\file logic.sv
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
 * Logic Module of Execute Unit.
 *
 * \detailed
 * Logic is a module that composes the Execute unit of the PUCRS-RV 
 * processor and is responsible for performing operations such as 
 * ANDs, ORs and XORs.
 */

import my_pkg::*;

module logicUnit(
    input logic         clk,
    input logic [31:0]  opA,
    input logic [31:0]  opB,
    input instruction_type i,
    output logic [31:0] result_out);

    logic [31:0] result;

    always_comb
        if(i==OP0)                      // XOR
            result <= opA ^ opB;
        else if(i==OP1)                 // OR
            result <= opA | opB;
        else                            // AND
            result <= opA & opB;

    always @(posedge clk)
        result_out <= result;



endmodule
