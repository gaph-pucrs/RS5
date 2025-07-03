`include "../RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorLane
    import RS5_pkg::*;
#(
    parameter int LLEN        = 32,
    parameter bit V_LOGIC_ON  = 1'b1,
    parameter bit V_MINMAX_ON = 1'b1,
    parameter bit V_MERGE_ON  = 1'b1,
    parameter bit V_DIV_ON    = 1'b1
) (
    input  logic              clk,
    input  logic              reset_n,

    input  logic [LLEN-1:0]    first_operand_i,
    input  logic [LLEN-1:0]    second_operand_i,
    input  logic [LLEN-1:0]    third_operand_i,
    input  logic [LLEN/ 8-1:0] mask_sew8_i,
    input  logic [LLEN/16-1:0] mask_sew16_i,
    input  logic [LLEN/32-1:0] mask_sew32_i,

    input  logic               enable_i,
    input  iTypeVector_e       vector_operation_i,
    input  vew_e               vsew,
    input  logic               vm,

    input  logic               mult_enable,
    input  logic               hold_widening,
    input  logic [ 1:0]        mult_signed_mode,
    input  logic               div_enable,

    output logic               hold_o,
    output logic [LLEN/8-1:0]  result_mask_o,
    output logic [2*LLEN-1:0]  result_mult_o,
    output logic [  LLEN-1:0]  result_o
);

    logic hold_mult;
    logic hold_div;

//////////////////////////////////////////////////////////////////////////////
// Operands Control
//////////////////////////////////////////////////////////////////////////////

    localparam ELEMENTS_PER_LANE = LLEN/32;
    logic [$clog2(LLEN/32)-1:0] cycle;
    logic [$clog2(LLEN/32)-1:0] cycle_r;
    logic hold_llen;

    logic [31:0] first_operand;
    logic [31:0] second_operand;
    logic [31:0] third_operand;
    logic [ 3:0] mask_sew8;
    logic [ 1:0] mask_sew16;
    logic        mask_sew32;

    if (LLEN > 32) begin
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                cycle <= '0;
            end
            else if (!enable_i) begin
                cycle <= '0;
            end
            else if (enable_i && !hold_mult && !hold_div) begin
                cycle <= cycle + 1;
            end
        end

        always_ff @(posedge clk) begin
            cycle_r <= cycle;
        end

        assign hold_llen = cycle < ELEMENTS_PER_LANE-1 && enable_i ;

    end
    else begin
        assign cycle     = 1'b0;
        assign cycle_r   = 1'b0;
        assign hold_llen = 1'b0;
    end

    always_comb begin
        first_operand  = first_operand_i [(32*cycle)+:32];
        second_operand = second_operand_i[(32*cycle)+:32];
        third_operand  = third_operand_i [(32*cycle)+:32];
        mask_sew8      = mask_sew8_i [(4*cycle)+:4];
        mask_sew16     = mask_sew16_i[(2*cycle)+:2];
        mask_sew32     = mask_sew32_i[cycle];
    end

//////////////////////////////////////////////////////////////////////////////
// 8 and 16 Operands
//////////////////////////////////////////////////////////////////////////////

    logic [3:0][ 7:0] second_op_8b;
    logic [1:0][15:0] second_op_16b;

    always_comb begin
        for (int i = 0; i < 4; i++) begin
            second_op_8b [i] = second_operand[(8*i)+:8];
        end
        for (int i = 0; i < 2; i++) begin
            second_op_16b[i] = second_operand[(16*i)+:16];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Logical
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] result_and;
    logic [31:0] result_or;
    logic [31:0] result_xor;

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
// Shifts
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] result_sll;
    logic [31:0] result_srl;
    logic [31:0] result_sra;

    always_comb begin
        unique case (vsew)
            EW8:
                for (int i = 0; i < 4; i++) begin
                    result_sll[(8*i)+:8] =         first_operand[(8*i)+:8]  <<  second_op_8b[i][2:0];
                    result_srl[(8*i)+:8] =         first_operand[(8*i)+:8]  >>  second_op_8b[i][2:0];
                    result_sra[(8*i)+:8] = $signed(first_operand[(8*i)+:8]) >>> second_op_8b[i][2:0];
                end
            EW16:
                for (int i = 0; i < 2; i++) begin
                    result_sll[(16*i)+:16] =         first_operand[(16*i)+:16]  <<  second_op_16b[i][3:0];
                    result_srl[(16*i)+:16] =         first_operand[(16*i)+:16]  >>  second_op_16b[i][3:0];
                    result_sra[(16*i)+:16] = $signed(first_operand[(16*i)+:16]) >>> second_op_16b[i][3:0];
                end
            default: begin
                result_sll =         first_operand  <<  second_operand[4:0];
                result_srl =         first_operand  >>  second_operand[4:0];
                result_sra = $signed(first_operand) >>> second_operand[4:0];
            end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
//  Merge
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] result_merge;

    if(V_MERGE_ON) begin : v_merge_gen_on
        always_comb begin
            unique case (vsew)
                EW8: begin
                    for (int i = 0; i < 4; i++) begin
                        result_merge[(8*i)+:8] = (mask_sew8[i]) ? second_operand[(8*i)+:8] : first_operand[(8*i)+:8];
                    end
                end
                EW16: begin
                    for (int i = 0; i < 2; i++) begin
                        result_merge[(16*i)+:16] = (mask_sew16[i]) ? second_operand[(16*i)+:16] : first_operand[(16*i)+:16];
                    end
                end
                default: begin
                    result_merge = (mask_sew32) ? second_operand : first_operand;
                end
            endcase
        end
    end
    else begin : v_merge_gen_off
        assign result_merge = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Compare
//////////////////////////////////////////////////////////////////////////////

    logic [3:0] equal_8b,  greater_than_8b,  greater_than_signed_8b,  result_comparison_8b;
    logic [1:0] equal_16b, greater_than_16b, greater_than_signed_16b, result_comparison_16b;
    logic       equal_32b, greater_than_32b, greater_than_signed_32b, result_comparison_32b;

    always_comb begin
        equal_32b               =         first_operand  ==         second_operand;
        greater_than_32b        =         first_operand  >          second_operand;
        greater_than_signed_32b = $signed(first_operand) >  $signed(second_operand);

        for (int i = 0; i < 2; i++) begin
            equal_16b[i]               =         first_operand[(16*i)+:16]  ==         second_operand[(16*i)+:16];
            greater_than_16b[i]        =         first_operand[(16*i)+:16]  >          second_operand[(16*i)+:16];
            greater_than_signed_16b[i] = $signed(first_operand[(16*i)+:16]) >  $signed(second_operand[(16*i)+:16]);
        end

        for (int i = 0; i < 4; i++) begin
            equal_8b[i]                =         first_operand[(8*i)+:8]  ==         second_operand[(8*i)+:8];
            greater_than_8b[i]         =         first_operand[(8*i)+:8]  >          second_operand[(8*i)+:8];
            greater_than_signed_8b[i]  = $signed(first_operand[(8*i)+:8]) >  $signed(second_operand[(8*i)+:8]);
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

    always_comb begin
        unique case (vsew)
            EW8:     result_mask_o[(4*cycle)+:4] =        result_comparison_8b  & ({4{vm}} | mask_sew8);
            EW16:    result_mask_o[(2*cycle)+:2] = {2'b0, result_comparison_16b & ({2{vm}} | mask_sew16)};
            default: result_mask_o[(  cycle)   ] = {3'b0, result_comparison_32b & ({1{vm}} | mask_sew32)};
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Min/Max
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] result_minu;
    logic [31:0] result_min;
    logic [31:0] result_maxu;
    logic [31:0] result_max;

    if (V_MINMAX_ON) begin : v_minmax_gen_on
        always_comb begin
            unique case (vsew)
                EW8: begin
                    for (int i = 0; i < 4; i++) begin
                        result_minu[(8*i)+:8] = (greater_than_8b[i])        ? second_operand[(8*i)+:8] : first_operand [(8*i)+:8];
                        result_min [(8*i)+:8] = (greater_than_signed_8b[i]) ? second_operand[(8*i)+:8] : first_operand [(8*i)+:8];
                        result_maxu[(8*i)+:8] = (greater_than_8b[i])        ? first_operand [(8*i)+:8] : second_operand[(8*i)+:8];
                        result_max [(8*i)+:8] = (greater_than_signed_8b[i]) ? first_operand [(8*i)+:8] : second_operand[(8*i)+:8];
                    end
                end

                EW16: begin
                    for (int i = 0; i < 2; i++) begin
                        result_minu[(16*i)+:16] = (greater_than_16b[i])         ? second_operand[(16*i)+:16] : first_operand [(16*i)+:16];
                        result_min [(16*i)+:16] = (greater_than_signed_16b[i])  ? second_operand[(16*i)+:16] : first_operand [(16*i)+:16];
                        result_maxu[(16*i)+:16] = (greater_than_16b[i])         ? first_operand [(16*i)+:16] : second_operand[(16*i)+:16];
                        result_max [(16*i)+:16] = (greater_than_signed_16b[i])  ? first_operand [(16*i)+:16] : second_operand[(16*i)+:16];
                    end
                end

                default: begin
                    result_minu = (greater_than_32b)        ? second_operand : first_operand;
                    result_min  = (greater_than_signed_32b) ? second_operand : first_operand;
                    result_maxu = (greater_than_32b)        ? first_operand  : second_operand;
                    result_max  = (greater_than_signed_32b) ? first_operand  : second_operand;
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
// Multiplication 32 bits
//////////////////////////////////////////////////////////////////////////////
    logic [31:0] mult_op_a_32b;
    logic [31:0] mult_op_b_32b;
    logic [31:0] mult_result_32b;

    logic widening_instruction;
    logic mult_low;

    always_comb begin
        unique case (vsew)
            EW8: begin
                mult_op_a_32b = {{24{first_operand [7]  & mult_signed_mode[0]}}, first_operand [7:0]};
                mult_op_b_32b = {{24{second_operand[7]  & mult_signed_mode[1]}}, second_operand[7:0]};
            end
            EW16: begin
                mult_op_a_32b = {{16{first_operand [15] & mult_signed_mode[0]}}, first_operand [15:0]};
                mult_op_b_32b = {{16{second_operand[15] & mult_signed_mode[1]}}, second_operand[15:0]};
            end
            default: begin
                mult_op_a_32b = first_operand;
                mult_op_b_32b = second_operand;
            end
        endcase
    end

    assign widening_instruction = (vector_operation_i inside {VWMUL, VWMULU, VWMULSU});

    assign mult_low = (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB} || widening_instruction);

    mul mul32b (
        .clk             (clk),
        .reset_n         (reset_n),
        .stall           (1'b0),
        .first_operand_i (mult_op_a_32b),
        .second_operand_i(mult_op_b_32b),
        .signed_mode_i   (mult_signed_mode),
        .enable_i        (mult_enable),
        .mul_low_i       (mult_low),
        .single_cycle_i  (vsew inside {EW8, EW16} || widening_instruction),
        .hold_o          (hold_mult),
        .result_o        (mult_result_32b)
    );

//////////////////////////////////////////////////////////////////////////////
// Multiplication 16 bits
//////////////////////////////////////////////////////////////////////////////
    logic [15:0]      mult_op_a_16b;
    logic [15:0]      mult_op_b_16b;
    logic [1:0][31:0] mult_result_16b;

    always_comb begin
        if (vsew == EW8) begin
            mult_op_a_16b = {{8{first_operand [15] & mult_signed_mode[0]}}, first_operand [15:8]};
            mult_op_b_16b = {{8{second_operand[15] & mult_signed_mode[1]}}, second_operand[15:8]};
        end
        else begin
            mult_op_a_16b = first_operand [31:16];
            mult_op_b_16b = second_operand[31:16];
        end
    end

    assign mult_result_16b[0] = {mult_result_32b[31:0]};

    mulNbits #(
        .N(16)
    ) mul16b (
        .first_operand_i (mult_op_a_16b),
        .second_operand_i(mult_op_b_16b),
        .signed_mode_i   (mult_signed_mode),
        .result_o        (mult_result_16b[1])
    );

//////////////////////////////////////////////////////////////////////////////
// Multiplication 8 bits
//////////////////////////////////////////////////////////////////////////////
    logic [3:0][15:0] mult_result_8b;

    assign mult_result_8b[0] = {mult_result_32b   [15:0]};
    assign mult_result_8b[1] = {mult_result_16b[1][15:0]};

    generate
        for (genvar i_mul8b = 2; i_mul8b < 4; i_mul8b++) begin : MUL8B_LOOP
            mulNbits #(
                .N(8)
            ) mul8b (
                .first_operand_i (first_operand [(8*i_mul8b)+:8]),
                .second_operand_i(second_operand[(8*i_mul8b)+:8]),
                .signed_mode_i   (mult_signed_mode),
                .result_o        (mult_result_8b[i_mul8b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication Demux
//////////////////////////////////////////////////////////////////////////////
    logic [63:0] result_mult;
    logic [31:0] result_mult_r;
    logic [31:0] third_operand_r;

    always_comb begin
        result_mult = '0;
        unique case (vsew)
            EW8:
                for (int i = 0; i < 4; i++)
                    if (widening_instruction)
                        result_mult[(16*i)+:16] = mult_result_8b[i][15:0];
                    else if (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB})
                        result_mult[(8*i)+:8]   = mult_result_8b[i][7:0];
                    else
                        result_mult[(8*i)+:8]   = mult_result_8b[i][15:8];

            EW16:
                for (int i = 0; i < 2; i++)
                    if (widening_instruction)
                        result_mult[(32*i)+:32] = mult_result_16b[i][31:0];
                    else if (vector_operation_i inside {VMUL, VMACC, VNMSAC, VMADD, VNMSUB})
                        result_mult[(16*i)+:16] = mult_result_16b[i][15:0];
                    else
                        result_mult[(16*i)+:16] = mult_result_16b[i][31:16];

            default:
                result_mult[31:0] = mult_result_32b;
        endcase
    end

    always_ff @(posedge clk) begin
        if (!hold_mult) begin
            result_mult_r   <= result_mult[31:0];
            third_operand_r <= third_operand;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Division Common
//////////////////////////////////////////////////////////////////////////////

    logic [3:0] hold_div_8b;
    logic [1:0] hold_div_16b;
    logic       hold_div_32b;

    logic        div_signed;
    logic [31:0] result_div;
    logic [31:0] result_rem;

    logic  div_enable_8b;
    logic  div_enable_16b;
    logic  div_enable_32b;

    if (V_DIV_ON) begin : v_div_common_gen_on
        assign div_enable_8b  = (div_enable && vsew == EW8);
        assign div_enable_16b = (div_enable && vsew == EW16);
        assign div_enable_32b = (div_enable && vsew == EW32);
        assign div_signed     = (vector_operation_i inside {VDIV, VREM});
        assign hold_div       = (|hold_div_8b) | (|hold_div_16b) | (|hold_div_32b);
    end
    else begin : v_div_common_gen_off
        assign div_enable_8b  = 1'b0;
        assign div_enable_16b = 1'b0;
        assign div_enable_32b = 1'b0;
        assign div_signed     = 1'b0;
        assign hold_div       = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// Division 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic [3:0][7:0] div_result_8b;
    logic [3:0][7:0] rem_result_8b;

    generate
        for (genvar i_div8b = 0; i_div8b < 4; i_div8b++) begin : DIV8B_LOOP
            if (V_DIV_ON) begin : v_div_8b_gen_on
                div #(
                    .N(8)
                ) div8b (
                    .clk              (clk),
                    .reset_n          (reset_n),
                    .first_operand_i  (first_operand [(8*i_div8b)+:8]),
                    .second_operand_i (second_operand[(8*i_div8b)+:8]),
                    .enable_i         (div_enable_8b),
                    .signed_i         (div_signed),
                    .hold_o           (hold_div_8b  [i_div8b]),
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

    logic [1:0][15:0] div_result_16b;
    logic [1:0][15:0] rem_result_16b;

    generate
        for (genvar i_div16b = 0; i_div16b < 2; i_div16b++) begin : DIV16B_LOOP
            if (V_DIV_ON) begin : v_div_16b_gen_on
                div #(
                    .N(16)
                ) div16b (
                    .clk              (clk),
                    .reset_n          (reset_n),
                    .first_operand_i  (first_operand [(16*i_div16b)+:16]),
                    .second_operand_i (second_operand[(16*i_div16b)+:16]),
                    .enable_i         (div_enable_16b),
                    .signed_i         (div_signed),
                    .hold_o           (hold_div_16b  [i_div16b]),
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

    logic [31:0] div_result_32b;
    logic [31:0] rem_result_32b;

    if (V_DIV_ON) begin : v_div_32b_gen_on
        div #(
            .N(32)
        ) div32b (
            .clk              (clk),
            .reset_n          (reset_n),
            .first_operand_i  (first_operand),
            .second_operand_i (second_operand),
            .enable_i         (div_enable_32b),
            .signed_i         (div_signed),
            .hold_o           (hold_div_32b),
            .div_result_o     (div_result_32b),
            .rem_result_o     (rem_result_32b)
        );
    end
    else begin : v_div_32b_gen_off
        assign div_result_32b = '0;
        assign rem_result_32b = '0;
        assign hold_div_32b   = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Division Demux
//////////////////////////////////////////////////////////////////////////////

    if (V_DIV_ON) begin : v_div_mux_gen_on
        always_comb begin
            unique case (vsew)
                EW8: begin
                    for (int i = 0; i < 4; i++) begin
                        result_div[(8*i)+:8] = div_result_8b[i];
                        result_rem[(8*i)+:8] = rem_result_8b[i];
                    end
                end
                EW16: begin
                    for (int i = 0; i < 2; i++) begin
                        result_div[(16*i)+:16] = div_result_16b[i];
                        result_rem[(16*i)+:16] = rem_result_16b[i];
                    end
                end
                default: begin
                    result_div = div_result_32b;
                    result_rem = rem_result_32b;
                end
            endcase
        end
    end else begin : v_div_mux_gen_off
        assign result_div = '0;
        assign result_rem = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Adder
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] subtraend;
    logic [31:0] subtraend_neg;
    logic [31:0] subtraend_8b;
    logic [31:0] subtraend_16b;
    logic [31:0] subtraend_32b;
    logic [31:0] summand_1;
    logic [31:0] summand_2;
    logic [31:0] summand_2_int;
    /* verilator lint_off UNOPTFLAT */
    logic [ 3:0] adder_carry;
    /* verilator lint_on UNOPTFLAT */
    logic [ 8:0] result_add_bytes[3:0];
    logic [31:0] result_add;

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
        subtraend_32b = subtraend_neg + 1'b1;
        for (int i = 0; i < 2; i++)
            subtraend_16b[(16*i)+:16] = subtraend_neg[(16*i)+:16] + 1'b1;
        for (int i = 0; i < 4; i++)
            subtraend_8b[(8*i)+:8] = subtraend_neg[(8*i)+:8] + 1'b1;
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

    assign summand_2_int = (vector_operation_i inside {VMACC, VMADD})
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
        for (int i = 0; i < 4; i++) begin
            case (vsew)
                EW16:    adder_carry[i] = (i%2 == 0) ? 1'b0 : result_add_bytes[i-1][8];
                EW32:    adder_carry[i] = (i%4 == 0) ? 1'b0 : result_add_bytes[i-1][8];
                default: adder_carry[i] = 1'b0;
            endcase
        end
    end

    always_comb begin
        for (int i = 0; i < 4; i++) begin
            result_add_bytes[i]  = {1'b0, summand_1[(8*i)+:8]} + {1'b0, summand_2[(8*i)+:8]} + adder_carry[i];
        end
    end

    always_comb begin
        for (int i = 0; i < 4; i++) begin
            result_add[(8*i)+:8] = result_add_bytes[i][7:0];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Hold generation
//////////////////////////////////////////////////////////////////////////////

    assign hold_o = hold_mult | hold_div | hold_llen;

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        unique case(vector_operation_i)
            VAND:              result_o[(32*cycle)+:32] <= result_and;
            VOR:               result_o[(32*cycle)+:32] <= result_or;
            VXOR:              result_o[(32*cycle)+:32] <= result_xor;
            VSLL:              result_o[(32*cycle)+:32] <= result_sll;
            VSRL:              result_o[(32*cycle)+:32] <= result_srl;
            VSRA:              result_o[(32*cycle)+:32] <= result_sra;
            VMIN:              result_o[(32*cycle)+:32] <= result_min;
            VMINU:             result_o[(32*cycle)+:32] <= result_minu;
            VMAX:              result_o[(32*cycle)+:32] <= result_max;
            VMAXU:             result_o[(32*cycle)+:32] <= result_maxu;
            VMERGE:            result_o[(32*cycle)+:32] <= result_merge;
            VDIV, VDIVU:       result_o[(32*cycle)+:32] <= result_div;
            VREM, VREMU:       result_o[(32*cycle)+:32] <= result_rem;
            VMACC, VNMSAC,
            VMADD, VNMSUB:     result_o[(32*cycle_r)+:32] <= result_add;
            default:           result_o[(32*cycle)  +:32] <= result_add;
        endcase
    end

    always_ff @(posedge clk) begin
        if (!hold_widening)
            result_mult_o[(64*cycle)+:64] <= result_mult;
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
