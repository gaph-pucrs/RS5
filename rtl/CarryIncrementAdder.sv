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

    logic [3:0] p;
    assign p = op_a_i ^ op_b_i;
    /* p and g are parallel */
    logic [3:0] g;
    assign g = op_a_i & op_b_i;

    logic [4:0] c0;
    assign c0[0] = 1'b0;
    assign c0[1] = g[0];
    assign c0[2] = g[1] | (p[1] & g[0]);
    assign c0[3] = g[2] | (p[2] & (g[1] | (p[1] & g[0])));
    assign c0[4] = g[3] | (p[3] & (g[2] | (p[2] & (g[1] | (p[1] & g[0])))));

    /* Full adder with carry in 0 */
    logic [3:0] s0;
    assign s0 = p ^ c0[3:0];

    logic [4:0] ci;
    assign ci[0] = 1'b1;
    assign ci[1] = s0[0];
    assign ci[2] = s0[1] & s0[0];
    assign ci[3] = s0[2] & s0[1] & s0[0];
    assign ci[4] = s0[3] & s0[2] & s0[1] & s0[0];

    // /* Increment with half adder */
    logic [3:0] si;
    assign si = s0 ^ ci[3:0];

    /* Mux between the two adders based on the carry input */
    assign c_o   = c0[4] | (ci[4] & c_i);
    assign sum_o = c_i ? si    : s0;

endmodule
