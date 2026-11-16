/*!\file rtc.sv
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
 *
 * \detailed
 *
 */

module rtc (
    input  logic        clk,
    input  logic        reset_n,

    /* OBI subordinate: always granted, answers in the next cycle */
    input  logic        req_i,
    output logic        gnt_o,
    /* Bits [3:2] select mtime low/high or mtimecmp low/high */
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [3:0]  addr_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input  logic        we_i,
    input  logic [3:0]  be_i,
    input  logic [31:0] wdata_i,
    output logic        rvalid_o,
    output logic [31:0] rdata_o,

    output logic        mti_o,
    output logic [63:0] mtime_o
);
    logic [63:0] mtime;
    logic [63:0] mtimecmp;
    logic intr;

    assign intr = (mtime >= mtimecmp);
    assign mtime_o = mtime;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mti_o <= 1'b0;
        end
        else begin
            mti_o <= intr;
        end
    end

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

    logic [63:0] r_data;
    assign r_data = addr_i[3] ? mtimecmp : mtime;

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

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtime    <= '0;
        end
        else begin
            mtime <= mtime + 1'b1;
            if (write && !addr_i[3])
                mtime <= w_data;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtimecmp <= '0;
        end
        else begin
            if (write && addr_i[3])
                mtimecmp <= w_data;
        end
    end

endmodule
