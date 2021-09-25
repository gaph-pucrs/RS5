/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// ARV IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// Developed By: Willian Analdo Nunes /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// PUCRS, Porto Alegre, 2020      /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

/* 
BUG FIXED --> Signals of Asynchronous Memory sensivity list were not changing when necessary(to trigger the process), what caused a misreading.
BUG FIXED --> When two or more consecutives Load instructions were in the pipeline the signals remained stable what causes a misreading of the consecutives Loads because it doesn't triggers the Asynchrous read process(was solved by allowing the signals only in a Clock negedge).
BUG FIXED --> Branch taken instruction followed (1 or 2 stages behind) by a Store instruction. The Store instruction was writing when it shouldn't. Now the store instructions looks ahead in pipeline to see if a branch has been taken.
BUG FIXED --> When a Branch occurs but there was a bubble being propagated in the pipeline the tag of the instruction leaving the fetch stage was being increased wrongly.
BUG FIXED --> Arithmetic Shift was identified as an error in Berkeley Suite tests because the rtl operand used was ">>" what is logic shift, and for arithmetic shift is ">>>".
BUG FIXED --> Testbench was considering only the less significant part of the address what cause an wrong write when the address was bigger than 16 bits, now it considers a memory write only when its below a constant address, otherwise the chip enable is not even activated.
BUG FIXED --> JALR was adding the A operand(target address) to C operand(in J_type instructions OPC is 0), when it should add the OPA to the B operand(the offset imediate). */


/*
`include "./pkg.sv"
`include "./adder.sv"
`include "./branchUnit.sv"
`include "./bypassUnit.sv"
`include "./logicUnit.sv"
`include "./memoryUnit.sv"
`include "./shiftUnit.sv"
`include "./execute.sv"
`include "./fetch.sv"
`include "./decoder.sv"
`include "./operandFetch.sv"
`include "./retire.sv"
`include "./regbank.sv"
*/

import my_pkg::*;

module SRV(
    input logic clk,
    input logic reset,
    input logic [31:0] instruction,                     // Object Code coming from Memory
    output logic [31:0] i_address,                      // Instruction Address in Memory
    output logic read,                                    // Memory chip enable
    output logic [31:0] read_address,                    // Data address in Memory
    input logic [31:0] DATA_in,                         // Data coming from Memory
    output logic [31:0] DATA_out,                       // Data to be written in Memory
    output logic [31:0] write_address,
    output logic write,                                    // Memory Read or Write signal
    output logic [1:0] size);                                  // Size of write in memory


    logic jump_wb, jump_retire, bubble, write_retire, freeMem, we_retire;
    logic regD_we;
    logic [31:0] dataA, dataB, data_RLock; // dados do banco de reg
    logic [4:0] regA_add, regB_add;
    logic [31:0] regD_add, regD_add_int;
    logic [31:0] result_wb, data_wb, New_pc;
    logic [31:0] IR, instruction_OPFetch; 
    logic [31:0] NPC_decode, NPC_OPFetch, NPC_execute;
    logic [31:0] opA_execute, opB_execute, opC_execute;
    logic [31:0] write_address_retire;
    logic [3:0] decode_tag, OPF_tag, execute_tag, retire_tag;
    logic [4:0] regA_OPFetch, regB_OPFetch, regD_OPFetch;
    logic [1:0] size_retire; // we do BR 
    fmts fmt_OPFetch;
    instruction_type i_OPFetch, i_execute, i_retire;
    xu xu_OPFetch, xu_execute;
    logic [31:0] result_retire [1:0];
    logic [31:1] wrAddr;
    logic [1:0] MEMBlock;

//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////

    fetch #(32'h00000000) fetch1 (.clk(clk), .reset(reset), .ce(bubble), .jump(jump_wb), .result(New_pc), .instruction(instruction), 
                .i_address(i_address), .IR(IR), .NPC(NPC_decode), .tag_out(decode_tag));

//////////////////////////////////////////////////////////// DECODER ////////////////////////////////////////////////////////////////////////////////

    decoder decoder1 (.clk(clk), .reset(reset), .ce(bubble), .NPC_in(NPC_decode), .instruction(IR), .tag_in(decode_tag), 
                .regA(regA_OPFetch), .regB(regB_OPFetch), .regD(regD_OPFetch), .NPC_out(NPC_OPFetch), .fmt_out(fmt_OPFetch), 
                .instruction_out(instruction_OPFetch), .i_out(i_OPFetch), .xu_sel(xu_OPFetch), .tag_out(OPF_tag));

/////////////////////////////////////////////////////////// OP FETCH ////////////////////////////////////////////////////////////////////////////////

    operandFetch OPfecth (.clk(clk), .reset(reset), .we(regD_we), .NPC(NPC_OPFetch), .regA(regA_OPFetch), .regB(regB_OPFetch), .regD(regD_OPFetch), 
                .fmt(fmt_OPFetch), .instruction(instruction_OPFetch), .i(i_OPFetch), .xu_sel_in(xu_OPFetch), .tag_in(OPF_tag), .dataA(dataA), 
                .dataB(dataB), .regA_add(regA_add), .regB_add(regB_add), .opA_out(opA_execute), .opB_out(opB_execute), 
                .opC_out(opC_execute), .NPC_out(NPC_execute), .i_out(i_execute), .xu_sel(xu_execute), .tag_out(execute_tag), .wrAddr(wrAddr), .bubble(bubble));

/////////////////////////////////////////////////////////// execute /////////////////////////////////////////////////////////////////////////////////

    execute execute1 (.clk(clk), .reset(reset), .NPC(NPC_execute), .opA(opA_execute), .opB(opB_execute), .opC(opC_execute),
                .i(i_execute), .xu_sel(xu_execute), .tag_in(execute_tag),  .result_out(result_retire), .jump_out(jump_retire), 
                .tag_out(retire_tag), .we_out(we_retire),
                .DATA_in(DATA_in), .read_address(read_address), .read(read), .write(write_retire), .size(size_retire));

/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////

    retire retire1 (.clk(clk), .reset(reset), .result(result_retire), .jump(jump_retire), .we(we_retire),
                .tag_in(retire_tag), .reg_we(regD_we), .WrData(data_wb),
                .New_pc(New_pc), .jump_out(jump_wb),
                .write_in(write_retire), .size_in(size_retire),
                .write(write), .size(size), .write_address(write_address), .DATA_out(DATA_out));

/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////

    regbank regbank1 (.clk(clk), .reset(reset), .addra(regA_add), .addrb(regB_add), .addrw(wrAddr), .in(data_wb), .outa(dataA), .outb(dataB));

endmodule