`include "RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorALU
    import RS5_pkg::*;
#(
    parameter int VLEN            = 64,
    parameter int VLENB           = 8,
    parameter int V_LOGIC_ON      = 1'b1,
    parameter int V_MINMAX_ON     = 1'b1,
    parameter int V_REDLOGIC_ON   = 1'b1,
    parameter int V_REDMINMAX_ON  = 1'b1,
    parameter int V_REDSUM_ON     = 1'b1,
    parameter int V_MERGE_ON      = 1'b1,
    parameter int V_DIV_ON        = 1'b1
) (
    input  logic                        clk,
    input  logic                        reset_n,

    input  logic [VLEN-1:0]             first_operand,
    input  logic [VLEN-1:0]             second_operand,
    input  vector_states_e              current_state,
    input  logic [3:0]                  cycle_count,
    input  logic [3:0]                  cycle_count_r,
    input  vlmul_e                      vlmul,
    input  logic[$bits(VLEN)-1:0]       vl,
    input  logic                        vm,
    input  logic [7:0][ VLENB   -1:0]   mask_sew8,
    input  logic [7:0][(VLENB/2)-1:0]   mask_sew16,
    input  logic [7:0][(VLENB/4)-1:0]   mask_sew32,

    input  iTypeVector_e                vector_operation_i,
    input  vew_e                        vsew,

    output logic                        hold_o,
    output logic                        hold_widening_o,
    output logic                        hold_accumulation_o,
    output logic [VLEN-1:0]             result_mask_o,
    output logic [VLEN-1:0]             result_o
);

    localparam TREE_LEVELS_8b  = $clog2(VLENB);
    localparam TREE_LEVELS_16b = $clog2(VLENB/2);
    localparam TREE_LEVELS_32b = $clog2(VLENB/4);

    logic hold_mult;
    logic hold;

    logic [(VLENB)  -1:0][ 7:0] first_operand_8b,  second_operand_8b;
    logic [(VLENB/2)-1:0][15:0] first_operand_16b, second_operand_16b;
    logic [(VLENB/4)-1:0][31:0] first_operand_32b, second_operand_32b;

    logic [VLEN-1:0] result_mult_r;

//////////////////////////////////////////////////////////////////////////////
// Operands Control
//////////////////////////////////////////////////////////////////////////////
    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            first_operand_8b [i] = first_operand [(8*i)+:8];
            second_operand_8b[i] = second_operand[(8*i)+:8];
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB/2; i++) begin
            first_operand_16b [i] = first_operand [(16*i)+:16];
            second_operand_16b[i] = second_operand[(16*i)+:16];
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB/4; i++) begin
            first_operand_32b [i] = first_operand [(32*i)+:32];
            second_operand_32b[i] = second_operand[(32*i)+:32];
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
// Accumulation Control
//////////////////////////////////////////////////////////////////////////////
    logic accumulate_instruction;
    logic hold_accumulation_r;

    assign accumulate_instruction = (vector_operation_i inside {VMACC, VNMSAC, VMADD, VNMSUB});

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hold_accumulation_r <= 1'b0;
        end
        else begin
            hold_accumulation_r <= hold_accumulation_o;
        end
    end

    assign hold_accumulation_o = accumulate_instruction && !hold && current_state == V_EXEC && !hold_accumulation_r;

//////////////////////////////////////////////////////////////////////////////
// Logical
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_and, result_or, result_xor;

    if (V_LOGIC_ON) begin : v_logic_gen_on
        always_comb begin
            result_and = first_operand & second_operand;
            result_or  = first_operand | second_operand;
            result_xor = first_operand ^ second_operand;
        end
    end
    else begin  : v_logic_gen_off
        always_comb begin
            result_and = '0;
            result_or  = '0;
            result_xor = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Reductions General
//////////////////////////////////////////////////////////////////////////////

    logic     [ 7:0] second_operand_reductions_8b;
    logic     [15:0] second_operand_reductions_16b;
    logic     [31:0] second_operand_reductions_32b;

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

//////////////////////////////////////////////////////////////////////////////
// Reductions Min-Max
//////////////////////////////////////////////////////////////////////////////

    if (V_REDMINMAX_ON) begin : v_redminmax_gen_on

        logic [(VLENB)  -1:0][ 7:0] result_redmin_8b   [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redmin_16b  [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redmin_32b  [TREE_LEVELS_32b:0];
        logic [(VLENB)  -1:0][ 7:0] result_redminu_8b  [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redminu_16b [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redminu_32b [TREE_LEVELS_32b:0];
        logic [(VLENB)  -1:0][ 7:0] result_redmax_8b   [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redmax_16b  [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redmax_32b  [TREE_LEVELS_32b:0];
        logic [(VLENB)  -1:0][ 7:0] result_redmaxu_8b  [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redmaxu_16b [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redmaxu_32b [TREE_LEVELS_32b:0];

        // *********************************
        //  8 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew8[cycle_count_r][0]) && i < vl) begin
                        result_redmin_8b [0][i] = ($signed(first_operand_8b[0]) > $signed(second_operand_reductions_8b))
                                                ? second_operand_reductions_8b
                                                : first_operand_8b [0];
                        result_redminu_8b[0][i] = (first_operand_8b[0] > second_operand_reductions_8b)
                                                ? second_operand_reductions_8b
                                                : first_operand_8b [0];
                        result_redmax_8b [0][i] = ($signed(first_operand_8b[0]) > $signed(second_operand_reductions_8b))
                                                ? first_operand_8b [0]
                                                : second_operand_reductions_8b;
                        result_redmaxu_8b[0][i] = (first_operand_8b[0] > second_operand_reductions_8b)
                                                ? first_operand_8b [0]
                                                : second_operand_reductions_8b;
                    end
                    else begin
                        result_redmin_8b [0][i] = second_operand_reductions_8b;
                        result_redminu_8b[0][i] = second_operand_reductions_8b;
                        result_redmax_8b [0][i] = second_operand_reductions_8b;
                        result_redmaxu_8b[0][i] = second_operand_reductions_8b;
                    end
                end
                else begin
                    if ((vm || mask_sew8[cycle_count_r][i]) && i < vl) begin
                        result_redmin_8b [0][i] = first_operand_8b[i];
                        result_redminu_8b[0][i] = first_operand_8b[i];
                        result_redmax_8b [0][i] = first_operand_8b[i];
                        result_redmaxu_8b[0][i] = first_operand_8b[i];
                    end
                    else begin
                        result_redmin_8b [0][i] = 8'h7F;
                        result_redminu_8b[0][i] = '1;
                        result_redmax_8b [0][i] = 8'h80;
                        result_redmaxu_8b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_8b; i++) begin
                for (int j = 0; j < VLENB/(2**(i+1)); j++) begin
                    result_redmin_8b [i+1][j] = ($signed(result_redmin_8b[i][2*j]) > $signed(result_redmin_8b[i][2*j+1]))
                                                ? result_redmin_8b[i][2*j+1]
                                                : result_redmin_8b[i][2*j];
                    result_redminu_8b[i+1][j] = (result_redminu_8b [i][2*j] > result_redminu_8b[i][2*j+1])
                                                ? result_redminu_8b[i][2*j+1]
                                                : result_redminu_8b[i][2*j];
                    result_redmax_8b [i+1][j] = ($signed(result_redmax_8b[i][2*j]) > $signed(result_redmax_8b[i][2*j+1]))
                                                ? result_redmax_8b[i][2*j]
                                                : result_redmax_8b[i][2*j+1];
                    result_redmaxu_8b[i+1][j] = (result_redmaxu_8b[i][2*j] > result_redmaxu_8b[i][2*j+1])
                                                ? result_redmaxu_8b[i][2*j]
                                                : result_redmaxu_8b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  16 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB/2; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew16[cycle_count_r][0]) && i < vl) begin
                        result_redmin_16b [0][i] = ($signed(first_operand_16b[0]) > $signed(second_operand_reductions_16b))
                                                ? second_operand_reductions_16b
                                                : first_operand_16b [0];
                        result_redminu_16b[0][i] = (first_operand_16b[0] > second_operand_reductions_16b)
                                                ? second_operand_reductions_16b
                                                : first_operand_16b [0];
                        result_redmax_16b [0][i] = ($signed(first_operand_16b[0]) > $signed(second_operand_reductions_16b))
                                                ? first_operand_16b [0]
                                                : second_operand_reductions_16b;
                        result_redmaxu_16b[0][i] = (first_operand_16b[0] > second_operand_reductions_16b)
                                                ? first_operand_16b [0]
                                                : second_operand_reductions_16b;
                    end
                    else begin
                        result_redmin_16b [0][i] = second_operand_reductions_16b;
                        result_redminu_16b[0][i] = second_operand_reductions_16b;
                        result_redmax_16b [0][i] = second_operand_reductions_16b;
                        result_redmaxu_16b[0][i] = second_operand_reductions_16b;
                    end
                end
                else begin
                    if ((vm || mask_sew16[cycle_count_r][i]) && i < vl) begin
                        result_redmin_16b [0][i] = first_operand_16b[i];
                        result_redminu_16b[0][i] = first_operand_16b[i];
                        result_redmax_16b [0][i] = first_operand_16b[i];
                        result_redmaxu_16b[0][i] = first_operand_16b[i];
                    end
                    else begin
                        result_redmin_16b [0][i] = 16'h7FFF;
                        result_redminu_16b[0][i] = '1;
                        result_redmax_16b [0][i] = 16'h8000;
                        result_redmaxu_16b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_16b; i++) begin
                for (int j = 0; j < (VLENB/2)/(2**(i+1)); j++) begin
                    result_redmin_16b [i+1][j] = ($signed(result_redmin_16b[i][2*j]) > $signed(result_redmin_16b[i][2*j+1]))
                                                ? result_redmin_16b[i][2*j+1]
                                                : result_redmin_16b[i][2*j];
                    result_redminu_16b[i+1][j] = (result_redminu_16b [i][2*j] > result_redminu_16b[i][2*j+1])
                                                ? result_redminu_16b[i][2*j+1]
                                                : result_redminu_16b[i][2*j];
                    result_redmax_16b [i+1][j] = ($signed(result_redmax_16b[i][2*j]) > $signed(result_redmax_16b[i][2*j+1]))
                                                ? result_redmax_16b[i][2*j]
                                                : result_redmax_16b[i][2*j+1];
                    result_redmaxu_16b[i+1][j] = (result_redmaxu_16b[i][2*j] > result_redmaxu_16b[i][2*j+1])
                                                ? result_redmaxu_16b[i][2*j]
                                                : result_redmaxu_16b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  32 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB/4; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew32[cycle_count_r][0]) && i < vl) begin
                        result_redmin_32b [0][i] = ($signed(first_operand_32b[0]) > $signed(second_operand_reductions_32b))
                                                ? second_operand_reductions_32b
                                                : first_operand_32b [0];
                        result_redminu_32b[0][i] = (first_operand_32b[0] > second_operand_reductions_32b)
                                                ? second_operand_reductions_32b
                                                : first_operand_32b [0];
                        result_redmax_32b [0][i] = ($signed(first_operand_32b[0]) > $signed(second_operand_reductions_32b))
                                                ? first_operand_32b [0]
                                                : second_operand_reductions_32b;
                        result_redmaxu_32b[0][i] = (first_operand_32b[0] > second_operand_reductions_32b)
                                                ? first_operand_32b [0]
                                                : second_operand_reductions_32b;
                    end
                    else begin
                        result_redmin_32b [0][i] = second_operand_reductions_32b;
                        result_redminu_32b[0][i] = second_operand_reductions_32b;
                        result_redmax_32b [0][i] = second_operand_reductions_32b;
                        result_redmaxu_32b[0][i] = second_operand_reductions_32b;
                    end
                end
                else begin
                    if ((vm || mask_sew32[cycle_count_r][i]) && i < vl) begin
                        result_redmin_32b [0][i] = first_operand_32b[i];
                        result_redminu_32b[0][i] = first_operand_32b[i];
                        result_redmax_32b [0][i] = first_operand_32b[i];
                        result_redmaxu_32b[0][i] = first_operand_32b[i];
                    end
                    else begin
                        result_redmin_32b [0][i] = 32'h7FFFFFFF;
                        result_redminu_32b[0][i] = '1;
                        result_redmax_32b [0][i] = 32'h80000000;
                        result_redmaxu_32b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_32b; i++) begin
                for (int j = 0; j < (VLENB/4)/(2**(i+1)); j++) begin
                    result_redmin_32b [i+1][j] = ($signed(result_redmin_32b[i][2*j]) > $signed(result_redmin_32b[i][2*j+1]))
                                                ? result_redmin_32b[i][2*j+1]
                                                : result_redmin_32b[i][2*j];
                    result_redminu_32b[i+1][j] = (result_redminu_32b [i][2*j] > result_redminu_32b[i][2*j+1])
                                                ? result_redminu_32b[i][2*j+1]
                                                : result_redminu_32b[i][2*j];
                    result_redmax_32b [i+1][j] = ($signed(result_redmax_32b[i][2*j]) > $signed(result_redmax_32b[i][2*j+1]))
                                                ? result_redmax_32b[i][2*j]
                                                : result_redmax_32b[i][2*j+1];
                    result_redmaxu_32b[i+1][j] = (result_redmaxu_32b[i][2*j] > result_redmaxu_32b[i][2*j+1])
                                                ? result_redmaxu_32b[i][2*j]
                                                : result_redmaxu_32b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  Sew Demux
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_redmin  = {'0, result_redmin_8b  [TREE_LEVELS_8b][0]};
                    result_redminu = {'0, result_redminu_8b [TREE_LEVELS_8b][0]};
                    result_redmax  = {'0, result_redmax_8b  [TREE_LEVELS_8b][0]};
                    result_redmaxu = {'0, result_redmaxu_8b [TREE_LEVELS_8b][0]};
                end
                EW16: begin
                    result_redmin  = {'0, result_redmin_16b  [TREE_LEVELS_16b][0]};
                    result_redminu = {'0, result_redminu_16b [TREE_LEVELS_16b][0]};
                    result_redmax  = {'0, result_redmax_16b  [TREE_LEVELS_16b][0]};
                    result_redmaxu = {'0, result_redmaxu_16b [TREE_LEVELS_16b][0]};
                end
                default: begin
                    result_redmin  = {'0, result_redmin_32b  [TREE_LEVELS_32b][0]};
                    result_redminu = {'0, result_redminu_32b [TREE_LEVELS_32b][0]};
                    result_redmax  = {'0, result_redmax_32b  [TREE_LEVELS_32b][0]};
                    result_redmaxu = {'0, result_redmaxu_32b [TREE_LEVELS_32b][0]};
                end
            endcase
        end
    end
    else begin : v_redminmax_gen_off
        always_comb begin
            result_redmin  = '0;
            result_redminu = '0;
            result_redmax  = '0;
            result_redmaxu = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Reductions Logic
//////////////////////////////////////////////////////////////////////////////

    if (V_REDLOGIC_ON) begin : v_redlogic_gen_on

        logic [(VLENB)  -1:0][ 7:0] result_redand_8b  [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redand_16b [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redand_32b [TREE_LEVELS_32b:0];
        logic [(VLENB)  -1:0][ 7:0] result_redor_8b   [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redor_16b  [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redor_32b  [TREE_LEVELS_32b:0];
        logic [(VLENB)  -1:0][ 7:0] result_redxor_8b  [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redxor_16b [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redxor_32b [TREE_LEVELS_32b:0];

        // *********************************
        //  8 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew8[cycle_count_r][0]) && i < vl) begin
                        result_redand_8b[0][i] = first_operand_8b[0] & second_operand_reductions_8b;
                        result_redor_8b [0][i] = first_operand_8b[0] | second_operand_reductions_8b;
                        result_redxor_8b[0][i] = first_operand_8b[0] ^ second_operand_reductions_8b;
                    end
                    else begin
                        result_redand_8b[0][i] = second_operand_reductions_8b;
                        result_redor_8b [0][i] = second_operand_reductions_8b;
                        result_redxor_8b[0][i] = second_operand_reductions_8b;
                    end
                end
                else begin
                    if ((vm || mask_sew8[cycle_count_r][i]) && i < vl) begin
                        result_redand_8b[0][i] = first_operand_8b[i];
                        result_redor_8b [0][i] = first_operand_8b[i];
                        result_redxor_8b[0][i] = first_operand_8b[i];
                    end
                    else begin
                        result_redand_8b[0][i] = '1;
                        result_redor_8b [0][i] = '0;
                        result_redxor_8b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_8b; i++) begin
                for (int j = 0; j < VLENB/(2**(i+1)); j++) begin
                    result_redand_8b[i+1][j] = result_redand_8b[i][2*j] & result_redand_8b[i][2*j+1];
                    result_redor_8b [i+1][j] = result_redor_8b [i][2*j] | result_redor_8b[i][2*j+1];
                    result_redxor_8b[i+1][j] = result_redxor_8b[i][2*j] ^ result_redxor_8b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  16 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB/2; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew16[cycle_count_r][0]) && i < vl) begin
                        result_redand_16b[0][i] = first_operand_16b[0] & second_operand_reductions_16b;
                        result_redor_16b [0][i] = first_operand_16b[0] | second_operand_reductions_16b;
                        result_redxor_16b[0][i] = first_operand_16b[0] ^ second_operand_reductions_16b;
                    end
                    else begin
                        result_redand_16b[0][i] = second_operand_reductions_16b;
                        result_redor_16b [0][i] = second_operand_reductions_16b;
                        result_redxor_16b[0][i] = second_operand_reductions_16b;
                    end
                end
                else begin
                    if ((vm || mask_sew16[cycle_count_r][i]) && i < vl) begin
                        result_redand_16b[0][i] = first_operand_16b[i];
                        result_redor_16b [0][i] = first_operand_16b[i];
                        result_redxor_16b[0][i] = first_operand_16b[i];
                    end
                    else begin
                        result_redand_16b[0][i] = '1;
                        result_redor_16b [0][i] = '0;
                        result_redxor_16b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_16b; i++) begin
                for (int j = 0; j < (VLENB/2)/(2**(i+1)); j++) begin
                    result_redand_16b[i+1][j] = result_redand_16b[i][2*j] & result_redand_16b[i][2*j+1];
                    result_redor_16b [i+1][j] = result_redor_16b [i][2*j] | result_redor_16b [i][2*j+1];
                    result_redxor_16b[i+1][j] = result_redxor_16b[i][2*j] ^ result_redxor_16b[i][2*j+1];
                end
            end
        end


        // *********************************
        //  32 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB/4; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew32[cycle_count_r][0]) && i < vl) begin
                        result_redand_32b[0][i] = first_operand_32b[0] & second_operand_reductions_32b;
                        result_redor_32b [0][i] = first_operand_32b[0] | second_operand_reductions_32b;
                        result_redxor_32b[0][i] = first_operand_32b[0] ^ second_operand_reductions_32b;
                    end
                    else begin
                        result_redand_32b[0][i] = second_operand_reductions_32b;
                        result_redor_32b [0][i] = second_operand_reductions_32b;
                        result_redxor_32b[0][i] = second_operand_reductions_32b;
                    end
                end
                else begin
                    if ((vm || mask_sew32[cycle_count_r][i]) && i < vl) begin
                        result_redand_32b[0][i] = first_operand_32b[i];
                        result_redor_32b [0][i] = first_operand_32b[i];
                        result_redxor_32b[0][i] = first_operand_32b[i];
                    end
                    else begin
                        result_redand_32b[0][i] = '1;
                        result_redor_32b [0][i] = '0;
                        result_redxor_32b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_32b; i++) begin
                for (int j = 0; j < (VLENB/4)/(2**(i+1)); j++) begin
                    result_redand_32b[i+1][j] = result_redand_32b[i][2*j] & result_redand_32b[i][2*j+1];
                    result_redor_32b [i+1][j] = result_redor_32b [i][2*j] | result_redor_32b [i][2*j+1];
                    result_redxor_32b[i+1][j] = result_redxor_32b[i][2*j] ^ result_redxor_32b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  Sew Demux
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_redand  = {'0, result_redand_8b [TREE_LEVELS_8b][0]};
                    result_redor   = {'0, result_redor_8b  [TREE_LEVELS_8b][0]};
                    result_redxor  = {'0, result_redxor_8b [TREE_LEVELS_8b][0]};
                end
                EW16: begin
                    result_redand  = {'0, result_redand_16b [TREE_LEVELS_16b][0]};
                    result_redor   = {'0, result_redor_16b  [TREE_LEVELS_16b][0]};
                    result_redxor  = {'0, result_redxor_16b [TREE_LEVELS_16b][0]};
                end
                default: begin
                    result_redand  = {'0, result_redand_32b [TREE_LEVELS_32b][0]};
                    result_redor   = {'0, result_redor_32b  [TREE_LEVELS_32b][0]};
                    result_redxor  = {'0, result_redxor_32b [TREE_LEVELS_32b][0]};
                end
            endcase
        end
    end
    else begin : v_redlogic_gen_off
        always_comb begin
            result_redand  = '0;
            result_redor   = '0;
            result_redxor  = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Reductions Sum
//////////////////////////////////////////////////////////////////////////////

    if (V_REDSUM_ON) begin : v_redsum_gen_on

        logic [(VLENB)  -1:0][ 7:0] result_redsum_8b  [TREE_LEVELS_8b :0];
        logic [(VLENB/2)-1:0][15:0] result_redsum_16b [TREE_LEVELS_16b:0];
        logic [(VLENB/4)-1:0][31:0] result_redsum_32b [TREE_LEVELS_32b:0];

        // *********************************
        //  8 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew8[cycle_count_r][0]) && i < vl) begin
                        result_redsum_8b[0][i] = first_operand_8b[0] + second_operand_reductions_8b;
                    end
                    else begin
                        result_redsum_8b[0][i] = second_operand_reductions_8b;
                    end
                end
                else begin
                    if ((vm || mask_sew8[cycle_count_r][i]) && i < vl) begin
                        result_redsum_8b[0][i] = first_operand_8b[i];
                    end
                    else begin
                        result_redsum_8b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_8b; i++) begin
                for (int j = 0; j < VLENB/(2**(i+1)); j++) begin
                    result_redsum_8b[i+1][j] = result_redsum_8b[i][2*j] + result_redsum_8b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  16 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB/2; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew16[cycle_count_r][0]) && i < vl) begin
                        result_redsum_16b[0][i] = first_operand_16b[0] + second_operand_reductions_16b;
                    end
                    else begin
                        result_redsum_16b[0][i] = second_operand_reductions_16b;
                    end
                end
                else begin
                    if ((vm || mask_sew16[cycle_count_r][i]) && i < vl) begin
                        result_redsum_16b[0][i] = first_operand_16b[i];
                    end
                    else begin
                        result_redsum_16b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_16b; i++) begin
                for (int j = 0; j < (VLENB/2)/(2**(i+1)); j++) begin
                    result_redsum_16b[i+1][j] = result_redsum_16b[i][2*j] + result_redsum_16b[i][2*j+1];
                end
            end
        end

        always_comb begin

        end

        // *********************************
        //  32 Bits
        // *********************************
        always_comb begin
            // First Level
            for (int i = 0; i < VLENB/4; i++) begin
                if (i == 0) begin
                    if ((vm || mask_sew32[cycle_count_r][0]) && i < vl) begin
                        result_redsum_32b[0][i] = first_operand_32b[0] + second_operand_reductions_32b;
                    end
                    else begin
                        result_redsum_32b[0][i] = second_operand_reductions_32b;
                    end
                end
                else begin
                    if ((vm || mask_sew32[cycle_count_r][i]) && i < vl) begin
                        result_redsum_32b[0][i] = first_operand_32b[i];
                    end
                    else begin
                        result_redsum_32b[0][i] = '0;
                    end
                end
            end

            // Other Levels
            for (int i = 0; i < TREE_LEVELS_32b; i++) begin
                for (int j = 0; j < (VLENB/4)/(2**(i+1)); j++) begin
                    result_redsum_32b[i+1][j] = result_redsum_32b[i][2*j] + result_redsum_32b[i][2*j+1];
                end
            end
        end

        // *********************************
        //  Sew Demux
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_redsum  = {'0, result_redsum_8b [TREE_LEVELS_8b][0]};
                end
                EW16: begin
                    result_redsum  = {'0, result_redsum_16b[TREE_LEVELS_16b][0]};
                end
                default: begin
                    result_redsum  = {'0, result_redsum_32b[TREE_LEVELS_32b][0]};
                end
            endcase
        end
    end
    else begin : v_redsum_gen_off
        assign result_redsum = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Adder
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] subtraend, subtraend_neg;
    logic [VLEN-1:0] subtraend_8b, subtraend_16b, subtraend_32b;
    logic [VLEN-1:0] summand_1, summand_2, summand_2_int;
    logic      [8:0] result_add_bytes [VLENB-1:0];
    /* verilator lint_off UNOPTFLAT */
    logic            adder_carry [VLENB-1:0];
    /* verilator lint_on UNOPTFLAT */
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
            default: summand_1 = first_operand;
        endcase
    end

    assign summand_2_int =  (vector_operation_i inside {VMACC, VMADD})
                            ? result_mult_r
                            : second_operand;

    always_comb begin
        if (vector_operation_i inside {VSUB, VRSUB, VNMSAC, VNMSUB}) begin
            unique case (vsew)
                EW8:    summand_2 = subtraend_8b;
                EW16:   summand_2 = subtraend_16b;
                default:summand_2 = subtraend_32b;
            endcase
        end
        else begin
            summand_2 = summand_2_int;
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            case (vsew)
                EW16:    adder_carry[i] = (i%2 == 0) ? 1'b0 : result_add_bytes[i-1][8];
                EW32:    adder_carry[i] = (i%4 == 0) ? 1'b0 : result_add_bytes[i-1][8];
                default: adder_carry[i] = 1'b0;
            endcase
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            result_add_bytes[i] = {1'b0, summand_1[(8*i)+:8]} + {1'b0, summand_2[(8*i)+:8]} + adder_carry[i];
        end
    end

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            result_add[(8*i)+:8] = result_add_bytes[i][7:0];
        end
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

    logic mask_instruction;

    assign mask_instruction = (vector_operation_i inside {VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT});

    logic [ VLENB   -1:0] equal_8b,  greater_than_8b,  greater_than_signed_8b,  result_comparison_8b;
    logic [(VLENB/2)-1:0] equal_16b, greater_than_16b, greater_than_signed_16b, result_comparison_16b;
    logic [(VLENB/4)-1:0] equal_32b, greater_than_32b, greater_than_signed_32b, result_comparison_32b;

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

    always @(posedge clk) begin
        if (mask_instruction) begin
            unique case (vsew)
                EW8:
                    for (int i = 0; i < 8; i++)
                        if (i == cycle_count_r)
                            result_mask_o[(VLENB*i)+:VLENB]       <= result_comparison_8b  & ({VLENB  {vm}} | mask_sew8 [cycle_count_r]);

                EW16:
                    for (int i = 0; i < 8; i++)
                        if (i == cycle_count_r)
                            result_mask_o[((VLENB/2)*i)+:VLENB/2] <= result_comparison_16b & ({VLENB/2{vm}} | mask_sew16[cycle_count_r]);

                default:
                    for (int i = 0; i < 8; i++)
                        if (i == cycle_count_r)
                            result_mask_o[((VLENB/4)*i)+:VLENB/4] <= result_comparison_32b & ({VLENB/4{vm}} | mask_sew32[cycle_count_r]);
            endcase
        end
        else begin
            result_mask_o <= '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Min/Max
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_minu, result_min, result_maxu, result_max;

    if (V_MINMAX_ON) begin : v_minmax_gen_on
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
    end
    else begin : v_minmax_gen_off
        always_comb begin
            result_minu = '0;
            result_min  = '0;
            result_maxu = '0;
            result_max  = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
//  Merge
//////////////////////////////////////////////////////////////////////////////

    logic [(VLEN-1):0] result_merge;

    if(V_MERGE_ON) begin : v_merge_gen_on
        always_comb begin
            unique case (vsew)
                EW8: begin
                    for (int i = 0; i < VLENB; i++) begin
                        result_merge[(8*i)+:8]    = (mask_sew8[cycle_count_r][i])  ? second_operand_8b[i]  : first_operand_8b[i];
                    end 
                end
                EW16: begin
                    for (int i = 0; i < (VLENB/2); i++) begin
                        result_merge[(16*i)+:16]  = (mask_sew16[cycle_count_r][i]) ? second_operand_16b[i] : first_operand_16b[i];
                    end 
                end
                default: begin
                    for (int i = 0; i < (VLENB/4); i++) begin
                        result_merge[(32*i)+:32]  = (mask_sew32[cycle_count_r][i]) ? second_operand_32b[i] : first_operand_32b[i];
                    end 
                end
            endcase
        end
    end
    else begin : v_merge_gen_off
        assign result_merge = '0;
    end
    
//////////////////////////////////////////////////////////////////////////////
// Multiplication_common
//////////////////////////////////////////////////////////////////////////////

    logic [ VLENB-1   :0][15:0] mult_result_8b;

    logic [(VLENB/2)-1:0][15:0] mult_op_a_16b;
    logic [(VLENB/2)-1:0][15:0] mult_op_b_16b;
    logic [(VLENB/2)-1:0][31:0] mult_result_16b;

    logic [(VLENB/4)-1:0][31:0] mult_op_a_32b;
    logic [(VLENB/4)-1:0][31:0] mult_op_b_32b;
    logic [(VLENB/4)-1:0][31:0] mult_result_32b;

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

    generate
        for (genvar i_mul8b = 0; i_mul8b < VLENB; i_mul8b++) begin : MUL8B_LOOP
            if (i_mul8b < VLENB/4) begin : g8b_mul_using_32b_multplier_blk
                assign mult_result_8b[i_mul8b] = {mult_result_32b[i_mul8b][15:0]};
            end
            else if (i_mul8b < VLENB/2) begin : g8b_mul_using_16b_multplier_blk
                assign mult_result_8b[i_mul8b] = {mult_result_16b[i_mul8b][15:0]};
            end
            else begin : g8b_multplier_blk
                mulNbits #(
                    .N(8)
                ) mul8b (
                    .first_operand_i (first_operand_8b [i_mul8b]),
                    .second_operand_i(second_operand_8b[i_mul8b]),
                    .signed_mode_i   (mult_signed_mode),
                    .result_o        (mult_result_8b[i_mul8b])
                );
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication 16 bits
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        for (int i = 0; i < VLENB/2; i++) begin
            if (i < VLENB/4) begin : g16b_mul_operands_to_32b_multiplier_blk
                mult_op_a_16b[i] = first_operand_16b [i];
                mult_op_b_16b[i] = second_operand_16b[i];
            end
            else begin  : g16b_mul_operands_blk
                if (vsew == EW8) begin
                    mult_op_a_16b[i] = {{8{first_operand_8b [i][7] & mult_signed_mode[0]}}, first_operand_8b [i]};
                    mult_op_b_16b[i] = {{8{second_operand_8b[i][7] & mult_signed_mode[1]}}, second_operand_8b[i]};
                end
                else begin
                    mult_op_a_16b[i] = first_operand_16b [i];
                    mult_op_b_16b[i] = second_operand_16b[i];
                end
            end
        end
    end

    generate
        for (genvar i_mul16b = 0; i_mul16b < VLENB/2; i_mul16b++) begin : MUL16B_LOOP
            if (i_mul16b < VLENB/4) begin : g16b_mul_using_32b_multplier_blk
                assign mult_result_16b[i_mul16b] = {mult_result_32b[i_mul16b][31:0]};
            end
            else begin : g16b_multplier_blk
                mulNbits #(
                    .N(16)
                ) mul16b (
                    .first_operand_i (mult_op_a_16b[i_mul16b]),
                    .second_operand_i(mult_op_b_16b[i_mul16b]),
                    .signed_mode_i   (mult_signed_mode),
                    .result_o        (mult_result_16b[i_mul16b])
                );
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication 32 bits
//////////////////////////////////////////////////////////////////////////////

    logic                 mult_enable, mult_low, ended_acc;
    logic [(VLENB/4)-1:0] hold_mult_int;

    always_comb begin
        for (int i = 0; i < VLENB/4; i++) begin
            unique case (vsew)
                EW8: begin
                    mult_op_a_32b[i] = {{24{first_operand_8b [i][7] & mult_signed_mode[0]}}, first_operand_8b [i]};
                    mult_op_b_32b[i] = {{24{second_operand_8b[i][7] & mult_signed_mode[1]}}, second_operand_8b[i]};
                end
                EW16: begin
                    mult_op_a_32b[i] = {{16{mult_op_a_16b[i][15] & mult_signed_mode[0]}}, mult_op_a_16b[i]};
                    mult_op_b_32b[i] = {{16{mult_op_b_16b[i][15] & mult_signed_mode[1]}}, mult_op_b_16b[i]};
                end
                default: begin
                    mult_op_a_32b[i] = first_operand_32b [i];
                    mult_op_b_32b[i] = second_operand_32b[i];
                end
            endcase
        end
    end

    assign ended_acc = (vector_operation_i inside {VMACC, VNMSAC, VMADD, VNMSUB})
                        &&  (
                                (vlmul == LMUL_1_2  && cycle_count > 1)
                            ||  (vlmul == LMUL_1    && cycle_count > 1)
                            ||  (vlmul == LMUL_2    && cycle_count > 2)
                            ||  (vlmul == LMUL_4    && cycle_count > 4)
                            ||  (vlmul == LMUL_8    && cycle_count > 8)
                            );

    assign mult_enable = (
                            (vector_operation_i inside {VMUL, VMULH, VMULHSU, VMULHU, VMACC, VNMSAC, VMADD, VNMSUB})
                        &&  (current_state == V_EXEC)
                        &&  (vsew == EW32)
                        &&  (!ended_acc)
                        &&  (!hold_accumulation_r)
                        );
    assign mult_low    = (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB});
    assign hold_mult   = |hold_mult_int;

    generate
        for (genvar i_mul32b = 0; i_mul32b < VLENB/4; i_mul32b++) begin : MUL32B_LOOP
            mul mul32b (
                .clk             (clk),
                .reset_n         (reset_n),
                .stall           (1'b0),
                .first_operand_i (mult_op_a_32b[i_mul32b]),
                .second_operand_i(mult_op_b_32b[i_mul32b]),
                .signed_mode_i   (mult_signed_mode),
                .enable_i        (mult_enable),
                .mul_low_i       (mult_low),
                .single_cycle_i  (vsew inside {EW8, EW16}),
                .hold_o          (hold_mult_int[i_mul32b]),
                .result_o        (mult_result_32b[i_mul32b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication Demux
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        result_mult = '0;
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
            result_mult_r <= result_mult[VLEN-1:0];
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

    logic  div_enable_8b;
    logic  div_enable_16b;
    logic  div_enable_32b;

    if (V_DIV_ON) begin : v_div_common_gen_on
        assign div_enable     = (vector_operation_i inside {VDIV, VDIVU, VREM, VREMU} && current_state == V_EXEC);
        assign div_enable_8b  = (div_enable && vsew == EW8);
        assign div_enable_16b = (div_enable && vsew == EW16);
        assign div_enable_32b = (div_enable && vsew == EW32);
        assign div_signed     = (vector_operation_i inside {VDIV, VREM});
        assign hold_div       = (|hold_div_8b) | (|hold_div_16b) | (|hold_div_32b);
    end
    else begin : v_div_common_gen_off
        assign div_enable     = 1'b0;
        assign div_enable_8b  = 1'b0;
        assign div_enable_16b = 1'b0;
        assign div_enable_32b = 1'b0;
        assign div_signed     = 1'b0;
        assign hold_div       = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// Division 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic [VLENB-1:0][7:0] div_result_8b;
    logic [VLENB-1:0][7:0] rem_result_8b;

    generate
        for (genvar i_div8b = 0; i_div8b < VLENB; i_div8b++) begin : DIV8B_LOOP
            if (V_DIV_ON) begin : v_div_8b_gen_on
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
            else begin : v_div_8b_gen_off
                assign div_result_8b[i_div8b] = '0;
                assign rem_result_8b[i_div8b] = '0;
                assign hold_div_8b  [i_div8b] = '0;
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Division 16 bits
//////////////////////////////////////////////////////////////////////////////

    logic [(VLENB/2)-1:0][15:0] div_result_16b;
    logic [(VLENB/2)-1:0][15:0] rem_result_16b;

    generate
        for (genvar i_div16b = 0; i_div16b < VLENB/2; i_div16b++) begin : DIV16B_LOOP
            if (V_DIV_ON) begin : v_div_16b_gen_on
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
            else begin : v_div_16b_gen_off
                assign div_result_16b[i_div16b] = '0;
                assign rem_result_16b[i_div16b] = '0;
                assign hold_div_16b  [i_div16b] = '0;
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Division 32 bits
//////////////////////////////////////////////////////////////////////////////

    logic [(VLENB/4)-1:0][31:0] div_result_32b;
    logic [(VLENB/4)-1:0][31:0] rem_result_32b;


    generate
        for (genvar i_div32b = 0; i_div32b < VLENB/4; i_div32b++) begin : DIV32B_LOOP
            if (V_DIV_ON) begin : v_div_32b_gen_on
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
            else begin : v_div_32b_gen_off
                assign div_result_32b[i_div32b] = '0;
                assign rem_result_32b[i_div32b] = '0;
                assign hold_div_32b  [i_div32b] = '0;
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Division Demux
//////////////////////////////////////////////////////////////////////////////

    if (V_DIV_ON) begin : v_div_mux_gen_on
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
    end else begin : v_div_mux_gen_off
        assign result_div = '0;
        assign result_rem = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Hold generation
//////////////////////////////////////////////////////////////////////////////

    assign hold   = hold_mult | hold_div;

    assign hold_o = hold | hold_widening_o | hold_accumulation_o;

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
            VMIN:            result_o <= result_min;
            VMINU:           result_o <= result_minu;
            VMAX:            result_o <= result_max;
            VMAXU:           result_o <= result_maxu;
            VMUL, VMULH,
            VMULHU, VMULHSU: result_o <= result_mult[VLEN-1:0];
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
            VMVR:            result_o <= first_operand;
            VMERGE:          result_o <= result_merge;
            default:         result_o <= result_add;
        endcase
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
