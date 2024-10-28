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
    parameter bit COMPRESSED    = 1'b0,
    parameter bit BRANCHPRED    = 1'b1
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           sys_reset,
    input   logic           enable_i,


    input   logic           jump_i,
    input   logic           jump_rollback_i,
    input   logic [31:0]    jump_target_i,
    input   logic           bp_take_i,
    input   logic [31:0]    bp_target_i,
    output  logic           jumping_o,
    output  logic           bp_rollback_o,

    input   logic [31:0]    mtvec_i,
    input   logic [31:0]    mepc_i,
    input   logic           exception_raised_i,
    input   logic           machine_return_i,
    input   logic           interrupt_ack_i,

    output  logic           jump_misaligned_o,
    output  logic [31:0]    instruction_address_o,
    input   logic [31:0]    instruction_data_i,
    output  logic [31:0]    instruction_o,
    output  logic [31:0]    pc_o,
    output  logic  [2:0]    tag_o
);

//////////////////////////////////////////////////////////////////////////////
// Instruction address control
//////////////////////////////////////////////////////////////////////////////

    logic        iaddr_continue;
    logic [31:0] iaddr_rollbacked;

    logic [31:0] iaddr_next;
    always_comb begin
        if (machine_return_i)
            iaddr_next = mepc_i;
        else if ((exception_raised_i || interrupt_ack_i))
            iaddr_next = mtvec_i;
        else if (jump_i)
            iaddr_next = jump_target_i;
        else if (jump_rollback_i)
            iaddr_next = iaddr_rollbacked;
        else if (bp_take_i)
            iaddr_next = bp_target_i;
        else if (iaddr_continue)
            iaddr_next = instruction_address_o + 32'd4;
        else
            iaddr_next = instruction_address_o;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_address_o <= start_address;
        else if (sys_reset)
            instruction_address_o <= start_address;
        else
            instruction_address_o <= {iaddr_next[31:2], 2'b00};
    end

////////////////////////////////////////////////////////////////////////////////
// Branch prediction
////////////////////////////////////////////////////////////////////////////////

    if (BRANCHPRED) begin : gen_bp_on
        logic bp_rollback_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_rollback_r <= 1'b0;
            else if (jump_rollback_i)
                bp_rollback_r <= 1'b1;
            else if (enable_i)
                bp_rollback_r <= 1'b0;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_rollback_o <= 1'b0;
            else if (enable_i)
                bp_rollback_o <= bp_rollback_r;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iaddr_rollbacked <= '0;
            else if (bp_take_i)
                iaddr_rollbacked <= iaddr_next;   // @todo What to do with compressed? :(
        end
    end
    else begin : gen_bp_off
        assign bp_rollback_o = 1'b0;
        assign iaddr_rollbacked = '0;
    end

////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

    logic jumped;
    assign jumped = machine_return_i || exception_raised_i || interrupt_ack_i || jump_i || bp_take_i;

    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_r <= 1'b1;
        else if (jumped || jump_rollback_i)
            jumped_r <= 1'b1;
        else if (enable_i)
            jumped_r <= 1'b0;
    end

    logic jumped_r2;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_r2 <= 1'b1;
        else if (enable_i)
            jumped_r2 <= jumped_r;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumping_o <= 1'b1;
        else if (jumped || jump_rollback_i || jumped_r)
            jumping_o <= 1'b1;
        else if (enable_i)
            jumping_o <= 1'b0;
    end

////////////////////////////////////////////////////////////////////////////////
// PC control
////////////////////////////////////////////////////////////////////////////////

    /**
     * We need to separate instruction address from PC to
     * 1. Identify misaligned fetches
     * 2. Allow 2-byte aligned 2/4-byte fetch in case of compressed
     */

    logic [31:0] pc;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc <= start_address;
        else if (jumped || jump_rollback_i)
            pc <= iaddr_next;
    end

    logic [31:0] pc_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc_r <= '0;
        else if (jumped_r)
            pc_r <= pc;
    end

    logic [ 2:0] pc_add;
    logic [31:0] pc_next;
    assign pc_next = pc_o + 32'(pc_add);

    logic [31:0] pc_update;
    /* pc_o is the PC of the fetched instruction */
    /* at the moment the instruction arrives     */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc_o <= '0;
        else if (enable_i)
            pc_o <= pc_update;
    end

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

    logic [31:0] idata_held;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            idata_held <= 32'h00000013;
        else if (!enable_i && enable_r)
            idata_held <= instruction_data_i;
    end

    logic [31:0] instruction_fetched;
    assign instruction_fetched = !enable_r ? idata_held : instruction_data_i;

    logic [31:0] instruction_next;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_o <= 32'h00000013;
        else if (enable_i)
            instruction_o <= instruction_next;
    end

//////////////////////////////////////////////////////////////////////////////
// TAG control
//////////////////////////////////////////////////////////////////////////////

    logic [2:0] tag;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            tag <= '0;
        else if (jumped)
            tag <= tag + 1'b1;
        else if (jump_rollback_i)
            tag <= tag - 1'b1;
    end

    logic [2:0] tag_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            tag_r <= '1;
        else if (enable_i)
            tag_r <= tag;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            tag_o <= '1;
        else if (enable_i)
            tag_o <= tag_r;
    end

////////////////////////////////////////////////////////////////////////////////
// Alignment control
////////////////////////////////////////////////////////////////////////////////

    if (COMPRESSED) begin : gen_compressed_on
        logic compressed;
        assign compressed = (instruction_o[1:0] != '1);

        logic unaligned;
        assign unaligned = pc_o[1];

        logic iaddr_hold;
        assign iaddr_hold = (!jumping_o && unaligned && compressed);

        logic iaddr_hold_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iaddr_hold_r <= 1'b0;
            else if (iaddr_hold)
                iaddr_hold_r <= 1'b1;
            else if (enable_i)
                iaddr_hold_r <= 1'b0;
        end

        logic unaligned_jump;
        assign unaligned_jump = pc_r[1];

        logic unaligned_jump_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                unaligned_jump_r <= 1'b0;
            else if (enable_i)
                unaligned_jump_r <= jumped_r2 && unaligned_jump;
        end

        logic [31:0] instruction_data_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                instruction_data_r <= 32'h00000013;
            else if (enable_i && ((jumped_r2 && unaligned_jump) || unaligned_jump_r || (unaligned || (compressed && !iaddr_hold_r))))
                instruction_data_r <= instruction_fetched;
        end

        logic [31:0] instruction_prefetched;
        assign instruction_prefetched = iaddr_hold_r ? instruction_data_r : instruction_fetched;

        assign jump_misaligned_o = unaligned_jump_r;
        assign iaddr_continue = enable_i && !iaddr_hold;
        assign pc_add = compressed ? 3'd2 : 3'd4;
       
        always_comb begin
            if (jumped_r2 && unaligned_jump)
                // Bubble on unaligned jump
                pc_update = '0;
            else if ((jumped_r2 && !unaligned_jump) || unaligned_jump_r)
                // Same as jumped instruction address on jump
                pc_update = pc_r;
            else
                // Independent control otherwise
                pc_update = pc_next;
        end

        always_comb begin
            if (jumped_r2 && unaligned_jump)
                // Bubble on unaligned jump
                instruction_next = 32'h00000013;
            else if (jumped_r2 && !unaligned_jump)
                // Disregard last instruction on jump
                instruction_next = instruction_fetched;
            else if (unaligned_jump_r || (unaligned && !compressed))
                // After bubble or unaligned 4-byte instruction we need the input of 2 fetches
                instruction_next = {instruction_fetched[15:0], instruction_data_r[31:16]};
            else if (!unaligned &&  compressed)
                // After aligned compressed the next instruction could be prefetched if the previous was compressed
                instruction_next = {instruction_prefetched[15:0], instruction_o[31:16]};
            else if (!unaligned && !compressed)
                // After aligned 4-byte instruction the next could be prefetched if the previous was compressed
                instruction_next = instruction_prefetched;
            else   // unaligned &&  compressed
                // After unaligned compressed, next instruction is surely prefetched
                instruction_next = instruction_data_r;
        end
    end
    else begin : gen_compressed_off
        assign jump_misaligned_o = 1'b0;
        assign iaddr_continue = enable_i;
        assign pc_add = 3'd4;
        assign pc_update = jumped_r2 ? pc_r : pc_next;
        assign instruction_next = instruction_fetched;
    end

endmodule
