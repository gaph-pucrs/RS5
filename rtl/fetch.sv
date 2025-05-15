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
 */

module fetch  
    import RS5_pkg::*;
#(
    parameter     start_address = 32'b0,
    parameter bit   COMPRESSED = 1'b0,
    parameter bit   BRANCHPRED = 1'b1,    
    parameter mul_e MULEXT     = MUL_M,
    parameter bit   ZCBEnable  = 1'b0
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           sys_reset,
    input   logic           enable_i,

    input   logic           jump_i,
    input   logic           ctx_switch_i,
    /* Bits 1:0 unused without compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]    jump_target_i,
    input   logic [31:0]    ctx_switch_target_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output  logic           jumping_o,
    
    input   logic           bp_take_i,
    input   logic           jump_rollback_i,
    /* Bits 1:0 unused without BP */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]    bp_target_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output  logic           bp_rollback_o,

    output  logic           jump_misaligned_o,
    output  logic           compressed_o,
    output  logic [31:0]    instruction_address_o,
    input   logic [31:0]    instruction_data_i,
    output  logic [31:0]    instruction_o,
    output  logic [31:0]    pc_o
);

////////////////////////////////////////////////////////////////////////////////
// Flow control
////////////////////////////////////////////////////////////////////////////////

    logic [31:2] iaddr_rollback;

    logic [31:2] iaddr_advance;
    assign iaddr_advance = instruction_address_o[31:2] + 1'b1;

    logic [31:2] iaddr_jumped;
    always_comb begin
        if (ctx_switch_i)
            iaddr_jumped = ctx_switch_target_i[31:2];
        else if (jump_i)
            iaddr_jumped = jump_target_i[31:2];
        else if (BRANCHPRED && (bp_take_i || jump_rollback_i))
            iaddr_jumped = jump_rollback_i ? iaddr_rollback : bp_target_i[31:2];
        else
            iaddr_jumped = iaddr_advance;
    end

////////////////////////////////////////////////////////////////////////////////
// Instruction address control
////////////////////////////////////////////////////////////////////////////////

    logic jumped;
    logic iaddr_continue;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_address_o <= start_address;
        end
        else if (sys_reset) begin
            instruction_address_o <= start_address;
        end
        else begin
            if (jumped || jump_rollback_i || iaddr_continue)
                instruction_address_o <= {iaddr_jumped, 2'b00};
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jumped_r <= 1'b1;
        end
        else if (sys_reset) begin
            jumped_r <= 1'b1;
        end
        else begin
            if (jumped)
                jumped_r <= 1'b1;
            else if (enable_i || jump_rollback_i)
                jumped_r <= 1'b0;
        end
    end
    
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jumping_o <= 1'b1;
        end
        else if (sys_reset) begin
            jumping_o <= 1'b1;
        end
        else begin 
            if (jumped || (jumped_r && !jump_rollback_i))
                jumping_o <= 1'b1;
            else if (enable_i || jump_rollback_i)
                jumping_o <= 1'b0;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// PC control
////////////////////////////////////////////////////////////////////////////////

    logic [31:0] pc_update;
    logic [31:0] pc_jumped;

    logic [31:0] pc_jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc_jumped_r <= '0;
        else if (jumped_r || (!COMPRESSED && enable_i))
            pc_jumped_r <= pc_jumped;
    end

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
        else if (sys_reset)
            instruction_o <= 32'h00000013;
        else if (enable_i)
            instruction_o <= instruction_next;
    end

////////////////////////////////////////////////////////////////////////////////
// Branch prediction
////////////////////////////////////////////////////////////////////////////////

    /* Only used with BP, but needed for BP + C */
    /* verilator lint_off UNUSEDSIGNAL */
    logic        jump_rollback_r;
    logic [31:2] iaddr_fetched_adv;
    /* verilator lint_on UNUSEDSIGNAL*/

    if (BRANCHPRED) begin : gen_bp_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iaddr_fetched_adv <= '0;
            else if (enable_i && bp_take_i)
                iaddr_fetched_adv <= iaddr_advance;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                jump_rollback_r <= 1'b0;
            end
            else if (sys_reset) begin
                jump_rollback_r <= 1'b0;
            end
            else begin 
                if (jump_rollback_i)
                    jump_rollback_r <= 1'b1;
                else if (enable_i)
                    jump_rollback_r <= 1'b0;
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_rollback_o <= 1'b0;
            else if (sys_reset)
                bp_rollback_o <= 1'b0;
            else if (enable_i)
                bp_rollback_o <= jump_rollback_r;
        end

        assign jumped = ctx_switch_i || jump_i || (enable_i && bp_take_i);
    end
    else begin : gen_bp_off
        assign bp_rollback_o     = 1'b0;
        assign jumped            = ctx_switch_i || jump_i;
        assign iaddr_fetched_adv = '0;
    end

////////////////////////////////////////////////////////////////////////////////
// Alignment control
////////////////////////////////////////////////////////////////////////////////

    if (COMPRESSED) begin : gen_compressed_on
        /**
        * We need to separate instruction address from PC to allow 2-byte aligned 
        * 2/4-byte fetch in case of compressed
        */
        typedef enum logic [3:0] {
            NO_JMP = 4'(1 << 0),
            CTX_SW = 4'(1 << 1),
            JMP_XU = 4'(1 << 2),
            BP_DEC = 4'(1 << 3)
        } jmp_reason_t;

        logic [31:0] bp_target_r;

        jmp_reason_t jmp_reason;
        always_comb begin
            if (ctx_switch_i)
                jmp_reason = CTX_SW;
            else if (jump_i)
                jmp_reason = JMP_XU;
            else if (BRANCHPRED && enable_i && bp_take_i)
                jmp_reason = BP_DEC;
            else
                jmp_reason = NO_JMP;
        end

        jmp_reason_t jmp_reason_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                jmp_reason_r <= NO_JMP;
            else if (sys_reset)
                jmp_reason_r <= NO_JMP;
            else
                jmp_reason_r <= jmp_reason;
        end

        logic [31:0] ctx_switch_target_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                ctx_switch_target_r <= start_address;
            else if (ctx_switch_i)
                ctx_switch_target_r <= ctx_switch_target_i;
        end

        logic [31:0] jump_target_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                jump_target_r <= start_address;
            else if (sys_reset)
                jump_target_r <= start_address;
            else if (jump_i)
                jump_target_r <= jump_target_i;
        end

        always_comb begin
            unique case (jmp_reason_r)
                CTX_SW:  pc_jumped = ctx_switch_target_r;
                BP_DEC:  pc_jumped = BRANCHPRED ? bp_target_r : jump_target_r;
                default: pc_jumped = jump_target_r; /* JMP_XU, allows for 2-input mux when no BP */
            endcase
        end

        logic [ 2:0] pc_add;
        logic [31:0] pc;
        logic [31:0] pc_next;

        assign pc_next = pc + 32'(pc_add);

        /* We only use some bits of this signal with this name */
        /* verilator lint_off UNUSEDSIGNAL */
        logic [31:0] instruction;
        /* verilator lint_on UNUSEDSIGNAL */
        logic [31:0] instruction_word;
        logic [31:0] instruction_built;
        logic iaddr_hold;
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

        logic jumped_r2;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                jumped_r2 <= 1'b1;
            else if (sys_reset)
                jumped_r2 <= 1'b1;
            else if (enable_i)
                jumped_r2 <= jumped_r && !jump_rollback_i;
        end

        logic unaligned_jump;
        assign unaligned_jump = jumped_r2 && pc_jumped_r[1];

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                jump_misaligned_o <= 1'b0;
            else if (enable_i)
                jump_misaligned_o <= unaligned_jump;
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
        assign pc_update = (jumped_r2 || jump_misaligned_o) ? pc_jumped_r : pc_next;
       
        always_comb begin
            if (jumped_r2)
                // Disregard last instruction on jump
                instruction_built = instruction_fetched;
            else if (jump_misaligned_o || (unaligned && !compressed))
                // After bubble or unaligned 4-byte instruction we need the input of 2 fetches
                instruction_built = {instruction_fetched[15:0], instruction_data_r[31:16]};
            else if (!unaligned &&  compressed)
                // After aligned compressed the next instruction could be prefetched if the previous was compressed
                instruction_built = {instruction_prefetched[15:0], instruction[31:16]};
            else if (!unaligned && !compressed)
                // After aligned 4-byte instruction the next could be prefetched if the previous was compressed
                instruction_built = instruction_prefetched;
            else   // unaligned &&  compressed
                // After unaligned compressed, next instruction is surely prefetched
                instruction_built = instruction_data_r;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                instruction_word <= 32'h00000013;
            else if (enable_i)
                instruction_word <= instruction_built;
        end

        logic [31:0] instruction_decompressed;

        decompresser #(
            .MULEXT    (MULEXT),
            .ZCBEnable (ZCBEnable)
        ) decompresser (
            .instruction_i (instruction_built[15:0]),
            .instruction_o (instruction_decompressed)
        );

        logic next_compressed;
        assign next_compressed = (instruction_built[1:0] != '1);
        assign instruction_next = next_compressed ? instruction_decompressed : instruction_built;

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                compressed_o <= 1'b0;
            else if (enable_i)
                compressed_o <= next_compressed;
        end

        assign iaddr_continue = enable_i && !iaddr_hold;

        if (BRANCHPRED) begin : gen_compressed_bp
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    bp_target_r <= start_address;
                else if (enable_i && bp_take_i)
                    bp_target_r <= bp_target_i;
            end

            logic [31:0] pc_rollbacked;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    pc_rollbacked <= '0;
                else if (jump_rollback_r)
                    pc_rollbacked <= pc_o;
            end

            logic [31:0] idata_rollbacked;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    idata_rollbacked <= 32'h00000013;
                else if (jump_rollback_r)
                    idata_rollbacked <= instruction_word;
            end

            logic [31:2] iaddr_fetched;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    iaddr_fetched <= '0;
                else if (enable_i && bp_take_i)
                    iaddr_fetched <= instruction_address_o[31:2];
            end

            assign pc             = bp_rollback_o ? pc_rollbacked : pc_o;
            assign iaddr_hold     = ((!(jumping_o && !jump_rollback_i) && unaligned && (compressed && !jump_misaligned_o)) || (iaddr_hold_r && jump_rollback_r)) && !(iaddr_hold_r && bp_rollback_o);
            assign instruction    = bp_rollback_o ? idata_rollbacked : instruction_word;
            assign iaddr_rollback = iaddr_hold_r ? iaddr_fetched : iaddr_fetched_adv;
            assign update_inst_r  = jump_misaligned_o || unaligned_jump || ((unaligned || (compressed && !iaddr_hold_r)) && !jump_rollback_r);
        end
        else begin : gen_compressed_wo_bp
            assign pc             = pc_o;
            assign bp_target_r    = '0;
            assign iaddr_hold     = !jumping_o && unaligned && (compressed && !jump_misaligned_o);
            assign instruction    = instruction_word;
            assign iaddr_rollback = '0;
            assign update_inst_r  = jump_misaligned_o || unaligned_jump || (unaligned || (compressed && !iaddr_hold_r));
        end
    end
    else begin : gen_compressed_off
        assign pc_jumped         = instruction_address_o;
        assign jump_misaligned_o = 1'b0;
        assign iaddr_continue    = enable_i;
        assign pc_update         = pc_jumped_r;
        assign instruction_next  = instruction_fetched;
        assign iaddr_rollback    = iaddr_fetched_adv;

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                compressed_o <= 1'b0;
            else if (enable_i)
                compressed_o <= (instruction_next[1:0] != '1);
        end
    end

endmodule
