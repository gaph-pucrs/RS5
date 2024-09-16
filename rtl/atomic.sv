`include "RS5_pkg.sv"

module atomic 
    import RS5_pkg::*;
(
    input  logic         clk,
    input  logic         reset_n,
    input  iTypeAtomic_e atomic_operation_i,

    input  logic [31:0]  rs1_i,
    input  logic [31:0]  rs2_i,

    output logic [31:0]  result_o,
    output logic         hold_o
);






endmodule
