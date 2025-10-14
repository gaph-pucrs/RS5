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
    parameter bit   BRANCHPRED = 1'b1, 
    parameter bit   COMPRESSED = 1'b0,
    /* verilator lint_off UNUSEDPARAM */
    parameter mul_e MULEXT     = MUL_M,
    parameter bit   ZCBEnable  = 1'b0
    /* verilator lint_on UNUSEDPARAM */
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
    output  logic           bp_rollback_o,
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
// Memory interface
////////////////////////////////////////////////////////////////////////////////

    logic jumped;
    logic jump_confirmed;
    logic valid;
    logic iaddr_hold;
    logic jumped_r;
    logic [31:0] instruction_address;

    logic empty_buffer;
    assign empty_buffer = sys_reset || jump_confirmed;

    logic buffer_tx;
    logic valid_buffer;
    assign valid_buffer = buffer_tx && !empty_buffer;

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
    logic compressed;
    logic unaligned;

    /* verilator lint_off UNUSEDSIGNAL */
    logic mem_operation_en;
    logic almost_empty;
    /* verilator lint_on UNUSEDSIGNAL */

    logic pop;
    // assign pop = enable_i;
    assign pop = enable_i && (!(unaligned && compressed) || (jumping_o && !jump_rollback_i) || jump_misaligned_o);

    logic [31:0] inst_buffered;

    logic almost_full;

    RingBuffer #(
        .DATA_SIZE(32),
        .BUFFER_SIZE(1),
        .ALMOST_FULL_THRESHOLD(1), /* DO NOT CHANGE */
        .ALMOST_EMPTY_THRESHOLD(0)
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

    logic [31:0] iaddr_jumped;
    logic [31:0] next_instruction_address;

    logic jump_rollback_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jump_rollback_r <= 1'b0;
        end
        else if (sys_reset) begin
            jump_rollback_r <= 1'b0;
        end
        else begin 
            // if (jump_rollback_i)
            //     jump_rollback_r <= 1'b1;
            // // else if (!busy_i)
            // else if (valid_o)
            // // else
            //     jump_rollback_r <= 1'b0;
            jump_rollback_r <= jump_rollback_i;
        end
    end

    logic valid_fetch;
    assign valid_fetch = !busy_r && !jump_rollback_r && !(jumped_r && !jump_rollback_i);

    if (BRANCHPRED) begin : gen_bp_on
        logic bp_taken;
        // assign bp_taken = (enable_i && bp_take_i && valid && push);
        assign bp_taken       = (enable_i && bp_take_i && valid);
        assign jumped         = ctx_switch_i || jump_i || bp_taken;
        assign jump_confirmed = ctx_switch_i || jump_i || (bp_ack_o && !jump_rollback_i);

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

        // assign push = valid_fetch && (!pop || valid_buffer);
        assign push = valid_fetch && (!pop || valid_buffer) && !jumping_o;

        assign bp_rollback_o  = 1'b0;
    end
    else begin : gen_bp_off
        // assign push           = !busy_r && (!pop || valid_buffer);
        assign push           = !busy_r && (!pop || valid_buffer) && !jumping_o;
        assign jumped         = ctx_switch_i || jump_i;
        assign jump_confirmed = jumped;
        assign bp_ack_o       = 1'b0;
        assign bp_rollback_o  = 1'b0;

        always_comb begin
            if (ctx_switch_i)
                iaddr_jumped = ctx_switch_target_i;
            else
                iaddr_jumped = jump_target_i;
        end
    end

    assign iaddr_hold = (almost_full && !pop && !busy_r) || (!pop && !mem_operation_en && busy_r) || busy_i;

    logic iaddr_hold_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            iaddr_hold_r <= 1'b0;
        else if (sys_reset)
            iaddr_hold_r <= 1'b0;
        else
            iaddr_hold_r <= iaddr_hold;
    end

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

////////////////////////////////////////////////////////////////////////////////
// CPU Interface
////////////////////////////////////////////////////////////////////////////////

    // assign valid = valid_fetch || valid_buffer;
    assign valid = valid_fetch || valid_buffer || (unaligned && compressed && !(jumping_o && !jump_rollback_i) && !jump_misaligned_o);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            valid_o <= 1'b0;
        else if (sys_reset)
            valid_o <= 1'b0;
        else if (enable_i)
            valid_o <= valid;
    end

    logic [31:0] next_instruction;
    logic [31:0] instruction;
    assign next_instruction = valid_buffer ? inst_buffered : instruction_data_i;

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
    if (COMPRESSED) begin : gen_compressed_on
        logic [31:0] instruction_built;


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

        logic [31:0] instruction_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                instruction_r <= 32'h00000013;
            else if (sys_reset)
                instruction_r <= 32'h00000013;
            // else if (pop && valid)
            else if (pop && (valid_fetch || valid_buffer))
                instruction_r <= next_instruction;
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

        logic [31:0] instruction_decompressed;
        decompresser #(
            .MULEXT    (MULEXT),
            .ZCBEnable (ZCBEnable)
        ) decompresser (
            .instruction_i (instruction_built[15:0]),
            .instruction_o (instruction_decompressed)
        );

        assign unaligned  = pc_o[1];
        
        assign instruction = next_compressed ? instruction_decompressed : instruction_built;
        assign next_pc     = pc_o + (compressed_o ? 32'd2 : 32'd4);

        always_comb begin
            if (jumping_o && !jump_rollback_i)
                // Disregard last instruction on jump 
                instruction_built = next_instruction;
            else if (jump_misaligned_o || (unaligned && !compressed))
                // After unaligned 4-byte instruction we need the input of 2 fetches
                instruction_built = {next_instruction[15:0], instruction_r[31:16]};
            else if (!unaligned &&  compressed)
                // After aligned compressed the next instruction could be prefetched if the previous was compressed
                instruction_built = {next_instruction[15:0], instruction_r[31:16]};
            else if (!unaligned && !compressed)
                // Normal flow: get the entire next instruction
                instruction_built = next_instruction;
            else   // unaligned &&  compressed
                // After unaligned compressed, the next instruction was not popped?
                instruction_built = instruction_r;
        end

        // always_ff @(posedge clk or negedge reset_n) begin
        //     if (!reset_n)
        //         jump_misaligned_o <= 1'b0;
        //     else if (sys_reset)
        //         jump_misaligned_o <= 1'b0;
        //     else if (jumping_o && !jump_rollback_i)
        //         jump_misaligned_o <= pc_jumped[1];
        //     else if (enable_i && valid_o)
        //         jump_misaligned_o <= 1'b0;
        // end
        assign jump_misaligned_o = unaligned_jump;
    end
    else begin : gen_compressed_off
        assign compressed_o      = 1'b0;
        assign next_pc           = pc_o + 32'd4;
        assign instruction       = next_instruction;
        assign compressed        = 1'b0;
        assign unaligned        = 1'b0;
        assign jump_misaligned_o = 1'b0;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            pc_o <= start_address;
        end
        else if (sys_reset) begin
            pc_o <= start_address;
        end
        else begin
            if ((jumping_o && !jump_rollback_i) || jump_misaligned_o)
                pc_o <= pc_jumped;
            // else if (enable_i && valid && !bp_rollback_o)
            // else if (enable_i && valid_o)
            else if (enable_i && valid)
                pc_o <= next_pc;
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
            jumped_r <= jumped;
            // if (jumped)
            //     jumped_r <= 1'b1;
            // else if (enable_i || jump_rollback_i)
            //     jumped_r <= 1'b0;
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
            // if (jumped || (jumped_r && !jump_rollback_i))
            if (jumped)
                jumping_o <= 1'b1;
            // else if ((enable_i && valid) || jump_rollback_i)
            // else if ((enable_i && valid) || jump_rollback_i)
            else if ((enable_i && valid) || jump_rollback_i)
            // else if ((enable_i && valid) || jump_rollback_i || (jump_rollback_r && valid))
                jumping_o <= 1'b0;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Flow control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PC control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Data control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Branch prediction
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Alignment control
////////////////////////////////////////////////////////////////////////////////

endmodule
