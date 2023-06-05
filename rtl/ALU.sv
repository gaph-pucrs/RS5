module ALU 
    import my_pkg::*;
(
    input   logic [31:0]        opA_i,
    input   logic [31:0]        opB_i,
    input   logic [31:0]        opC_i,
    input   logic [31:0]        opD_i,
    input   iType_e             operation_i,

    output  logic [31:0]        result_o,
    output  logic               jump_o
);

    logic [31:0] opB_int;
    logic [31:0] opA_adder, opB_adder;
    logic [31:0] sum;
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

    logic is_cond_branch;
    assign is_cond_branch = executionUnit_e'(operation_i[5:3]) == BRANCH_UNIT && !(operation_i inside{JAL,JALR});

    assign opB_int = operation_i == SUB
                    ? -opB_i
                    :  opB_i;

    assign opA_adder = is_cond_branch 
                        ? opC_i
                        : opA_i;
    
    assign opB_adder = is_cond_branch 
                        ? opD_i
                        : opB_int;

    always_comb begin
        sum                     = opA_adder + opB_adder;
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
        greater_equal           = $signed(opA_i) >= $signed(opB_i);
        greater_equal_unsigned  = $unsigned(opA_i) >= $unsigned(opB_i);
    end

    always_comb begin
        case (operation_i)
            SLT:            result_o = {31'b0, less_than};
            SLTU:           result_o = {31'b0, less_than_unsigned};
            XOR:            result_o = logic_xor;
            OR:             result_o = logic_or;
            AND:            result_o = logic_and;
            SLL:            result_o = sll;
            SRL:            result_o = srl;
            SRA:            result_o = sra;
            JALR:           result_o = {sum[31:1], 1'b0};
            default:        result_o = sum;
        endcase
    end

    always_comb begin
        case (operation_i)
            BEQ:            jump_o = equal;
            BNE:            jump_o = not_equal;
            BLT:            jump_o = less_than;
            BLTU:           jump_o = less_than_unsigned;
            BGE:            jump_o = greater_equal;
            BGEU:           jump_o = greater_equal_unsigned;
            JAL, JALR:      jump_o = 1;
            default:        jump_o = 0;
        endcase
    end

endmodule
