/*!\file PUCRS-RV.sv
 * PUCRS-RV VERSION - 1.0 - Public Release
 *
 * Distribution:  September 2021
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Is the top Module of PUCRS-RV.
 *
 * \detailed
 * This is the top Module of the PUCRS-RV processor
 * and is responsible for the instantiation of the lower level modules
 * ans also defines the interface ports(inputs and outputs) os the processor.
 */
/*
`include "../rtl/pkg.sv"
`include "../rtl/xus.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decoder.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
*/
import my_pkg::*;

module PUCRS_RV(
    input  logic        clk,
    input  logic        reset,
    output logic [31:0] i_address,                      // Instruction Address in Memory
    input  logic [31:0] instruction,                    // Object Code coming from Memory
    output logic        read,                           // Memory chip enable
    output logic [31:0] read_address,                   // Data address in Memory
    input  logic [31:0] DATA_in,                        // Data coming from Memory
    output logic [31:0] DATA_out,                       // Data to be written in Memory
    output logic [31:0] write_address,
    output logic [3:0]  write,                          // Memory Write signal One Hot, each bit address 1 byte
    input  logic [31:0] IRQ
    );

    logic jump_wb, jump_retire, hazard, we_retire, pipe_clear;
    logic [3:0] we_mem_retire;
    logic regD_we;
    logic [31:0] dataA, dataB;
    logic [4:0] regA_add, regB_add;
    logic [31:0] data_wb, New_pc;
    logic [31:0] NPC_decode, NPC_execute;
    logic [31:0] opA_execute, opB_execute, opC_execute;
    logic [3:0] decode_tag, execute_tag, retire_tag, curr_retire_tag;
    i_type i_execute, i_retire;
    xu xu_execute;
    logic [31:0] result_retire [1:0];
    logic [31:1] wrAddr;

    logic [31:0] instruction_execute, instruction_retire;
    logic [31:0] NPC_retire;
    logic exception_execute, exception_retire;
    logic csr_rd_en, csr_wr_en;
    csr_ops csr_op;
    logic [11:0] csr_addr;
    logic [31:0] csr_data, csr_data_rd;
    logic [31:0] mepc, mtvec;
    logic RAISE_EXCEPTION, MACHINE_RETURN;
    EXCEPT_CODE   Exception_Code;
    logic Interupt_pending, Interupt_ACK;

    assign pipe_clear = hazard;

//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////

    fetch fetch1 (
        .clk(clk), .reset(reset), .pipe_clear(pipe_clear), .jump(jump_wb), .result(New_pc),
        .i_address(i_address), .NPC(NPC_decode), .tag_out(decode_tag),
        .EXCEPTION_RAISED(RAISE_EXCEPTION), .MACHINE_RETURN(MACHINE_RETURN), .Interupt_ACK(Interupt_ACK),
        .mepc(mepc), .mtvec(mtvec)
        );

/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////

    decoder decoder1 (
        .clk(clk), .reset(reset), .we(regD_we), 
        .NPC(NPC_decode), .instruction_in(instruction), .tag_in(decode_tag), 
        .dataA(dataA), .dataB(dataB), .regA_add(regA_add), .regB_add(regB_add), .opA_out(opA_execute), .opB_out(opB_execute), 
        .opC_out(opC_execute), .NPC_out(NPC_execute), .i_out(i_execute), .tag_out(execute_tag), .wrAddr(wrAddr), 
        .hazard(hazard), .pipe_clear(pipe_clear), .instruction_out(instruction_execute), .exception(exception_execute)
        );

/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////

    execute execute1 (
        .clk(clk), .reset(reset), .NPC(NPC_execute), .opA(opA_execute), .opB(opB_execute), .opC(opC_execute),
        .i(i_execute), .tag_in(execute_tag), .instruction_in(instruction_execute), .exception_in(exception_execute),
        .result_out(result_retire), .jump_out(jump_retire), .tag_out(retire_tag), .i_out(i_retire), .we_out(we_retire),
        .read_address(read_address), .read(read), .we_mem(we_mem_retire),
        .instruction_out(instruction_retire), .NPC_out(NPC_retire), .exception_out(exception_retire),
        .csr_rd_en(csr_rd_en), .csr_wr_en(csr_wr_en), .csr_op(csr_op), .csr_addr(csr_addr), .csr_data(csr_data), .csr_data_rd(csr_data_rd)
        );

/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////

    retire retire1 (
        .clk(clk), .reset(reset), .result(result_retire), .jump(jump_retire), .we(we_retire),
        .tag_in(retire_tag), .reg_we(regD_we), .WrData(data_wb),
        .New_pc(New_pc), .jump_out(jump_wb),
        .we_mem_in(we_mem_retire), .curr_retire_tag(curr_retire_tag),
        .DATA_in(DATA_in), .i(i_retire),
        .write(write), .write_address(write_address), .DATA_out(DATA_out),
        .instruction(instruction_retire), .NPC(NPC_retire),
        .exception('0), 
        .RAISE_EXCEPTION(RAISE_EXCEPTION), .Exception_Code(Exception_Code),
        .MACHINE_RETURN(MACHINE_RETURN),
        .Interupt_pending(Interupt_pending), .Interupt_ACK(Interupt_ACK)
        );

/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////

    regbank regbank1 (
        .clk(clk), .reset(reset), .addra(regA_add), .addrb(regB_add), .addrw(wrAddr), .in(data_wb), .outa(dataA), .outb(dataB)
        );

/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
    CSRBank CSRBank1 (
        .clk(clk), .reset(reset), .rd_en(csr_rd_en), .wr_en(csr_wr_en), .csr_op(csr_op), .addr(csr_addr), .data(csr_data), .out(csr_data_rd),
        .RAISE_EXCEPTION(RAISE_EXCEPTION), .Exception_Code(Exception_Code), .killed(execute_tag!=curr_retire_tag),
        .MACHINE_RETURN(MACHINE_RETURN),
        .privilege(Privilege'(2'b11)), .PC(NPC_retire), .instruction(instruction_retire),
        .mepc(mepc), .mtvec(mtvec),
        .IRQ(IRQ), .Interupt_pending(Interupt_pending), .Interupt_ACK(Interupt_ACK)
    );
    
endmodule