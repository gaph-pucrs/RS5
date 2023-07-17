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
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/mmu.sv"
`include "../rtl/CSRBank.sv"
*/

module RS5
    import RS5_pkg::*;
(
    input  logic        clk,
    input  logic        reset,
    input  logic        stall,

    input  logic [31:0] instruction_i,
    input  logic [31:0] mem_data_i,
    input  logic [31:0] IRQ_i,
    input  logic [63:0] mtime_i,

    output logic [31:0] instruction_address_o,
    output logic        mem_operation_enable_o,
    output logic  [3:0] mem_write_enable_o,
    output logic [31:0] mem_address_o,
    output logic [31:0] mem_data_o,
    output logic        interrupt_ack_o
);

//////////////////////////////////////////////////////////////////////////////
// Global signals
//////////////////////////////////////////////////////////////////////////////
    logic            jump;
    logic            hazard;

`ifdef M_EXT
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
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_decode;
    logic   [2:0]   tag_decode;

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

//////////////////////////////////////////////////////////////////////////////
// CSR Bank signals
//////////////////////////////////////////////////////////////////////////////

    logic           csr_read_enable, csr_write_enable;
    csrOperation_e  csr_operation;
    logic   [11:0]  csr_addr;
    logic   [31:0]  csr_data_to_write, csr_data_read;
    logic   [31:0]  mepc, mtvec;
    logic           RAISE_EXCEPTION, MACHINE_RETURN;
    exceptionCode_e Exception_Code;
    logic           Interrupt_pending;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// FETCH //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    fetch fetch1 (
        .clk                    (clk), 
        .reset                  (reset), 
        .stall                  (stall | hold),
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
        .stall                      (stall | hold),
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
`endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// EXECUTE /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    execute execute1 (
        .clk                    (clk), 
        .reset                  (reset), 
        .stall                  (stall),
        .hold_o                 (hold),
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
        .interrupt_pending_i    (Interrupt_pending),
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
        .mem_data_i             (mem_data_i), 
        .regbank_data_o         (regbank_data_writeback)
    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// CSRs BANK ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CSRBank CSRBank1 (
        .clk                (clk), 
        .reset              (reset), 
        .read_enable_i      (csr_read_enable), 
        .write_enable_i     (csr_write_enable), 
        .operation_i        (csr_operation), 
        .address_i          (csr_addr), 
        .data_i             (csr_data_to_write), 
        .killed             (killed),
        .out                (csr_data_read),
        .raise_exception_i  (RAISE_EXCEPTION), 
        .machine_return_i   (MACHINE_RETURN),
        .exception_code_i   (Exception_Code), 
        .pc_i               (pc_execute), 
        .instruction_i      (instruction_execute),
        .jump_i             (jump),
        .jump_target_i      (jump_target),
        .mtime_i            (mtime_i),
        .IRQ_i              (IRQ_i), 
        .interrupt_ack_i    (interrupt_ack_o),
        .interrupt_pending_o(Interrupt_pending), 
        .privilege_o        (privilege), 
        .mepc               (mepc), 
    `ifdef XOSVM
        .mvmctl_o           (mvmctl),
        .mvmdo_o            (mvmdo),
        .mvmds_o            (mvmds),
        .mvmio_o            (mvmio),
        .mvmis_o            (mvmis),
    `endif
        .mtvec              (mtvec)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DEBUG ///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

`ifdef DEBUG
    int fd;
    int clock_counter, instuctions_retired_counter, instructions_killed_counter, jumps_counter;
    int interrupt_ack_counter, raise_exception_counter, context_switch_counter;
    int hazard_counter, stall_counter, hazard_stall_counter;
    int nop_counter, lui_counter, sret_counter, mret_counter, wfi_counter, ecall_counter, ebreak_counter, invalid_counter;
    int add_counter, sub_counter, sltu_counter, slt_counter;
    int xor_counter, or_counter, and_counter;
    int sll_counter, srl_counter, sra_counter;
    int beq_counter, bne_counter, blt_counter, bltu_counter, bge_counter, bgeu_counter, jal_counter, jalr_counter;
    int lb_counter, lbu_counter, lh_counter, lhu_counter, lw_counter, sb_counter, sh_counter, sw_counter;
    int csrrw_counter, csrrs_counter, csrrc_counter, csrrwi_counter, csrrsi_counter, csrrci_counter;

    always_ff @(posedge clk) begin
        if (reset) begin
            clock_counter               <= 0;
            instuctions_retired_counter <= 0;
            instructions_killed_counter <= 0;
            jumps_counter               <= 0;
            nop_counter                 <= 0;

            hazard_counter              <= 0;
            stall_counter               <= 0;
            hazard_stall_counter        <= 0;

            interrupt_ack_counter       <= 0;
            raise_exception_counter     <= 0;
            context_switch_counter      <= 0;

            lui_counter                 <= 0;
            sret_counter                <= 0;
            mret_counter                <= 0;
            wfi_counter                 <= 0;
            ecall_counter               <= 0;
            ebreak_counter              <= 0;
            invalid_counter             <= 0;
            add_counter                 <= 0;
            sub_counter                 <= 0;
            sltu_counter                <= 0;
            slt_counter                 <= 0;
            xor_counter                 <= 0;
            or_counter                  <= 0;
            and_counter                 <= 0;
            sll_counter                 <= 0;
            srl_counter                 <= 0;
            sra_counter                 <= 0;
            beq_counter                 <= 0;
            bne_counter                 <= 0;
            blt_counter                 <= 0;
            bltu_counter                <= 0;
            bge_counter                 <= 0;
            bgeu_counter                <= 0;
            jal_counter                 <= 0;
            jalr_counter                <= 0;
            lb_counter                  <= 0;
            lbu_counter                 <= 0;
            lh_counter                  <= 0;
            lhu_counter                 <= 0;
            lw_counter                  <= 0;
            sb_counter                  <= 0;
            sh_counter                  <= 0;
            sw_counter                  <= 0;
            csrrw_counter               <= 0;
            csrrs_counter               <= 0;
            csrrc_counter               <= 0;
            csrrwi_counter              <= 0;
            csrrsi_counter              <= 0;
            csrrci_counter              <= 0;
        end
        else begin
            clock_counter  <= clock_counter + 1;

            instuctions_retired_counter <= (!killed) ? instuctions_retired_counter  + 1 : instuctions_retired_counter;
            instructions_killed_counter <= (killed) ? instructions_killed_counter  + 1 : instructions_killed_counter;
            jumps_counter               <= (jump)   ? jumps_counter                + 1 : jumps_counter;

            hazard_counter              <= (hazard) ? hazard_counter               + 1 : hazard_counter;
            stall_counter               <= (stall)  ? stall_counter                + 1 : stall_counter;
            hazard_stall_counter        <= (hazard && stall) ? hazard_stall_counter + 1 : hazard_stall_counter;

            interrupt_ack_counter   <= (interrupt_ack_o) ? interrupt_ack_counter   + 1 : interrupt_ack_counter;
            raise_exception_counter <= (RAISE_EXCEPTION) ? raise_exception_counter + 1 : raise_exception_counter;
            context_switch_counter  <= (jump || RAISE_EXCEPTION || MACHINE_RETURN || interrupt_ack_o) ? context_switch_counter + 1 : context_switch_counter;
            nop_counter             <= (instruction_operation_retire == NOP) ? nop_counter + 1 : nop_counter;

            if (!killed) begin
                lui_counter     <= (instruction_operation_retire == LUI)     ? lui_counter       + 1 : lui_counter;
                sret_counter    <= (instruction_operation_retire == SRET)    ? sret_counter      + 1 : sret_counter;
                mret_counter    <= (instruction_operation_retire == MRET)    ? mret_counter      + 1 : mret_counter;
                wfi_counter     <= (instruction_operation_retire == WFI)     ? wfi_counter       + 1 : wfi_counter;
                ecall_counter   <= (instruction_operation_retire == ECALL)   ? ecall_counter     + 1 : ecall_counter;
                ebreak_counter  <= (instruction_operation_retire == EBREAK)  ? ebreak_counter    + 1 : ebreak_counter;
                invalid_counter <= (instruction_operation_retire == INVALID) ? invalid_counter   + 1 : invalid_counter;
                add_counter     <= (instruction_operation_retire == ADD)     ? add_counter       + 1 : add_counter;
                sub_counter     <= (instruction_operation_retire == SUB)     ? sub_counter       + 1 : sub_counter;
                sltu_counter    <= (instruction_operation_retire == SLTU)    ? sltu_counter      + 1 : sltu_counter;
                slt_counter     <= (instruction_operation_retire == SLT)     ? slt_counter       + 1 : slt_counter;
                xor_counter     <= (instruction_operation_retire == XOR)     ? xor_counter       + 1 : xor_counter;
                or_counter      <= (instruction_operation_retire == OR)      ? or_counter        + 1 : or_counter;
                and_counter     <= (instruction_operation_retire == AND)     ? and_counter       + 1 : and_counter;
                sll_counter     <= (instruction_operation_retire == SLL)     ? sll_counter       + 1 : sll_counter;
                srl_counter     <= (instruction_operation_retire == SRL)     ? srl_counter       + 1 : srl_counter;
                sra_counter     <= (instruction_operation_retire == SRA)     ? sra_counter       + 1 : sra_counter;
                beq_counter     <= (instruction_operation_retire == BEQ)     ? beq_counter       + 1 : beq_counter;
                bne_counter     <= (instruction_operation_retire == BNE)     ? bne_counter       + 1 : bne_counter;
                blt_counter     <= (instruction_operation_retire == BLT)     ? blt_counter       + 1 : blt_counter;
                bltu_counter    <= (instruction_operation_retire == BLTU)    ? bltu_counter      + 1 : bltu_counter;
                bge_counter     <= (instruction_operation_retire == BGE)     ? bge_counter       + 1 : bge_counter;
                bgeu_counter    <= (instruction_operation_retire == BGEU)    ? bgeu_counter      + 1 : bgeu_counter;
                jal_counter     <= (instruction_operation_retire == JAL)     ? jal_counter       + 1 : jal_counter;
                jalr_counter    <= (instruction_operation_retire == JALR)    ? jalr_counter      + 1 : jalr_counter;
                lb_counter      <= (instruction_operation_retire == LB)      ? lb_counter        + 1 : lb_counter;
                lbu_counter     <= (instruction_operation_retire == LBU)     ? lbu_counter       + 1 : lbu_counter;
                lh_counter      <= (instruction_operation_retire == LH)      ? lh_counter        + 1 : lh_counter;
                lhu_counter     <= (instruction_operation_retire == LHU)     ? lhu_counter       + 1 : lhu_counter;
                lw_counter      <= (instruction_operation_retire == LW)      ? lw_counter        + 1 : lw_counter;
                sb_counter      <= (instruction_operation_retire == SB)      ? sb_counter        + 1 : sb_counter;
                sh_counter      <= (instruction_operation_retire == SH)      ? sh_counter        + 1 : sh_counter;
                sw_counter      <= (instruction_operation_retire == SW)      ? sw_counter        + 1 : sw_counter;
                csrrw_counter   <= (instruction_operation_retire == CSRRW)   ? csrrw_counter     + 1 : csrrw_counter;
                csrrs_counter   <= (instruction_operation_retire == CSRRS)   ? csrrs_counter     + 1 : csrrs_counter;
                csrrc_counter   <= (instruction_operation_retire == CSRRC)   ? csrrc_counter     + 1 : csrrc_counter;
                csrrwi_counter  <= (instruction_operation_retire == CSRRWI)  ? csrrwi_counter    + 1 : csrrwi_counter;
                csrrsi_counter  <= (instruction_operation_retire == CSRRSI)  ? csrrsi_counter    + 1 : csrrsi_counter;
                csrrci_counter  <= (instruction_operation_retire == CSRRCI)  ? csrrci_counter    + 1 : csrrci_counter;
            end
        end
    end

    initial 
        fd = $fopen ("./debug/Report.txt", "w");

    always_comb begin
        if (mem_address == 32'h80000000 && mem_write_enable_o != '0) begin
            $fwrite(fd,"Clock Cycles:           %d\n", clock_counter);
            $fwrite(fd,"Instructions Retired:   %d\n", instuctions_retired_counter);
            $fwrite(fd,"Instructions Killed:    %d\n", instructions_killed_counter);
            $fwrite(fd,"Context Switches:       %d\n", context_switch_counter);
            $fwrite(fd,"Jumps:                  %d\n", jumps_counter);
            $fwrite(fd,"Exceptions Raised:      %d\n", raise_exception_counter);
            $fwrite(fd,"Interrupts Acked:       %d\n", interrupt_ack_counter);

            $fwrite(fd,"\nCYCLES WITH::\n");
            $fwrite(fd,"HAZARDS:                %d\n", hazard_counter);
            $fwrite(fd,"STALL:                  %d\n", stall_counter);
            $fwrite(fd,"HAZARDS AND STALL:      %d\n", hazard_stall_counter);

            $fwrite(fd,"\nINSTRUCTION COUNTERS:\n");
            $fwrite(fd,"NOP:                    %d\n", nop_counter);
            $fwrite(fd,"LUI:                    %d\n", lui_counter);
            $fwrite(fd,"SRET:                   %d\n", sret_counter);
            $fwrite(fd,"MRET:                   %d\n", mret_counter);
            $fwrite(fd,"WFI:                    %d\n", wfi_counter);
            $fwrite(fd,"ECALL:                  %d\n", ecall_counter);
            $fwrite(fd,"EBREAK:                 %d\n", ebreak_counter);
            $fwrite(fd,"INVALID:                %d\n", invalid_counter);
            $fwrite(fd,"ADD:                    %d\n", add_counter);
            $fwrite(fd,"SUB:                    %d\n", sub_counter);
            $fwrite(fd,"SLT:                    %d\n", slt_counter);
            $fwrite(fd,"SLTU:                   %d\n", sltu_counter);
            $fwrite(fd,"XOR:                    %d\n", xor_counter);
            $fwrite(fd,"OR:                     %d\n", or_counter);
            $fwrite(fd,"AND:                    %d\n", and_counter);
            $fwrite(fd,"SLL:                    %d\n", sll_counter);
            $fwrite(fd,"SRL:                    %d\n", srl_counter);
            $fwrite(fd,"SRA:                    %d\n", sra_counter);
            $fwrite(fd,"BEQ:                    %d\n", beq_counter);
            $fwrite(fd,"BNE:                    %d\n", bne_counter);
            $fwrite(fd,"BLT:                    %d\n", blt_counter);
            $fwrite(fd,"BLTU:                   %d\n", bltu_counter);
            $fwrite(fd,"BGE:                    %d\n", bge_counter);
            $fwrite(fd,"BGEU:                   %d\n", bgeu_counter);
            $fwrite(fd,"JAL:                    %d\n", jal_counter);
            $fwrite(fd,"JALR:                   %d\n", jalr_counter);
            $fwrite(fd,"LB:                     %d\n", lb_counter);
            $fwrite(fd,"LBU:                    %d\n", lbu_counter);
            $fwrite(fd,"LH:                     %d\n", lh_counter);
            $fwrite(fd,"LHU:                    %d\n", lhu_counter);
            $fwrite(fd,"LW:                     %d\n", lw_counter);
            $fwrite(fd,"SB:                     %d\n", sb_counter);
            $fwrite(fd,"SH:                     %d\n", sh_counter);
            $fwrite(fd,"SW:                     %d\n", sw_counter);
            $fwrite(fd,"CSRRW:                  %d\n", csrrw_counter);
            $fwrite(fd,"CSRRS:                  %d\n", csrrs_counter);
            $fwrite(fd,"CSRRC:                  %d\n", csrrc_counter);
            $fwrite(fd,"CSRRWI:                 %d\n", csrrwi_counter);
            $fwrite(fd,"CSRRSI:                 %d\n", csrrsi_counter);
            $fwrite(fd,"CSRRCI:                 %d\n", csrrci_counter);
        end
    end
`endif

endmodule
