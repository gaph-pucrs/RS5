/*!\file pkg.sv
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
 * Package definition.
 *
 * \detailed
 * Defines the package used in the processor units, it defines some types
 * for instruction formats, instruction types and execute units.
 */

package my_pkg;

    typedef enum  logic[2:0] {R_TYPE, I_TYPE, S_TYPE, B_TYPE, U_TYPE, J_TYPE} formatType_e;

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

    typedef enum  logic[2:0] {BYPASS_UNIT, ADDER_UNIT, LOGICAL_UNIT, SHIFTER_UNIT, BRANCH_UNIT, MEMORY_UNIT, CSR_UNIT} executionUnit_e;

    typedef enum  logic[1:0] {USER, SUPERVISOR, HYPERVISOR, MACHINE = 3} privilegeLevel_e;

    typedef enum  logic[1:0] {NONE, WRITE, SET, CLEAR} csrOperation_e;

    typedef enum  logic[1:0] {DIRECT, VECTORED} trapMode_e;

    typedef enum  logic[11:0] { MVENDORID = 12'hF11, MARCHID, MIMPID, MHARTID, MCONFIGPTR, 
                                MSTATUS = 12'h300, MISA, MEDELEG, MIDELEG, MIE, MTVEC, MCOUNTEREN, MSTATUSH = 12'h310, 
                                MSCRATCH = 12'h340, MEPC, MCAUSE, MTVAL, MIP, MTINST = 12'h34A, MTVAL2,
                                CYCLE = 12'hC00, TIME, INSTRET, CYCLEH=12'hC80, TIMEH, INSTRETH} CSRs;

    typedef enum  logic[4:0] { INSTRUCTION_ADDRESS_MISALIGNED, INSTRUCTION_ACCESS_FAULT, ILLEGAL_INSTRUCTION, BREAKPOINT, LOAD_ADDRESS_MISALIGNED,
		                        LOAD_ACCESS_FAULT, STORE_AMO_ADDRESS_MISALIGNED, STORE_AMO_ACCESS_FAULT, ECALL_FROM_UMODE,ECALL_FROM_SMODE,
                                ECALL_FROM_MMODE = 11, INSTRUCTION_PAGE_FAULT, LOAD_PAGE_FAULT, STORE_AMO_PAGE_FAULT = 15, NE} exceptionCode_e;

    typedef enum  logic[4:0] { S_SW_INT = 1, M_SW_INT = 3, S_TIM_INT = 5, M_TIM_INT = 7, S_EXT_INT = 9, M_EXT_INT = 11} interruptionCode_e;

endpackage

