/*!\file fetch.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
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
 * Fetch Unit is the first stage of the processor core and fetch the instruction in memory.
 *
 * \detailed
 * Fetch Unit is the first stage of the RS5 processor core. It has an
 * internal loop that contains the Program Counter(PC) that is increased by four 
 * on a new clock cycle or is replaced by a new address in case of a branch. 
 * It has a internal tag calculator that is increased in branches and mantained
 * in regular flows, the instruction fetched leaves arrives at next stage alongside
 * its associated tag.
 */

module fetch  #(parameter start_address = 32'b0)(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           enable,

    input   logic           jump_i,
    input   logic [31:0]    jump_target_i,

    input   logic [31:0]    mtvec_i,
    input   logic [31:0]    mepc_i,
    input   logic           exception_raised_i,
    input   logic           machine_return_i,
    input   logic           interrupt_ack_i,
    
    output  logic           jump_misaligned_o,
    output  logic [31:0]    instruction_address_o,
    output  logic [31:0]    pc_o,
    output  logic  [2:0]    tag_o
);

    logic [31:0] pc;
    logic  [2:0] next_tag, current_tag;
    logic jump_misaligned;

//////////////////////////////////////////////////////////////////////////////
// PC Control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc <= start_address;
            jump_misaligned <= 1'b0;
        end
        else if (machine_return_i == 1'b1) begin                              
            pc <= {mepc_i[31:2], 2'b00};
            if (mepc_i[1] == 1'b1)
                jump_misaligned <= 1'b1;
        end
        else if ((exception_raised_i | interrupt_ack_i) == 1'b1) begin
            pc <= {mtvec_i[31:2], 2'b00};
            if (mtvec_i[1] == 1'b1)
                jump_misaligned <= 1'b1;
        end
        else if (jump_i == 1'b1) begin
            pc <= {jump_target_i[31:2], 2'b00};
            if (jump_target_i[1] == 1'b1)
                jump_misaligned <= 1'b1;
        end
        else if (enable == 1'b1) begin
            pc <= pc + 4;
            jump_misaligned <= 1'b0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Sensitive Outputs 
//////////////////////////////////////////////////////////////////////////////
    
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_o <= '0;
        end
        else if (enable == 1'b1) begin
            pc_o <= pc;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jump_misaligned_o <= '0;
        end
        else begin
            jump_misaligned_o <= jump_misaligned;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Non-Sensitive Outputs 
//////////////////////////////////////////////////////////////////////////////

    assign instruction_address_o = pc;
    assign tag_o = current_tag;

//////////////////////////////////////////////////////////////////////////////
// TAG Calculator 
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            current_tag <= '1;  /* Start with invalid tag */
            next_tag    <= '0;
        end
        else if ((jump_i | exception_raised_i | machine_return_i | interrupt_ack_i) == 1'b1) begin
            next_tag    <= current_tag + 1'b1;
        end
        else if (enable == 1'b1) begin
            current_tag <= next_tag;
        end
    end
    
endmodule
