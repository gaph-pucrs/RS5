/*!\file CarryBypass.sv
 * RS5 VERSION
 *
 * Fernando Gehm Moraes <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 *
 * \brief
 * Carry bypass 4-bit adder.
 */

module CarryBypass (
    input  logic       c_i,
    input  logic [3:0] op_a_i,
    input  logic [3:0] op_b_i,
    output logic       c_o,
    output logic [3:0] sum_o
);

    logic [3:0] p;
    assign p = op_a_i ^ op_b_i;

    logic [3:0] g;
    assign g = op_a_i & op_b_i;

    logic [4:0] c;
    assign c[0] = c_i;
    assign c[1] = g[0] | (p[0] & c_i);
    assign c[2] = g[1] | (p[1] & (g[0] | (p[0] & c_i)));
    assign c[3] = g[2] | (p[2] & (g[1] | (p[1] & (g[0] | (p[0] & c_i)))));
    assign c[4] = g[3] | (p[3] & (g[2] | (p[2] & (g[1] | (p[1] & (g[0] | (p[0] & c_i)))))));

    assign sum_o = p[3:0] ^ c[3:0];
    assign c_o = (p == '1) ? c_i : c[4];

endmodule
