/*!\file mmu.sv
 * PUC-RS5 VERSION - 1.0.0 - Public Release
 *
 * Distribution:  May 2023
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

module mmu
    import my_pkg::*;
(
    input  logic        en_i,

    input  logic [31:0] base_i,
    input  logic [31:0] limit_i,
    input  logic [31:0] address_i,

    output logic        exception_o,
    output logic [31:0] address_o
);
    logic [31:0] phy_addr;

    assign phy_addr = address_i + base_i;

    always_comb begin
        if (en_i) begin
            address_o = phy_addr;
            if (phy_addr >= limit_i) begin
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
