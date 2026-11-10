/*!\file mmu.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 *
 * \brief
 *
 * \detailed
 *
 */

`include "RS5_pkg.sv"

module mmu
    import RS5_pkg::*;
#(
    parameter bit EXEC = 1'b0   /* 1: instruction fetch MMU, 0: data MMU */
)
(
    input  logic        en_i,

    /* Page configuration */
    input  logic [31:0] offset_i,       /* Physical base address           */
    input  logic [31:0] size_i,         /* Page size in bytes              */

    /* Only one of the regions applies, depending on EXEC */
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [31:0] exec_limit_i,   /* First non-executable address    */
    input  logic [31:0] write_base_i,   /* First writable address          */
    input  logic        write_i,        /* Store, store-conditional or AMO */
    /* verilator lint_on UNUSEDSIGNAL */

    input  logic [31:0] address_i,

    output logic        exception_o,
    output logic [31:0] address_o
);

    logic deny;
    if (EXEC) begin : gen_exec
        /* Fetching past the executable region */
        assign deny = address_i >= exec_limit_i;
    end
    else begin : gen_data
        /* Writing below the writable region */
        assign deny = write_i && (address_i < write_base_i);
    end

    assign address_o   = en_i ? (address_i + offset_i) : address_i;
    assign exception_o = en_i && ((address_i >= size_i) || deny);

endmodule
