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

    input  iTypeVector_e    vector_operation_i,
    input  vew_e            vsew,

    output logic [VLEN-1:0] result_o
);

    logic signed [VLEN-1:0] first_operand_signed, second_operand_signed, third_operand_signed;

    assign first_operand_signed  = first_operand;
    assign second_operand_signed = second_operand;
    assign third_operand_signed  = third_operand;

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
// Adder
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] subtraend_int, subtraend_neg;
    logic [VLEN-1:0] subtraend_8b, subtraend_16b, subtraend_32b;
    logic [VLEN-1:0] summand_1, summand_2_8b, summand_2_16b, summand_2_32b;
    logic [VLEN-1:0] result_add_8b, result_add_16b, result_add_32b;
    logic [VLEN-1:0] result_add;

    assign subtraend_int = (vector_operation_i == vrsub) ? first_operand : second_operand;
    assign subtraend_neg = ~subtraend_int;

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            subtraend_8b[(8*(i+1))-1-:8]    = subtraend_neg[(8*(i+1))-1-:8] + 1'b1;
        for (int i = 0; i < VLENB/2; i++)
            subtraend_16b[(16*(i+1))-1-:16] = subtraend_neg[(16*(i+1))-1-:16] + 1'b1;
        for (int i = 0; i < VLENB/4; i++)
            subtraend_32b[(32*(i+1))-1-:32] = subtraend_neg[(32*(i+1))-1-:32] + 1'b1;
    end

    assign summand_1     = (vector_operation_i inside {vrsub})        ? second_operand : first_operand;
    assign summand_2_8b  = (vector_operation_i inside {vsub, vrsub})  ? subtraend_8b   : second_operand;
    assign summand_2_16b = (vector_operation_i inside {vsub, vrsub})  ? subtraend_16b  : second_operand;
    assign summand_2_32b = (vector_operation_i inside {vsub, vrsub})  ? subtraend_32b  : second_operand;

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

    logic [1:0]  signed_mode;
    logic        signed_mult;

    always_comb begin
        unique case (vector_operation_i)
            vmulh:    signed_mode = 2'b11;
            vmulhsu:  signed_mode = 2'b01;
            default:  signed_mode = 2'b00;
        endcase
    end

    assign signed_mult  = (signed_mode != 2'b00);

//////////////////////////////////////////////////////////////////////////////
// Multiplication 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic [7:0]       accum_8b    [VLENB-1:0];
    logic [8:0]       mult_op_a_8b[VLENB-1:0];
    logic [8:0]       mult_op_b_8b[VLENB-1:0];
    logic [VLENB-1:0] sign_a_8b;
    logic [VLENB-1:0] sign_b_8b;
    logic [17:0]      mac_result_8b[VLENB-1:0];
    logic [VLEN-1:0]  result_mult;

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            sign_a_8b[i] = (first_operand [(8*(i+1))-1] & signed_mode[0]);
            sign_b_8b[i] = (second_operand[(8*(i+1))-1] & signed_mode[1]);
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            accum_8b[i]     = '0;
            mult_op_a_8b[i] = {sign_a_8b[i], first_operand[(8*(i+1))-1-:8]};
            mult_op_b_8b[i] = {sign_b_8b[i], second_operand[(8*(i+1))-1-:8]};
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            mac_result_8b[i] = $signed(mult_op_a_8b[i]) * $signed(mult_op_b_8b[i]) + $signed(accum_8b[i]);
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            if (vector_operation_i == vmul)
                result_mult[(8*(i+1))-1-:8] = mac_result_8b[i][7:0];
            else
                result_mult[(8*(i+1))-1-:8] = mac_result_8b[i][15:8];
        end
    end

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
            default:         result_o <= result_add;
        endcase
    end

endmodule