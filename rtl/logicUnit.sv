//--------------------------------------------------------------------------------------------------
// LOGIC UNIT
//--------------------------------------------------------------------------------------------------

module logicUnit 
    import my_pkg::*;
(
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   operationType_e     operation_i,
    output  logic [31:0]        result_o
);

    always_comb begin
        if (operation_i == OP0) begin
            result_o = first_operand_i ^ second_operand_i;
        end
        else if (operation_i == OP1) begin
            result_o = first_operand_i | second_operand_i;
        end
        else begin
            result_o = first_operand_i & second_operand_i;
        end
    end
endmodule
