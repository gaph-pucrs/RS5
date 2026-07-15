// Copyright lowRISC contributors.
// Copyright 2018 ETH Zurich and University of Bologna, see also CREDITS.md.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

`include "RS5_pkg.sv"

module xkyber
    import RS5_pkg::*;
(
    input   logic        clk,
    input   logic        reset_n,
    input   logic        stall,

    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0] alu_adder_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   logic         is_xkyber_i,

    input   logic  [2:0]  alu_cbd_high_i,
    input   logic  [2:0]  alu_cbd_low_i,

    input   logic  [3:0]  kyber_compress_bits_i,

    input   iType_e      operator_i,

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,

    input   logic [31:0] result_mul_i,    

    output  logic [31:0] alu_operand_a_kyber_o,
    output  logic [31:0] alu_operand_b_kyber_o,

    output  logic [15:0] mult_kyber_op_a, 
    output  logic [15:0] mult_kyber_op_b, 

    output  logic        hold_o,
    output  logic [31:0] result_o
);

   /* verilator lint_off UNUSEDSIGNAL */
   logic [31:0] alu_adder_i_reg;
   /* verilator lint_on UNUSEDSIGNAL */

    always_ff@(posedge clk or negedge reset_n) begin
        if(!reset_n) begin  
            alu_adder_i_reg <= '0;
        end else begin 
            alu_adder_i_reg <= alu_adder_i;
        end
    end

    logic  [2:0]  alu_cbd_high_reg;
    logic  [2:0]  alu_cbd_low_reg;

    always_ff@(posedge clk or negedge reset_n) begin
        if(!reset_n) begin  
            alu_cbd_high_reg <= '0;
            alu_cbd_low_reg  <= '0;
        end else begin 
            alu_cbd_high_reg <= alu_cbd_high_i;
            alu_cbd_low_reg  <= alu_cbd_low_i;
        end
    end


    ///
    // Kyber Compress logic
    ///

    // logic[31:0] alu_adder_compress_shifted;
    logic[12:0] alu_adder_compress_shifted;
    logic compress_carry_in;

    always_comb begin

      unique case (kyber_compress_bits_i)

        4'd4:    alu_adder_compress_shifted = 13'(alu_adder_i_reg[23:0] >> (24 - 4 - 1));
        4'd5:    alu_adder_compress_shifted = 13'(alu_adder_i_reg[23:0] >> (24 - 5 - 1));
        4'd10:   alu_adder_compress_shifted = 13'(alu_adder_i_reg[23:0] >> (24 - 10 - 1));
        4'd11:   alu_adder_compress_shifted = 13'(alu_adder_i_reg[23:0] >> (24 - 11 - 1));
        default: alu_adder_compress_shifted = 13'(alu_adder_i_reg[23:0] >> (24 - 1 - 1));

      endcase

    end

    logic [12:0] alu_adder_compress_shifted_reg;

    always_ff@(posedge clk or negedge reset_n) begin
        if(!reset_n) begin  
            alu_adder_compress_shifted_reg <= '0;
        end else begin 
            alu_adder_compress_shifted_reg <= alu_adder_compress_shifted;
        end

    end

    assign compress_carry_in = alu_adder_compress_shifted_reg[0];


    ///
    // Kyber Add/Sub logic (Fit ALU adder output to [0, 3328] range)
    ///

    logic adjust_adder_op_b_inv;

    logic[12:0] adjust_adder_high, adjust_adder_high_op_a, adjust_adder_high_op_b;
    logic adjust_adder_high_carry_in;
    logic[11:0] adjust_result_high;
    logic adjust_result_high_mux_sel;  // 0 for passthrough from ALU adder, 1 for "adjust_adder_high"

    logic[12:0] adjust_adder_low_op_a, adjust_adder_low_op_b;
    /* verilator lint_off UNUSEDSIGNAL */
    logic[13:0] adjust_adder_low;
    /* verilator lint_on UNUSEDSIGNAL */
    logic adjust_adder_low_carry_in;
    logic[11:0] adjust_result_low_mask;
    logic[11:0] adjust_result_low;
    logic adjust_result_low_mux_sel;  // 0 for passthrough from ALU adder, 1 for "adjust_adder_low"

    // Conditionally subtract Q = 3329 from ALU output when performing modular addition or last step of Barrett reduction in modular multiplication
    // Subtraction is performed by adding the two's complement of 3329 (op_a + (op_b = !13'd3329) + (carry_in = 1'b1))
    assign adjust_adder_op_b_inv = (operator_i == KYBER_ADD || operator_i == KYBER_MUL);

    assign adjust_adder_high_op_a = (operator_i inside {KYBER_CBD2, KYBER_CBD3}) ? {{10{alu_cbd_high_reg[2]}}, alu_cbd_high_reg} : (operator_i == KYBER_MUL) ? alu_adder_i_reg[28:16] : alu_adder_i_reg[28:16];
    assign adjust_adder_high_op_b = adjust_adder_op_b_inv ? (13'd3329 ^ {13{1'b1}}) : 13'd3329;
    assign adjust_adder_high_carry_in = adjust_adder_op_b_inv;
    assign adjust_adder_high = adjust_adder_high_op_a + adjust_adder_high_op_b + 13'(adjust_adder_high_carry_in);

    // Select "adjust_adder" when:
    //  ALU subtraction underflows (meaning addition to 3329 brings result back to [0, 3328] range)
    //  ALU addition overflows or subtraction by 3329 does NOT underflow (meaning subtraction by 3329 brings result back to [0, 3328] range)
    //  CBD sampling A-B < 0 (add Q to ALU output making sampled coeficient in [0, 3328] range)
    always_comb begin

      unique case (1'b1)
        // (operator_i == KYBER_ADD):  adjust_result_high_mux_sel = alu_adder_i[28] | !adjust_adder_high[12];
        (operator_i == KYBER_ADD):  adjust_result_high_mux_sel = !adjust_adder_high[12];
        // (operator_i == KYBER_SUB):  adjust_result_high_mux_sel = adjust_adder_high[12];
        (operator_i == KYBER_SUB):  adjust_result_high_mux_sel = !alu_adder_i_reg[28];
        // (operator_i == KYBER_CBD2): adjust_result_high_mux_sel = adjust_adder_high[12];
        (operator_i == KYBER_CBD2): adjust_result_high_mux_sel = alu_cbd_high_reg[2];
        // (operator_i == KYBER_CBD3): adjust_result_high_mux_sel = adjust_adder_high[12];
        (operator_i == KYBER_CBD3): adjust_result_high_mux_sel = alu_cbd_high_reg[2];
        default:                            adjust_result_high_mux_sel = 1'b0;

      endcase

    end

    assign adjust_result_high = adjust_result_high_mux_sel ? adjust_adder_high[11:0] : adjust_adder_high_op_a[11:0];

    // TODO: This mask may not be needed for compress_d != 1;
    always_comb begin

      unique case (kyber_compress_bits_i)

        1: adjust_result_low_mask = 12'h001;
        4: adjust_result_low_mask = 12'h00F;
        5: adjust_result_low_mask = 12'h01F;
        10: adjust_result_low_mask = 12'h3FF;
        11: adjust_result_low_mask = 12'h7FF;
        default: adjust_result_low_mask = 12'hFFF;

      endcase

    end

    assign adjust_adder_low_op_a = (operator_i == KYBER_COMPRESS)               ? {1'b0, alu_adder_compress_shifted_reg[12:1]} :
                                   (operator_i inside {KYBER_CBD2, KYBER_CBD3}) ? {{10{alu_cbd_low_reg[2]}}, alu_cbd_low_reg} :
                                   (operator_i == KYBER_MUL)                    ? alu_adder_i_reg[12:0] : alu_adder_i_reg[12:0];

    // assign adjust_adder_low_op_b = (operator_i == KYBER_COMPRESS) ? 13'd0 : (adjust_adder_op_b_inv ? !(13'd3329): 13'd3329);
    assign adjust_adder_low_op_b = (operator_i == KYBER_COMPRESS) ? 13'd0 : (adjust_adder_op_b_inv ? (13'd3329 ^ {13{1'b1}}): 13'd3329);
    assign adjust_adder_low_carry_in = (operator_i == KYBER_COMPRESS) ? compress_carry_in : adjust_adder_op_b_inv;
    assign adjust_adder_low = (adjust_adder_low_op_a + adjust_adder_low_op_b + 13'(adjust_adder_low_carry_in));

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
        (operator_i == KYBER_SUB):    adjust_result_low_mux_sel = !alu_adder_i_reg[12];
        // (operator_i == KYBER_CBD2):   adjust_result_low_mux_sel = adjust_adder_low[12];
        (operator_i == KYBER_CBD2):   adjust_result_low_mux_sel = alu_cbd_low_reg[2];
        // (operator_i == KYBER_CBD3):   adjust_result_low_mux_sel = adjust_adder_low[12];
        (operator_i == KYBER_CBD3):   adjust_result_low_mux_sel = alu_cbd_low_reg[2];
        (operator_i == KYBER_MUL):      adjust_result_low_mux_sel = !adjust_adder_low[12];
        (operator_i == KYBER_COMPRESS): adjust_result_low_mux_sel = 1'b1;
        default:                              adjust_result_low_mux_sel = 1'b0;

      endcase

    end

    assign adjust_result_low = (adjust_result_low_mux_sel ? adjust_adder_low[11:0] : adjust_adder_low_op_a[11:0]) & adjust_result_low_mask;


 typedef enum logic [17:0] {
    IDLE                           = 18'b000000000000000001,
    L1_STAGE0_WAIT                 = 18'b000000000000000010,
    L1_STAGE0_WAIT2                = 18'b000000000000000100,
    L1_STAGE0_LOW                  = 18'b000000000000001000,
    L1_STAGE0_HIGH                 = 18'b000000000000010000, 
    KYBER_BARRETT_L2               = 18'b000000000000100000, 
    KYBER_BARRETT_L3               = 18'b000000000001000000,
    KYBER_BARRETT_L4_STAGE0        = 18'b000000000010000000, 
    KYBER_BARRETT_L4_STAGE1        = 18'b000000000100000000,
    KYBER_BARRETT_L4_STAGE2        = 18'b000000001000000000,
    COMPRESS_STAGE0                = 18'b000000010000000000, 
    COMPRESS_END_STAGE0_SUM0       = 18'b000000100000000000,
    COMPRESS_END_STAGE0_SUM1       = 18'b000001000000000000,
    COMPRESS_END_STAGE1            = 18'b000010000000000000,
    COMPRESS_END_STAGE2            = 18'b000100000000000000,
    FINAL_STAGE_SUB_CBD_SUM_STAGE0 = 18'b001000000000000000,
    FINAL_STAGE_SUB_CBD_SUM_STAGE1 = 18'b010000000000000000,
    LAST_STAGE                     = 18'b100000000000000000
} mul_states_e;

    mul_states_e mul_state;
    mul_states_e next_state;

    mul_states_e stage;

    always_comb begin
        if(is_xkyber_i) begin
            unique case (operator_i)
                KYBER_MUL: 
                    stage = L1_STAGE0_WAIT;
                KYBER_COMPRESS: 
                    stage = COMPRESS_STAGE0;
                KYBER_ADD, KYBER_SUB, KYBER_CBD2, KYBER_CBD3: 
                    stage = FINAL_STAGE_SUB_CBD_SUM_STAGE0;
                default: 
                    stage = IDLE;
            endcase
        end else begin
            stage = IDLE;
        end
    end

    logic is_compress;

    assign is_compress = (operator_i == KYBER_COMPRESS);


    always_comb begin
        next_state = IDLE;
        unique case (mul_state)
            IDLE:                           next_state = stage;
            L1_STAGE0_WAIT:                 next_state = L1_STAGE0_WAIT2;
            L1_STAGE0_WAIT2:                next_state = L1_STAGE0_LOW;
            L1_STAGE0_LOW:                  next_state = L1_STAGE0_HIGH;
            L1_STAGE0_HIGH:                 next_state = (is_compress) ? COMPRESS_END_STAGE0_SUM0 : KYBER_BARRETT_L2;
            KYBER_BARRETT_L2:               next_state = KYBER_BARRETT_L3;
            KYBER_BARRETT_L3:               next_state = KYBER_BARRETT_L4_STAGE0;
            KYBER_BARRETT_L4_STAGE0:        next_state = KYBER_BARRETT_L4_STAGE1;
            KYBER_BARRETT_L4_STAGE1:        next_state = KYBER_BARRETT_L4_STAGE2;
            KYBER_BARRETT_L4_STAGE2:        next_state = LAST_STAGE;  
            COMPRESS_STAGE0:                next_state = L1_STAGE0_WAIT2;
            COMPRESS_END_STAGE0_SUM0:       next_state = COMPRESS_END_STAGE0_SUM1;
            COMPRESS_END_STAGE0_SUM1:       next_state = COMPRESS_END_STAGE1;
            COMPRESS_END_STAGE1:            next_state = COMPRESS_END_STAGE2;  
            COMPRESS_END_STAGE2:            next_state = LAST_STAGE; 
            FINAL_STAGE_SUB_CBD_SUM_STAGE0: next_state = FINAL_STAGE_SUB_CBD_SUM_STAGE1;
            FINAL_STAGE_SUB_CBD_SUM_STAGE1: next_state = LAST_STAGE;
            LAST_STAGE:                     next_state = IDLE;
            default:                        next_state = IDLE;
        endcase
    end

     always_ff@(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mul_state <= IDLE;
        else if (!stall)
            mul_state <= next_state;
    end

    logic xkyber_valid;

    assign hold_o = is_xkyber_i && !xkyber_valid;

    // synthesis translate_off

    /*localparam string OUTPUT_FILE = "./result_kyber/Output.txt";
    integer fd; 

    initial begin

        fd = $fopen(OUTPUT_FILE, "w");
        
        if (fd == 0) begin
            $display("ERRO FATAL: Não foi possível criar o arquivo %s. Verifique se a pasta existe!", OUTPUT_FILE);
            $finish;
        end
    end

    
    always_ff @(posedge clk) begin

       
        if (xkyber_valid) begin 
            if (operator_i == KYBER_MUL)
                $fdisplay(fd, "[CHECKER] KYBER_MUL      0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
            else if (operator_i == KYBER_COMPRESS)
                $fdisplay(fd, "[CHECKER] KYBER_COMPRESS 0x%0h e 0x%0h = 0x%0h", first_operand_i, second_operand_i, result_o);
        end 
        
        
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

    
    final begin
        if (fd != 0) begin
            $fclose(fd);
            $display("Log de saída salvo com sucesso em: %s", OUTPUT_FILE);
        end
    end*/

    // synthesis translate_on

    logic [31:0] result_xkyber;

    assign result_xkyber = {{4{1'b0}}, adjust_result_high, {4{1'b0}}, adjust_result_low};

    logic [31:0] result_compress;

    logic [31:0] result;

    always_comb begin 
        result = '0;
        if(is_compress) result = result_compress;
        else if(is_xkyber_i) result = result_xkyber;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin 
            result_o <= '0;
        end else begin 
            result_o <= result;
        end
    end


//kyber part!

    /* verilator lint_off UNUSEDSIGNAL */
    logic [34:0] temp0;
    /* verilator lint_on UNUSEDSIGNAL */

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin 
            temp0 <= '0;
        end else begin 
            if (mul_state == L1_STAGE0_WAIT) temp0 <= {3'b000,result_mul_i}; //in idle mac_res_d will hold the temp0 value
            else if(is_compress && mul_state == L1_STAGE0_WAIT2) temp0 <= {3'b000,result_mul_i};
        end
    end

    logic [36:0] temp1;

     always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin 
            temp1 <= '0;
        end else begin 
            if (mul_state == L1_STAGE0_HIGH) temp1 <= (37'({2'b00, result_mul_i[20:0]}) << 16) + temp1;
            else begin
                if(!is_compress) begin
                    if ((mul_state != KYBER_BARRETT_L2) && (mul_state != IDLE)) temp1 <= {5'b00000, result_mul_i};
                end
                else begin 
                    if (mul_state == L1_STAGE0_LOW) temp1 <= {5'b00000, result_mul_i}; //testar se essa condição não funciona para o mul tbm
                end
            end
        end
    end 

    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] second_operand_neg, second_value_sub;
    /* verilator lint_on UNUSEDSIGNAL */

    assign second_operand_neg = second_operand_i ^ {32{1'b1}};

    assign second_value_sub = {{3{1'b0}}, 13'(second_operand_neg[27:16] + 12'd1), {3{1'b0}}, 13'(second_operand_neg[11:0] + 12'd1)};

    logic [31:0] alu_operand_a_kyber_mul, alu_operand_b_kyber_mul;

    logic [31:0] alu_operand_a_kyber, alu_operand_b_kyber; 

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

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            alu_operand_a_kyber_o <= '0;
            alu_operand_b_kyber_o <= '0;
        end begin 
            alu_operand_a_kyber_o <= alu_operand_a_kyber;
            alu_operand_b_kyber_o <= alu_operand_b_kyber;
        end 
    end 

    always_comb begin

      mult_kyber_op_a            = first_operand_i[15:0];
      mult_kyber_op_b            = 16'd5039;
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
            if(!is_compress) mult_kyber_op_a  = temp0[15:0];  // 16 bits unsigned → 17 bits signed OK
        end

        L1_STAGE0_LOW: begin 
            if(is_compress) mult_kyber_op_a = {8'b00000000, first_operand_i[23:16]};
            else mult_kyber_op_a  = temp0[31:16];  // 16 bits altos
        end

        L1_STAGE0_HIGH: begin 

        end

        KYBER_BARRETT_L2: begin 
            mult_kyber_op_a = 16'(temp1 >> 24);
            mult_kyber_op_b = 16'd3329;
        end

        KYBER_BARRETT_L3: begin
            
          // Note no state transition will occur if mult_hold is set
          //mult_hold    = ~multdiv_ready_id_i;

        end

        KYBER_BARRETT_L4_STAGE0: begin

        end

        KYBER_BARRETT_L4_STAGE1: begin

            //xkyber_valid         = 1'b1;

            // Note no state transition will occur if mult_hold is set
            //mult_hold    = ~multdiv_ready_id_i;
        end

        KYBER_BARRETT_L4_STAGE2 : begin

        end



        COMPRESS_STAGE0: begin 

            mult_kyber_op_b = 16'hB760;  // Fractional part of 2**24/q, 12 bits of precision

        end

        COMPRESS_END_STAGE0_SUM0: begin 
            alu_operand_a_kyber_mul = {{16{1'b0}}, temp0[31:16]};
            alu_operand_b_kyber_mul = temp1[31:0];

        end

        COMPRESS_END_STAGE0_SUM1: begin 
        
        end 

        COMPRESS_END_STAGE1: begin 
            
        end

        COMPRESS_END_STAGE2: begin 
            //acho que pode ser comentado, porque ja pego o resultado no estagio anterior
            //alu_operand_a_kyber_mul = {{16{1'b0}}, temp0[31:16]};
            //alu_operand_b_kyber_mul = temp1[31:0];

            result_compress = {{20{1'b0}}, adjust_result_low};
            //xkyber_valid = 1'b1;
        end

        FINAL_STAGE_SUB_CBD_SUM_STAGE0: begin 
            //xkyber_valid = 1'b1;
        end

        FINAL_STAGE_SUB_CBD_SUM_STAGE1: begin 
            //xkyber_valid = 1'b1;
        end

        LAST_STAGE: begin 
            xkyber_valid = 1'b1;
        end

        default: ;

      endcase // mult_state_q
    end

endmodule
