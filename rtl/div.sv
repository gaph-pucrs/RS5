`include "RS5_pkg.sv"

module div
    import RS5_pkg::*;
#(
    parameter int N = 32
) (
    input   logic         clk,
    input   logic         reset_n,

    input   logic [N-1:0] first_operand_i,
    input   logic [N-1:0] second_operand_i,

    input   logic         enable_i,
    input   logic         signed_i,

    output  logic         hold_o,

    output  logic [N-1:0] div_result_o,
    output  logic [N-1:0] rem_result_o
);

    localparam COUNTER_WIDTH = $clog2(N);

    logic [COUNTER_WIDTH-1:0] counter;

    logic           sign_a, sign_b;
    logic           change_sign;

    logic [N-1:0]   a_unsig, b_unsig;

    logic [N-1:0]   quo, next_quo;
    logic [N:0]     acc, next_acc;

    div_states_e    state;
    logic           start, busy, valid_result;
    logic           divide_by_zero, divide_by_one, overflow;

    logic [N-1:0]   div_result;

//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    assign divide_by_zero   = (second_operand_i == '0);
    assign divide_by_one    = (second_operand_i ==  1);
    assign overflow         = (second_operand_i == '1 && first_operand_i == (1 << 31) && signed_i == 1'b1);

    assign start            = (enable_i == 1'b1 && busy == 1'b0 && valid_result == 1'b0);

//////////////////////////////////////////////////////////////////////////////
// Sign Control
//////////////////////////////////////////////////////////////////////////////

    assign sign_a = first_operand_i [N-1] & signed_i;
    assign sign_b = second_operand_i[N-1] & signed_i;

    assign change_sign = (sign_a ^ sign_b);

//////////////////////////////////////////////////////////////////////////////
// Div Operations
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (acc >= {1'b0, b_unsig}) begin
            next_acc = acc - b_unsig;
            {next_acc, next_quo} = {next_acc[N-1:0], quo, 1'b1};
        end else begin
            {next_acc, next_quo} = {acc, quo} << 1;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state       <= D_IDLE;
            busy        <= 1'b0;
            valid_result<= 1'b0;
            acc         <= '0;
            quo         <= '0;
            div_result  <= '0;
            a_unsig     <= '0;
            b_unsig     <= '0;
            counter     <= '0;
        end
        else if (!enable_i) begin
            valid_result   <= 1'b0;
        end
        else begin
            case (state)

                D_IDLE: begin
                    if (start) begin
                        if (divide_by_zero | divide_by_one | overflow) begin
                            state        <= D_IDLE;
                            busy         <= 1'b0;
                            valid_result <= 1'b1;
                        end
                        else begin
                            state        <= D_INIT;
                            busy         <= 1'b1;
                            valid_result <= 1'b0;
                            a_unsig      <= (sign_a)
                                            ? -first_operand_i[N-1:0]
                                            :  first_operand_i[N-1:0];
                            b_unsig      <= (sign_b)
                                            ? -second_operand_i[N-1:0]
                                            :  second_operand_i[N-1:0];
                        end
                    end
                    else begin
                        valid_result <= 1'b0;
                    end
                end

                D_INIT: begin
                    state       <= D_CALC;
                    counter     <= '0;
                    {acc, quo}  <= {{N{1'b0}}, a_unsig, 1'b0};
                end

                D_CALC: begin
                    counter <= counter + 1'b1;
                    acc     <= next_acc;
                    quo     <= next_quo;
                    if (counter == COUNTER_WIDTH'(N-1)) state <= D_SIGN;
                end

                D_SIGN: begin
                    state        <= D_IDLE;
                    busy         <= 1'b0;
                    valid_result <= 1'b1;

                    if (quo != 0)
                        div_result  <=  (change_sign)
                                        ? {1'b1, -quo[N-2:0]}
                                        : {1'b0,  quo[N-2:0]};
                    else
                        div_result  <= '0;
                end

            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (divide_by_zero)
            div_result_o  = '1;
        else if (divide_by_one)
            div_result_o  = first_operand_i;
        else
            div_result_o  = (overflow) ? first_operand_i : div_result;
    end

    always_comb begin
        if (divide_by_zero)
            rem_result_o = first_operand_i;
        else if (overflow || divide_by_one)
            rem_result_o = '0;
        else if (sign_a)
            rem_result_o = {1'b1, -acc[N-1:1]};
        else if (div_result == '0)
            rem_result_o = first_operand_i;
        else
            rem_result_o = {1'b0, acc[N-1:1]};
    end

    assign hold_o = (start | busy);

endmodule
