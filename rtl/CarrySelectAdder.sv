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
    /* carry in 0 and in 1 are parallel */
    logic [4:0] c1;
    assign c1[0] = 1'b1;
    assign c1[1] = g[0] | p[0];
    assign c1[2] = g[1] | (p[1] & (g[0] | p[0]));
    assign c1[3] = g[2] | (p[2] & (g[1] | (p[1] & (g[0] | p[0]))));
    assign c1[4] = g[3] | (p[3] & (g[2] | (p[2] & (g[1] | (p[1] & (g[0] | p[0]))))));

    logic [3:0] s0;
    assign s0 = p ^ c0[3:0];
    /* sum with carry in 0 and 1 are parallel */
    logic [3:0] s1;
    assign s1 = p[3:0] ^ c1[3:0];

    /* Mux between the two full adders based on the carry input */
    assign c_o   = c_i ? c1[4] : c0[4];
    assign sum_o = c_i ? s1    : s0;

endmodule
