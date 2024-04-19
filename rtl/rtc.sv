/*!\file rtc.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes     <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto  <angelo.dalzotto@edu.pucrs.br>
 * Caroline Borges   <caroline.s@edu.pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
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
    input  logic [3:0]  addr_i,
    input  logic [7:0]  we_i,
    input  logic [63:0] data_i,
    output logic [63:0] data_o,
    output logic        mti_o,
    output logic [63:0] mtime_o
);
    // memory[7:0] = mtime (64 bits)
    // memory[15:0] = mtimecmp (64 bits)
    logic [15:0][7:0] memory;
    logic intr;

    assign intr = (memory[7:0] >= memory[15:8]);
    assign mtime_o = memory[7:0];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mti_o <= 1'b0;
        end
        else begin
            mti_o <= intr;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        memory[7:0] <= memory[7:0] + 1'b1;
        if (!reset_n) begin
            memory <= '0;
            data_o <= '0;
        end
        else if (en_i == 1'b1) begin
            if (we_i != '0) begin
                if (we_i[7] == 1'b1) begin                                 
                    memory[addr_i+7] <= data_i[63:56];
                end 
                if (we_i[6] == 1'b1) begin                                 
                    memory[addr_i+6] <= data_i[55:48];
                end
                if (we_i[5] == 1'b1) begin                                 
                    memory[addr_i+5] <= data_i[47:40];
                end
                if (we_i[4] == 1'b1) begin                                 
                    memory[addr_i+4] <= data_i[39:32];
                end
                if (we_i[3] == 1'b1) begin                                
                    memory[addr_i+3] <= data_i[31:24];
                end 
                if (we_i[2] == 1'b1) begin                                 
                    memory[addr_i+2] <= data_i[23:16];
                end
                if (we_i[1] == 1'b1) begin                                 
                    memory[addr_i+1] <= data_i[15:8];
                end
                if (we_i[0] == 1'b1) begin                                 
                    memory[addr_i]   <= data_i[7:0];
                end
            end
            else begin
                data_o[63:56] <= memory[addr_i+7];
                data_o[55:48] <= memory[addr_i+6];
                data_o[47:40] <= memory[addr_i+5];
                data_o[39:32] <= memory[addr_i+4];
                data_o[31:24] <= memory[addr_i+3];
                data_o[23:16] <= memory[addr_i+2];
                data_o[15:8]  <= memory[addr_i+1];
                data_o[7:0]   <= memory[addr_i];
            end
        end
    end

endmodule
