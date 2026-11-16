/*!\file AtomicHart.sv
 *
 * \brief
 * Simulation-only second hart that competes for atomics with RS5.
 *
 * \detailed
 * A behavioural OBI manager with atop, used by app/baremetal/tests/atomic-test.
 * It shares four words with the program running on RS5:
 *   BASE + 0x00 go:      the program writes 1 to start this hart
 *   BASE + 0x04 done:    this hart writes 1 after its increments
 *   BASE + 0x08 counter: incremented ITERATIONS times, alternating AMOADD
 *                        and LR/SC retry loops
 *   BASE + 0x0C scratch: after the increments, written with plain stores
 *                        until the program writes 1 to stop
 *   BASE + 0x10 stop
 * One transaction is issued at a time, and every request is held until gnt.
 */

module AtomicHart
#(
    parameter logic [31:0] BASE       = 32'h0000E000,
    parameter int          ITERATIONS = 200
)
(
    input  logic        clk,
    input  logic        reset_n,

    output logic        req_o,
    input  logic        gnt_i,
    output logic [31:0] addr_o,
    output logic        we_o,
    output logic  [3:0] be_o,
    output logic [31:0] wdata_o,
    output logic  [5:0] atop_o,
    input  logic        rvalid_i,
    input  logic [31:0] rdata_i,
    input  logic        exokay_i
);

    localparam logic [5:0] ATOP_NONE   = 6'h00;
    localparam logic [5:0] ATOP_LR     = 6'h22;
    localparam logic [5:0] ATOP_SC     = 6'h23;
    localparam logic [5:0] ATOP_AMOADD = 6'h20;

    initial begin
        req_o   = 1'b0;
        addr_o  = '0;
        we_o    = 1'b0;
        be_o    = 4'hF;
        wdata_o = '0;
        atop_o  = '0;
    end

    task automatic access(
        input  logic [31:0] addr,
        input  logic        we,
        input  logic [31:0] wdata,
        input  logic  [5:0] atop,
        output logic [31:0] rdata,
        output logic        exokay
    );
        req_o   <= 1'b1;
        addr_o  <= addr;
        we_o    <= we;
        wdata_o <= wdata;
        atop_o  <= atop;
        do @(posedge clk); while (!gnt_i);
        req_o   <= 1'b0;
        do @(posedge clk); while (!rvalid_i);
        rdata  = rdata_i;
        exokay = exokay_i;
    endtask

    logic [31:0] data;
    logic        ok;
    int          sc_retries;

    initial begin
        sc_retries = 0;
        @(posedge clk iff reset_n);

        /* Wait for the program */
        do begin
            repeat (5) @(posedge clk);
            access(BASE + 32'h00, 1'b0, '0, ATOP_NONE, data, ok);
        end while (data == '0);

        for (int i = 0; i < ITERATIONS; i++) begin
            if (i % 2 == 0) begin
                access(BASE + 32'h08, 1'b1, 32'd1, ATOP_AMOADD, data, ok);
            end
            else begin
                do begin
                    access(BASE + 32'h08, 1'b0, '0, ATOP_LR, data, ok);
                    access(BASE + 32'h08, 1'b1, data + 1, ATOP_SC, data, ok);
                    if (!ok)
                        sc_retries++;
                end while (!ok);
            end
            repeat (i % 3) @(posedge clk);
        end

        access(BASE + 32'h04, 1'b1, 32'd1, ATOP_NONE, data, ok);
        $display("[AtomicHart] %0d increments done, %0d SC retries", ITERATIONS, sc_retries);

        /* Break the program's reservations on scratch until told to stop */
        for (int i = 0; ; i++) begin
            access(BASE + 32'h0C, 1'b1, i, ATOP_NONE, data, ok);
            repeat (4) @(posedge clk);
            access(BASE + 32'h10, 1'b0, '0, ATOP_NONE, data, ok);
            if (data != '0)
                break;
        end
    end

endmodule
