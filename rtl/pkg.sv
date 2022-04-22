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

    typedef enum  logic[1:0] {none, write, set, clear} csr_ops;

    const int            MEMORY_SIZE = 65535;

endpackage