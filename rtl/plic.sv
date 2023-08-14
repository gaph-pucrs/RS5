module plic
	import RS5_pkg::*;
#(
	parameter i_cnt = 0
)
(
    input   logic                   clk,
    input   logic                   reset,

    input   logic                   en_i,
    input   logic  [3:0]            we_i,
    input   logic [23:0]            addr_i,
    input   logic [31:0]            data_i,
    output  logic [31:0]            data_o,

    input   logic [i_cnt:1]         irq_i,
    input   logic                   iack_i,

    output  logic [i_cnt:1]         iack_o,
    output  logic                   irq_o,
    output  logic [$clog2(i_cnt):0] id_o
);

    logic [31:0]    ie;
    logic [i_cnt:1] ip;
    logic [i_cnt:1] interrupt;

    always_ff @(posedge clk) begin
        if (reset) begin
            ip <= '0;
        end
        else begin
            ip <= irq_i;
        end
    end

    assign interrupt = ip & ie;

	always_comb begin
		id_o = '0;   /* 0 = NO IRQ */
		for(logic [$clog2(i_cnt):0] i = 1; i <= i_cnt; i++) begin
			if (interrupt[i]) begin
				id_o = i;
				break;
			end
		end
	end

    assign irq_o    = (|interrupt) & ~iack_i;

    assign iack_o   = iack_i;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Mapped Regs
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    always_ff @( posedge clk ) begin
        if (reset) begin
            ie      <= '0;
            data_o  <= '0;
        end  
        else if (en_i) begin
            if (we_i != '0) begin
                case (addr_i)
                    24'h002000:     ie      <= data_i;
                    default:        ;
                endcase
            end
            else begin
                case (addr_i)
                    24'h001000:     data_o  <= ip;
                    24'h002000:     data_o  <= ie;
                    default:        data_o  <= '0;
                endcase
            end
        end
    end
endmodule
