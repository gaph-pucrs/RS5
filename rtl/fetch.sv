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
    input   logic [31:0]    jump_target_i,
    output  logic           jumping_o,
    
    /* Signals not used without BP */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           bp_take_i,
    input   logic           jump_rollback_i,
    input   logic [31:0]    bp_target_i,
    /* verilator lint_on UNUSEDSIGNAL */
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
    logic [31:0] iaddr_continue_next;

    logic        should_jump;
    logic [31:0] jump_target;

    logic [31:0] iaddr_advance;
    assign iaddr_advance = instruction_address_o + 32'd4;

    logic [31:0] iaddr_next;
    always_comb begin
        if (machine_return_i)
            iaddr_next = mepc_i;
        else if ((exception_raised_i || interrupt_ack_i))
            iaddr_next = mtvec_i;
        else if (should_jump)
            iaddr_next = jump_target;
        else if (iaddr_continue)
            iaddr_next = iaddr_continue_next;
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
// Jump control
////////////////////////////////////////////////////////////////////////////////

    logic jumped;
    assign jumped = machine_return_i || exception_raised_i || interrupt_ack_i || should_jump;

    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_r <= 1'b1;
        else if (jumped) // || jump_rollback_i
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
        else if (jumped || jumped_r) // || jump_rollback_i
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

    logic [31:0] iaddr_jumped;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            iaddr_jumped <= start_address;
        else if (jumped) // || jump_rollback_i
            iaddr_jumped <= iaddr_next;
    end

    logic [31:0] iaddr_jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            iaddr_jumped_r <= '0;
        else if (jumped_r)
            iaddr_jumped_r <= iaddr_jumped;
    end

    logic [ 2:0] pc_add;
    logic [31:0] pc;
    logic [31:0] pc_next;
    logic [31:0] pc_update;

    assign pc_next = pc + 32'(pc_add);

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

    logic [2:0] tag_next;
    logic [2:0] tag;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            tag <= '0;
        else
            tag <= tag_next;
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
// Branch prediction
////////////////////////////////////////////////////////////////////////////////

    /* Only used with BP, but needed for BP + C */
    /* verilator lint_off UNUSEDSIGNAL */
    logic bp_rollback_r;
    logic should_rollback;
    logic [31:0] iaddr_not_jumped;
    /* verilator lint_on UNUSEDSIGNAL*/

    if (BRANCHPRED) begin : gen_bp_on
        logic [31:0] iaddr_rollbacked;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iaddr_rollbacked <= '0;
            else if (bp_take_i)
                iaddr_rollbacked <= iaddr_not_jumped;
        end

        logic jump_rollback_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                jump_rollback_r <= 1'b0;
            else if (jump_rollback_i)
                jump_rollback_r <= 1'b1;
            else if (enable_i || enable_r)
                jump_rollback_r <= 1'b0;
        end

        assign should_rollback = jump_rollback_i || (jump_rollback_r && !enable_r);

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_rollback_r <= 1'b0;
            else if (enable_i)
                bp_rollback_r <= should_rollback;
        end

        logic [31:0] pc_rollbacked;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                pc_rollbacked <= '0;
            else if (bp_rollback_r)
                pc_rollbacked <= pc_o;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_rollback_o <= 1'b0;
            else if (enable_i)
                bp_rollback_o <= bp_rollback_r;
        end

        always_comb begin
            if (jumped && !jump_rollback_i)
                tag_next = tag + 1'b1;
            else if (jump_rollback_i && !jumped)
                tag_next = tag - 1'b1;
            else
                tag_next = tag;
        end

        assign pc = bp_rollback_o ? pc_rollbacked : pc_o;
        assign should_jump = jump_i || (enable_i && bp_take_i);
        assign jump_target = jump_i ? jump_target_i : bp_target_i;
        assign iaddr_continue_next = should_rollback ? iaddr_rollbacked : iaddr_advance;
    end
    else begin : gen_bp_off
        assign pc = pc_o;
        assign bp_rollback_r = 1'b0;
        assign should_rollback = 1'b0;
        assign bp_rollback_o = 1'b0;
        assign should_jump = jump_i;
        assign jump_target = jump_target_i;
        assign tag_next = jumped ? (tag + 1'b1) : tag;
        assign iaddr_continue_next = iaddr_advance;
    end

////////////////////////////////////////////////////////////////////////////////
// Alignment control
////////////////////////////////////////////////////////////////////////////////

    if (COMPRESSED) begin : gen_compressed_on
        /* We only use some bits of this signal with this name */
        /* verilator lint_off UNUSEDSIGNAL */
        logic [31:0] instruction;
        /* verilator lint_on UNUSEDSIGNAL */
        logic iaddr_hold;
        logic realign_jump;
        logic update_inst_r;

        logic compressed;
        assign compressed = (instruction[1:0] != '1);

        logic unaligned;
        assign unaligned = pc[1];

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
        assign unaligned_jump = iaddr_jumped_r[1];

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
            else if (enable_i && update_inst_r)
                instruction_data_r <= instruction_fetched;
        end

        logic [31:0] instruction_prefetched;
        assign instruction_prefetched = iaddr_hold_r ? instruction_data_r : instruction_fetched;

        assign pc_add = compressed ? 3'd2 : 3'd4;
        assign jump_misaligned_o = realign_jump;
       
        always_comb begin
            if (jumped_r2 && unaligned_jump)
                // Bubble on unaligned jump
                pc_update = '0;
            else if ((jumped_r2 && !unaligned_jump) || realign_jump)
                // Same as jumped instruction address on jump
                pc_update = iaddr_jumped_r;
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
            else if (realign_jump || (unaligned && !compressed))
                // After bubble or unaligned 4-byte instruction we need the input of 2 fetches
                instruction_next = {instruction_fetched[15:0], instruction_data_r[31:16]};
            else if (!unaligned &&  compressed)
                // After aligned compressed the next instruction could be prefetched if the previous was compressed
                instruction_next = {instruction_prefetched[15:0], instruction[31:16]};
            else if (!unaligned && !compressed)
                // After aligned 4-byte instruction the next could be prefetched if the previous was compressed
                instruction_next = instruction_prefetched;
            else   // unaligned &&  compressed
                // After unaligned compressed, next instruction is surely prefetched
                instruction_next = instruction_data_r;
        end

        if (BRANCHPRED) begin : gen_compressed_bp
            logic [31:0] idata_rollbacked;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    idata_rollbacked <= 32'h00000013;
                else if (bp_rollback_r)
                    idata_rollbacked <= instruction_o;
            end

            assign iaddr_hold = ((!(jumping_o && !should_rollback && !bp_rollback_r) && unaligned && compressed) || (iaddr_hold_r && bp_rollback_r)) && !(iaddr_hold_r && bp_rollback_o);
            assign iaddr_continue = enable_i && (should_rollback || !iaddr_hold);
            assign instruction = bp_rollback_o ? idata_rollbacked : instruction_o;
            assign iaddr_not_jumped = iaddr_hold ? instruction_address_o : iaddr_advance;
            assign realign_jump = unaligned_jump_r && !bp_rollback_o;
            assign update_inst_r = realign_jump || (jumped_r2 && unaligned_jump && !bp_rollback_r) || ((unaligned || (compressed && !iaddr_hold_r)) && !bp_rollback_r);
        end
        else begin : gen_compressed_wo_bp
            assign iaddr_hold = !jumping_o && unaligned && compressed;
            assign iaddr_continue = enable_i && !iaddr_hold;
            assign instruction = instruction_o;
            assign iaddr_not_jumped = '0;
            assign realign_jump = unaligned_jump_r;
            assign update_inst_r = realign_jump || (jumped_r2 && unaligned_jump) || (unaligned || (compressed && !iaddr_hold_r));
        end
    end
    else begin : gen_compressed_off
        assign jump_misaligned_o = 1'b0;
        assign iaddr_continue = enable_i;
        assign pc_add = 3'd4;
        assign pc_update = jumped_r2 ? iaddr_jumped_r : pc_next;
        assign instruction_next = instruction_fetched;
        assign iaddr_not_jumped = iaddr_advance;
    end

endmodule
