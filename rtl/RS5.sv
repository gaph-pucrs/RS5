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
    parameter rv32_e        RV32           = RV32M,
    parameter bit           COMPRESSED     = 1'b0,
    parameter bit           VEnable        = 1'b1,
    parameter int           VLEN           = 256,
    parameter atomic_ext_e  AEnable        = OFF,
    parameter bit           XOSVMEnable    = 1'b0,
    parameter bit           ZIHPMEnable    = 1'b0,
    parameter bit           ZKNEEnable     = 1'b0
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

    /* Unused without compressed */
    /* verilator lint_off UNUSEDSIGNAL */
    logic           instruction_prefetched;
    /* verilator lint_on UNUSEDSIGNAL */

//////////////////////////////////////////////////////////////////////////////
// Prefetch signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_prefetch;
    logic    [2:0]  tag_prefetch;
    logic           jumped, jumped_r;

//////////////////////////////////////////////////////////////////////////////
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_decode;
    logic    [2:0]  tag_decode;
    logic           enable_decode;
    logic           jump_misaligned;
    logic           instruction_compressed;
    logic           is_jumping;

//////////////////////////////////////////////////////////////////////////////
// RegBank signals
//////////////////////////////////////////////////////////////////////////////

    logic    [4:0]  rs1, rs2;
    logic   [31:0]  regbank_data1, regbank_data2;
    logic   [31:0]  rs1_data_read, rs2_data_read;
    logic    [4:0]  rd_decode;
    logic    [4:0]  rd;
    logic   [31:0]  regbank_data_writeback;
    logic           regbank_write_enable_int, regbank_write_enable;

//////////////////////////////////////////////////////////////////////////////
// Execute signals
//////////////////////////////////////////////////////////////////////////////

    logic [4:0] rd_atomic;
    logic retire_atomic;

    iType_e         instruction_operation_execute;
    iTypeVector_e   vector_operation_execute;
    iTypeAtomic_e   atomic_operation_execute;
    logic   [31:0]  first_operand_execute, second_operand_execute, third_operand_execute;
    logic   [31:0]  instruction_execute;
    logic   [31:0]  pc_execute;
    logic    [2:0]  tag_execute;
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

    assign regbank_write_enable =   (rd_decode == '0)
                                    ? 1'b0
                                    : regbank_write_enable_int;

    assign rs1_data_read =  (rs1 == rd_decode && regbank_write_enable)
                            ? regbank_data_writeback
                            : regbank_data1;

    assign rs2_data_read =  (rs2 == rd_decode && regbank_write_enable)
                            ? regbank_data_writeback
                            : regbank_data2;

    if (COMPRESSED == 1'b1) begin : gen_en_fetch_c
        assign enable_fetch = ~(stall || hold || instruction_prefetched);
    end
    else begin : gen_en_fetch_nc
        assign enable_fetch = ~(stall || hold || hazard);
    end

    assign enable_decode = ~(stall | hold);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    fetch #(
        .COMPRESSED(COMPRESSED)
    ) fetch1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .sys_reset              (sys_reset_i),
        .enable_i               (enable_fetch),
        .jump_i                 (jump),
        .jump_target_i          (jump_target),
        .mtvec_i                (mtvec),
        .mepc_i                 (mepc),
        .exception_raised_i     (RAISE_EXCEPTION),
        .machine_return_i       (MACHINE_RETURN),
        .interrupt_ack_i        (interrupt_ack_o),
        .hazard_i               (hazard),
        .jump_misaligned_o      (jump_misaligned),
        .jumped_o               (jumped),
        .jumped_r_o             (jumped_r),
        .instruction_address_o  (instruction_address), 
        .pc_o                   (pc_prefetch), 
        .tag_o                  (tag_prefetch)
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
//////////////////////////////////////////////////////////// C EXTENSION PREFETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    logic [31:0] instruction_decode;

    if (COMPRESSED == 1'b1) begin : gen_compressed_on

        logic enable_prefetch;

        logic [31:0] instruction_fetched;
        logic [31:0] instruction_decompressed;

        assign enable_prefetch = !(stall || hold);
        assign instruction_decode = instruction_compressed ? instruction_decompressed : instruction_fetched;

        align align (
            .clk                (clk),
            .reset_n            (reset_n),
            .enable_i           (enable_prefetch),
            .hazard_i           (hazard),
            .jumped_i           (jumped),
            .jumped_r           (jumped_r),
            .jump_i             (jump),
            .tag_i              (tag_prefetch),
            .pc_i               (pc_prefetch),
            .instruction_i      (instruction_i),
            .jump_misaligned_i  (jump_misaligned),
            .prefetched_o       (instruction_prefetched),
            .compressed_o       (instruction_compressed),
            .tag_o              (tag_decode),
            .pc_o               (pc_decode),
            .instruction_o      (instruction_fetched)
        );

        decompresser decompresser (
            .instruction_i (instruction_fetched[15:0]),
            .instruction_o (instruction_decompressed)
        );
    end
    else begin : gen_compressed_off
        assign instruction_decode = instruction_i;
        assign instruction_compressed = 1'b0;
        assign pc_decode = pc_prefetch;
        assign tag_decode = tag_prefetch;
        assign instruction_prefetched = 1'b0;
    end


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    assign is_jumping = jumped || jumped_r || jump;

    decode # (
        .ZKNEEnable(ZKNEEnable),
        .COMPRESSED(COMPRESSED),
        .AEnable   (AEnable),
        .VEnable   (VEnable)
    ) decoder1 (
        .clk                        (clk),
        .reset_n                    (reset_n),
        .enable                     (enable_decode),
        .instruction_i              (instruction_decode),
        .pc_i                       (pc_decode),
        .tag_i                      (tag_decode),
        .jumped_i                   (is_jumping),
        .rs1_data_read_i            (rs1_data_read),
        .rs2_data_read_i            (rs2_data_read),
        .rs1_o                      (rs1),
        .rs2_o                      (rs2),
        .rd_o                       (rd_decode),
        .first_operand_o            (first_operand_execute),
        .second_operand_o           (second_operand_execute),
        .third_operand_o            (third_operand_execute),
        .pc_o                       (pc_execute),
        .instruction_o              (instruction_execute),
        .compressed_i               (instruction_compressed),
        .compressed_o               (instruction_compressed_execute),
        .tag_o                      (tag_execute),
        .instruction_operation_o    (instruction_operation_execute),
        .vector_operation_o         (vector_operation_execute),
        .atomic_operation_o         (atomic_operation_execute),
        .hazard_o                   (hazard),
        .exc_inst_access_fault_i    (mmu_inst_fault),
        .exc_inst_access_fault_o    (exc_inst_access_fault_execute),
        .exc_ilegal_inst_o          (exc_ilegal_inst_execute),
        .exc_misaligned_fetch_o     (exc_misaligned_fetch_execute)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    assign rd = retire_atomic ? rd_atomic : rd_decode;

    if (Environment == FPGA) begin :RegFileFPGA_blk
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
            .rd         (rd),
            .enable     (regbank_write_enable),
            .data_i     (regbank_data_writeback),
            .data1_o    (regbank_data1),
            .data2_o    (regbank_data2)
        );
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    execute #(
        .Environment (Environment),
        .RV32        (RV32),
        .ZKNEEnable  (ZKNEEnable),
        .AEnable     (AEnable),
        .VEnable     (VEnable),
        .VLEN        (VLEN)
    ) execute1 (
        .clk                     (clk),
        .reset_n                 (reset_n),
        .sys_reset               (sys_reset_i),
        .stall                   (stall),
        .instruction_i           (instruction_execute),
        .pc_i                    (pc_execute),
        .first_operand_i         (first_operand_execute),
        .second_operand_i        (second_operand_execute),
        .third_operand_i         (third_operand_execute),
        .instruction_operation_i (instruction_operation_execute),
        .instruction_compressed_i(instruction_compressed_execute),
        .vector_operation_i      (vector_operation_execute),
        .atomic_operation_i      (atomic_operation_execute),
        .atomic_read_value_i     (regbank_data_writeback),
        .tag_i                   (tag_execute),
        .privilege_i             (privilege),
        .exc_ilegal_inst_i       (exc_ilegal_inst_execute),
        .exc_misaligned_fetch_i  (exc_misaligned_fetch_execute),
        .exc_inst_access_fault_i (exc_inst_access_fault_execute),
        .exc_load_access_fault_i (mmu_data_fault),
        .hold_o                  (hold),
        .killed_o                (killed),
        .write_enable_o          (regbank_write_enable_int),
        .instruction_operation_o (instruction_operation_retire),
        .result_o                (result_retire),
        .mem_address_o           (mem_address),
        .mem_read_enable_o       (mem_read_enable),
        .mem_write_enable_o      (mem_write_enable),
        .mem_write_data_o        (mem_data_o),
        .mem_read_data_i         (mem_data_i),
        .csr_address_o           (csr_addr),
        .csr_read_enable_o       (csr_read_enable),
        .csr_data_read_i         (csr_data_read),
        .csr_write_enable_o      (csr_write_enable),
        .csr_operation_o         (csr_operation),
        .csr_data_o              (csr_data_to_write),
        .vtype_o                 (vtype),
        .vlen_o                  (vlen),
        .jump_o                  (jump),
        .jump_target_o           (jump_target),
        .atomic_write_reg_o      (retire_atomic),
        .rd_atomic_o             (rd_atomic),

        .interrupt_pending_i     (interrupt_pending),
        .interrupt_ack_o         (interrupt_ack_o),
        .machine_return_o        (MACHINE_RETURN),
        .raise_exception_o       (RAISE_EXCEPTION),
        .exception_code_o        (Exception_Code)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    retire retire1 (
        .instruction_operation_i(instruction_operation_retire),
        .result_i               (result_retire),
        .mem_data_i             (mem_data_i),
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
        .RV32          (RV32          ),
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
        if ((killed == 1'b0 && (mem_write_enable != '0 || mem_read_enable == 1'b1)) && mmu_data_fault == 1'b0) begin
            mem_operation_enable_o = 1'b1;
        end
        else begin
            mem_operation_enable_o = 1'b0;
        end
    end

    assign mem_write_enable_o = mem_write_enable;

endmodule
