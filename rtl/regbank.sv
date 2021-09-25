/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// REGISTER BANK ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Developed By: Willian Analdo Nunes ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// PUCRS, Porto Alegre, 2020      ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

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
  assign outa = outa_int,
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

endmodule