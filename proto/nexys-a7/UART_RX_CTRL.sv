module UART_RX_CTRL
#(
	parameter int unsigned CLK_FREQUENCE = 256_000_000,
 	parameter int unsigned BAUD_RATE = 115_200
)
(
	input  logic         clk,
	input  logic         reset_n,
	input  logic     	 UART_RX_serial_i,
	output logic         UART_byte_valid_o,
	output logic [7:0]   UART_byte_o,
	input  logic [15:0]	 clks_per_bit_i
);

	typedef enum logic[2:0] { 
		RX_START_BIT = 3'b001,
		RX_DATA_BITS = 3'b010,
		RX_STOP_BIT  = 3'b100
	} state_e;

	logic r_rx_serial;
	
	// Purpose: Double-logicister the incoming data.
	// This allows it to be used in the UART RX Clock Domain.
	// (It removes problems caused by metastability)
	
	prim_sync #(
        .RESET_VALUE(1'b1)
	) u_serial_sync (
        .clk(clk),
        .reset_n(reset_n),
        .d(UART_RX_serial_i),
        .q(r_rx_serial)
    );

	state_e current_state;
	state_e next_state;

	always_ff @(posedge clk or negedge reset_n) begin 
		if (!reset_n) 
			current_state <= RX_START_BIT;
		else
			current_state <= next_state;
	end

	logic [15:0] r_Clock_Count;
	logic [15:0] clks_per_bit;

	logic clk_cnt_top;
	assign clk_cnt_top = (r_Clock_Count >= clks_per_bit);
	
	always_ff @(posedge clk or negedge reset_n) begin
		if (!reset_n) begin
			r_Clock_Count <= '0;
		end 
		else begin
			if ((current_state == RX_START_BIT && r_rx_serial) || clk_cnt_top) begin
				r_Clock_Count <= '0;
			end
			else begin
				r_Clock_Count <= r_Clock_Count + 1'b1;
			end
		end
	end

	logic clk_cnt_half;
	assign clk_cnt_half = (r_Clock_Count == {1'b0, clks_per_bit[15:1]});

	logic [2:0] r_Bit_Index;
	always_ff @(posedge clk or negedge reset_n) begin
		if (!reset_n)
			r_Bit_Index <= '0;
		else if (clk_cnt_half && current_state == RX_DATA_BITS)
			r_Bit_Index <= r_Bit_Index + 1'b1;
	end

	logic [7:0] r_Rx_Byte;
	always_ff @(posedge clk or negedge reset_n) begin
		if (!reset_n)
			r_Rx_Byte <= '0;
		else if (clk_cnt_half && current_state == RX_DATA_BITS)
			r_Rx_Byte[r_Bit_Index] <= r_rx_serial;
	end
	
	always_comb begin
		next_state = RX_START_BIT;
		unique case(current_state)
			RX_START_BIT: next_state = !r_rx_serial && clk_cnt_half        ? RX_DATA_BITS : RX_START_BIT;
			RX_DATA_BITS: next_state = clk_cnt_half && r_Bit_Index == 3'd7 ? RX_STOP_BIT  : RX_DATA_BITS;
			RX_STOP_BIT:  next_state = clk_cnt_half 					   ? RX_START_BIT : RX_STOP_BIT;
			default: ;
		endcase
	end

	logic r_Rx_DV;
	always_ff @(posedge clk or negedge reset_n) begin: r_Rx_DV_fsm
		if (!reset_n) begin
			r_Rx_DV <= 1'b0;
		end 
		else begin
			if (clk_cnt_half && current_state == RX_STOP_BIT)
				r_Rx_DV <= 1'b1;
			else
				r_Rx_DV <= 1'b0;
		end
	end

	always_ff @(posedge clk or negedge reset_n) begin
		if (!reset_n) begin
			clks_per_bit <= CLK_FREQUENCE/BAUD_RATE;
		end 
		else begin
			if (current_state == RX_START_BIT)
				clks_per_bit <= clks_per_bit_i;
		end
	end

	assign UART_byte_valid_o = r_Rx_DV;
	assign UART_byte_o 		 = r_Rx_Byte;
	
endmodule
