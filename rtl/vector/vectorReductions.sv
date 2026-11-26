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
    parameter int VLEN                  = 64,
    parameter int VLENB                 = 8,
    parameter bit VRedSumEnable         = 1'b1,
    parameter bit VRedLogicEnable       = 1'b1,
    parameter bit VRedMinMaxEnable      = 1'b1,
    parameter bit VMultiCycleReductions = 1'b0
) (
    input  logic                       clk,
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic                       reset_n,
    input  logic                       enable_i,
    /* verilator lint_on UNUSEDSIGNAL  */
    input  logic                       stall,
    input  iTypeVector_e               vector_operation_i,
    /* vwredsum, vwredsumu: each source register is reduced in two passes */
    input  logic                       widening_reduction,

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

    logic [$clog2(TREE_LEVELS_8b):0] cycle_counter;

    if (VMultiCycleReductions) begin  : multi_cycle_reduction_on
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
        assign cycle_counter = '0;
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
    // Mask of this pass
    // *********************************
    logic [ VLENB   -1:0] mask_8b;
    logic [(VLENB/2)-1:0] mask_16b;
    logic [(VLENB/4)-1:0] mask_32b;

    /* The widening sum reductions read each source register in two passes */
    /* of 2*SEW elements: pass c takes half c[0] of the SEW mask of source  */
    /* register c >> 1                                                      */
    logic [2:0] src_reg;

    assign src_reg  = cycle_count_r[3:1];

    assign mask_8b  = mask_sew8 [cycle_count_r];

    always_comb begin
        if (!widening_reduction)
            mask_16b = mask_sew16[cycle_count_r];
        else if (cycle_count_r[0])
            mask_16b = mask_sew8[src_reg][VLENB-1:VLENB/2];
        else
            mask_16b = mask_sew8[src_reg][(VLENB/2)-1:0];
    end

    always_comb begin
        if (!widening_reduction)
            mask_32b = mask_sew32[cycle_count_r];
        else if (cycle_count_r[0])
            mask_32b = mask_sew16[src_reg][(VLENB/2)-1:VLENB/4];
        else
            mask_32b = mask_sew16[src_reg][(VLENB/4)-1:0];
    end

    // *********************************
    //  SUM
    // *********************************
    if (VRedSumEnable) begin : v_redsum_gen_on
        logic [ 7:0] result_redsum_8b;
        logic [15:0] result_redsum_16b;
        logic [31:0] result_redsum_32b;

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_SUM),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_sum_8b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redsum_8b)
        );

        vectorReductionTree #(
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_SUM),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_sum_16b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redsum_16b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_SUM),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_sum_32b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
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
    if (VRedLogicEnable) begin : v_redlogic_gen_on
        /* AND, OR and XOR are bitwise, so the 8 and 16 bit reductions run on */
        /* the 32 bit trees: each inactive element takes the identity of its  */
        /* operation, the accumulator goes in the low SEW bits of word 0 with */
        /* the identity above, and the 32 bit result is folded to SEW at the  */
        /* end. OR runs on the AND tree with inputs and result inverted       */
        /* (De Morgan: or(x) = ~and(~x)).                                     */
        logic [VLENB-1:0] active_byte;
        logic [VLEN-1:0]  active_bits;
        logic [VLEN-1:0]  inverted_operand;
        logic [31:0]      sew_bits;
        logic             invert;

        always_comb begin
            for (int i = 0; i < VLENB; i++) begin
                unique case (vsew)
                    EW8:     active_byte[i] = (vm || mask_8b [i  ]) && (i   < vl);
                    EW16:    active_byte[i] = (vm || mask_16b[i/2]) && (i/2 < vl);
                    default: active_byte[i] = (vm || mask_32b[i/4]) && (i/4 < vl);
                endcase
                active_bits[(8*i)+:8] = {8{active_byte[i]}};
            end
        end

        always_comb begin
            unique case (vsew)
                EW8:     sew_bits = 32'h0000_00FF;
                EW16:    sew_bits = 32'h0000_FFFF;
                default: sew_bits = 32'hFFFF_FFFF;
            endcase
        end

        assign invert           = (vector_operation_i == VREDOR);
        assign inverted_operand = first_operand ^ {VLEN{invert}};

        logic [(VLENB/4)-1:0][31:0] and_operand;
        logic [(VLENB/4)-1:0][31:0] xor_operand;
        logic [31:0]                and_accumulator;
        logic [31:0]                xor_accumulator;
        logic [31:0]                result_and_32b;
        logic [31:0]                result_xor_32b;

        always_comb begin
            for (int i = 0; i < VLENB/4; i++) begin
                and_operand[i] = inverted_operand[(32*i)+:32] | ~active_bits[(32*i)+:32];
                xor_operand[i] = first_operand   [(32*i)+:32] &  active_bits[(32*i)+:32];
            end
        end

        assign and_accumulator = ((second_operand ^ {32{invert}}) & sew_bits) | ~sew_bits;
        assign xor_accumulator =   second_operand                 & sew_bits;

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_AND),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_and (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (and_operand),
            .second_operand(and_accumulator),
            .vl            (VLEN/32),
            .vm            (1'b1),
            .mask          ('1),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_and_32b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_XOR),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_xor (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (xor_operand),
            .second_operand(xor_accumulator),
            .vl            (VLEN/32),
            .vm            (1'b1),
            .mask          ('1),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_xor_32b)
        );

        // *********************************
        //  Fold to SEW
        // *********************************
        logic [31:0] result_and_folded;

        always_comb begin
            unique case (vsew)
                EW8: begin
                    result_and_folded = {24'b0, result_and_32b[7:0]   & result_and_32b[15:8]
                                              & result_and_32b[23:16] & result_and_32b[31:24]};
                    result_redxor     = {24'b0, result_xor_32b[7:0]   ^ result_xor_32b[15:8]
                                              ^ result_xor_32b[23:16] ^ result_xor_32b[31:24]};
                end
                EW16: begin
                    result_and_folded = {16'b0, result_and_32b[15:0] & result_and_32b[31:16]};
                    result_redxor     = {16'b0, result_xor_32b[15:0] ^ result_xor_32b[31:16]};
                end
                default: begin
                    result_and_folded = result_and_32b;
                    result_redxor     = result_xor_32b;
                end
            endcase
        end

        assign result_redand = result_and_folded;
        assign result_redor  = result_and_folded ^ sew_bits;
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
    if (VRedMinMaxEnable) begin : v_redminmax_gen_on
        /////////////////////////////////////////////////
        // 8 Bits
        /////////////////////////////////////////////////
        logic [ 7:0] result_redmin_8b;
        logic [ 7:0] result_redminu_8b;
        logic [ 7:0] result_redmax_8b;
        logic [ 7:0] result_redmaxu_8b;

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_MIN),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_min_8b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redmin_8b)
        );

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_MINU),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_minu_8b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redminu_8b)
        );

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_MAX),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_max_8b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redmax_8b)
        );

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_MAXU),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_maxu_8b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
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
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_MIN),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_min_16b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redmin_16b)
        );

        vectorReductionTree #(
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_MINU),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_minu_16b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redminu_16b)
        );

        vectorReductionTree #(
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_MAX),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_max_16b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redmax_16b)
        );

        vectorReductionTree #(
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_MAXU),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_maxu_16b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
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
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_MIN),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_min_32b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redmin_32b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_MINU),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_minu_32b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redminu_32b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_MAX),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_max_32b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
            .result_o      (result_redmax_32b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_MAXU),
            .VMultiCycleReductions (VMultiCycleReductions)
        )   reduction_tree_maxu_32b (
            .clk           (clk),
            .reset_n       (reset_n),
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
            .cycle         ({ {(10-$bits(cycle_counter)){1'b0}}, cycle_counter}),
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
        if (!stall) begin
            unique case(vector_operation_i)
                VREDOR:   result_o <= result_redor;
                VREDXOR:  result_o <= result_redxor;
                VREDSUM,
                VWREDSUMU,
                VWREDSUM: result_o <= result_redsum;
                VREDMIN:  result_o <= result_redmin;
                VREDMINU: result_o <= result_redminu;
                VREDMAX:  result_o <= result_redmax;
                VREDMAXU: result_o <= result_redmaxu;
                default:  result_o <= result_redand;
            endcase
        end
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
