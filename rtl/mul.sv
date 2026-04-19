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

    typedef enum logic [13:0] {
        IDLE                         = 14'b00000000000001,
        ALBL                         = 14'b00000000000010,
        ALBH                         = 14'b00000000000100,
        AHBL                         = 14'b00000000001000,
        AHBH                         = 14'b00000000010000,
        L1_STAGE0_WAIT               = 14'b00000000100000,
        L1_STAGE0_WAIT2              = 14'b00000001000000,
        L1_STAGE0_LOW                = 14'b00000010000000,
        L1_STAGE0_HIGH               = 14'b00000100000000, 
        KYBER_BARRETT_L2             = 14'b00001000000000, 
        KYBER_BARRETT_L3             = 14'b00010000000000,
        KYBER_BARRETT_L4             = 14'b00100000000000, 
        COMPRESS_STAGE0              = 14'b01000000000000, 
        COMPRESS_END                 = 14'b10000000000000
    } mul_states_e;

    mul_states_e mul_state;
    mul_states_e next_state;

    mul_states_e stage;

    always_comb begin 
        stage = IDLE;
        if(enable_i) begin 
            if(operator_i == KYBER_MUL) stage = L1_STAGE0_WAIT; 
            else if(operator_i == KYBER_COMPRESS) stage = COMPRESS_STAGE0;
            else stage = ALBL;
        end
    end

    logic is_compress;

    assign is_compress = (operator_i == KYBER_COMPRESS);

    always_comb begin
        next_state = IDLE;
        unique case (mul_state)
            IDLE:                         next_state = stage;
            ALBL:                         next_state = single_cycle_i ? IDLE : ALBH;
            ALBH:                         next_state = AHBL;
            AHBL:                         next_state = mul_low_i      ? IDLE : AHBH;
            AHBH:                         next_state = IDLE;
            L1_STAGE0_WAIT:               next_state = L1_STAGE0_WAIT2;
            L1_STAGE0_WAIT2:              next_state = L1_STAGE0_LOW;
            L1_STAGE0_LOW:                next_state = L1_STAGE0_HIGH;
            L1_STAGE0_HIGH:               next_state = (is_compress) ? COMPRESS_END : KYBER_BARRETT_L2;
            KYBER_BARRETT_L2:             next_state = KYBER_BARRETT_L3;
            KYBER_BARRETT_L3:             next_state = KYBER_BARRETT_L4;
            KYBER_BARRETT_L4:             next_state = IDLE;
            COMPRESS_STAGE0:              next_state = L1_STAGE0_WAIT2;
            COMPRESS_END:                 next_state = IDLE;
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

    logic [16:0] mult_kyber_op_a, mult_kyber_op_b; 

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

    // synthesis translate_off

    localparam string OUTPUT_FILE = "./result_kyber/Output.txt";
    integer fd; // File Descriptor (o ponteiro para o arquivo)

    // 1. Abre o arquivo uma vez só no começo da simulação
    initial begin
        // "w" abre em modo Write (apaga o log do run anterior e começa limpo). 
        // Se quiser que ele vá somando os logs, troque "w" por "a" (Append).
        fd = $fopen(OUTPUT_FILE, "w");
        
        if (fd == 0) begin
            $display("ERRO FATAL: Não foi possível criar o arquivo %s. Verifique se a pasta existe!", OUTPUT_FILE);
            $finish;
        end
    end

    // 2. Grava no arquivo usando $fdisplay(fd, ...)
    always_ff @(posedge clk) begin

        // Operações Multi-ciclo
        if (xkyber_valid) begin 
            if (operator_i == KYBER_MUL)
                $fdisplay(fd, "[CHECKER] KYBER_MUL      0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
            else if (operator_i == KYBER_COMPRESS)
                $fdisplay(fd, "[CHECKER] KYBER_COMPRESS 0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
        end 
        
        // Operações Single-cycle
        else if (operator_i inside {KYBER_ADD, KYBER_SUB, KYBER_CBD2, KYBER_CBD3}) begin 
            case (operator_i)
                KYBER_ADD:  $fdisplay(fd, "[CHECKER] KYBER_ADD      0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
                KYBER_SUB:  $fdisplay(fd, "[CHECKER] KYBER_SUB      0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
                KYBER_CBD2: $fdisplay(fd, "[CHECKER] KYBER_CBD2     0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
                KYBER_CBD3: $fdisplay(fd, "[CHECKER] KYBER_CBD3     0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
                default: ;
            endcase
        end

    end

    // 3. Fecha o arquivo de forma segura quando a simulação acaba
    final begin
        if (fd != 0) begin
            $fclose(fd);
            $display("Log de saída salvo com sucesso em: %s", OUTPUT_FILE);
        end
    end

    // synthesis translate_on

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

    logic [31:0] result_compress;

    always_comb begin 
        result_o = mac_result_partial[31:0];
        if(is_compress) result_o = result_compress;
        else if(is_xkyber_i) result_o = result_xkyber;
    end


//kyber part!

    logic [34:0] temp0;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin 
            temp0 <= '0;
        end else begin 
            if (mul_state == L1_STAGE0_WAIT) temp0 <= mac_result; //in idle mac_res_d will hold the temp0 value
            else if(is_compress && mul_state == L1_STAGE0_WAIT2) temp0 <= mac_result;
        end
    end

    logic [36:0] temp1;

     always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin 
            temp1 <= '0;
        end else begin 
            if (mul_state == L1_STAGE0_HIGH) temp1 <= ({2'b00, mac_result[20:0]} << 16) + temp1;
            else begin
                if(!is_compress) begin
                    if (mul_state != KYBER_BARRETT_L2) temp1 <= {2'b00, mac_result};
                end
                else begin 
                    if (mul_state == L1_STAGE0_LOW) temp1 <= {2'b00, mac_result}; //testar se essa condição não funciona para o mul tbm
                end
            end
        end
    end 

    logic [31:0] second_operand_neg, second_value_sub;

    assign second_operand_neg = second_operand_i ^ {32{1'b1}};

    assign second_value_sub = {{3{1'b0}}, 13'(second_operand_neg[27:16] + 1), {3{1'b0}}, 13'(second_operand_neg[11:0] + 1)};

    logic [31:0] alu_operand_a_kyber_mul, alu_operand_b_kyber_mul;

    always_comb begin 
        alu_operand_a_kyber = first_operand_i;
        alu_operand_b_kyber = second_operand_i;
        if(operator_i == KYBER_SUB) begin 
            alu_operand_b_kyber = second_value_sub;
        end else if(operator_i == KYBER_MUL || operator_i == KYBER_COMPRESS) begin
            alu_operand_a_kyber = alu_operand_a_kyber_mul;
            alu_operand_b_kyber = alu_operand_b_kyber_mul;
        end
    end

    always_comb begin

      mult_kyber_op_a            = {1'b0, first_operand_i[15:0]};
      mult_kyber_op_b            = 17'd5039;
      xkyber_valid               = 1'b0;

      alu_operand_a_kyber_mul = temp0[31:0];
      alu_operand_b_kyber_mul = -(temp1[31:0]);

      result_compress = '0;

      unique case (mul_state)

        IDLE: begin 
            mult_kyber_op_b = second_operand_i[15:0];
        end

        L1_STAGE0_WAIT: begin 
            
        end

        L1_STAGE0_WAIT2: begin 
            if(!is_compress) mult_kyber_op_a  = {1'b0, temp0[15:0]};  // 16 bits unsigned → 17 bits signed OK
        end

        L1_STAGE0_LOW: begin 
            if(is_compress) mult_kyber_op_a = {9'b000000000, first_operand_i[23:16]};
            else mult_kyber_op_a  = {1'b0, temp0[31:16]};  // 16 bits altos
        end

        L1_STAGE0_HIGH: begin 

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

            // Note no state transition will occur if mult_hold is set
            //mult_hold    = ~multdiv_ready_id_i;
        end

        COMPRESS_STAGE0: begin 

            mult_kyber_op_b = 16'hB760;  // Fractional part of 2**24/q, 12 bits of precision

        end

        COMPRESS_END: begin 
            alu_operand_a_kyber_mul = {{16{1'b0}}, temp0[31:16]};
            alu_operand_b_kyber_mul = temp1[31:0];

            result_compress = {{20{1'b0}}, adjust_result_low};
            xkyber_valid = 1'b1;
        end

        default: ;

      endcase // mult_state_q
    end

endmodule
