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

module regbank(
    input   logic         clk, 
    input   logic         reset,

    input   logic [4:0]   rs1,
    input   logic [4:0]   rs2,
    input   logic [4:0]   rd,
    input   logic         enable,
    input   logic [31:0]  data_i,
    output  logic [31:0]  data1_o,
    output  logic [31:0]  data2_o
);

    reg [31:0] regfile [31:0];
    assign regfile[0] = '0;
    
    assign  data1_o = regfile[rs1],
            data2_o = regfile[rs2];
    
    // Reset and Write control
    for (genvar i = 1; i < 32 ; i++) begin
        always_ff @(posedge clk) begin
            if (reset) begin
                regfile[i] <= '0;
            end
            else if (rd == i && enable) begin
                regfile[i] <= data_i;
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// DEBUG 
//////////////////////////////////////////////////////////////////////////////

    int fd;
    initial 
        fd = $fopen ("./debug/regBank.txt", "w");

    always_ff @(posedge clk ) begin
        $fwrite(fd,"[%0d] %02d - %8h \t %02d - %8h\n", $time, rs1, data1_o, rs2, data2_o);
        if (rd != '0 && enable == 1'b1) begin
            $fwrite(fd,"[%0d] --------------------------------- %02d - %8h\n", $time, rd, data_i);
        end
    end

endmodule
