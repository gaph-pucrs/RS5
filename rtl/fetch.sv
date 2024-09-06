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

module fetch  #(
    parameter     start_address = 32'b0,
    parameter bit COMPRESSED    = 1'b0
)
(
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
    /* Used only with compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           hazard_i,
    /* verilator lint_on UNUSEDSIGNAL */

    output  logic           jump_misaligned_o,
    output  logic           jumped_o,
    output  logic           jumped_r_o,
    output  logic [31:0]    instruction_address_o,
    output  logic [31:0]    pc_o,
    output  logic  [2:0]    tag_o
);

    logic [31:0] pc;
    logic  [2:0] next_tag, current_tag;

    logic enable;

    /* Not used without compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    logic        jump_misaligned;
    logic [31:0] pc_r;
    logic [31:0] last_pc;
    logic [31:0] last_pc_o;
    /* verilator lint_on UNUSEDSIGNAL */

    logic jumped;
    logic jumped_r;

    assign enable = COMPRESSED ? (enable_i || jumped) : enable_i;

//////////////////////////////////////////////////////////////////////////////
// PC Control
//////////////////////////////////////////////////////////////////////////////

    if (COMPRESSED) begin : gen_pc_c
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                pc <= start_address;
                jump_misaligned <= 1'b0;
            end
            else if (sys_reset)begin
                pc <= start_address;
                jump_misaligned <= 1'b0;
            end
            else if (machine_return_i) begin
                pc <= {mepc_i[31:2], 1'b0, mepc_i[0]};
                if (mepc_i[1:0] != '0)
                    jump_misaligned <= 1'b1;
            end
            else if ((exception_raised_i || interrupt_ack_i)) begin
                pc <= {mtvec_i[31:2], 1'b0, mtvec_i[0]};
                if (mtvec_i[1:0] != '0)
                    jump_misaligned <= 1'b1;
            end
            else if (jump_i) begin
                pc <= {jump_target_i[31:2], 1'b0, jump_target_i[0]};
                if (jump_target_i[1:0] != '0)
                    jump_misaligned <= 1'b1;
            end
            else if (enable && !hazard_i) begin
                pc <= pc + 4;
                jump_misaligned <= 1'b0;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                last_pc <= '0;
                last_pc_o <= '0;
            end
            else if (enable) begin
                last_pc <= pc;
                last_pc_o <= pc_o;
            end
        end
    end
    else begin : gen_pc_nc
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                pc <= start_address;
            end
            else if (sys_reset) begin
                pc <= start_address;
            end
            else if (machine_return_i) begin
                pc <= mepc_i;
            end
            else if ((exception_raised_i || interrupt_ack_i)) begin
                pc <= mtvec_i;
            end
            else if (jump_i) begin
                pc <= jump_target_i;
            end
            else if (enable) begin
                pc <= pc + 4;
            end
        end

        assign last_pc   = '0;
        assign last_pc_o = '0;
        assign jump_misaligned = 1'b0;
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

    assign jumped_r_o = jumped_r;

    if (COMPRESSED) begin : gen_jmp_c

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                pc_r <= '0;
            else if (hazard_i)
                pc_r <= last_pc;
            else if (enable)
                pc_r <= pc;
        end

        assign pc_o = (hazard_i) ? last_pc_o : pc_r;

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                jump_misaligned_o <= '0;
            end
            else begin
                jump_misaligned_o <= jump_misaligned;
            end
        end
    end
    else begin : gen_jmp_nc
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                pc_o <= '0;
            end
            else if (enable) begin
                pc_o <= pc;
            end
        end

        assign pc_r = '0;
        assign jump_misaligned_o = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// Non-Sensitive Outputs
//////////////////////////////////////////////////////////////////////////////

    /* Not used when compressed is disabled */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [2:0] last_tag;
    /* verilator lint_on UNUSEDSIGNAL */

    if (COMPRESSED) begin : gen_addr_c
        always_comb begin
            if (hazard_i || !enable) begin
                instruction_address_o = last_pc;
                tag_o = last_tag;
            end
            else begin
                instruction_address_o = pc;
                tag_o = current_tag;
            end
        end
    end
    else begin : gen_addr_nc
        assign last_tag = '0;
        assign instruction_address_o = pc;
        assign tag_o = current_tag;
    end

//////////////////////////////////////////////////////////////////////////////
// TAG Calculator
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            current_tag <= '1;
            next_tag    <= '0;
        end
        else if (jumped) begin
            next_tag    <= current_tag + 1'b1;
        end
        else if (enable) begin
            current_tag <= next_tag;
        end
    end

    if (COMPRESSED) begin : gen_tag_c
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                last_tag <= '0;
            end
            else begin
                last_tag <= current_tag;
            end
        end
    end

endmodule
