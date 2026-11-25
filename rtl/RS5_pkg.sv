/*!\file RS5_pkg.sv
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
        CZERO_NEZ,
        ALU_ROL,
        ALU_ROR,  
        ALU_PACK, 
        ALU_PACKH,
        ALU_XNOR, 
        ALU_ORN,  
        ALU_ANDN,
        ALU_ZIP,
        ALU_BREV8,
        ALU_REV8,
        ALU_UNZIP,
        SIG0H,
        SIG0L,
        SIG1H,
        SIG1L,
        SUM0R,
        SUM1R,
        SIG0, 
        SIG1, 
        SUM0,
        SUM1,
        KYBER_ADD, 
        KYBER_SUB,
        KYBER_CBD2,
        KYBER_CBD3, 
        KYBER_MUL, 
        KYBER_COMPRESS
    } iType_e;

    typedef enum logic[1:0] {
        USER, SUPERVISOR, HYPERVISOR, MACHINE = 3
    } privilegeLevel_e;

    typedef enum logic[1:0] {
        NONE, WRITE, SET, CLEAR
    } csrOperation_e;

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

    typedef enum logic[10:0] {
        SHA2NOP   = 11'b00000000001,
        SHA2SIG0  = 11'b00000000010,
        SHA2SIG1  = 11'b00000000100,
        SHA2SUM0  = 11'b00000001000,
        SHA2SUM1  = 11'b00000010000,
        SHA2SIG0H = 11'b00000100000,
        SHA2SIG0L = 11'b00001000000,
        SHA2SIG1H = 11'b00010000000,
        SHA2SIG1L = 11'b00100000000,
        SHA2SUM0R = 11'b01000000000,
        SHA2SUM1R = 11'b10000000000
    } iTypeSha2_e;

    typedef enum logic[6:0] {
        KYBNOP      = 7'b0000001,
        KYBADD      = 7'b0000010,
        KYBSUB      = 7'b0000100,
        KYBCBD2     = 7'b0001000,
        KYBCBD3     = 7'b0010000,
        KYBMUL      = 7'b0100000,
        KYBCOMPRESS = 7'b1000000
    } iTypeKyber_e;

    typedef enum logic[11:0] {
        ZBKBNOP   = 12'b000000000001,
        ZBKBROR   = 12'b000000000010,
        ZBKBROL   = 12'b000000000100,
        ZBKBPACK  = 12'b000000001000,
        ZBKBPACKH = 12'b000000010000,
        ZBKBXNOR  = 12'b000000100000,
        ZBKBORN   = 12'b000001000000,
        ZBKBANDN  = 12'b000010000000,
        ZBKBZIP   = 12'b000100000000,
        ZBKBUNZIP = 12'b001000000000,
        ZBKBBREV8 = 12'b010000000000,
        ZBKBREV8  = 12'b100000000000
    } iTypeZbkb_e;

    /* Vector operation select. The entries after VSLIDE1DOWN are the      */
    /* Zve32x classes added later; the decoder returns VNOP (illegal) for   */
    /* the instructions of a class not implemented yet.                     */
    typedef enum logic [6:0] {
        VNOP,
        // Configuration
        VSETVL, VSETVLI, VSETIVLI,
        // Add/subtract
        VADD, VSUB, VRSUB,
        // Bitwise logical (VLogicEnable)
        VAND, VOR, VXOR,
        // Shifts
        VSLL, VSRL, VSRA,
        // Integer compares
        VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT,
        // Min/max (VMinMaxEnable)
        VMINU, VMIN, VMAXU, VMAX,
        // Multiply and widening multiply
        VMUL, VMULH, VMULHU, VMULHSU, VWMUL, VWMULU, VWMULSU,
        // Divide and remainder (VDivEnable)
        VDIVU, VDIV, VREMU, VREM,
        // Multiply-add
        VMACC, VNMSAC, VMADD, VNMSUB,
        // Sum reduction (VRedSumEnable)
        VREDSUM,
        // Min/max reductions (VRedMinMaxEnable)
        VREDMAXU, VREDMAX, VREDMINU, VREDMIN,
        // Logical reductions (VRedLogicEnable)
        VREDAND, VREDOR, VREDXOR,
        // Moves
        VMV, VMVR, VMVSX, VMVXS,
        // Merge (VMergeEnable)
        VMERGE,
        // Slide by one
        VSLIDE1UP, VSLIDE1DOWN,
        // Integer extension
        VZEXT, VSEXT,
        // Widening add/subtract
        VWADDU, VWADD, VWSUBU, VWSUB, VWADDU_W, VWADD_W, VWSUBU_W, VWSUB_W,
        // Widening multiply-add and sum reduction
        VWMACC, VWREDSUM,
        // Add/subtract with carry (VCarryEnable)
        VADC, VMADC, VSBC, VMSBC,
        // Narrowing shift (VNarrowEnable)
        VNSRL, VNSRA,
        // Fixed point (VFixedPointEnable)
        VSADDU, VSADD, VSSUBU, VSSUB, VAADDU, VAADD, VASUBU, VASUB,
        VSMUL, VSSRL, VSSRA, VNCLIPU, VNCLIP,
        // Mask logical (VMaskLogicEnable)
        VMAND, VMNAND, VMANDN, VMXOR, VMOR, VMNOR, VMORN, VMXNOR,
        // Mask bits (VMaskBitsEnable)
        VCPOP, VFIRST, VMSBF, VMSIF, VMSOF, VIOTA, VID,
        // Slide (VSlideEnable)
        VSLIDEUP, VSLIDEDOWN,
        // Gather and compress (VGatherEnable)
        VRGATHER, VRGATHEREI16, VCOMPRESS,
        // Loads and stores
        VLD,            // Vector load  (was iType_e VLOAD)
        VST             // Vector store (was iType_e VSTORE)
    } iTypeVector_e;

    /* Vector operations whose result is a mask (compares, carry/borrow-out) */
    function automatic logic is_mask_result(iTypeVector_e op);
        return op inside {VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT,
                          VMADC, VMSBC};
    endfunction

    /* Vector reductions: they write a scalar result to element 0 of vd */
    function automatic logic is_reduction(iTypeVector_e op);
        return op inside {VREDSUM, VREDMAXU, VREDMAX, VREDMINU, VREDMIN, VREDAND, VREDOR, VREDXOR};
    endfunction

    typedef struct packed {
        // AMO operation select (one-hot, AMONOP when unused)
        iTypeAtomic_e amo_op;
        // SHA2 operation select (one-hot, SHA2NOP when unused)
        iTypeSha2_e  sha2_op;
        // Kyber operation select (one-hot, KYBNOP when unused)
        iTypeKyber_e kyber_op;
        // Zbkb operation select (one-hot, ZBKBNOP when unused)
        iTypeZbkb_e  zbkb_op;
        // Vector operation select (VNOP when unused)
        iTypeVector_e vector_op;
        // Pipeline status
        logic        hazard;
        logic        killed;
        logic        compressed;
        logic        bp_taken;
        logic        exc_ilegal_inst;
        logic        exc_inst_access_fault;
        logic        exc_inst_fault_upper;
        // Result select
        logic        is_nop;
        logic        is_add;
        logic        is_csr;
        logic        is_jal_jalr;
        logic        is_lui;
        logic        is_auipc;
        logic        is_slt;
        logic        is_sltu;
        logic        is_xor;
        logic        is_or;
        logic        is_and;
        logic        is_sll;
        logic        is_srl;
        logic        is_sra;
        logic        is_mul;
        logic        is_div;
        logic        is_rem;
        logic        is_aes;
        logic        is_vector;
        // Vector loads/stores (subset of is_vector)
        logic        is_vector_mem;
        // Vector instruction that depends on vtype (traps when vill = 1)
        logic        uses_vtype;
        logic        is_zicond;
        logic        is_sha2;
        logic        is_zbkb;
        logic        is_kyber;
        logic        is_sc;
        // Memory
        logic        is_load;
        logic        is_store;
        logic        is_amo;
        logic        is_lr;
        // Branch/jump control
        logic        is_beq;
        logic        is_bne;
        logic        is_blt;
        logic        is_bltu;
        logic        is_bge;
        logic        is_bgeu;
        logic        is_jalr;
        // Write-back suppress
        logic        rd_we;
        // Opcode-derived exception/system flags
        logic        is_ecall;
        logic        is_ebreak;
        logic        is_mret;
        logic        is_sret;
        logic        is_wfi;
        // Memory width/sign for load/store
        logic        is_byte;
        logic        is_half;
        logic        is_unsigned;
        // Sub-op selects
        logic        is_sub;
        logic        is_amo_w;
        // Mul sub-op
        logic        mul_low;
        logic [1:0]  mul_signed_mode;
        // AES sub-op
        logic        aes_is_mix;
        // Zicond sub-op
        logic        zicond_is_eqz;
        // Div sub-op
        logic        div_signed;
        // CSR operation
        csrOperation_e csr_op;
        logic        csr_rd_uses_rs1;
        logic        csr_wr_uses_rs1;
    } exec_ctrl_t;

    /* Integer extension of a vector source: none, or from 1/2 or 1/4 of SEW */
    typedef enum logic [1:0] {
        EXT_NONE, EXT_VF2, EXT_VF4
    } vext_sel_e;

    /* Vector control decoded once in vectorUnit, from the operation and vm. */
    /* The instructions not implemented yet add their fields here.          */
    typedef struct packed {
        // The adder subtracts: the second addend is inverted and the
        // carry-in of each element is set (a + ~b + 1 = a - b)
        logic        is_sub;
        // The carry-in (borrow-in for a subtraction) of each element is
        // its v0 bit (vadc, vsbc, and vmadc, vmsbc with vm = 0)
        logic        use_carry_in;
        // v0 is an operand, not a mask (vmerge, vadc, vsbc, vmadc, vmsbc)
        logic        mask_is_data;
        // vs2 is extended to SEW from 1/2 or 1/4 of it (vzext, vsext)
        vext_sel_e   ext_sel;
        // The extension copies the sign (vsext, signed widening add/subtract)
        logic        ext_signed;
        // vs2 already has EEW = 2*SEW and is not extended (vwadd.w*, vwsub.w*)
        logic        src2_wide;
    } vector_ctrl_t;

    typedef struct packed {
        logic        valid;
        logic        compressed;
        logic        jumping;
        logic        jump_misaligned;
        logic        inst_fault;
        logic        inst_fault_upper;
    } decode_ctrl_t;

    typedef struct packed {
        logic        rd_we;
        logic        is_load;
        logic        is_lr;
        logic        is_sc;
        logic        is_byte;
        logic        is_half;
        logic        is_unsigned;
    } wb_ctrl_t;

    typedef enum logic {
        M_IDLE, M_CALC
    } mult_states_e;

    typedef enum logic [1:0] {
        D_IDLE, D_INIT, D_CALC, D_SIGN
    } div_states_e;

    typedef enum logic {
        V_IDLE, V_EXEC
    } vector_states_e;

    typedef enum logic [2:0] {
        VLSU_IDLE, VLSU_FIRST_CYCLE, VLSU_EXEC, VLSU_LAST_CYCLE, VLSU_DELAY
    } vector_lsu_states_e;

    typedef enum  logic[1:0] {DIRECT, VECTORED} trapMode_e;

    typedef enum  logic[11:0] {
        VSTART        = 12'h008, VXSAT, VXRM,
        VCSR          = 12'h00F,
        MSTATUS       = 12'h300, MISA, 
        MIE           = 12'h304, MTVEC, MCOUNTEREN,
        MENVCFG       = 12'h30A, 
        MSTATUSH      = 12'h310,
        MENVCFGH      = 12'h31A, 
        MCOUNTINHIBIT = 12'h320,
        MHPMEVENT3    = 12'h323, MHPMEVENT4, MHPMEVENT5, MHPMEVENT6, MHPMEVENT7, MHPMEVENT8, MHPMEVENT9, MHPMEVENT10, 
                                 MHPMEVENT11, MHPMEVENT12, MHPMEVENT13, MHPMEVENT14, MHPMEVENT15, MHPMEVENT16, 
                                 MHPMEVENT17, MHPMEVENT18, MHPMEVENT19, MHPMEVENT20, MHPMEVENT21, MHPMEVENT22, 
                                 MHPMEVENT23, MHPMEVENT24, MHPMEVENT25, MHPMEVENT26, MHPMEVENT27, MHPMEVENT28, 
                                 MHPMEVENT29, MHPMEVENT30, MHPMEVENT31,
        MSCRATCH      = 12'h340, MEPC, MCAUSE, MTVAL, MIP, 
        MHPMEVENT3H   = 12'h723, MHPMEVENT4H, MHPMEVENT5H, MHPMEVENT6H, MHPMEVENT7H, MHPMEVENT8H, MHPMEVENT9H,
                                 MHPMEVENT10H, MHPMEVENT11H, MHPMEVENT12H, MHPMEVENT13H, MHPMEVENT14H, MHPMEVENT15H, 
                                 MHPMEVENT16H, MHPMEVENT17H, MHPMEVENT18H, MHPMEVENT19H, MHPMEVENT20H, MHPMEVENT21H, 
                                 MHPMEVENT22H, MHPMEVENT23H, MHPMEVENT24H, MHPMEVENT25H, MHPMEVENT26H, MHPMEVENT27H, 
                                 MHPMEVENT28H, MHPMEVENT29H, MHPMEVENT30H, MHPMEVENT31H,
        MVMDO         = 12'h7C0, MVMDS, MVMIO, MVMIS, MVMCTL, MVMDM, MVMIM,
        MCYCLE        = 12'hB00, 
        MINSTRET      = 12'hB02, MHPMCOUNTER3, MHPMCOUNTER4, MHPMCOUNTER5, MHPMCOUNTER6, MHPMCOUNTER7, MHPMCOUNTER8, 
                                 MHPMCOUNTER9, MHPMCOUNTER10, MHPMCOUNTER11, MHPMCOUNTER12, MHPMCOUNTER13, 
                                 MHPMCOUNTER14, MHPMCOUNTER15, MHPMCOUNTER16, MHPMCOUNTER17, MHPMCOUNTER18, 
                                 MHPMCOUNTER19, MHPMCOUNTER20, MHPMCOUNTER21, MHPMCOUNTER22, MHPMCOUNTER23, 
                                 MHPMCOUNTER24, MHPMCOUNTER25, MHPMCOUNTER26, MHPMCOUNTER27, MHPMCOUNTER28, 
                                 MHPMCOUNTER29, MHPMCOUNTER30, MHPMCOUNTER31,
        MCYCLEH       = 12'hB80, 
        MINSTRETH     = 12'hB82, MHPMCOUNTER3H, MHPMCOUNTER4H, MHPMCOUNTER5H, MHPMCOUNTER6H, MHPMCOUNTER7H, 
                                 MHPMCOUNTER8H, MHPMCOUNTER9H, MHPMCOUNTER10H, MHPMCOUNTER11H, MHPMCOUNTER12H, 
                                 MHPMCOUNTER13H, MHPMCOUNTER14H, MHPMCOUNTER15H, MHPMCOUNTER16H, MHPMCOUNTER17H, 
                                 MHPMCOUNTER18H, MHPMCOUNTER19H, MHPMCOUNTER20H, MHPMCOUNTER21H, MHPMCOUNTER22H, 
                                 MHPMCOUNTER23H, MHPMCOUNTER24H, MHPMCOUNTER25H, MHPMCOUNTER26H, MHPMCOUNTER27H, 
                                 MHPMCOUNTER28H, MHPMCOUNTER29H, MHPMCOUNTER30H, MHPMCOUNTER31H,
        CYCLE         = 12'hC00, TIME, INSTRET, HPMCOUNTER3, HPMCOUNTER4, HPMCOUNTER5, HPMCOUNTER6, HPMCOUNTER7, 
                                 HPMCOUNTER8, HPMCOUNTER9, HPMCOUNTER10, HPMCOUNTER11, HPMCOUNTER12, HPMCOUNTER13, 
                                 HPMCOUNTER14, HPMCOUNTER15, HPMCOUNTER16, HPMCOUNTER17, HPMCOUNTER18, HPMCOUNTER19, 
                                 HPMCOUNTER20, HPMCOUNTER21, HPMCOUNTER22, HPMCOUNTER23, HPMCOUNTER24, HPMCOUNTER25, 
                                 HPMCOUNTER26, HPMCOUNTER27, HPMCOUNTER28, HPMCOUNTER29, HPMCOUNTER30, HPMCOUNTER31,
        VL            = 12'hC20, VTYPE, VLENBYTES, 
        CYCLEH        = 12'hC80, TIMEH, INSTRETH, HPMCOUNTER3H, HPMCOUNTER4H, HPMCOUNTER5H, HPMCOUNTER6H, HPMCOUNTER7H, 
                                 HPMCOUNTER8H, HPMCOUNTER9H, HPMCOUNTER10H, HPMCOUNTER11H, HPMCOUNTER12H, HPMCOUNTER13H, 
                                 HPMCOUNTER14H, HPMCOUNTER15H, HPMCOUNTER16H, HPMCOUNTER17H, HPMCOUNTER18H, 
                                 HPMCOUNTER19H, HPMCOUNTER20H, HPMCOUNTER21H, HPMCOUNTER22H, HPMCOUNTER23H, 
                                 HPMCOUNTER24H, HPMCOUNTER25H, HPMCOUNTER26H, HPMCOUNTER27H, HPMCOUNTER28H, 
                                 HPMCOUNTER29H, HPMCOUNTER30H, HPMCOUNTER31H,
        MVENDORID     = 12'hF11, MARCHID, MIMPID, MHARTID, MCONFIGPTR
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

    typedef enum integer {
        RED_MAX,
        RED_MAXU,
        RED_MIN,
        RED_MINU,
        RED_AND,
        RED_OR,
        RED_XOR,
        RED_SUM
    } red_op_e;

endpackage

`endif
