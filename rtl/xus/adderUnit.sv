//--------------------------------------------------------------------------------------------------
// ADDER UNIT
//--------------------------------------------------------------------------------------------------

module adderUnit 
    import my_pkg::*;
(
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   operationType_e     operation_i,

    output  logic [31:0]        result_o
);

    always_comb begin
        if (operation_i == OP3) begin
            if ($signed(first_operand_i) < $signed(second_operand_i)) begin
                result_o = 32'b1;
            end
            else begin
                result_o = 32'b0;
            end
        end
        else if (operation_i == OP2) begin
            if ($unsigned(first_operand_i) < $unsigned(second_operand_i)) begin
                result_o = 32'b1;
            end
            else begin
                result_o = 32'b0;
            end
        end
        else if (operation_i == OP1) begin
            result_o = first_operand_i - second_operand_i;
        end
        else begin
            result_o = first_operand_i + second_operand_i;
        end
    end
endmodule
