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
    input   logic [31:0]    instruction_data_i,
    output  logic [31:0]    instruction_o,
    output  logic [31:0]    pc_o,
    output  logic  [2:0]    tag_o
);

//////////////////////////////////////////////////////////////////////////////
// Instruction address and PC control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] pc;
    logic [31:0] pc_r;

    /* Not used without compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    logic jump_misaligned;
    /* verilator lint_on UNUSEDSIGNAL */


    if (COMPRESSED) begin : gen_pc_c

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                pc <= start_address;
                jump_misaligned <= 1'b0;
            end
            else if (sys_reset) begin
                pc <= start_address;
                jump_misaligned <= 1'b0;
            end
            else begin
                if (machine_return_i) begin
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
                else if (enable_i) begin
                    pc <= pc + 4;
                    jump_misaligned <= 1'b0;
                end
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
            else begin
                if (machine_return_i)
                    pc <= mepc_i;
                else if ((exception_raised_i || interrupt_ack_i))
                    pc <= mtvec_i;
                else if (jump_i)
                    pc <= jump_target_i;
                else if (enable_i)
                    pc <= pc + 4;
            end
        end
    end

    /* pc_r is the PC of the fetched instruction */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_r <= '0;
        end
        else if (enable_i) begin
            pc_r <= pc;
        end
    end

    /* pc_o is the PC of the fetched instruction */
    /* at the moment the instruction arrives     */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_o <= '0;
        end
        else if (enable_i) begin
            pc_o <= pc_r;
        end
    end

    assign instruction_address_o = pc;

////////////////////////////////////////////////////////////////////////////////
// Data control
////////////////////////////////////////////////////////////////////////////////
    
    logic enable_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            enable_r <= '0;
        else
            enable_r <= enable_i;
    end

    logic enable_negedge;
    assign enable_negedge = !enable_i && enable_r;

    logic [31:0] instruction_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_r <= '0;
        else if (enable_negedge)
            instruction_r <= instruction_data_i;
    end

    logic enable_posedge;
    assign enable_posedge = enable_i && !enable_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_o <= '0;
        end
        else begin
            if (enable_posedge)
                instruction_o <= instruction_r;
            else if (enable_i)
                instruction_o <= instruction_data_i;
        end
    end
    
////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

    logic jumped;
    assign jumped = machine_return_i || exception_raised_i || interrupt_ack_i || jump_i;

    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_r <= 1'b1;
        else
            jumped_r <= jumped;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_o <= 1'b1;
        else
            jumped_o <= jumped_r;
    end

    if (COMPRESSED) begin : gen_jmp_c
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
        assign jump_misaligned_o = 1'b0;
    end


    /* Only for compressed, ignore for now */
    assign jumped_r_o = jumped_r;

//////////////////////////////////////////////////////////////////////////////
// TAG control
//////////////////////////////////////////////////////////////////////////////

    logic [2:0] tag;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            tag <= '0;
        end
        else begin
            if (jumped)
                tag <= tag + 1'b1;
        end
    end

    logic [2:0] tag_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            tag_r <= '1;
        end
        else if (enable_i) begin
            tag_r <= tag;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            tag_o <= '1;
        end
        else if (enable_i) begin
            tag_o <= tag_r;
        end
    end

endmodule
