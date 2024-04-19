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
    input   iType_e      instruction_operation_i,

    output  logic        hold_o,
    
    output  logic [31:0] mul_result_o
   
);

    typedef enum logic [1:0]{
         ALBL, ALBH, AHBL, AHBH
    } mul_fsm;
    mul_fsm mul_state, next_state;

    logic [34:0] mac_result, mac_result_partial;
    logic [34:0] mac_result_reg;
    logic [34:0] accum;
    logic [15:0] op_a;
    logic [15:0] op_b;
    logic        sign_a;
    logic        sign_b;
    logic [1:0]  signed_mode;
    logic        start;
    logic        signed_mult;

    always_comb begin
        unique case (instruction_operation_i)
            MULH:    signed_mode = 2'b11;
            MULHSU:  signed_mode = 2'b01;
            default: signed_mode = 2'b00;
        endcase
    end

    assign signed_mult  = (signed_mode != 2'b00);
    assign mul_result_o = mac_result_partial[31:0];
    assign start        = (mul_state == ALBL && instruction_operation_i inside {MUL, MULH, MULHU, MULHSU});        
    
    assign mac_result   = $signed({sign_a, op_a}) * $signed({sign_b, op_b}) + $signed(accum);     

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mac_result_reg <= 0;
        end 
        else begin
            mac_result_reg <= mac_result_partial;
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
                sign_a         = 1'b0;
                sign_b         = 1'b0;
                accum          = '0;
                mac_result_partial = mac_result;
                if (start == 1'b1) begin 
                    next_state = ALBH;
                    hold_o     = 1'b1;
                end else begin
                    next_state = ALBL;
                    hold_o     = 1'b0;
                end
            end
            ALBH: begin
                op_a   = first_operand_i[15:0];
                op_b   = second_operand_i[31:16];
                sign_a = '0;
                sign_b = (second_operand_i[31] & signed_mode[1]);

                accum  = {19'b0, mac_result_reg[31:16]};

                if (instruction_operation_i == MUL) begin
                    mac_result_partial = {3'b0, mac_result[15:0], mac_result_reg[15:0]};
                end 
                else begin
                    mac_result_partial = mac_result;
                end

                next_state = AHBL;
                hold_o     = 1'b1;
            end
            AHBL: begin
                op_a   = first_operand_i[31:16];
                op_b   = second_operand_i[15:0];
                sign_a = (first_operand_i[31] & signed_mode[0]);
                sign_b = '0;

                if (instruction_operation_i == MUL) begin
                    accum               = {19'b0, mac_result_reg[31:16]};
                    mac_result_partial  = {3'b0, mac_result[15:0], mac_result_reg[15:0]};

                    hold_o     = 1'b0;
                    next_state = ALBL;
                end
                else begin
                    mac_result_partial = mac_result;
                    accum      = mac_result_reg;
                    hold_o     = 1'b1;
                    next_state = AHBH;
                end
            end
            AHBH: begin
                op_a    = first_operand_i[31:16];
                op_b    = second_operand_i[31:16];

                sign_a  = (signed_mode[0] & first_operand_i[31]);
                sign_b  = (signed_mode[1] & second_operand_i[31]);

                accum[17:0]  = mac_result_reg[33:16];
                accum[34:18] = {17{signed_mult & mac_result_reg[33]}};

                mac_result_partial = mac_result;

                next_state = ALBL;
                hold_o     = 1'b0;
            end
            default: begin
                next_state = ALBL;
                hold_o     = 1'b0;
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
