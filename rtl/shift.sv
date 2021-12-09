/*!\file shift.sv
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
 * Shift Module of Execute Unit.
 *
 * \detailed
 * Shift is a module that composes the Execute unit of the PUCRS-RV 
 * processor and is responsible for performing operations such as 
 * SLL, SRL and SRA.
 */
<<<<<<< Updated upstream
 
=======

>>>>>>> Stashed changes
import my_pkg::*;

module shiftUnit(
    input logic         clk,
    input logic [31:0]  opA,
    input logic [4:0]   opB,
    input instruction_type i,
    output logic [31:0] result_out);

    logic [31:0] result;

    always_comb 
        if(i==OP0)                                  // Logical Left Shift (SLL)
            result <= opA << opB;
        else if(i==OP1)                             // Logical Right Shift (SRL)
            result <= opA >> opB;
        else                                        // Arithmetic Right Shift  (SRA)
            result <= $signed(opA) >>> opB;

    always @(posedge clk)
        result_out <= result;


endmodule
