/*!\file vectorDiv.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 *
 * \brief
 * Partitioned divider of a 32 bit lane slice.
 *
 * \detailed
 * Divides the four bytes, the two halfwords or the word of the slice at
 * once, as SEW selects, with the radix 2 restoring algorithm of div.sv:
 * SEW iterations, SEW + 3 cycles in all. Adders and negators are shared by
 * all widths: each one is a single carry chain with a separator bit between
 * bytes, which either stops the carry at an element boundary (and injects
 * the carry-in of the next element) or lets it through inside an element.
 * Division by zero, by one and the signed overflow are resolved per
 * element at the output, as in div.sv, but the latency stays the same for
 * them. The handshake is the one of div.sv: hold_o is high from the cycle
 * enable_i rises until the cycle the result is ready.
 */

`include "../RS5_pkg.sv"

module vectorDiv
    import RS5_pkg::*;
(
    input  logic        clk,
    input  logic        reset_n,

    input  logic [31:0] first_operand_i,
    input  logic [31:0] second_operand_i,
    input  vew_e        vsew_i,

    input  logic        enable_i,
    input  logic        signed_i,

    output logic        hold_o,

    output logic [31:0] div_result_o,
    output logic [31:0] rem_result_o
);

//////////////////////////////////////////////////////////////////////////////
// Element layout
//////////////////////////////////////////////////////////////////////////////

    /* boundary[k]: bytes k and k+1 belong to different elements */
    logic [2:0] boundary;

    always_comb begin
        unique case (vsew_i)
            EW8:     boundary = 3'b111;
            EW16:    boundary = 3'b010;
            default: boundary = 3'b000;
        endcase
    end

    /* Each bit of a byte flag replicated to the bytes of its element, by */
    /* AND of the bytes (element_all) or by the flag of its top byte      */
    function automatic logic [3:0] element_all(input logic [3:0] f, input vew_e sew);
        logic [3:0] r;
        unique case (sew)
            EW8:     r = f;
            EW16:    r = {{2{f[3] & f[2]}}, {2{f[1] & f[0]}}};
            default: r = {4{&f}};
        endcase
        return r;
    endfunction

    function automatic logic [3:0] element_top(input logic [3:0] f, input vew_e sew);
        logic [3:0] r;
        unique case (sew)
            EW8:     r = f;
            EW16:    r = {{2{f[3]}}, {2{f[1]}}};
            default: r = {4{f[3]}};
        endcase
        return r;
    endfunction

    /* Conditional negation of each element: x ^ s + s, with s per byte. */
    /* A separator with a = b = s stops the carry and adds the carry-in  */
    /* of the next element; a = 1, b = 0 propagates it.                  */
    function automatic logic [31:0] negate(input logic [31:0] x, input logic [3:0] s,
                                           input logic [2:0] bnd);
        logic [31:0] xs;
        logic [2:0]  sa, sb;
        /* verilator lint_off UNUSEDSIGNAL */
        logic [34:0] sum;   /* the separator bits are dropped */
        /* verilator lint_on UNUSEDSIGNAL */
        for (int k = 0; k < 4; k++)
            xs[(8*k)+:8] = x[(8*k)+:8] ^ {8{s[k]}};
        for (int k = 0; k < 3; k++) begin
            sa[k] = bnd[k] ? s[k+1] : 1'b1;
            sb[k] = bnd[k] ? s[k+1] : 1'b0;
        end
        sum = {xs[31:24], sa[2], xs[23:16], sa[1], xs[15:8], sa[0], xs[7:0]}
            + {8'b0,      sb[2], 8'b0,       sb[1], 8'b0,      sb[0], 8'b0}
            + 35'(s[0]);
        return {sum[34:27], sum[25:18], sum[16:9], sum[7:0]};
    endfunction

//////////////////////////////////////////////////////////////////////////////
// Special cases, from the inputs as in div.sv
//////////////////////////////////////////////////////////////////////////////

    logic [2:0] a_zero_byte;   /* only below the top byte of an element */
    logic [3:0] b_zero_byte, b_one_byte, b_ones_byte, a_min_byte;
    logic [3:0] sign_a, sign_b;
    logic [3:0] divide_by_zero, divide_by_one, overflow;

    always_comb begin
        for (int k = 0; k < 3; k++)
            a_zero_byte[k] = (first_operand_i [(8*k)+:8] == 8'h00);
        for (int k = 0; k < 4; k++) begin
            b_zero_byte[k] = (second_operand_i[(8*k)+:8] == 8'h00);
            b_one_byte [k] = (second_operand_i[(8*k)+:8] == 8'h01);
            b_ones_byte[k] = (second_operand_i[(8*k)+:8] == 8'hFF);
            a_min_byte [k] = (first_operand_i [(8*k)+:8] == 8'h80);
        end
    end

    /* Per byte, for the element the byte belongs to */
    logic [3:0] b_one;
    logic [3:0] a_min;

    always_comb begin
        unique case (vsew_i)
            EW8: begin
                b_one = b_one_byte;
                a_min = a_min_byte;
            end
            EW16: begin
                b_one = {{2{b_zero_byte[3] & b_one_byte[2]}}, {2{b_zero_byte[1] & b_one_byte[0]}}};
                a_min = {{2{a_min_byte[3] & a_zero_byte[2]}}, {2{a_min_byte[1] & a_zero_byte[0]}}};
            end
            default: begin
                b_one = {4{&b_zero_byte[3:1] & b_one_byte[0]}};
                a_min = {4{a_min_byte[3] & (&a_zero_byte[2:0])}};
            end
        endcase
    end

    assign sign_a         = element_top({first_operand_i [31], first_operand_i [23],
                                         first_operand_i [15], first_operand_i [7]}, vsew_i)
                          & {4{signed_i}};
    assign sign_b         = element_top({second_operand_i[31], second_operand_i[23],
                                         second_operand_i[15], second_operand_i[7]}, vsew_i)
                          & {4{signed_i}};
    assign divide_by_zero = element_all(b_zero_byte, vsew_i);
    assign divide_by_one  = b_one;
    assign overflow       = element_all(b_ones_byte, vsew_i) & a_min & {4{signed_i}};

//////////////////////////////////////////////////////////////////////////////
// Datapath
//////////////////////////////////////////////////////////////////////////////

    /* The accumulator has SEW+1 bits per element, kept in a field of     */
    /* 10 bits per byte of the element (bits above SEW+1 stay zero); the  */
    /* top bit of the field is the sign of the difference.                */
    logic [39:0] acc, next_acc;
    logic [31:0] quo, next_quo;
    logic [31:0] b_unsig;

    logic [39:0] b_field;
    logic [39:0] diff;
    logic [3:0]  fits;      /* per byte: acc >= b in its element */

    always_comb begin
        b_field = '0;
        unique case (vsew_i)
            EW8:     for (int e = 0; e < 4; e++) b_field[(10*e)+:8]  = b_unsig[(8*e)+:8];
            EW16:    for (int e = 0; e < 2; e++) b_field[(20*e)+:16] = b_unsig[(16*e)+:16];
            default:                             b_field[31:0]       = b_unsig;
        endcase
    end

    /* acc - b per element: acc + ~b + 1, one carry chain with separators */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [42:0] diff_sum;   /* the separator bits are dropped */
    /* verilator lint_on UNUSEDSIGNAL */
    logic [39:0] b_inv;
    logic [2:0]  sep_b;

    assign b_inv = ~b_field;
    assign sep_b = boundary;

    assign diff_sum = {acc[39:30],   1'b1,     acc[29:20],   1'b1,     acc[19:10],   1'b1,     acc[9:0]}
                    + {b_inv[39:30], sep_b[2], b_inv[29:20], sep_b[1], b_inv[19:10], sep_b[0], b_inv[9:0]}
                    + 43'd1;
    assign diff     = {diff_sum[42:33], diff_sum[31:22], diff_sum[20:11], diff_sum[9:0]};

    assign fits = ~element_top({diff[39], diff[29], diff[19], diff[9]}, vsew_i);

    /* Shift of {acc, quo} with the new quotient bit, per element */
    always_comb begin
        next_acc = '0;
        next_quo = '0;
        unique case (vsew_i)
            EW8: begin
                for (int e = 0; e < 4; e++) begin
                    next_acc[(10*e)+:9] = {(fits[e] ? diff[(10*e)+:8] : acc[(10*e)+:8]), quo[(8*e)+7]};
                    next_quo[(8*e)+:8]  = {quo[(8*e)+:7], fits[e]};
                end
            end
            EW16: begin
                for (int e = 0; e < 2; e++) begin
                    next_acc[(20*e)+:17] = {(fits[2*e] ? diff[(20*e)+:16] : acc[(20*e)+:16]), quo[(16*e)+15]};
                    next_quo[(16*e)+:16] = {quo[(16*e)+:15], fits[2*e]};
                end
            end
            default: begin
                next_acc[32:0] = {(fits[0] ? diff[31:0] : acc[31:0]), quo[31]};
                next_quo       = {quo[30:0], fits[0]};
            end
        endcase
    end

    /* First shift: the top bit of each element of |a| enters the accumulator */
    logic [39:0] init_acc;
    logic [31:0] init_quo;

    always_comb begin
        init_acc = '0;
        init_quo = '0;
        unique case (vsew_i)
            EW8: begin
                for (int e = 0; e < 4; e++) begin
                    init_acc[10*e]      = quo[(8*e)+7];
                    init_quo[(8*e)+:8]  = {quo[(8*e)+:7], 1'b0};
                end
            end
            EW16: begin
                for (int e = 0; e < 2; e++) begin
                    init_acc[20*e]       = quo[(16*e)+15];
                    init_quo[(16*e)+:16] = {quo[(16*e)+:15], 1'b0};
                end
            end
            default: begin
                init_acc[0] = quo[31];
                init_quo    = {quo[30:0], 1'b0};
            end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    div_states_e state;
    logic [4:0]  counter;
    logic [4:0]  last_iteration;
    logic        busy, valid_result, start;

    always_comb begin
        unique case (vsew_i)
            EW8:     last_iteration = 5'd7;
            EW16:    last_iteration = 5'd15;
            default: last_iteration = 5'd31;
        endcase
    end

    assign start  = (enable_i && !busy && !valid_result);
    assign hold_o = (start || busy);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state        <= D_IDLE;
            busy         <= 1'b0;
            valid_result <= 1'b0;
            acc          <= '0;
            quo          <= '0;
            b_unsig      <= '0;
            counter      <= '0;
        end
        else if (!enable_i) begin
            valid_result <= 1'b0;
        end
        else begin
            unique case (state)
                D_IDLE: begin
                    valid_result <= 1'b0;
                    if (start) begin
                        state   <= D_INIT;
                        busy    <= 1'b1;
                        quo     <= negate(first_operand_i,  sign_a, boundary);
                        b_unsig <= negate(second_operand_i, sign_b, boundary);
                    end
                end

                D_INIT: begin
                    state   <= D_CALC;
                    counter <= '0;
                    acc     <= init_acc;
                    quo     <= init_quo;
                end

                D_CALC: begin
                    counter <= counter + 1'b1;
                    acc     <= next_acc;
                    quo     <= next_quo;
                    if (counter == last_iteration)
                        state <= D_SIGN;
                end

                default: begin
                    state        <= D_IDLE;
                    busy         <= 1'b0;
                    valid_result <= 1'b1;
                end
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////////////////////////

    /* The remainder is acc >> 1 of each element */
    logic [31:0] rem_unsig;
    logic [31:0] div_signed_result;
    logic [31:0] rem_signed_result;
    logic [3:0]  quo_zero_byte;
    logic [3:0]  quo_zero;

    always_comb begin
        rem_unsig = '0;
        unique case (vsew_i)
            EW8:     for (int e = 0; e < 4; e++) rem_unsig[(8*e)+:8]   = acc[((10*e)+1)+:8];
            EW16:    for (int e = 0; e < 2; e++) rem_unsig[(16*e)+:16] = acc[((20*e)+1)+:16];
            default:                             rem_unsig             = acc[32:1];
        endcase
    end

    assign div_signed_result = negate(quo,       sign_a ^ sign_b, boundary);
    assign rem_signed_result = negate(rem_unsig, sign_a,          boundary);

    always_comb begin
        for (int k = 0; k < 4; k++)
            quo_zero_byte[k] = (quo[(8*k)+:8] == 8'h00);
    end

    assign quo_zero = element_all(quo_zero_byte, vsew_i);

    always_comb begin
        for (int k = 0; k < 4; k++) begin
            if (divide_by_zero[k]) begin
                div_result_o[(8*k)+:8] = 8'hFF;
                rem_result_o[(8*k)+:8] = first_operand_i[(8*k)+:8];
            end
            else if (divide_by_one[k] || overflow[k]) begin
                div_result_o[(8*k)+:8] = first_operand_i[(8*k)+:8];
                rem_result_o[(8*k)+:8] = 8'h00;
            end
            else if (quo_zero[k]) begin
                div_result_o[(8*k)+:8] = 8'h00;
                rem_result_o[(8*k)+:8] = first_operand_i[(8*k)+:8];
            end
            else begin
                div_result_o[(8*k)+:8] = div_signed_result[(8*k)+:8];
                rem_result_o[(8*k)+:8] = rem_signed_result[(8*k)+:8];
            end
        end
    end

endmodule
