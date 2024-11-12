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

`include "RS5_pkg.sv"

module RS5
    import RS5_pkg::*;
#(
`ifndef SYNTH
    parameter bit           DEBUG          = 1'b0,
    parameter string        DBG_REG_FILE   = "./debug/regBank.txt",
    parameter bit           PROFILING      = 1'b0,
    parameter string        PROFILING_FILE = "./debug/Report.txt",
`endif
    parameter environment_e Environment    = ASIC,
    parameter mul_e         MULEXT         = MUL_M,
    parameter atomic_e      AMOEXT         = AMO_A,
    parameter bit           COMPRESSED     = 1'b0,
    parameter bit           VEnable        = 1'b0,
    parameter int           VLEN           = 256,
    parameter bit           XOSVMEnable    = 1'b0,
    parameter bit           ZIHPMEnable    = 1'b0,
    parameter bit           ZKNEEnable     = 1'b0,
    parameter bit           BRANCHPRED     = 1'b1
)
(
    input  logic                    clk,
    input  logic                    reset_n,
    input  logic                    sys_reset_i,
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
    logic            hold;

    logic            mmu_inst_fault;
    logic            mmu_data_fault;

    privilegeLevel_e privilege;
    logic   [31:0]   jump_target;

    logic            mem_read_enable;
    logic    [3:0]   mem_write_enable;
    logic   [31:0]   mem_address;
    logic   [31:0]   instruction_address;

//////////////////////////////////////////////////////////////////////////////
// Fetch signals
//////////////////////////////////////////////////////////////////////////////

    logic           enable_fetch;

//////////////////////////////////////////////////////////////////////////////
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_decode;
    logic           enable_decode;
    logic           jump_misaligned;

//////////////////////////////////////////////////////////////////////////////
// RegBank signals
//////////////////////////////////////////////////////////////////////////////

    logic    [4:0]  rs1, rs2;
    logic   [31:0]  regbank_data1, regbank_data2;
    logic    [4:0]  rd_retire;
    logic   [31:0]  regbank_data_writeback;
    logic           regbank_write_enable;

//////////////////////////////////////////////////////////////////////////////
// Execute signals
//////////////////////////////////////////////////////////////////////////////

    iType_e         instruction_operation_execute;
    iTypeAtomic_e   atomic_operation_execute;
    iTypeVector_e   vector_operation_execute;
    logic   [31:0]  rs1_data_execute, rs2_data_execute, second_operand_execute;
    logic   [31:0]  instruction_execute;
    logic   [31:0]  pc_execute;
    logic    [4:0]  rd_execute;
    logic    [4:0]  rs1_execute;
    logic           exc_ilegal_inst_execute;
    logic           exc_misaligned_fetch_execute;
    logic           exc_inst_access_fault_execute;
    logic           instruction_compressed_execute;
    logic   [31:0]  vtype, vlen;


//////////////////////////////////////////////////////////////////////////////
// Retire signals
//////////////////////////////////////////////////////////////////////////////

    iType_e         instruction_operation_retire;
    logic   [31:0]  result_retire;
    logic           killed;

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

    /* Signals enabled with XOSVM */
    /* verilator lint_off UNUSEDSIGNAL */
    logic   [31:0]  mvmdo, mvmio, mvmds, mvmis, mvmdm, mvmim;
    logic           mvmctl;
    logic           mmu_en;
    /* verilator lint_on UNUSEDSIGNAL */

//////////////////////////////////////////////////////////////////////////////
// Assigns
//////////////////////////////////////////////////////////////////////////////

    if (XOSVMEnable == 1'b1) begin : gen_xosvm_mmu_on
        assign mmu_en = privilege != privilegeLevel_e'(2'b11) && mvmctl == 1'b1;
    end
    else begin : gen_xosvm_mmu_off
        assign mmu_en = 1'b0;
    end

    assign enable_fetch  = !(stall || hold || hazard);
    assign enable_decode = !(stall || hold);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic        jump_rollback;
    logic        jumping;
    logic        ctx_switch;
    logic        bp_take_fetch;
    logic        bp_rollback;
    logic        compressed_decode;
    logic [31:0] bp_target;
    logic [31:0] ctx_switch_target;
    logic [31:0] instruction_decode;

    fetch #(
        .COMPRESSED(COMPRESSED),
        .BRANCHPRED(BRANCHPRED)
    ) fetch1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset              (sys_reset_i),
        .enable_i               (enable_fetch),
        .ctx_switch_i           (ctx_switch),
        .jump_rollback_i        (jump_rollback),
        .ctx_switch_target_i    (ctx_switch_target),
        .bp_take_i              (bp_take_fetch),
        .bp_target_i            (bp_target),
        .jumping_o              (jumping),
        .bp_rollback_o          (bp_rollback),
        .jump_misaligned_o      (jump_misaligned),
        .compressed_o           (compressed_decode),
        .instruction_address_o  (instruction_address), 
        .instruction_data_i     (instruction_i),
        .instruction_o          (instruction_decode),
        .pc_o                   (pc_decode)
    );

    if (XOSVMEnable == 1'b1) begin : gen_xosvm_i_mmu_on
        mmu i_mmu (
            .en_i           (mmu_en               ),
            .mask_i         (mvmim                ),
            .offset_i       (mvmio                ),
            .size_i         (mvmis                ),
            .address_i      (instruction_address  ),
            .exception_o    (mmu_inst_fault       ),
            .address_o      (instruction_address_o)
        );
    end
    else begin : gen_xosvm_i_mmu_off
        assign mmu_inst_fault        = 1'b0;
        assign instruction_address_o = instruction_address;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic        bp_taken_exec;
    logic        write_enable_exec;
    logic [31:0] result_exec;
    logic [31:0] jump_imm_target_exec;

    decode # (
        .MULEXT    (MULEXT    ),
        .AMOEXT    (AMOEXT    ),
        .COMPRESSED(COMPRESSED),
        .ZKNEEnable(ZKNEEnable),
        .VEnable   (VEnable   ),
        .BRANCHPRED(BRANCHPRED)
    ) decoder1 (
        .clk                        (clk),
        .reset_n                    (reset_n),
        .enable                     (enable_decode),
        .instruction_i              (instruction_decode),
        .pc_i                       (pc_decode),
        .rs1_data_read_i            (regbank_data1),
        .rs2_data_read_i            (regbank_data2),
        .rd_retire_i                (rd_retire),
        .writeback_i                (regbank_data_writeback),
        .result_i                   (result_exec),
        .regbank_we_i               (regbank_write_enable),
        .execute_we_i               (write_enable_exec),
        .rs1_o                      (rs1),
        .rs2_o                      (rs2),
        .rd_o                       (rd_execute),
        .instr_rs1_o                (rs1_execute),
        .csr_address_o              (csr_addr),
        .rs1_data_o                 (rs1_data_execute),
        .rs2_data_o                 (rs2_data_execute),
        .second_operand_o           (second_operand_execute),
        .pc_o                       (pc_execute),
        .instruction_o              (instruction_execute),
        .jump_imm_target_o          (jump_imm_target_exec),
        .compressed_o               (instruction_compressed_execute),
        .instruction_operation_o    (instruction_operation_execute),
        .atomic_operation_o         (atomic_operation_execute),
        .vector_operation_o         (vector_operation_execute),
        .hazard_o                   (hazard),
        .killed_o                   (killed),
        .ctx_switch_i               (ctx_switch),
        .jumping_i                  (jumping),
        .jump_rollback_i            (jump_rollback),
        .rollback_i                 (bp_rollback),
        .compressed_i               (compressed_decode),
        .jump_misaligned_i          (jump_misaligned),
        .bp_take_o                  (bp_take_fetch),
        .bp_taken_o                 (bp_taken_exec),
        .bp_target_o                (bp_target),
        .exc_inst_access_fault_i    (mmu_inst_fault),
        .exc_inst_access_fault_o    (exc_inst_access_fault_execute),
        .exc_ilegal_inst_o          (exc_ilegal_inst_execute),
        .exc_misaligned_fetch_o     (exc_misaligned_fetch_execute)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (Environment == FPGA) begin :RegFileFPGA_blk
        DRAM_RegBank RegBankA (
            .clk        (clk),
            .we         (regbank_write_enable),
            .a          (rd_retire),
            .d          (regbank_data_writeback),
            .dpra       (rs1),
            .dpo        (regbank_data1)
        );

        DRAM_RegBank RegBankB (
            .clk        (clk),
            .we         (regbank_write_enable),
            .a          (rd_retire),
            .d          (regbank_data_writeback),
            .dpra       (rs2),
            .dpo        (regbank_data2)
        );
    end
    else begin : RegFileFF_blk
        regbank #(
        `ifndef SYNTH
            .DEBUG      (DEBUG       ),
            .DBG_FILE   (DBG_REG_FILE)
        `endif
        ) regbankff (
            .clk        (clk),
            .reset_n    (reset_n),
            .rs1        (rs1),
            .rs2        (rs2),
            .rd         (rd_retire),
            .enable     (regbank_write_enable),
            .data_i     (regbank_data_writeback),
            .data1_o    (regbank_data1),
            .data2_o    (regbank_data2)
        );
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic [31:0] reservation_data;

    execute #(
        .Environment (Environment),
        .MULEXT      (MULEXT),
        .AMOEXT      (AMOEXT),
        .ZKNEEnable  (ZKNEEnable),
        .VEnable     (VEnable),
        .VLEN        (VLEN),
        .BRANCHPRED  (BRANCHPRED)
    ) execute1 (
        .clk                     (clk),
        .reset_n                 (reset_n),
        .stall                   (stall),
        .instruction_i           (instruction_execute),
        .pc_i                    (pc_execute),
        .rs1_data_i              (rs1_data_execute),
        .rs2_data_i              (rs2_data_execute),
        .second_operand_i        (second_operand_execute),
        .rd_i                    (rd_execute),
        .rs1_i                   (rs1_execute),
        .instruction_operation_i (instruction_operation_execute),
        .instruction_compressed_i(instruction_compressed_execute),
        .atomic_operation_i      (atomic_operation_execute),
        .vector_operation_i      (vector_operation_execute),
        .privilege_i             (privilege),
        .exc_ilegal_inst_i       (exc_ilegal_inst_execute),
        .exc_misaligned_fetch_i  (exc_misaligned_fetch_execute),
        .exc_inst_access_fault_i (exc_inst_access_fault_execute),
        .exc_load_access_fault_i (mmu_data_fault),
        .hold_o                  (hold),
        .write_enable_o          (regbank_write_enable),
        .write_enable_fwd_o      (write_enable_exec),
        .instruction_operation_o (instruction_operation_retire),
        .result_o                (result_retire),
        .result_fwd_o            (result_exec),
        .rd_o                    (rd_retire),
        .mem_address_o           (mem_address),
        .mem_read_enable_o       (mem_read_enable),
        .mem_write_enable_o      (mem_write_enable),
        .mem_write_data_o        (mem_data_o),
        .mem_read_data_i         (mem_data_i),
        .csr_address_i           (csr_addr),
        .csr_read_enable_o       (csr_read_enable),
        .csr_data_read_i         (csr_data_read),
        .csr_write_enable_o      (csr_write_enable),
        .csr_operation_o         (csr_operation),
        .csr_data_o              (csr_data_to_write),
        .vtype_o                 (vtype),
        .vlen_o                  (vlen),
        .bp_taken_i              (bp_taken_exec),
        .ctx_switch_o            (ctx_switch),
        .jump_rollback_o         (jump_rollback),
        .ctx_switch_target_o     (ctx_switch_target),
        .jump_imm_target_i       (jump_imm_target_exec),
        .reservation_data_i      (reservation_data),
        .jump_target_o           (jump_target),
        .interrupt_pending_i     (interrupt_pending),
        .mtvec_i                 (mtvec),
        .mepc_i                  (mepc),
        .jump_o                  (jump),
        .interrupt_ack_o         (interrupt_ack_o),
        .machine_return_o        (MACHINE_RETURN),
        .raise_exception_o       (RAISE_EXCEPTION),
        .exception_code_o        (Exception_Code)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    retire #(
        .AMOEXT      (AMOEXT)
    ) retire1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .instruction_operation_i(instruction_operation_retire),
        .result_i               (result_retire),
        .mem_data_i             (mem_data_i),
        .reservation_data_o     (reservation_data),
        .regbank_data_o         (regbank_data_writeback)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSRBank #(
    `ifndef SYNTH
        .PROFILING     (PROFILING     ),
        .PROFILING_FILE(PROFILING_FILE),
    `endif
        .XOSVMEnable   (XOSVMEnable   ),
        .ZIHPMEnable   (ZIHPMEnable   ),
        .COMPRESSED    (COMPRESSED    ),
        .MULEXT        (MULEXT        ),
        .VEnable       (VEnable       ),
        .VLEN          (VLEN          )
    ) CSRBank1 (
        .clk                        (clk),
        .reset_n                    (reset_n),
        .sys_reset                  (sys_reset_i),
        .read_enable_i              (csr_read_enable),
        .write_enable_i             (csr_write_enable),
        .operation_i                (csr_operation),
        .address_i                  (csr_addr),
        .data_i                     (csr_data_to_write),
        .killed                     (killed),
        .out                        (csr_data_read),
        .instruction_operation_i    (instruction_operation_execute),
        .hazard                     (hazard),
        .stall                      (stall),
        .hold                       (hold),
        .vtype_i                    (vtype),
        .vlen_i                     (vlen),
        .raise_exception_i          (RAISE_EXCEPTION),
        .machine_return_i           (MACHINE_RETURN),
        .exception_code_i           (Exception_Code),
        .pc_i                       (pc_execute),
        .next_pc_i                  (pc_decode),
        .instruction_i              (instruction_execute),
        .instruction_compressed_i   (instruction_compressed_execute),
        .jump_misaligned_i          (jump_misaligned),
        .jump_i                     (jump),
        .jump_target_i              (jump_target),
        .mtime_i                    (mtime_i),
        .irq_i                      (irq_i),
        .interrupt_ack_i            (interrupt_ack_o),
        .interrupt_pending_o        (interrupt_pending),
        .privilege_o                (privilege),
        .mepc                       (mepc),
        .mtvec                      (mtvec),
    // XOSVM Signals
        .mvmctl_o                   (mvmctl),
        .mvmdo_o                    (mvmdo),
        .mvmds_o                    (mvmds),
        .mvmdm_o                    (mvmdm),
        .mvmio_o                    (mvmio),
        .mvmis_o                    (mvmis),
        .mvmim_o                    (mvmim)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// MEMORY SIGNALS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (XOSVMEnable == 1'b1) begin : gen_d_mmu_on
        mmu d_mmu (
            .en_i           (mmu_en        ),
            .mask_i         (mvmdm         ),
            .offset_i       (mvmdo         ),
            .size_i         (mvmds         ),
            .address_i      (mem_address   ),
            .exception_o    (mmu_data_fault),
            .address_o      (mem_address_o )
        );
    end
    else begin : gen_d_mmu_off
        assign mmu_data_fault = 1'b0;
        assign mem_address_o  = mem_address;
    end

    always_comb begin
        if ((mem_write_enable != '0 || mem_read_enable) && !mmu_data_fault)
            mem_operation_enable_o = 1'b1;
        else
            mem_operation_enable_o = 1'b0;
    end

    assign mem_write_enable_o = mem_write_enable;

endmodule
