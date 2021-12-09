/*!\file branch.sv
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
 * Branch Module of Execute Unit.
 *
 * \detailed
 * Branch is a module that composes the Execute unit of the PUCRS-RV 
 * processor and is responsible for performing operations such as 
 * JAL, JALR, and Conditional Branches(BEQ,BNE,etc).
 */

import my_pkg::*;

module branchUnit(
    input logic         clk,
    input logic [31:0]  opA,                        // In JALR is used to calculate the target and in conditional is used as condition
    input logic [31:0]  opB,                        // In JALR is used to calculate the target and in conditional is used as condition
    input logic [31:0]  offset,                     // Immediate OFFSET is added to PC value
    input logic [31:0]  NPC,                        // PC value
    input instruction_type i,                       // Instruction Type
    output logic [31:0] result_out,                 // Branch target
    output logic [31:0] result_jal,                 // Return addres to a JAL instruction (NPC+4)
    output logic        jump_out,                   // Signal that indicate a jump/branch
    output logic        we_out);                    // Wrtie enable to register bank (used only in JAL)

    logic [31:0]        result, sum;
    logic               jump, we_int;

///////////////////////////////////////////////// Result assign /////////////////////////////////////////////////////////////////////////////////////
    assign sum = opA + opB;                         // Generates the JALR target

    always_comb
        if(i==OP6)                                  // JAL
            result <= sum;                          // Branch target is Sum of opA and opB

        else if(i==OP7) begin                       // JALR
            result[31:1] <= sum[31:1];              // Branch target is opA+opB with
            result[0]<=0;                           // The less significant digit in 0

        end else                                    // Conditional Branches
            result <= NPC + offset;                 // Branch target is PC + immediate

///////////////////////////////////////////////// Genarates the branch signal ///////////////////////////////////////////////////////////////////////
    always_comb
      if(i==OP0)                                    // Branch if equals (BEQ)
        jump <= (opA == opB);
      else if(i==OP1)                               // Branch if not equal (BNE)
        jump <= (opA != opB);
      else if(i==OP2)                               // Branch if less than (BLT)
        jump <= ($signed(opA) < $signed(opB));
      else if(i==OP3)                               // Branch if less than unsigned (BLTU)
        jump <= ($unsigned(opA) < $unsigned(opB));
      else if(i==OP4)                               // Branch if greather or equals than (BGE)
        jump <= ($signed(opA) >= $signed(opB));
      else if(i==OP5)                               // Branch if greather or equals than unsigned (BGEU)
        jump <= ($unsigned(opA) >= $unsigned(opB));
      else if(i==OP6 || i==OP7)                     // Unconditional Branches
        jump <= 1;
      else
        jump <= 0;

///////////////////////////////////////////////// Write enable signal generator /////////////////////////////////////////////////////////////////////
    always_comb                                     // Register write enable is 1 in JAL and JALR instructions
        if(i==OP6 || i==OP7)
            we_int <= '1;
        else 
            we_int <= '0;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
   always @(posedge clk) begin
        result_out <= result;
        result_jal <= NPC+4;
        jump_out <= jump;
        we_out <= we_int;
     end

endmodule
