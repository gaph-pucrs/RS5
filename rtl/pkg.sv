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

    const int            MEMORY_SIZE = 65535;

    typedef enum  logic[2:0] {R_type, I_type, S_type, B_type, U_type, J_type} fmts;

    typedef enum  logic[2:0] {
                              OP0, OP1, OP2, OP3, OP4, OP5, OP6, OP7, NOTOKEN='Z
                              } instruction_type;

    typedef enum  logic[5:0] {
                              NOP,LUI,INVALID,
                              ADD,SUB,SLTU,SLT,
                              XOR,OR,AND,
                              SLL,SRL,SRA,
                              BEQ,BNE,BLT,BLTU,BGE,BGEU,JAL,JALR,
                              LB,LBU,LH,LHU,LW,SB,SH,SW,
                              CSRRW,CSRRS,CSRRC,CSRRWI,CSRRSI,CSRRCI
                              } i_type;

    typedef enum  logic[2:0] {bypass, adder, logical, shifter, branch, memory, csri} xu;

    typedef enum  logic[1:0] {USER, SUPERVISOR, HYPERVISOR, MACHINE = 3} Privilege;

    typedef enum  logic[1:0] {none, write, set, clear} csr_ops;

    typedef enum  logic[11:0] { MVENDORID = 12'hF11, MARCHID, MIMPID, MHARTID, MCONFIGPTR, 
                                MSTATUS = 12'h300, MISA, MEDELEG, MIDELEG, MIE, MTVEC, MCOUNTEREN, MSTATUSH = 12'h310, 
                                MSCRATCH = 12'h340, MEPC, MCAUSE, MTVAL, MIP, MTINST = 12'h34A, MTVAL2} CSRs;

    typedef enum  logic[30:0] { INSTRUCTION_ADDRESS_MISALIGNED, INSTRUCTION_ACCESS_FAULT, ILLEGAL_INSTRUCTION, BREAKPOINT, LOAD_ADDRESS_MISALIGNED,
		                        LOAD_ACCESS_FAULT, STORE_AMO_ADDRESS_MISALIGNED, STORE_AMO_ACCESS_FAULT, ECALL_FROM_UMODE,ECALL_FROM_SMODE,
                                ECALL_FROM_MMODE = 11, INSTRUCTION_PAGE_FAULT, LOAD_PAGE_FAULT, STORE_AMO_PAGE_FAULT = 15,	NE} EXCEPTION_CODE;

    typedef enum  logic[30:0] { SUP_SW_INT = 1, MAC_SW_INT = 3, SUP_TIM_INT = 5, MAC_TIM_INT = 7, SUP_EXT_INT = 9, MAC_EXT_INT = 11} INTERRUPT_CODE;

endpackage

