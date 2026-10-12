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
    input  logic        en_i,

    /* Unaligned access is not supported */
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [3:0]  addr_i,
    /* verilator lint_on UNUSEDSIGNAL */
    
    input  logic [7:0]  we_i,
    input  logic [63:0] data_i,
    output logic [63:0] data_o,
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

    logic [63:0] r_data;
    assign r_data = addr_i[3] ? mtimecmp : mtime;

    logic [63:0] r_data_unaligned;
    assign r_data_unaligned = addr_i[2] ? {32'h0, r_data[63:32]} : r_data;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            data_o <= '0;
        else if (en_i && we_i == '0)
            data_o <= r_data_unaligned;
    end

    logic [63:0] w_data;
    always_comb begin
        if (addr_i[2]) begin
            w_data[63:56] = we_i[3] ? data_i[31:24] : r_data[63:56];
            w_data[55:48] = we_i[2] ? data_i[23:16] : r_data[55:48];
            w_data[47:40] = we_i[1] ? data_i[15: 8] : r_data[47:40];
            w_data[39:32] = we_i[0] ? data_i[ 7: 0] : r_data[39:32];
            w_data[31: 0] =                           r_data[31: 0];
        end
        else begin
            w_data[63:56] = we_i[7] ? data_i[63:56] : r_data[63:56];
            w_data[55:48] = we_i[6] ? data_i[55:48] : r_data[55:48];
            w_data[47:40] = we_i[5] ? data_i[47:40] : r_data[47:40];
            w_data[39:32] = we_i[4] ? data_i[39:32] : r_data[39:32];
            w_data[31:24] = we_i[3] ? data_i[31:24] : r_data[31:24];
            w_data[23:16] = we_i[2] ? data_i[23:16] : r_data[23:16];
            w_data[15: 8] = we_i[1] ? data_i[15: 8] : r_data[15: 8];
            w_data[ 7: 0] = we_i[0] ? data_i[ 7: 0] : r_data[ 7: 0];
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtime    <= '0;
        end
        else begin
            mtime <= mtime + 1'b1;
            if (en_i && we_i != '0 && !addr_i[3])
                mtime <= w_data;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtimecmp <= '0;
        end
        else begin
            if (en_i && we_i != '0 && addr_i[3])
                mtimecmp <= w_data;
        end
    end

endmodule
