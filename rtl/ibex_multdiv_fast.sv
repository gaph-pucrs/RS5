// Copyright lowRISC contributors.
// Copyright 2018 ETH Zurich and University of Bologna, see also CREDITS.md.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

`define OP_L 15:0
`define OP_H 31:16

/**
 * Fast Multiplier and Division
 *
 * 16x16 kernel multiplier and Long Division
 */

// `include "prim_assert.sv"


module ibex_multdiv_fast 
  import RS5_pkg::*;
#(
  parameter rv32m_e RV32M = RV32MFast
) (
  input  logic             clk_i,
  input  logic             rst_ni,
  input  logic             mult_en_i,  // dynamic enable signal, for FSM control
  input  logic             div_en_i,   // dynamic enable signal, for FSM control
  input  logic             mult_sel_i, // static decoder output, for data muxes
  input  logic             div_sel_i,  // static decoder output, for data muxes
  //input  md_op_e operator_i,
  input  iType_e           operator_i,
  input  logic  [1:0]      signed_mode_i,
  input  logic [31:0]      op_a_i,
  input  logic [31:0]      op_b_i,
  input  logic [33:0]      alu_adder_ext_i,
  input  logic [31:0]      alu_adder_i,
  input  logic [2:0]       alu_cbd_high_i,
  input  logic [2:0]       alu_cbd_low_i,
  input  logic             equal_to_zero_i,
  input  logic             data_ind_timing_i,
  input  logic[3:0]        kyber_compress_bits_i,

  output logic [32:0]      alu_operand_a_o,
  output logic [32:0]      alu_operand_b_o,

  input  logic             multdiv_ready_id_i,

  output logic [31:0]      multdiv_result_o,
  output logic             valid_o
);

  //import ibex_pkg::*;

  // Kyber Barrett reduction (CGG)
  logic [32:0] alu_operand_a_div, alu_operand_a_kyber;
  logic [32:0] alu_operand_b_div, alu_operand_b_kyber;
  logic [1:0] barrett_imd_we;

  // Both multiplier variants
  logic signed [34:0] mac_res_signed;
  logic        [34:0] mac_res_ext;
  logic        [33:0] accum;
  logic        sign_a, sign_b;
  logic        mult_valid;
  logic        signed_mult;

  // Results that become intermediate value depending on whether mul or div is being calculated
  logic [33:0] mac_res_d, op_remainder_d;
  // Raw output of MAC calculation
  logic [33:0] mac_res;

  logic [33:0] barrett_imd_d;

  // Divider signals
  logic        div_sign_a, div_sign_b;
  logic        is_greater_equal;
  logic        div_change_sign, rem_change_sign;
  logic [31:0] one_shift;
  logic [31:0] op_denominator_q;
  logic [31:0] op_numerator_q;
  logic [31:0] op_quotient_q;
  logic [31:0] op_denominator_d;
  logic [31:0] op_numerator_d;
  logic [31:0] op_quotient_d;
  logic [31:0] next_remainder;
  logic [32:0] next_quotient;
  logic [31:0] res_adder_h;
  logic        div_valid;
  logic [ 4:0] div_counter_q, div_counter_d;
  logic        multdiv_en;
  logic        mult_hold;
  logic        div_hold;
  logic        div_by_zero_d, div_by_zero_q;

  logic        mult_en_internal;
  logic        div_en_internal;

  typedef enum logic [2:0] {
    MD_IDLE, MD_ABS_A, MD_ABS_B, MD_COMP, MD_LAST, MD_CHANGE_SIGN, MD_FINISH
  } md_fsm_e;
  md_fsm_e md_state_q, md_state_d;

  logic unused_mult_sel_i;
  assign unused_mult_sel_i = mult_sel_i;

  assign mult_en_internal = mult_en_i & ~mult_hold;
  assign div_en_internal  = div_en_i & ~div_hold;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      div_counter_q    <= '0;
      md_state_q       <= MD_IDLE;
      op_numerator_q   <= '0;
      op_quotient_q    <= '0;
      div_by_zero_q    <= '0;
    end else if (div_en_internal) begin
      div_counter_q    <= div_counter_d;
      op_numerator_q   <= op_numerator_d;
      op_quotient_q    <= op_quotient_d;
      md_state_q       <= md_state_d;
      div_by_zero_q    <= div_by_zero_d;
    end
  end

  // `ASSERT_KNOWN(DivEnKnown, div_en_internal)
  // `ASSERT_KNOWN(MultEnKnown, mult_en_internal)
  // `ASSERT_KNOWN(MultDivEnKnown, multdiv_en)

  assign multdiv_en = mult_en_internal | div_en_internal;

  // Kyber Barrett reduction (CGG)
  assign alu_operand_a_o = div_sel_i ? alu_operand_a_div : alu_operand_a_kyber;
  assign alu_operand_b_o = div_sel_i ? alu_operand_b_div : alu_operand_b_kyber;


  logic [33:0]      imd_val_q[2];
  logic [33:0]      imd_val_d[2];
  logic [1:0]       imd_val_we;

  always_ff @(posedge clk_i or negedge rst_ni) begin
  	if (!rst_ni) begin
      imd_val_q[0] <= '0; 
      imd_val_q[1] <= '0;
    end else begin 
      if(imd_val_we[0]) imd_val_q[0] <= imd_val_d[0];
      if(imd_val_we[1]) imd_val_q[1] <= imd_val_d[1];
	end
  end

  // Intermediate value register shared with ALU
  assign imd_val_d[0] = div_sel_i ? op_remainder_d : mac_res_d;
  // assign imd_val_we[0] = multdiv_en;
  assign imd_val_we[0] = (operator_i == KYBER_MUL || operator_i == KYBER_COMPRESS) ? barrett_imd_we[0] : multdiv_en;

  // assign imd_val_d[1] = {2'b0, op_denominator_d};
  // assign imd_val_d[1] = (operator_i == KYBER_MUL || operator_i == KYBER_COMPRESS) ? mac_res_d : {2'b0, op_denominator_d};
  assign imd_val_d[1] = (operator_i == KYBER_MUL || operator_i == KYBER_COMPRESS) ? barrett_imd_d : {2'b0, op_denominator_d};
  // assign imd_val_we[1] = div_en_internal;
  assign imd_val_we[1] = (operator_i == KYBER_MUL || operator_i == KYBER_COMPRESS) ? barrett_imd_we[1] : div_en_internal;
  assign op_denominator_q = imd_val_q[1][31:0];

  logic [1:0] unused_imd_val;
  assign unused_imd_val = imd_val_q[1][33:32];
  logic unused_mac_res_ext;
  assign unused_mac_res_ext = mac_res_ext[34];

  assign signed_mult      = (signed_mode_i != 2'b00);
  assign multdiv_result_o = div_sel_i ? imd_val_q[0][31:0] : mac_res_d[31:0];

  // The single cycle multiplier uses three 17 bit multipliers to compute MUL instructions in a
  // single cycle and MULH instructions in two cycles.
  if (RV32M == RV32MSingleCycle) begin : gen_mult_single_cycle

    typedef enum logic {
      MULL, MULH
    } mult_fsm_e;
    mult_fsm_e mult_state_q, mult_state_d;

    logic signed [33:0] mult1_res, mult2_res, mult3_res;
    logic [33:0]        mult1_res_uns;
    logic [33:32]       unused_mult1_res_uns;
    logic [15:0]        mult1_op_a, mult1_op_b;
    logic [15:0]        mult2_op_a, mult2_op_b;
    logic [15:0]        mult3_op_a, mult3_op_b;
    logic               mult1_sign_a, mult1_sign_b;
    logic               mult2_sign_a, mult2_sign_b;
    logic               mult3_sign_a, mult3_sign_b;
    logic [33:0]        summand1, summand2, summand3;

    assign mult1_res = $signed({mult1_sign_a, mult1_op_a}) * $signed({mult1_sign_b, mult1_op_b});
    assign mult2_res = $signed({mult2_sign_a, mult2_op_a}) * $signed({mult2_sign_b, mult2_op_b});
    assign mult3_res = $signed({mult3_sign_a, mult3_op_a}) * $signed({mult3_sign_b, mult3_op_b});

    assign mac_res_signed = $signed(summand1) + $signed(summand2) + $signed(summand3);

    assign mult1_res_uns  = $unsigned(mult1_res);
    assign mac_res_ext    = $unsigned(mac_res_signed);
    assign mac_res        = mac_res_ext[33:0];

    assign sign_a = signed_mode_i[0] & op_a_i[31];
    assign sign_b = signed_mode_i[1] & op_b_i[31];

    // The first two multipliers are only used in state 1 (MULL). We can assign them statically.
    // al*bl
    assign mult1_sign_a = 1'b0;
    assign mult1_sign_b = 1'b0;
    assign mult1_op_a = op_a_i[`OP_L];
    assign mult1_op_b = op_b_i[`OP_L];

    // al*bh
    assign mult2_sign_a = 1'b0;
    assign mult2_sign_b = sign_b;
    assign mult2_op_a = op_a_i[`OP_L];
    assign mult2_op_b = op_b_i[`OP_H];

    // used in MULH
    assign accum[17:0] = imd_val_q[0][33:16];
    assign accum[33:18] = {16{signed_mult & imd_val_q[0][33]}};

    always_comb begin
      // Default values == MULL

      // ah*bl
      mult3_sign_a = sign_a;
      mult3_sign_b = 1'b0;
      mult3_op_a = op_a_i[`OP_H];
      mult3_op_b = op_b_i[`OP_L];

      summand1 = {18'h0, mult1_res_uns[`OP_H]};
      summand2 = $unsigned(mult2_res);
      summand3 = $unsigned(mult3_res);

      // mac_res = A*B[47:16], mult1_res = A*B[15:0]
      mac_res_d = {2'b0, mac_res[`OP_L], mult1_res_uns[`OP_L]};
      mult_valid = mult_en_i;
      mult_state_d = MULL;

      mult_hold = 1'b0;

      if (operator_i == KYBER_MUL)
        $fatal("Multiplication mod 3329 is only implemented for RV32M = RV32MFast");

      unique case (mult_state_q)

        MULL: begin

          if (operator_i != MUL) begin
            mac_res_d = mac_res;
            mult_valid = 1'b0;
            mult_state_d = MULH;
          end else begin
            mult_hold = ~multdiv_ready_id_i;
          end
        end

        MULH: begin
          // ah*bh
          mult3_sign_a = sign_a;
          mult3_sign_b = sign_b;
          mult3_op_a = op_a_i[`OP_H];
          mult3_op_b = op_b_i[`OP_H];
          mac_res_d = mac_res;

          summand1 = '0;
          summand2 = accum;
          summand3 = $unsigned(mult3_res);

          mult_state_d = MULL;
          mult_valid = 1'b1;

          mult_hold = ~multdiv_ready_id_i;
        end

        default: begin
          mult_state_d = MULL;
        end

      endcase // mult_state_q
    end

    always_ff @(posedge clk_i or negedge rst_ni) begin
      if (!rst_ni) begin
        mult_state_q <= MULL;
      end else begin
        if (mult_en_internal) begin
          mult_state_q <= mult_state_d;
        end
      end
    end

    assign unused_mult1_res_uns = mult1_res_uns[33:32];

    // States must be knwon/valid.
    // `ASSERT_KNOWN(IbexMultStateKnown, mult_state_q)

  // The fast multiplier uses one 17 bit multiplier to compute MUL instructions in 3 cycles
  // and MULH instructions in 4 cycles.
  end else begin : gen_mult_fast
    logic [15:0] mult_op_a;
    logic [15:0] mult_op_b;

    typedef enum logic [2:0] {
      ALBL, ALBH, AHBL, AHBH, KYBER_BARRETT_MULT_M, KYBER_BARRETT_MULT_Q, KYBER_BARRETT_SUB_ADJUST, KYBER_COMPRESS_STATE
    } mult_fsm_e;
    mult_fsm_e mult_state_q, mult_state_d;

    // The 2 MSBs of mac_res_ext (mac_res_ext[34:33]) are always equal since:
    // 1. The 2 MSBs of the multiplicants are always equal, and
    // 2. The 16 MSBs of the addend (accum[33:18]) are always equal.
    // Thus, it is safe to ignore mac_res_ext[34].
    assign mac_res_signed =
        $signed({sign_a, mult_op_a}) * $signed({sign_b, mult_op_b}) + $signed(accum);
    assign mac_res_ext    = $unsigned(mac_res_signed);
    assign mac_res        = mac_res_ext[33:0];

    logic[23:0] constant_5039_mult_operand;
    logic[36:0] constant_5039_mult_result;

    assign constant_5039_mult_operand = (operator_i == KYBER_COMPRESS) ? op_a_i[23:0] : imd_val_q[0][23:0];
    // assign constant_5039_mult_result = imd_val_q[0][23:0] * 13'd5039;
    // assign constant_5039_mult_result = (alu_adder_i[25:0] << 10) - (imd_val_q[0][23:0] << 6) - (imd_val_q[0][23:0] << 4) - (imd_val_q[0][23:0]);
    assign constant_5039_mult_result = (alu_adder_i[25:0] << 10) - (constant_5039_mult_operand << 6) - (constant_5039_mult_operand << 4) - (constant_5039_mult_operand);  // TODO: Ranges

    ///
    // Kyber Compress logic
    ///

    // logic[31:0] alu_adder_compress_shifted;
    logic[12:0] alu_adder_compress_shifted;
    logic compress_carry_in;

    always_comb begin

      unique case (kyber_compress_bits_i)

        4'd4:    alu_adder_compress_shifted = alu_adder_i[23:0] >> (24 - 4 - 1);
        4'd5:    alu_adder_compress_shifted = alu_adder_i[23:0] >> (24 - 5 - 1);
        4'd10:   alu_adder_compress_shifted = alu_adder_i[23:0] >> (24 - 10 - 1);
        4'd11:   alu_adder_compress_shifted = alu_adder_i[23:0] >> (24 - 11 - 1);
        default: alu_adder_compress_shifted = alu_adder_i[23:0] >> (24 - 1 - 1);

      endcase

    end

    assign compress_carry_in = alu_adder_compress_shifted[0];

    ///
    // Kyber Add/Sub logic (Fit ALU adder output to [0, 3328] range)
    ///

    logic adjust_adder_op_b_inv;

    logic[12:0] adjust_adder_high, adjust_adder_high_op_a, adjust_adder_high_op_b;
    logic adjust_adder_high_carry_in;
    logic[11:0] adjust_result_high;
    logic adjust_result_high_mux_sel;  // 0 for passthrough from ALU adder, 1 for "adjust_adder_high"

    logic[12:0] adjust_adder_low_op_a, adjust_adder_low_op_b;
    logic[13:0] adjust_adder_low;
    logic adjust_adder_low_carry_in;
    logic[11:0] adjust_result_low_mask;
    logic[11:0] adjust_result_low;
    logic adjust_result_low_mux_sel;  // 0 for passthrough from ALU adder, 1 for "adjust_adder_low"

    // Conditionally subtract Q = 3329 from ALU output when performing modular addition or last step of Barrett reduction in modular multiplication
    // Subtraction is performed by adding the two's complement of 3329 (op_a + (op_b = !13'd3329) + (carry_in = 1'b1))
    assign adjust_adder_op_b_inv = (operator_i == KYBER_ADD || operator_i == KYBER_MUL);

    assign adjust_adder_high_op_a = (operator_i inside {KYBER_CBD2, KYBER_CBD3}) ? {{10{alu_cbd_high_i[2]}}, alu_cbd_high_i} : alu_adder_i[28:16];
    assign adjust_adder_high_op_b = adjust_adder_op_b_inv ? (13'd3329 ^ {13{1'b1}}) : 13'd3329;
    assign adjust_adder_high_carry_in = adjust_adder_op_b_inv;
    assign adjust_adder_high = adjust_adder_high_op_a + adjust_adder_high_op_b + adjust_adder_high_carry_in;

    // Select "adjust_adder" when:
    //  ALU subtraction underflows (meaning addition to 3329 brings result back to [0, 3328] range)
    //  ALU addition overflows or subtraction by 3329 does NOT underflow (meaning subtraction by 3329 brings result back to [0, 3328] range)
    //  CBD sampling A-B < 0 (add Q to ALU output making sampled coeficient in [0, 3328] range)
    always_comb begin

      unique case (1'b1)
        // (operator_i == KYBER_ADD):  adjust_result_high_mux_sel = alu_adder_i[28] | !adjust_adder_high[12];
        (operator_i == KYBER_ADD):  adjust_result_high_mux_sel = !adjust_adder_high[12];
        // (operator_i == KYBER_SUB):  adjust_result_high_mux_sel = adjust_adder_high[12];
        (operator_i == KYBER_SUB):  adjust_result_high_mux_sel = !alu_adder_i[28];
        // (operator_i == KYBER_CBD2): adjust_result_high_mux_sel = adjust_adder_high[12];
        (operator_i == KYBER_CBD2): adjust_result_high_mux_sel = alu_cbd_high_i[2];
        // (operator_i == KYBER_CBD3): adjust_result_high_mux_sel = adjust_adder_high[12];
        (operator_i == KYBER_CBD3): adjust_result_high_mux_sel = alu_cbd_high_i[2];
        default:                            adjust_result_high_mux_sel = 1'b0;

      endcase

    end

    assign adjust_result_high = adjust_result_high_mux_sel ? adjust_adder_high[11:0] : adjust_adder_high_op_a[11:0];

    // TODO: This mask may not be needed for compress_d != 1;
    always_comb begin

      unique case (kyber_compress_bits_i)

        1: adjust_result_low_mask = 13'h001;
        4: adjust_result_low_mask = 13'h00F;
        5: adjust_result_low_mask = 13'h01F;
        10: adjust_result_low_mask = 13'h3FF;
        11: adjust_result_low_mask = 13'h7FF;
        default: adjust_result_low_mask = 13'hFFF;

      endcase

    end

    assign adjust_adder_low_op_a = (operator_i == KYBER_COMPRESS)                    ? {2'b00, alu_adder_compress_shifted[12:1]} :
                                   (operator_i inside {KYBER_CBD2, KYBER_CBD3} ? {{10{alu_cbd_low_i[2]}}, alu_cbd_low_i} :
                                                                                             alu_adder_i[12:0]);

    // assign adjust_adder_low_op_b = (operator_i == KYBER_COMPRESS) ? 13'd0 : (adjust_adder_op_b_inv ? !(13'd3329): 13'd3329);
    assign adjust_adder_low_op_b = (operator_i == KYBER_COMPRESS) ? 13'd0 : (adjust_adder_op_b_inv ? (13'd3329 ^ {13{1'b1}}): 13'd3329);
    assign adjust_adder_low_carry_in = (operator_i == KYBER_COMPRESS) ? compress_carry_in : adjust_adder_op_b_inv;
    assign adjust_adder_low = (adjust_adder_low_op_a + adjust_adder_low_op_b + adjust_adder_low_carry_in);

    // Select "adjust_adder" when:
    //  ALU subtraction underflows (meaning addition to 3329 brings result back to [0, 3328] range)
    //  ALU addition overflows or subtraction by 3329 does NOT underflow (meaning subtraction by 3329 brings result back to [0, 3328] range)
    //  Barrett reduction output is in [3329, 2*3329-1] range (subtraction by 3329 brings result back to [0, 3328] range)
    //  CBD sampling A-B < 0 (add Q to ALU output making sampled coeficient in [0, 3328] range)
    //  Compress + 1 for rounding up
    always_comb begin

      unique case (1'b1)
        // (operator_i == KYBER_ADD):    adjust_result_low_mux_sel = alu_adder_i[12] | !adjust_adder_low[12];
        (operator_i == KYBER_ADD):    adjust_result_low_mux_sel = !adjust_adder_low[12];
        // (operator_i == KYBER_SUB):    adjust_result_low_mux_sel = adjust_adder_low[12];
        (operator_i == KYBER_SUB):    adjust_result_low_mux_sel = !alu_adder_i[12];
        // (operator_i == KYBER_CBD2):   adjust_result_low_mux_sel = adjust_adder_low[12];
        (operator_i == KYBER_CBD2):   adjust_result_low_mux_sel = alu_cbd_low_i[2];
        // (operator_i == KYBER_CBD3):   adjust_result_low_mux_sel = adjust_adder_low[12];
        (operator_i == KYBER_CBD3):   adjust_result_low_mux_sel = alu_cbd_low_i[2];
        (operator_i == KYBER_MUL):      adjust_result_low_mux_sel = !adjust_adder_low[12];
        (operator_i == KYBER_COMPRESS): adjust_result_low_mux_sel = 1'b1;
        default:                              adjust_result_low_mux_sel = 1'b0;

      endcase

    end

    assign adjust_result_low = (adjust_result_low_mux_sel ? adjust_adder_low[11:0] : adjust_adder_low_op_a[11:0]) & adjust_result_low_mask;

    always_comb begin
      barrett_imd_d              = mac_res;
      mult_op_a                  = op_a_i[`OP_L];
      mult_op_b                  = op_b_i[`OP_L];
      sign_a                     = 1'b0;
      sign_b                     = 1'b0;
      accum                      = imd_val_q[0];
      mac_res_d                  = mac_res;
      mult_state_d               = mult_state_q;
      mult_valid                 = 1'b0;
      mult_hold                  = 1'b0;

      barrett_imd_we             = 2'b00;

      alu_operand_a_kyber = {imd_val_q[0] << 2, 1'b0};
      alu_operand_b_kyber = {imd_val_q[0], 1'b0};

      unique case (mult_state_q)

        ALBL: begin
          // al*bl
          mult_op_a = op_a_i[`OP_L];
          mult_op_b = op_b_i[`OP_L];
          sign_a    = 1'b0;
          sign_b    = 1'b0;
          accum     = '0;
          mac_res_d = mac_res;

          if (operator_i == KYBER_MUL) begin
            barrett_imd_we = 2'b01;
            mult_state_d = KYBER_BARRETT_MULT_M;

          end else if (operator_i == KYBER_COMPRESS) begin

            // a << 12 + a << 10 (shift by 10 in barret_adder_chain last operand (from ALU output))
            alu_operand_a_kyber = {{6{1'b0}}, op_a_i[23:0] << 2, 1'b0};
            alu_operand_b_kyber = {{8{1'b0}}, op_a_i[24:0], 1'b0};

            mult_op_a = op_a_i[`OP_L];
            mult_op_b = 16'hB760;  // Fractional part of 2**24/q, 12 bits of precision

            // mac_res_d = barrett_adder_chain;
            barrett_imd_d = constant_5039_mult_result[33:0];
            barrett_imd_we = 2'b11;
            mult_state_d = KYBER_COMPRESS_STATE;

          end else if (operator_i inside {KYBER_ADD, KYBER_SUB, KYBER_CBD2, KYBER_CBD3}) begin

            mac_res_d = {4'b0000, adjust_result_high[11:0], 4'b0000, adjust_result_low[11:0]};

            mult_valid = 1'b1;
            mult_state_d = ALBL;

          end else begin
            mult_state_d = ALBH;
          end

        end

        ALBH: begin
          // al*bh<<16
          mult_op_a = op_a_i[`OP_L];
          mult_op_b = op_b_i[`OP_H];
          sign_a    = 1'b0;
          sign_b    = signed_mode_i[1] & op_b_i[31];
          // result of AL*BL (in imd_val_q[0]) always unsigned with no carry
          accum     = {18'b0, imd_val_q[0][31:16]};
          if (operator_i == MUL) begin
            mac_res_d = {2'b0, mac_res[`OP_L], imd_val_q[0][`OP_L]};
          end else begin
            // MD_OP_MULH
            mac_res_d = mac_res;
          end
          mult_state_d = AHBL;
        end

        AHBL: begin
          // ah*bl<<16
          mult_op_a = op_a_i[`OP_H];
          mult_op_b = op_b_i[`OP_L];
          sign_a    = signed_mode_i[0] & op_a_i[31];
          sign_b    = 1'b0;
          if (operator_i == MUL) begin
            accum        = {18'b0, imd_val_q[0][31:16]};
            mac_res_d    = {2'b0, mac_res[15:0], imd_val_q[0][15:0]};
            mult_valid   = 1'b1;

            // Note no state transition will occur if mult_hold is set
            mult_state_d = ALBL;
            mult_hold    = ~multdiv_ready_id_i;
          end else begin
            accum        = imd_val_q[0];
            mac_res_d    = mac_res;
            mult_state_d = AHBH;
          end
        end

        AHBH: begin
          // only MD_OP_MULH here
          // ah*bh
          mult_op_a = op_a_i[`OP_H];
          mult_op_b = op_b_i[`OP_H];
          sign_a    = signed_mode_i[0] & op_a_i[31];
          sign_b    = signed_mode_i[1] & op_b_i[31];
          accum[17: 0]  = imd_val_q[0][33:16];
          accum[33:18]  = {16{signed_mult & imd_val_q[0][33]}};
          // result of AH*BL is not signed only if signed_mode_i == 2'b00
          mac_res_d    = mac_res;
          mult_valid   = 1'b1;

          // Note no state transition will occur if mult_hold is set
          mult_state_d = ALBL;
          mult_hold    = ~multdiv_ready_id_i;
        end

        KYBER_BARRETT_MULT_M: begin

          // a << 12 + a << 10 (shift by 10 in barret_adder_chain last operand (from ALU output))
          alu_operand_a_kyber = {imd_val_q[0] << 2, 1'b0};
          alu_operand_b_kyber = {imd_val_q[0], 1'b0};

          // mac_res_d = barrett_adder_chain >> 24;
          barrett_imd_d = (constant_5039_mult_result >> 24);
          barrett_imd_we = 2'b10;

          // Note no state transition will occur if mult_hold is set
          if (operator_i == KYBER_COMPRESS) begin
            mult_valid = 1'b1;
            mult_state_d = ALBL;
          end else
            mult_state_d = KYBER_BARRETT_MULT_Q;

          mult_hold    = ~multdiv_ready_id_i;
        end

        KYBER_BARRETT_MULT_Q: begin

          // alu_operand_a_kyber = {imd_val_q[1], 1'b0};
          // alu_operand_b_kyber = {imd_val_q[1] << 1, 1'b0};
          // mult_op_a = imd_val_q[0];
          mult_op_a = imd_val_q[1][15:0];
          mult_op_b = 16'd3329;

          accum = '0;
          // mac_res_d = barrett_adder_chain;
          // mac_res_d = mac_res;
          barrett_imd_d = mac_res;
          barrett_imd_we = 2'b10;

          // Note no state transition will occur if mult_hold is set
          mult_state_d = KYBER_BARRETT_SUB_ADJUST;
          mult_hold    = ~multdiv_ready_id_i;

        end

        KYBER_BARRETT_SUB_ADJUST: begin

          // alu_operand_a_kyber = {imd_val_q[0], 1'b0};
          alu_operand_a_kyber = {imd_val_q[0][31:0], 1'b1};
          alu_operand_b_kyber = {{imd_val_q[1][31:0] ^ {32{1'b1}}}, 1'b1};

          // mac_res_d  = barrett_adjust;
          mac_res_d  = {{4{1'b0}}, adjust_result_high, {4{1'b0}}, adjust_result_low};
          mult_valid = 1'b1;

          // Note no state transition will occur if mult_hold is set
          mult_state_d = ALBL;
          mult_hold    = ~multdiv_ready_id_i;

        end

        KYBER_COMPRESS_STATE: begin

          // Sum 16 higher bits of ibex_mult with result of constant 5039 multiplication
          alu_operand_a_kyber = {{16{1'b0}}, imd_val_q[0][31:16], 1'b0};
          alu_operand_b_kyber = {imd_val_q[1], 1'b1};

          // Right shift by 24 - d ALU output
          // Add 1 to shifted ALU output if 0.5 bit is set (rounds to nearest integer)

          mac_res_d  = {{20{1'b0}}, adjust_result_low};
          mult_valid = 1'b1;

          // Note no state transition will occur if mult_hold is set
          mult_state_d = ALBL;
          mult_hold    = ~multdiv_ready_id_i;

        end

        default: begin
          mult_state_d = ALBL;
        end

      endcase // mult_state_q
    end

    always_ff @(posedge clk_i or negedge rst_ni) begin
      if (!rst_ni) begin
        mult_state_q <= ALBL;
      end else begin
        if (mult_en_internal) begin
          mult_state_q <= mult_state_d;
        end
      end
    end

    // States must be knwon/valid.
    // `ASSERT_KNOWN(IbexMultStateKnown, mult_state_q)

  end // gen_mult_fast

  // Divider
  assign res_adder_h    = alu_adder_ext_i[32:1];
  logic [1:0] unused_alu_adder_ext;
  assign unused_alu_adder_ext = {alu_adder_ext_i[33],alu_adder_ext_i[0]};

  assign next_remainder = is_greater_equal ? res_adder_h[31:0] : imd_val_q[0][31:0];
  assign next_quotient  = is_greater_equal ? {1'b0, op_quotient_q} | {1'b0, one_shift} :
                                             {1'b0, op_quotient_q};

  assign one_shift      = {31'b0, 1'b1} << div_counter_q;

  // The adder in the ALU computes alu_operand_a_o + alu_operand_b_o which means
  // Remainder - Divisor. If Remainder - Divisor >= 0, is_greater_equal is equal to 1,
  // the next Remainder is Remainder - Divisor contained in res_adder_h and the
  always_comb begin
    if ((imd_val_q[0][31] ^ op_denominator_q[31]) == 1'b0) begin
      is_greater_equal = (res_adder_h[31] == 1'b0);
    end else begin
      is_greater_equal = imd_val_q[0][31];
    end
  end

  assign div_sign_a      = op_a_i[31] & signed_mode_i[0];
  assign div_sign_b      = op_b_i[31] & signed_mode_i[1];
  assign div_change_sign = (div_sign_a ^ div_sign_b) & ~div_by_zero_q;
  assign rem_change_sign = div_sign_a;


  always_comb begin
    div_counter_d    = div_counter_q - 5'h1;
    op_remainder_d   = imd_val_q[0];
    op_quotient_d    = op_quotient_q;
    md_state_d       = md_state_q;
    op_numerator_d   = op_numerator_q;
    op_denominator_d = op_denominator_q;
    // alu_operand_a_o  = {32'h0  , 1'b1};
    alu_operand_a_div  = {32'h0  , 1'b1};
    // alu_operand_b_o  = {~op_b_i, 1'b1};
    alu_operand_b_div  = {~op_b_i, 1'b1};
    div_valid        = 1'b0;
    div_hold         = 1'b0;
    div_by_zero_d    = div_by_zero_q;

    unique case (md_state_q)
      MD_IDLE: begin
        if (operator_i == DIV) begin
          // Check if the Denominator is 0
          // quotient for division by 0 is specified to be -1
          // Note with data-independent time option, the full divide operation will proceed as
          // normal and will naturally return -1
          op_remainder_d = '1;
          // SEC_CM: CORE.DATA_REG_SW.SCA
          md_state_d     = (!data_ind_timing_i && equal_to_zero_i) ? MD_FINISH : MD_ABS_A;
          // Record that this is a div by zero to stop the sign change at the end of the
          // division (in data_ind_timing mode).
          div_by_zero_d  = equal_to_zero_i;
        end else begin
          // Check if the Denominator is 0
          // remainder for division by 0 is specified to be the numerator (operand a)
          // Note with data-independent time option, the full divide operation will proceed as
          // normal and will naturally return operand a
          op_remainder_d = {2'b0, op_a_i};
          // SEC_CM: CORE.DATA_REG_SW.SCA
          md_state_d     = (!data_ind_timing_i && equal_to_zero_i) ? MD_FINISH : MD_ABS_A;
        end
        // 0 - B = 0 iff B == 0
        // alu_operand_a_o  = {32'h0  , 1'b1};
        alu_operand_a_div  = {32'h0  , 1'b1};
        // alu_operand_b_o  = {~op_b_i, 1'b1};
        alu_operand_b_div  = {~op_b_i, 1'b1};
        div_counter_d    = 5'd31;
      end

      MD_ABS_A: begin
        // quotient
        op_quotient_d   = '0;
        // A abs value
        op_numerator_d  = div_sign_a ? alu_adder_i : op_a_i;
        md_state_d      = MD_ABS_B;
        div_counter_d   = 5'd31;
        // ABS(A) = 0 - A
        // alu_operand_a_o = {32'h0  , 1'b1};
        alu_operand_a_div = {32'h0  , 1'b1};
        // alu_operand_b_o = {~op_a_i, 1'b1};
        alu_operand_b_div = {~op_a_i, 1'b1};
      end

      MD_ABS_B: begin
        // remainder
        op_remainder_d   = { 33'h0, op_numerator_q[31]};
        // B abs value
        op_denominator_d = div_sign_b ? alu_adder_i : op_b_i;
        md_state_d       = MD_COMP;
        div_counter_d    = 5'd31;
        // ABS(B) = 0 - B
        // alu_operand_a_o  = {32'h0  , 1'b1};
        alu_operand_a_div  = {32'h0  , 1'b1};
        // alu_operand_b_o  = {~op_b_i, 1'b1};
        alu_operand_b_div  = {~op_b_i, 1'b1};
      end

      MD_COMP: begin
        op_remainder_d  = {1'b0, next_remainder[31:0], op_numerator_q[div_counter_d]};
        op_quotient_d   = next_quotient[31:0];
        md_state_d      = (div_counter_q == 5'd1) ? MD_LAST : MD_COMP;
        // Division
        // alu_operand_a_o = {imd_val_q[0][31:0], 1'b1}; // it contains the remainder
        alu_operand_a_div = {imd_val_q[0][31:0], 1'b1}; // it contains the remainder
        // alu_operand_b_o = {~op_denominator_q[31:0], 1'b1};  // -denominator two's compliment
        alu_operand_b_div = {~op_denominator_q[31:0], 1'b1};  // -denominator two's compliment
      end

      MD_LAST: begin
        if (operator_i == DIV) begin
          // this time we save the quotient in op_remainder_d (i.e. imd_val_q[0]) since
          // we do not need anymore the remainder
          op_remainder_d = {1'b0, next_quotient};
        end else begin
          // this time we do not save the quotient anymore since we need only the remainder
          op_remainder_d = {2'b0, next_remainder[31:0]};
        end
        // Division
        // alu_operand_a_o  = {imd_val_q[0][31:0], 1'b1}; // it contains the remainder
        alu_operand_a_div  = {imd_val_q[0][31:0], 1'b1}; // it contains the remainder
        // alu_operand_b_o  = {~op_denominator_q[31:0], 1'b1};  // -denominator two's compliment
        alu_operand_b_div  = {~op_denominator_q[31:0], 1'b1};  // -denominator two's compliment

        md_state_d = MD_CHANGE_SIGN;
      end

      MD_CHANGE_SIGN: begin
        md_state_d  = MD_FINISH;
        if (operator_i == DIV) begin
          op_remainder_d = (div_change_sign) ? {2'h0, alu_adder_i} : imd_val_q[0];
        end else begin
          op_remainder_d = (rem_change_sign) ? {2'h0, alu_adder_i} : imd_val_q[0];
        end
        // ABS(Quotient) = 0 - Quotient (or Remainder)
        // alu_operand_a_o  = {32'h0  , 1'b1};
        alu_operand_a_div  = {32'h0  , 1'b1};
        // alu_operand_b_o  = {~imd_val_q[0][31:0], 1'b1};
        alu_operand_b_div  = {~imd_val_q[0][31:0], 1'b1};
      end

      MD_FINISH: begin
        // Hold result until ID stage is ready to accept it
        // Note no state transition will occur if div_hold is set
        md_state_d = MD_IDLE;
        div_hold   = ~multdiv_ready_id_i;
        div_valid   = 1'b1;
      end

      default: begin
        md_state_d = MD_IDLE;
      end
    endcase // md_state_q
  end

  assign valid_o = mult_valid | div_valid;

  // States must be knwon/valid.
  //`ASSERT(IbexMultDivStateValid, md_state_q inside {
  //    MD_IDLE, MD_ABS_A, MD_ABS_B, MD_COMP, MD_LAST, MD_CHANGE_SIGN, MD_FINISH})

`ifdef FORMAL
  `ifdef YOSYS
    `include "formal_tb_frag.svh"
  `endif
`endif

endmodule // ibex_mult
