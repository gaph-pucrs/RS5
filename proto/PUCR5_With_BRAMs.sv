import my_pkg::*;

module PUCR5_With_BRAMs (
    input logic         clk,
    input logic         reset,
    input logic [31:0]  DATA_in,
    output logic [31:0] DATA_out,
    output logic [31:0] DATA_address,
    output logic        enable,
    output logic [3:0]  write,
    output logic [31:0] IRQ
);

    logic [31:0]  i_address, instruction;
    logic [31:0]  DATA_read, DATA_write;
    logic [31:0]  DATA_BRAM;
    logic enable_int, enable_bram;
    
    assign DATA_out = DATA_write;
    assign DATA_read = (enable) ? DATA_in : DATA_BRAM;

    assign enable = (DATA_address > 32'h0000FFFF && enable_int) ? 1 : 0;
    assign enable_bram = (DATA_address <= 32'h0000FFFF && enable_int) ? 1 : 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// CPU INSTANTIATION ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    PUCRS_RV dut (
        .clk(clk), 
        .reset(reset), 
        .instruction(instruction), 
        .i_address(i_address), 
        .DATA_in(DATA_read), 
        .DATA_out(DATA_write), 
        .DATA_address(DATA_address), 
        .enable(enable_int), 
        .write(write),
        .IRQ(IRQ)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// BRAM INSTANTIATION ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BRAM RAM (
        .clka(clk),             // input wire clka
        .wea(0),                // input wire [3 : 0] wea
        .addra(i_address),      // input wire [31 : 0] addra
        .dina(0),               // input wire [31 : 0] dina
        .douta(instruction),    // output wire [31 : 0] douta
        //////////////////////////////////////////////////////
        .clkb(clk),             // input wire clkb
        .enb(enable_bram),      // input wire enb
        .web(write),            // input wire [3 : 0] web
        .addrb(DATA_address),   // input wire [31 : 0] addrb
        .dinb(DATA_write),      // input wire [31 : 0] dinb
        .doutb(DATA_BRAM)       // output wire [31 : 0] doutb
    );

endmodule