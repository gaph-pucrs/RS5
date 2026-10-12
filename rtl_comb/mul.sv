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

    typedef enum logic [4:0] {
        IDLE = 5'b00001,
        ALBL = 5'b00010,
        ALBH = 5'b00100,
        AHBL = 5'b01000,
        AHBH = 5'b10000
    } mul_states_e;

    mul_states_e mul_state;
    mul_states_e next_state;

    always_comb begin
        unique case (mul_state)
            IDLE:    next_state = enable_i       ? ALBL : IDLE;
            ALBL:    next_state = single_cycle_i ? IDLE : ALBH;
            ALBH:    next_state = AHBL;
            AHBL:    next_state = mul_low_i      ? IDLE : AHBH;
            AHBH:    next_state = IDLE;
            default: next_state = IDLE;
        endcase
    end

    logic last_cycle;
    assign last_cycle = (mul_state == AHBH) || (mul_state == AHBL && mul_low_i) || (mul_state == ALBL && single_cycle_i);

    logic should_stall;
    assign should_stall = stall && last_cycle;

    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mul_state <= ALBL;
        else if (!should_stall)
            mul_state <= next_state;
    end

    assign hold_o = enable_i && !last_cycle;

    logic [16:0] op_al;
    logic [16:0] op_ah;
    assign op_al = {single_cycle_i && signed_mode_i[0] && first_operand_i[15], first_operand_i[15: 0]};
    assign op_ah = {                  signed_mode_i[0] && first_operand_i[31], first_operand_i[31:16]};

    logic [16:0] op_a;
    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            op_a <= '0;
        end
        else begin
            unique case (mul_state)
                IDLE: op_a <= op_al;
                ALBH: op_a <= op_ah;
                default: ;
            endcase
        end
    end

    logic [16:0] op_bl;
    logic [16:0] op_bh;
    assign op_bl = {single_cycle_i && signed_mode_i[1] && second_operand_i[15], second_operand_i[15: 0]};
    assign op_bh = {                  signed_mode_i[1] && second_operand_i[31], second_operand_i[31:16]};

    logic [16:0] op_b;
    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            op_b <= '0;
        end
        else begin
            unique case (mul_state)
                IDLE,
                ALBH: op_b <= op_bl;
                ALBL,
                AHBL: op_b <= !should_stall ? op_bh : op_b;
                default: ;
            endcase
        end
    end

    logic [15:0] mac_result_r;

    logic signed_mult;
    assign signed_mult = (signed_mode_i != '0);

    logic [34:0] mac_result_partial;
    logic [34:0] accum;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            accum <= '0;
        end
        else if (!should_stall) begin
            unique case (mul_state)
                IDLE:    accum <= '0;
                ALBL:    accum <= {19'b0, mac_result_partial[31:16]};
                ALBH:    accum <= mul_low_i ? {19'b0, mac_result_partial[31:16]} : mac_result_partial;
                AHBL:    accum <= {{17{signed_mult && mac_result_partial[33]}}, mac_result_partial[33:16]};
                default: ;
            endcase
        end
    end

    logic [34:0] mac_result;
    assign mac_result = $signed(op_a) * $signed(op_b) + $signed(accum);

    always_comb begin
        unique case (mul_state)
            ALBL,
            AHBH:    mac_result_partial = mac_result;
            ALBH,
            AHBL:    mac_result_partial = mul_low_i ? {3'b0, mac_result[15:0], mac_result_r} : mac_result;
            default: mac_result_partial = '0;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mac_result_r <= 0;
        else if (!should_stall)
            mac_result_r <= mac_result_partial[15:0];
    end

    assign result_o     = mac_result_partial[31:0];

endmodule
