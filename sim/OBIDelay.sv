/*!\file OBIDelay.sv
 *
 * \brief
 * OBI subordinate model with configurable grant and response delays.
 *
 * \detailed
 * Simulation only. Connects an OBI manager to a target that is accessed in
 * the grant cycle and answers in the next one, like RAM_mem and the
 * peripherals. The grant waits GNT_DELAY cycles and the response is held
 * RSP_DELAY more cycles, in order. With RANDOM, each delay is drawn from 0 up
 * to its parameter. Up to OUTSTANDING requests are granted without response.
 * The manager side is checked against the OBI address phase rules.
 */

module OBIDelay
#(
    parameter int BUS_WIDTH   = 32,
    parameter int GNT_DELAY   = 0,
    parameter int RSP_DELAY   = 0,
    parameter bit RANDOM      = 1'b0,
    parameter int OUTSTANDING = 8,
    parameter int SEED        = 1
)
(
    input  logic                   clk,
    input  logic                   reset_n,

    /* Manager side */
    input  logic                   req_i,
    output logic                   gnt_o,
    input  logic [31:0]            addr_i,
    input  logic                   we_i,
    input  logic [BUS_WIDTH/8-1:0] be_i,
    input  logic [BUS_WIDTH-1:0]   wdata_i,
    output logic                   rvalid_o,
    output logic [BUS_WIDTH-1:0]   rdata_o,

    /* Target side: accessed in the grant cycle, read data in the next one */
    input  logic                   ready_i,
    output logic                   en_o,
    output logic [BUS_WIDTH/8-1:0] we_o,
    output logic [31:0]            addr_o,
    output logic [BUS_WIDTH-1:0]   wdata_o,
    input  logic [BUS_WIDTH-1:0]   rdata_i
);

    localparam int Q = OUTSTANDING + 1;

//////////////////////////////////////////////////////////////////////////////
// Random delays (xorshift32)
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] rnd;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            rnd <= (SEED == 0) ? 32'h1 : 32'(SEED);
        end
        else begin
            logic [31:0] x;
            x = rnd;
            x = x ^ (x << 13);
            x = x ^ (x >> 17);
            x = x ^ (x << 5);
            rnd <= x;
        end
    end

    function automatic int draw(input int max, input logic [15:0] r);
        if (max == 0)
            return 0;
        return RANDOM ? int'(r) % (max + 1) : max;
    endfunction

//////////////////////////////////////////////////////////////////////////////
// Address phase
//////////////////////////////////////////////////////////////////////////////

    int outstanding;
    int waited;
    int gnt_wait;

    assign gnt_o   = req_i && ready_i && (outstanding < OUTSTANDING) && (waited >= gnt_wait);
    assign en_o    = req_i && gnt_o;
    assign we_o    = we_i ? be_i : '0;
    assign addr_o  = addr_i;
    assign wdata_o = wdata_i;

    /* Cycles the current request has waited, and how long it must wait */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            waited   <= 0;
            gnt_wait <= draw(GNT_DELAY, 16'(SEED >> 3));
        end
        else if (!req_i || gnt_o) begin
            waited   <= 0;
            gnt_wait <= draw(GNT_DELAY, rnd[15:0]);
        end
        else begin
            waited   <= waited + 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Response phase
//////////////////////////////////////////////////////////////////////////////

    logic                 en_r;
    int                   rsp_delay;
    logic [BUS_WIDTH-1:0] q_data [Q];
    int                   q_wait [Q];
    int                   q_head;
    int                   q_count;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            en_r       <= 1'b0;
            rsp_delay <= 0;
        end
        else begin
            en_r       <= en_o;
            rsp_delay <= draw(RSP_DELAY, rnd[31:16]);
        end
    end

    /* The target answers the access of the last cycle: release it now when */
    /* it has no delay and nothing is queued before it                      */
    logic bypass;
    assign bypass = en_r && rsp_delay == 0 && q_count == 0;

    always_comb begin
        if (q_count > 0) begin
            rvalid_o = q_wait[q_head] == 0;
            rdata_o  = q_data[q_head];
        end
        else begin
            rvalid_o = bypass;
            rdata_o  = rdata_i;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            q_head  <= 0;
            q_count <= 0;
        end
        else begin
            int count;
            count = q_count;

            for (int i = 0; i < Q; i++) begin
                if (q_wait[i] > 0)
                    q_wait[i] <= q_wait[i] - 1;
            end

            if (q_count > 0 && rvalid_o) begin
                q_head <= (q_head + 1) % Q;
                count  = count - 1;
            end

            if (en_r && !bypass) begin
                q_data[(q_head + q_count) % Q] <= rdata_i;
                q_wait[(q_head + q_count) % Q] <= (rsp_delay > 0) ? rsp_delay - 1 : 0;
                count = count + 1;
            end

            q_count <= count;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            outstanding <= 0;
        else
            outstanding <= outstanding + int'(en_o) - int'(rvalid_o);
    end

//////////////////////////////////////////////////////////////////////////////
// OBI protocol checks
//////////////////////////////////////////////////////////////////////////////

    /* Once req is asserted, it and the address phase signals hold until gnt */
    logic                   waiting_r;
    logic [31:0]            addr_r;
    logic                   we_r;
    logic [BUS_WIDTH/8-1:0] be_r;
    logic [BUS_WIDTH-1:0]   wdata_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            waiting_r <= 1'b0;
        end
        else begin
            if (waiting_r && (!req_i || addr_i != addr_r || we_i != we_r || be_i != be_r || (we_i && wdata_i != wdata_r)))
                $error("[%0t] %m: OBI request changed before gnt", $time);
            waiting_r <= req_i && !gnt_o;
            addr_r    <= addr_i;
            we_r      <= we_i;
            be_r      <= be_i;
            wdata_r   <= wdata_i;
        end
    end

    /* rvalid only answers granted requests */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            ;
        else if (rvalid_o && outstanding == 0)
            $error("[%0t] %m: OBI response without request", $time);
    end

endmodule
