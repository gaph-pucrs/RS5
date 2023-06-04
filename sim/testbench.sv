/*!\file testbench.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  December 2021
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Testbench for pucrs-rv simulation.
 *
 * \detailed
 * Testbench for pucrs-rv simulation.
 */

`timescale 1ns/1ps

`include "../rtl/my_pkg.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decode.sv"
`include "../rtl/ALU.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
`include "../rtl/PUC_RS5.sv"
`include "../rtl/rtc.sv"
`include "./RAM_mem.sv"

//////////////////////////////////////////////////////////////////////////////
// CPU TESTBENCH
//////////////////////////////////////////////////////////////////////////////

module testbench
    import my_pkg::*;
(
    input logic clk_i,
    input logic rst_i
);

/* verilator lint_off UNUSEDSIGNAL */
logic [31:0]  instruction_address;
logic         interrupt_ack;
logic [63:0]  mtime;
logic [63:0]  data_rtc;
/* verilator lint_on UNUSEDSIGNAL */
logic [31:0]  instruction;
logic         enable_ram, enable_tb, enable_rtc, mem_operation_enable;
logic [31:0]  mem_address, mem_data_read, mem_data_write;
logic [3:0]   mem_write_enable;
byte          char;
logic [31:0]  data_ram, data_tb;
logic         enable_tb_r, enable_rtc_r;
logic [31:0]  IRQ;
logic         mti;

assign IRQ = {24'h0, mti, 7'h0};

//////////////////////////////////////////////////////////////////////////////
// CPU INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    PUC_RS5 dut (
        .clk(clk_i), 
        .reset(rst_i), 
        .stall(1'b0),
        .instruction_i(instruction), 
        .mem_data_i(mem_data_read), 
        .IRQ_i(IRQ),
        .instruction_address_o(instruction_address), 
        .mem_operation_enable_o(mem_operation_enable), 
        .mem_write_enable_o(mem_write_enable),
        .mem_address_o(mem_address),
        .mem_data_o(mem_data_write),
        .interrupt_ack_o(interrupt_ack)
    );

//////////////////////////////////////////////////////////////////////////////
// RAM INSTANTIATION
//////////////////////////////////////////////////////////////////////////////

    RAM_mem RAM_MEM(
        .clk(clk_i), 
        .instruction_address_i(instruction_address[15:0]), 
        .instruction_o(instruction),
        .operation_enable_i(enable_ram), 
        .write_enable_i(mem_write_enable), 
        .data_address_i(mem_address[15:0]), 
        .data_i(mem_data_write), 
        .data_o(data_ram)
    );

    rtc rtc(
        .clk(clk_i),
        .en_i(enable_rtc),
        .addr_i(mem_address[3:0]),
        .we_i({4'h0, mem_write_enable}),
        .data_i({32'h0, mem_data_write}),
        .data_o(data_rtc),     
        .mti_o(mti),
        .mtime_o(mtime)
    );

    always_comb begin
        if (enable_tb_r) begin
            mem_data_read = data_tb;
        end
        else if (enable_rtc_r) begin
            mem_data_read = data_rtc[31:0];
        end
        else begin
            mem_data_read = data_ram;
        end
    end

    always_comb begin
        if (mem_operation_enable) begin
            if (mem_address[31:28] < 4'h2) begin
                enable_ram = 1'b1;
                enable_tb  = 1'b0;
                enable_rtc = 1'b0;
            end
            else if (mem_address[31:28] < 4'h8) begin
                enable_ram = 1'b0;
                enable_tb  = 1'b0;
                enable_rtc = 1'b1;
            end
            else begin
                enable_ram = 1'b0;
                enable_tb  = 1'b1;
                enable_rtc = 1'b0;
            end
        end
        else begin
            enable_ram = 1'b0;
            enable_tb  = 1'b0;
            enable_rtc = 1'b0;
        end
    end
    
    always_ff @(posedge clk_i) begin
        enable_tb_r  <= enable_tb;
        enable_rtc_r <= enable_rtc;
    end


//////////////////////////////////////////////////////////////////////////////
// Memory Mapped regs
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk_i) begin
        if (enable_tb) begin
            // OUTPUT REG
            if ((mem_address == 32'h80004000 || mem_address == 32'h80001000) && mem_write_enable != '0) begin
                char <= mem_data_write[7:0];
                $write("%c",char);
            end
            // END REG
            if (mem_address == 32'h80000000 && mem_write_enable != '0) begin
                $display("# %t END OF SIMULATION",$time);
                $finish;
            end
            // TIMER REG
            if (mem_address == 32'h80006000 && mem_write_enable == '0) begin
                data_tb <= 32'($time/1000);
            end
        end 
        else begin
            data_tb <= '0;
        end
    end

endmodule
