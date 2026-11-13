/*!\file RS5.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
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
    parameter environment_e Environment      = ASIC,
    parameter mul_e         MULEXT           = MUL_M,
    parameter atomic_e      AMOEXT           = AMO_A,
    parameter logic [31:0]  START_ADDR       = '0,
    parameter bit           COMPRESSED       = 1'b0,
    parameter bit           VEnable          = 1'b0,
    parameter int           VLEN             = 256,
    parameter int           LLEN             = 32,
    parameter int           BUS_WIDTH        = 32,
    parameter bit           XOSVMEnable      = 1'b0,
    parameter bit           ZKNEEnable       = 1'b0,
    parameter bit           ZBKBEnable       = 1'b0,
    parameter bit           ZKNHEnable       = 1'b0,
    parameter bit           XKYBEREnable     = 1'b0,
    parameter bit           ZICONDEnable     = 1'b0,
    parameter bit           ZCBEnable        = 1'b0,
    parameter bit           HPMCOUNTEREnable = 1'b0,
    parameter int           IMEM_LATENCY     = 1,
    parameter bit           BRANCHPRED       = 1'b1,
    parameter bit           FORWARDING       = 1'b1
)
(
    input  logic                    clk,
    input  logic                    reset_n,
    input  logic                    sys_reset_i,

    input  logic                    tip_i,
    input  logic                    eip_i,
    output logic                    interrupt_ack_o,

    input  logic [63:0]             mtime_i,

    /* OBI instruction interface */
    output logic                    instr_req_o,
    input  logic                    instr_gnt_i,
    output logic [31:0]             instr_addr_o,
    input  logic                    instr_rvalid_i,
    input  logic [31:0]             instr_rdata_i,

    /* OBI data interface */
    output logic                    data_req_o,
    input  logic                    data_gnt_i,
    output logic [31:0]             data_addr_o,
    output logic                    data_we_o,
    output logic [BUS_WIDTH/8-1:0]  data_be_o,
    output logic [BUS_WIDTH-1:0]    data_wdata_o,
    input  logic                    data_rvalid_i,
    input  logic [BUS_WIDTH-1:0]    data_rdata_i
);

    /* Cycles from instr_gnt_i to instr_rvalid_i of a typical fetch. The fetch */
    /* queue, and the requests kept in flight, cover that round trip plus the  */
    /* cycle a word takes to free its room (instr_req_o is registered-only).   */
    localparam int IQUEUE_SIZE = 2 ** $clog2(IMEM_LATENCY + 2);

    /* The pipeline stalls while the data interface is busy */
    logic                stall;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic                hold;
    logic                fetch_hazard;

    logic                enable_fetch;

    logic                jump, ctx_switch, should_jump;
    logic         [31:0] jump_target, ctx_switch_target;

    logic                bp_take_fetch, jump_rollback, bp_ack;
    logic         [31:0] bp_target;

    logic         [31:0] instruction_address;
    logic         [31:0] instruction_paddr;
    logic                mmu_inst_fault;

    decode_ctrl_t        decode_ctrl;
    logic         [31:0] instruction_decode, pc_decode;

    assign enable_fetch  = !(stall || hold || fetch_hazard);

    fetch #(
        .start_address(START_ADDR ),
        .IQUEUE_SIZE  (IQUEUE_SIZE),
        .MULEXT       (MULEXT     ),
        .ZCBEnable    (ZCBEnable  ),
        .COMPRESSED   (COMPRESSED ),
        .BRANCHPRED   (BRANCHPRED ),
        .XOSVMEnable  (XOSVMEnable)
    ) fetch1 (
        .clk                  (clk                    ),
        .reset_n              (reset_n                ),
        .sys_reset            (sys_reset_i            ),
        .enable_i             (enable_fetch           ),

        .jump_i               (jump                   ),
        .ctx_switch_i         (ctx_switch             ),
        .should_jump_i        (should_jump            ),
        .jump_target_i        (jump_target            ),
        .ctx_switch_target_i  (ctx_switch_target      ),

        .bp_take_i            (bp_take_fetch          ),
        .bp_target_i          (bp_target              ),
        .jump_rollback_i      (jump_rollback          ),
        .bp_ack_o             (bp_ack                 ),

        .instruction_address_o(instruction_address    ),
        .instruction_paddr_i  (instruction_paddr      ),
        .inst_fault_i         (mmu_inst_fault         ),

        .mem_req_o            (instr_req_o            ),
        .mem_gnt_i            (instr_gnt_i            ),
        .mem_addr_o           (instr_addr_o           ),
        .mem_rvalid_i         (instr_rvalid_i         ),
        .instruction_data_i   (instr_rdata_i          ),

        .ctrl_o               (decode_ctrl            ),
        .instruction_o        (instruction_decode     ),
        .pc_o                 (pc_decode              )
    );

    privilegeLevel_e privilege;

    /* Signals enabled with XOSVM */
    /* verilator lint_off UNUSEDSIGNAL */
    logic            mmu_en;
    logic            mvmctl;
    logic     [31:0] mvmio, mvmis, mvmim;
    /* verilator lint_on UNUSEDSIGNAL */


    if (XOSVMEnable == 1'b1) begin : gen_xosvm_mmu_on
        assign mmu_en = privilege != privilegeLevel_e'(2'b11) && mvmctl == 1'b1;
    end
    else begin : gen_xosvm_mmu_off
        assign mmu_en = 1'b0;
    end

    if (XOSVMEnable == 1'b1) begin : gen_xosvm_i_mmu_on
        mmu i_mmu (
            .en_i           (mmu_en               ),
            .mask_i         (mvmim                ),
            .offset_i       (mvmio                ),
            .size_i         (mvmis                ),
            .address_i      (instruction_address  ),
            .exception_o    (mmu_inst_fault       ),
            .address_o      (instruction_paddr    )
        );
    end
    else begin : gen_xosvm_i_mmu_off
        assign mmu_inst_fault    = 1'b0;
        assign instruction_paddr = instruction_address;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DECODER /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic               enable_decode;

    logic         [4:0] rs1, rs2;
    logic        [31:0] regbank_data1, regbank_data2;

    wb_ctrl_t           ctrl_mem_access, ctrl_retire, ctrl_writeback;
    logic               write_enable_exec;
    logic         [4:0] rd_mem_access, rd_retire;
    logic        [31:0] result_exec, result_mem_access, regbank_data_writeback;

    exec_ctrl_t          ctrl_execute;
    logic          [4:0] rd_execute, rs1_execute;
    logic         [11:0] csr_addr;
    logic         [31:0] pc_execute, rs1_data_execute, rs2_data_execute;
    logic         [31:0] second_operand_execute, instruction_execute, jump_imm_target_exec;


    assign enable_decode = !(stall || hold);

    decode # (
        .MULEXT       (MULEXT      ),
        .AMOEXT       (AMOEXT      ),
        .COMPRESSED   (COMPRESSED  ),
        .ZKNEEnable   (ZKNEEnable  ),
        .ZBKBEnable   (ZBKBEnable  ),
        .ZKNHEnable   (ZKNHEnable  ),
        .XKYBEREnable (XKYBEREnable),
        .ZICONDEnable (ZICONDEnable),
        .VEnable      (VEnable     ),
        .BRANCHPRED   (BRANCHPRED  ),
        .FORWARDING   (FORWARDING  )
    ) decoder1 (
        .clk                        (clk                          ),
        .reset_n                    (reset_n                      ),
        .enable                     (enable_decode                ),
        .sys_reset                  (sys_reset_i                  ),

        .ctrl_i                     (decode_ctrl                  ),
        .pc_i                       (pc_decode                    ),
        .instruction_i              (instruction_decode           ),

        .should_jump_i              (should_jump                  ),
        .jump_rollback_i            (jump_rollback                ),
        

        .rs1_o                      (rs1                          ),
        .rs2_o                      (rs2                          ),
        .rs1_data_read_i            (regbank_data1                ),
        .rs2_data_read_i            (regbank_data2                ),

        .execute_we_i               (write_enable_exec            ),
        .mem_access_we_i            (ctrl_mem_access.rd_we        ),
        .regbank_we_i               (ctrl_writeback.rd_we         ),
        .rd_mem_access_i            (rd_mem_access                ),
        .rd_retire_i                (rd_retire                    ),
        .result_i                   (result_exec                  ),
        .mem_access_result_i        (result_mem_access            ),
        .writeback_i                (regbank_data_writeback       ),

        .dec_hazard_o               (fetch_hazard                 ),
        .bp_take_o                  (bp_take_fetch                ),
        .bp_target_o                (bp_target                    ),

        .ctrl_o                     (ctrl_execute                 ),
        .rd_o                       (rd_execute                   ),
        .instr_rs1_o                (rs1_execute                  ),
        .csr_address_o              (csr_addr                     ),
        .pc_o                       (pc_execute                   ),
        .rs1_data_o                 (rs1_data_execute             ),
        .rs2_data_o                 (rs2_data_execute             ),
        .second_operand_o           (second_operand_execute       ),
        .instruction_o              (instruction_execute          ),
        .jump_imm_target_o          (jump_imm_target_exec         )
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (Environment == FPGA) begin :RegFileFPGA_blk
        DRAM_RegBank RegBankA (
            .clk        (clk                   ),
            .we         (ctrl_writeback.rd_we  ),
            .a          (rd_retire             ),
            .d          (regbank_data_writeback),
            .dpra       (rs1                   ),
            .dpo        (regbank_data1         )
        );

        DRAM_RegBank RegBankB (
            .clk        (clk                   ),
            .we         (ctrl_writeback.rd_we  ),
            .a          (rd_retire             ),
            .d          (regbank_data_writeback),
            .dpra       (rs2                   ),
            .dpo        (regbank_data2         )
        );
    end
    else begin : RegFileFF_blk
        regbank regbankff (
            .clk        (clk                   ),
            .reset_n    (reset_n               ),
            .rs1        (rs1                   ),
            .rs2        (rs2                   ),
            .rd         (rd_retire             ),
            .enable     (ctrl_writeback.rd_we  ),
            .data_i     (regbank_data_writeback),
            .data1_o    (regbank_data1         ),
            .data2_o    (regbank_data2         )
        );
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    logic                  exec_valid;

    logic                  load_access_fault;
    logic           [31:0] reservation_data;

    csrOperation_e         csr_operation;
    exceptionCode_e        Exception_Code;
    logic                  interrupt_pending, csr_read_enable, csr_write_enable;
    logic                  RAISE_EXCEPTION, MACHINE_RETURN;
    logic           [31:0] csr_data_to_write, csr_data_read;
    logic           [31:0] mepc, mtvec, vtype, vlen, pc_irq, pc_exc;

    logic                   mem_enable;
    logic                   dmem_req;
    logic                   rsp_ok;
    logic            [31:0] mem_address_exec;
    /* We always mask the two lsbs */
    /* verilator lint_off UNUSEDSIGNAL */
    logic            [31:0] mem_address;
    /* verilator lint_on UNUSEDSIGNAL */

    assign exec_valid = !(ctrl_execute.killed || ctrl_execute.hazard);

    execute #(
        .Environment  (Environment ),
        .MULEXT       (MULEXT      ),
        .AMOEXT       (AMOEXT      ),
        .COMPRESSED   (COMPRESSED  ),
        .ZKNEEnable   (ZKNEEnable  ),
        .ZBKBEnable   (ZBKBEnable  ),
        .ZKNHEnable   (ZKNHEnable  ),
        .XKYBEREnable (XKYBEREnable),
        .ZICONDEnable (ZICONDEnable),
        .VEnable      (VEnable     ),
        .XOSVMEnable  (XOSVMEnable ),
        .VLEN         (VLEN        ),
        .LLEN         (LLEN        ),
        .BUS_WIDTH    (BUS_WIDTH   ),
        .BRANCHPRED   (BRANCHPRED  )
    ) execute1 (
        .clk                     (clk                          ),
        .reset_n                 (reset_n                      ),
        .stall                   (stall                        ),

        .ctrl_i                  (ctrl_execute                 ),
        .valid_i                 (exec_valid                   ),
        .bp_ack_i                (bp_ack                       ),
        .rd_i                    (rd_execute                   ),
        .rs1_i                   (rs1_execute                  ),
        .csr_address_i           (csr_addr                     ),
        .pc_i                    (pc_execute                   ),
        .rs1_data_i              (rs1_data_execute             ),
        .rs2_data_i              (rs2_data_execute             ),
        .second_operand_i        (second_operand_execute       ),
        .jump_imm_target_i       (jump_imm_target_exec         ),
        .instruction_i           (instruction_execute          ),

        .exc_load_access_fault_i (load_access_fault            ),
        .reservation_data_i      (reservation_data             ),

        .privilege_i             (privilege                    ),
        .interrupt_pending_i     (interrupt_pending            ),
        .interrupt_ack_o         (interrupt_ack_o              ),
        .machine_return_o        (MACHINE_RETURN               ),
        .raise_exception_o       (RAISE_EXCEPTION              ),
        .csr_read_enable_o       (csr_read_enable              ),
        .csr_write_enable_o      (csr_write_enable             ),
        .csr_operation_o         (csr_operation                ),
        .exception_code_o        (Exception_Code               ),
        .csr_data_read_i         (csr_data_read                ),
        .csr_data_o              (csr_data_to_write            ),
        .mtvec_i                 (mtvec                        ),
        .mepc_i                  (mepc                         ),
        .vtype_o                 (vtype                        ),
        .vlen_o                  (vlen                         ),
        .pc_irq_o                (pc_irq                       ),
        .pc_exc_o                (pc_exc                       ),
        
        .mem_address_exec_o      (mem_address_exec             ),
        .mem_address_o           (mem_address                  ),
        .mem_enable_o            (mem_enable                   ),
        .mem_we_o                (data_we_o                    ),
        .mem_be_o                (data_be_o                    ),
        .mem_write_data_o        (data_wdata_o                 ),
        .mem_read_data_i         (data_rdata_i                 ),
        .mem_rsp_ok_i            (rsp_ok                       ),
        
        .hold_o                  (hold                         ),
        .write_enable_fwd_o      (write_enable_exec            ),
        .jump_rollback_o         (jump_rollback                ),
        .ctx_switch_o            (ctx_switch                   ),
        .jump_o                  (jump                         ),
        .should_jump_o           (should_jump                  ),
        .ctx_switch_target_o     (ctx_switch_target            ),
        .jump_target_o           (jump_target                  ),
        .result_fwd_o            (result_exec                  ),

        .ctrl_o                  (ctrl_mem_access              ),
        .rd_o                    (rd_mem_access                ),
        .result_o                (result_mem_access            ) 
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// MEMORY ACCESS ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    logic [31:0] result_retire;

    mem_access mem_access1 (
        .clk                    (clk              ),
        .reset_n                (reset_n          ),
        .stall                  (stall            ),

        .ctrl_i                 (ctrl_mem_access  ),
        .rd_i                   (rd_mem_access    ),
        .result_i               (result_mem_access),

        .load_access_fault_i    (load_access_fault),
        .rsp_ok_i               (rsp_ok           ),
        
        .ctrl_o                 (ctrl_retire      ),
        .result_o               (result_retire    ),
        .rd_o                   (rd_retire        )
    );

    /* Unused without MMU */
    /* verilator lint_off UNUSEDSIGNAL */
    logic     [31:0] mvmdo, mvmds, mvmdm;
    /* verilator lint_on UNUSEDSIGNAL */

    if (XOSVMEnable) begin : gen_d_mmu_on
        logic mmu_en_r;
        logic mmu_data_fault;

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                mmu_en_r <= 1'b0;
            else if (!stall)
                mmu_en_r <= mmu_en;
        end

        mmu d_mmu (
            .en_i       (mmu_en_r                       ),
            .mask_i     (mvmdm                          ),
            .offset_i   (mvmdo                          ),
            .size_i     (mvmds                          ),
            .address_i  ({mem_address[31:2], 2'b00}     ),
            .exception_o(mmu_data_fault                 ),
            .address_o  (data_addr_o                    )
        );

        assign load_access_fault    = mem_enable && mmu_data_fault;
        assign dmem_req             = mem_enable && !mmu_data_fault;
    end
    else begin : gen_d_mmu_off
        assign load_access_fault       = 1'b0;
        assign data_addr_o             = {mem_address[31:2], 2'b00};
        assign dmem_req                = mem_enable;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// OBI DATA INTERFACE //////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /* The request leaves execute registered and waits in mem_access for gnt.  */
    /* Its response is awaited when the instruction reaches retire. When the   */
    /* pipeline is stalled waiting for that response, the next request may     */
    /* already be granted: it is not issued again.                             */
    logic data_granted;
    logic rsp_pending;

    assign data_req_o = dmem_req && !data_granted;
    assign stall      = (data_req_o && !data_gnt_i) || (rsp_pending && !data_rvalid_i);
    assign rsp_ok     = !rsp_pending || data_rvalid_i;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            data_granted <= 1'b0;
        else if (!stall)
            data_granted <= 1'b0;
        else if (data_req_o && data_gnt_i)
            data_granted <= 1'b1;
    end

    /* Without a stall, a request in mem_access was granted and moves to retire */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rsp_pending <= 1'b0;
        else if (!stall)
            rsp_pending <= dmem_req;
        else if (data_rvalid_i)
            rsp_pending <= 1'b0;
    end

    /* The register bank is written once the read data is present */
    always_comb begin
        ctrl_writeback       = ctrl_retire;
        ctrl_writeback.rd_we = ctrl_retire.rd_we && rsp_ok;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// RETIRE //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    retire #(
        .AMOEXT      (AMOEXT)
    ) retire1 (
        .clk               (clk                   ),
        .reset_n           (reset_n               ),

        .ctrl_i            (ctrl_writeback        ),
        .result_i          (result_retire         ),

        .mem_data_i        (data_rdata_i[31:0]    ),

        .regbank_data_o    (regbank_data_writeback),

        .reservation_data_o(reservation_data      )
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CSRBank #(
        .HPMCOUNTEREnable(HPMCOUNTEREnable),
        .XOSVMEnable     (XOSVMEnable     ),
        .XKYBEREnable    (XKYBEREnable    ),
        .COMPRESSED      (COMPRESSED      ),
        .ZKNEEnable      (ZKNEEnable      ),
        .ZKNHEnable      (ZKNHEnable      ),
        .MULEXT          (MULEXT          ),
        .AMOEXT          (AMOEXT          ),
        .VEnable         (VEnable         ),
        .VLEN            (VLEN            )
    ) CSRBank1 (
        .clk                        (clk),
        .reset_n                    (reset_n),
        .sys_reset                  (sys_reset_i),
        .read_enable_i              (csr_read_enable),
        .write_enable_i             (csr_write_enable),
        .operation_i                (csr_operation),
        .address_i                  (CSRs'(csr_addr)),
        .data_i                     (csr_data_to_write),
        .data_o                     (csr_data_read),
        .ctrl_i                     (ctrl_execute),
        .stall                      (stall),
        .hold                       (hold),
        .vtype_i                    (vtype),
        .vlen_i                     (vlen),
        .raise_exception_i          (RAISE_EXCEPTION),
        .machine_return_i           (MACHINE_RETURN),
        .exception_code_i           (Exception_Code),
        .pc_i                       (pc_execute),
        .mem_address_exec_i         (mem_address_exec),
        .mem_address_i              (mem_address),
        .pc_irq_i                   (pc_irq),
        .pc_exc_i                   (pc_exc),
        .instruction_i              (instruction_execute),
        .jump_misaligned_i          (decode_ctrl.jump_misaligned),
        .jump_target_i              (jump_target),
        .mtime_i                    (mtime_i),
        .tip_i                      (tip_i),
        .eip_i                      (eip_i),
        .interrupt_ack_i            (interrupt_ack_o),
        .interrupt_pending_o        (interrupt_pending),
        .privilege_o                (privilege),
        .mepc_o                     (mepc),
        .mtvec_o                    (mtvec),
    // XOSVM Signals
        .mvmctl_o                   (mvmctl),
        .mvmdo_o                    (mvmdo),
        .mvmds_o                    (mvmds),
        .mvmdm_o                    (mvmdm),
        .mvmio_o                    (mvmio),
        .mvmis_o                    (mvmis),
        .mvmim_o                    (mvmim)
    );

endmodule
