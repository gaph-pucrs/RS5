/*!\file mswi.sv
 *
 * \brief
 * Machine software interrupts: one MSIP register for each hart.
 *
 * \detailed
 * OBI subordinate with 32-bit registers, as the RISC-V ACLINT MSWI:
 *   0x0 + 4*k: MSIP of hart k. Bit 0 raises msi_o[k], the other bits are zero
 * Any hart writes 1 to interrupt hart k, which writes 0 to clear it.
 * Unmapped registers read zero and ignore writes.
 */

module mswi
#(
    parameter int NUM_HARTS = 1,
    localparam int SEL_W    = (NUM_HARTS > 1) ? $clog2(NUM_HARTS) : 1,
    localparam int ADDR_W   = SEL_W + 2
)
(
    input  logic                 clk,
    input  logic                 reset_n,

    /* OBI subordinate: always granted, answers in the next cycle */
    input  logic                 req_i,
    output logic                 gnt_o,
    /* Only the bits that select the hart, and bit 0 of the lowest byte, are used */
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [ADDR_W-1:0]    addr_i,
    input  logic                 we_i,
    input  logic [3:0]           be_i,
    input  logic [31:0]          wdata_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output logic                 rvalid_o,
    output logic [31:0]          rdata_o,

    output logic [NUM_HARTS-1:0] msi_o
);

    assign gnt_o = 1'b1;

    logic read;
    logic write;
    assign read  = req_i && !we_i;
    assign write = req_i &&  we_i && be_i[0];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rvalid_o <= 1'b0;
        else
            rvalid_o <= req_i;
    end

    logic [SEL_W-1:0] sel;
    assign sel = addr_i[ADDR_W-1:2];

    /* Unmapped registers read zero */
    logic [2**SEL_W-1:0] regs;
    assign regs = (2**SEL_W)'(msi_o);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rdata_o <= '0;
        else if (read)
            rdata_o <= {31'b0, regs[sel]};
    end

    for (genvar k = 0; k < NUM_HARTS; k++) begin : gen_hart
        logic write_msip;
        assign write_msip = write && (sel == SEL_W'(k));

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                msi_o[k] <= 1'b0;
            else if (write_msip)
                msi_o[k] <= wdata_i[0];
        end
    end

endmodule
