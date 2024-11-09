// Copyright lowRISC contributors.
// Copyright 2018 ETH Zurich and University of Bologna, see also CREDITS.md.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

`include "RS5_pkg.sv"

module mul
    import RS5_pkg::*;
(
    input   logic        clk,
    input   logic        reset_n,
    input   logic        stall,

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,
    input   logic [ 1:0] signed_mode_i,
    input   logic        enable_i,
    input   logic        mul_low_i,
    input   logic        single_cycle_i,

    output  logic        hold_o,
    output  logic [31:0] result_o
);

    typedef enum logic [3:0] {
        ALBL = 4'b0001, 
        ALBH = 4'b0010, 
        AHBL = 4'b0100, 
        AHBH = 4'b1000
    } mul_states_e;

    mul_states_e mul_state, next_state;

    logic [34:0] mac_result, mac_result_partial;
    logic [34:0] mac_result_reg;
    logic [34:0] accum;
    logic [15:0] op_a;
    logic [15:0] op_b;
    logic        sign_a;
    logic        sign_b;
    logic        start;
    logic        signed_mult;

    assign signed_mult  = (signed_mode_i != '0);
    assign start        = enable_i && (mul_state == ALBL);
    assign result_o     = mac_result_partial[31:0];
    assign mac_result   = $signed({sign_a, op_a}) * $signed({sign_b, op_b}) + $signed(accum);

    logic hold;
    assign hold_o = start || hold;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mac_result_reg <= 0;
        else if (!(((mul_state == AHBH) || (mul_state == AHBL && mul_low_i)) && stall))
            mac_result_reg <= mac_result_partial;
    end

    always_comb begin
        unique case (mul_state)
            ALBL:    next_state = start ? ALBH : ALBL;
            ALBH:    next_state = AHBL;
            AHBL:    next_state = mul_low_i ? ALBL : AHBH;
            AHBH:    next_state = ALBL;
            default: next_state = ALBL;
        endcase
    end

    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mul_state <= ALBL;
        else if (!(((mul_state == AHBH) || (mul_state == AHBL && mul_low_i)) && stall))
            mul_state <= next_state;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hold <= 1'b0;
        end
        else begin
            unique case (mul_state)
                ALBL:    hold <= start;
                ALBH:    hold <= !mul_low_i;
                default: hold <= 1'b0;
            endcase
        end
    end

    always_comb begin
        unique case (mul_state)
            ALBL,
            ALBH:    op_a = first_operand_i[15:0];
            AHBL,
            AHBH:    op_a = first_operand_i[31:16];
            default: op_a = '0;
        endcase
    end

    always_comb begin
        unique case (mul_state)
            ALBL,
            AHBL:    op_b = second_operand_i[15:0];
            ALBH,
            AHBH:    op_b = second_operand_i[31:16];
            default: op_b = '0;
        endcase
    end

    always_comb begin
        unique case (mul_state)
            ALBL:    accum = '0;
            ALBH:    accum = {19'b0, mac_result_reg[31:16]};
            AHBL:    accum = mul_low_i ? {19'b0, mac_result_reg[31:16]} : mac_result_reg;
            AHBH:    accum = {{17{signed_mult && mac_result_reg[33]}}, mac_result_reg[33:16]}; 
            default: accum = '0;
        endcase
    end

    always_comb begin
        unique case (mul_state)
            ALBL:    sign_a = single_cycle_i && first_operand_i[31] && signed_mode_i[0];
            ALBH:    sign_a = 1'b0;
            AHBL,
            AHBH:    sign_a = signed_mode_i[0] && first_operand_i[31];
            default: sign_a = 1'b0;
        endcase
    end

    always_comb begin
        unique case (mul_state)
            ALBL:    sign_b = single_cycle_i && second_operand_i[31] && signed_mode_i[1];
            AHBL:    sign_b = 1'b0;
            ALBH,
            AHBH:    sign_b = signed_mode_i[1] && second_operand_i[31];
            default: sign_b = 1'b0;
        endcase
    end

    always_comb begin
        unique case (mul_state)
            ALBL, 
            AHBH:    mac_result_partial = mac_result;
            ALBH,
            AHBL:    mac_result_partial = mul_low_i ? {3'b0, mac_result[15:0], mac_result_reg[15:0]} : mac_result;
            default: mac_result_partial = '0;
        endcase
    end

endmodule
