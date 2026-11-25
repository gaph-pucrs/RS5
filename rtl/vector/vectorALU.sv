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
    parameter int VLEN                  = 64,
    parameter int LLEN                  = 32,
    parameter int VLENB                 = 8,
    parameter bit VLogicEnable          = 1'b1,
    parameter bit VMinMaxEnable         = 1'b1,
    parameter bit VRedLogicEnable       = 1'b1,
    parameter bit VRedMinMaxEnable      = 1'b1,
    parameter bit VRedSumEnable         = 1'b1,
    parameter bit VMergeEnable          = 1'b1,
    parameter bit VCarryEnable          = 1'b1,
    parameter bit VDivEnable            = 1'b1,
    parameter bit VMultiCycleReductions = 1'b0
) (
    input  logic                        clk,
    input  logic                        reset_n,
    input  logic                        stall,

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
    input  vector_ctrl_t                vctrl_i,
    input  vew_e                        vsew,

    input  logic                        accumulate_instruction,
    input  logic                        mask_instruction,
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
    logic             hold_mask;
    logic             hold;

//////////////////////////////////////////////////////////////////////////////
// Widening Control
//////////////////////////////////////////////////////////////////////////////
    logic hold_widening_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hold_widening_r <= 1'b0;
        end
        else if (!stall) begin
            hold_widening_r <= hold_widening_o;
        end
    end

    /* The widening multiply-add adds each half of the registered product  */
    /* to the old destination: WM_MUL multiplies, and its last cycle holds */
    /* while the product is registered; WM_LO adds the low half to vd[2c]  */
    /* and raises hold_widening_o; WM_HI adds the high half to vd[2c+1]    */
    typedef enum logic [1:0] {
        WM_MUL, WM_LO, WM_HI
    } wmacc_phase_e;

    logic         widening_accumulate;
    logic         hold_product;
    wmacc_phase_e wmacc_phase;

    assign widening_accumulate = widening_instruction && (vector_operation_i inside {VWMACCU, VWMACC, VWMACCSU, VWMACCUS});

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            wmacc_phase <= WM_MUL;
        end
        else if (!stall) begin
            if (!widening_accumulate)
                wmacc_phase <= WM_MUL;
            else if (!hold) begin
                unique case (wmacc_phase)
                    WM_MUL:  wmacc_phase <= WM_LO;
                    WM_LO:   wmacc_phase <= WM_HI;
                    default: wmacc_phase <= WM_MUL;
                endcase
            end
        end
    end

    assign hold_product = widening_accumulate && (wmacc_phase == WM_MUL) && !hold;

    always_comb begin
        if (widening_accumulate)
            hold_widening_o = (wmacc_phase == WM_LO) && !hold;
        else
            hold_widening_o = widening_instruction && !hold && !hold_widening_r;
    end

    /* In WM_LO and WM_HI the lanes add at 2*SEW: they take a half of the */
    /* product and the old destination (third_operand), and keep the      */
    /* product registered                                                 */
    logic wmacc_add;
    assign wmacc_add = widening_accumulate && (wmacc_phase != WM_MUL);

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
// Mask Control
//////////////////////////////////////////////////////////////////////////////
    logic hold_mask_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            hold_mask_r <= 1'b0;
        end
        else begin
            hold_mask_r <= hold_mask;
        end
    end

    assign hold_mask = mask_instruction && !hold && !hold_mask_r ;

//////////////////////////////////////////////////////////////////////////////
// Reductions
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] second_operand_reductions;
    logic [31:0] result_reductions;

    assign second_operand_reductions = (cycle_count_r > 0)
                                     ?  result_reductions
                                     :  second_operand[31:0];

    vectorReductions #(
            .VLEN                  (VLEN),
            .VLENB                 (VLENB),
            .VRedSumEnable         (VRedSumEnable),
            .VRedLogicEnable       (VRedLogicEnable),
            .VRedMinMaxEnable      (VRedMinMaxEnable),
            .VMultiCycleReductions (VMultiCycleReductions)
    )   u_vector_reductions (
            .clk               (clk),
            .reset_n           (reset_n),
            .stall             (stall),
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
            .stall             (stall),
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
            /* Bit 0 is the sign of vs2 (first operand), bit 1 of vs1 or rs1 */
            VMULH,   VWMUL,
            VWMACC:           mult_signed_mode = 2'b11;
            VMULHSU, VWMULSU,
            VWMACCUS:         mult_signed_mode = 2'b01;
            VWMACCSU:         mult_signed_mode = 2'b10;
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
                        &&  (!wmacc_add)
                        );

//////////////////////////////////////////////////////////////////////////////
// Division Common
//////////////////////////////////////////////////////////////////////////////

    logic div_enable;

    if (VDivEnable) begin : v_div_common_gen_on
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

    /* The lanes stop in the extra cycle of a compare (hold_mask_r): with      */
    /* LLEN > 32 a lane that kept running would restart its element counter, */
    /* raise hold_llen again and re-arm hold_mask, so the compare never ends. */
    /* Loads and stores do not use the lanes: with LLEN > 32 a running lane */
    /* raises hold_llen and breaks the LSU sequencing.                      */
    /* The widening multiply-add keeps the lanes running in WM_HI, which */
    /* follows its hold_widening_o                                       */
    assign enable_lane = current_state == V_EXEC && !(vector_operation_i inside {VNOP, VLD, VST}) && !(hold_widening_r && !widening_accumulate) && !hold_accumulation_r && !hold_mask_r && !reduction_instruction && !slide_instruction;

    /* Lane inputs of the widening multiply-add: a widening multiply in */
    /* WM_MUL, then an add at 2*SEW of a product half and the old vd    */
    logic [VLEN-1:0] lane_first_operand, lane_second_operand;
    iTypeVector_e    lane_operation;
    vew_e            lane_vsew, vsew_wide;
    logic            lane_hold_widening;

    always_comb begin
        if (vsew == EW8)
            vsew_wide = EW16;
        else
            vsew_wide = EW32;
    end

    always_comb begin
        if (!widening_accumulate) begin
            lane_operation      = vector_operation_i;
            lane_vsew           = vsew;
            lane_first_operand  = first_operand;
            lane_second_operand = second_operand;
        end
        else if (wmacc_phase == WM_MUL) begin
            lane_operation      = VWMUL;
            lane_vsew           = vsew;
            lane_first_operand  = first_operand;
            lane_second_operand = second_operand;
        end
        else if (wmacc_phase == WM_LO) begin
            lane_operation      = VADD;
            lane_vsew           = vsew_wide;
            lane_first_operand  = result_lanes_mult[VLEN-1:0];
            lane_second_operand = third_operand;
        end
        else begin
            lane_operation      = VADD;
            lane_vsew           = vsew_wide;
            lane_first_operand  = result_lanes_mult[(2*VLEN)-1:VLEN];
            lane_second_operand = third_operand;
        end
    end

    assign lane_hold_widening = hold_widening_r || wmacc_add;

    generate
        for (genvar i_lane = 0; i_lane < LANES; i_lane++) begin : LANE_LOOP
            vectorLane #(
                .LLEN          (LLEN),
                .VLogicEnable  (VLogicEnable),
                .VMinMaxEnable (VMinMaxEnable),
                .VMergeEnable  (VMergeEnable),
                .VCarryEnable  (VCarryEnable),
                .VDivEnable    (VDivEnable)
            )   u_vectorLane (
                .clk               (clk),
                .reset_n           (reset_n),
                .first_operand_i   (lane_first_operand [(LLEN*i_lane)+:LLEN]),
                .second_operand_i  (lane_second_operand[(LLEN*i_lane)+:LLEN]),
                .third_operand_i   (third_operand [(LLEN*i_lane)+:LLEN]),
                .mask_sew8_i       (mask_sew8 [cycle_count_r][((LLEN/ 8)*i_lane)+:LLEN/8]),
                .mask_sew16_i      (mask_sew16[cycle_count_r][((LLEN/16)*i_lane)+:LLEN/16]),
                .mask_sew32_i      (mask_sew32[cycle_count_r][((LLEN/32)*i_lane)+:LLEN/32]),
                .enable_i          (enable_lane),
                .vector_operation_i(lane_operation),
                .vctrl_i           (vctrl_i),
                .vsew              (lane_vsew),
                .vm                (vm),
                .mult_enable       (mult_enable),
                .hold_widening     (lane_hold_widening),
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

    assign hold_o = hold | hold_widening_o | hold_product | hold_accumulation | hold_reductions | hold_mask;

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
            VREDAND, VREDOR,
            VWREDSUMU,
            VWREDSUM:          result_o = {'0, result_reductions};
            VMV, VMVSX:        result_o = second_operand_r;
            VMVR,
            VZEXT, VSEXT:      result_o = first_operand_r;
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
