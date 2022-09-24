import my_pkg::*;

module PUCR5_With_BRAMs (
    input logic         clk,
    input logic         reset,
    output logic [7:0]  gpioa_out,
    output logic [7:0]  gpioa_addr,
    output logic        UART_TX
    //input logic [31:0]  IRQ
    );

    logic [31:0]  i_address, instruction;

    logic [31:0] DATA_address, DATA_in_cpu, DATA_out_cpu;
    logic [31:0] DATA_BRAM, DATA_peripherals;
    logic enable_int, enable_bram, enable_peripherals, enable_r;
    logic [3:0] write;
    logic stall, Interupt_ACK;

    assign enable_peripherals = (DATA_address > 32'h0000FFFF && enable_int) ? 1 : 0;
    assign enable_bram = (DATA_address <= 32'h0000FFFF && enable_int) ? 1 : 0;

    always @(posedge clk)
        enable_r <= enable_bram;

    assign DATA_in_cpu = (enable_r) ? DATA_BRAM : DATA_peripherals;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// CPU INSTANTIATION ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    PUCRS_RV dut (
        .clk(clk), 
        .reset(reset),
        .stall(stall),
        .instruction(instruction), 
        .i_address(i_address), 
        .enable(enable_int), 
        .write(write),
        .DATA_address(DATA_address), 
        .DATA_in(DATA_in_cpu), 
        .DATA_out(DATA_out_cpu), 
        .IRQ('0),
        .Interupt_ACK(Interupt_ACK)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// BRAM INSTANTIATION ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BRAM RAM (
        .clka(clk),             // input wire clka
        .ena(!stall),           // input wire ena
        .wea(4'h0),             // input wire [3 : 0] wea
        .addra(i_address),      // input wire [31 : 0] addra
        .dina(0),               // input wire [31 : 0] dina
        .douta(instruction),    // output wire [31 : 0] douta
        //////////////////////////////////////////////////////
        .clkb(clk),             // input wire clkb
        .enb(enable_bram),      // input wire enb
        .web(write),            // input wire [3 : 0] web
        .addrb(DATA_address),   // input wire [31 : 0] addrb
        .dinb(DATA_out_cpu),    // input wire [31 : 0] dinb
        .doutb(DATA_BRAM)       // output wire [31 : 0] doutb
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// PERIPHERALS //////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Peripherals Peripherals1 (
        .clk(clk), 
        .reset(reset), 
        .enable(enable_peripherals), 
        .write(write),
        .DATA_address(DATA_address), 
        .DATA_in(DATA_out_cpu), 
        .DATA_out(DATA_peripherals),
        .gpioa_out(gpioa_out),
        .gpioa_addr(gpioa_addr),
        .UART_TX(UART_TX),
        .stall(stall),
        .Interupt_ACK(Interupt_ACK)
    );


endmodule