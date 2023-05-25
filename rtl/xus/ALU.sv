module ALU 
    import my_pkg::*;
(
    input   logic [31:0]        opA_i,
    input   logic [31:0]        opB_i,
    input   operationType_e     op_i,

    output  logic               sum_o,
    output  logic [31:0]        result_o,
    output  logic               jump_o
);

    logic [31:0] sum;
    logic [31:0] subtraction;
    logic [31:0] logic_and;
    logic [31:0] logic_or;
    logic [31:0] logic_xor;
    logic [31:0] sll;
    logic [31:0] srl;
    logic [31:0] sra;

    logic less_than;
    logic less_than_unsigned;
    logic not_equal;
    logic equal;
    logic greater_equal;
    logic greater_equal_unsigned;

    always_comb begin
        sum                     = opA_i + opB_i;
        subtraction             = opA_i - opB_i;
        logic_and               = opA_i & opB_i;
        logic_or                = opA_i | opB_i;
        logic_xor               = opA_i ^ opB_i;
        sll                     = opA_i << opB_i[4:0];
        srl                     = opA_i >> opB_i[4:0];
        sra                     = $signed(opA_i) >>> opB_i[4:0];

        less_than               = $signed(opA_i) < $signed(opB_i);
        less_than_unsigned      = $unsigned(opA_i) < $unsigned(opB_i);
        not_equal               = opA_i != opB_i;
        equal                   = opA_i == opB_i;
        greater_equal           = $signed(first_operand_i) >= $signed(second_operand_i);
        greater_equal_unsigned  = $unsigned(first_operand_i) >= $unsigned(second_operand_i);
    end

    always_comb begin
        case (op_i)
            BEQ:        jump_o = equal;
            BNE:        jump_o = not_equal;
            BLT:        jump_o = less_than;
            BLTU:       jump_o = less_than_unsigned;
            BGE:        jump_o = greater_equal;
            BGEU:       jump_o = greater_equal_unsigned;
            JAL, JALR:  jump_o = 1;
            default:    jump_o = 0;
        endcase
    end

    assign sum_o = sum;

endmodule
