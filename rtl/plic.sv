module plic
	import RS5_pkg::*;
#(
	parameter i_cnt = 1
)
(
    input   logic                   clk,
    input   logic                   reset,

    input   logic                   en_i,
    input   logic  [3:0]            we_i,
    input   logic [23:0]            addr_i,
/* verilator lint_off UNUSEDSIGNAL */ 
    input   logic [31:0]            data_i,
/* verilator lint_on UNUSEDSIGNAL */
    output  logic [31:0]            data_o,

    input   logic [i_cnt:1]         irq_i,
    input   logic                   iack_i,

    output  logic [i_cnt:1]         iack_o,
    output  logic                   irq_o
);

    logic [$clog2(i_cnt):0] id_int, id;
    logic [i_cnt:1]         ie;
    logic [i_cnt:1]         ip;
    logic [i_cnt:1]         interrupt;

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            ip <= '0;
        end
        else begin
            ip <= irq_i;
        end
    end

    assign interrupt = ip & ie;

/* verilator lint_off WIDTHTRUNC */
	always_comb begin
		id_int = '0;   /* 0 = NO IRQ */
		for (int i = 1; i <= i_cnt; i++) begin
			if (interrupt[i] == 1'b1) begin
				id_int = i-1;               
				break;
			end
		end
	end
/* verilator lint_on WIDTHTRUNC */

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            id <= '0;
        end
        else if (iack_i == 1'b1)begin
            id <= id_int;
        end
    end

    assign irq_o    = (|interrupt) & ~iack_i;

    always_comb begin
        if (iack_i == 1'b1) begin
            iack_o = (1'b1 << id);
        end
        else begin
            iack_o = '0;
        end
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Mapped Regs
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    always_ff @( posedge clk ) begin
        if (reset == 1'b1) begin
            ie      <= '0;
            data_o  <= '0;
        end  
        else if (en_i == 1'b1) begin
            if (we_i != '0) begin
                case (addr_i)
                    24'h000008:     ie      <= data_i[i_cnt:1];
                    default:        ;
                endcase
            end
            else begin
                case (addr_i)
                    24'h000000:     data_o <= {{31-$clog2(i_cnt){1'b0}}, id};
                    24'h000004:     data_o <= {{31-i_cnt{1'b0}}, ip, 1'b0};
                    24'h000008:     data_o <= {{31-i_cnt{1'b0}}, ie, 1'b0};

                    default:        data_o <= '0;
                endcase
            end
        end
    end
endmodule
