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
    parameter bit   ZCBEnable     = 1'b0,
    parameter bit   XOSVMEnable   = 1'b0
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           sys_reset,
    input   logic           enable_i,

    /* Jump control */
    input   logic           ctx_switch_i,
    input   logic           should_jump_i,
    input   logic [31:0]    jump_target_i,
    input   logic [31:0]    ctx_switch_target_i,
    
    /* Branch prediction */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           jump_i,
    input   logic           bp_take_i,
    input   logic [31:0]    bp_target_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input   logic           jump_rollback_i,
    output  logic           bp_ack_o,

    /* Address translation: virtual address out, physical address back in */
    output  logic [31:0]    instruction_address_o,
    input   logic [31:0]    instruction_paddr_i,
    /* Only Xosvm can fault a fetch */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           inst_fault_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* OBI instruction interface */
    output  logic           mem_req_o,
    input   logic           mem_gnt_i,
    output  logic [31:0]    mem_addr_o,
    input   logic           mem_rvalid_i,
    input   logic [31:0]    instruction_data_i,

    /* Fetched output */
    output  decode_ctrl_t   ctrl_o,
    output  logic [31:0]    pc_o,
    output  logic [31:0]    instruction_o
);

////////////////////////////////////////////////////////////////////////////////
// Jump control
////////////////////////////////////////////////////////////////////////////////

    logic valid;

    /* Jumped condition and fetched instruction invalidation depends on BP */
    /* Instruction address of jump target also depends on BP               */
    logic jumped;
    logic bp_taken_r;
    logic [31:0] iaddr_jumped;

    logic jumping_r;
    logic jump_misaligned_r;

    logic is_jumping;
    assign is_jumping = (jumping_r && !jump_rollback_i) || jump_misaligned_r;

    /* A predicted branch is resolved in the cycle after the prediction */
    logic bp_confirm;
    assign bp_confirm = bp_taken_r && !jump_rollback_i;

    logic bp_rollback;
    assign bp_rollback = bp_taken_r && jump_rollback_i;

    logic jump_confirmed;
    assign jump_confirmed = should_jump_i || bp_confirm;

    logic jump_confirmed_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jump_confirmed_r <= 1'b1;
        end
        else if (sys_reset) begin
            jump_confirmed_r <= 1'b1;
        end
        else begin
            if (jump_confirmed)
                jump_confirmed_r <= 1'b1;
            else if (valid)
                jump_confirmed_r <= 1'b0;
        end
    end

////////////////////////////////////////////////////////////////////////////////
// Instruction queue
////////////////////////////////////////////////////////////////////////////////

    /* The existance of prefetching only occurs with compressed enablement */
    logic instruction_prefetched;

    /* Buffer signals */
    logic valid_fetch;
    logic pop;
    logic buffer_tx;
    logic empty_buffer;
    logic [31:0] inst_buffered;
    /* Unused without Xosvm */
    /* verilator lint_off UNUSEDSIGNAL */
    logic        fault_buffered;
    /* verilator lint_on UNUSEDSIGNAL */
    /* Never used: requests start only with room reserved (ibuf_cnt) */
    /* verilator lint_off UNUSEDSIGNAL */
    logic        buffer_not_full;
    logic        almost_full;
    logic        almost_empty;
    /* verilator lint_on UNUSEDSIGNAL */

    /* With Xosvm, the fault of each fetch travels along with its word */
    localparam int IBUF_SIZE = XOSVMEnable ? 33 : 32;

    logic [(IBUF_SIZE - 1):0] ibuf_in;
    logic [(IBUF_SIZE - 1):0] ibuf_out;

    /* Fault of the oldest request in flight, which is the one answering */
    /* Unused without Xosvm */
    /* verilator lint_off UNUSEDSIGNAL */
    logic rsp_fault;
    /* verilator lint_on UNUSEDSIGNAL */

    if (XOSVMEnable) begin : gen_fetch_fault_on
        assign ibuf_in        = {rsp_fault, instruction_data_i};
        assign fault_buffered = ibuf_out[32];
    end
    else begin : gen_fetch_fault_off
        assign ibuf_in        = instruction_data_i;
        assign fault_buffered = 1'b0;
    end

    assign inst_buffered = ibuf_out[31:0];

    /* Words in the buffer */
    logic [$clog2(IQUEUE_SIZE + 1) - 1:0] ibuf_cnt;

    RingBuffer #(
        .DATA_SIZE              (IBUF_SIZE  ),
        .BUFFER_SIZE            (IQUEUE_SIZE),
        .FIRST_WORD_FALL_THROUGH(1          ),
        .ALMOST_FULL_THRESHOLD  (0          ),
        .ALMOST_EMPTY_THRESHOLD (0          )
    ) ibuf (
        .clk_i         (clk),
        .rst_ni        (reset_n),
        .buf_rst_i     (empty_buffer),
        .rx_i          (valid_fetch),
        .rx_ack_o      (buffer_not_full),
        .data_i        (ibuf_in),
        .tx_o          (buffer_tx),
        .tx_ack_i      (pop),
        .data_o        (ibuf_out),
        .count_o       (ibuf_cnt),
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
    assign pop = ((enable_i && !instruction_prefetched) || is_jumping);

////////////////////////////////////////////////////////////////////////////////
// OBI instruction interface
////////////////////////////////////////////////////////////////////////////////

    /* Requests in flight: started and not yet answered, oldest at index 0. */
    /* A started request is committed: it is held until granted, and its    */
    /* response is dropped when a jump made it stale. A predicted branch is */
    /* resolved in the next cycle: a confirmation makes the requests before */
    /* it stale, a rollback the one started on the predicted path.          */
    /* One request in flight per word the buffer can hold */
    localparam int INFLIGHT = IQUEUE_SIZE;
    localparam int CNT_W    = $clog2(INFLIGHT + 1);
    localparam int IDX_W    = $clog2(INFLIGHT);

    logic [CNT_W-1:0]    inflight_cnt;
    logic [INFLIGHT-1:0] stale;
    /* Unused without Xosvm */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [INFLIGHT-1:0] inflight_fault;
    /* verilator lint_on UNUSEDSIGNAL */

    /* Requests still in flight that will be written to the buffer */
    logic [CNT_W-1:0] inflight_valid;
    always_comb begin
        inflight_valid = '0;
        for (int i = 0; i < INFLIGHT; i++) begin
            if (CNT_W'(i) < inflight_cnt && !stale[i])
                inflight_valid = inflight_valid + 1'b1;
        end
    end

    /* Only start a request that will find room in the buffer. Right after   */
    /* a predicted branch, the request needs no room: a confirmation flushes */
    /* the buffer and the requests before it, a rollback makes it stale.     */
    /* OBI: req only depends on registers, never on gnt or rvalid. A word    */
    /* leaving the buffer frees room only in the next cycle, which the extra */
    /* buffer entry (see RS5 IQUEUE_SIZE) hides.                             */
    logic can_start;
    assign can_start = (
        inflight_cnt < CNT_W'(INFLIGHT)
        && (bp_taken_r || (32'(ibuf_cnt) + 32'(inflight_valid)) < IQUEUE_SIZE)
    );

    /* An address phase waits for gnt with stable signals */
    logic        pending_r;
    logic [31:0] pending_addr;

    logic req_start;
    assign req_start = !pending_r && can_start;

    assign mem_req_o  = pending_r || req_start;
    assign mem_addr_o = pending_r ? pending_addr : instruction_paddr_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pending_r <= 1'b0;
        else
            pending_r <= mem_req_o && !mem_gnt_i;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pending_addr <= '0;
        else if (req_start)
            pending_addr <= instruction_paddr_i;
    end

    /* Any jump makes all requests up to now stale */
    logic hard_redirect;
    assign hard_redirect = sys_reset || should_jump_i;

    /* The oldest request answers. It is dropped when stale, or when it */
    /* followed a predicted branch that is confirmed now                */
    assign rsp_fault   = inflight_fault[0];
    assign valid_fetch = mem_rvalid_i && !stale[0] && !bp_confirm;

    /* Position of a starting request: after the ones still in flight. */
    /* A request only starts with room, so it never exceeds INFLIGHT-1  */
    logic [CNT_W-1:0] start_idx;
    assign start_idx = inflight_cnt - CNT_W'(mem_rvalid_i);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            inflight_cnt <= '0;
        else
            inflight_cnt <= start_idx + CNT_W'(req_start);
    end

    logic [INFLIGHT-1:0] stale_next;
    always_comb begin
        stale_next = mem_rvalid_i ? (stale >> 1) : stale;
        stale_next = stale_next | {INFLIGHT{hard_redirect || bp_confirm}};
        /* A request started now is stale if its address is being replaced */
        if (req_start)
            stale_next[start_idx[IDX_W-1:0]] = hard_redirect || bp_rollback;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            stale <= '0;
        else
            stale <= stale_next;
    end

    logic [INFLIGHT-1:0] fault_next;
    always_comb begin
        fault_next = mem_rvalid_i ? (inflight_fault >> 1) : inflight_fault;
        if (req_start)
            fault_next[start_idx[IDX_W-1:0]] = inst_fault_i;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            inflight_fault <= '0;
        else
            inflight_fault <= fault_next;
    end

////////////////////////////////////////////////////////////////////////////////
// Instruction address
////////////////////////////////////////////////////////////////////////////////

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
            if (jumped || bp_rollback)
                instruction_address <= iaddr_jumped;
            else if (req_start)
                instruction_address <= next_instruction_address;
        end
    end

    assign instruction_address_o = {instruction_address[31:2], 2'b00};
    
    assign valid = valid_fetch || valid_buffer || instruction_prefetched;

////////////////////////////////////////////////////////////////////////////////
// Branch Prediction
////////////////////////////////////////////////////////////////////////////////

    if (BRANCHPRED) begin : gen_bp_on
        logic bp_taken;
        assign bp_taken = (enable_i && bp_take_i && valid);
        assign jumped   = should_jump_i || bp_taken;

        /* A rollback continues after the last request started before the branch */
        logic [31:0] iaddr_rollback;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                iaddr_rollback <= '0;
            else if (bp_taken)
                iaddr_rollback <= req_start ? next_instruction_address : instruction_address;
        end

        always_comb begin
            if (ctx_switch_i)
                iaddr_jumped = ctx_switch_target_i;
            else if (jump_i)
                iaddr_jumped = jump_target_i;
            else if (bp_take_i)
                iaddr_jumped = bp_target_i;
            else
                iaddr_jumped = iaddr_rollback;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_taken_r <= '0;
            else if (sys_reset)
                bp_taken_r <= '0;
            else
                bp_taken_r <= bp_taken;
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
        assign jumped       = should_jump_i;
        assign bp_taken_r   = 1'b0;
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

    logic valid_r;
    logic compressed;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            valid_r <= 1'b0;
        else if (sys_reset)
            valid_r <= 1'b0;
        else if (enable_i || is_jumping)
            valid_r <= valid;
    end

    logic [31:0] instruction;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_o <= 32'h00000013;
        else if (sys_reset)
            instruction_o <= 32'h00000013;
        else if (enable_i || is_jumping)
            instruction_o <= instruction;
    end

    /* The instruction being built came from a faulting fetch */
    /* Unused without Xosvm */
    /* verilator lint_off UNUSEDSIGNAL */
    logic inst_fault;
    /* verilator lint_on UNUSEDSIGNAL */

    if (XOSVMEnable) begin : gen_inst_fault_on
        logic inst_fault_r;
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                inst_fault_r <= 1'b0;
            else if (sys_reset)
                inst_fault_r <= 1'b0;
            else if (enable_i || is_jumping)
                inst_fault_r <= inst_fault;
        end

        assign ctrl_o.inst_fault = inst_fault_r;
    end
    else begin : gen_inst_fault_off
        assign ctrl_o.inst_fault = 1'b0;
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
            if (jump_confirmed_r || jump_misaligned_r)
                pc_o <= pc_jumped;
            else if (enable_i && valid)
                pc_o <= next_pc;
        end
    end
    
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jumping_r <= 1'b1;
        end
        else if (sys_reset) begin
            jumping_r <= 1'b1;
        end
        else begin
            if (jumped)
                jumping_r <= 1'b1;
            else if (valid || jump_rollback_i)
                jumping_r <= 1'b0;
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
                instruction_r <= inst_buffered;
        end

        /* Alignment control */
        logic [31:0] instruction_built;
        always_comb begin
            if (jump_confirmed_r)
                /* On jump, last valid instruction is the next one */
                instruction_built = inst_buffered;
            else if (jump_misaligned_r || (unaligned ^ compressed))
                /* When next instruction is unaligned we also need two fetches */
                /* Shift the last instruction msbs and join with the next lsbs */
                instruction_built = {inst_buffered[15:0], instruction_r[31:16]};
            else if (!(unaligned || compressed))
                /* Normal flow of 4-byte aligned instructions */
                instruction_built = inst_buffered;
            else   // unaligned &&  compressed
                /* After an unaligned compressed, the instruction we want was */
                /* already removed from the buffer/memory                     */
                instruction_built = instruction_r;
        end

        logic next_compressed;        
        assign next_compressed = (instruction_built[1:0] != 2'b11);

        if (XOSVMEnable) begin : gen_fault_on
            /* Fault of the last word removed from buffer/memory */
            logic fault_r;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    fault_r <= 1'b0;
                else if (sys_reset)
                    fault_r <= 1'b0;
                else if (pop && (valid_fetch || valid_buffer))
                    fault_r <= fault_buffered;
            end

            /* Faults of each halfword, following the alignment control */
            logic fault_built_lower;
            logic fault_built_upper;
            always_comb begin
                if (jump_confirmed_r) begin
                    fault_built_lower = fault_buffered;
                    fault_built_upper = fault_buffered;
                end
                else if (jump_misaligned_r || (unaligned ^ compressed)) begin
                    fault_built_lower = fault_r;
                    fault_built_upper = fault_buffered;
                end
                else if (!(unaligned || compressed)) begin
                    fault_built_lower = fault_buffered;
                    fault_built_upper = fault_buffered;
                end
                else begin  // unaligned &&  compressed
                    fault_built_lower = fault_r;
                    fault_built_upper = fault_r;
                end
            end

            /* A compressed instruction does not use the upper halfword */
            logic fault_upper;
            assign fault_upper = fault_built_upper && !next_compressed;
            assign inst_fault  = fault_built_lower || fault_upper;

            /* When only the upper halfword faulted, mtval must point to it */
            logic inst_fault_upper_r;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    inst_fault_upper_r <= 1'b0;
                else if (sys_reset)
                    inst_fault_upper_r <= 1'b0;
                else if (enable_i || is_jumping)
                    inst_fault_upper_r <= fault_upper && !fault_built_lower;
            end

            assign ctrl_o.inst_fault_upper = inst_fault_upper_r;
        end
        else begin : gen_fault_off
            assign inst_fault              = 1'b0;
            assign ctrl_o.inst_fault_upper = 1'b0;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                compressed <= 1'b0;
            else if (sys_reset)
                compressed <= 1'b0;
            else if ((enable_i || is_jumping) && valid)
                compressed <= next_compressed;
        end

        /* We consider a instruction prefetched when it was removed from buffer */
        /* or read from memory but will be used again. Happens after compressed */
        /* instruction with unaligned PC. If jumping, it is invalid.            */
        assign instruction_prefetched = unaligned && compressed && !is_jumping;

        /* An unaligned jump requires the input of two fetches                 */
        /* Only after the first needed fetch is valid the signal is deasserted */
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                jump_misaligned_r <= 1'b0;
            end
            else if (sys_reset) begin
                jump_misaligned_r <= 1'b0;
            end
            else begin
                if (jump_confirmed_r)
                    jump_misaligned_r <= pc_jumped[1];
                else if (!jumping_r && valid)
                    jump_misaligned_r <= 1'b0;
            end
        end

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
        assign next_pc     = pc_o + (compressed ? 32'd2 : 32'd4);
    end
    else begin : gen_compressed_off
        assign instruction_prefetched = 1'b0;
        assign compressed             = 1'b0;
        assign next_pc                = pc_o + 32'd4;
        assign instruction            = inst_buffered;
        assign jump_misaligned_r      = 1'b0;
        assign inst_fault             = fault_buffered;
        assign ctrl_o.inst_fault_upper = 1'b0;
    end

    assign ctrl_o.valid           = valid_r;
    assign ctrl_o.compressed      = compressed;
    assign ctrl_o.jumping         = jumping_r;
    assign ctrl_o.jump_misaligned = jump_misaligned_r;

endmodule
