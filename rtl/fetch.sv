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
    input   logic           sys_reset,
    input   logic           enable_i,


    input   logic           jump_i,
    input   logic [31:0]    jump_target_i,

    input   logic [31:0]    mtvec_i,
    input   logic [31:0]    mepc_i,
    input   logic           exception_raised_i,
    input   logic           machine_return_i,
    input   logic           interrupt_ack_i,
    input   logic           hazard_i,
    
    output  logic           jump_misaligned_o,
    output  logic           jumped_o,
    output  logic [31:0]    instruction_address_o,
    output  logic [31:0]    pc_o,
    output  logic  [2:0]    tag_o
);

    logic [31:0] pc;
    logic [31:0] pc_r;
    logic  [2:0] next_tag, current_tag;
    logic jump_misaligned;
    logic [31:0] last_pc;
    logic [31:0] last_pc_o;

    logic jumped;
    logic jumped_r;

    logic enable;

    assign enable = enable_i || jumped;


//////////////////////////////////////////////////////////////////////////////
// PC Control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n | sys_reset) begin
            pc <= start_address;
            jump_misaligned <= 1'b0;
        end
        else if (machine_return_i == 1'b1) begin                              
            pc <= {mepc_i[31:2], 2'b00};
            if (mepc_i[1:0] != '0)
                jump_misaligned <= 1'b1;
        end
        else if ((exception_raised_i | interrupt_ack_i) == 1'b1) begin
            pc <= {mtvec_i[31:2], 2'b00};
            if (mtvec_i[1:0] != '0)
                jump_misaligned <= 1'b1;
        end
        else if (jump_i == 1'b1) begin
            pc <= {jump_target_i[31:2], 2'b00};
            if (jump_target_i[1:0] != '0)
                jump_misaligned <= 1'b1;
        end
        else if (enable == 1'b1 && (!hazard_i || jumped_r)) begin
            pc <= pc + 4;
            jump_misaligned <= 1'b0;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            last_pc <= '0;
            last_pc_o <= '0;
        end
        else if (enable == 1'b1) begin
            last_pc <= pc;
            last_pc_o <= pc_o;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Sensitive Outputs 
//////////////////////////////////////////////////////////////////////////////


    assign jumped = machine_return_i || exception_raised_i || interrupt_ack_i || jump_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_r <= 1'b1;
        else if (enable)
            jumped_r <= jumped;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_o <= 1'b1;
        else if (enable)
            jumped_o <= jumped_r;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc_r <= '0;
        else if (hazard_i && !jumped_r)
            pc_r <= last_pc;
        else if (enable == 1'b1)
            pc_r <= pc;
    end

    assign pc_o = (hazard_i && !jumped_o) ? last_pc_o : pc_r;

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

    logic [2:0] last_tag;

    always_comb begin
        if (hazard_i && !jumped_r || !enable) begin
            instruction_address_o = last_pc;
            tag_o = last_tag;
        end
        else begin
            instruction_address_o = pc;
            tag_o = current_tag;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// TAG Calculator 
//////////////////////////////////////////////////////////////////////////////


    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            current_tag <= '0;
            next_tag    <= '0;
        end
        else if (jumped) begin
            next_tag    <= current_tag + 1'b1;
        end
        else if (enable == 1'b1) begin
            current_tag <= next_tag;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            last_tag <= '0;
        end
        else begin
            last_tag <= current_tag;
        end
    end
    
endmodule
