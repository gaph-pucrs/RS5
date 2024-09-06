`include "RS5_pkg.sv"

module plic
	import RS5_pkg::*;
#(
	parameter i_cnt = 1
)
(
    input   logic                   clk,
    input   logic                   reset_n,

    input   logic                   en_i,
    input   logic  [3:0]            we_i,
    input   logic [23:0]            addr_i,
    output  logic [31:0]            data_o,

    /* Only a reduced number of bits is used depending on the number of interrupts */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]            data_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   logic [i_cnt:1]         irq_i,
    input   logic                   iack_i,

    output  logic [i_cnt:1]         iack_o,
    output  logic                   irq_o
);
    typedef logic [$clog2(i_cnt):0] intr_t;

    intr_t          id_int;
    intr_t          id_r;
    logic [i_cnt:1] ie;
    logic [i_cnt:1] ip;
    logic [i_cnt:1] interrupt;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            ip <= '0;
        end
        else begin
            ip <= irq_i;
        end
    end

    assign interrupt = ip & ie;

	always_comb begin
		id_int = '0;   /* 0 = NO IRQ */
		for (int i = 1; i <= i_cnt; i++) begin
			if (interrupt[i] == 1'b1) begin
				id_int = intr_t'(i);           
				break;
			end
		end
	end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            id_r <= '0;
        else if (iack_i)
            id_r <= id_int;
    end

    assign irq_o    = (|interrupt); //& ~iack_i;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Mapped Regs
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            ie      <= '0;
            data_o  <= '0;
        end  
        else if (en_i == 1'b1) begin
            if (we_i != '0) begin
                case (addr_i)
                    24'h002000:     ie            <= data_i[i_cnt:1];
                    default:        ;
                endcase
            end
            else begin
                case (addr_i)
                    24'h200004:     data_o <= {{31-$clog2(i_cnt){1'b0}}, id_r}; /* ID */
                    24'h001000:     data_o <= {{31-i_cnt{1'b0}}, ip, 1'b0};     /* IP */
                    24'h002000:     data_o <= {{31-i_cnt{1'b0}}, ie, 1'b0};     /* IE */
                    default:        data_o <= '0;
                endcase
            end
        end 
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            iack_o <= '0;
        end
        else begin 
            if (en_i == 1'b1 && we_i != '0) begin
                if (addr_i == 24'h200004) begin
                    iack_o[data_i] <= 1'b1;
                end
            end else begin
                iack_o <= '0;
            end
        end
    end
endmodule
