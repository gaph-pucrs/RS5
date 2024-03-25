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

module RS5
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
    parameter rv32_e        RV32        = RV32I,
    parameter bit           XOSVMEnable = 1'b0,
    parameter bit           ZIHPMEnable = 1'b0
)
(
    input  logic                    clk,
    input  logic                    reset,
    input  logic                    stall,

    input  logic [31:0]             instruction_i,
    input  logic [31:0]             mem_data_i,
    input  logic [63:0]             mtime_i,
    input  logic [31:0]             irq_i,

    output logic [31:0]             instruction_address_o,
    //output logic                    mem_operation_enable_o,
    //output logic  [3:0]             mem_write_enable_o,
    //output logic [31:0]             mem_address_o,
    //output logic [31:0]             mem_data_o,

    //////////////////////////////////////////////////////////////////////////////
    // AXI signals
    //////////////////////////////////////////////////////////////////////////////
    output logic        mem_awvalid_o,
    output logic        mem_arvalid_o,
    output logic        mem_rready_o,
    input  logic        mem_arready_i,
    output logic        mem_wvalid_o,
    output logic [ 3:0] mem_wstrb_o,
    output logic [31:0] mem_araddr_o,
    output logic [31:0] mem_awaddr_o,
    output logic [31:0] mem_wdata_o,
    input  logic [31:0] mem_rdata_i,
    input  logic        mem_rvalid_i,
    input  logic        mem_wready_i,
    input  logic        mem_awready_i,
    input  logic        mem_bvalid_i,
    output logic        mem_bready_o,
    input  logic [1:0]  mem_bresp_i,
    input  logic [1:0]  mem_rresp_i,
    output logic [2:0]  mem_awprot_o,
    output logic [2:0]  mem_arprot_o,

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
    /* verilator lint_off UNUSEDSIGNAL */
    logic   [31:0]   mem_address;
    /* verilator lint_on UNUSEDSIGNAL */
    logic   [31:0]   instruction_address;

//////////////////////////////////////////////////////////////////////////////
// Fetch signals
//////////////////////////////////////////////////////////////////////////////

    logic           enable_fetch;

//////////////////////////////////////////////////////////////////////////////
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_decode;
    logic    [2:0]  tag_decode;
    logic           enable_decode;

//////////////////////////////////////////////////////////////////////////////
// RegBank signals
//////////////////////////////////////////////////////////////////////////////

    logic    [4:0]  rs1, rs2;
    logic   [31:0]  regbank_data1, regbank_data2;
    logic   [31:0]  rs1_data_read, rs2_data_read;
    logic    [4:0]  rd;
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
    logic           exc_inst_access_fault_execute;

    logic        mem_awvalid;
    logic        mem_arvalid;
    logic        mem_wvalid;

//////////////////////////////////////////////////////////////////////////////
// Retire signals
//////////////////////////////////////////////////////////////////////////////

    iType_e         instruction_operation_retire;
    logic   [31:0]  result_retire;
    logic           killed;

    logic   [63:0]  mul_result;
    logic   [63:0]  mulh_result;
    logic   [63:0]  mulhsu_result;

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

    /* verilator lint_off UNUSEDSIGNAL */
    logic   [31:0]  mvmdo, mvmio, mvmds, mvmis, mvmdm, mvmim;
    logic           mvmctl;
    logic           mmu_en;
    /* verilator lint_on UNUSEDSIGNAL */

//////////////////////////////////////////////////////////////////////////////
// Assigns
//////////////////////////////////////////////////////////////////////////////
    
    if (XOSVMEnable == 1'b1) begin
        assign mmu_en = privilege != privilegeLevel_e'(2'b11) && mvmctl == 1'b1;
    end
    else begin
        assign mmu_en = 1'b0;     
    end

    assign regbank_write_enable =   (rd == '0) 
                                    ? 1'b0 
                                    : regbank_write_enable_int;

    assign rs1_data_read =  (rs1 == rd && regbank_write_enable) 
                            ? regbank_data_writeback 
                            : regbank_data1;

    assign rs2_data_read =  (rs2 == rd && regbank_write_enable) 
                            ? regbank_data_writeback 
                            : regbank_data2;

    assign enable_fetch = ~(stall | hazard | hold);

    assign enable_decode = ~(stall | hold);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    fetch fetch1 (
        .clk                    (clk), 
        .reset                  (reset), 
        .enable                 (enable_fetch),
        .jump_i                 (jump), 
        .jump_target_i          (jump_target),
        .mtvec_i                (mtvec),
        .mepc_i                 (mepc), 
        .exception_raised_i     (RAISE_EXCEPTION), 
        .machine_return_i       (MACHINE_RETURN), 
        .interrupt_ack_i        (interrupt_ack_o),
        .instruction_address_o  (instruction_address), 
        .pc_o                   (pc_decode), 
        .tag_o                  (tag_decode)
    );

    if (XOSVMEnable == 1'b1) begin :i_mmu_blk
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
    else begin
        assign mmu_inst_fault        = 1'b0;
        assign instruction_address_o = instruction_address;
    end


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    decode decoder1 (
        .clk                        (clk), 
        .reset                      (reset),
        .enable                     (enable_decode),
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
        regbank regbankff (
            .clk        (clk),
            .reset      (reset),
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
        .RV32        (RV32)
    ) execute1 (
        .clk                    (clk), 
        .reset                  (reset), 
        .stall                  (stall),
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
        .exc_inst_access_fault_i(exc_inst_access_fault_execute),
        .exc_load_access_fault_i(mmu_data_fault),
        .hold_o                 (hold),
        .killed_o               (killed),
        .write_enable_o         (regbank_write_enable_int),
        .instruction_operation_o(instruction_operation_retire), 
        .result_o               (result_retire),
        .mul_result_o           (mul_result),
        .mulh_result_o          (mulh_result),
        .mulhsu_result_o        (mulhsu_result),
        //.mem_address_o          (mem_address), 
        //.mem_read_enable_o      (mem_read_enable), 
        //.mem_write_enable_o     (mem_write_enable),
        //.mem_write_data_o       (mem_data_o),

        // AXI
        .mem_awvalid_o(mem_awvalid),
        .mem_arvalid_o(mem_arvalid),
        .mem_rready_o,
        .mem_arready_i,
        .mem_wvalid_o(mem_wvalid),
        .mem_wstrb_o,
        .mem_araddr_o,
        .mem_awaddr_o,
        .mem_rvalid_i,
        .mem_wready_i,
        .mem_awready_i,
        .mem_bvalid_i,
        .mem_bready_o,
        .mem_bresp_i,
        .mem_rresp_i,
        .mem_awprot_o,
        .mem_arprot_o,
        .mem_wdata_o,
        .mem_rdata_i,

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

    assign mem_awvalid_o = killed ? '0 : mem_awvalid;
    assign mem_arvalid_o = killed ? '0 : mem_arvalid;
    assign mem_wvalid_o = killed ? '0 : mem_wvalid;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    retire #(
        .RV32   (RV32)
    ) retire1 (
        .instruction_operation_i(instruction_operation_retire),
        .result_i               (result_retire),
        .mul_result_i           (mul_result),
        .mulh_result_i          (mulh_result),
        .mulhsu_result_i        (mulhsu_result),
        .mem_data_i             (mem_data_i), 
        .regbank_data_o         (regbank_data_writeback)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSRBank #(
      .XOSVMEnable  (XOSVMEnable),
      .ZIHPMEnable  (ZIHPMEnable),
      .RV32         (RV32       )
    ) CSRBank1 (
        .clk                        (clk), 
        .reset                      (reset), 
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

    //if (XOSVMEnable == 1'b1) begin : d_mmu_blk
    //    mmu d_mmu (
    //        .en_i           (mmu_en        ),
    //        .mask_i         (mvmdm         ),
    //        .offset_i       (mvmdo         ),
    //        .size_i         (mvmds         ),
    //        .address_i      (mem_address   ),
    //        .exception_o    (mmu_data_fault),
    //        .address_o      (mem_address_o )
    //    );
    //end
    //else begin
    //    assign mmu_data_fault = 1'b0;
    //    assign mem_address_o  = mem_address;
    //end

    //always_comb begin
    //    if ((killed == 1'b0 && (mem_write_enable != '0 || mem_read_enable == 1'b1)) && mmu_data_fault == 1'b0) begin
    //        mem_operation_enable_o = 1'b1;
    //    end
    //    else begin
    //        mem_operation_enable_o = 1'b0;
    //    end
    //end

    //assign mem_write_enable_o = mem_write_enable;

endmodule
