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

    input   logic [31:0] alu_adder_i,

    input   logic  [2:0]  alu_cbd_high_i,
    input   logic  [2:0]  alu_cbd_low_i,

    input   logic  [3:0]  kyber_compress_bits_i,

    input   iType_e      operator_i,
    input   logic        is_xkyber_i,

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,
    input   logic [ 1:0] signed_mode_i,
    input   logic        enable_i,
    input   logic        mul_low_i,
    input   logic        single_cycle_i,

    output  logic [31:0] alu_operand_a_kyber,
    output  logic [31:0] alu_operand_b_kyber,

    output  logic        hold_o,
    output  logic [31:0] result_o
);

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

    assign adjust_adder_low_op_a = (operator_i == KYBER_COMPRESS)              ? {2'b00, alu_adder_compress_shifted[12:1]} :
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

    typedef enum logic [17:0] {
        IDLE                         = 18'b000000000000000001,
        ALBL                         = 18'b000000000000000010,
        ALBH                         = 18'b000000000000000100,
        AHBL                         = 18'b000000000000001000,
        AHBH                         = 18'b000000000000010000,
        L1_STAGE0_LOW                = 18'b000000000000100000,
        L1_STAGE0_HIGH               = 18'b000000000001000000, 
        L1_STAGE1_LOW                = 18'b000000000010000000,
        L1_STAGE1_HIGH               = 18'b000000000100000000,
        L1_STAGE2_LOW                = 18'b000000001000000000,
        L1_STAGE2_HIGH               = 18'b000000010000000000,
        L1_STAGE3_LOW                = 18'b000000100000000000,
        L1_STAGE3_HIGH               = 18'b000001000000000000,
        L1_STAGE4_LOW                = 18'b000010000000000000,
        L1_STAGE4_HIGH               = 18'b000100000000000000,
        KYBER_BARRETT_L2             = 18'b001000000000000000, 
        KYBER_BARRETT_L3             = 18'b010000000000000000,
        KYBER_BARRETT_L4             = 18'b100000000000000000
    } mul_states_e;

    mul_states_e mul_state;
    mul_states_e next_state;

    always_comb begin
        next_state = IDLE;
        unique case (mul_state)
            IDLE:                         next_state = (enable_i) ? ((operator_i == KYBER_MUL) ? L1_STAGE0_LOW : ALBL) : IDLE;
            ALBL:                         next_state = single_cycle_i ? IDLE : ALBH;
            ALBH:                         next_state = AHBL;
            AHBL:                         next_state = mul_low_i      ? IDLE : AHBH;
            AHBH:                         next_state = IDLE;
            L1_STAGE0_LOW:                next_state = L1_STAGE0_HIGH;
            L1_STAGE0_HIGH:               next_state = L1_STAGE1_LOW;
            L1_STAGE1_LOW:                next_state = L1_STAGE1_HIGH;
            L1_STAGE1_HIGH:               next_state = L1_STAGE2_LOW;
            L1_STAGE2_LOW:                next_state = L1_STAGE2_HIGH;
            L1_STAGE2_HIGH:               next_state = L1_STAGE3_LOW;
            L1_STAGE3_LOW:                next_state = L1_STAGE3_HIGH;
            L1_STAGE3_HIGH:               next_state = L1_STAGE4_LOW;
            L1_STAGE4_LOW :               next_state = L1_STAGE4_HIGH;
            L1_STAGE4_HIGH:               next_state = KYBER_BARRETT_L2;
            KYBER_BARRETT_L2:             next_state = KYBER_BARRETT_L3;
            KYBER_BARRETT_L3:             next_state = KYBER_BARRETT_L4;
            KYBER_BARRETT_L4:             next_state = IDLE;  
            default:                      next_state = IDLE;
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

    logic xkyber_valid;

    assign hold_o = enable_i && (!last_cycle && !xkyber_valid);

    logic [16:0] op_al;
    logic [16:0] op_ah;
    assign op_al = {single_cycle_i && signed_mode_i[0] && first_operand_i[15], first_operand_i[15: 0]};
    assign op_ah = {                  signed_mode_i[0] && first_operand_i[31], first_operand_i[31:16]};

    logic [15:0] mult_kyber_op_a, mult_kyber_op_b; 

    logic [16:0] op_a;
    always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            op_a <= '0;
        end
        else begin
            unique case (mul_state)
                IDLE: op_a <= op_al;
                ALBH: op_a <= op_ah;
                default: op_a <= mult_kyber_op_a;
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
                default: op_b <= mult_kyber_op_b;
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
                default: accum <= '0;
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

    logic [31:0] result_xkyber;

    assign result_xkyber = {{4{1'b0}}, adjust_result_high, {4{1'b0}}, adjust_result_low};

    assign result_o = (is_xkyber_i) ? result_xkyber : mac_result_partial[31:0];

//kyber part!
    
    logic [31:0] alu_operand_a_kyber_mul, alu_operand_b_kyber_mul;

    logic [34:0] temp0, temp0_last_stage;

    assign temp0 = (mul_state != KYBER_BARRETT_L4) ? mac_result : temp0_last_stage;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin 
            temp0_last_stage <= '0;
        end else begin 
            if (mul_state == L1_STAGE0_LOW) temp0_last_stage <= mac_result; //in idle mac_res_d will hold the temp0 value
        end
    end

    logic [36:0] temp1;

    logic [35:0] temp1_shift;
    logic        carry_reg;

    
    
    // ── always_ff ──────────────────────────────────────────────────────────────
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            temp1     <= '0;
            carry_reg <= '0;
        end else begin
            unique case (mul_state)

                IDLE: begin
                    temp1     <= '0;
                    carry_reg <= '0;
                end

                // -temp0
                L1_STAGE0_LOW: begin
                    temp1[31:0]  <= alu_adder_i;
                    // REMOVIDO: temp1[36:32] <= '0; <-- NUNCA zere a parte alta do acumulador no meio do LOW
                    carry_reg <= (alu_adder_i < temp1[31:0]) ? 1'b1 : 1'b0;
                end
                L1_STAGE0_HIGH: begin
                    temp1[36:32] <= alu_adder_i[4:0];
                    carry_reg    <= '0;
                end

                // -(temp0<<4)
                L1_STAGE1_LOW: begin
                    temp1[31:0]  <= alu_adder_i;
                    carry_reg    <= (alu_adder_i < temp1[31:0]) ? 1'b1 : 1'b0;
                end
                L1_STAGE1_HIGH: begin
                    temp1[36:32] <= alu_adder_i[4:0];
                    carry_reg    <= '0;
                end

                // -(temp0<<6)
                L1_STAGE2_LOW: begin
                    temp1[31:0]  <= alu_adder_i;
                    carry_reg    <= (alu_adder_i < temp1[31:0]) ? 1'b1 : 1'b0;
                end
                L1_STAGE2_HIGH: begin
                    temp1[36:32] <= alu_adder_i[4:0];
                    carry_reg    <= '0;
                end

                // +(temp0<<10)
                L1_STAGE3_LOW: begin
                    temp1[31:0]  <= alu_adder_i;
                    // REMOVIDO: temp1[36:32] <= '0;
                    carry_reg    <= (alu_adder_i < temp1[31:0]) ? 1'b1 : 1'b0;
                end
                L1_STAGE3_HIGH: begin
                    temp1[36:32] <= alu_adder_i[4:0];
                    carry_reg    <= '0;
                end

                // +(temp0<<12)
                L1_STAGE4_LOW: begin
                    temp1[31:0]  <= alu_adder_i;
                    // REMOVIDO: temp1[36:32] <= '0;
                    carry_reg    <= (alu_adder_i < temp1[31:0]) ? 1'b1 : 1'b0;
                end
                L1_STAGE4_HIGH: begin
                    temp1[36:32] <= alu_adder_i[4:0];
                    carry_reg    <= '0;
                end

                KYBER_BARRETT_L3: begin
                    temp1 <= {2'b00, mac_result};
                end

                default: ;

            endcase
        end
    end

    // ── always_comb ────────────────────────────────────────────────────────────
    always_comb begin
        temp1_shift = '0;
        alu_operand_a_kyber_mul = '0;
        alu_operand_b_kyber_mul = '0;

        unique case (mul_state)

            // -temp0: LOW
            L1_STAGE0_LOW: begin
                // CORREÇÃO 1: Estica para 36 bits PRIMEIRO, depois negativa (Complemento de 2 real)
                temp1_shift             = -(36'(temp0[23:0])); 
                alu_operand_a_kyber_mul = '0;
                alu_operand_b_kyber_mul = temp1_shift[31:0];
            end
            // -temp0: HIGH
            L1_STAGE0_HIGH: begin
                temp1_shift             = -(36'(temp0[23:0]));
                // CORREÇÃO 2: Extensão de Sinal (Preserva os '1's do número negativo)
                alu_operand_a_kyber_mul = {{28{temp1_shift[35]}}, temp1_shift[35:32]};
                alu_operand_b_kyber_mul = {{27{temp1[36]}}, temp1[36:32]} + {31'd0, carry_reg};
            end

            // -(temp0<<4): LOW
            L1_STAGE1_LOW: begin
                temp1_shift             = -(36'(temp0[23:0]) << 4);
                alu_operand_a_kyber_mul = temp1[31:0];
                alu_operand_b_kyber_mul = temp1_shift[31:0];
            end
            // -(temp0<<4): HIGH
            L1_STAGE1_HIGH: begin
                temp1_shift             = -(36'(temp0[23:0]) << 4);
                alu_operand_a_kyber_mul = {{27{temp1[36]}}, temp1[36:32]} + {31'd0, carry_reg};
                // CORREÇÃO 2: Extensão de Sinal
                alu_operand_b_kyber_mul = {{28{temp1_shift[35]}}, temp1_shift[35:32]};
            end

            // -(temp0<<6): LOW
            L1_STAGE2_LOW: begin
                temp1_shift             = -(36'(temp0[23:0]) << 6);
                alu_operand_a_kyber_mul = temp1[31:0];
                alu_operand_b_kyber_mul = temp1_shift[31:0];
            end
            // -(temp0<<6): HIGH
            L1_STAGE2_HIGH: begin
                temp1_shift             = -(36'(temp0[23:0]) << 6);
                alu_operand_a_kyber_mul = {{27{temp1[36]}}, temp1[36:32]} + {31'd0, carry_reg};
                // CORREÇÃO 2: Extensão de Sinal
                alu_operand_b_kyber_mul = {{28{temp1_shift[35]}}, temp1_shift[35:32]};
            end

            // +(temp0<<10): LOW
            L1_STAGE3_LOW: begin
                temp1_shift             = 36'(temp0[23:0]) << 10;
                alu_operand_a_kyber_mul = temp1_shift[31:0];
                alu_operand_b_kyber_mul = temp1[31:0];
            end
            // +(temp0<<10): HIGH
            L1_STAGE3_HIGH: begin
                temp1_shift             = 36'(temp0[23:0]) << 10;
                // AQUI É POSITIVO: Zero-padding {28'd0} está correto! (Ajustado para [35:32] por segurança)
                alu_operand_a_kyber_mul = {28'd0, temp1_shift[35:32]};
                alu_operand_b_kyber_mul = {{27{temp1[36]}}, temp1[36:32]} + {31'd0, carry_reg};
            end

            // +(temp0<<12): LOW
            L1_STAGE4_LOW: begin
                temp1_shift             = 36'(temp0[23:0]) << 12;
                alu_operand_a_kyber_mul = temp1_shift[31:0];
                alu_operand_b_kyber_mul = temp1[31:0];
            end
            // +(temp0<<12): HIGH
            L1_STAGE4_HIGH: begin
                temp1_shift             = 36'(temp0[23:0]) << 12;
                // AQUI É POSITIVO: Zero-padding {28'd0} está correto!
                alu_operand_a_kyber_mul = {28'd0, temp1_shift[35:32]};
                alu_operand_b_kyber_mul = {{27{temp1[36]}}, temp1[36:32]} + {31'd0, carry_reg};
            end

            KYBER_BARRETT_L4: begin
                alu_operand_a_kyber_mul = temp0[31:0];
                alu_operand_b_kyber_mul = -temp1[31:0];
            end

            default: ;

        endcase
    end
    

    logic [31:0] second_operand_neg, second_value_sub;

    assign second_operand_neg = second_operand_i ^ {32{1'b1}};

    assign second_value_sub = second_operand_neg + 1 + (1 << 16);

    always_comb begin 
        if(operator_i == KYBER_ADD) begin 
            alu_operand_a_kyber = first_operand_i; 
            alu_operand_b_kyber = second_operand_i;
        end else if(operator_i == KYBER_SUB) begin 
            alu_operand_a_kyber = first_operand_i;
            alu_operand_b_kyber = {{4{1'b0}}, (second_value_sub[27:16]), {4{1'b0}}, second_value_sub[11:0]};
        end else begin 
            alu_operand_a_kyber = alu_operand_a_kyber_mul;
            alu_operand_b_kyber = alu_operand_b_kyber_mul;
        end
    end

    always_comb begin

      mult_kyber_op_a            = first_operand_i[15:0];
      mult_kyber_op_b            = second_operand_i[15:0];
      xkyber_valid               = 1'b0;

      unique case (mul_state)

        L1_STAGE4_HIGH: begin
            //mult_hold    = ~multdiv_ready_id_i;  
            mult_kyber_op_a = temp1 >> 24;
            mult_kyber_op_b = 16'd3329;
        end

        KYBER_BARRETT_L2: begin 
            mult_kyber_op_a = temp1 >> 24;
            mult_kyber_op_b = 16'd3329;
        end

        KYBER_BARRETT_L3: begin

          // Note no state transition will occur if mult_hold is set
          //mult_hold    = ~multdiv_ready_id_i;

        end

        KYBER_BARRETT_L4: begin 
            xkyber_valid         = 1'b1;
        end

        default:;

      endcase // mult_state_q
    end

endmodule
