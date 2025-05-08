/*!\file CarryBypass.sv
 * RS5 VERSION
 *
 * Fernando Gehm Moraes <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 *
 * \brief
 * Generic carry-bypass adder.
 */

module CarryBypassAdder #(
    parameter int NBITS = 32
)(
    input  logic             c_i,
    input  logic [NBITS-1:0] op_a_i,
    input  logic [NBITS-1:0] op_b_i,
    output logic             c_o,
    output logic [NBITS-1:0] sum_o
);

    logic [(NBITS/4):0] c;
    assign c[0] = c_i;
    
    for (genvar i = 0; i < (NBITS/4); i++) begin : gen_cba_adder4
        CarryBypass adder4 (
            .c_i   (c[i]          ),
            .op_a_i(op_a_i[i*4+:4]),
            .op_b_i(op_b_i[i*4+:4]),
            .c_o   (c[i+1]        ),
            .sum_o (sum_o[i*4+:4] )
        );
    end

    assign c_o = c[(NBITS/4)];

endmodule
