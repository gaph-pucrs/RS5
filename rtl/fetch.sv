/*!\file fetch.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
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
    parameter       start_address = 32'b0,
    /* verilator lint_off UNUSEDPARAM */
    parameter bit   COMPRESSED = 1'b0,
    parameter bit   BRANCHPRED = 1'b1,    
    parameter mul_e MULEXT     = MUL_M,
    parameter bit   ZCBEnable  = 1'b0
    /* verilator lint_on UNUSEDPARAM */
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           sys_reset,
    input   logic           enable_i,
    input   logic           busy_i,
    output  logic           valid_o,
    output  logic           bp_ack_o,

    input   logic           jump_i,
    input   logic           ctx_switch_i,
    /* Bits 1:0 unused without compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]    jump_target_i,
    input   logic [31:0]    ctx_switch_target_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output  logic           jumping_o,
    
    /* Bits 1:0 unused without BP */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           bp_take_i,
    input   logic [31:0]    bp_target_i,
    input   logic           jump_rollback_i,
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
// Memory interface
////////////////////////////////////////////////////////////////////////////////

    logic jumped;
    assign jumped = ctx_switch_i || jump_i;

    logic empty_buffer;
    assign empty_buffer = sys_reset || jumped;

    logic valid_buffer;

    logic busy_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            busy_r <= 1'b1;
        else if (sys_reset)
            busy_r <= 1'b1;
        else
            busy_r <= busy_i;
    end

    logic push;
    assign push = !busy_r && !(enable_i && !valid_buffer);

    /* verilator lint_off UNUSEDSIGNAL */
    logic mem_operation_en;
    logic almost_empty;
    /* verilator lint_on UNUSEDSIGNAL */

    logic pop;
    assign pop = enable_i;

    logic [31:0] inst_buffered;

    logic almost_full;

    RingBuffer #(
        .DATA_SIZE(32),
        .BUFFER_SIZE(4),
        .ALMOST_FULL_THRESHOLD(1),
        .ALMOST_EMPTY_THRESHOLD(0)
    ) ibuf (
        .clk_i         (clk),
        .rst_ni        (reset_n),
        .buf_rst_i     (empty_buffer),
        .rx_i          (push),
        .rx_ack_o      (mem_operation_en),
        .data_i        (instruction_data_i),
        .tx_o          (valid_buffer),
        .tx_ack_i      (pop),
        .data_o        (inst_buffered),
        .almost_full_o (almost_full),
        .almost_empty_o(almost_empty)
    );

    logic [31:0] iaddr_jumped;
    always_comb begin
        if (ctx_switch_i)
            iaddr_jumped = ctx_switch_target_i;
        else
            iaddr_jumped = jump_target_i;
    end

    logic iaddr_hold;
    assign iaddr_hold = (almost_full && !pop) || busy_i;

    logic iaddr_hold_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            iaddr_hold_r <= 1'b0;
        else if (sys_reset)
            iaddr_hold_r <= 1'b0;
        else
            iaddr_hold_r <= iaddr_hold;
    end

    logic [31:0] instruction_address;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_address <= start_address;
        end
        else if (sys_reset) begin
            instruction_address <= start_address;
        end
        else begin
            if (jumped)
                instruction_address <= iaddr_jumped;
            else if (!iaddr_hold || (iaddr_hold_r && push && mem_operation_en))
                instruction_address <= instruction_address + 32'd4;
        end
    end

    assign instruction_address_o = {instruction_address[31:2], 2'b00};

////////////////////////////////////////////////////////////////////////////////
// CPU Interface
////////////////////////////////////////////////////////////////////////////////

    logic valid;
    assign valid = valid_buffer || !busy_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            valid_o <= 1'b0;
        else if (sys_reset)
            valid_o <= 1'b0;
        else if (enable_i)
            valid_o <= valid;
    end

    logic [31:0] next_instruction;
    assign next_instruction = valid_buffer ? inst_buffered : instruction_data_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_o <= 32'h00000013;
        else if (sys_reset)
            instruction_o <= 32'h00000013;
        else if (enable_i && valid)
            instruction_o <= next_instruction;
    end

    logic [31:0] pc_jumped;
    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) 
            pc_jumped <= start_address;
        else if (sys_reset)
            pc_jumped <= start_address;
        else if (jumped_r)
            pc_jumped <= instruction_address;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_o <= start_address;
        end
        else if (sys_reset) begin
            pc_o <= start_address;
        end
        else begin
            if (jumping_o)
                pc_o <= pc_jumped;
            else if (enable_i && valid)
                pc_o <= pc_o + 32'd4;
        end
    end

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
            else if (enable_i)
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
            if (jumped || jumped_r)
                jumping_o <= 1'b1;
            else if (enable_i)
                jumping_o <= 1'b0;
        end
    end

    assign bp_ack_o = 1'b0;
    assign bp_rollback_o = 1'b0;
    assign jump_misaligned_o = 1'b0;
    assign compressed_o = 1'b0;

////////////////////////////////////////////////////////////////////////////////
// Flow control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PC control
////////////////////////////////////////////////////////////////////////////////

    // logic [31:0] pc_update;
    // logic [31:0] pc_jumped;

    // logic [31:0] pc_jumped_r;
    // always_ff @(posedge clk or negedge reset_n) begin
    //     if (!reset_n)
    //         pc_jumped_r <= '0;
    //     else if (enable_i)
    //         pc_jumped_r <= pc_jumped;
    // end

    // /* pc_o is the PC of the fetched instruction */
    // /* at the moment the instruction arrives     */
    // always_ff @(posedge clk or negedge reset_n) begin
    //     if (!reset_n)
    //         pc_o <= '0;
    //     else if (enable_i && !is_invalid && !jump_misaligned_o) 
    //         pc_o <= pc_update;
    // end

////////////////////////////////////////////////////////////////////////////////
// Data control
////////////////////////////////////////////////////////////////////////////////

    // logic fetched;
    // always_ff @(posedge clk or negedge reset_n) begin
    //     if (!reset_n)
    //         fetched <= '0;
    //     else
    //         fetched <= enable_i && !busy_i;
    // end

    // logic [31:0] idata_held;
    // always_ff @(posedge clk or negedge reset_n) begin
    //     if (!reset_n)
    //         idata_held <= 32'h00000013;
    //     else if ((!enable_i || busy_i) && fetched)
    //         idata_held <= instruction_data_i;
    // end

    // logic [31:0] instruction_fetched;
    // assign instruction_fetched = fetched ? instruction_data_i : idata_held;

    // logic [31:0] instruction_next;

    // always_ff @(posedge clk or negedge reset_n) begin
    //     if (!reset_n)
    //         instruction_o <= 32'h00000013;
    //     else if (sys_reset)
    //         instruction_o <= 32'h00000013;
    //     else if (enable_i && !is_invalid)
    //         instruction_o <= instruction_next;
    // end

////////////////////////////////////////////////////////////////////////////////
// Branch prediction
////////////////////////////////////////////////////////////////////////////////

    // /* Only used with BP, but needed for BP + C */
    // /* verilator lint_off UNUSEDSIGNAL */
    // logic        jump_rollback_r;
    // logic [31:2] iaddr_fetched_adv;
    // /* verilator lint_on UNUSEDSIGNAL*/

    // if (BRANCHPRED) begin : gen_bp_on
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             iaddr_fetched_adv <= '0;
    //         else if ((enable_i && !busy_i) && bp_take_i)
    //             iaddr_fetched_adv <= iaddr_advance;
    //     end

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n) begin
    //             jump_rollback_r <= 1'b0;
    //         end
    //         else if (sys_reset) begin
    //             jump_rollback_r <= 1'b0;
    //         end
    //         else begin 
    //             if (jump_rollback_i)
    //                 jump_rollback_r <= 1'b1;
    //             else if (enable_i)
    //                 jump_rollback_r <= 1'b0;
    //         end
    //     end

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             bp_rollback_o <= 1'b0;
    //         else if (sys_reset)
    //             bp_rollback_o <= 1'b0;
    //         else if (enable_i)
    //             bp_rollback_o <= jump_rollback_r;
    //     end

    //     assign jumped = ctx_switch_i || jump_i || (enable_i && !busy_i && bp_take_i);

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             bp_ack_o <= '0;
    //         else if (enable_i)
    //             bp_ack_o <= bp_take_i && !busy_i;
    //     end
    // end
    // else begin : gen_bp_off
    //     assign bp_rollback_o     = 1'b0;
    //     assign bp_ack_o          = 1'b0;
    //     assign iaddr_fetched_adv = '0;
    // end

////////////////////////////////////////////////////////////////////////////////
// Alignment control
////////////////////////////////////////////////////////////////////////////////

    // if (COMPRESSED) begin : gen_compressed_on
    //     /**
    //     * We need to separate instruction address from PC to allow 2-byte aligned 
    //     * 2/4-byte fetch in case of compressed
    //     */
    //     typedef enum logic [3:0] {
    //         NO_JMP = 4'(1 << 0),
    //         CTX_SW = 4'(1 << 1),
    //         JMP_XU = 4'(1 << 2),
    //         BP_DEC = 4'(1 << 3)
    //     } jmp_reason_t;

    //     logic [31:0] bp_target_r;

    //     jmp_reason_t jmp_reason;
    //     always_comb begin
    //         if (ctx_switch_i)
    //             jmp_reason = CTX_SW;
    //         else if (jump_i)
    //             jmp_reason = JMP_XU;
    //         else if (BRANCHPRED && enable_i && !next_invalid && bp_take_i)
    //             jmp_reason = BP_DEC;
    //         else
    //             jmp_reason = NO_JMP;
    //     end

    //     jmp_reason_t jmp_reason_r;
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             jmp_reason_r <= NO_JMP;
    //         else if (sys_reset)
    //             jmp_reason_r <= NO_JMP;
    //         else
    //             jmp_reason_r <= jmp_reason;
    //     end

    //     logic [31:0] ctx_switch_target_r;
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             ctx_switch_target_r <= start_address;
    //         else if (ctx_switch_i)
    //             ctx_switch_target_r <= ctx_switch_target_i;
    //     end

    //     logic [31:0] jump_target_r;
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             jump_target_r <= start_address;
    //         else if (sys_reset)
    //             jump_target_r <= start_address;
    //         else if (jump_i)
    //             jump_target_r <= jump_target_i;
    //     end

    //     always_comb begin
    //         unique case (jmp_reason_r)
    //             CTX_SW:  pc_jumped = ctx_switch_target_r;
    //             JMP_XU:  pc_jumped = jump_target_r;
    //             BP_DEC:  pc_jumped = BRANCHPRED ? bp_target_r : jump_target_r;
    //             default: pc_jumped = instruction_address_o; /* NO_JMP */
    //         endcase
    //     end

    //     logic [ 2:0] pc_add;
    //     logic [31:0] pc;
    //     logic [31:0] pc_next;

    //     assign pc_next = pc + 32'(pc_add);

    //     /* We only use some bits of this signal with this name */
    //     /* verilator lint_off UNUSEDSIGNAL */
    //     logic [31:0] instruction;
    //     /* verilator lint_on UNUSEDSIGNAL */
    //     logic [31:0] instruction_word;
    //     logic [31:0] instruction_built;
    //     logic update_inst_r;

    //     assign compressed = (instruction[1:0] != '1);

    //     assign unaligned = pc[1];

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             iaddr_hold_r <= 1'b0;
    //         else if (iaddr_hold) //  && !(busy_r || busy_r2)
    //             iaddr_hold_r <= 1'b1;
    //         else if (enable_i) // && !busy_i?
    //             iaddr_hold_r <= 1'b0;
    //     end

    //     logic jumped_r2;
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             jumped_r2 <= 1'b1;
    //         else if (sys_reset)
    //             jumped_r2 <= 1'b1;
    //         else if (enable_i)
    //             jumped_r2 <= jumped_r && !jump_rollback_i;
    //     end

    //     logic unaligned_jump;
    //     assign unaligned_jump = jumped_r2 && pc_jumped_r[1];

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             jump_misaligned_o <= 1'b0;
    //         else if (enable_i)
    //             jump_misaligned_o <= unaligned_jump;
    //     end

    //     logic [31:0] instruction_data_r;
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             instruction_data_r <= 32'h00000013;
    //         else if (enable_i && update_inst_r)
    //             instruction_data_r <= instruction_fetched;
    //     end

    //     logic [31:0] instruction_prefetched;
    //     /* We may lose the prefetch on busy */
    //     // assign instruction_prefetched = iaddr_hold_r ? instruction_data_r : instruction_fetched;
    //     // assign instruction_prefetched = (iaddr_hold_r && !busy_r) ? instruction_data_r : instruction_fetched;
    //     assign instruction_prefetched = (iaddr_hold_r && !(busy_r || busy_r2)) ? instruction_data_r : instruction_fetched;

    //     assign pc_add = compressed ? 3'd2 : 3'd4;
    //     assign pc_update = (jumped_r2 || jump_misaligned_o || is_invalid) ? pc_jumped_r : pc_next;
       
    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             busy_r2 <= 1'b0;
    //         else if (enable_i)
    //             busy_r2 <= busy_r;
    //     end

    //     // logic iaddr_hold_r2;
    //     // always_ff @(posedge clk or negedge reset_n) begin
    //     //     if (!reset_n)
    //     //         iaddr_hold_r2 <= 1'b0;
    //     //     else
    //     //         iaddr_hold_r2 <= iaddr_hold_r;
    //     // end

    //     always_comb begin
    //         if (jumped_r2)
    //             // Disregard last instruction on jump 
    //             instruction_built = instruction_fetched;
    //         else if (jump_misaligned_o || (unaligned && !compressed))
    //             // After bubble or unaligned 4-byte instruction we need the input of 2 fetches
    //             instruction_built = {instruction_fetched[15:0], instruction_data_r[31:16]};
    //         else if (!unaligned &&  compressed)
    //             // After aligned compressed the next instruction could be prefetched if the previous was compressed
    //             instruction_built = {instruction_prefetched[15:0], instruction[31:16]};
    //         else if (!unaligned && !compressed)
    //             // After aligned 4-byte instruction the next could be prefetched if the previous was compressed
    //             instruction_built = instruction_prefetched;
    //         else   // unaligned &&  compressed
    //             // After unaligned compressed, next instruction is surely prefetched
    //             // instruction_built = (busy_r2 && !iaddr_hold_r2) ? instruction_fetched : instruction_data_r;
    //             instruction_built = busy_r2 ? instruction_fetched : instruction_data_r;
    //     end

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             instruction_word <= 32'h00000013;
    //         else if (enable_i && !is_invalid)
    //             instruction_word <= instruction_built;
    //     end

    //     logic [31:0] instruction_decompressed;

    //     decompresser #(
    //         .MULEXT    (MULEXT),
    //         .ZCBEnable (ZCBEnable)
    //     ) decompresser (
    //         .instruction_i (instruction_built[15:0]),
    //         .instruction_o (instruction_decompressed)
    //     );

    //     logic next_compressed;
    //     assign next_compressed = (instruction_built[1:0] != '1);
    //     assign instruction_next = next_compressed ? instruction_decompressed : instruction_built;

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             compressed_o <= 1'b0;
    //         else if (enable_i)
    //             compressed_o <= next_compressed;
    //     end

    //     if (BRANCHPRED) begin : gen_compressed_bp
    //         always_ff @(posedge clk or negedge reset_n) begin
    //             if (!reset_n)
    //                 bp_target_r <= start_address;
    //             else if (enable_i && bp_take_i)
    //                 bp_target_r <= bp_target_i;
    //         end

    //         logic [31:0] pc_rollbacked;
    //         always_ff @(posedge clk or negedge reset_n) begin
    //             if (!reset_n)
    //                 pc_rollbacked <= '0;
    //             else if (jump_rollback_r)
    //                 pc_rollbacked <= pc_o;
    //         end

    //         logic [31:0] idata_rollbacked;
    //         always_ff @(posedge clk or negedge reset_n) begin
    //             if (!reset_n)
    //                 idata_rollbacked <= 32'h00000013;
    //             else if (jump_rollback_r)
    //                 idata_rollbacked <= instruction_word;
    //         end

    //         logic [31:2] iaddr_fetched;
    //         always_ff @(posedge clk or negedge reset_n) begin
    //             if (!reset_n)
    //                 iaddr_fetched <= '0;
    //             else if (enable_i && bp_take_i)
    //                 iaddr_fetched <= instruction_address_o[31:2];
    //         end

    //         assign pc             = bp_rollback_o ? pc_rollbacked : pc_o;
    //         assign iaddr_hold     = ((!(jumping_o && !jump_rollback_i) && unaligned && (compressed && !jump_misaligned_o)) || (iaddr_hold_r && jump_rollback_r)) && !(iaddr_hold_r && bp_rollback_o);
    //         assign instruction    = bp_rollback_o ? idata_rollbacked : instruction_word;
    //         assign iaddr_rollback = iaddr_hold_r ? iaddr_fetched : iaddr_fetched_adv;
    //         assign update_inst_r  = jump_misaligned_o || unaligned_jump || ((unaligned || (compressed && !iaddr_hold_r)) && !jump_rollback_r);
    //     end
    //     else begin : gen_compressed_wo_bp
    //         assign pc             = pc_o;
    //         assign bp_target_r    = '0;
    //         assign iaddr_hold     = !jumping_o && unaligned && (compressed && !jump_misaligned_o) && !(busy_r || busy_r2);
    //         assign instruction    = instruction_word;
    //         assign iaddr_rollback = '0;
    //         // assign update_inst_r  = jump_misaligned_o || unaligned_jump || (unaligned || (compressed && !iaddr_hold_r));
    //         // assign update_inst_r  = (jump_misaligned_o || unaligned_jump || (unaligned || (compressed && !iaddr_hold_r))) && !busy_r;
    //         assign update_inst_r  = (jump_misaligned_o || unaligned_jump || (unaligned || (compressed && !(iaddr_hold_r && !busy_r2)))) && !busy_r;
    //     end
    // end
    // else begin : gen_compressed_off
    //     assign pc_jumped         = instruction_address_o;
    //     assign jump_misaligned_o = 1'b0;
    //     assign iaddr_continue    = enable_i && !busy_i;
    //     assign pc_update         = pc_jumped_r;
    //     assign instruction_next  = instruction_fetched;
    //     assign iaddr_rollback    = iaddr_fetched_adv;

    //     always_ff @(posedge clk or negedge reset_n) begin
    //         if (!reset_n)
    //             compressed_o <= 1'b0;
    //         else if (enable_i)
    //             compressed_o <= (instruction_next[1:0] != '1);
    //     end
    // end

endmodule
