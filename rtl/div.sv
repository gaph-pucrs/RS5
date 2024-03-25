module div 
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
    parameter rv32_e        RV32        = RV32I
)
(
    input   logic        clk,
    input   logic        reset,

    input   logic [31:0] first_operand_i,
    input   logic [31:0] second_operand_i,
    input   iType_e      instruction_operation_i,

    output  logic        hold_o,

    output  logic [31:0] div_result_o, 
    output  logic [31:0] divu_result_o, 
    output  logic [31:0] rem_result_o, 
    output  logic [31:0] remu_result_o

    
);

    logic hold_div;
    assign hold_o =  hold_div;
    
//////////////////////////////////////////////////////////////////////////////
// Div Operations Control
//////////////////////////////////////////////////////////////////////////////

    if (RV32 == RV32M) begin
        div_states_e    div_state;
        logic           a_signal, b_signal, signal_diff;
        logic [30:0]    a_unsig, b_unsig;
        logic [31:0]    divisor;
        logic [30:0]    quo_sig_div, quo_next_sig_div;
        logic [31:0]    acc_sig_div, acc_next_sig_div;
        logic [31:0]    quo_unsig_div, quo_next_unsig_div;
        logic [32:0]    acc_unsig_div, acc_next_unsig_div;
        logic           start_sig_div, busy_sig_div, valid_sig_div;
        logic           start_unsig_div, busy_unsig_div, valid_unsig_div;
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
            if (divide_by_zero == 1'b1) begin
                rem_result_o = first_operand_i;
            end
            else if (overflow == 1'b1) begin
                rem_result_o = 0;
            end
            else if (a_signal == 1'b1) begin
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

            if (reset == 1'b1) begin
                busy_unsig_div    <= 0;
                valid_unsig_div   <= 0;
                acc_unsig_div     <= '0;
                quo_unsig_div     <= '0;
                divisor           <= second_operand_i;

            end 
            else if (!(instruction_operation_i inside {DIVU, REMU})) begin
                valid_unsig_div <= 0;
            end 
            else if (start_unsig_div == 1'b1) begin
                valid_unsig_div                     <= 0;
                i                                   <= 0;
                if (divide_by_zero == 1'b1) begin
                    busy_unsig_div                  <= 0;
                    valid_unsig_div                 <= 1;
                end else begin
                    busy_unsig_div                  <= 1;
                    divisor                         <= second_operand_i;
                    {acc_unsig_div, quo_unsig_div}  <= {{32{1'b0}}, first_operand_i, 1'b0};
                end
            end 
            else if (busy_unsig_div == 1'b1) begin
                if (i == 31) begin
                    busy_unsig_div    <= 0;
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

        always_ff @(posedge clk) begin
            logic [4:0] i;

            if (reset == 1'b1) begin
                div_state       <= D_IDLE; 
                busy_sig_div    <= 0;
                valid_sig_div   <= 0;
                acc_sig_div     <= '0;
                quo_sig_div     <= '0;
                overflow        <= 0;
                div_result      <= '0;
                a_unsig         <= '0;
                b_unsig         <= '0;
                signal_diff     <= 0;
            end 
            else if (!(instruction_operation_i inside {DIV, REM})) begin
                valid_sig_div   <= 0;
            end
            else begin
                case (div_state)

                    D_INIT: begin
                        div_state                   <= D_CALC;
                        overflow                    <= 0;
                        i                           <= 0;
                        {acc_sig_div, quo_sig_div}  <= {{31{1'b0}}, a_unsig, 1'b0};
                    end

                    D_CALC: begin
                        if (i == 30 && quo_next_sig_div[30] != 0) begin
                            div_state       <= D_IDLE;
                            busy_sig_div    <= 0;
                            overflow        <= 1;
                        end
                        else begin
                            if (i == 30) begin
                                div_state   <= D_SIGN;
                            end 
                            i           <= i + 1;
                            acc_sig_div <= acc_next_sig_div;
                            quo_sig_div <= quo_next_sig_div;
                        end
                    end

                    D_SIGN: begin
                        div_state       <= D_IDLE;
                        busy_sig_div    <= 0;
                        valid_sig_div   <= 1;
                        
                        if (overflow == 1'b1) begin
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
                        if (start_sig_div == 1'b1) begin
                            valid_sig_div       <= 0;
                            if (divide_by_zero == 1'b1) begin
                                div_state       <= D_IDLE;
                                busy_sig_div    <= 0;
                                overflow        <= 0;
                                valid_sig_div   <= 1;
                            end 
                            else if (second_operand_i == 32'h80000000) begin
                                div_state       <= D_IDLE;
                                busy_sig_div    <= 0;
                                overflow        <= 1;
                                valid_sig_div   <= 1;
                            end 
                            else begin
                                div_state                   <= D_INIT;
                                busy_sig_div                <= 1;
                                overflow                    <= 0;
                                signal_diff                 <= (a_signal ^ b_signal);
                                a_unsig                     <=  (a_signal) 
                                                                ? -first_operand_i[30:0] 
                                                                : first_operand_i[30:0];
                                b_unsig                     <= (b_signal) 
                                                                ? -second_operand_i[30:0] 
                                                                : second_operand_i[30:0];
                                {acc_sig_div, quo_sig_div}  <= {{30{1'b0}}, first_operand_i, 1'b0};
                            end
                        end
                    end
                endcase
            end
        end
    end
    else begin
        assign hold_div         = 1'b0;
        assign div_result_o     = '0;
        assign divu_result_o    = '0;
        assign rem_result_o     = '0;
        assign remu_result_o    = '0;
    end

endmodule
