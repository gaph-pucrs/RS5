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
    parameter int   IQUEUE_SIZE   = 2,
    parameter bit   BRANCHPRED    = 1'b1, 
    parameter bit   COMPRESSED    = 1'b0,
    parameter mul_e MULEXT        = MUL_M,
    parameter bit   ZCBEnable     = 1'b0
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           sys_reset,
    input   logic           enable_i,

    /* Jump control */
    input   logic           jump_i,
    input   logic           ctx_switch_i,
    input   logic [31:0]    jump_target_i,
    input   logic [31:0]    ctx_switch_target_i,
    output  logic           jumping_o,
    output  logic           jump_misaligned_o,
    
    /* Branch prediction */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           bp_take_i,
    input   logic [31:0]    bp_target_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input   logic           jump_rollback_i,
    output  logic           bp_ack_o,

    /* Memory interface */
    input   logic           busy_i,
    output  logic [31:0]    instruction_address_o,
    input   logic [31:0]    instruction_data_i,

    /* Fetched output */
    output  logic [31:0]    pc_o,
    output  logic [31:0]    instruction_o,
    output  logic           valid_o,
    output  logic           compressed_o
);

////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

    /* Jumped condition and fetched instruction invalidation depends on BP */
    /* Instruction address of jump target also depends on BP               */
    logic jumped;
    logic jumped_fetch;
    logic [31:0] iaddr_jumped;

    logic should_jump;
    assign should_jump = ctx_switch_i || jump_i;

    logic jump_confirmed;
    assign jump_confirmed = should_jump || (bp_ack_o && !jump_rollback_i);

    logic is_jumping;
    assign is_jumping = jumping_o && !jump_rollback_i;

    logic jumped_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jumped_r <= 1'b1;
        else if (sys_reset)
            jumped_r <= 1'b1;
        else
            jumped_r <= jumped;
    end

////////////////////////////////////////////////////////////////////////////////
// Memory interface and instruction queue
////////////////////////////////////////////////////////////////////////////////

    /* The existance of prefetching only occurs with compressed enablement */
    logic instruction_prefetched;

    /* verilator lint_off UNUSEDSIGNAL */
    logic almost_empty;
    /* verilator lint_on UNUSEDSIGNAL */

    /* Buffer signals */
    logic pop;
    logic almost_full;
    logic mem_operation_en;
    logic buffer_tx;
    logic push;
    logic empty_buffer;
    logic [31:0] inst_buffered;

    RingBuffer #(
        .DATA_SIZE             (32         ),
        .BUFFER_SIZE           (IQUEUE_SIZE),
        .ALMOST_FULL_THRESHOLD (1          ), 
        .ALMOST_EMPTY_THRESHOLD(0          )
    ) ibuf (
        .clk_i         (clk),
        .rst_ni        (reset_n),
        .buf_rst_i     (empty_buffer),
        .rx_i          (push),
        .rx_ack_o      (mem_operation_en),
        .data_i        (instruction_data_i),
        .tx_o          (buffer_tx),
        .tx_ack_i      (pop),
        .data_o        (inst_buffered),
        .almost_full_o (almost_full),
        .almost_empty_o(almost_empty)
    );

    /* When a jump is confirmed we clear the buffer */
    assign empty_buffer = sys_reset || jump_confirmed;

    logic valid_buffer;
    assign valid_buffer = buffer_tx && !empty_buffer;

    /* Read instruction from buffer/memory                */
    /* Read when enabled and not prefetched               */
    /* A misaligned jump will always have to read 2 times */
    assign pop = (enable_i && !instruction_prefetched) || jump_misaligned_o;

    /* When last cycle was busy, we do not have a valid fetch */
    logic busy_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            busy_r <= 1'b1;
        else if (sys_reset)
            busy_r <= 1'b1;
        else
            busy_r <= busy_i;
    end

    /* A valid fetch happens only when memory answers and the requested */
    /* address is still valid. A jump invalidates the request.          */
    logic valid_fetch;
    assign valid_fetch = !busy_r && !jumped_fetch;

    /* Insert instruction from memory into buffer      */
    /* Only insert when fetched instruction is valid   */
    /* Do not insert when being pasthrough from memory */
    assign push = valid_fetch && (!pop || valid_buffer);

    /* Do not update instruction address if memory can't answer       */
    /* Do not update if the present request will make the buffer full */
    /* Do not update if the buffer is already full                    */
    logic iaddr_hold;
    assign iaddr_hold = (
        busy_i 
        || (!pop && ((almost_full && valid_fetch) || !mem_operation_en))
    );

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
    logic [31:0] next_instruction_address;
    assign next_instruction_address = instruction_address + 32'd4;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_address <= start_address;
        end
        else if (sys_reset) begin
            instruction_address <= start_address;
        end
        else begin
            if (jumped || jump_rollback_i)
                instruction_address <= iaddr_jumped;
            else if (!iaddr_hold || (iaddr_hold_r && push && mem_operation_en))
                instruction_address <= next_instruction_address;
        end
    end

    assign instruction_address_o = {instruction_address[31:2], 2'b00};

    logic [31:0] next_instruction;
    assign next_instruction = valid_buffer ? inst_buffered : instruction_data_i;

    logic valid_prefetch;
    assign valid_prefetch = instruction_prefetched && !jump_misaligned_o;

    logic valid;
    assign valid = valid_fetch || valid_buffer || valid_prefetch;

////////////////////////////////////////////////////////////////////////////////
// Branch Prediction
////////////////////////////////////////////////////////////////////////////////

    if (BRANCHPRED) begin : gen_bp_on
        logic jump_rollback_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                jump_rollback_r <= 1'b0;
            else if (sys_reset)
                jump_rollback_r <= 1'b0;
            else 
                jump_rollback_r <= jump_rollback_i;
        end
        assign jumped_fetch = (jumped_r && !jump_rollback_i) || jump_rollback_r;

        logic bp_taken;
        assign bp_taken = (enable_i && bp_take_i && valid);
        assign jumped   = should_jump || bp_taken;

        logic [31:0] iaddr_rollback;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iaddr_rollback <= '0;
            else if (bp_taken)
                iaddr_rollback <= iaddr_hold ? instruction_address : next_instruction_address;
        end

        always_comb begin
            if (ctx_switch_i)
                iaddr_jumped = ctx_switch_target_i;
            else if (jump_i)
                iaddr_jumped = jump_target_i;
            else if (jump_rollback_i)
                iaddr_jumped = iaddr_rollback;
            else
                iaddr_jumped = bp_target_i;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_ack_o <= '0;
            else if (sys_reset)
                bp_ack_o <= '0;
            else if (enable_i)
                bp_ack_o <= bp_taken;
        end
    end
    else begin : gen_bp_off
        assign jumped       = should_jump;
        assign jumped_fetch = jumped_r && !jump_rollback_i;
        assign bp_ack_o     = 1'b0;

        always_comb begin
            if (ctx_switch_i)
                iaddr_jumped = ctx_switch_target_i;
            else
                iaddr_jumped = jump_target_i;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// CPU Interface
////////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            valid_o <= 1'b0;
        else if (sys_reset)
            valid_o <= 1'b0;
        else if (enable_i)
            valid_o <= valid;
    end

    logic [31:0] instruction;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_o <= 32'h00000013;
        else if (sys_reset)
            instruction_o <= 32'h00000013;
        else if (enable_i && valid)
            instruction_o <= instruction;
    end

    logic [31:0] pc_jumped;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) 
            pc_jumped <= start_address;
        else if (sys_reset)
            pc_jumped <= start_address;
        else if (jumped)
            pc_jumped <= iaddr_jumped;
    end

    logic [31:0] next_pc;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_o <= start_address;
        end
        else if (sys_reset) begin
            pc_o <= start_address;
        end
        else begin
            if (is_jumping || jump_misaligned_o)
                pc_o <= pc_jumped;
            else if (enable_i && valid)
                pc_o <= next_pc;
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
            if (jumped)
                jumping_o <= 1'b1;
            else if ((enable_i && valid) || jump_rollback_i)
                jumping_o <= 1'b0;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Instruction aligner and compressed expansion
////////////////////////////////////////////////////////////////////////////////

    if (COMPRESSED) begin : gen_compressed_on
        /* PC is always 2-byte or 4-byte aligned */
        logic unaligned;
        assign unaligned = pc_o[1];

        /* Last instruction removed from buffer/memory                    */
        /* Sometimes we need its contents two times, causing a "prefetch" */
        logic [31:0] instruction_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                instruction_r <= 32'h00000013;
            else if (sys_reset)
                instruction_r <= 32'h00000013;
            else if (pop && (valid_fetch || valid_buffer))
                instruction_r <= next_instruction;
        end

        logic compressed;
        
        /* Alignment control */
        logic [31:0] instruction_built;
        always_comb begin
            if (is_jumping || (!jump_misaligned_o && !(unaligned || compressed)))
                /* On jump, last valid instruction is the next one */
                /* Also normal flow of 4-byte aligned instructions */
                instruction_built = next_instruction;
            else if (jump_misaligned_o || (unaligned ^ compressed))
                /* When next instruction is unaligned we also need two fetches */
                /* Shift the last instruction msbs and join with the next lsbs */
                instruction_built = {next_instruction[15:0], instruction_r[31:16]};
            else   // unaligned &&  compressed
                /* After an unaligned compressed, the instruction we want was */
                /* already removed from the buffer/memory                     */
                instruction_built = instruction_r;
        end

        logic next_compressed;        
        assign next_compressed = (instruction_built[1:0] != 2'b11);

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                compressed <= 1'b0;
            else if (sys_reset)
                compressed <= 1'b0;
            else if (enable_i && valid)
                compressed <= next_compressed;
        end
        assign compressed_o = compressed;

        /* We consider a instruction prefetched when it was removed from buffer */
        /* or read from memory but will be used again. Happens after compressed */
        /* instruction with unaligned PC. If jumping, it is invalid.            */
        assign instruction_prefetched = unaligned && compressed && !is_jumping;

        /* An unaligned jump requires the input of two fetches                 */
        /* Only after the first needed fetch is valid the signal is deasserted */
        logic unaligned_jump;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                unaligned_jump <= 1'b0;
            end
            else if (sys_reset) begin
                unaligned_jump <= 1'b0;
            end
            else begin
                if (jumping_o && !jump_rollback_i)
                    unaligned_jump <= pc_jumped[1];
                else if (enable_i && valid_o)
                    unaligned_jump <= 1'b0;
            end
        end
        assign jump_misaligned_o = unaligned_jump;

        /* Compressed instruction expansion */
        logic [31:0] instruction_decompressed;
        decompresser #(
            .MULEXT    (MULEXT),
            .ZCBEnable (ZCBEnable)
        ) decompresser (
            .instruction_i (instruction_built[15:0] ),
            .instruction_o (instruction_decompressed)
        );

        assign instruction = next_compressed ? instruction_decompressed : instruction_built;
        assign next_pc     = pc_o + (compressed_o ? 32'd2 : 32'd4);
    end
    else begin : gen_compressed_off
        assign instruction_prefetched = 1'b0;
        assign compressed_o           = 1'b0;
        assign next_pc                = pc_o + 32'd4;
        assign instruction            = next_instruction;
        assign jump_misaligned_o      = 1'b0;
    end
endmodule
