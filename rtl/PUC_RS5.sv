/*!\file PUC_RS5.sv
 * PUC-RS5 VERSION - 1.0.0 - Public Release
 *
 * Distribution:  March 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Is the top Module of PUC-RS5 processor core.
 *
 * \detailed
 * This is the top Module of the PUC-RS5 processor core
 * and is responsible for the instantiation of the lower level modules
 * ans also defines the interface ports (inputs and outputs) os the processor.
 */
 
/*
`include "../rtl/my_pkg.sv"
`include "../rtl/xus/adderUnit.sv"
`include "../rtl/xus/csrUnit.sv"
`include "../rtl/xus/branchUnit.sv"
`include "../rtl/xus/logicUnit.sv"
`include "../rtl/xus/LSUnit.sv"
`include "../rtl/xus/shiftUnit.sv"
`include "../rtl/fetch.sv"
`include "../rtl/decode.sv"
`include "../rtl/execute.sv"
`include "../rtl/retire.sv"
`include "../rtl/regbank.sv"
`include "../rtl/CSRBank.sv"
*/

`define PROTO 1
// `define DEBUG 1


module PUC_RS5 
    import my_pkg::*;
(
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
    logic           read;
    logic           jump;
    logic           hazard;
    logic   [31:0]  jump_target;
    /* verilator lint_off UNUSEDSIGNAL */
    logic   [31:0]  mem_read_address_int;
    logic   [31:0]  mem_write_address_int;
    /* verilator lint_on UNUSEDSIGNAL */

    logic           predict_branch_taken;
    logic   [31:0]  predict_branch_pc;
    logic   [31:0]  predict_branch_pc_next;

    logic           predict_jump_taken;
    logic   [31:0]  predict_jump_pc;
    logic   [31:0]  predict_jump_pc_next;

//////////////////////////////////////////////////////////////////////////////
// Decoder signals
//////////////////////////////////////////////////////////////////////////////

    logic   [31:0]  pc_decode;
    logic   [2:0]   tag_decode;

//////////////////////////////////////////////////////////////////////////////
// RegBank signals
//////////////////////////////////////////////////////////////////////////////

    logic   [4:0]   rs1, rs2;
    logic   [31:0]  regbank_data1, regbank_data2, rs1_data_read, rs2_data_read;
    logic           write_enable_regbank_int, regbank_write_enable;
    logic   [4:0]   rd;
    logic   [31:0]  regbank_data_writeback;

//////////////////////////////////////////////////////////////////////////////
// Execute signals
//////////////////////////////////////////////////////////////////////////////

    iType_e         instruction_operation_execute;
    logic   [31:0]  first_operand_execute, second_operand_execute, third_operand_execute;
    logic   [31:0]  instruction_execute;
    logic   [31:0]  pc_execute;
    logic   [2:0]   tag_execute;
    logic           exception_execute;
    logic           predicted_branch_execute;

//////////////////////////////////////////////////////////////////////////////
// Retire signals
//////////////////////////////////////////////////////////////////////////////

    logic           jump_retire, we_retire;
    logic   [3:0]   mem_write_enable_retire;
    iType_e         instruction_operation_retire;
    logic   [31:0]  instruction_retire;
    logic   [31:0]  result_retire [1:0];
    logic   [2:0]   tag_retire;
    logic   [2:0]   curr_retire_tag;
    logic   [31:0]  pc_retire;
    /* verilator lint_off UNUSEDSIGNAL */
    logic           exception_retire;
    logic           killed;
    /* verilator lint_on UNUSEDSIGNAL */
    logic           predicted_branch_retire;

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
        .predict_branch_taken_i(predict_branch_taken),
        .predict_branch_pc_i(predict_branch_pc),
        .predict_branch_pc_next_i(predict_branch_pc_next),
        .predict_jump_taken_i(predict_jump_taken),
        .predict_jump_pc_i(predict_jump_pc),
        .predict_jump_pc_next_i(predict_jump_pc_next),
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
    assign rs1_data_read = (rs1 == rd && rd != '0 && regbank_write_enable) 
                            ? regbank_data_writeback 
                            : regbank_data1;

    assign rs2_data_read = (rs2 == rd && rd != '0 && regbank_write_enable) 
                            ? regbank_data_writeback 
                            : regbank_data2;

    decode decoder1 (
        .clk(clk), 
        .reset(reset),
        .stall(stall),
        .instruction_i(instruction_i), 
        .pc_i(pc_decode), 
        .tag_i(tag_decode), 
        .rs1_data_read_i(rs1_data_read), 
        .rs2_data_read_i(rs2_data_read), 
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
        .exception_o(exception_execute),

        .predicted_branch_o(predicted_branch_execute),
        .predict_branch_taken_o(predict_branch_taken),
        .predict_branch_pc_o(predict_branch_pc),
        .predict_branch_pc_next_o(predict_branch_pc_next),

        .predict_jump_taken_o(predict_jump_taken),
        .predict_jump_pc_o(predict_jump_pc),
        .predict_jump_pc_next_o(predict_jump_pc_next),

        .killed_i(killed)

    );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// REGISTER BANK ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    assign regbank_write_enable = (rd == '0) 
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
        .exception_o(exception_retire),

        .predicted_branch_i(predicted_branch_execute),
        .predicted_branch_o(predicted_branch_retire)
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
        .killed_o(killed),
        .mem_write_enable_o(mem_write_enable_o), 
        .mem_write_address_o(mem_write_address_int), 
        .mem_data_o(mem_data_o),
        .mem_data_i(mem_data_i), 
        .current_retire_tag_o(curr_retire_tag),
        .exception_code_o(Exception_Code),
        .raise_exception_o(RAISE_EXCEPTION), 
        .machine_return_o(MACHINE_RETURN),
        .interrupt_ack_o(interrupt_ack_o),
        .interrupt_pending_i(Interrupt_pending),

        .predicted_branch_i(predicted_branch_retire)
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
        .jump_i(jump),
        .jump_target_i(jump_target),
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
            mem_address_o[31:2] = mem_write_address_int[31:2];
        end
        else begin
            mem_address_o[31:2] = mem_read_address_int[31:2];
        end
        mem_address_o[1:0] = '0;

        if (mem_write_enable_o != '0 || read) begin
            mem_operation_enable_o = 1;
        end
        else begin
            mem_operation_enable_o = 0;
        end
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////// DEBUG ///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

`ifdef DEBUG
    int fd;
    int clock_counter, instuctions_retired_counter, instructions_killed_counter, jumps_counter;
    int interrupt_ack_counter, raise_exception_counter, context_switch_counter;
    int hazard_counter, stall_counter, hazard_stall_counter;
    int bypass_counter, adder_counter, logical_counter, shifter_counter, branch_counter, memory_counter, csr_counter;
    int nop_counter, lui_counter, sret_counter, mret_counter, wfi_counter, ecall_counter, ebreak_counter, invalid_counter;
    int add_counter, sub_counter, sltu_counter, slt_counter;
    int xor_counter, or_counter, and_counter;
    int sll_counter, srl_counter, sra_counter;
    int beq_counter, bne_counter, blt_counter, bltu_counter, bge_counter, bgeu_counter, jal_counter, jalr_counter;
    int lb_counter, lbu_counter, lh_counter, lhu_counter, lw_counter, sb_counter, sh_counter, sw_counter;
    int csrrw_counter, csrrs_counter, csrrc_counter, csrrwi_counter, csrrsi_counter, csrrci_counter;

    executionUnit_e execution_unit_selection_retire;

    assign execution_unit_selection_retire = executionUnit_e'(instruction_operation_retire[5:3]);

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

            bypass_counter              <= 0;
            adder_counter               <= 0;
            logical_counter             <= 0;
            shifter_counter             <= 0;
            branch_counter              <= 0;
            memory_counter              <= 0;
            csr_counter                 <= 0;

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

                bypass_counter  <= (execution_unit_selection_retire == BYPASS_UNIT)  ? bypass_counter  + 1 : bypass_counter;
                adder_counter   <= (execution_unit_selection_retire == ADDER_UNIT)   ? adder_counter   + 1 : adder_counter;
                logical_counter <= (execution_unit_selection_retire == LOGICAL_UNIT) ? logical_counter + 1 : logical_counter;
                shifter_counter <= (execution_unit_selection_retire == SHIFTER_UNIT) ? shifter_counter + 1 : shifter_counter;
                branch_counter  <= (execution_unit_selection_retire == BRANCH_UNIT)  ? branch_counter  + 1 : branch_counter;
                memory_counter  <= (execution_unit_selection_retire == MEMORY_UNIT)  ? memory_counter  + 1 : memory_counter;
                csr_counter     <= (execution_unit_selection_retire == CSR_UNIT)     ? csr_counter     + 1 : csr_counter;

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
        if (mem_write_address_int == 32'h80000000 && mem_write_enable_o != '0) begin
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

            $fwrite(fd,"\nINSTRUCTIONS PER EXECUTE UNIT:\n");
            $fwrite(fd,"BYPASS:                 %d\n", bypass_counter);
            $fwrite(fd,"ADDER:                  %d\n", adder_counter);
            $fwrite(fd,"LOGICAL:                %d\n", logical_counter);
            $fwrite(fd,"SHIFTER:                %d\n", shifter_counter);
            $fwrite(fd,"BRANCHES:               %d\n", branch_counter);
            $fwrite(fd,"LOAD/STORE:             %d\n", memory_counter);
            $fwrite(fd,"CSR:                    %d\n", csr_counter);

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
