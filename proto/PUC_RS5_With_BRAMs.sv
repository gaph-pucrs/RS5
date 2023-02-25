import my_pkg::*;

module PUC_RS5_With_BRAMs (
    input logic         clk,
    input logic         reset,
    output logic [7:0]  gpioa_out,
    output logic [7:0]  gpioa_addr,
    input logic         BTND,
    output logic        UART_TX
    );

    logic [31:0]    CPU_instruction_address, CPU_instruction;
    logic [31:0]    CPU_data_address, CPU_data_in, CPU_data_out;
    logic [31:0]    BRAM_data_o, PERIPHERALS_data_o;
    logic           CPU_operation_enable, BRAM_enable, PERIPHERALS_enable, enable_r;
    logic [3:0]     CPU_write_enable;
    logic           stall;
    logic [31:0]    IRQ;
    logic           Interrupt_ACK;

    assign PERIPHERALS_enable = (CPU_data_address > 32'h0000FFFF && CPU_operation_enable) 
                                ? 1 
                                : 0;

    assign BRAM_enable = (CPU_data_address <= 32'h0000FFFF && CPU_operation_enable) 
                        ? 1 
                        : 0;

    always @(posedge clk) begin
        enable_r <= BRAM_enable;
    end

    assign CPU_data_in = (enable_r) 
                        ? BRAM_data_o 
                        : PERIPHERALS_data_o;

//////////////////////////////////////////////////////////////////////////////
// CPU INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    PUC_RS5 dut (
        .clk(clk), 
        .reset(!reset),
        .stall(stall),
        .instruction_i(CPU_instruction), 
        .mem_data_i(CPU_data_in), 
        .IRQ_i(IRQ),
        .instruction_address_o(CPU_instruction_address), 
        .mem_operation_enable_o(CPU_operation_enable), 
        .mem_write_enable_o(CPU_write_enable),
        .mem_address_o(CPU_data_address), 
        .mem_data_o(CPU_data_out), 
        .interrupt_ack_o(Interrupt_ACK)
    );


//////////////////////////////////////////////////////////////////////////////
// BRAM INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    BRAM RAM (
        .clka(clk),                         // input wire clka
        .ena(!stall),                       // input wire ena
        .wea(4'h0),                         // input wire [3 : 0] wea
        .addra(CPU_instruction_address),    // input wire [31 : 0] addra
        .dina(0),                           // input wire [31 : 0] dina
        .douta(CPU_instruction),            // output wire [31 : 0] douta
        //////////////////////////////////////////////////////
        .clkb(clk),                         // input wire clkb
        .enb(BRAM_enable),                  // input wire enb
        .web(CPU_write_enable),             // input wire [3 : 0] web
        .addrb(CPU_data_address),           // input wire [31 : 0] addrb
        .dinb(CPU_data_out),                // input wire [31 : 0] dinb
        .doutb(BRAM_data_o)                 // output wire [31 : 0] doutb
    );

//////////////////////////////////////////////////////////////////////////////
// PERIPHERALS
//////////////////////////////////////////////////////////////////////////////

    Peripherals Peripherals1 (
        .clk(clk), 
        .reset(!reset), 
        .stall_o(stall),
        .enable_i(PERIPHERALS_enable), 
        .write_enable_i(CPU_write_enable),
        .data_address_i(CPU_data_address), 
        .data_i(CPU_data_out), 
        .data_o(PERIPHERALS_data_o),
        .gpioa_out(gpioa_out),
        .gpioa_addr(gpioa_addr),
        .BTND(BTND),
        .UART_TX(UART_TX),
        .IRQ_o(IRQ),
        .interrupt_ack_i(Interrupt_ACK)
    );

endmodule
