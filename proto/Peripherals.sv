import my_pkg::*;

module Peripherals (
    input logic         clk,
    input logic         reset,
    input logic         enable,
    input logic [3:0]   write,
    input logic [31:0]  DATA_address,
    input logic [31:0]  DATA_in,
    output logic [31:0] DATA_out,
    output logic [7:0]  gpioa_out,
    output logic [7:0]  gpioa_addr,
    output logic        UART_TX,
    output logic        stall
);

logic stall_r;
logic [31:0] DATA_r;
logic UART_send, UART_ready, UART_rst;
logic [7:0] UART_data;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Writes in Peripherals ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if (enable==1 && write!=0) begin
            ///////////////////////////////////// OUTPUT REG ///////////////////////////////////
            if ((DATA_address == 32'h80004000 || DATA_address == 32'h80001000) && UART_ready==1 && UART_rst==0) begin
                gpioa_out <= DATA_in[7:0];
                gpioa_addr <= 8'h84;
                UART_send <= 1;
                UART_data <= DATA_in[7:0];
            end
            ///////////////////////////////////// END REG //////////////////////////////////////
            else if (DATA_address==32'h80000000)
                gpioa_addr <= 8'h80;
            ///////////////////////////////////// UART REG /////////////////////////////////////
            else if (DATA_address==32'h90001000) begin
                UART_send <= 1;
                UART_data <= DATA_in[7:0];
            end
            ///////////////////////////////////// NOTHING //////////////////////////////////////
            else begin
                gpioa_out <= '0;
                gpioa_addr <= '0;
                UART_send <= '0;         
            end

        end else begin
            gpioa_out <= '0;
            gpioa_addr <= '0;
            UART_send <= '0;         
        end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Reads from Peripherals ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk) 
        if (enable==1 && write==0) begin
        ///////////////////////////////////// TIMER REG ////////////////////////////////////
            if (DATA_address==32'h80006000)
                DATA_r <= 1000;
            else
                DATA_r <= '0;

        end else begin
            DATA_r <= '0;
        end

    always_comb
        if (enable==1 && write==0 && stall_r!=1)
            if (DATA_address==32'h80006000)
                stall <= 1;
            else
                stall <= 0;
        else if (enable==1 && write!=0)
            if (UART_rst==1)
                stall <= 1;
            else if ((DATA_address == 32'h80004000 || DATA_address == 32'h80001000) && UART_ready==0)
                stall <= 1;
            else
                stall <= 0;
        else
            stall <= 0;

    always @(posedge clk) begin
        stall_r <= stall;
        DATA_out <= DATA_r;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// UART INSTANTIATION ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    UART_TX_CTRL UART(
        .CLK(clk),
        .SEND(UART_send),
        .DATA(UART_data),
        .READY(UART_ready),
        .UART_TX(UART_TX)
    );

int RESET_CNTR_MAX = 200000;
int reset_cntr;
always @(posedge clk)
    if (reset) begin
        reset_cntr <= '0;
        UART_rst <= 1;
    end else if ((reset_cntr == RESET_CNTR_MAX)) begin
        reset_cntr <= '0;
        UART_rst <= 0;
    end else begin
        reset_cntr <= reset_cntr + 1;
        UART_rst <= 1;
    end
endmodule
