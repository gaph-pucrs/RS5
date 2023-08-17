/*!\file RS5.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Is the top Module of RS5 processor core.
 *
 * \detailed
 * This is the top Module of the RS5 processor core
 * and is responsible for the instantiation of the lower level modules
 * and also defines the interface ports (inputs and outputs) os the processor.
 */
/*
`include "../rtl/RS5_pkg.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decode.sv"
`include "../rtl/muldiv.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/mmu.sv"
`include "../rtl/CSRBank.sv"
*/

module RS5
    import RS5_pkg::*;
(
    input  logic                    clk,
    input  logic                    reset,
    input  logic                    stall,

    input  logic [31:0]             instruction_i,
    input  logic [31:0]             mem_data_i,
    input  logic [63:0]             mtime_i,
    input  logic [31:0]             irq_i,

    output logic [31:0]             instruction_address_o,
    output logic                    mem_operation_enable_o,
    output logic  [3:0]             mem_write_enable_o,
    output logic [31:0]             mem_address_o,
    output logic [31:0]             mem_data_o,
    output logic                    interrupt_ack_o
);

//////////////////////////////////////////////////////////////////////////////
// Global signals
//////////////////////////////////////////////////////////////////////////////
    logic            jump;
    logic            hazard;

`ifdef MULTICYCLE_INSTRUCTIONS
    logic            hold;
`endif

`ifdef XOSVM
    logic            mmu_inst_fault;
    logic            mmu_data_fault;
`endif
    privilegeLevel_e privilege;
    logic   [31:0]   jump_target;

    logic            mem_read_enable;
    logic    [3:0]   mem_write_enable;
    /* verilator lint_off UNUSEDSIGNAL */
    logic   [31:0]   mem_address;
    /* verilator lint_on UNUSEDSIGNAL */
    logic   [31:0]   instruction_address;

//////////////////////////////////////////////////////////////////////////////
// Fetch signals
//////////////////////////////////////////////////////////////////////////////

    logic           stall_fetch;

//////////////////////////////////////////////////////////////////////////////
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_decode;
    logic    [2:0]  tag_decode;
    logic           stall_decode;

//////////////////////////////////////////////////////////////////////////////
// RegBank signals
//////////////////////////////////////////////////////////////////////////////

    logic   [4:0]   rs1, rs2;
    logic   [31:0]  regbank_data1, regbank_data2;
    logic   [31:0]  rs1_data_read, rs2_data_read;
    logic   [4:0]   rd;
    logic   [31:0]  regbank_data_writeback;
    logic           regbank_write_enable_int, regbank_write_enable;

//////////////////////////////////////////////////////////////////////////////
// Execute signals
//////////////////////////////////////////////////////////////////////////////

    iType_e         instruction_operation_execute;
    logic   [31:0]  first_operand_execute, second_operand_execute, third_operand_execute;
    logic   [31:0]  instruction_execute;
    logic   [31:0]  pc_execute;
    logic    [2:0]  tag_execute;
    logic           exc_ilegal_inst_execute;
    logic           exc_misaligned_fetch_execute;
`ifdef XOSVM
    logic           exc_inst_access_fault_execute;
`endif

//////////////////////////////////////////////////////////////////////////////
// Retire signals
//////////////////////////////////////////////////////////////////////////////

    iType_e         instruction_operation_retire;
    logic   [31:0]  result_retire;
    logic           killed;

`ifdef HARDWARE_MULTIPLICATION
    logic [63:0]    mul_result;
    logic [63:0]    mulh_result;
    logic [63:0]    mulhsu_result;
`endif

//////////////////////////////////////////////////////////////////////////////
// CSR Bank signals
//////////////////////////////////////////////////////////////////////////////

    logic           csr_read_enable, csr_write_enable;
    csrOperation_e  csr_operation;
    logic   [11:0]  csr_addr;
    logic   [31:0]  csr_data_to_write, csr_data_read;
    logic   [31:0]  mepc, mtvec;
    logic           RAISE_EXCEPTION, MACHINE_RETURN;
    logic           interrupt_pending;
    exceptionCode_e Exception_Code;
`ifdef XOSVM
    logic   [31:0]  mvmdo, mvmio, mvmds, mvmis;
    logic           mvmctl;
    logic           mmu_en;
`endif

//////////////////////////////////////////////////////////////////////////////
// Assigns
//////////////////////////////////////////////////////////////////////////////
`ifdef XOSVM
    assign mmu_en = privilege != privilegeLevel_e'(2'b11) && mvmctl;
`endif

    assign regbank_write_enable =   (rd == '0) 
                                    ? 0 
                                    : regbank_write_enable_int;

    assign rs1_data_read =  (rs1 == rd && regbank_write_enable) 
                            ? regbank_data_writeback 
                            : regbank_data1;

    assign rs2_data_read =  (rs2 == rd && regbank_write_enable) 
                            ? regbank_data_writeback 
                            : regbank_data2;

    assign stall_fetch = (stall
                    `ifdef MULTICYCLE_INSTRUCTIONS
                        | hold
                    `endif
                        );

    assign stall_decode = (stall
                    `ifdef MULTICYCLE_INSTRUCTIONS
                        | hold
                    `endif
                        );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    fetch fetch1 (
        .clk                    (clk), 
        .reset                  (reset), 
        .stall                  (stall_fetch),
        .hazard_i               (hazard), 
        .jump_i                 (jump), 
        .jump_target_i          (jump_target),
        .instruction_address_o  (instruction_address), 
        .pc_o                   (pc_decode), 
        .tag_o                  (tag_decode),
        .mepc_i                 (mepc), 
        .mtvec_i                (mtvec),
        .exception_raised_i     (RAISE_EXCEPTION), 
        .machine_return_i       (MACHINE_RETURN), 
        .interrupt_ack_i        (interrupt_ack_o)
    );

`ifdef XOSVM
    mmu i_mmu (
        .en_i           (mmu_en),
        .offset_i       (mvmio),
        .size_i         (mvmis),
        .address_i      (instruction_address),
        .exception_o    (mmu_inst_fault),
        .address_o      (instruction_address_o)
    );
`else
    assign instruction_address_o = instruction_address;
`endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    decode decoder1 (
        .clk                        (clk), 
        .reset                      (reset),
        .stall                      (stall_decode),
        .instruction_i              (instruction_i), 
        .pc_i                       (pc_decode), 
        .tag_i                      (tag_decode), 
        .rs1_data_read_i            (rs1_data_read), 
        .rs2_data_read_i            (rs2_data_read), 
        .rs1_o                      (rs1), 
        .rs2_o                      (rs2), 
        .rd_o                       (rd), 
        .first_operand_o            (first_operand_execute), 
        .second_operand_o           (second_operand_execute), 
        .third_operand_o            (third_operand_execute), 
        .pc_o                       (pc_execute), 
        .instruction_o              (instruction_execute), 
        .tag_o                      (tag_execute), 
        .instruction_operation_o    (instruction_operation_execute), 
        .hazard_o                   (hazard),
    `ifdef XOSVM
        .exc_inst_access_fault_i    (mmu_inst_fault),
        .exc_inst_access_fault_o    (exc_inst_access_fault_execute),
    `endif
        .exc_ilegal_inst_o          (exc_ilegal_inst_execute),
        .exc_misaligned_fetch_o     (exc_misaligned_fetch_execute)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

`ifdef PROTO
    DRAM_RegBank RegBankA (
        .clk        (clk),
        .we         (regbank_write_enable),
        .a          (rd),
        .d          (regbank_data_writeback),
        .dpra       (rs1),
        .dpo        (regbank_data1)
    );

    DRAM_RegBank RegBankB (
        .clk        (clk),
        .we         (regbank_write_enable),
        .a          (rd),
        .d          (regbank_data_writeback),
        .dpra       (rs2),
        .dpo        (regbank_data2)
    );

`else
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
`endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    execute execute1 (
        .clk                    (clk), 
        .reset                  (reset), 
        .stall                  (stall),
    `ifdef MULTICYCLE_INSTRUCTIONS
        .hold_o                 (hold),
    `endif
        .instruction_i          (instruction_execute), 
        .pc_i                   (pc_execute), 
        .first_operand_i        (first_operand_execute), 
        .second_operand_i       (second_operand_execute), 
        .third_operand_i        (third_operand_execute),
        .instruction_operation_i(instruction_operation_execute), 
        .tag_i                  (tag_execute), 
        .privilege_i            (privilege),
        .exc_ilegal_inst_i      (exc_ilegal_inst_execute),
        .exc_misaligned_fetch_i (exc_misaligned_fetch_execute),
    `ifdef XOSVM
        .exc_inst_access_fault_i(exc_inst_access_fault_execute),
        .exc_load_access_fault_i(mmu_data_fault),
    `endif
        .killed_o               (killed),
        .write_enable_o         (regbank_write_enable_int),
        .instruction_operation_o(instruction_operation_retire), 
        .result_o               (result_retire),
    `ifdef HARDWARE_MULTIPLICATION
        .mul_result_o           (mul_result),
        .mulh_result_o          (mulh_result),
        .mulhsu_result_o        (mulhsu_result),
    `endif
        .mem_address_o          (mem_address), 
        .mem_read_enable_o      (mem_read_enable), 
        .mem_write_enable_o     (mem_write_enable),
        .mem_write_data_o       (mem_data_o),
        .csr_address_o          (csr_addr), 
        .csr_read_enable_o      (csr_read_enable), 
        .csr_data_read_i        (csr_data_read),
        .csr_write_enable_o     (csr_write_enable), 
        .csr_operation_o        (csr_operation), 
        .csr_data_o             (csr_data_to_write), 
        .jump_o                 (jump),
        .jump_target_o          (jump_target),
        .interrupt_pending_i    (interrupt_pending),
        .interrupt_ack_o        (interrupt_ack_o),
        .machine_return_o       (MACHINE_RETURN),
        .raise_exception_o      (RAISE_EXCEPTION), 
        .exception_code_o       (Exception_Code)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    retire retire1 (
        .instruction_operation_i(instruction_operation_retire),
        .result_i               (result_retire),
    `ifdef HARDWARE_MULTIPLICATION
        .mul_result_i           (mul_result),
        .mulh_result_i          (mulh_result),
        .mulhsu_result_i        (mulhsu_result),
    `endif
        .mem_data_i             (mem_data_i), 
        .regbank_data_o         (regbank_data_writeback)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSRBank CSRBank1 (
        .clk                        (clk), 
        .reset                      (reset), 
        .read_enable_i              (csr_read_enable), 
        .write_enable_i             (csr_write_enable), 
        .operation_i                (csr_operation), 
        .address_i                  (csr_addr), 
        .data_i                     (csr_data_to_write), 
        .killed                     (killed),
        .out                        (csr_data_read),
    `ifdef DEBUG
        .instruction_operation_i    (instruction_operation_execute),
        .hazard                     (hazard),
        .stall                      (stall),
    `endif
        .raise_exception_i          (RAISE_EXCEPTION), 
        .machine_return_i           (MACHINE_RETURN),
        .exception_code_i           (Exception_Code), 
        .pc_i                       (pc_execute), 
        .instruction_i              (instruction_execute),
        .jump_i                     (jump),
        .jump_target_i              (jump_target),
        .mtime_i                    (mtime_i),
        .irq_i                      (irq_i),
        .interrupt_ack_i            (interrupt_ack_o),
        .interrupt_pending_o        (interrupt_pending),
        .privilege_o                (privilege), 
        .mepc                       (mepc), 
    `ifdef XOSVM
        .mvmctl_o                   (mvmctl),
        .mvmdo_o                    (mvmdo),
        .mvmds_o                    (mvmds),
        .mvmio_o                    (mvmio),
        .mvmis_o                    (mvmis),
    `endif
        .mtvec                      (mtvec)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// MEMORY SIGNALS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (
            (!killed && (mem_write_enable != '0 || mem_read_enable))
        `ifdef XOSVM
            && !mmu_data_fault
        `endif
        ) begin
            mem_operation_enable_o = 1;
        end
        else begin
            mem_operation_enable_o = 0;
        end
    end

`ifdef XOSVM
    mmu d_mmu (
        .en_i           (mmu_en),
        .offset_i       (mvmdo),
        .size_i         (mvmds),
        .address_i      (mem_address),
        .exception_o    (mmu_data_fault),
        .address_o      (mem_address_o)
    );
`else
    assign mem_address_o = mem_address;
`endif

    assign mem_write_enable_o = mem_write_enable;

endmodule
