module sha2_unit import RS5_pkg::*;  #(
    parameter LOGIC_GATING = 1  // Gate sub-module inputs to save toggling
)(

  input  logic       sha2_en_i,
  input  iType_e     sha2_op_i,

  input  logic[31:0] op_a_i,
  input  logic[31:0] op_b_i,
  output logic[31:0] sha2_result_o

);

  `define GATE_INPUTS(LEN,SEL,SIG) (LOGIC_GATING ? ({LEN{SEL}} & SIG[LEN-1:0]) : SIG[LEN-1:0])
  `define ROTR(x, n) ($bits(x)'(x >> n) | $bits(x)'(x << ($bits(x) - n)))
  
  wire[31:0] op_a_gated = `GATE_INPUTS(32, sha2_en_i, op_a_i);
  wire[31:0] op_b_gated = `GATE_INPUTS(32, sha2_en_i , op_b_i);

  always_comb begin

    sha2_result_o = `ROTR(op_a_gated, 7) ^ `ROTR(op_a_gated, 18) ^ (op_a_gated >> 3);

    unique case (sha2_op_i)

      // SHA256 instructions
      SIG0: sha2_result_o = `ROTR(op_a_gated, 7) ^ `ROTR(op_a_gated, 18) ^ (op_a_gated >> 3);
      SIG1: sha2_result_o = `ROTR(op_a_gated, 17) ^ `ROTR(op_a_gated, 19) ^ (op_a_gated >> 10);
      SUM0: sha2_result_o = `ROTR(op_a_gated, 2) ^ `ROTR(op_a_gated, 13) ^ `ROTR(op_a_gated, 22);
      SUM1: sha2_result_o = `ROTR(op_a_gated, 6) ^ `ROTR(op_a_gated, 11) ^ `ROTR(op_a_gated, 25);

      // SHA512 instructions
      SIG0H: sha2_result_o = (op_a_gated >> 1) ^ (op_a_gated >> 7) ^ (op_a_gated >> 8) ^ (op_b_gated << 31) ^ (op_b_gated << 24);
      SIG0L: sha2_result_o = (op_a_gated >> 1) ^ (op_a_gated >> 7) ^ (op_a_gated >> 8) ^ (op_b_gated << 31) ^ (op_b_gated << 25) ^ (op_b_gated << 24);
      SIG1H: sha2_result_o = (op_a_gated << 3) ^ (op_a_gated >> 6) ^ (op_a_gated >> 19) ^ (op_b_gated >> 29) ^ (op_b_gated << 13);
      SIG1L: sha2_result_o = (op_a_gated << 3) ^ (op_a_gated >> 6) ^ (op_a_gated >> 19) ^ (op_b_gated >> 29) ^ (op_b_gated << 26) ^ (op_b_gated << 13);
      SUM0R: sha2_result_o = (op_a_gated << 25) ^ (op_a_gated << 30) ^ (op_a_gated >> 28) ^ (op_b_gated >> 7) ^ (op_b_gated >> 2) ^ (op_b_gated << 4);
      SUM1R: sha2_result_o = (op_a_gated << 23) ^ (op_a_gated >> 14) ^ (op_a_gated >> 18) ^ (op_b_gated >> 9) ^ (op_b_gated << 18) ^ (op_b_gated << 14);

      //default: sha2_result_o = sha2_result_o;

    endcase

  end

  `undef GATE_INPUTS
  `undef ROTR
endmodule
