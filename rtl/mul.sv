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

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,
    input   logic [ 1:0] signed_mode_i,
    input   logic        enable_i,
    input   logic        mul_low_i,
    input   logic        single_cycle_i,

    output  logic        hold_o,
    output  logic [31:0] result_o
);

    typedef enum logic [1:0]{
        ALBL, ALBH, AHBL, AHBH
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

    assign signed_mult  = (signed_mode_i != 2'b00);
    assign result_o = mac_result_partial[31:0];
    assign start        = (mul_state == ALBL && enable_i == 1'b1);

    assign mac_result   = $signed({sign_a, op_a}) * $signed({sign_b, op_b}) + $signed(accum);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mac_result_reg <= 0;
        end
        else begin
            mac_result_reg <= mac_result_partial;
        end
    end

    logic hold;

    assign hold_o = start || hold;

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
        op_a           = first_operand_i[15:0];
        op_b           = second_operand_i[15:0];
        accum          = mac_result_reg;
        sign_a         = '0;
        sign_b         = '0;
        mac_result_partial = mac_result;

        unique case (mul_state)
            ALBL: begin
                op_a           = first_operand_i[15:0];
                op_b           = second_operand_i[15:0];
                sign_a         = (single_cycle_i) ? (first_operand_i [31] & signed_mode_i[0]) : 1'b0;
                sign_b         = (single_cycle_i) ? (second_operand_i[31] & signed_mode_i[1]) : 1'b0;
                accum          = '0;
                mac_result_partial = mac_result;
                if (start == 1'b1) begin
                    next_state = ALBH;
                end else begin
                    next_state = ALBL;
                end
            end
            ALBH: begin
                op_a   = first_operand_i[15:0];
                op_b   = second_operand_i[31:16];
                sign_a = '0;
                sign_b = (second_operand_i[31] & signed_mode_i[1]);

                accum  = {19'b0, mac_result_reg[31:16]};

                if (mul_low_i) begin
                    mac_result_partial = {3'b0, mac_result[15:0], mac_result_reg[15:0]};
                end
                else begin
                    mac_result_partial = mac_result;
                end

                next_state = AHBL;
            end
            AHBL: begin
                op_a   = first_operand_i[31:16];
                op_b   = second_operand_i[15:0];
                sign_a = (first_operand_i[31] & signed_mode_i[0]);
                sign_b = '0;

                if (mul_low_i) begin
                    accum               = {19'b0, mac_result_reg[31:16]};
                    mac_result_partial  = {3'b0, mac_result[15:0], mac_result_reg[15:0]};

                    next_state = ALBL;
                end
                else begin
                    mac_result_partial = mac_result;
                    accum      = mac_result_reg;
                    next_state = AHBH;
                end
            end
            AHBH: begin
                op_a    = first_operand_i[31:16];
                op_b    = second_operand_i[31:16];

                sign_a  = (signed_mode_i[0] & first_operand_i[31]);
                sign_b  = (signed_mode_i[1] & second_operand_i[31]);

                accum[17:0]  = mac_result_reg[33:16];
                accum[34:18] = {17{signed_mult & mac_result_reg[33]}};

                mac_result_partial = mac_result;

                next_state = ALBL;
            end
        endcase
    end

    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mul_state <= ALBL;
        end else begin
            mul_state <= next_state;
        end
    end

endmodule
