module vectorALU
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64,
    parameter int VLENB = 8
) (
    input  logic                  clk,
    input  logic                  reset_n,

    input  logic [VLEN-1:0]       first_operand,
    input  logic [VLEN-1:0]       second_operand,
    input  logic [VLEN-1:0]       third_operand,
    input  vector_states_e        current_state,
    input  logic [4:0]            cycle_count,
    input  logic [4:0]            cycle_count_r,
    input  vlmul_e                vlmul,
    input  logic[$bits(VLEN)-1:0] vl,
    input  logic                  vm,
    input  logic [ VLENB   -1:0]  mask_sew8 [8],
    input  logic [(VLENB/2)-1:0]  mask_sew16[8],
    input  logic [(VLENB/4)-1:0]  mask_sew32[8],

    input  iTypeVector_e          vector_operation_i,
    input  vew_e                  vsew,

    output logic                  hold_o,
    output logic                  hold_widening_o,
    output logic [VLEN-1:0]       result_o
);

    logic hold_mult;
    logic hold;

    logic [(VLENB)  -1:0][ 7:0] first_operand_8b,  second_operand_8b,  third_operand_8b;
    logic [(VLENB/2)-1:0][15:0] first_operand_16b, second_operand_16b, third_operand_16b;
    logic [(VLENB/4)-1:0][31:0] first_operand_32b, second_operand_32b, third_operand_32b;

    logic [VLEN-1:0] third_operand_r, result_mult_r;

//////////////////////////////////////////////////////////////////////////////
// Operands Control
//////////////////////////////////////////////////////////////////////////////
    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            first_operand_8b [i] = first_operand [(8*i)+:8];
            second_operand_8b[i] = second_operand[(8*i)+:8];
            third_operand_8b [i] = third_operand [(8*i)+:8];
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB/2; i++) begin
            first_operand_16b [i] = first_operand [(16*i)+:16];
            second_operand_16b[i] = second_operand[(16*i)+:16];
            third_operand_16b [i] = third_operand [(16*i)+:16];
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB/4; i++) begin
            first_operand_32b [i] = first_operand [(32*i)+:32];
            second_operand_32b[i] = second_operand[(32*i)+:32];
            third_operand_32b [i] = third_operand [(32*i)+:32];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Widening Control
//////////////////////////////////////////////////////////////////////////////
    logic widening_instruction;
    logic widening_counter;

    assign widening_instruction = (vector_operation_i inside {VWMUL, VWMULU, VWMULSU});

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            widening_counter <= 1'b0;
        end
        else if (widening_instruction && !hold && current_state == V_EXEC) begin
            widening_counter <= widening_counter + 1'b1;
        end
        else begin
            widening_counter <= 1'b0;
        end
    end

    assign hold_widening_o = widening_instruction & !widening_counter && current_state == V_EXEC;

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

    logic                [ 7:0] second_operand_reductions_8b;
    logic                [15:0] second_operand_reductions_16b;
    logic                [31:0] second_operand_reductions_32b;

    logic [(VLENB)  -1:0][ 7:0] result_redand_8b, result_redor_8b;
    logic [(VLENB)  -1:0][ 7:0] result_redxor_8b, result_redsum_8b;
    logic [(VLENB)  -1:0][ 7:0] result_redmin_8b, result_redminu_8b;
    logic [(VLENB)  -1:0][ 7:0] result_redmax_8b, result_redmaxu_8b;

    logic [(VLENB/2)-1:0][15:0] result_redand_16b, result_redor_16b;
    logic [(VLENB/2)-1:0][15:0] result_redxor_16b, result_redsum_16b;
    logic [(VLENB/2)-1:0][15:0] result_redmin_16b, result_redminu_16b;
    logic [(VLENB/2)-1:0][15:0] result_redmax_16b, result_redmaxu_16b;

    logic [(VLENB/4)-1:0][31:0] result_redand_32b, result_redor_32b;
    logic [(VLENB/4)-1:0][31:0] result_redxor_32b, result_redsum_32b;
    logic [(VLENB/4)-1:0][31:0] result_redmin_32b, result_redminu_32b;
    logic [(VLENB/4)-1:0][31:0] result_redmax_32b, result_redmaxu_32b;

    logic [VLEN-1:0] result_redand, result_redor;
    logic [VLEN-1:0] result_redxor, result_redsum;
    logic [VLEN-1:0] result_redmin, result_redminu;
    logic [VLEN-1:0] result_redmax, result_redmaxu;

    always_comb begin
        if (cycle_count_r > 0) begin
            second_operand_reductions_8b  = result_o[ 7:0];
            second_operand_reductions_16b = result_o[15:0];
            second_operand_reductions_32b = result_o[31:0];
        end
        else begin
            second_operand_reductions_8b  = second_operand_8b [0];
            second_operand_reductions_16b = second_operand_16b[0];
            second_operand_reductions_32b = second_operand_32b[0];
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            if (i == 0) begin
                if (vm || mask_sew8[cycle_count_r][0]) begin
                    result_redand_8b[i] = first_operand_8b[0] & second_operand_reductions_8b;
                    result_redor_8b [i] = first_operand_8b[0] | second_operand_reductions_8b;
                    result_redxor_8b[i] = first_operand_8b[0] ^ second_operand_reductions_8b;
                    result_redsum_8b[i] = first_operand_8b[0] + second_operand_reductions_8b;

                    result_redmin_8b [i] = ($signed(first_operand_8b[0]) > $signed(second_operand_reductions_8b))
                                            ? second_operand_reductions_8b
                                            : first_operand_8b [0];
                    result_redminu_8b[i] = (first_operand_8b[0] > second_operand_reductions_8b)
                                            ? second_operand_reductions_8b
                                            : first_operand_8b [0];
                    result_redmax_8b [i] = ($signed(first_operand_8b[0]) > $signed(second_operand_reductions_8b))
                                            ? first_operand_8b [0]
                                            : second_operand_reductions_8b;
                    result_redmaxu_8b[i] = (first_operand_8b[0] > second_operand_reductions_8b)
                                            ? first_operand_8b [0]
                                            : second_operand_reductions_8b;
                end
                else begin
                    result_redand_8b[i] = second_operand_reductions_8b;
                    result_redor_8b [i] = second_operand_reductions_8b;
                    result_redxor_8b[i] = second_operand_reductions_8b;
                    result_redsum_8b[i] = second_operand_reductions_8b;

                    result_redmin_8b [i] = second_operand_reductions_8b;
                    result_redminu_8b[i] = second_operand_reductions_8b;
                    result_redmax_8b [i] = second_operand_reductions_8b;
                    result_redmaxu_8b[i] = second_operand_reductions_8b;
                end
            end
            else begin
                if (vm || mask_sew8[cycle_count_r][i]) begin
                    result_redand_8b[i] = first_operand_8b[i] & result_redand_8b[i-1];
                    result_redor_8b [i] = first_operand_8b[i] | result_redor_8b [i-1];
                    result_redxor_8b[i] = first_operand_8b[i] ^ result_redxor_8b[i-1];
                    result_redsum_8b[i] = first_operand_8b[i] + result_redsum_8b[i-1];

                    result_redmin_8b [i] = ($signed(first_operand_8b[i]) > $signed(result_redmin_8b[i-1]))
                                            ? result_redmin_8b[i-1]
                                            : first_operand_8b[i];
                    result_redminu_8b[i] = (first_operand_8b[i] > result_redminu_8b[i-1])
                                            ? result_redminu_8b[i-1]
                                            : first_operand_8b[i];
                    result_redmax_8b [i] = ($signed(first_operand_8b[i]) > $signed(result_redmax_8b[i-1]))
                                            ? first_operand_8b[i]
                                            : result_redmax_8b[i-1];
                    result_redmaxu_8b[i] = (first_operand_8b[i] > result_redmaxu_8b[i-1])
                                            ? first_operand_8b[i]
                                            : result_redmaxu_8b[i-1];
                end
                else begin
                    result_redand_8b[i] = result_redand_8b[i-1];
                    result_redor_8b [i] = result_redor_8b [i-1];
                    result_redxor_8b[i] = result_redxor_8b[i-1];
                    result_redsum_8b[i] = result_redsum_8b[i-1];

                    result_redmin_8b [i] = result_redmin_8b [i-1];
                    result_redminu_8b[i] = result_redminu_8b[i-1];
                    result_redmax_8b [i] = result_redmax_8b [i-1];
                    result_redmaxu_8b[i] = result_redmaxu_8b[i-1];
                end
            end
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB/2; i++) begin
            if (i == 0) begin
                if (vm || mask_sew16[cycle_count_r][0]) begin
                    result_redand_16b[i] = first_operand_16b[0] & second_operand_reductions_16b;
                    result_redor_16b [i] = first_operand_16b[0] | second_operand_reductions_16b;
                    result_redxor_16b[i] = first_operand_16b[0] ^ second_operand_reductions_16b;
                    result_redsum_16b[i] = first_operand_16b[0] + second_operand_reductions_16b;

                    result_redmin_16b [i] = ($signed(first_operand_16b[0]) > $signed(second_operand_reductions_16b))
                                            ? second_operand_reductions_16b
                                            : first_operand_16b[0];
                    result_redminu_16b[i] = (first_operand_16b[0] > second_operand_reductions_16b)
                                            ? second_operand_reductions_16b
                                            : first_operand_16b[0];
                    result_redmax_16b [i] = ($signed(first_operand_16b[0]) > $signed(second_operand_reductions_16b))
                                            ? first_operand_16b[0]
                                            : second_operand_reductions_16b;
                    result_redmaxu_16b[i] = (first_operand_16b[0] > second_operand_reductions_16b)
                                            ? first_operand_16b[0]
                                            : second_operand_reductions_16b;
                end
                else begin
                    result_redand_16b[i] = second_operand_reductions_16b;
                    result_redor_16b [i] = second_operand_reductions_16b;
                    result_redxor_16b[i] = second_operand_reductions_16b;
                    result_redsum_16b[i] = second_operand_reductions_16b;

                    result_redmin_16b [i] = second_operand_reductions_16b;
                    result_redminu_16b[i] = second_operand_reductions_16b;
                    result_redmax_16b [i] = second_operand_reductions_16b;
                    result_redmaxu_16b[i] = second_operand_reductions_16b;
                end
            end
            else begin
                if (vm || mask_sew16[cycle_count_r][i]) begin
                    result_redand_16b[i] = first_operand_16b[i] & result_redand_16b[i-1];
                    result_redor_16b [i] = first_operand_16b[i] | result_redor_16b [i-1];
                    result_redxor_16b[i] = first_operand_16b[i] ^ result_redxor_16b[i-1];
                    result_redsum_16b[i] = first_operand_16b[i] + result_redsum_16b[i-1];

                    result_redmin_16b [i] = ($signed(first_operand_16b[i]) > $signed(result_redmin_16b[i-1]))
                                            ? result_redmin_16b[i-1]
                                            : first_operand_16b[i];
                    result_redminu_16b[i] = (first_operand_16b[i] > result_redminu_16b[i-1])
                                            ? result_redminu_16b[i-1]
                                            : first_operand_16b[i];
                    result_redmax_16b [i] = ($signed(first_operand_16b[i]) > $signed(result_redmax_16b[i-1]))
                                            ? first_operand_16b[i]
                                            : result_redmax_16b[i-1];
                    result_redmaxu_16b[i] = (first_operand_16b[i] > result_redmaxu_16b[i-1])
                                            ? first_operand_16b[i]
                                            : result_redmaxu_16b[i-1];
                end
                else begin
                    result_redand_16b[i] = result_redand_16b[i-1];
                    result_redor_16b [i] = result_redor_16b [i-1];
                    result_redxor_16b[i] = result_redxor_16b[i-1];
                    result_redsum_16b[i] = result_redsum_16b[i-1];

                    result_redmin_16b [i] = result_redmin_16b [i-1];
                    result_redminu_16b[i] = result_redminu_16b[i-1];
                    result_redmax_16b [i] = result_redmax_16b [i-1];
                    result_redmaxu_16b[i] = result_redmaxu_16b[i-1];
                end
            end
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB/4; i++) begin
            if (i == 0) begin
                if (vm || mask_sew32[cycle_count_r][i]) begin
                    result_redand_32b[i] = first_operand_32b[0] & second_operand_reductions_32b;
                    result_redor_32b [i] = first_operand_32b[0] | second_operand_reductions_32b;
                    result_redxor_32b[i] = first_operand_32b[0] ^ second_operand_reductions_32b;
                    result_redsum_32b[i] = first_operand_32b[0] + second_operand_reductions_32b;

                    result_redmin_32b [i] = ($signed(first_operand_32b[0]) > $signed(second_operand_reductions_32b))
                                            ? second_operand_reductions_32b
                                            : first_operand_32b [0];
                    result_redminu_32b[i] = (first_operand_32b[0] > second_operand_reductions_32b)
                                            ? second_operand_reductions_32b
                                            : first_operand_32b [0];
                    result_redmax_32b [i] = ($signed(first_operand_32b[0]) > $signed(second_operand_reductions_32b))
                                            ? first_operand_32b [0]
                                            : second_operand_reductions_32b;
                    result_redmaxu_32b[i] = (first_operand_32b[0] > second_operand_reductions_32b)
                                            ? first_operand_32b [0]
                                            : second_operand_reductions_32b;
                end
                else begin
                    result_redand_32b[i] = second_operand_reductions_32b;
                    result_redor_32b [i] = second_operand_reductions_32b;
                    result_redxor_32b[i] = second_operand_reductions_32b;
                    result_redsum_32b[i] = second_operand_reductions_32b;

                    result_redmin_32b [i] = second_operand_reductions_32b;
                    result_redminu_32b[i] = second_operand_reductions_32b;
                    result_redmax_32b [i] = second_operand_reductions_32b;
                    result_redmaxu_32b[i] = second_operand_reductions_32b;
                end
            end
            else begin
                if (vm || mask_sew32[cycle_count_r][i]) begin
                    result_redand_32b[i] = first_operand_32b[i] & result_redand_32b[i-1];
                    result_redor_32b [i] = first_operand_32b[i] | result_redor_32b [i-1];
                    result_redxor_32b[i] = first_operand_32b[i] ^ result_redxor_32b[i-1];
                    result_redsum_32b[i] = first_operand_32b[i] + result_redsum_32b[i-1];

                    result_redmin_32b [i] = ($signed(first_operand_32b[i]) > $signed(result_redmin_32b[i-1]))
                                            ? result_redmin_32b[i-1]
                                            : first_operand_32b[i];
                    result_redminu_32b[i] = (first_operand_32b[i] > result_redminu_32b[i-1])
                                            ? result_redminu_32b[i-1]
                                            : first_operand_32b[i];
                    result_redmax_32b [i] = ($signed(first_operand_32b[i]) > $signed(result_redmax_32b[i-1]))
                                            ? first_operand_32b[i]
                                            : result_redmax_32b[i-1];
                    result_redmaxu_32b[i] = (first_operand_32b[i] > result_redmaxu_32b[i-1])
                                            ? first_operand_32b[i]
                                            : result_redmaxu_32b[i-1];
                end
                else begin
                    result_redand_32b[i] = result_redand_32b[i-1];
                    result_redor_32b [i] = result_redor_32b [i-1];
                    result_redxor_32b[i] = result_redxor_32b[i-1];
                    result_redsum_32b[i] = result_redsum_32b[i-1];

                    result_redmin_32b [i] = result_redmin_32b [i-1];
                    result_redminu_32b[i] = result_redminu_32b[i-1];
                    result_redmax_32b [i] = result_redmax_32b [i-1];
                    result_redmaxu_32b[i] = result_redmaxu_32b[i-1];
                end
            end
        end
    end

    always_comb begin
        unique case (vsew)
            EW8: begin
                result_redand  = {'0, result_redand_8b [vl-1]};
                result_redor   = {'0, result_redor_8b  [vl-1]};
                result_redxor  = {'0, result_redxor_8b [vl-1]};
                result_redsum  = {'0, result_redsum_8b [vl-1]};
                result_redmin  = {'0, result_redmin_8b [vl-1]};
                result_redminu = {'0, result_redminu_8b[vl-1]};
                result_redmax  = {'0, result_redmax_8b [vl-1]};
                result_redmaxu = {'0, result_redmaxu_8b[vl-1]};
            end
            EW16: begin
                result_redand  = {'0, result_redand_16b [vl-1]};
                result_redor   = {'0, result_redor_16b  [vl-1]};
                result_redxor  = {'0, result_redxor_16b [vl-1]};
                result_redsum  = {'0, result_redsum_16b [vl-1]};
                result_redmin  = {'0, result_redmin_16b [vl-1]};
                result_redminu = {'0, result_redminu_16b[vl-1]};
                result_redmax  = {'0, result_redmax_16b [vl-1]};
                result_redmaxu = {'0, result_redmaxu_16b[vl-1]};
            end
            default: begin
                result_redand  = {'0, result_redand_32b [vl-1]};
                result_redor   = {'0, result_redor_32b  [vl-1]};
                result_redxor  = {'0, result_redxor_32b [vl-1]};
                result_redsum  = {'0, result_redsum_32b [vl-1]};
                result_redmin  = {'0, result_redmin_32b [vl-1]};
                result_redminu = {'0, result_redminu_32b[vl-1]};
                result_redmax  = {'0, result_redmax_32b [vl-1]};
                result_redmaxu = {'0, result_redmaxu_32b[vl-1]};
            end
        endcase
    end

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
            VRSUB:   subtraend = first_operand;
            VNMSAC,
            VNMSUB:  subtraend = result_mult_r;
            default: subtraend = second_operand;
        endcase
    end

    assign subtraend_neg = ~subtraend;

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            subtraend_8b[(8*i)+:8]    = subtraend_neg[(8*i)+:8] + 1'b1;
        for (int i = 0; i < VLENB/2; i++)
            subtraend_16b[(16*i)+:16] = subtraend_neg[(16*i)+:16] + 1'b1;
        for (int i = 0; i < VLENB/4; i++)
            subtraend_32b[(32*i)+:32] = subtraend_neg[(32*i)+:32] + 1'b1;
    end

    always_comb begin
        unique case (vector_operation_i)
            VRSUB:   summand_1 = second_operand;
            VNMSAC,
            VMACC,
            VMADD,
            VNMSUB:  summand_1 = third_operand_r;
            default: summand_1 = first_operand;
        endcase
    end

    assign summand_2 =  (vector_operation_i inside {VMACC, VMADD})
                        ? result_mult_r
                        : second_operand;

    always_comb begin
        if (vector_operation_i inside {VSUB, VRSUB, VNMSAC, VNMSUB}) begin
            summand_2_8b  = subtraend_8b;
            summand_2_16b = subtraend_16b;
            summand_2_32b = subtraend_32b;
        end
        else begin
            summand_2_8b  = summand_2;
            summand_2_16b = summand_2;
            summand_2_32b = summand_2;
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            result_add_8b[(8*i)+:8]    = summand_1[(8*i)+:8]   + summand_2_8b[(8*i)+:8];
        for (int i = 0; i < VLENB/2; i++)
            result_add_16b[(16*i)+:16] = summand_1[(16*i)+:16] + summand_2_16b[(16*i)+:16];
        for (int i = 0; i < VLENB/4; i++)
            result_add_32b[(32*i)+:32] = summand_1[(32*i)+:32] + summand_2_32b[(32*i)+:32];
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
                    result_sll[(8*i)+:8]   =         first_operand_8b[i]    <<  second_operand_8b[i][2:0];
                    result_srl[(8*i)+:8]   =         first_operand_8b[i]    >>  second_operand_8b[i][2:0];
                    result_sra[(8*i)+:8]   = $signed(first_operand_8b[i])   >>> second_operand_8b[i][2:0];
                end
            EW16:
                for (int i = 0; i < VLENB/2; i++) begin
                    result_sll[(16*i)+:16] =         first_operand_16b[i]  <<  second_operand_16b[i][3:0];
                    result_srl[(16*i)+:16] =         first_operand_16b[i]  >>  second_operand_16b[i][3:0];
                    result_sra[(16*i)+:16] = $signed(first_operand_16b[i]) >>> second_operand_16b[i][3:0];
                end
            default:
                for (int i = 0; i < VLENB/4; i++) begin
                    result_sll[(32*i)+:32] =         first_operand_32b[i]  <<  second_operand_32b[i][4:0];
                    result_srl[(32*i)+:32] =         first_operand_32b[i]  >>  second_operand_32b[i][4:0];
                    result_sra[(32*i)+:32] = $signed(first_operand_32b[i]) >>> second_operand_32b[i][4:0];
                end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Compare
//////////////////////////////////////////////////////////////////////////////

    logic [ VLENB   -1:0] equal_8b,  greater_than_8b,  greater_than_signed_8b,  result_comparison_8b;
    logic [(VLENB/2)-1:0] equal_16b, greater_than_16b, greater_than_signed_16b, result_comparison_16b;
    logic [(VLENB/4)-1:0] equal_32b, greater_than_32b, greater_than_signed_32b, result_comparison_32b;
    logic [ VLENB   -1:0] result_comparison;

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            equal_8b[i]                =         first_operand_8b[i]  ==         second_operand_8b[i];
            greater_than_8b[i]         =         first_operand_8b[i]  >          second_operand_8b[i];
            greater_than_signed_8b[i]  = $signed(first_operand_8b[i]) >  $signed(second_operand_8b[i]);
        end

        for (int i = 0; i < VLENB/2; i++) begin
            equal_16b[i]               =         first_operand_16b[i]  ==         second_operand_16b[i];
            greater_than_16b[i]        =         first_operand_16b[i]  >          second_operand_16b[i];
            greater_than_signed_16b[i] = $signed(first_operand_16b[i]) >  $signed(second_operand_16b[i]);
        end

        for (int i = 0; i < VLENB/4; i++) begin
            equal_32b[i]               =         first_operand_32b[i]  ==         second_operand_32b[i];
            greater_than_32b[i]        =         first_operand_32b[i]  >          second_operand_32b[i];
            greater_than_signed_32b[i] = $signed(first_operand_32b[i]) >  $signed(second_operand_32b[i]);
        end
    end
/*
    always_comb begin
        unique case(vector_operation_i)
            VMSNE:  begin
                        result_comparison_8b  = ~equal_8b;
                        result_comparison_16b = ~equal_16b;
                        result_comparison_32b = ~equal_32b;
                    end
            VMSLTU: begin
                        result_comparison_8b  = ~equal_8b  & ~greater_than_8b;
                        result_comparison_16b = ~equal_16b & ~greater_than_16b;
                        result_comparison_32b = ~equal_32b & ~greater_than_32b;
                    end
            VMSLT:  begin
                        result_comparison_8b  = ~equal_8b  & ~greater_than_signed_8b;
                        result_comparison_16b = ~equal_16b & ~greater_than_signed_16b;
                        result_comparison_32b = ~equal_32b & ~greater_than_signed_32b;
                    end
            VMSLEU: begin
                        result_comparison_8b  = equal_8b  | ~greater_than_8b;
                        result_comparison_16b = equal_16b | ~greater_than_16b;
                        result_comparison_32b = equal_32b | ~greater_than_32b;
                    end
            VMSLE:  begin
                        result_comparison_8b  = equal_8b  | ~greater_than_signed_8b;
                        result_comparison_16b = equal_16b | ~greater_than_signed_16b;
                        result_comparison_32b = equal_32b | ~greater_than_signed_32b;
                    end
            VMSGTU: begin
                        result_comparison_8b  = greater_than_8b;
                        result_comparison_16b = greater_than_16b;
                        result_comparison_32b = greater_than_32b;
                    end
            VMSGT : begin
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
*/
//////////////////////////////////////////////////////////////////////////////
// Min/Max
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_minu, result_min, result_maxu, result_max;

    always_comb begin
        unique case (vsew)
            EW8: begin
                for (int i = 0; i < VLENB; i++) begin
                    result_minu[(8*i)+:8] = (greater_than_8b[i])         ? second_operand_8b[i] : first_operand_8b [i];
                    result_min [(8*i)+:8] = (greater_than_signed_8b[i])  ? second_operand_8b[i] : first_operand_8b [i];
                    result_maxu[(8*i)+:8] = (greater_than_8b[i])         ? first_operand_8b [i] : second_operand_8b[i];
                    result_max [(8*i)+:8] = (greater_than_signed_8b[i])  ? first_operand_8b [i] : second_operand_8b[i];
                end
            end

            EW16: begin
                for (int i = 0; i < VLENB/2; i++) begin
                    result_minu[(16*i)+:16] = (greater_than_16b[i])         ? second_operand_16b[i] : first_operand_16b [i];
                    result_min [(16*i)+:16] = (greater_than_signed_16b[i])  ? second_operand_16b[i] : first_operand_16b [i];
                    result_maxu[(16*i)+:16] = (greater_than_16b[i])         ? first_operand_16b [i] : second_operand_16b[i];
                    result_max [(16*i)+:16] = (greater_than_signed_16b[i])  ? first_operand_16b [i] : second_operand_16b[i];
                end
            end

            default: begin
                for (int i = 0; i < VLENB/4; i++) begin
                    result_minu[(32*i)+:32] = (greater_than_32b[i])         ? second_operand_32b[i] : first_operand_32b [i];
                    result_min [(32*i)+:32] = (greater_than_signed_32b[i])  ? second_operand_32b[i] : first_operand_32b [i];
                    result_maxu[(32*i)+:32] = (greater_than_32b[i])         ? first_operand_32b [i] : second_operand_32b[i];
                    result_max [(32*i)+:32] = (greater_than_signed_32b[i])  ? first_operand_32b [i] : second_operand_32b[i];
                end
            end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Multiplication_common
//////////////////////////////////////////////////////////////////////////////

    logic [(2*VLEN)-1:0] result_mult;
    logic [1:0] mult_signed_mode;

    always_comb begin
        unique case (vector_operation_i)
            VMULH,   VWMUL:   mult_signed_mode = 2'b11;
            VMULHSU, VWMULSU: mult_signed_mode = 2'b01;
            default:          mult_signed_mode = 2'b00;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Multiplication 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic [VLENB-1:0][ 7:0] mult_op_a_8b;
    logic [VLENB-1:0][ 7:0] mult_op_b_8b;
    logic [VLENB-1:0][15:0] mult_result_8b;

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            mult_op_a_8b[i] = first_operand_8b [i];
            mult_op_b_8b[i] = second_operand_8b[i];
        end
    end

    generate
        for (genvar i_mul8b = 0; i_mul8b < VLENB; i_mul8b++) begin : MUL8B_LOOP
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

    logic [(VLENB/2)-1:0][15:0] mult_op_a_16b;
    logic [(VLENB/2)-1:0][15:0] mult_op_b_16b;
    logic [(VLENB/2)-1:0][31:0] mult_result_16b;

    always_comb begin
        for (int i = 0; i < VLENB/2; i++) begin
            mult_op_a_16b[i] = first_operand_16b [i];
            mult_op_b_16b[i] = second_operand_16b[i];
        end
    end

    generate
        for (genvar i_mul16b = 0; i_mul16b < VLENB/2; i_mul16b++) begin : MUL16B_LOOP
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

    logic [(VLENB/4)-1:0][31:0] mult_op_a_32b;
    logic [(VLENB/4)-1:0][31:0] mult_op_b_32b;
    logic [(VLENB/4)-1:0][31:0] mult_result_32b;

    always_comb begin
        for (int i = 0; i < VLENB/4; i++) begin
            mult_op_a_32b[i] = first_operand_32b [i];
            mult_op_b_32b[i] = second_operand_32b[i];
        end
    end

    logic ended_acc;
    assign ended_acc = (vector_operation_i inside {VMACC, VNMSAC, VMADD, VNMSUB})
                        &&  (
                                (vlmul == LMUL_1  && cycle_count > 1)
                            ||  (vlmul == LMUL_2  && cycle_count > 2)
                            ||  (vlmul == LMUL_4  && cycle_count > 4)
                            ||  (vlmul == LMUL_8  && cycle_count > 8)
                            );

    assign mult_enable = (
                            (vector_operation_i inside {VMUL, VMULH, VMULHSU, VMULHU, VMACC, VNMSAC, VMADD, VNMSUB})
                        &&  (current_state == V_EXEC)
                        &&  (vsew == EW32)
                        &&  (!ended_acc)
                        );
    assign mult_low    = (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB});
    assign hold_mult   = |hold_mult_int;

    generate
        for (genvar i_mul32b = 0; i_mul32b < VLENB/4; i_mul32b++) begin : MUL32B_LOOP
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
            EW8:
                for (int i = 0; i < VLENB; i++)
                    if (widening_instruction)
                        result_mult[(16*i)+:16] = mult_result_8b[i][15:0];
                    else if (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB})
                        result_mult[(8*i)+:8]   = mult_result_8b[i][7:0];
                    else
                        result_mult[(8*i)+:8]   = mult_result_8b[i][15:8];

            EW16:
                for (int i = 0; i < VLENB/2; i++)
                    if (widening_instruction)
                        result_mult[(32*i)+:32] = mult_result_16b[i][31:0];
                    else if (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB})
                        result_mult[(16*i)+:16] = mult_result_16b[i][15:0];
                    else
                        result_mult[(16*i)+:16] = mult_result_16b[i][31:16];

            default:
                for (int i = 0; i < VLENB/4; i++)
                    result_mult[(32*i)+:32] = mult_result_32b[i][31:0];

        endcase
    end

    always @(posedge clk) begin
        if (!hold_mult) begin
            result_mult_r   <= result_mult;
            third_operand_r <= third_operand;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Division Common
//////////////////////////////////////////////////////////////////////////////

    logic [ VLENB   -1:0] hold_div_8b;
    logic [(VLENB/2)-1:0] hold_div_16b;
    logic [(VLENB/4)-1:0] hold_div_32b;
    logic hold_div;

    logic            div_signed;
    logic            div_enable;
    logic [VLEN-1:0] result_div;
    logic [VLEN-1:0] result_rem;

    assign div_enable = (vector_operation_i inside {VDIV, VDIVU, VREM, VREMU} && current_state == V_EXEC);
    assign div_signed = (vector_operation_i inside {VDIV, VREM});

    assign hold_div = (|hold_div_8b) | (|hold_div_16b) | (|hold_div_32b);

//////////////////////////////////////////////////////////////////////////////
// Division 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic                  div_enable_8b;
    logic [VLENB-1:0][7:0] div_result_8b;
    logic [VLENB-1:0][7:0] rem_result_8b;

    assign div_enable_8b = (div_enable && vsew == EW8);

    generate
        for (genvar i_div8b = 0; i_div8b < VLENB; i_div8b++) begin : DIV8B_LOOP
            div #(
                .N(8)
            ) div8b (
                .clk              (clk),
                .reset_n          (reset_n),
                .first_operand_i  (first_operand_8b [i_div8b]),
                .second_operand_i (second_operand_8b[i_div8b]),
                .enable_i         (div_enable_8b),
                .signed_i         (div_signed),
                .hold_o           (hold_div_8b[i_div8b]),
                .div_result_o     (div_result_8b[i_div8b]),
                .rem_result_o     (rem_result_8b[i_div8b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Division 16 bits
//////////////////////////////////////////////////////////////////////////////

    logic                       div_enable_16b;
    logic [(VLENB/2)-1:0][15:0] div_result_16b;
    logic [(VLENB/2)-1:0][15:0] rem_result_16b;

    assign div_enable_16b = (div_enable && vsew == EW16);

    generate
        for (genvar i_div16b = 0; i_div16b < VLENB/2; i_div16b++) begin : DIV16B_LOOP
            div #(
                .N(16)
            ) div16b (
                .clk              (clk),
                .reset_n          (reset_n),
                .first_operand_i  (first_operand_16b [i_div16b]),
                .second_operand_i (second_operand_16b[i_div16b]),
                .enable_i         (div_enable_16b),
                .signed_i         (div_signed),
                .hold_o           (hold_div_16b[i_div16b]),
                .div_result_o     (div_result_16b[i_div16b]),
                .rem_result_o     (rem_result_16b[i_div16b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Division 32 bits
//////////////////////////////////////////////////////////////////////////////

    logic                       div_enable_32b;
    logic [(VLENB/4)-1:0][31:0] div_result_32b;
    logic [(VLENB/4)-1:0][31:0] rem_result_32b;

    assign div_enable_32b = (div_enable && vsew == EW32);

    generate
        for (genvar i_div32b = 0; i_div32b < VLENB/4; i_div32b++) begin : DIV32B_LOOP
            div #(
                .N(32)
            ) div32b (
                .clk              (clk),
                .reset_n          (reset_n),
                .first_operand_i  (first_operand_32b [i_div32b]),
                .second_operand_i (second_operand_32b[i_div32b]),
                .enable_i         (div_enable_32b),
                .signed_i         (div_signed),
                .hold_o           (hold_div_32b[i_div32b]),
                .div_result_o     (div_result_32b[i_div32b]),
                .rem_result_o     (rem_result_32b[i_div32b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Division Demux
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (vsew)
            EW8: begin
                for (int i = 0; i < VLENB; i++) begin
                    result_div[(8*i)+:8] = div_result_8b[i];
                    result_rem[(8*i)+:8] = rem_result_8b[i];
                end
            end
            EW16: begin
                for (int i = 0; i < VLENB/2; i++) begin
                    result_div[(16*i)+:16] = div_result_16b[i];
                    result_rem[(16*i)+:16] = rem_result_16b[i];
                end
            end
            default: begin
                for (int i = 0; i < VLENB/4; i++)begin
                    result_div[(32*i)+:32] = div_result_32b[i];
                    result_rem[(32*i)+:32] = rem_result_32b[i];
                end
            end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Hold generation
//////////////////////////////////////////////////////////////////////////////

    assign hold   = hold_mult | hold_div;

    assign hold_o = hold | hold_widening_o;

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk) begin
        unique case(vector_operation_i)
            VAND:            result_o <= result_and;
            VOR:             result_o <= result_or;
            VXOR:            result_o <= result_xor;
            VSLL:            result_o <= result_sll;
            VSRL:            result_o <= result_srl;
            VSRA:            result_o <= result_sra;
            /*
            VMSEQ,  VMSNE,
            VMSLTU, VMSLT,
            VMSLEU, VMSLE,
            VMSGTU, VMSGT:   result_o <= result_comparison;
            */
            VMIN:            result_o <= result_min;
            VMINU:           result_o <= result_minu;
            VMAX:            result_o <= result_max;
            VMAXU:           result_o <= result_maxu;
            VMUL, VMULH,
            VMULHU, VMULHSU: result_o <= result_mult;
            VWMUL, VWMULU,
            VWMULSU:         result_o <= (widening_counter == 1'b1) ? result_mult[(2*VLEN)-1:VLEN] : result_mult[VLEN-1:0];
            VDIV, VDIVU:     result_o <= result_div;
            VREM, VREMU:     result_o <= result_rem;
            VREDAND:         result_o <= result_redand;
            VREDOR:          result_o <= result_redor;
            VREDXOR:         result_o <= result_redxor;
            VREDSUM:         result_o <= result_redsum;
            VREDMIN:         result_o <= result_redmin;
            VREDMINU:        result_o <= result_redminu;
            VREDMAX:         result_o <= result_redmax;
            VREDMAXU:        result_o <= result_redmaxu;
            VMV, VMVSX:      result_o <= second_operand;
            VMVXS, VMVR:     result_o <= first_operand;
            default:         result_o <= result_add;
        endcase
    end

endmodule