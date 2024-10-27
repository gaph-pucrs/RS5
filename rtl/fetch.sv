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
    /* verilator lint_off UNUSEDPARAM */
    parameter bit COMPRESSED    = 1'b0,
    /* verilator lint_on UNUSEDPARAM */
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

    logic compressed;
    assign compressed = (instruction_o[1:0] != '1);

    logic unaligned;
    assign unaligned = pc_o[1];

    logic jumped_r2;

    logic enable_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            enable_r <= '0;
        else
            enable_r <= enable_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Instruction address control
//////////////////////////////////////////////////////////////////////////////

    logic iaddr_hold;
    logic [31:0] pc_rollbacked;
    logic unaligned_jump;
    logic unaligned_jump_r;
    logic iaddr_hold_r;
    assign iaddr_hold = (!jumping_o && unaligned && compressed);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            iaddr_hold_r <= 1'b0;
        else if (iaddr_hold)
            iaddr_hold_r <= 1'b1;
        else if (enable_i)
            iaddr_hold_r <= 1'b0;
    end

    logic [31:0] iaddr_next;
    always_comb begin
        if (machine_return_i)
            iaddr_next = mepc_i;
        else if ((exception_raised_i || interrupt_ack_i))
            iaddr_next = mtvec_i;
        else if (jump_i)
            iaddr_next = jump_target_i;
        else if (jump_rollback_i)
            iaddr_next = pc_rollbacked;
        else if (bp_take_i)
            iaddr_next = bp_target_i;
        else if (enable_i && !iaddr_hold)
            iaddr_next = instruction_address_o + 4;
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

    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] iaddr_continue;
    /* verilator lint_on UNUSEDSIGNAL */
    assign iaddr_continue = '0;
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
                pc_rollbacked <= '0;
            else if (bp_take_i)
                pc_rollbacked <= iaddr_continue;   // @todo What to do with compressed? :(
        end
    end
    else begin : gen_bp_off
        assign bp_rollback_o = 1'b0;
        assign pc_rollbacked = '0;
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
    
    assign unaligned_jump = pc_r[1];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            unaligned_jump_r <= 1'b0;
        else if (enable_i)
            unaligned_jump_r <= jumped_r2 && unaligned_jump;
    end

    assign jump_misaligned_o = unaligned_jump_r;

    logic [2:0] pc_add;
    assign pc_add = compressed ? 3'd2 : 3'd4;

    logic [31:0] pc_next;
    assign pc_next = pc_o + 32'(pc_add);

    /* pc_o is the PC of the fetched instruction */
    /* at the moment the instruction arrives     */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_o <= '0;
        end
        else if (enable_i) begin
            if (jumped_r2) begin
                if (unaligned_jump)
                    pc_o <= '0;
                else
                    pc_o <= pc_r;
            end
            else if (unaligned_jump_r) begin
                pc_o <= pc_r;
            end
            else begin
                pc_o <= pc_next;
            end
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Data control
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] idata_held;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            idata_held <= 32'h00000013;
        else if (!enable_i && enable_r)
            idata_held <= instruction_data_i;
    end

    logic [31:0] instruction_fetched;
    assign instruction_fetched = !enable_r ? idata_held : instruction_data_i;

    logic [31:0] instruction_data_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_data_r <= 32'h00000013;
        else if (enable_i && ((jumped_r2 && unaligned_jump) || unaligned_jump_r || (unaligned || (compressed && !iaddr_hold_r))))
            instruction_data_r <= instruction_fetched;
    end

    logic [31:0] instruction_prefetched;
    assign instruction_prefetched = iaddr_hold_r ? instruction_data_r : instruction_fetched;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_o <= 32'h00000013;
        end
        else begin
            if (jumped_r2) begin
                if (unaligned_jump)
                    instruction_o <= 32'h00000013;
                else
                    instruction_o <= instruction_data_i;
            end
            else if (unaligned_jump_r) begin
                instruction_o <= {instruction_data_i[15:0], instruction_data_r[31:16]};
            end
            else if (enable_i) begin
                if      (!unaligned && !compressed)
                    instruction_o <= instruction_prefetched;
                else if (!unaligned &&  compressed) 
                    instruction_o <= {instruction_prefetched[15:0], instruction_o[31:16]};
                else if ( unaligned && !compressed)
                    instruction_o <= {instruction_fetched[15:0], instruction_data_r[31:16]};
                else  //  unaligned &&  compressed
                    instruction_o <= instruction_data_r;
            end
        end
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

endmodule
