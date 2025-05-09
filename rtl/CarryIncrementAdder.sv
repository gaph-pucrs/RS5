/*!\file CarryIncrementAdder.sv
 * RS5
 *
 * Angelo Elias Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 *
 * \brief
 * Carry increment 4-bit block.
 */

module CarryIncrementAdder (
    input  logic       c_i,
    input  logic [3:0] op_a_i,
    input  logic [3:0] op_b_i,
    output logic       c_o,
    output logic [3:0] sum_o
);

    logic [4:0] s0;
    assign s0 = op_a_i + op_b_i;

    logic [4:0] si;
    assign si = s0[3:0] + 1'b1;

    /* Mux between the two adders based on the carry input */
    assign c_o   = s0[4] | (si[4] & c_i);
    assign sum_o = c_i ? si[3:0] : s0[3:0];

endmodule
