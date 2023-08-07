module PLIC
	import my_pkg::*;
#(
	parameter irq_cnt = 0
)
(
    input logic [irq_cnt:1] irq_i,
    input logic [irq_cnt:1] ie_i,

    output logic irq_o,
    output logic [$clog2(irq_cnt):0] id_o
);

    logic [irq_cnt:1] ip;

    always_ff @(posedge clk) begin
        if (reset) begin
            irq = '0;
        end
        else begin
            ip |= irq;
        end
    end

    logic [irq_cnt:1] interrupt;

    assign interrupt = ip & ie;

    // Beautiful synthesizable SystemVerilog code:
	always_comb begin
		id_o = '0;   /* 0 = NO IRQ */
		for(int i = 1; i <= irq_cnt; i++) begin
			if (interrupt[i]) begin
				id_o = (logic [$clog2(irq_cnt):0])'(i);
				break;
			end
		end
	end

    assign irq_o = | interrupt;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLD 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    always_ff @(posedge clk) begin
        if (reset) begin
            mip <= '0;
        end
        else begin
            mip <= IRQ_i;
        end
    end
    
    always_ff @(posedge clk) begin
        if (mstatus[3] && (mie & mip) != '0 && !interrupt_ack_i) begin
            interrupt_pending_o <= 1;
            if (mip[11] & mie[11])                   // Machine External
                Interruption_Code <= M_EXT_INT;
            else if (mip[3] & mie[3])                // Machine Software
                Interruption_Code <= M_SW_INT;
            else if (mip[7] & mie[7])                // Machine Timer
                Interruption_Code <= M_TIM_INT;

        end 
        else begin
            interrupt_pending_o <= 0;
        end
    end
*/
endmodule
