module muldiv 
    import RS5_pkg::*;
(
    input   logic        clk,
    input   logic        reset,

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,
    input   iType_e      instruction_operation_i,

    output  logic        hold_o,

    output  logic [63:0] mul_result_o, 
    output  logic [63:0] mulh_result_o, 
    output  logic [63:0] mulhsu_result_o, 
    output  logic [31:0] div_result_o, 
    output  logic [31:0] divu_result_o, 
    output  logic [31:0] rem_result_o, 
    output  logic [31:0] remu_result_o
);

    logic hold_mul, hold_div;

    assign hold_o = hold_mul | hold_div;

//////////////////////////////////////////////////////////////////////////////
// Mul Operations
//////////////////////////////////////////////////////////////////////////////

    mult_states_e   mul_state;
    logic           start_mul;

    assign start_mul = (mul_state == M_IDLE && instruction_operation_i inside {MUL, MULH, MULHU, MULHSU});

    assign hold_mul = ((mul_state == M_IDLE && start_mul == 1'b1) || mul_state == M_CALC);

    always_ff @(posedge clk ) begin
        if (reset == 1'b1) begin
            mul_state <= M_IDLE;
        end
        else if (start_mul == 1'b1) begin
            mul_state <= M_CALC;
        end
        else if (mul_state == M_CALC) begin
            mul_state <= M_DONE;
        end
        else begin
            mul_state <= M_IDLE;
        end
    end

`ifdef PROTO
    mult_unsigned_unsigned mult_unsig_unsig (
        .CLK(clk),              // input wire CLK
        .A(first_operand_i),    // input wire [31 : 0] A
        .B(second_operand_i),   // input wire [31 : 0] B
        .P(mul_result_o)        // output wire [63 : 0] P
    );

    mult_signed_signed mult_sig_sig (
        .CLK(clk),              // input wire CLK
        .A(first_operand_i),    // input wire [31 : 0] A
        .B(second_operand_i),   // input wire [31 : 0] B
        .P(mulh_result_o)       // output wire [63 : 0] P
    );

    mult_signed_unsigned mult_sig_unsig (
        .CLK(clk),              // input wire CLK
        .A(first_operand_i),    // input wire [31 : 0] A
        .B(second_operand_i),   // input wire [31 : 0] B
        .P(mulhsu_result_o)     // output wire [63 : 0] P
    );

`else
    logic signed [63:0]    mul_opa_signed, mul_opb_signed;
    logic        [63:0]    mul_opa, mul_opb;

    assign  mul_opa = first_operand_i,
            mul_opb = second_operand_i;
    
    assign  mul_opa_signed = $signed(first_operand_i),
            mul_opb_signed = $signed(second_operand_i);

    always_comb begin
        mul_result_o      = mul_opa        * mul_opb;
        mulh_result_o     = mul_opa_signed * mul_opb_signed;
        mulhsu_result_o   = mul_opa_signed * mul_opb;
    end
`endif

//////////////////////////////////////////////////////////////////////////////
// Div Operations Control
//////////////////////////////////////////////////////////////////////////////

    logic           a_signal, b_signal, signal_diff;
    logic [30:0]    a_unsig, b_unsig;
    logic [31:0]    divisor;
    logic [30:0]    quo_sig_div, quo_next_sig_div;
    logic [31:0]    acc_sig_div, acc_next_sig_div;
    logic [31:0]    quo_unsig_div, quo_next_unsig_div;
    logic [32:0]    acc_unsig_div, acc_next_unsig_div;
    logic           start_sig_div, busy_sig_div, done_sig_div, valid_sig_div;
    logic           start_unsig_div, busy_unsig_div, done_unsig_div, valid_unsig_div;
    logic           divide_by_zero, overflow;
    logic [31:0]    div_result;

    assign divide_by_zero   = second_operand_i == 0;
    assign start_sig_div    = instruction_operation_i inside {DIV, REM}   && busy_sig_div   == 0 && valid_sig_div   == 0;
    assign start_unsig_div  = instruction_operation_i inside {DIVU, REMU} && busy_unsig_div == 0 && valid_unsig_div == 0;

    assign hold_div = (start_unsig_div | busy_unsig_div) || (start_sig_div | busy_sig_div);

    always_comb begin
        div_result_o    = (divide_by_zero) 
                        ? -1  
                        : div_result;

        divu_result_o   = (divide_by_zero)
                        ? 2**32 -1
                        : quo_next_unsig_div;

        remu_result_o   = (divide_by_zero) 
                        ? first_operand_i
                        : acc_next_unsig_div[32:1];
    end

    always_comb begin
        if (divide_by_zero) begin
            rem_result_o = first_operand_i;
        end
        else if (overflow) begin
            rem_result_o = 0;
        end
        else if (a_signal) begin
            rem_result_o = {1'b1, -acc_sig_div[31:1]};
        end
        else begin
            rem_result_o = {1'b0, acc_sig_div[31:1]};
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Unsigned Div Operations
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (acc_unsig_div >= {1'b0, divisor}) begin
            acc_next_unsig_div = acc_unsig_div - divisor;
            {acc_next_unsig_div, quo_next_unsig_div} = {acc_next_unsig_div[31:0], quo_unsig_div, 1'b1};
        end else begin
            {acc_next_unsig_div, quo_next_unsig_div} = {acc_unsig_div, quo_unsig_div} << 1;
        end
    end

    always_ff @(posedge clk) begin
        logic [4:0] i;

        done_unsig_div <= 0;
        if (reset) begin
            busy_unsig_div    <= 0;
            done_unsig_div    <= 0;
            valid_unsig_div   <= 0;
            acc_unsig_div     <= '0;
            quo_unsig_div     <= '0;
        end 
        else if (!(instruction_operation_i inside {DIVU, REMU})) begin
            valid_unsig_div <= 0;
        end 
        else if (start_unsig_div) begin
            valid_unsig_div                     <= 0;
            i                                   <= 0;
            if (divide_by_zero) begin
                busy_unsig_div                  <= 0;
                done_unsig_div                  <= 1;
                valid_unsig_div                 <= 1;
            end else begin
                busy_unsig_div                  <= 1;
                divisor                         <= second_operand_i;
                {acc_unsig_div, quo_unsig_div}  <= {{32{1'b0}}, first_operand_i, 1'b0};
            end
        end 
        else if (busy_unsig_div) begin
            if (i == 31) begin
                busy_unsig_div    <= 0;
                done_unsig_div    <= 1;
                valid_unsig_div   <= 1;
            end 
            else begin
                i                 <= i + 1;
                acc_unsig_div     <= acc_next_unsig_div;
                quo_unsig_div     <= quo_next_unsig_div;
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Signed Div Operations
//////////////////////////////////////////////////////////////////////////////

    assign  a_signal = first_operand_i[31],
            b_signal = second_operand_i[31];

    always_comb begin
        if (acc_sig_div >= {1'b0, b_unsig}) begin
            acc_next_sig_div = acc_sig_div - b_unsig;
            {acc_next_sig_div, quo_next_sig_div} = {acc_next_sig_div[30:0], quo_sig_div, 1'b1};
        end else begin
            {acc_next_sig_div, quo_next_sig_div} = {acc_sig_div, quo_sig_div} << 1;
        end
    end

    enum {IDLE, INIT, CALC, SIGN} state;
    always_ff @(posedge clk) begin
        logic [4:0] i;

        done_sig_div        <= 0;
        if (reset) begin
            state           <= IDLE; 
            busy_sig_div    <= 0;
            done_sig_div    <= 0;
            valid_sig_div   <= 0;
            acc_sig_div     <= '0;
            quo_sig_div     <= '0;
        end 
        else if (!(instruction_operation_i inside {DIV, REM})) begin
            valid_sig_div   <= 0;
        end
        else begin
            case (state)

                INIT: begin
                    state                       <= CALC;
                    overflow                    <= 0;
                    i                           <= 0;
                    {acc_sig_div, quo_sig_div}  <= {{31{1'b0}}, a_unsig, 1'b0};
                end

                CALC: begin
                    if (i == 30 && quo_next_sig_div[30] != 0) begin
                        state           <= IDLE;
                        busy_sig_div    <= 0;
                        done_sig_div    <= 1;
                        overflow        <= 1;
                    end
                    else begin
                        if (i == 30) begin
                            state   <= SIGN;
                        end 
                        i           <= i + 1;
                        acc_sig_div <= acc_next_sig_div;
                        quo_sig_div <= quo_next_sig_div;
                    end
                end

                SIGN: begin
                    state           <= IDLE;
                    busy_sig_div    <= 0;
                    done_sig_div    <= 1;
                    valid_sig_div   <= 1;
                    
                    if (overflow) begin
                        div_result  <= first_operand_i;
                    end
                    else if (quo_sig_div != 0) begin
                        div_result  <= (signal_diff) 
                                        ? {1'b1, -quo_sig_div} 
                                        : {1'b0, quo_sig_div};
                    end
                    else begin
                        div_result  <= '0;
                    end
                end

                default: begin
                    if (start_sig_div) begin
                        valid_sig_div       <= 0;
                        if (divide_by_zero) begin
                            state           <= IDLE;
                            busy_sig_div    <= 0;
                            done_sig_div    <= 1;
                            overflow        <= 0;
                            valid_sig_div   <= 1;
                        end 
                        else if (second_operand_i == 32'h80000000) begin
                            state           <= IDLE;
                            busy_sig_div    <= 0;
                            done_sig_div    <= 1;
                            overflow        <= 1;
                            valid_sig_div   <= 1;
                        end 
                        else begin
                            state                       <= INIT;
                            busy_sig_div                <= 1;
                            overflow                    <= 0;
                            signal_diff                 <= (a_signal ^ b_signal);
                            a_unsig                     <=  (a_signal) 
                                                            ? -first_operand_i[30:0] 
                                                            : first_operand_i[30:0];
                            b_unsig                     <= (b_signal) 
                                                            ? -second_operand_i[30:0] 
                                                            : second_operand_i[30:0];
                            {acc_sig_div, quo_sig_div}  <= {{32{1'b0}}, first_operand_i, 1'b0};
                        end
                    end
                end
            endcase
        end
    end

endmodule