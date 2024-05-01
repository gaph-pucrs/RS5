module vectorALU
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64,
    parameter int VLENB = 8
) (
    input  logic            clk,
    input  logic            reset_n,

    input  logic [VLEN-1:0] first_operand,
    input  logic [VLEN-1:0] second_operand,
    input  logic [VLEN-1:0] third_operand,
    input  vector_states_e  current_state,
    input  logic [4:0]      cycle_count,
    input  logic            widening_i,

    input  iTypeVector_e    vector_operation_i,
    input  vew_e            vsew,

    output logic            hold_o,
    output logic            hold_widening_o,
    output logic [VLEN-1:0] result_o
);

    logic hold_mult;
    logic hold;

    logic signed [VLEN-1:0] first_operand_signed, second_operand_signed, third_operand_signed;

    assign first_operand_signed  = first_operand;
    assign second_operand_signed = second_operand;
    assign third_operand_signed  = third_operand;

    logic [VLEN-1:0] result_mult_r;

//////////////////////////////////////////////////////////////////////////////
// Accumulate Control
//////////////////////////////////////////////////////////////////////////////
    logic hold_acc, hold_acc_r;
    logic accumulate_instruction;

    assign accumulate_instruction = (vector_operation_i inside {vmacc, vnmsac, vmadd, vnmsub});

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            hold_acc_r <= 1'b0;
        else 
            hold_acc_r <= hold_acc;

    assign hold_acc = (accumulate_instruction == 1'b1 && hold_acc_r == 1'b0 && current_state == V_EXEC && cycle_count == 1 && hold_mult == 1'b0);

//////////////////////////////////////////////////////////////////////////////
// Widening Control
//////////////////////////////////////////////////////////////////////////////
    logic widening_counter;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            widening_counter <= 1'b0;
        end
        else if (widening_i == 1'b1 && hold == 1'b0 && current_state == V_EXEC) begin
            widening_counter <= widening_counter + 1'b1;
        end
        else begin
            widening_counter <= 1'b0;
        end
    end

    assign hold_widening_o = widening_i & !widening_counter && current_state == V_EXEC;

//////////////////////////////////////////////////////////////////////////////
// Logical
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_and, result_or, result_xor;

    always_comb begin
        result_and = first_operand & second_operand;
        result_or  = first_operand | second_operand;
        result_xor = first_operand ^ second_operand;
    end

//////////////////////////////////////////////////////////////////////////////
// Reductions
//////////////////////////////////////////////////////////////////////////////
/*
    logic [31:0] op1_redLog_32, op2_redLog_32;
    logic [VLEN-1:0] result_redAnd_32, result_redOr_32, result_redXor_32;

    assign op1_redLog_32 = first_operand[31:0];
    assign op2_redLog_32 = second_operand[63:32];

    always_comb begin
        result_redAnd_32 = op1_redLog_32 & op2_redLog_32;
        result_redOr_32  = op1_redLog_32 | op2_redLog_32;
        result_redXor_32 = op1_redLog_32 ^ op2_redLog_32;
    end
*/
//////////////////////////////////////////////////////////////////////////////
// Adder
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] subtraend, subtraend_neg;
    logic [VLEN-1:0] subtraend_8b, subtraend_16b, subtraend_32b;
    logic [VLEN-1:0] summand_1, summand_2, summand_2_8b, summand_2_16b, summand_2_32b;
    logic [VLEN-1:0] result_add_8b, result_add_16b, result_add_32b;
    logic [VLEN-1:0] result_add;

    always_comb begin
        unique case (vector_operation_i)
            vrsub:   subtraend = first_operand;
            vnmsac,
            vnmsub:  subtraend = result_mult_r;
            default: subtraend = second_operand;
        endcase
    end

    assign subtraend_neg = ~subtraend;

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            subtraend_8b[(8*(i+1))-1-:8]    = subtraend_neg[(8*(i+1))-1-:8] + 1'b1;
        for (int i = 0; i < VLENB/2; i++)
            subtraend_16b[(16*(i+1))-1-:16] = subtraend_neg[(16*(i+1))-1-:16] + 1'b1;
        for (int i = 0; i < VLENB/4; i++)
            subtraend_32b[(32*(i+1))-1-:32] = subtraend_neg[(32*(i+1))-1-:32] + 1'b1;
    end

    always_comb begin
        unique case (vector_operation_i)
            vrsub:   summand_1 = second_operand;
            vnmsac,
            vmacc,
            vmadd,
            vnmsub:  summand_1 = third_operand;
            default: summand_1 = first_operand;
        endcase
    end

    assign summand_2 = (vector_operation_i inside {vmacc, vmadd}) ? result_mult_r : second_operand;

    assign summand_2_8b  = (vector_operation_i inside {vsub, vrsub, vnmsac, vnmsub}) ? subtraend_8b  : summand_2;
    assign summand_2_16b = (vector_operation_i inside {vsub, vrsub, vnmsac, vnmsub}) ? subtraend_16b : summand_2;
    assign summand_2_32b = (vector_operation_i inside {vsub, vrsub, vnmsac, vnmsub}) ? subtraend_32b : summand_2;

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            result_add_8b[(8*(i+1))-1-:8]    = summand_1[(8*(i+1))-1-:8]   + summand_2_8b[(8*(i+1))-1-:8];
        for (int i = 0; i < VLENB/2; i++)
            result_add_16b[(16*(i+1))-1-:16] = summand_1[(16*(i+1))-1-:16] + summand_2_16b[(16*(i+1))-1-:16];
        for (int i = 0; i < VLENB/4; i++)
            result_add_32b[(32*(i+1))-1-:32] = summand_1[(32*(i+1))-1-:32] + summand_2_32b[(32*(i+1))-1-:32];
    end

    always_comb begin
        unique case (vsew)
            EW8:    result_add = result_add_8b;
            EW16:   result_add = result_add_16b;
            default:result_add = result_add_32b;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Shifts
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_sll, result_srl, result_sra;

    always_comb begin
        unique case (vsew)
            EW8:
                for (int i = 0; i < VLENB; i++) begin
                    automatic logic [7:0] operand_sliced, operand_sliced_signed;
                    operand_sliced        = second_operand[(8*(i+1))-1-:8];
                    operand_sliced_signed = second_operand_signed[(8*(i+1))-1-:8];

                    result_sll[(8*(i+1))-1-:8]   = first_operand[(8*(i+1))-1-:8]           <<  operand_sliced[2:0];
                    result_srl[(8*(i+1))-1-:8]   = first_operand[(8*(i+1))-1-:8]           >>  operand_sliced[2:0];
                    result_sra[(8*(i+1))-1-:8]   = first_operand_signed[(8*(i+1))-1-:8]    >>> operand_sliced_signed[2:0];
                end
            EW16:
                for (int i = 0; i < VLENB/2; i++) begin
                    automatic logic [15:0] operand_sliced, operand_sliced_signed;
                    operand_sliced        = second_operand[(16*(i+1))-1-:16];
                    operand_sliced_signed = second_operand_signed[(16*(i+1))-1-:16];

                    result_sll[(16*(i+1))-1-:16] = first_operand[(16*(i+1))-1-:16]         <<  operand_sliced[3:0];
                    result_srl[(16*(i+1))-1-:16] = first_operand[(16*(i+1))-1-:16]         >>  operand_sliced[3:0];
                    result_sra[(16*(i+1))-1-:16] = first_operand_signed[(16*(i+1))-1-:16]  >>> operand_sliced_signed[3:0];
                end
            default:
                for (int i = 0; i < VLENB/4; i++) begin
                    automatic logic [31:0] operand_sliced, operand_sliced_signed;
                    operand_sliced        = second_operand[(32*(i+1))-1-:32];
                    operand_sliced_signed = second_operand_signed[(32*(i+1))-1-:32];

                    result_sll[(32*(i+1))-1-:32] = first_operand[(32*(i+1))-1-:32]         <<  operand_sliced[4:0];
                    result_srl[(32*(i+1))-1-:32] = first_operand[(32*(i+1))-1-:32]         >>  operand_sliced[4:0];
                    result_sra[(32*(i+1))-1-:32] = first_operand_signed[(32*(i+1))-1-:32]  >>> operand_sliced_signed[4:0];
                end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Compare
//////////////////////////////////////////////////////////////////////////////

    logic [VLENB-1:0]     result_comparison;
    logic [VLENB-1:0]     equal_8b,  greater_than_8b,  greater_than_signed_8b,  result_comparison_8b;
    logic [(VLENB/2)-1:0] equal_16b, greater_than_16b, greater_than_signed_16b, result_comparison_16b;
    logic [(VLENB/4)-1:0] equal_32b, greater_than_32b, greater_than_signed_32b, result_comparison_32b;

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            equal_8b[i]                = first_operand[(8*(i+1))-1-:8] == second_operand[(8*(i+1))-1-:8];
            greater_than_8b[i]         = first_operand[(8*(i+1))-1-:8] >  second_operand[(8*(i+1))-1-:8];
            greater_than_signed_8b[i]  = first_operand_signed[(8*(i+1))-1-:8] > second_operand_signed[(8*(i+1))-1-:8];
        end

        for (int i = 0; i < VLENB/2; i++) begin
            equal_16b[i]               = first_operand[(16*(i+1))-1-:16] == second_operand[(16*(i+1))-1-:16];
            greater_than_16b[i]        = first_operand[(16*(i+1))-1-:16] >  second_operand[(16*(i+1))-1-:16];
            greater_than_signed_16b[i] = first_operand_signed[(16*(i+1))-1-:16] > second_operand_signed[(16*(i+1))-1-:16];
        end

        for (int i = 0; i < VLENB/4; i++) begin
            equal_32b[i]               = first_operand[(32*(i+1))-1-:32] == second_operand[(32*(i+1))-1-:32];
            greater_than_32b[i]        = first_operand[(32*(i+1))-1-:32] >  second_operand[(32*(i+1))-1-:32];
            greater_than_signed_32b[i] = first_operand_signed[(32*(i+1))-1-:32] > second_operand_signed[(32*(i+1))-1-:32];
        end
    end

    always_comb begin
        unique case(vector_operation_i)
            vmsne:  begin 
                        result_comparison_8b  = ~equal_8b;
                        result_comparison_16b = ~equal_16b;
                        result_comparison_32b = ~equal_32b;
                    end 
            vmsltu: begin 
                        result_comparison_8b  = ~equal_8b  & ~greater_than_8b;
                        result_comparison_16b = ~equal_16b & ~greater_than_16b;
                        result_comparison_32b = ~equal_32b & ~greater_than_32b;
                    end 
            vmslt:  begin 
                        result_comparison_8b  = ~equal_8b  & ~greater_than_signed_8b;
                        result_comparison_16b = ~equal_16b & ~greater_than_signed_16b;
                        result_comparison_32b = ~equal_32b & ~greater_than_signed_32b;
                    end 
            vmsleu: begin 
                        result_comparison_8b  = equal_8b  | ~greater_than_8b;
                        result_comparison_16b = equal_16b | ~greater_than_16b;
                        result_comparison_32b = equal_32b | ~greater_than_32b;
                    end 
            vmsle:  begin 
                        result_comparison_8b  = equal_8b  | ~greater_than_signed_8b;
                        result_comparison_16b = equal_16b | ~greater_than_signed_16b;
                        result_comparison_32b = equal_32b | ~greater_than_signed_32b;
                    end 
            vmsgtu: begin 
                        result_comparison_8b  = greater_than_8b;
                        result_comparison_16b = greater_than_16b;
                        result_comparison_32b = greater_than_32b;
                    end 
            vmsgt : begin 
                        result_comparison_8b  = greater_than_signed_8b;
                        result_comparison_16b = greater_than_signed_16b;
                        result_comparison_32b = greater_than_signed_32b;
                    end 
            default:begin 
                        result_comparison_8b  = equal_8b;
                        result_comparison_16b = equal_16b;
                        result_comparison_32b = equal_32b;
                    end 
        endcase
    end

    always_comb begin
        unique case (vsew)
            EW8:    result_comparison = {'0, result_comparison_8b};
            EW16:   result_comparison = {'0, result_comparison_16b};
            default:result_comparison = {'0, result_comparison_32b};
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Min/Max
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_minu, result_min, result_maxu, result_max;

    always_comb begin
        unique case (vsew)
            EW8:    begin
                        for (int i = 0; i < VLENB; i++) begin
                            result_minu[(8*(i+1))-1-:8] = (greater_than_8b[i])         ? second_operand[(8*(i+1))-1-:8] : first_operand [(8*(i+1))-1-:8];
                            result_min [(8*(i+1))-1-:8] = (greater_than_signed_8b[i])  ? second_operand[(8*(i+1))-1-:8] : first_operand [(8*(i+1))-1-:8];
                            result_maxu[(8*(i+1))-1-:8] = (greater_than_8b[i])         ? first_operand [(8*(i+1))-1-:8] : second_operand[(8*(i+1))-1-:8];
                            result_max [(8*(i+1))-1-:8] = (greater_than_signed_8b[i])  ? first_operand [(8*(i+1))-1-:8] : second_operand[(8*(i+1))-1-:8];
                        end
                    end

            EW16:   begin
                        for (int i = 0; i < VLENB/2; i++) begin
                            result_minu[(16*(i+1))-1-:16] = (greater_than_16b[i])         ? second_operand[(16*(i+1))-1-:16] : first_operand [(16*(i+1))-1-:16];
                            result_min [(16*(i+1))-1-:16] = (greater_than_signed_16b[i])  ? second_operand[(16*(i+1))-1-:16] : first_operand [(16*(i+1))-1-:16];
                            result_maxu[(16*(i+1))-1-:16] = (greater_than_16b[i])         ? first_operand [(16*(i+1))-1-:16] : second_operand[(16*(i+1))-1-:16];
                            result_max [(16*(i+1))-1-:16] = (greater_than_signed_16b[i])  ? first_operand [(16*(i+1))-1-:16] : second_operand[(16*(i+1))-1-:16];
                        end
                    end

            default:begin
                        for (int i = 0; i < VLENB/4; i++) begin
                            result_minu[(32*(i+1))-1-:32] = (greater_than_32b[i])         ? second_operand[(32*(i+1))-1-:32] : first_operand [(32*(i+1))-1-:32];
                            result_min [(32*(i+1))-1-:32] = (greater_than_signed_32b[i])  ? second_operand[(32*(i+1))-1-:32] : first_operand [(32*(i+1))-1-:32];
                            result_maxu[(32*(i+1))-1-:32] = (greater_than_32b[i])         ? first_operand [(32*(i+1))-1-:32] : second_operand[(32*(i+1))-1-:32];
                            result_max [(32*(i+1))-1-:32] = (greater_than_signed_32b[i])  ? first_operand [(32*(i+1))-1-:32] : second_operand[(32*(i+1))-1-:32];
                        end
                    end
        endcase
        
    end

//////////////////////////////////////////////////////////////////////////////
// Multiplication_common
//////////////////////////////////////////////////////////////////////////////

    logic [(2*VLEN)-1:0] result_mult;
    logic [1:0]      mult_signed_mode;

    always_comb begin
        unique case (vector_operation_i)
            vmulh:    mult_signed_mode = 2'b11;
            vmulhsu:  mult_signed_mode = 2'b01;
            default:  mult_signed_mode = 2'b00;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Multiplication 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic [ 7:0] mult_op_a_8b  [VLENB-1:0];
    logic [ 7:0] mult_op_b_8b  [VLENB-1:0];
    logic [15:0] mult_result_8b [VLENB-1:0];

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            //mult_op_a_8b[i] = (vector_operation_i inside {vmadd, vnmsub}) 
            //                ? third_operand [(8*(i+1))-1-:8] 
            //                : first_operand [(8*(i+1))-1-:8];
            mult_op_a_8b[i] = first_operand [(8*(i+1))-1-:8];
            mult_op_b_8b[i] = second_operand[(8*(i+1))-1-:8];
        end
    end

    genvar i_mul8b;
    generate
        for (i_mul8b = 0; i_mul8b < VLENB; i_mul8b++) begin : MUL8B_LOOP
            mulNbits #(
                .N(8)
            ) mul8b (
                .first_operand_i (mult_op_a_8b[i_mul8b]),
                .second_operand_i(mult_op_b_8b[i_mul8b]),
                .signed_mode_i   (mult_signed_mode),
                .result_o        (mult_result_8b[i_mul8b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication 16 bits
//////////////////////////////////////////////////////////////////////////////

    logic [15:0] mult_op_a_16b [(VLENB/2)-1:0];
    logic [15:0] mult_op_b_16b [(VLENB/2)-1:0];
    logic [31:0] mult_result_16b[(VLENB/2)-1:0];

    always_comb begin
        for (int i = 0; i < VLENB/2; i++) begin
            //mult_op_a_16b[i] = (vector_operation_i inside {vmadd, vnmsub}) 
            //                    ? third_operand [(16*(i+1))-1-:16] 
            //                    : first_operand [(16*(i+1))-1-:16];
            mult_op_a_16b[i] =    first_operand [(16*(i+1))-1-:16];
            mult_op_b_16b[i] =    second_operand[(16*(i+1))-1-:16];
        end
    end

    genvar i_mul16b;
    generate
        for (i_mul16b = 0; i_mul16b < VLENB/2; i_mul16b++) begin : MUL16B_LOOP
            mulNbits #(
                .N(16)
            ) mul16b (
                .first_operand_i (mult_op_a_16b[i_mul16b]),
                .second_operand_i(mult_op_b_16b[i_mul16b]),
                .signed_mode_i   (mult_signed_mode),
                .result_o        (mult_result_16b[i_mul16b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication 32 bits
//////////////////////////////////////////////////////////////////////////////

    logic                 mult_enable, mult_low;
    logic [(VLENB/4)-1:0] hold_mult_int;

    logic [31:0] mult_op_a_32b [(VLENB/4)-1:0];
    logic [31:0] mult_op_b_32b [(VLENB/4)-1:0];
    logic [31:0] mult_result_32b[(VLENB/4)-1:0];

    always_comb begin
        for (int i = 0; i < VLENB/4; i++) begin
            //mult_op_a_32b[i] = (vector_operation_i inside {vmadd, vnmsub}) 
            //                    ? third_operand [(32*(i+1))-1-:32] 
            //                    : first_operand [(32*(i+1))-1-:32];
            mult_op_a_32b[i] =    first_operand [(32*(i+1))-1-:32];
            mult_op_b_32b[i] =    second_operand[(32*(i+1))-1-:32];
        end
    end

    assign mult_enable = (
                            (vector_operation_i inside {vmul, vmulh, vmulhsu, vmulhu, vmacc, vnmsac, vmadd, vnmsub})
                        &&  (current_state == V_EXEC) 
                        &&  (vsew==EW32)
                        );
    assign mult_low    = (vector_operation_i inside {vmul, vmacc, vnmsac, vmadd, vnmsub});
    assign hold_mult   = |hold_mult_int;

    genvar i_mul32b;
    generate
        for (i_mul32b = 0; i_mul32b < VLENB/4; i_mul32b++) begin : MUL32B_LOOP
            mul mul32b (
                .clk             (clk),
                .reset_n         (reset_n),
                .first_operand_i (mult_op_a_32b[i_mul32b]),
                .second_operand_i(mult_op_b_32b[i_mul32b]),
                .signed_mode_i   (mult_signed_mode),
                .enable_i        (mult_enable),
                .mul_low_i       (mult_low),
                .hold_o          (hold_mult_int[i_mul32b]),
                .result_o        (mult_result_32b[i_mul32b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication Demux
//////////////////////////////////////////////////////////////////////////////
    always_comb begin
        unique case (vsew)
            EW8: begin
                for (int i = 0; i < VLENB; i++)
                    if (widening_i)
                        result_mult[(16*(i+1))-1-:16] = mult_result_8b[i][15:0];
                    else if (vector_operation_i inside {vmul, vmacc, vnmsac, vmadd, vnmsub})
                        result_mult[(8*(i+1))-1-:8] = mult_result_8b[i][7:0];
                    else
                        result_mult[(8*(i+1))-1-:8] = mult_result_8b[i][15:8];
            end
            EW16: begin
                for (int i = 0; i < VLENB/2; i++)
                    if (widening_i)
                        result_mult[(32*(i+1))-1-:32] = mult_result_16b[i][31:0];
                    else if (vector_operation_i inside {vmul, vmacc, vnmsac, vmadd, vnmsub})
                        result_mult[(16*(i+1))-1-:16] = mult_result_16b[i][15:0];
                    else
                        result_mult[(16*(i+1))-1-:16] = mult_result_16b[i][31:16];
            end
            default: begin
                for (int i = 0; i < VLENB/4; i++)
                    result_mult[(32*(i+1))-1-:32] = mult_result_32b[i][31:0];
            end
        endcase
    end

    always @(posedge clk) begin
        if (!hold_mult)
            result_mult_r <= result_mult;
    end

//////////////////////////////////////////////////////////////////////////////
// Hold generation
//////////////////////////////////////////////////////////////////////////////

    assign hold   = hold_mult;
    assign hold_o = hold | hold_widening_o | hold_acc;

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk) begin
        unique case(vector_operation_i)
            vand:            result_o <= result_and;
            vor:             result_o <= result_or;
            vxor:            result_o <= result_xor;
            vsll:            result_o <= result_sll;
            vsrl:            result_o <= result_srl;
            vsra:            result_o <= result_sra;
            /*
            vmseq,  vmsne,
            vmsltu, vmslt,
            vmsleu, vmsle,
            vmsgtu, vmsgt:   result_o <= result_comparison;*/
            vmin:            result_o <= result_min;
            vminu:           result_o <= result_minu;
            vmax:            result_o <= result_max;
            vmaxu:           result_o <= result_maxu;
            vmul, vmulh,
            vmulhu, vmulhsu: result_o <= result_mult;
            vwmul, vwmulu, 
            vwmulsu:         result_o <= (widening_counter == 1'b1) ? result_mult[VLEN-1:0] : result_mult[VLEN-1:0];
            /*
            vredand:         result_o <= {'0, result_redAnd_32};
            vredor:          result_o <= {'0, result_redOr_32};
            vredxor:         result_o <= {'0, result_redXor_32};
            */
            default:         result_o <= result_add;
        endcase
    end

endmodule