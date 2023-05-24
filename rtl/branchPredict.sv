/*!\file BranchPredict.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  May 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Defines a Branch Prediction Mechanism.
 *
 * \detailed
 * This implements static branch prediction. It takes an instruction and its PC and determines if
 * it's a branch or a jump and calculates its target. For jumps it will always predict taken. For
 * branches it will predict taken if the PC offset is negative.
 */

module branchPredict
    import my_pkg::*;
(
    input   logic [6:0]     instruction_opcode_i,
    input   logic           hazard_i,
    input   logic           killed_i,
    input   logic           jump_i,
    input   logic [31:0]    immediate_b_type_i,
    input   logic [31:0]    immediate_j_type_i,
    input   logic [31:0]    pc_i,
    input   logic           predicted_r,

    output  logic           predict_branch_taken_o,
    output  logic [31:0]    predict_branch_pc_o
);

    logic           inconditional_branch, conditional_branch;
    logic           negative_offset, conditional_branch_taken;
    logic [31:0]    immediate;

    always_comb begin
        if (instruction_opcode_i == 7'h6f) begin
            immediate               = immediate_j_type_i;
            inconditional_branch    = 1'b1;
            conditional_branch      = 1'b0;
        end
        else if (instruction_opcode_i == 7'h63) begin
            immediate               = immediate_b_type_i;
            inconditional_branch    = 1'b0;
            conditional_branch      = 1'b1;
        end
        else begin
            immediate               = '0;
            inconditional_branch    = 1'b0;
            conditional_branch      = 1'b0;
        end
    end

    assign negative_offset          = immediate[31];
    assign conditional_branch_taken = conditional_branch && negative_offset;
    assign predict_branch_taken_o   = (inconditional_branch || conditional_branch_taken) && !predicted_r && !killed_i && !jump_i && !hazard_i;

    assign predict_branch_pc_o      = pc_i + immediate;

endmodule
