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
    logic [31:0] result_redminmax;

    /* Element by element add of two 32 bit slices: a separator bit between */
    /* bytes stops the carry at an element boundary (a = b = 0) or lets it  */
    /* through inside an element (a = 1, b = 0)                             */
    function automatic logic [31:0] simd_add(input logic [31:0] a, input logic [31:0] b,
                                             input logic [2:0] bnd);
        /* verilator lint_off UNUSEDSIGNAL */
        logic [34:0] s;     /* the separator bits are dropped */
        /* verilator lint_on UNUSEDSIGNAL */
        s = {a[31:24], ~bnd[2], a[23:16], ~bnd[1], a[15:8], ~bnd[0], a[7:0]}
          + {b[31:24],    1'b0, b[23:16],    1'b0, b[15:8],    1'b0, b[7:0]};
        return {s[34:27], s[25:18], s[16:9], s[7:0]};
    endfunction

    /* Element by element unsigned minimum: a - b with the same separators, */
    /* which at a boundary (a = b = 1) also add the +1 of the next element; */
    /* the sum bit of a boundary separator is the carry out of the element  */
    /* below it, which is 1 when a >= b                                     */
    function automatic logic [31:0] simd_minu(input logic [31:0] a, input logic [31:0] b,
                                              input logic [2:0] bnd, input vew_e sew);
        /* verilator lint_off UNUSEDSIGNAL */
        logic [35:0] d;     /* only the carries are used */
        /* verilator lint_on UNUSEDSIGNAL */
        logic [3:0]  carry, a_ge_b;
        logic [31:0] nb, r;
        nb = ~b;
        d = {1'b0, a[31:24],   1'b1, a[23:16],   1'b1, a[15:8],   1'b1, a[7:0]}
          + {1'b0, nb[31:24], bnd[2], nb[23:16], bnd[1], nb[15:8], bnd[0], nb[7:0]}
          + 36'd1;
        carry = {d[35], d[26], d[17], d[8]};
        unique case (sew)
            EW8:     a_ge_b = carry;
            EW16:    a_ge_b = {{2{carry[3]}}, {2{carry[1]}}};
            default: a_ge_b = {4{carry[3]}};
        endcase
        for (int k = 0; k < 4; k++)
            r[(8*k)+:8] = a_ge_b[k] ? b[(8*k)+:8] : a[(8*k)+:8];
        return r;
    endfunction

    // *********************************
    // Operands Control
    // *********************************
    /* verilator lint_off UNUSEDSIGNAL */
    /* The 8 and 16 bit views are not used with VMultiCycleReductions = 1 */
    logic [(VLENB)  -1:0][ 7:0] first_operand_8b;
    logic [(VLENB/2)-1:0][15:0] first_operand_16b;
    /* verilator lint_on UNUSEDSIGNAL */
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
    if (VRedSumEnable && !VMultiCycleReductions) begin : v_redsum_gen_on
        logic [ 7:0] result_redsum_8b;
        logic [15:0] result_redsum_16b;
        logic [31:0] result_redsum_32b;

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_SUM)
        )   reduction_tree_sum_8b (
            .first_operand (first_operand_8b),
            .second_operand(second_operand[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .result_o      (result_redsum_8b)
        );

        vectorReductionTree #(
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_SUM)
        )   reduction_tree_sum_16b (
            .first_operand (first_operand_16b),
            .second_operand(second_operand[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .result_o      (result_redsum_16b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_SUM)
        )   reduction_tree_sum_32b (
            .first_operand (first_operand_32b),
            .second_operand(second_operand[31:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
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
    if (VRedLogicEnable && !VMultiCycleReductions) begin : v_redlogic_gen_on
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
            .RED_OP                (RED_AND)
        )   reduction_tree_and (
            .first_operand (and_operand),
            .second_operand(and_accumulator),
            .vl            (VLEN/32),
            .vm            (1'b1),
            .mask          ('1),
            .result_o      (result_and_32b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_XOR)
        )   reduction_tree_xor (
            .first_operand (xor_operand),
            .second_operand(xor_accumulator),
            .vl            (VLEN/32),
            .vm            (1'b1),
            .mask          ('1),
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
    if (VRedMinMaxEnable && !VMultiCycleReductions) begin : v_redminmax_gen_on
        /* One minu tree per width covers the four operations: flipping the */
        /* MSB of each element turns the signed order into the unsigned     */
        /* one, and inverting every bit turns max into min                  */
        /* (max(a,b) = ~min(~a,~b)). The same XOR pattern goes into the     */
        /* elements and the accumulator and comes out of the result; the    */
        /* identity of the inactive elements ('1 for minu) is the right one */
        /* after the transform.                                             */
        logic        minmax_signed;
        logic        minmax_max;
        logic [31:0] minmax_pattern;

        assign minmax_signed = (vector_operation_i inside {VREDMIN, VREDMAX});
        assign minmax_max    = (vector_operation_i inside {VREDMAX, VREDMAXU});

        always_comb begin
            unique case (vsew)
                EW8:     minmax_pattern = {4{{8{minmax_max}}  ^ {minmax_signed, 7'b0}}};
                EW16:    minmax_pattern = {2{{16{minmax_max}} ^ {minmax_signed, 15'b0}}};
                default: minmax_pattern =     {32{minmax_max}} ^ {minmax_signed, 31'b0};
            endcase
        end

        logic [VLEN-1:0] minmax_operand;
        logic [31:0]     minmax_accumulator;

        assign minmax_operand     = first_operand  ^ {(VLEN/32){minmax_pattern}};
        assign minmax_accumulator = second_operand ^ minmax_pattern;

        logic [(VLENB)  -1:0][ 7:0] minmax_operand_8b;
        logic [(VLENB/2)-1:0][15:0] minmax_operand_16b;
        logic [(VLENB/4)-1:0][31:0] minmax_operand_32b;

        always_comb begin
            for (int i = 0; i < VLENB; i++) begin
                minmax_operand_8b [i] = minmax_operand[(8*i)+:8];
            end
            for (int i = 0; i < VLENB/2; i++) begin
                minmax_operand_16b[i] = minmax_operand[(16*i)+:16];
            end
            for (int i = 0; i < VLENB/4; i++) begin
                minmax_operand_32b[i] = minmax_operand[(32*i)+:32];
            end
        end

        logic [ 7:0] result_minu_8b;
        logic [15:0] result_minu_16b;
        logic [31:0] result_minu_32b;

        vectorReductionTree #(
            .SEW                   (8),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/8),
            .RED_OP                (RED_MINU)
        )   reduction_tree_minu_8b (
            .first_operand (minmax_operand_8b),
            .second_operand(minmax_accumulator[7:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_8b),
            .result_o      (result_minu_8b)
        );

        vectorReductionTree #(
            .SEW                   (16),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/16),
            .RED_OP                (RED_MINU)
        )   reduction_tree_minu_16b (
            .first_operand (minmax_operand_16b),
            .second_operand(minmax_accumulator[15:0]),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_16b),
            .result_o      (result_minu_16b)
        );

        vectorReductionTree #(
            .SEW                   (32),
            .VLEN                  (VLEN),
            .ELEMENTS_PER_REG      (VLEN/32),
            .RED_OP                (RED_MINU)
        )   reduction_tree_minu_32b (
            .first_operand (minmax_operand_32b),
            .second_operand(minmax_accumulator),
            .vl            (vl),
            .vm            (vm),
            .mask          (mask_32b),
            .result_o      (result_minu_32b)
        );

        // *********************************
        //  Sew Demux and inverse transform
        // *********************************
        always_comb begin
            unique case (vsew)
                EW8:     result_redminmax = {24'b0, result_minu_8b  ^ minmax_pattern[7:0]};
                EW16:    result_redminmax = {16'b0, result_minu_16b ^ minmax_pattern[15:0]};
                default: result_redminmax =         result_minu_32b ^ minmax_pattern;
            endcase
        end
    end
    else begin : v_redminmax_gen_off
        assign result_redminmax = '0;
    end

    // *********************************
    //  MULTI-CYCLE
    // *********************************
    /* The source register is reduced 32 bits per cycle: each step combines */
    /* one 32 bit chunk of first_operand, element by element, into a 32 bit */
    /* accumulator, and after the last chunk the accumulator is folded to   */
    /* one element (2 steps with SEW = 8, 1 with SEW = 16). The accumulator */
    /* starts with the scalar operand in element 0 and the identity of the  */
    /* operation elsewhere, as do the inactive elements. OR runs as AND     */
    /* with inputs and result inverted, and min/max as minu with the        */
    /* pattern of the single-cycle trees. The last step is combinational,   */
    /* in the cycle hold_o falls.                                           */
    logic [31:0] result_multi_cycle;

    if (VMultiCycleReductions) begin : multi_cycle_reduction_on
        localparam CHUNKS    = VLEN/32;
        localparam STEP_BITS = $clog2(CHUNKS+2);

        logic [STEP_BITS-1:0] step;
        logic [STEP_BITS-1:0] last_step;
        logic                 last_cycle;

        always_comb begin
            unique case (vsew)
                EW8:     last_step = STEP_BITS'(CHUNKS + 1);
                EW16:    last_step = STEP_BITS'(CHUNKS);
                default: last_step = STEP_BITS'(CHUNKS - 1);
            endcase
        end

        assign last_cycle = (step == last_step);
        assign hold_o     = enable_i && !last_cycle;

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                step <= '0;
            else if (enable_i && !last_cycle)
                step <= step + 1'b1;
            else
                step <= '0;
        end

        /* Operation */
        logic       op_sum, op_minu, op_and;
        logic       minmax_signed, minmax_max, invert;
        logic [2:0] boundary;
        logic [7:0] pattern_8b;
        logic [15:0] pattern_16b;
        logic [31:0] pattern, identity, sew_bits;

        assign op_sum        = (vector_operation_i inside {VREDSUM, VWREDSUMU, VWREDSUM});
        assign op_minu       = (vector_operation_i inside {VREDMIN, VREDMINU, VREDMAX, VREDMAXU});
        assign op_and        = (vector_operation_i inside {VREDAND, VREDOR});
        assign minmax_signed = (vector_operation_i inside {VREDMIN, VREDMAX});
        assign minmax_max    = (vector_operation_i inside {VREDMAX, VREDMAXU});
        assign invert        = (vector_operation_i == VREDOR);
        assign identity      = {32{op_and || op_minu}};

        assign pattern_8b  = {8{minmax_max  || invert}} ^ {minmax_signed, 7'b0};
        assign pattern_16b = {16{minmax_max || invert}} ^ {minmax_signed, 15'b0};

        always_comb begin
            unique case (vsew)
                EW8: begin
                    boundary = 3'b111;
                    pattern  = {4{pattern_8b}};
                    sew_bits = 32'h0000_00FF;
                end
                EW16: begin
                    boundary = 3'b010;
                    pattern  = {2{pattern_16b}};
                    sew_bits = 32'h0000_FFFF;
                end
                default: begin
                    boundary = 3'b000;
                    pattern  = {32{minmax_max || invert}} ^ {minmax_signed, 31'b0};
                    sew_bits = 32'hFFFF_FFFF;
                end
            endcase
        end

        /* Active elements of the chunk of this step, one bit per byte */
        logic [3:0]  active_byte;
        logic [31:0] active_bits;

        always_comb begin
            for (int j = 0; j < 4; j++) begin
                unique case (vsew)
                    EW8:     active_byte[j] = (vm || mask_8b [(4*step) + j    ]) && (((4*step) + j    ) < vl);
                    EW16:    active_byte[j] = (vm || mask_16b[(2*step) + (j/2)]) && (((2*step) + (j/2)) < vl);
                    default: active_byte[j] = (vm || mask_32b[step           ]) && (step < vl);
                endcase
                active_bits[(8*j)+:8] = {8{active_byte[j]}};
            end
        end

        /* Operands of the step */
        logic [31:0] accumulator, initial_value, chunk, chunk_operand, fold_operand;
        logic [31:0] operand_a, operand_b, step_result;

        assign chunk         = (step < CHUNKS) ? first_operand_32b[step[STEP_BITS-1:0]] : '0;
        assign chunk_operand = ((chunk ^ pattern) & active_bits) | (identity & ~active_bits);
        assign initial_value = ((second_operand ^ pattern) & sew_bits) | (identity & ~sew_bits);
        assign fold_operand  = (step == STEP_BITS'(CHUNKS)) ? (accumulator >> 16) : (accumulator >> 8);

        assign operand_a = (step == '0)     ? initial_value : accumulator;
        assign operand_b = (step < CHUNKS)  ? chunk_operand : fold_operand;

        /* Element by element operation on the 32 bits */
        logic [31:0] sum, smaller;

        assign sum     = (VRedSumEnable)    ? simd_add(operand_a, operand_b, boundary)     : '0;
        assign smaller = (VRedMinMaxEnable) ? simd_minu(operand_a, operand_b, boundary, vsew) : '0;

        always_comb begin
            if (op_sum)
                step_result = sum;
            else if (op_minu)
                step_result = smaller;
            else if (op_and)
                step_result = (VRedLogicEnable) ? (operand_a & operand_b) : '0;
            else
                step_result = (VRedLogicEnable) ? (operand_a ^ operand_b) : '0;
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                accumulator <= '0;
            else if (enable_i)
                accumulator <= step_result;
        end

        assign result_multi_cycle = (step_result ^ pattern) & sew_bits;
    end
    else begin : multi_cycle_reduction_off
        assign hold_o             = 1'b0;
        assign result_multi_cycle = '0;
    end

    // *********************************
    //  Result Demux
    // *********************************

    always @(posedge clk) begin
        if (!stall) begin
            if (VMultiCycleReductions) begin
                result_o <= result_multi_cycle;
            end
            else begin
                unique case(vector_operation_i)
                    VREDOR:   result_o <= result_redor;
                    VREDXOR:  result_o <= result_redxor;
                    VREDSUM,
                    VWREDSUMU,
                    VWREDSUM: result_o <= result_redsum;
                    VREDMIN,
                    VREDMINU,
                    VREDMAX,
                    VREDMAXU: result_o <= result_redminmax;
                    default:  result_o <= result_redand;
                endcase
            end
        end
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
