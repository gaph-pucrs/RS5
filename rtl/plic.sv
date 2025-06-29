/*!\file plic.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 *
 * \brief
 * Peripheral Local Interrupt Controller.
 */

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

    /* Register mux */
    logic [31:0] reg_val;
    always_comb begin
        case (addr_i)
            24'h200004: reg_val = {{31-$clog2(i_cnt){1'b0}}, id_r}; /* ID */
            24'h001000: reg_val = {{31-i_cnt{1'b0}}, ip, 1'b0};     /* IP */
            24'h002000: reg_val = {{31-i_cnt{1'b0}}, ie, 1'b0};     /* IE */
            default:    reg_val = '0;
        endcase
    end

    /* Byte access */
    /* The number of bits used depends on i_cnt */
    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] write_val;
    /* verilator lint_on UNUSEDSIGNAL */
    assign write_val[31:24] = we_i[3] ? data_i[31:24] : reg_val[31:24];
    assign write_val[23:16] = we_i[2] ? data_i[23:16] : reg_val[23:16];
    assign write_val[15: 8] = we_i[1] ? data_i[15: 8] : reg_val[15: 8];
    assign write_val[ 7: 0] = we_i[0] ? data_i[ 7: 0] : reg_val[ 7: 0];

    /* Read */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            data_o <= '0;
        end  
        else if (en_i == 1'b1 && we_i == '0) begin
            data_o <= reg_val;
        end
    end

    /* Write */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            ie      <= '0;
        end
        else if (en_i == 1'b1 && we_i != '0 && addr_i == 24'h002000) begin
            ie <= write_val[i_cnt:1];
        end 
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            iack_o <= '0;
        end
        else begin 
            if (en_i == 1'b1 && we_i != '0 && addr_i == 24'h200004) 
                iack_o[write_val[$clog2(i_cnt+1):0]] <= 1'b1;
            else
                iack_o <= '0;
        end
    end
endmodule
