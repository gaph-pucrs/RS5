/*!\file regbank.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  September 2021
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Defines a Regbank with 32 regs of 32 bits.
 *
 * \detailed
 * The Begister Bank is composed by 32 registers of 32 bits each. 
 * It has two read ports and one write port, the read is indexed by
 * direct codificadion and the write is index and enabled by a one-hot
 * signal 32 bits wide where each bit represent one register. The ZERO(0)
 * register is constant and the other 31 register implement a tri-state logic.
 */

module regbank (
    input logic         clk, 
    input logic [4:0]   addra,
    input logic [4:0]   addrb,
    input logic         enable,
    input logic [4:0]   addrw,
    input logic [31:0]  in,
    output logic [31:0] outa,
    output logic [31:0] outb
);

    reg [31:0] regFile [31:0];

///////////////////////////////////////////////// READ ////////////////////////////////////////////////////////////////    
    assign  outa = regFile[addra],
            outb = regFile[addrb];

///////////////////////////////////////////////// WRITE ///////////////////////////////////////////////////////////////    
    assign regFile[0] = '0;

    always_ff @(posedge clk)
        if (enable)
            regFile[addrw] <= in;

endmodule
