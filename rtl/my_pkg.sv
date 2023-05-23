/*!\file pkg.sv
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
 * Package definition.
 *
 * \detailed
 * Defines the package used in the processor units, it defines some types
 * for instruction formats, instruction types and execute units.
 */

package my_pkg;

    typedef enum  logic[2:0] {
        R_TYPE, I_TYPE, S_TYPE, B_TYPE, U_TYPE, J_TYPE
    } formatType_e;

    typedef enum  logic[2:0] {
        OP0, OP1, OP2, OP3, OP4, OP5, OP6, OP7
    } operationType_e;

    typedef enum  logic[5:0] {
        NOP = 6'o00,LUI,SRET,MRET,WFI,ECALL,EBREAK,INVALID,
        ADD = 6'o10,SUB,SLTU,SLT,
        XOR = 6'o20,OR,AND,
        SLL = 6'o30,SRL,SRA,
        BEQ = 6'o40,BNE,BLT,BLTU,BGE,BGEU,JAL,JALR,
        LB  = 6'o50,LBU,LH,LHU,LW,SB,SH,SW,
        CSRRW=6'o60,CSRRS,CSRRC,CSRRWI,CSRRSI,CSRRCI
    } iType_e;

    typedef enum  logic[2:0] {
        BYPASS_UNIT, ADDER_UNIT, LOGICAL_UNIT, SHIFTER_UNIT, BRANCH_UNIT, 
        MEMORY_UNIT, CSR_UNIT
    } executionUnit_e;

    typedef enum  logic[1:0] {
        USER, SUPERVISOR, HYPERVISOR, MACHINE = 3
    } privilegeLevel_e;

    typedef enum  logic[1:0] {
        NONE, WRITE, SET, CLEAR
    } csrOperation_e;

    typedef enum  logic[1:0] {DIRECT, VECTORED} trapMode_e;

    typedef enum  logic[11:0] { 
        MVENDORID = 12'hF11, MARCHID, MIMPID, MHARTID, MCONFIGPTR, 
        MSTATUS = 12'h300, MISA, MEDELEG, MIDELEG, MIE, MTVEC, MCOUNTEREN, MSTATUSH = 12'h310, 
        MSCRATCH = 12'h340, MEPC, MCAUSE, MTVAL, MIP, MTINST = 12'h34A, MTVAL2,
        CYCLE = 12'hC00, TIME, INSTRET, CYCLEH=12'hC80, TIMEH, INSTRETH
    } CSRs;

    typedef enum  logic[4:0] {  
        INSTRUCTION_ADDRESS_MISALIGNED, INSTRUCTION_ACCESS_FAULT, ILLEGAL_INSTRUCTION, 
        BREAKPOINT, LOAD_ADDRESS_MISALIGNED, LOAD_ACCESS_FAULT, STORE_AMO_ADDRESS_MISALIGNED, 
        STORE_AMO_ACCESS_FAULT, ECALL_FROM_UMODE,ECALL_FROM_SMODE, ECALL_FROM_MMODE = 11, 
        INSTRUCTION_PAGE_FAULT, LOAD_PAGE_FAULT, STORE_AMO_PAGE_FAULT = 15, NE
    } exceptionCode_e;

    typedef enum  logic[4:0] {
        S_SW_INT = 1, M_SW_INT = 3, S_TIM_INT = 5, M_TIM_INT = 7, S_EXT_INT = 9, 
        M_EXT_INT = 11
    } interruptionCode_e;

    typedef enum  logic[6:0] { 
        OP_IMM = 7'b0010011, OP_LUI = 7'b0110111, OP_AUIPC = 7'b0010111, 
        OP_OP = 7'b0110011, OP_JAL = 7'b1101111, OP_JALR = 7'b1100111, 
        OP_BRANCH = 7'b1100011, OP_LOAD = 7'b0000011, OP_STORE = 7'b0100011, 
        OP_MISC_MEM = 7'b0001111, OP_SYSTEM = 7'b1110011 
    } opcodes_e;

    typedef enum  logic[2:0] { 
        F3_ADDI  = 3'b000, F3_SLLI, F3_SLTI, F3_SLTIU, F3_XORI, F3_SRLI_SRAI, F3_ORI, F3_ANDI
    } funct3_imm_e;

    typedef enum  logic[2:0] { 
        F3_ADD   = 3'b000, F3_SLL, F3_SLT, F3_SLTU, F3_XOR, F3_SR, F3_OR, F3_AND
    } funct3_op_e;

    typedef enum  logic[2:0] { 
        F3_BEQ   = 3'b000, F3_BNE, F3_BLT = 3'b100, F3_BGE, F3_BLTU, F3_BGEU
    } funct3_branch_e;

    typedef enum  logic[2:0] { 
        F3_LB    = 3'b000, F3_LH, F3_LW, F3_LBU = 3'b100, F3_LHU
    } funct3_load_e;

    typedef enum  logic[2:0] { 
        F3_SB    = 3'b000, F3_SH, F3_SW
    } funct3_store_e;

    typedef enum  logic[2:0] { 
        F3_PRIV  = 3'b000, F3_CSRRW, F3_CSRRS, F3_CSRRC, F3_CSRRWI = 3'b101, F3_CSRRSI, F3_CSRRCI
    } funct3_system_e;

    typedef enum  logic[2:0] { 
        F3_JALR  = 3'b000
    } funct3_jalr_e;

    typedef enum  logic[2:0] { 
        F3_FENCE = 3'b000
    } funct3_misc_mem_e;    

    typedef enum  logic[6:0] { 
        F7_SLLI = 7'b0000000
    } funct7_sl_e;

    typedef enum  logic[6:0] { 
        F7_SRLI = 7'b0000000, F7_SRAI = 7'b0100000
    } funct7_sr_e;

    typedef enum  logic[6:0] { 
        F7_SUB_SRA = 7'b0100000
    } funct7_sub_sra_e;

    typedef enum  logic[6:0] { 
        F7_ECALL_EBREAK = 7'b0000000, F7_WFI = 7'b0001000, F7_MRET = 7'b0011000
    } funct7_priv_e;

    typedef enum  logic[4:0] { 
        RS2_ECALL = 5'b00000, RS2_EBREAK, RS2_RET, RS2_WFI
    } rs2Op_e;

endpackage

