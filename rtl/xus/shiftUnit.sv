//--------------------------------------------------------------------------------------------------
// SHIFT UNIT
//--------------------------------------------------------------------------------------------------

module shiftUnit 
    import my_pkg::*;
(
    input   logic [31:0]        first_operand_i,
    input   logic [4:0]         second_operand_i,
    input   operationType_e     operation_i,

    output  logic [31:0]        result_o
);

    always_comb begin
        if (operation_i == OP0) begin  // SLL
            result_o = first_operand_i << second_operand_i;
        end
        else if (operation_i == OP1) begin // SRL
            result_o = first_operand_i >> second_operand_i;
        end
        else begin // SRA
            result_o = $signed(first_operand_i) >>> second_operand_i;
        end
    end
endmodule
