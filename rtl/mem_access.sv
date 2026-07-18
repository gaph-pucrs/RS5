`include "RS5_pkg.sv"

module mem_access
    import RS5_pkg::*;
(
    input  logic        clk,
    input  logic        reset_n,
    input  logic        stall,

    /* Registered input from execute */
    input  wb_ctrl_t    ctrl_i,
    input  logic [31:0] result_i,
    input  logic  [4:0] rd_i,

    /* MMU interface */
    input  logic        load_access_fault_i,

    /* Registered outputs to retire */
    output wb_ctrl_t    ctrl_o,
    output logic [31:0] result_o,
    output logic  [4:0] rd_o
);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            ctrl_o <= '0;
        else if (!stall) begin
            ctrl_o        <= ctrl_i;
            ctrl_o.rd_we  <= ctrl_i.rd_we && !load_access_fault_i;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            rd_o <= '0;
        end
        else if (!stall) begin
            rd_o <= rd_i;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            result_o <= '0;
        end
        else if (!stall) begin
            result_o <= result_i;
        end
    end

endmodule
