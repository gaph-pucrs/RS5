/*!\file mtimer.sv
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
 * Machine timer: one mtime for all harts, one mtimecmp for each.
 *
 * \detailed
 * OBI subordinate with 64-bit registers, low word first:
 *   0x0:       mtime
 *   0x8 + 8*k: mtimecmp of hart k, which raises mti_o[k] while mtime >= mtimecmp
 * Unmapped registers read zero and ignore writes.
 */

module mtimer
#(
    parameter int NUM_HARTS = 1,
    localparam int ADDR_W   = $clog2(8 * (NUM_HARTS + 1))
)
(
    input  logic                 clk,
    input  logic                 reset_n,

    /* OBI subordinate: always granted, answers in the next cycle */
    input  logic                 req_i,
    output logic                 gnt_o,
    /* Bit 2 selects the low/high word, the bits above select the register */
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [ADDR_W-1:0]    addr_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input  logic                 we_i,
    input  logic [3:0]           be_i,
    input  logic [31:0]          wdata_i,
    output logic                 rvalid_o,
    output logic [31:0]          rdata_o,

    output logic [NUM_HARTS-1:0] mti_o,
    output logic [63:0]          mtime_o
);
    localparam int SEL_W = ADDR_W - 3;

    logic [63:0]                mtime;
    logic [NUM_HARTS-1:0][63:0] mtimecmp;

    assign mtime_o = mtime;

//////////////////////////////////////////////////////////////////////////////
// OBI
//////////////////////////////////////////////////////////////////////////////

    assign gnt_o = 1'b1;

    logic read;
    logic write;
    assign read  = req_i && !we_i;
    assign write = req_i &&  we_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rvalid_o <= 1'b0;
        else
            rvalid_o <= req_i;
    end

    /* Register 0 is mtime, register k + 1 is the mtimecmp of hart k */
    logic [SEL_W-1:0] sel;
    assign sel = addr_i[ADDR_W-1:3];

    logic [2**SEL_W-1:0][63:0] regs;
    for (genvar k = 0; k < 2**SEL_W; k++) begin : gen_regs
        if (k == 0) begin : gen_mtime
            assign regs[k] = mtime;
        end
        else if (k <= NUM_HARTS) begin : gen_mtimecmp
            assign regs[k] = mtimecmp[k - 1];
        end
        else begin : gen_unmapped
            assign regs[k] = '0;
        end
    end

    logic [63:0] r_data;
    assign r_data = regs[sel];

    logic [31:0] r_word;
    assign r_word = addr_i[2] ? r_data[63:32] : r_data[31:0];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rdata_o <= '0;
        else if (read)
            rdata_o <= r_word;
    end

    logic [31:0] w_word;
    assign w_word[31:24] = be_i[3] ? wdata_i[31:24] : r_word[31:24];
    assign w_word[23:16] = be_i[2] ? wdata_i[23:16] : r_word[23:16];
    assign w_word[15: 8] = be_i[1] ? wdata_i[15: 8] : r_word[15: 8];
    assign w_word[ 7: 0] = be_i[0] ? wdata_i[ 7: 0] : r_word[ 7: 0];

    logic [63:0] w_data;
    assign w_data = addr_i[2] ? {w_word, r_data[31:0]} : {r_data[63:32], w_word};

    logic write_mtime;
    assign write_mtime = write && (sel == '0);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtime    <= '0;
        end
        else begin
            mtime <= mtime + 1'b1;
            if (write_mtime)
                mtime <= w_data;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Harts
//////////////////////////////////////////////////////////////////////////////

    for (genvar k = 0; k < NUM_HARTS; k++) begin : gen_hart
        logic write_mtimecmp;
        assign write_mtimecmp = write && (sel == SEL_W'(k + 1));

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                mtimecmp[k] <= '0;
            else if (write_mtimecmp)
                mtimecmp[k] <= w_data;
        end

        logic intr;
        assign intr = (mtime >= mtimecmp[k]);

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                mti_o[k] <= 1'b0;
            else
                mti_o[k] <= intr;
        end
    end

endmodule
