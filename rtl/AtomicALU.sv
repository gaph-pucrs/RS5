/*!\file AtomicALU.sv
 *
 * \brief
 * Executes the RISC-V A extension at the memory, for OBI managers with atop.
 *
 * \detailed
 * Sits in front of a memory that only knows plain OBI reads and writes.
 * Ordinary transactions pass through unchanged. An atomic transaction
 * (atop[5] = 1) waits until no ordinary response is pending, and no other
 * transaction is granted until it completes:
 *  - LR.W reads the word and reserves it for the manager (aid_i), exokay = 1.
 *  - SC.W writes the word only if that reservation still holds, and answers
 *    exokay = 1 on success. Any SC ends the manager's reservation.
 *  - AMO*.W reads the word, writes the operation result and returns the
 *    original value.
 * A write by another manager (ordinary, SC or AMO) to a reserved word clears
 * that reservation. The reservation set is one 32-bit word. Atomics use the
 * word in the lowest bus lanes (addr_i is word aligned, be_i = 4'b1111).
 * AMOEXT builds only what the core issues: Zalrsc (LR/SC), Zaamo (AMOs),
 * A (both) or none, which leaves a plain pass-through.
 */

`include "RS5_pkg.sv"

module AtomicALU
#(
    parameter RS5_pkg::atomic_e AMOEXT    = RS5_pkg::AMO_A,
    parameter int               BUS_WIDTH = 32,
    parameter int               NUM_IDS   = 1,    /* Managers that may hold a reservation */
    parameter int               AID_W     = (NUM_IDS > 1) ? $clog2(NUM_IDS) : 1
)
(
    input  logic                     clk,
    input  logic                     reset_n,

    /* From the managers */
    input  logic                     req_i,
    output logic                     gnt_o,
    input  logic [31:0]              addr_i,
    input  logic                     we_i,
    input  logic [BUS_WIDTH/8-1:0]   be_i,
    input  logic [BUS_WIDTH-1:0]     wdata_i,
    input  logic [5:0]               atop_i,
    input  logic [AID_W-1:0]         aid_i,
    output logic                     rvalid_o,
    output logic [BUS_WIDTH-1:0]     rdata_o,
    output logic                     exokay_o,

    /* To the memory */
    output logic                     req_o,
    input  logic                     gnt_i,
    output logic [31:0]              addr_o,
    output logic                     we_o,
    output logic [BUS_WIDTH/8-1:0]   be_o,
    output logic [BUS_WIDTH-1:0]     wdata_o,
    input  logic                     rvalid_i,
    input  logic [BUS_WIDTH-1:0]     rdata_i
);

    localparam logic [4:0] OP_LR = 5'h02;
    localparam logic [4:0] OP_SC = 5'h03;

    localparam bit LRSC = AMOEXT inside {RS5_pkg::AMO_ZALRSC, RS5_pkg::AMO_A};
    localparam bit AMO  = AMOEXT inside {RS5_pkg::AMO_ZAAMO,  RS5_pkg::AMO_A};

    typedef enum logic [2:0] {
        IDLE,
        READ,
        READ_WAIT,
        WRITE,
        WRITE_WAIT,
        SC_FAIL
    } state_e;

    state_e state;
    state_e state_next;

//////////////////////////////////////////////////////////////////////////////
// Ordinary transactions
//////////////////////////////////////////////////////////////////////////////

    logic is_atomic;
    assign is_atomic = atop_i[5];

    logic pass;
    assign pass = (state == IDLE) && req_i && !is_atomic;

    /* ponytail: 8-bit count, widen if a memory keeps more than 255 in flight */
    logic [7:0] pending;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pending <= '0;
        else
            pending <= pending + 8'(pass && gnt_i) - 8'((state == IDLE) && rvalid_i);
    end

//////////////////////////////////////////////////////////////////////////////
// Atomic transactions
//////////////////////////////////////////////////////////////////////////////

    logic accept;
    assign accept = (LRSC || AMO) && (state == IDLE) && req_i && is_atomic && (pending == '0);

    logic [4:0]       op;
    logic [31:0]      addr;
    logic [31:0]      operand;
    logic [AID_W-1:0] aid;
    logic [31:0]      loaded;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            op <= '0;
        else if (accept)
            op <= atop_i[4:0];
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            addr <= '0;
        else if (accept)
            addr <= {addr_i[31:2], 2'b00};
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            operand <= '0;
        else if (accept)
            operand <= wdata_i[31:0];
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            aid <= '0;
        else if (accept)
            aid <= aid_i;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            loaded <= '0;
        else if (state == READ_WAIT && rvalid_i)
            loaded <= rdata_i[31:0];
    end

    /* Reservations: one word per manager */
    logic [NUM_IDS-1:0] resv_valid;
    logic [29:0]        resv_addr [NUM_IDS];

    logic reserved;
    assign reserved = resv_valid[aid_i] && (resv_addr[aid_i] == addr_i[31:2]);

    /* The read in flight belongs to an LR: without Zaamo, every read does */
    logic is_lr;
    assign is_lr = !AMO || (op == OP_LR);

    logic accept_lr;
    logic accept_sc;
    assign accept_lr = LRSC && accept && (atop_i[4:0] == OP_LR);
    assign accept_sc = LRSC && accept && (atop_i[4:0] == OP_SC);

    always_comb begin
        unique case (state)
            IDLE:       state_next = !accept               ? IDLE
                                   : (atop_i[4:0] != OP_SC) ? READ
                                   : reserved               ? WRITE
                                   :                          SC_FAIL;
            READ:       state_next = gnt_i    ? READ_WAIT : READ;
            READ_WAIT:  state_next = !rvalid_i ? READ_WAIT
                                   : is_lr     ? IDLE : WRITE;
            WRITE:      state_next = gnt_i    ? WRITE_WAIT : WRITE;
            WRITE_WAIT: state_next = rvalid_i ? IDLE : WRITE_WAIT;
            default:    state_next = IDLE;  /* SC_FAIL answers in one cycle */
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            state <= IDLE;
        else
            state <= state_next;
    end

    logic [31:0] amo_result;
    always_comb begin
        if (!AMO) begin
            amo_result = operand;                                                              /* SC */
        end
        else begin
            unique case (op)
                5'h00:   amo_result = loaded + operand;                                        /* AMOADD  */
                5'h04:   amo_result = loaded ^ operand;                                        /* AMOXOR  */
                5'h0C:   amo_result = loaded & operand;                                        /* AMOAND  */
                5'h08:   amo_result = loaded | operand;                                        /* AMOOR   */
                5'h10:   amo_result = ($signed(loaded) < $signed(operand)) ? loaded : operand; /* AMOMIN  */
                5'h14:   amo_result = ($signed(loaded) < $signed(operand)) ? operand : loaded; /* AMOMAX  */
                5'h18:   amo_result = (loaded < operand) ? loaded : operand;                   /* AMOMINU */
                5'h1C:   amo_result = (loaded < operand) ? operand : loaded;                   /* AMOMAXU */
                default: amo_result = operand;                                                 /* AMOSWAP, SC */
            endcase
        end
    end

    /* A write granted to the memory: it clears other managers' reservations */
    logic             write_granted;
    logic [29:0]      write_word;
    logic [AID_W-1:0] write_aid;
    assign write_granted = (pass && gnt_i && we_i) || (state == WRITE && gnt_i);
    assign write_word    = (state == WRITE) ? addr[31:2] : addr_i[31:2];
    assign write_aid     = (state == WRITE) ? aid        : aid_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            resv_valid <= '0;
        end
        else begin
            for (int i = 0; i < NUM_IDS; i++) begin
                if (write_granted && AID_W'(i) != write_aid && resv_addr[i] == write_word)
                    resv_valid[i] <= 1'b0;
            end
            if (accept_lr)
                resv_valid[aid_i] <= 1'b1;
            else if (accept_sc)
                resv_valid[aid_i] <= 1'b0;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            for (int i = 0; i < NUM_IDS; i++)
                resv_addr[i] <= '0;
        end
        else if (accept_lr) begin
            resv_addr[aid_i] <= addr_i[31:2];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////////////////////////

    assign gnt_o = pass ? gnt_i : accept;

    always_comb begin
        unique case (state)
            READ: begin
                req_o   = 1'b1;
                addr_o  = addr;
                we_o    = 1'b0;
                be_o    = (BUS_WIDTH/8)'(4'hF);
                wdata_o = '0;
            end
            WRITE: begin
                req_o   = 1'b1;
                addr_o  = addr;
                we_o    = 1'b1;
                be_o    = (BUS_WIDTH/8)'(4'hF);
                wdata_o = BUS_WIDTH'(amo_result);
            end
            default: begin
                req_o   = pass;
                addr_o  = addr_i;
                we_o    = we_i;
                be_o    = be_i;
                wdata_o = wdata_i;
            end
        endcase
    end

    /* Only an AMO answers with a word of its own, the old value */
    assign rdata_o = (AMO && state == WRITE_WAIT) ? BUS_WIDTH'(loaded) : rdata_i;

    always_comb begin
        unique case (state)
            IDLE:       rvalid_o = rvalid_i;
            READ_WAIT:  rvalid_o = rvalid_i && is_lr;           /* an AMO goes on to write */
            WRITE_WAIT: rvalid_o = rvalid_i;
            SC_FAIL:    rvalid_o = 1'b1;
            default:    rvalid_o = 1'b0;                        /* READ, WRITE */
        endcase
    end

    /* exokay: LR always, SC when it wrote */
    assign exokay_o = (state == READ_WAIT) || (state == WRITE_WAIT && op == OP_SC);

endmodule
