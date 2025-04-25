/*!\file RS5_pkg.sv
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
 * RS5 Package definition.
 *
 * \detailed
 * Defines the package used in the processor units, it defines some types
 * for instruction formats, instruction types, operation, exceptions and
 * interrupts causes and CSR addresses.
 */

`ifndef RS5_PKG
`define RS5_PKG

package RS5_pkg;

    typedef enum integer {
        ASIC    = 0,
        FPGA    = 1
    } environment_e;

    typedef enum integer {
        MUL_OFF     = 0,
        MUL_M       = 1,
        MUL_ZMMUL   = 2
    } mul_e;

    typedef enum integer {
        AMO_OFF,
        AMO_ZALRSC,
        AMO_ZAAMO,
        AMO_A
    } atomic_e;

    typedef enum logic[5:0] {
        R_TYPE = 6'b000001,
        I_TYPE = 6'b000010,
        S_TYPE = 6'b000100,
        B_TYPE = 6'b001000,
        U_TYPE = 6'b010000,
        J_TYPE = 6'b100000
    } formatType_e;

    typedef enum {
        NOP,
        LUI,
        SRET,
        MRET,
        WFI,
        ECALL,
        EBREAK,
        INVALID,
        ADD,
        SUB,
        SLTU,
        SLT,
        XOR,
        OR,
        AND,
        SLL,
        SRL,
        SRA,
        BEQ,
        BNE,
        BLT,
        BLTU,
        BGE,
        BGEU,
        JAL,
        JALR,
        LB,
        LBU,
        LH,
        LHU,
        LW,
        SB,
        SH,
        SW,
        CSRRW,
        CSRRS,
        CSRRC,
        CSRRWI,
        CSRRSI,
        CSRRCI,
        MUL,
        MULH,
        MULHSU,
        MULHU,
        DIV,
        DIVU,
        REM,
        REMU,
        AES32ESMI,
        AES32ESI,
        VLOAD,
        VSTORE,
        VECTOR,
        AUIPC,
        LR_W,
        SC_W,
        AMO_W,
        CZERO_EQZ,
        CZERO_NEZ
    } iType_e;

    typedef enum logic[1:0] {
        USER, SUPERVISOR, HYPERVISOR, MACHINE = 3
    } privilegeLevel_e;

    typedef enum logic[1:0] {
        NONE, WRITE, SET, CLEAR
    } csrOperation_e;

    typedef enum logic {
        M_IDLE, M_CALC
    } mult_states_e;

    typedef enum logic [1:0] {
        D_IDLE, D_INIT, D_CALC, D_SIGN
    } div_states_e;

    typedef enum logic {
        V_IDLE, V_EXEC
    } vector_states_e;

    typedef enum logic [1:0] {
        VLSU_IDLE, VLSU_FIRST_CYCLE, VLSU_EXEC, VLSU_LAST_CYCLE
    } vector_lsu_states_e;

    typedef enum  logic[1:0] {DIRECT, VECTORED} trapMode_e;

    typedef enum  logic[11:0] {
        VSTART = 12'h008,
        MVENDORID = 12'hF11, MARCHID, MIMPID, MHARTID, MCONFIGPTR,
        MSTATUS = 12'h300, MISA, MEDELEG, MIDELEG, MIE, MTVEC, MCOUNTEREN, MSTATUSH = 12'h310,
        MSCRATCH = 12'h340, MEPC, MCAUSE, MTVAL, MIP, MTINST = 12'h34A, MTVAL2,
        MVMDO = 12'h7C0, MVMDS, MVMIO, MVMIS, MVMCTL, MVMDM, MVMIM,
        MCYCLE = 12'hB00, MINSTRET = 12'hB02, MHPMCOUNTER3 = 12'hB03, MHPMCOUNTER4 = 12'hB04, MHPMCOUNTER5 = 12'hB05, MHPMCOUNTER6  = 12'hB06,
        MHPMCOUNTER7  = 12'hB07, MHPMCOUNTER8  = 12'hB08, MHPMCOUNTER9  = 12'hB09, MHPMCOUNTER10 = 12'hB0A, MHPMCOUNTER11 = 12'hB0B,
        MHPMCOUNTER12 = 12'hB0C, MHPMCOUNTER13 = 12'hB0D, MHPMCOUNTER14 = 12'hB0E, MHPMCOUNTER15 = 12'hB0F, MHPMCOUNTER16 = 12'hB10,
        MHPMCOUNTER17 = 12'hB11, MHPMCOUNTER18 = 12'hB12, MHPMCOUNTER19 = 12'hB13, MHPMCOUNTER20 = 12'hB14, MHPMCOUNTER21 = 12'hB15,
        MHPMCOUNTER22 = 12'hB16, MHPMCOUNTER23 = 12'hB17, MHPMCOUNTER24 = 12'hB18, MHPMCOUNTER25 = 12'hB19, MHPMCOUNTER26 = 12'hB1A,
        MHPMCOUNTER27 = 12'hB1B, MHPMCOUNTER28 = 12'hB1C, MHPMCOUNTER29 = 12'hB1D, MHPMCOUNTER30 = 12'hB1E, MHPMCOUNTER31 = 12'hB1F,
        MCYCLEH = 12'hB80, MINSTRETH = 12'hB82, MHPMCOUNTER3H = 12'hB83, MHPMCOUNTER4H = 12'hB84, MHPMCOUNTER5H = 12'hB85, MHPMCOUNTER6H  = 12'hB86,
        MHPMCOUNTER7H  = 12'hB87, MHPMCOUNTER8H  = 12'hB88, MHPMCOUNTER9H  = 12'hB89, MHPMCOUNTER10H = 12'hB8A, MHPMCOUNTER11H = 12'hB8B,
        MHPMCOUNTER12H = 12'hB8C, MHPMCOUNTER13H = 12'hB8D, MHPMCOUNTER14H = 12'hB8E, MHPMCOUNTER15H = 12'hB8F, MHPMCOUNTER16H = 12'hB90,
        MHPMCOUNTER17H = 12'hB91, MHPMCOUNTER18H = 12'hB92, MHPMCOUNTER19H = 12'hB93, MHPMCOUNTER20H = 12'hB94, MHPMCOUNTER21H = 12'hB95,
        MHPMCOUNTER22H = 12'hB96, MHPMCOUNTER23H = 12'hB97, MHPMCOUNTER24H = 12'hB98, MHPMCOUNTER25H = 12'hB99, MHPMCOUNTER26H = 12'hB9A,
        MHPMCOUNTER27H = 12'hB9B, MHPMCOUNTER28H = 12'hB9C, MHPMCOUNTER29H = 12'hB9D, MHPMCOUNTER30H = 12'hB9E, MHPMCOUNTER31H = 12'hB9F,
                                                                             MHPMEVENT3  = 12'h323, MHPMEVENT4  = 12'h324,
        MHPMEVENT5  = 12'h325, MHPMEVENT6  = 12'h326, MHPMEVENT7  = 12'h327, MHPMEVENT8  = 12'h328, MHPMEVENT9  = 12'h329,
        MHPMEVENT10 = 12'h32A, MHPMEVENT11 = 12'h32B, MHPMEVENT12 = 12'h32C, MHPMEVENT13 = 12'h32D, MHPMEVENT14 = 12'h32E, 
        MHPMEVENT15 = 12'h32F, MHPMEVENT16 = 12'h330, MHPMEVENT17 = 12'h331, MHPMEVENT18 = 12'h332, MHPMEVENT19 = 12'h333,
        MHPMEVENT20 = 12'h334, MHPMEVENT21 = 12'h335, MHPMEVENT22 = 12'h336, MHPMEVENT23 = 12'h337, MHPMEVENT24 = 12'h338,
        MHPMEVENT25 = 12'h339, MHPMEVENT26 = 12'h33A, MHPMEVENT27 = 12'h33B, MHPMEVENT28 = 12'h33C, MHPMEVENT29 = 12'h33D,
        MHPMEVENT30 = 12'h33E, MHPMEVENT31 = 12'h33F,
                                                                                MHPMEVENT3H  = 12'h723, MHPMEVENT4H  = 12'h724,
        MHPMEVENT5H  = 12'h725, MHPMEVENT6H  = 12'h726, MHPMEVENT7H  = 12'h727, MHPMEVENT8H  = 12'h728, MHPMEVENT9H  = 12'h729,
        MHPMEVENT10H = 12'h72A, MHPMEVENT11H = 12'h72B, MHPMEVENT12H = 12'h72C, MHPMEVENT13H = 12'h72D, MHPMEVENT14H = 12'h72E, 
        MHPMEVENT15H = 12'h72F, MHPMEVENT16H = 12'h730, MHPMEVENT17H = 12'h731, MHPMEVENT18H = 12'h732, MHPMEVENT19H = 12'h733,
        MHPMEVENT20H = 12'h734, MHPMEVENT21H = 12'h735, MHPMEVENT22H = 12'h736, MHPMEVENT23H = 12'h737, MHPMEVENT24H = 12'h738,
        MHPMEVENT25H = 12'h739, MHPMEVENT26H = 12'h73A, MHPMEVENT27H = 12'h73B, MHPMEVENT28H = 12'h73C, MHPMEVENT29H = 12'h73D,
        MHPMEVENT30H = 12'h73E, MHPMEVENT31H = 12'h73F,
        MCOUNTINHIBIT = 12'h320,
        MENVCFG = 12'h30A, MENVCFGH = 12'h31A, 
        CYCLE = 12'hC00, TIME, INSTRET, CYCLEH=12'hC80, TIMEH, INSTRETH,
        VL = 12'hC20, VTYPE, VLENBYTES
    } CSRs;

    typedef enum  logic[4:0] {
        INSTRUCTION_ADDRESS_MISALIGNED, INSTRUCTION_ACCESS_FAULT, ILLEGAL_INSTRUCTION,
        BREAKPOINT, LOAD_ADDRESS_MISALIGNED, LOAD_ACCESS_FAULT, STORE_AMO_ADDRESS_MISALIGNED,
        STORE_AMO_ACCESS_FAULT, ECALL_FROM_UMODE, ECALL_FROM_SMODE, ECALL_FROM_MMODE = 11,
        INSTRUCTION_PAGE_FAULT, LOAD_PAGE_FAULT, STORE_AMO_PAGE_FAULT = 15, NE
    } exceptionCode_e;

    typedef enum  logic[4:0] {
        NO_INT = 0, S_SW_INT = 1, M_SW_INT = 3, S_TIM_INT = 5, M_TIM_INT = 7, S_EXT_INT = 9,
        M_EXT_INT = 11
    } interruptionCode_e;

    // Element width
    typedef enum logic [2:0] {
        EW8    = 3'b000,
        EW16   = 3'b001,
        EW32   = 3'b010,
        EW64   = 3'b011,
        EW128  = 3'b100,
        EW256  = 3'b101,
        EW512  = 3'b110,
        EW1024 = 3'b111
    } vew_e;

    // Length multiplier
    typedef enum logic [2:0] {
        LMUL_1    = 3'b000,
        LMUL_2    = 3'b001,
        LMUL_4    = 3'b010,
        LMUL_8    = 3'b011,
        LMUL_RSVD = 3'b100,
        LMUL_1_8  = 3'b101,
        LMUL_1_4  = 3'b110,
        LMUL_1_2  = 3'b111
    } vlmul_e;

    typedef enum {
        VNOP,
        VSETVL,
        VSETVLI,
        VSETIVLI,
        VADD,
        VSUB,
        VRSUB,
        VAND,
        VOR,
        VXOR,
        VSLL,
        VSRL,
        VSRA,
        VMSEQ,
        VMSNE,
        VMSLTU,
        VMSLT,
        VMSLEU,
        VMSLE,
        VMSGTU,
        VMSGT,
        VMINU,
        VMIN,
        VMAXU,
        VMAX,
        VMUL,
        VMULH,
        VMULHU,
        VMULHSU,
        VWMUL,
        VWMULU,
        VWMULSU,
        VDIVU,
        VDIV,
        VREMU,
        VREM,
        VMACC,
        VNMSAC,
        VMADD,
        VNMSUB,
        VREDSUM,
        VREDMAXU,
        VREDMAX,
        VREDMINU,
        VREDMIN,
        VREDAND,
        VREDOR,
        VREDXOR,
        VMV,
        VMVR,
        VMVSX,
        VMVXS,
        VMERGE
    } iTypeVector_e;

    typedef enum  logic[9:0] {
        AMONOP  = 10'b0000000001,
        AMOSWAP = 10'b0000000010,
        AMOADD  = 10'b0000000100,
        AMOXOR  = 10'b0000001000,
        AMOAND  = 10'b0000010000,
        AMOOR   = 10'b0000100000,
        AMOMIN  = 10'b0001000000,
        AMOMAX  = 10'b0010000000,
        AMOMINU = 10'b0100000000,
        AMOMAXU = 10'b1000000000
    } iTypeAtomic_e;

    typedef enum  logic[2:0] {
        OPIVV = 3'b000,
        OPFVV = 3'b001,
        OPMVV = 3'b010,
        OPIVI = 3'b011,
        OPIVX = 3'b100,
        OPFVF = 3'b101,
        OPMVX = 3'b110,
        OPCFG = 3'b111
    } opCat_e;

    typedef enum {
        UNIT_STRIDED,
        INDEXED_UNORDERED,
        STRIDED,
        INDEXED_ORDERED
    } addrModes_e;

endpackage

`endif
