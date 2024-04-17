/*!\file mmu.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes     <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto  <angelo.dalzotto@edu.pucrs.br>
 * Caroline Borges   <caroline.s@edu.pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 *
 * \detailed
 *
 */

`include "RS5_pkg.sv"

module mmu
    import RS5_pkg::*;
(
    input  logic        en_i,

    input  logic [31:0] mask_i,
    input  logic [31:0] offset_i,
    input  logic [31:0] size_i,
    input  logic [31:0] address_i,

    output logic        exception_o,
    output logic [31:0] address_o
);

    always_comb begin
        if (en_i == 1'b1) begin
            address_o = (address_i | offset_i);
            if (((address_i & ~mask_i) & ~size_i) != '0) begin
                exception_o = 1'b1;
            end
            else begin
                exception_o = 1'b0;
            end
        end
        else begin
            address_o   = address_i;
            exception_o = 1'b0;
        end
    end

endmodule
