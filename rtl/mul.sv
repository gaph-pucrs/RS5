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

    mul_states_e mul_state;
    mul_states_e next_state;

    always_comb begin
        unique case (mul_state)
            ALBL:    next_state = enable_i ? ALBH : ALBL;
            ALBH:    next_state = AHBL;
            AHBL:    next_state = mul_low_i ? ALBL : AHBH;
            AHBH:    next_state = ALBL;
            default: next_state = ALBL;
        endcase
    end

    logic last_cycle;
    assign last_cycle = (mul_state == AHBH) || (mul_state == AHBL && mul_low_i) || (mul_state == ALBH && single_cycle_i);
    
    assign hold_o = enable_i && !last_cycle;
    
    logic should_stall;
    assign should_stall = stall && last_cycle;

    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mul_state <= ALBL;
        else if (!should_stall)
            mul_state <= next_state;
    end

    logic [16:0] op_al;
    logic [16:0] op_ah;
    logic [16:0] op_a;
    assign op_al = {single_cycle_i && signed_mode_i[0] && first_operand_i[15], first_operand_i[15: 0]};
    assign op_ah = {                  signed_mode_i[0] && first_operand_i[31], first_operand_i[31:16]};
    assign op_a  = (mul_state inside {ALBL, ALBH}) ? op_al : op_ah;

    logic [16:0] op_bl;
    logic [16:0] op_bh;
    logic [16:0] op_b;
    assign op_bl = {single_cycle_i && signed_mode_i[1] && second_operand_i[15], second_operand_i[15: 0]};
    assign op_bh = {                  signed_mode_i[1] && second_operand_i[31], second_operand_i[31:16]};
    assign op_b  = (mul_state inside {ALBL, AHBL}) ? op_bl : op_bh;

    logic [34:0] mac_result_r;

    logic signed_mult;
    assign signed_mult = (signed_mode_i != '0);

    logic [34:0] accum;
    always_comb begin
        unique case (mul_state)
            ALBL:    accum = '0;
            ALBH:    accum = {19'b0, mac_result_r[31:16]};
            AHBL:    accum = mul_low_i ? {19'b0, mac_result_r[31:16]} : mac_result_r;
            AHBH:    accum = {{17{signed_mult && mac_result_r[33]}}, mac_result_r[33:16]}; 
            default: accum = '0;
        endcase
    end

    logic [34:0] mac_result;
    assign mac_result = $signed(op_a) * $signed(op_b) + $signed(accum);
    
    logic [34:0] mac_result_partial;
    always_comb begin
        unique case (mul_state)
            ALBL, 
            AHBH:    mac_result_partial = mac_result;
            ALBH,
            AHBL:    mac_result_partial = mul_low_i ? {3'b0, mac_result[15:0], mac_result_r[15:0]} : mac_result;
            default: mac_result_partial = '0;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mac_result_r <= 0;
        else if (!should_stall)
            mac_result_r <= mac_result_partial;
    end

    assign result_o     = mac_result_partial[31:0];

endmodule
