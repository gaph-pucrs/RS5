import my_pkg::*;

module Peripherals (
    input logic         clk,
    input logic         reset,
    
    input logic         enable_i,
    input logic [3:0]   write_enable_i,
    input logic [31:0]  data_address_i,
    input logic [31:0]  data_i,
    output logic [31:0] data_o,
    output logic [7:0]  gpioa_out,
    output logic [7:0]  gpioa_addr,
    input logic         BTND,
    output logic        UART_TX,
    output logic        stall_o,
    output logic [31:0] IRQ_o,
    input logic         interrupt_ack_i
);

logic stall_r;
logic [31:0] data_r, counter;
logic BUFFER_write, BUFFER_read, BUFFER_empty, BUFFER_full;
logic [7:0] BUFFER_data;
logic UART_send, UART_ready;
logic [7:0] UART_data;
logic BTND_Debounced, BTND_Debounced_r, Button_Detected, Button_request;

//////////////////////////////////////////////////////////////////////////////
// Writes in Peripherals
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk) begin
        if (enable_i && write_enable_i != '0) begin
            /// OUTPUT REG
            if ((data_address_i == 32'h80004000 || data_address_i == 32'h80001000) && BUFFER_full == '0) begin
                gpioa_out <= data_i[7:0];
                gpioa_addr <= 8'h84;
                BUFFER_write <= 1;
                BUFFER_data <= data_i[7:0];
            end
            // END REG
            else if (data_address_i == 32'h80000000) begin
                gpioa_addr <= 8'h80;
            end
            // NOTHING
            else begin
                gpioa_out <= '0;
                gpioa_addr <= '0;
                BUFFER_write <= '0;         
            end

        end else begin
            gpioa_out <= '0;
            gpioa_addr <= '0;
            BUFFER_write <= '0;         
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Reads from Peripherals
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk) begin
        if (enable_i && write_enable_i == '0) begin
        ///////////////////////////////////// TIMER REG ////////////////////////////////////
            if (data_address_i == 32'h80006000)
                data_r <= counter;
            else
                data_r <= '0;

        end else begin
            data_r <= '0;
        end
    end
//////////////////////////////////////////////////////////////////////////////
// INTERRUPT CONTROL
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk) begin
        if (reset) begin
            IRQ_o <= '0;
        end
        // EXTERNAL
        else if (IRQ_o[11] && interrupt_ack_i) begin
            IRQ_o[11] <= 0;
        end
        else if (Button_request) begin
            IRQ_o[11] <= 1;
        end
        // TIMER
        else if (IRQ_o[7] && interrupt_ack_i) begin
            IRQ_o[7] <= 0;
        end
        else if (counter >= 32'h0EE6B280) begin
            IRQ_o[7] <= 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// TIMER AND BUTTON
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset) begin
            counter <= 0;
        end
        else if (IRQ_o[7] && interrupt_ack_i) begin
            counter <= 0;
        end
        else begin
            counter <= counter + 1;
        end
    end

    always_ff @(posedge clk) begin
        if (reset) begin
            Button_request <= 0;
        end
        else if (IRQ_o[11] && interrupt_ack_i) begin
            Button_request <= 0;
        end
        else if (Button_Detected || Button_request) begin
            Button_request <= 1;
        end
    end

    debouncer #(.DEBNC_CLOCKS(2**16), .PORT_WIDTH(1)) Debouncer (
        .CLK_I(clk),
        .SIGNAL_I(BTND),
        .SIGNAL_O(BTND_Debounced)
    );

    always_ff @(posedge clk) begin
        BTND_Debounced_r <= BTND_Debounced;
    end
    assign Button_Detected = (!BTND_Debounced_r && BTND_Debounced);

//////////////////////////////////////////////////////////////////////////////
// STALL GENERATION
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (enable_i) begin
            // READS
            if (write_enable_i == '0 && stall_r != 1) begin
                if (data_address_i == 32'h80006000) begin
                    stall_o = 1;
                end
                else begin
                    stall_o = 0;
                end
            end
            // WRITES
            else if (write_enable_i != '0) begin
                if ((data_address_i == 32'h80004000 || data_address_i == 32'h80001000) && BUFFER_full) begin
                    stall_o = 1;
                end
                else begin
                    stall_o = 0;
                end
            end
            else begin
                stall_o = 0;
            end
        end 
        else begin
            stall_o = 0;
        end
    end

    always_ff @(posedge clk) begin
        stall_r <= stall_o;
        data_o <= data_r;
    end

//////////////////////////////////////////////////////////////////////////////
// UART INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    UART_TX_CTRL UART(
        .CLK(clk),
        .SEND(UART_send),
        .DATA(UART_data),
        .READY(UART_ready),
        .UART_TX(UART_TX)
    );

//////////////////////////////////////////////////////////////////////////////
// UART BUFFER
//////////////////////////////////////////////////////////////////////////////

    FIFO_BUFFER_UART FIFO_BUFFER_UART1 (
    .clk(clk),                // input wire clk
    .srst(reset),             // input wire srst
    .din(BUFFER_data),        // input wire [7 : 0] din
    .wr_en(BUFFER_write),     // input wire wr_en
    .rd_en(BUFFER_read),      // input wire rd_en
    .dout(UART_data),         // output wire [7 : 0] dout
    .full(BUFFER_full),       // output wire full
    .empty(BUFFER_empty)      // output wire empty
    );

    assign BUFFER_read = UART_ready & !BUFFER_empty & !UART_send;

    always_ff @(posedge clk) begin
        UART_send <= BUFFER_read;
    end

endmodule
