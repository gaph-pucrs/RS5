`include "RS5_pkg.sv"

module div
    import RS5_pkg::*;
(
    input   logic        clk,
    input   logic        reset_n,

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,
    input   iType_e      instruction_operation_i,

    output  logic        hold_o,

    output  logic [31:0] div_result_o, 
    output  logic [31:0] rem_result_o
);

    div_states_e    state;
    logic [ 4:0]    counter;

    logic           sign_a, sign_b;
    logic [ 1:0]    signed_mode;
    logic           change_sign;

    logic [31:0]    a_unsig, b_unsig;

    logic [31:0]    quo, next_quo;
    logic [32:0]    acc, next_acc;

    logic           start, busy, valid_result;
    logic           divide_by_zero, divide_by_one, overflow;

    logic [31:0]    div_result;

//////////////////////////////////////////////////////////////////////////////
// Control
//////////////////////////////////////////////////////////////////////////////

    assign divide_by_zero   = (second_operand_i == '0);
    assign divide_by_one    = (second_operand_i ==  1);
    assign overflow         = (second_operand_i == '1 && first_operand_i == 32'h80000000 && signed_mode == 2'b11);
    
    assign start            = (instruction_operation_i inside {DIV, DIVU, REM, REMU} && busy == 1'b0 && valid_result == 1'b0);

//////////////////////////////////////////////////////////////////////////////
// Sign Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_operation_i)
            DIV, REM: signed_mode = 2'b11;
            default:  signed_mode = 2'b00;
        endcase
    end

    assign sign_a = first_operand_i [31] & signed_mode[0];
    assign sign_b = second_operand_i[31] & signed_mode[1];

    assign change_sign = (sign_a ^ sign_b);

//////////////////////////////////////////////////////////////////////////////
// Div Operations
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (acc >= {1'b0, b_unsig}) begin
            next_acc = acc - b_unsig;
            {next_acc, next_quo} = {next_acc[31:0], quo, 1'b1};
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
        else if (!(instruction_operation_i inside {DIV, DIVU, REM, REMU})) begin
            valid_result   <= 1'b0;
        end
        else begin
            case (state)

                D_IDLE: begin
                    if (start == 1'b1) begin
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
                                            ? -first_operand_i[31:0] 
                                            :  first_operand_i[31:0];
                            b_unsig      <= (sign_b) 
                                            ? -second_operand_i[31:0] 
                                            :  second_operand_i[31:0];
                        end
                    end
                end

                D_INIT: begin
                    state       <= D_CALC;
                    counter     <= '0;
                    {acc, quo}  <= {32'h0, a_unsig, 1'b0};
                end

                D_CALC: begin
                    counter <= counter + 1'b1;
                    acc     <= next_acc;
                    quo     <= next_quo;
                    if (counter == 5'd31) state <= D_SIGN;
                end

                D_SIGN: begin
                    state        <= D_IDLE;
                    busy         <= 1'b0;
                    valid_result <= 1'b1;
                    
                    if (quo != 0)
                        div_result  <=  (change_sign) 
                                        ? {1'b1, -quo} 
                                        : {1'b0, quo};
                    else
                        div_result  <= '0;
                end

                default: state <= state;
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (divide_by_zero)
            div_result_o  = 32'hFFFFFFFF;
        else if (divide_by_one)
            div_result_o  = first_operand_i;
        else
            div_result_o  = (overflow) ? first_operand_i : div_result;
    end

    always_comb begin
        if (divide_by_zero) 
            rem_result_o = first_operand_i;
        else if (overflow || divide_by_one)
            rem_result_o = 32'h0;
        else if (sign_a)
            rem_result_o = {1'b1, -acc[31:1]};
        else if (div_result == 32'h0)
            rem_result_o = first_operand_i;
        else
            rem_result_o = {1'b0, acc[31:1]};
    end

    assign hold_o = (start | busy);

endmodule