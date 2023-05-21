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
    input   iType_e         instruction_operation_i,
    input   logic           killed_i,
    input   logic [31:0]    immediate_i,
    input   logic [31:0]    pc_i,

    output  logic [31:0]    predict_branch_taken_o,
    output  logic [31:0]    predict_branch_pc_o
);

    logic   inconditional_branch, conditional_branch;
    logic   negative_offset, conditional_branch_taken;

    always_comb begin
        if (executionUnit_e'(instruction_operation_i[5:3]) == BRANCH_UNIT) begin
            if (instruction_operation_i == JAL) begin
                inconditional_branch    <= 1'b1;
                conditional_branch      <= 1'b0;
            end
            else if (instruction_operation_i == JALR) begin
                inconditional_branch    <= 1'b0;
                conditional_branch      <= 1'b0;
            end
            else begin
                inconditional_branch    <= 1'b0;
                conditional_branch      <= 1'b1;
            end
        end
        else begin
            inconditional_branch    <= 1'b0;
            conditional_branch      <= 1'b0;
        end
    end

    assign negative_offset          = immediate_i[31];
    assign conditional_branch_taken = conditional_branch   & negative_offset;
    assign predict_branch_taken_o   = (inconditional_branch | conditional_branch_taken) & !killed_i;

    assign predict_branch_pc_o      = pc_i + immediate_i;

endmodule
