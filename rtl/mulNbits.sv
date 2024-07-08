module mulNbits
#(
    parameter int N = 8
)
(
    input   logic [N-1:0]     first_operand_i,
    input   logic [N-1:0]     second_operand_i,
    input   logic [1:0]       signed_mode_i,

    output  logic [(2*N)-1:0] result_o
);

    logic [N:0]       op_a;
    logic [N:0]       op_b;
    logic             sign_a;
    logic             sign_b;
    /* verilator lint_off UNUSEDSIGNAL */
    logic [(2*N)+1:0] mac_result;
    /* verilator lint_on UNUSEDSIGNAL */

    assign  sign_a = (first_operand_i [N-1] & signed_mode_i[0]),
            sign_b = (second_operand_i[N-1] & signed_mode_i[1]);

    assign  op_a  = {sign_a, first_operand_i},
            op_b  = {sign_b, second_operand_i};

    assign mac_result  = $signed(op_a) * $signed(op_b);

    assign result_o = mac_result[(2*N)-1:0];

endmodule
