package my_pkg;

   typedef enum  logic[2:0] {R_type, I_type, S_type, B_type, U_type, J_type} fmts;

   typedef enum  logic[2:0] {
                              OP0, OP1, OP2, OP3, OP4, OP5, OP6, OP7, NOTOKEN='Z
                              } instruction_type;

   typedef enum  logic[4:0] {
                              NOP,LUI,INVALID,
                              ADD,SUB,SLTU,SLT,
                              XOR,OR,AND,
                              SLL,SRL,SRA,
                              BEQ,BNE,BLT,BLTU,BGE,BGEU,JAL,JALR,
                              LB,LBU,LH,LHU,LW,SB,SH,SW
                              } i_type;

   typedef enum  logic[2:0] {bypass, adder, logical, shifter, branch, memory} xu;

   const int            MEMORY_SIZE = 65535;

   typedef logic[7:0] [0:65535] ram_memory;

endpackage