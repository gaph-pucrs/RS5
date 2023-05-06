module PUC_RS5_With_BRAMs
    import my_pkg::*;
(
    input  logic       clk,
    input  logic       reset,
    output logic [7:0] gpioa_out,
    output logic [7:0] gpioa_addr,
    input  logic       BTND,
    output logic       UART_TX
);
    logic [63:0]    mtime;
    logic [63:0]    data_rtc;
    logic [31:0]    CPU_instruction_address, CPU_instruction;
    logic [31:0]    CPU_data_address, CPU_data_in, CPU_data_out;
    logic [31:0]    BRAM_data_o, PERIPHERALS_data_o;
    logic           CPU_operation_enable, BRAM_enable, PERIPHERALS_enable, enable_rtc, enable_r, enable_rtc_r;
    logic [3:0]     CPU_write_enable;
    logic           stall;
    logic           mei, mti;
    logic           Interrupt_ACK;
    logic [31:0]    IRQ;

    assign IRQ = {20'h0, mei, 3'h0, mti, 7'h0};

    always_comb begin
        if (enable_r) begin
            CPU_data_in = BRAM_data_o;
        end
        else if (enable_rtc_r) begin
            CPU_data_in = data_rtc[31:0];
        end
        else begin
            CPU_data_in = PERIPHERALS_data_o;
        end
    end
    
    always_comb begin
        if (CPU_operation_enable) begin
            if (CPU_data_address[31:28] < 4'h2) begin
                BRAM_enable = 1'b1;
                PERIPHERALS_enable  = 1'b0;
                enable_rtc = 1'b0;
            end
            else if (CPU_data_address[31:28] < 4'h8) begin
                BRAM_enable = 1'b0;
                PERIPHERALS_enable  = 1'b0;
                enable_rtc = 1'b1;
            end
            else begin
                BRAM_enable = 1'b0;
                PERIPHERALS_enable  = 1'b1;
                enable_rtc = 1'b0;
            end
        end
        else begin
            BRAM_enable = 1'b0;
            PERIPHERALS_enable  = 1'b0;
            enable_rtc = 1'b0;
        end
    end

    always_ff @(posedge clk) begin
        enable_r <= BRAM_enable;
        enable_rtc_r <= enable_rtc;
    end

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
// RTC INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    rtc rtc(
        .clk(clk),
        .en_i(enable_rtc),
        .addr_i(CPU_data_address[3:0]),
        .we_i({4'h0, CPU_write_enable}),
        .data_i({32'h0, CPU_data_out}),
        .data_o(data_rtc),     
        .mti_o(mti),
        .mtime_o(mtime)
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
        .mei_o(mei),
        .interrupt_ack_i(Interrupt_ACK)
    );

endmodule
