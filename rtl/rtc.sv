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

    logic en_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            en_r <= 1'b0;
        else
            en_r <= en_i;
    end

    logic [3:0] addr_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            addr_r <= '0;
        else
            addr_r <= addr_i;
    end

    logic [7:0] we_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            we_r <= '0;
        else
            we_r <= we_i;
    end

    logic [63:0] data_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            data_r <= '0;
        else
            data_r <= data_i;
    end

    logic [63:0] r_data_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            r_data_r <= '0;
        else
            r_data_r <= r_data;
    end

    logic [63:0] w_data;
    always_comb begin
        if (addr_i[2]) begin
            w_data[63:56] = we_r[3] ? data_r[31:24] : r_data_r[63:56];
            w_data[55:48] = we_r[2] ? data_r[23:16] : r_data_r[55:48];
            w_data[47:40] = we_r[1] ? data_r[15: 8] : r_data_r[47:40];
            w_data[39:32] = we_r[0] ? data_r[ 7: 0] : r_data_r[39:32];
            w_data[31: 0] =                           r_data_r[31: 0];
        end
        else begin
            w_data[63:56] = we_r[7] ? data_r[63:56] : r_data_r[63:56];
            w_data[55:48] = we_r[6] ? data_r[55:48] : r_data_r[55:48];
            w_data[47:40] = we_r[5] ? data_r[47:40] : r_data_r[47:40];
            w_data[39:32] = we_r[4] ? data_r[39:32] : r_data_r[39:32];
            w_data[31:24] = we_r[3] ? data_r[31:24] : r_data_r[31:24];
            w_data[23:16] = we_r[2] ? data_r[23:16] : r_data_r[23:16];
            w_data[15: 8] = we_r[1] ? data_r[15: 8] : r_data_r[15: 8];
            w_data[ 7: 0] = we_r[0] ? data_r[ 7: 0] : r_data_r[ 7: 0];
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtime    <= '0;
        end
        else begin
            if (en_r && we_r != '0 && !addr_r[3])
                mtime <= w_data;
            else
                mtime <= mtime + 1'b1;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mtimecmp <= '0;
        end
        else begin
            if (en_r && we_r != '0 && addr_r[3])
                mtimecmp <= w_data;
        end
    end

endmodule
