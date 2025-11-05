/*!\file vectorALU.sv
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
module vectorALU
    import RS5_pkg::*;
#(
    parameter int VLEN                   = 64,
    parameter int LLEN                   = 32,
    parameter int VLENB                  = 8,
    parameter bit V_LOGIC_ON             = 1'b1,
    parameter bit V_MINMAX_ON            = 1'b1,
    parameter bit V_REDLOGIC_ON          = 1'b1,
    parameter bit V_REDMINMAX_ON         = 1'b1,
    parameter bit V_REDSUM_ON            = 1'b1,
    parameter bit V_MERGE_ON             = 1'b1,
    parameter bit V_DIV_ON               = 1'b1,
    parameter bit MULTI_CYCLE_REDUCTIONS = 1'b0
) (
    input  logic                        clk,
    input  logic                        reset_n,

    input  logic [VLEN-1:0]             first_operand,
    input  logic [VLEN-1:0]             second_operand,
    input  logic [VLEN-1:0]             third_operand,
    input  logic [31:0]                 scalar_operand,
    input  vector_states_e              current_state,
    input  logic [3:0]                  cycle_count,
    input  logic [3:0]                  cycle_count_r,
    input  vlmul_e                      vlmul,
    input  logic[$bits(VLEN)-1:0]       vl,
    input  logic[$bits(VLEN)-1:0]       vl_next,
    input  logic                        vm,
    input  logic [7:0][ VLENB   -1:0]   mask_sew8,
    input  logic [7:0][(VLENB/2)-1:0]   mask_sew16,
    input  logic [7:0][(VLENB/4)-1:0]   mask_sew32,

    input  iTypeVector_e                vector_operation_i,
    input  vew_e                        vsew,

    input  logic                        accumulate_instruction,
    input  logic                        multiply_instruction,
    input  logic                        reduction_instruction,
    input  logic                        widening_instruction,

    output logic                        hold_o,
    output logic                        hold_widening_o,
    output logic [VLEN-1:0]             result_mask_o,
    output logic [VLEN-1:0]             result_o
);

    localparam LANES = VLEN/LLEN;

    logic [LANES-1:0] hold_lanes;
    logic             hold_reductions;
    logic             hold_accumulation;
    logic             hold;

//////////////////////////////////////////////////////////////////////////////
// Widening Control
//////////////////////////////////////////////////////////////////////////////
    logic hold_widening_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hold_widening_r <= 1'b0;
        end
        else begin
            hold_widening_r <= hold_widening_o;
        end
    end

    assign hold_widening_o = widening_instruction && !hold && !hold_widening_r;

//////////////////////////////////////////////////////////////////////////////
// Accumulation Control
//////////////////////////////////////////////////////////////////////////////
    logic hold_accumulation_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hold_accumulation_r <= 1'b0;
        end
        else begin
            hold_accumulation_r <= hold_accumulation;
        end
    end

    assign hold_accumulation = accumulate_instruction && !hold && !hold_accumulation_r;

//////////////////////////////////////////////////////////////////////////////
// Reductions
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] second_operand_reductions;
    logic [31:0] result_reductions;

    assign second_operand_reductions = (cycle_count_r > 0)
                                     ?  result_reductions
                                     :  second_operand[31:0];

    vectorReductions #(
            .VLEN            (VLEN),
            .VLENB           (VLENB),
            .V_REDSUM_ON     (V_REDSUM_ON),
            .V_REDLOGIC_ON   (V_REDLOGIC_ON),
            .V_REDMINMAX_ON  (V_REDMINMAX_ON),
            .MULTI_CYCLE     (MULTI_CYCLE_REDUCTIONS)
    )   u_vector_reductions (
            .clk               (clk),
            .reset_n           (reset_n),
            .enable_i          (reduction_instruction),
            .vector_operation_i(vector_operation_i),
            .first_operand     (first_operand),
            .second_operand    (second_operand_reductions),
            .vsew              (vsew),
            .cycle_count_r     (cycle_count_r),
            .vl                (vl),
            .vm                (vm),
            .mask_sew8         (mask_sew8),
            .mask_sew16        (mask_sew16),
            .mask_sew32        (mask_sew32),
            .hold_o            (hold_reductions),
            .result_o          (result_reductions)
        );

//////////////////////////////////////////////////////////////////////////////
// Slides
//////////////////////////////////////////////////////////////////////////////
    logic            slide_instruction;
    logic [VLEN-1:0] result_slide;

    assign slide_instruction = vector_operation_i inside {VSLIDE1UP, VSLIDE1DOWN};

    vectorSlide #(
            .VLEN (VLEN)
    )   u_vector_slides (
            .clk               (clk),
            .reset_n           (reset_n),
            .vector_operation_i(vector_operation_i),
            .first_operand     (first_operand),
            .second_operand    (second_operand[31:0]),
            .scalar_operand    (scalar_operand),
            .cycle_count       (cycle_count),
            .vsew              (vsew),
            .vlmul             (vlmul),
            .vl                (vl),
            .vl_next           (vl_next),
            .result_o          (result_slide)
        );

//////////////////////////////////////////////////////////////////////////////
// Multiplication_common
//////////////////////////////////////////////////////////////////////////////

    logic [1:0] mult_signed_mode;
    logic       ended_acc;
    logic       mult_enable;

    always_comb begin
        unique case (vector_operation_i)
            VMULH,   VWMUL:   mult_signed_mode = 2'b11;
            VMULHSU, VWMULSU: mult_signed_mode = 2'b01;
            default:          mult_signed_mode = 2'b00;
        endcase
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
                            multiply_instruction
                        &&  (!ended_acc)
                        &&  (!hold_widening_r == 1'b1)
                        &&  (!hold_accumulation_r)
                        );

//////////////////////////////////////////////////////////////////////////////
// Division Common
//////////////////////////////////////////////////////////////////////////////

    logic div_enable;

    if (V_DIV_ON) begin : v_div_common_gen_on
        assign div_enable = (vector_operation_i inside {VDIV, VDIVU, VREM, VREMU} && current_state == V_EXEC);
    end
    else begin : v_div_common_gen_off
        assign div_enable = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// Lanes
//////////////////////////////////////////////////////////////////////////////

    logic enable_lane;
    logic [LANES-1:0][LLEN/8-1:0] result_lanes_mask;
    logic [(2*VLEN)-1:0]    result_lanes_mult;
    logic [   VLEN -1:0]    result_lanes;
    logic [   VLEN -1:0]    result_mult_low;

    assign enable_lane = current_state == V_EXEC && vector_operation_i != VNOP && !hold_widening_r && !hold_accumulation_r && !reduction_instruction && !slide_instruction;

    generate
        for (genvar i_lane = 0; i_lane < LANES; i_lane++) begin : LANE_LOOP
            vectorLane #(
                .LLEN        (LLEN),
                .V_LOGIC_ON  (V_LOGIC_ON),
                .V_MINMAX_ON (V_MINMAX_ON),
                .V_MERGE_ON  (V_MERGE_ON),
                .V_DIV_ON    (V_DIV_ON)
            )   u_vectorLane (
                .clk               (clk),
                .reset_n           (reset_n),
                .first_operand_i   (first_operand [(LLEN*i_lane)+:LLEN]),
                .second_operand_i  (second_operand[(LLEN*i_lane)+:LLEN]),
                .third_operand_i   (third_operand [(LLEN*i_lane)+:LLEN]),
                .mask_sew8_i       (mask_sew8 [cycle_count_r][((LLEN/ 8)*i_lane)+:LLEN/8]),
                .mask_sew16_i      (mask_sew16[cycle_count_r][((LLEN/16)*i_lane)+:LLEN/16]),
                .mask_sew32_i      (mask_sew32[cycle_count_r][((LLEN/32)*i_lane)+:LLEN/32]),
                .enable_i          (enable_lane),
                .vector_operation_i(vector_operation_i),
                .vsew              (vsew),
                .vm                (vm),
                .mult_enable       (mult_enable),
                .hold_widening     (hold_widening_r),
                .mult_signed_mode  (mult_signed_mode),
                .div_enable        (div_enable),
                .hold_o            (hold_lanes[i_lane]),
                .result_mask_o     (result_lanes_mask[i_lane]),
                .result_mult_o     (result_lanes_mult[(2*LLEN*i_lane)+:2*LLEN]),
                .result_o          (result_lanes[(LLEN*i_lane)+:LLEN])
            );
        end
    endgenerate

    always_comb begin
        result_mult_low = '0;
        for (int i = 0; i < VLEN/32; i++) begin
            result_mult_low[(32*i)+:32] = result_lanes_mult[(64*i)+:64];
        end
    end


//////////////////////////////////////////////////////////////////////////////
// Mask Instructions
//////////////////////////////////////////////////////////////////////////////
    logic [VLENB-1:0] result_mask;

    always_comb begin
        result_mask = '0;
        unique case (vsew)
            EW8:
                for (int i = 0; i < LANES; i++)
                    result_mask[(LLEN/8)*i+:LLEN/8] = result_lanes_mask[i];

            EW16:
                for (int i = 0; i < LANES; i++)
                    result_mask[(LLEN/16)*i+:LLEN/16] = result_lanes_mask[i][(LLEN/16)-1:0];

            default:
                for (int i = 0; i < LANES; i++)
                    result_mask[(LLEN/32)*i+:LLEN/32] = result_lanes_mask[i][(LLEN/32)-1:0];
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            result_mask_o <= '0;
        end
        else begin
            unique case (vsew)
                EW8:
                    for (int i = 0; i < 8; i++)
                        if (i == cycle_count_r)
                            result_mask_o[(VLENB*i)+:VLENB] <= result_mask[VLENB-1:0];

                EW16:
                    for (int i = 0; i < 8; i++)
                        if (i == cycle_count_r)
                            result_mask_o[((VLENB/2)*i)+:VLENB/2] <= result_mask[(VLENB/2)-1:0];

                default:
                    for (int i = 0; i < 8; i++)
                        if (i == cycle_count_r)
                            result_mask_o[((VLENB/4)*i)+:VLENB/4] <= result_mask[(VLENB/4)-1:0];
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Hold generation
//////////////////////////////////////////////////////////////////////////////

    assign hold = |hold_lanes;

    assign hold_o = hold | hold_widening_o | hold_accumulation | hold_reductions;

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] first_operand_r;
    logic [VLEN-1:0] second_operand_r;
    iTypeVector_e    vector_operation_r;
    logic            hold_widening_2r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            first_operand_r    <= '0;
            second_operand_r   <= '0;
            vector_operation_r <= VNOP;
            hold_widening_2r   <= '0;
        end
        else begin
            first_operand_r    <= first_operand;
            second_operand_r   <= second_operand;
            vector_operation_r <= vector_operation_i;
            hold_widening_2r   <= hold_widening_r;
        end
    end

    always_comb begin
        unique case(vector_operation_r)
            VREDXOR, VREDSUM,
            VREDMIN, VREDMINU,
            VREDMAX, VREDMAXU,
            VREDAND, VREDOR:   result_o = {'0, result_reductions};
            VMV, VMVSX:        result_o = second_operand_r;
            VMVR:              result_o = first_operand_r;
            VMUL, VMULH,
            VMULHU, VMULHSU:   result_o = result_mult_low;
            VWMUL, VWMULU,
            VWMULSU:           result_o = (hold_widening_2r == 1'b1) ? result_lanes_mult[(2*VLEN)-1:VLEN] : result_lanes_mult[VLEN-1:0];
            VSLIDE1UP,
            VSLIDE1DOWN:       result_o = result_slide;
            default:           result_o = result_lanes;
        endcase
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
