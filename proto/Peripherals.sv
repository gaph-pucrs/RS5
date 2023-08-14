module Peripherals
    import RS5_pkg::*;
#(
    parameter i_cnt = 0
)
(
    input  logic            clk,
    input  logic            reset,
    
    input  logic            enable_i,
    input  logic [3:0]      write_enable_i,
    input  logic [31:0]     data_address_i,
    input  logic [31:0]     data_i,
    output logic [31:0]     data_o,
    output logic [7:0]      gpioa_out,
    output logic [7:0]      gpioa_addr,
    input  logic            BTND,
    output logic            UART_TX,
    output logic            stall_o,
    output logic [i_cnt:1]  interrupt_req_o,
    input  logic [i_cnt:1]  interrupt_ack_i
);

    logic           stall_r;
    logic           BUFFER_write, BUFFER_read, BUFFER_empty, BUFFER_full;
    logic [7:0]     BUFFER_data;
    logic           UART_send, UART_ready;
    logic [7:0]     UART_data;
    logic [i_cnt:1] irq;
    logic           BTND_debounced, BTND_debounced_r, button_detected, button_irq, button_ack;

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
// INTERRUPT CONTROL
//////////////////////////////////////////////////////////////////////////////

    assign interrupt_req_o[1]   = button_irq;

    assign button_ack           = interrupt_ack_i[1];

//////////////////////////////////////////////////////////////////////////////
// BUTTON
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            button_irq <= 0;
        end
        else if (button_ack == 1'b1) begin
            button_irq <= 0;
        end
        else if (button_detected == 1'b1) begin
            button_irq <= 1;
        end
    end

    debouncer #(.DEBNC_CLOCKS(2**10), .PORT_WIDTH(1)) Debouncer (
        .CLK_I      (clk),
        .SIGNAL_I   (BTND),
        .SIGNAL_O   (BTND_debounced)
    );

    always_ff @(posedge clk) begin
        BTND_debounced_r <= BTND_debounced;
    end
    assign button_detected = (!BTND_debounced_r && BTND_debounced);

//////////////////////////////////////////////////////////////////////////////
// STALL GENERATION
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (enable_i) begin
            // READS
            if (write_enable_i == '0 && !stall_r) begin
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
        data_o  <= '0;
    end

//////////////////////////////////////////////////////////////////////////////
// UART INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    UART_TX_CTRL UART(
        .CLK        (clk),
        .SEND       (UART_send),
        .DATA       (UART_data),
        .READY      (UART_ready),
        .UART_TX    (UART_TX)
    );

//////////////////////////////////////////////////////////////////////////////
// UART BUFFER
//////////////////////////////////////////////////////////////////////////////

    FIFO_BUFFER_UART FIFO_BUFFER_UART1 (
        .clk    (clk),                  // input wire clk
        .srst   (reset),                // input wire srst
        .din    (BUFFER_data),          // input wire [7 : 0] din
        .wr_en  (BUFFER_write),         // input wire wr_en
        .rd_en  (BUFFER_read),          // input wire rd_en
        .dout   (UART_data),            // output wire [7 : 0] dout
        .full   (BUFFER_full),          // output wire full
        .empty  (BUFFER_empty)          // output wire empty
    );

    assign BUFFER_read = UART_ready & !BUFFER_empty & !UART_send;

    always_ff @(posedge clk) begin
        UART_send <= BUFFER_read;
    end

endmodule
