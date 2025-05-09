/*!\file Adder.sv
 * RS5
 *
 * Fernando Gehm Moraes <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 *
 * \brief
 * Generic adder using 4-bit blocks
 */

`include "AdderPkg.sv"

module Adder
    import AdderPkg::*;
#(
    parameter add_type_t TYPE  = CARRY_BYPASS,
    parameter int        NBITS = 32
)
(
    input  logic             c_i,
    input  logic [NBITS-1:0] op_a_i,
    input  logic [NBITS-1:0] op_b_i,
    output logic             c_o,
    output logic [NBITS-1:0] sum_o
);

    logic [(NBITS/4):0] c;
    assign c[0] = c_i;
    
    for (genvar i = 0; i < (NBITS/4); i++) begin : gen_adder4
        if (TYPE == CARRY_BYPASS) begin : gen_bypass
            CarryBypassAdder adder4 (
                .c_i   (c[i]          ),
                .op_a_i(op_a_i[i*4+:4]),
                .op_b_i(op_b_i[i*4+:4]),
                .c_o   (c[i+1]        ),
                .sum_o (sum_o[i*4+:4] )
            );
        end
        else if (TYPE == CARRY_SELECT) begin : gen_select
            CarrySelectAdder adder4 (
                .c_i   (c[i]          ),
                .op_a_i(op_a_i[i*4+:4]),
                .op_b_i(op_b_i[i*4+:4]),
                .c_o   (c[i+1]        ),
                .sum_o (sum_o[i*4+:4] )
            );
        end
        else if (TYPE == CARRY_INCREMENT) begin : gen_increment
            CarryIncrementAdder adder4 (
                .c_i   (c[i]          ),
                .op_a_i(op_a_i[i*4+:4]),
                .op_b_i(op_b_i[i*4+:4]),
                .c_o   (c[i+1]        ),
                .sum_o (sum_o[i*4+:4] )
            );
        end
    end

    assign c_o = c[(NBITS/4)];

endmodule
