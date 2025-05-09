/*!\file CarrySelectAdder.sv
 * RS5
 *
 * Angelo Elias Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 *
 * \brief
 * Carry select 4-bit block.
 */

module CarrySelectAdder (
    input  logic       c_i,
    input  logic [3:0] op_a_i,
    input  logic [3:0] op_b_i,
    output logic       c_o,
    output logic [3:0] sum_o
);

    /* Full adder without carry in */
    logic [4:0] s0;
    assign s0 = op_a_i + op_b_i;

    /* Full adder with carry in */
    logic [4:0] s1;
    assign s1 = op_a_i + op_b_i + 1'b1;

    /* Mux between the two full adders based on the carry input */
    assign c_o   = c_i ? s1[4]   : s0[4];
    assign sum_o = c_i ? s1[3:0] : s0[3:0];

endmodule
