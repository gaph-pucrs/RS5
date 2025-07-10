/*!\file vectorReductions.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 */

`include "../RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorReductions
    import RS5_pkg::*;
#(
    parameter int VLEN           = 64,
    parameter int VLENB          = 8,
    parameter int V_REDSUM_ON    = 1'b1,
    parameter int V_REDLOGIC_ON  = 1'b1,
    parameter int V_REDMINMAX_ON = 1'b1,
    parameter bit MULTI_CYCLE    = 1'b0
) (
    input  logic                       clk,
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic                       reset_n,
    input  logic                       enable_i,
    /* verilator lint_on UNUSEDSIGNAL  */
    input  iTypeVector_e               vector_operation_i,

    input  logic [VLEN-1:0]            first_operand,
    input  logic [31:0]                second_operand,

    input  vew_e                       vsew,
    input  logic [3:0]                 cycle_count_r,
    input  logic[$bits(VLEN)-1:0]      vl,
    input  logic                       vm,

    input  logic [7:0][ VLENB   -1:0]  mask_sew8,
    input  logic [7:0][(VLENB/2)-1:0]  mask_sew16,
    input  logic [7:0][(VLENB/4)-1:0]  mask_sew32,


    output logic                       hold_o,
    output logic [31:0]                result_o
);

    logic [31:0] result_redsum;
    logic [31:0] result_redand;
    logic [31:0] result_redor;
    logic [31:0] result_redxor;
    logic [31:0] result_redmin;
    logic [31:0] result_redminu;
    logic [31:0] result_redmax;
    logic [31:0] result_redmaxu;

    // *********************************
    //  HOLD CONTROL
    // *********************************
    localparam TREE_LEVELS_8b  = $clog2(VLENB);
    localparam TREE_LEVELS_16b = $clog2(VLENB/2);
    localparam TREE_LEVELS_32b = $clog2(VLENB/4);

    if (MULTI_CYCLE) begin  : multi_cycle_reduction_on
        logic [$clog2(TREE_LEVELS_8b):0] cycle_counter;
        logic                            last_cycle;

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                cycle_counter <= '0;
            else if (enable_i && !last_cycle)
                cycle_counter <= cycle_counter + 1;
            else
                cycle_counter <= '0;
        end

        always_comb begin
            unique case (vsew)
                EW8:    last_cycle = (cycle_counter == TREE_LEVELS_8b+1);
                EW16:   last_cycle = (cycle_counter == TREE_LEVELS_16b+1);
                default:last_cycle = (cycle_counter == TREE_LEVELS_32b+1);
            endcase
        end

        assign hold_o = enable_i && !last_cycle;
    end
    else begin : multi_cycle_reduction_off
        assign hold_o = 1'b0;
    end

    // *********************************
    // Operands Control
    // *********************************
    logic [(VLENB)  -1:0][ 7:0] first_operand_8b;
    logic [(VLENB/2)-1:0][15:0] first_operand_16b;
    logic [(VLENB/4)-1:0][31:0] first_operand_32b;

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            first_operand_8b [i] = first_operand[(8*i)+:8];
        end
        for (int i = 0; i < VLENB/2; i++) begin
            first_operand_16b[i] = first_operand[(16*i)+:16];
        end
        for (int i = 0; i < VLENB/4; i++) begin
            first_operand_32b[i] = first_operand[(32*i)+:32];
        end
    end

    // *********************************
    //  SUM
    // *********************************
    if (V_REDSUM_ON) begin : v_redsum_gen_on
        logic [ 7:0] result_redsum_8b;
        logic [15:0] result_redsum_16b;
        logic [31:0] result_redsum_32b;

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_SUM),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_sum_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redsum_8b)
        );

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_SUM),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_sum_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redsum_16b)
        );

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_SUM),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_sum_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redsum_32b)
        );

        // *********************************
        //  Sew Demux
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_redsum  = {'0, result_redsum_8b};
                end
                EW16: begin
                    result_redsum  = {'0, result_redsum_16b};
                end
                default: begin
                    result_redsum  = result_redsum_32b;
                end
            endcase
        end
    end
    else begin : v_redsum_gen_off
        assign result_redsum = '0;
    end

    // *********************************
    //  LOGIC
    // *********************************
    if (V_REDLOGIC_ON) begin : v_redlogic_gen_on
        /////////////////////////////////////////////////
        // 8 Bits
        /////////////////////////////////////////////////
        logic [ 7:0] result_redand_8b;
        logic [ 7:0] result_redor_8b;
        logic [ 7:0] result_redxor_8b;

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_AND),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_and_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redand_8b)
        );

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_OR),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_or_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redor_8b)
        );

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_XOR),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_xor_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redxor_8b)
        );

        /////////////////////////////////////////////////
        // 16 Bits
        /////////////////////////////////////////////////
        logic [15:0] result_redand_16b;
        logic [15:0] result_redor_16b;
        logic [15:0] result_redxor_16b;

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_AND),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_and_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redand_16b)
        );

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_OR),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_or_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redor_16b)
        );

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_XOR),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_xor_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redxor_16b)
        );

        /////////////////////////////////////////////////
        // 32 Bits
        /////////////////////////////////////////////////
        logic [31:0] result_redand_32b;
        logic [31:0] result_redor_32b;
        logic [31:0] result_redxor_32b;

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_AND),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_and_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redand_32b)
        );

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_OR),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_or_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redor_32b)
        );

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_XOR),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_xor_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redxor_32b)
        );

        // *********************************
        //  Sew Demux
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_redand  = {'0, result_redand_8b};
                    result_redor   = {'0, result_redor_8b };
                    result_redxor  = {'0, result_redxor_8b};
                end
                EW16: begin
                    result_redand  = {'0, result_redand_16b};
                    result_redor   = {'0, result_redor_16b };
                    result_redxor  = {'0, result_redxor_16b};
                end
                default: begin
                    result_redand  = result_redand_32b;
                    result_redor   = result_redor_32b;
                    result_redxor  = result_redxor_32b;
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

    // *********************************
    //  MIN-MAX
    // *********************************
    if (V_REDMINMAX_ON) begin : v_redminmax_gen_on
        /////////////////////////////////////////////////
        // 8 Bits
        /////////////////////////////////////////////////
        logic [ 7:0] result_redmin_8b;
        logic [ 7:0] result_redminu_8b;
        logic [ 7:0] result_redmax_8b;
        logic [ 7:0] result_redmaxu_8b;

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_MIN),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_min_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmin_8b)
        );

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_MINU),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_minu_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redminu_8b)
        );

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_MAX),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_max_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmax_8b)
        );

        vectorReductionTree #(
            .SEW             (8),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/8),
            .RED_OP          (RED_MAXU),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_maxu_8b (
            .clk           (clk),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew8),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmaxu_8b)
        );

        /////////////////////////////////////////////////
        // 16 Bits
        /////////////////////////////////////////////////
        logic [15:0] result_redmin_16b;
        logic [15:0] result_redminu_16b;
        logic [15:0] result_redmax_16b;
        logic [15:0] result_redmaxu_16b;

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_MIN),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_min_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmin_16b)
        );

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_MINU),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_minu_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redminu_16b)
        );

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_MAX),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_max_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmax_16b)
        );

        vectorReductionTree #(
            .SEW             (16),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/16),
            .RED_OP          (RED_MAXU),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_maxu_16b (
            .clk           (clk),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew16),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmaxu_16b)
        );

        /////////////////////////////////////////////////
        // 32 Bits
        /////////////////////////////////////////////////
        logic [31:0] result_redmin_32b;
        logic [31:0] result_redminu_32b;
        logic [31:0] result_redmax_32b;
        logic [31:0] result_redmaxu_32b;

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_MIN),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_min_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmin_32b)
        );

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_MINU),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_minu_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redminu_32b)
        );

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_MAX),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_max_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmax_32b)
        );

        vectorReductionTree #(
            .SEW             (32),
            .VLEN            (VLEN),
            .ELEMENTS_PER_REG(VLEN/32),
            .RED_OP          (RED_MAXU),
            .MULTI_CYCLE     (MULTI_CYCLE)
        )   reduction_tree_maxu_32b (
            .clk           (clk),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_sew32),
            .cycle_count_r (cycle_count_r),
            .result_o      (result_redmaxu_32b)
        );

        // *********************************
        //  Sew Demux
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_redmin  = {'0, result_redmin_8b };
                    result_redminu = {'0, result_redminu_8b};
                    result_redmax  = {'0, result_redmax_8b };
                    result_redmaxu = {'0, result_redmaxu_8b};
                end
                EW16: begin
                    result_redmin  = {'0, result_redmin_16b };
                    result_redminu = {'0, result_redminu_16b};
                    result_redmax  = {'0, result_redmax_16b };
                    result_redmaxu = {'0, result_redmaxu_16b};
                end
                default: begin
                    result_redmin  = result_redmin_32b;
                    result_redminu = result_redminu_32b;
                    result_redmax  = result_redmax_32b;
                    result_redmaxu = result_redmaxu_32b;
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

    // *********************************
    //  Result Demux
    // *********************************

    always @(posedge clk) begin
        unique case(vector_operation_i)
            VREDOR:   result_o <= result_redor;
            VREDXOR:  result_o <= result_redxor;
            VREDSUM:  result_o <= result_redsum;
            VREDMIN:  result_o <= result_redmin;
            VREDMINU: result_o <= result_redminu;
            VREDMAX:  result_o <= result_redmax;
            VREDMAXU: result_o <= result_redmaxu;
            default:  result_o <= result_redand;
        endcase
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
