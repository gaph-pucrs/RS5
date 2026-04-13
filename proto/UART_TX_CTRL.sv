module UART_TX_CTRL
#(
    parameter int unsigned CLK_FREQUENCE = 256_000_000,
    parameter int unsigned BAUD_RATE = 115_200
)
(
   input  logic        clk,
   input  logic        reset_n,
   input  logic        i_Tx_DV,
   input  logic [7:0]  i_Tx_Byte, 
   output logic        o_Tx_Active,
   output logic        o_Tx_Serial,
   input  logic [15:0] clks_per_bit_i
);

    typedef enum logic[3:0] { 
        IDLE         = 4'b0001,
        TX_START_BIT = 4'b0010,
        TX_DATA_BITS = 4'b0100,
        TX_STOP_BIT  = 4'b1000
    } state_e;

    state_e current_state;
    state_e next_state;

    always_ff @(posedge clk or negedge reset_n) begin 
        if (!reset_n) 
            current_state <= IDLE;
        else
            current_state <= next_state;
    end

    logic [15:0] r_Clock_Count;

    logic clk_cnt_top;
    logic [15:0] clks_per_bit;
    assign clk_cnt_top = (r_Clock_Count >= clks_per_bit);

    always_ff @(posedge clk or negedge reset_n) begin
		if (!reset_n) begin
			r_Clock_Count <= '0;
		end 
		else begin
			if (current_state == IDLE || clk_cnt_top) begin
				r_Clock_Count <= '0;
			end
			else begin
				r_Clock_Count <= r_Clock_Count + 1'b1;
			end
		end
	end

    logic [2:0]  r_Bit_Index;
    logic [7:0]  r_Tx_Data;
    logic        r_Tx_Active;

    always_comb begin
        unique case (current_state)
            IDLE:         next_state = i_Tx_DV                           ? TX_START_BIT : IDLE;
            TX_START_BIT: next_state = (clk_cnt_top)                     ? TX_DATA_BITS : TX_START_BIT;
            TX_DATA_BITS: next_state = (clk_cnt_top && r_Bit_Index == 7) ? TX_STOP_BIT  : TX_DATA_BITS;
            TX_STOP_BIT:  next_state = (clk_cnt_top)                     ? IDLE         : TX_STOP_BIT;
            default:      next_state = IDLE;
        endcase
    end

    always_comb begin
        unique case (current_state)
            TX_START_BIT:
                o_Tx_Serial = 1'b0;
            TX_DATA_BITS:
                o_Tx_Serial = r_Tx_Data[r_Bit_Index];
            default:
                o_Tx_Serial = 1'b1;         // Drive Line High for Idle/Stop
        endcase
    end

    always_ff@ (posedge clk or negedge reset_n) begin
        if(!reset_n) begin
            r_Bit_Index <= '0;
        end 
        else begin
            unique case (current_state)
                TX_DATA_BITS: r_Bit_Index <= clk_cnt_top ? r_Bit_Index + 1'b1 : r_Bit_Index;
                default:      r_Bit_Index <= '0;
            endcase
        end
    end

    always_ff@ (posedge clk or negedge reset_n) begin
        if(!reset_n) begin
            r_Tx_Active <= 1'b0;
        end 
        else begin
            unique case (current_state)
                IDLE:        r_Tx_Active <= i_Tx_DV;
                TX_STOP_BIT: r_Tx_Active <= !clk_cnt_top;
                default:     ;
            endcase
        end
    end

    always_ff@ (posedge clk or negedge reset_n) begin
        if(!reset_n) begin
            r_Tx_Data <= '0;
        end 
        else begin
            if (current_state == IDLE)
                r_Tx_Data <= i_Tx_Byte;
        end
    end

    always_ff@ (posedge clk or negedge reset_n) begin
        if(!reset_n) begin
            clks_per_bit <= CLK_FREQUENCE/BAUD_RATE;
        end 
        else begin
            if (current_state == IDLE)
                clks_per_bit <= clks_per_bit_i;
        end
    end

    assign o_Tx_Active = r_Tx_Active;

endmodule
