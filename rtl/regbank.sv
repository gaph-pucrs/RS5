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
    input logic         clk, reset,
    input logic [4:0]   addra,
    input logic [4:0]   addrb,
    input logic [31:1]  addrw,
    input logic [31:0]  in,
    output logic [31:0] outa,
    output logic [31:0] outb);

    logic [31:0] regfile [31:1];
    wire [31:0] outa_int, outb_int;

    // Assign to outputs
    assign  outa = outa_int,
            outb = outb_int;

    // Emulate zero register
    assign  outa_int = (addra == 0) ? '0 : 'z,
            outb_int = (addrb == 0) ? '0 : 'z;

    // Read regA
    for (genvar i = 1; i < 32 ; i++)
        assign outa_int = (addra == i) ?  regfile[i] : 'z;

    // Read RegB
    for (genvar i = 1; i < 32 ; i++)
        assign outb_int = (addrb == i) ?  regfile[i] : 'z;

    // Reset and Write control
    for (genvar i = 1; i < 32 ; i++)
        always_ff @(posedge clk or negedge reset)
            if(!reset)
                regfile[i] <= '0;
            else if (addrw[i])
                regfile[i] <= in;


////////////////// DEBUG ///////////////////////////////////
    int fd;
    initial 
        fd = $fopen ("./debug/regBank.txt", "w");

    always @(posedge clk ) begin
        automatic int i;
        $fwrite(fd,"[%0d] %02d - %8h \t %02d - %8h\n", $time, addra, outa, addrb, outb);
        if(addrw != '0) begin
            for (i = 0; i <= 32; i++) 
                if(addrw[i]==1)
                    break;
            $fwrite(fd,"[%0d] --------------------------------- %02d - %8h\n", $time, i, in);
        end
    end
endmodule