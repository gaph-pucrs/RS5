/*!\file fetch.sv
 * PUC-RS5 VERSION - 1.0.0 - Public Release
 *
 * Distribution:  March 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Fetch Unit is the first stage of the processor core and fetch the instruction in memory.
 *
 * \detailed
 * Fetch Unit is the first stage of the PUC-RS5 processor core. It has an
 * internal loop that contains the Program Counter(PC) that is increased by four 
 * on a new clock cycle or is replaced by a new address in case of a branch. 
 * It has a internal tag calculator that is increased in branchs and mantained
 * in regular flows, the tag leaves the unit with the instruction fetched.
 */

module fetch  #(parameter start_address = 32'b0)(  //Generic start address
    input   logic           clk,
    input   logic           reset,
    input   logic           stall,

    input   logic           hazard_i,
    input   logic           jump_i,
    input   logic [31:0]    jump_target_i,

    input   logic           predict_branch_taken_i,
    input   logic [31:0]    predict_branch_pc_i,
    input   logic [31:0]    predict_branch_pc_next_i,
    input   logic           predict_jump_taken_i,
    input   logic [31:0]    predict_jump_pc_i,
    input   logic [31:0]    predict_jump_pc_next_i,

    
    output  logic [31:0]    instruction_address_o,
    output  logic [31:0]    pc_o,
    output  logic [2:0]     tag_o,

    input   logic [31:0]    mtvec_i,
    input   logic [31:0]    mepc_i,
    input   logic           exception_raised_i,
    input   logic           machine_return_i,
    input   logic           interrupt_ack_i
);

    logic [31:0] pc;
    logic  [2:0] next_tag, current_tag;

//////////////////////////////////////////////////////////////////////////////
// PC Control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset) begin
            pc <= start_address;
        end
        else if (machine_return_i) begin                              
            pc <= mepc_i;
        end
        else if (exception_raised_i | interrupt_ack_i) begin                               
            pc <= mtvec_i;
        end
        else if (jump_i) begin
            pc <= jump_target_i;
        end
        else if (predict_branch_taken_i) begin
            pc <= predict_branch_pc_i + 4;
        end
        else if (predict_jump_taken_i) begin
            pc <= predict_jump_pc_i + 4;
        end
        else if (~(hazard_i | stall)) begin
            pc <= pc + 4;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Sensitive Outputs 
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (~(hazard_i | stall)) begin
            case({predict_branch_taken_i, predict_jump_taken_i})
                2'b10:      pc_o <= predict_branch_pc_i;
                2'b01:      pc_o <= predict_jump_pc_i;
                default:    pc_o <= pc;
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Non-Sensitive Outputs 
//////////////////////////////////////////////////////////////////////////////
    always_comb begin
        case({predict_branch_taken_i, predict_jump_taken_i})
            2'b10:      instruction_address_o <= predict_branch_pc_i;
            2'b01:      instruction_address_o <= predict_jump_pc_i;
            default:    instruction_address_o <= pc;
        endcase
    end

    assign tag_o = current_tag;

//////////////////////////////////////////////////////////////////////////////
// TAG Calculator 
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset) begin
            current_tag <= 0;
            next_tag <= 0;
        end
        else if (jump_i | exception_raised_i | machine_return_i | interrupt_ack_i) begin
            next_tag <= current_tag + 1;
        end
        else if (~(hazard_i | stall)) begin
            current_tag <= next_tag;
        end
    end
endmodule
