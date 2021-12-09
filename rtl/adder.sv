/*!\file adder.sv
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
 * Adder Module of Execute Unit.
 *
 * \detailed
 * Adder is a module that composes the Execute unit of the PUCRS-RV 
 * processor and is responsible for porforming operations such as 
 * ADDs, SUBs and SLTs.
 */

import my_pkg::*;

module adder(
    input logic         clk,
    input logic [31:0]  opA,
    input logic [31:0]  opB,
    input instruction_type i,
    output logic [31:0] result_out);

    logic [31:0] result;

    always_comb
        if(i==OP3)                              // Set if opA is less than opB (SLT)
            if($signed(opA) < $signed(opB))
                result <= 32'b1;
            else
                result <= 32'b0;

        else if(i==OP2)                         // Set if opA is less than opB UNSIGNED (SLTU)
            if($unsigned(opA) < $unsigned(opB))
                result <= 32'b1;
            else
                result <= 32'b0;

        else if(i==OP1)                         // SUBTRACT (SUB)
            result <= opA - opB;

        else                                    // ADD (ADD,ADDI and AUIPC)
            result <= opA + opB;

    always @(posedge clk)
        result_out <= result;

endmodule

