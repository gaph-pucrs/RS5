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
    input logic         clk, 
    input logic         reset,
    input logic [4:0]   addra,
    input logic [4:0]   addrb,
    input logic [4:0]   addrw,
    input logic         enable,
    input logic [31:0]  in,
    output logic [31:0] outa,
    output logic [31:0] outb
);

    reg [31:0] regfile [31:0];

    // Reg 0 assigned to zero
    assign regfile[0] = '0;

    assign  outa = regfile[addra],
            outb = regfile[addrb];
    
    // Reset and Write control
    for (genvar i = 1; i < 32 ; i++)
        always_ff @(posedge clk)
            if(reset)
                regfile[i] <= '0;
            else if (addrw==i && enable==1)
                regfile[i] <= in;

////////////////// DEBUG ///////////////////////////////////
    int fd;
    initial 
        fd = $fopen ("./debug/regBank.txt", "w");

    always @(posedge clk ) begin
        $fwrite(fd,"[%0d] %02d - %8h \t %02d - %8h\n", $time, addra, outa, addrb, outb);
        if(addrw != '0) begin
            $fwrite(fd,"[%0d] --------------------------------- %02d - %8h\n", $time, addrw, in);
        end
    end

endmodule
