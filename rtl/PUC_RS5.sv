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
`include "../rtl/decode.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
*/
import my_pkg::*;

`define PROTO 1

module PUC_RS5 (
    input  logic        clk,
    input  logic        reset,
    input  logic        stall,

    input  logic [31:0] instruction_i,
    input  logic [31:0] mem_data_i,
    input  logic [31:0] IRQ_i,

    output logic [31:0] instruction_address_o,
    output logic        mem_operation_enable_o,
    output logic [3:0]  mem_write_enable_o,
    output logic [31:0] mem_address_o,
    output logic [31:0] mem_data_o,
    output logic        interrupt_ack_o
);

//////////////////////////////////////////////////////////////////////////////
// Global signals
//////////////////////////////////////////////////////////////////////////////

    logic hazard;
    logic [31:0] jump_target;

    logic [31:0] mem_read_address_int;
    logic [31:0] mem_write_address_int;

//////////////////////////////////////////////////////////////////////////////
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] pc_decode;
    logic [2:0] tag_decode;

//////////////////////////////////////////////////////////////////////////////
// RegBank signals
//////////////////////////////////////////////////////////////////////////////

    logic [4:0] rs1, rs2;
    logic [31:0] regbank_data1, regbank_data2, rs1_data_read, rs2_data_read;
    logic write_enable_regbank_int, regbank_write_enable;
    logic [4:0] rd;
    logic [31:0] regbank_data_writeback;

//////////////////////////////////////////////////////////////////////////////
// Execute signals
//////////////////////////////////////////////////////////////////////////////

    executionUnit_e xu_execute;
    iType_e instruction_operation_execute;
    logic [31:0] first_operand_execute, second_operand_execute, third_operand_execute;
    logic [31:0] instruction_execute;
    logic [31:0] pc_execute;
    logic [2:0] tag_execute;
    logic exception_execute;

//////////////////////////////////////////////////////////////////////////////
// Retire signals
//////////////////////////////////////////////////////////////////////////////

    logic jump_retire, we_retire;
    logic [3:0] mem_write_enable_retire;
    iType_e instruction_operation_retire;
    logic [31:0] instruction_retire;
    logic [31:0] result_retire [1:0];
    logic [2:0] tag_retire;
    logic [2:0] curr_retire_tag;
    logic [31:0] pc_retire;
    logic exception_retire;

//////////////////////////////////////////////////////////////////////////////
// CSR Bank signals
//////////////////////////////////////////////////////////////////////////////
    
    logic csr_read_enable, csr_write_enable;
    csrOperation_e csr_operation;
    logic [11:0] csr_addr;
    logic [31:0] csr_data_to_write, csr_data_read;
    logic [31:0] mepc, mtvec;
    logic RAISE_EXCEPTION, MACHINE_RETURN;
    exceptionCode_e   Exception_Code;
    logic Interrupt_pending;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    fetch fetch1 (
        .clk(clk), 
        .reset(reset), 
        .stall(stall),
        .hazard_i(hazard), 
        .jump_i(jump), 
        .jump_target_i(jump_target),
        .instruction_address_o(instruction_address_o), 
        .pc_o(pc_decode), 
        .tag_o(tag_decode),
        .mepc_i(mepc), 
        .mtvec_i(mtvec),
        .exception_raised_i(RAISE_EXCEPTION), 
        .machine_return_i(MACHINE_RETURN), 
        .interrupt_ack_i(interrupt_ack_o)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    assign rs1_data_read = (rs1 == rd && rd != '0) 
                            ? regbank_data_writeback 
                            : regbank_data1;

    assign rs2_data_read = (rs2 == rd && rd != '0) 
                            ? regbank_data_writeback 
                            : regbank_data2;
    
    decode decoder1 (
        .clk(clk), 
        .reset(reset),
        .stall(stall),
        .instruction_i(instruction_i), 
        .pc_i(pc_decode), 
        .tag_i(tag_decode), 
        .rs1_data_read(rs1_data_read), 
        .rs2_data_read(rs2_data_read), 
        .rs1_o(rs1), 
        .rs2_o(rs2), 
        .rd_o(rd), 
        .first_operand_o(first_operand_execute), 
        .second_operand_o(second_operand_execute), 
        .third_operand_o(third_operand_execute), 
        .pc_o(pc_execute), 
        .instruction_o(instruction_execute), 
        .tag_o(tag_execute), 
        .instruction_operation_o(instruction_operation_execute), 
        .hazard_o(hazard), 
        .exception_o(exception_execute)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    assign regbank_write_enable = (rd == 0) 
                                ? 0 
                                : write_enable_regbank_int; 

`ifndef PROTO
    regbank regbank1 (
        .clk(clk),
        .reset(reset),
        .rs1(rs1), 
        .rs2(rs2),
        .rd(rd), 
        .enable(regbank_write_enable),
        .data_i(regbank_data_writeback), 
        .data1_o(regbank_data1), 
        .data2_o(regbank_data2)
    );

`else
    regBankA RegBankA (
        .clk(clk),
        .we(regbank_write_enable),
        .a(rd),
        .d(regbank_data_writeback),
        .dpra(rs1),
        .dpo(regbank_data1)
    );

    regBankB RegBankB (
        .clk(clk),
        .we(regbank_write_enable),
        .a(rd),
        .d(regbank_data_writeback),
        .dpra(rs2),
        .dpo(regbank_data2)
    );
`endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    execute execute1 (
        .clk(clk), 
        .stall(stall),
        .instruction_i(instruction_execute), 
        .pc_i(pc_execute), 
        .first_operand_i(first_operand_execute), 
        .second_operand_i(second_operand_execute), 
        .third_operand_i(third_operand_execute),
        .instruction_operation_i(instruction_operation_execute), 
        .instruction_o(instruction_retire), 
        .tag_i(tag_execute), 
        .instruction_operation_o(instruction_operation_retire), 
        .pc_o(pc_retire), 
        .result_o(result_retire), 
        .tag_o(tag_retire), 
        .jump_o(jump_retire), 
        .write_enable_o(we_retire),
        .mem_read_address_o(mem_read_address_int), 
        .mem_write_enable_o(mem_write_enable_retire),
        .mem_read_o(read), 
        .csr_read_enable_o(csr_read_enable), 
        .csr_write_enable_o(csr_write_enable), 
        .csr_operation_o(csr_operation), 
        .csr_address_o(csr_addr), 
        .csr_data_o(csr_data_to_write), 
        .csr_data_read_i(csr_data_read),
        .exception_i(exception_execute),
        .exception_o(exception_retire)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    retire retire1 (
        .clk(clk), 
        .reset(reset), 
        .instruction_i(instruction_retire), 
        .pc_i(pc_retire),
        .results_i(result_retire), 
        .tag_i(tag_retire), 
        .mem_write_enable_i(mem_write_enable_retire),
        .write_enable_i(we_retire),
        .jump_i(jump_retire), 
        .instruction_operation_i(instruction_operation_retire),
        .exception_i('0), 
        .regbank_write_enable_o(write_enable_regbank_int), 
        .regbank_data_o(regbank_data_writeback),
        .jump_target_o(jump_target), 
        .jump_o(jump),
        .mem_write_enable_o(mem_write_enable_o), 
        .mem_write_address_o(mem_write_address_int), 
        .mem_data_o(mem_data_o),
        .mem_data_i(mem_data_i), 
        .current_retire_tag_o(curr_retire_tag),
        .exception_code_o(Exception_Code),
        .raise_exception_o(RAISE_EXCEPTION), 
        .machine_return_o(MACHINE_RETURN),
        .interrupt_ack_o(interrupt_ack_o),
        .interrupt_pending_i(Interrupt_pending)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSRBank CSRBank1 (
        .clk(clk), 
        .reset(reset), 
        .read_enable_i(csr_read_enable), 
        .write_enable_i(csr_write_enable), 
        .operation_i(csr_operation), 
        .address_i(csr_addr), 
        .data_i(csr_data_to_write), 
        .killed(tag_execute != curr_retire_tag),
        .out(csr_data_read),
        .raise_exception_i(RAISE_EXCEPTION), 
        .machine_return_i(MACHINE_RETURN),
        .exception_code_i(Exception_Code), 
        .privilege_i(privilegeLevel_e'(2'b11)), 
        .pc_i(pc_retire), 
        .instruction_i(instruction_retire),
        .IRQ_i(IRQ_i), 
        .interrupt_ack_i(interrupt_ack_o),
        .interrupt_pending_o(Interrupt_pending), 
        .mepc(mepc), 
        .mtvec(mtvec)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// MEMORY SIGNALS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always_comb begin
        if (mem_write_enable_o != '0) begin
            mem_address_o[31:2] <= mem_write_address_int[31:2];
        end
        else begin
            mem_address_o[31:2] <= mem_read_address_int[31:2];
        end
        mem_address_o[1:0] <= '0;

        if (mem_write_enable_o != '0 || read == 1) begin
            mem_operation_enable_o <= 1;
        end
        else begin
            mem_operation_enable_o <= 0;
        end
    end

endmodule