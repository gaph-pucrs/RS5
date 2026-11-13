/*!\file decode.sv
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
 * Decoder Unit is the second stage of RS5 processor core.
 *
 * \detailed
 * The decoder unit is the second stage of the RS5 processor core and
 * is responsible for identifying the instruction format and operation,
 * fetching the operands in the register bank, and calculating the immediate
 * operand. It contains the mechanism of hazard detection, if a hazard is
 * detected (e.g. one operand is a locked register) a bubble is issued, which
 * consists in a NOP (NO Operation) instruction.
 */

`include "RS5_pkg.sv"

module decode
    import RS5_pkg::*;
#(
    parameter mul_e         MULEXT       = MUL_M,
    parameter atomic_e      AMOEXT       = AMO_A,
    parameter bit           COMPRESSED   = 1'b1,
    parameter bit           ZKNEEnable   = 1'b0,
    parameter bit           ZBKBEnable   = 1'b0,
    parameter bit           ZKNHEnable   = 1'b0,
    parameter bit           XKYBEREnable = 1'b0,
    parameter bit           ZICONDEnable = 1'b0,
    parameter bit           VEnable      = 1'b0,
    parameter bit           BRANCHPRED   = 1'b1,
    parameter bit           FORWARDING   = 1'b1
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           enable,
    input   logic           sys_reset,

    /* Registered inputs from fetch */
    input   decode_ctrl_t   ctrl_i,
    input   logic [31:0]    pc_i,
    input   logic [31:0]    instruction_i,

    /* Combinational inputs from execute */
    input   logic           should_jump_i,
    /* Not used without BP */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           jump_rollback_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* Combinational inputs from mem_access */

    /* Combinational regbank access */
    output  logic  [4:0]    rs1_o,
    output  logic  [4:0]    rs2_o,
    input   logic [31:0]    rs1_data_read_i,
    input   logic [31:0]    rs2_data_read_i,

    /* Combinational forwarding */
    input   logic           regbank_we_i,
    input   logic [ 4:0]    rd_retire_i,
    input   logic [31:0]    writeback_i,
    /* Not used without forwarding */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           execute_we_i,
    input   logic           mem_access_we_i,
    input   logic [ 4:0]    rd_mem_access_i,
    input   logic [31:0]    result_i,
    input   logic [31:0]    mem_access_result_i,
    /* verilator lint_on UNUSEDSIGNAL */  
    
    /* Combinational outputs to fetch */
    output  logic           dec_hazard_o,
    output  logic           bp_take_o,
    output  logic [31:0]    bp_target_o,

    /* Registered outputs to execute */
    output  exec_ctrl_t     ctrl_o,
    output  logic  [4:0]    rd_o,
    output  logic  [4:0]    instr_rs1_o,
    output  logic [11:0]    csr_address_o,
    output  logic [31:0]    pc_o,
    output  logic [31:0]    rs1_data_o,
    output  logic [31:0]    rs2_data_o,
    output  logic [31:0]    second_operand_o,
    output  logic [31:0]    instruction_o,
    output  logic [31:0]    jump_imm_target_o
);

//////////////////////////////////////////////////////////////////////////////
// Find out the type of the instruction
//////////////////////////////////////////////////////////////////////////////

    logic   killed;
    logic   hazard;
    iType_e instruction_operation;

    logic [2:0] funct3;
    logic [6:0] funct7;
    logic [4:0] opcode;

    assign funct3 = instruction_i[14:12];
    assign funct7 = instruction_i[31:25];
    assign opcode = instruction_i[6:2];

    iType_e decode_branch;
    always_comb begin
        unique case (funct3)
            3'b000:     decode_branch = BEQ;
            3'b001:     decode_branch = BNE;
            3'b100:     decode_branch = BLT;
            3'b101:     decode_branch = BGE;
            3'b110:     decode_branch = BLTU;
            3'b111:     decode_branch = BGEU;
            default:    decode_branch = INVALID;
        endcase
    end

    iType_e decode_load;
    always_comb begin
        unique case (funct3)
            3'b000:     decode_load = LB;
            3'b001:     decode_load = LH;
            3'b010:     decode_load = LW;
            3'b100:     decode_load = LBU;
            3'b101:     decode_load = LHU;
            default:    decode_load = INVALID;
        endcase
    end

    iType_e decode_store;
    always_comb begin
        unique case (funct3)
            3'b000:     decode_store = SB;
            3'b001:     decode_store = SH;
            3'b010:     decode_store = SW;
            default:    decode_store = INVALID;
        endcase
    end

    iType_e sha2_type;
    always_comb begin 
        unique case (instruction_i[26:20])
            7'b000_0010: sha2_type = SIG0; // sha256sig0
            7'b000_0011: sha2_type = SIG1; // sha256sig1
            7'b000_0000: sha2_type = SUM0; // sha256sum0
            7'b000_0001: sha2_type = SUM1; // sha256sum1
            default: sha2_type = INVALID;
        endcase
    end

    iType_e brev_op;
    always_comb begin
        unique case (instruction_i[26:20])
            7'b000_0111: brev_op = ALU_BREV8;  // brev8: imm[6:0] = 0000111 (imm = 0x687)
            7'b001_1000: brev_op = ALU_REV8;   // rev8:  imm[6:0] = 0011000 (imm = 0x698)
            default:     brev_op = INVALID;
        endcase
    end

    iType_e decode_op_imm;
    always_comb begin
        unique case ({funct7, funct3}) inside
            10'b???????000:     decode_op_imm = ADD;    /* ADDI */
            10'b0000000001:     decode_op_imm = SLL;    /* SLLI */
            10'b???????010:     decode_op_imm = SLT;    /* SLTI */
            10'b???????011:     decode_op_imm = SLTU;   /* SLTIU */
            10'b???????100:     decode_op_imm = XOR;    /* XORI */
            10'b0000000101:     decode_op_imm = SRL;    /* SRLI */
            10'b0100000101:     decode_op_imm = SRA;    /* SRAI */
            10'b???????110:     decode_op_imm = OR;     /* ORI */
            10'b???????111:     decode_op_imm = AND;    /* ANDI */
            10'b0001000001:     decode_op_imm = (ZKNHEnable) ? sha2_type  : INVALID; 
            10'b01100??101:     decode_op_imm = (ZBKBEnable) ? ALU_ROR    : INVALID;  
            10'b0000100001:     decode_op_imm = (ZBKBEnable) ? ALU_ZIP    : INVALID;
            10'b01101??101:     decode_op_imm = (ZBKBEnable) ? brev_op    : INVALID;
            10'b00001??101:     decode_op_imm = (ZBKBEnable) ? ALU_UNZIP  : INVALID;
            default:            decode_op_imm = INVALID;
        endcase
    end

    iType_e decode_op;
    always_comb begin
        unique case ({funct7, funct3}) inside
            10'b0000000000:     decode_op = ADD;
            10'b0100000000:     decode_op = SUB;
            10'b0000000001:     decode_op = SLL;
            10'b0000000010:     decode_op = SLT;
            10'b0000000011:     decode_op = SLTU;
            10'b0000000100:     decode_op = XOR;
            10'b0000000101:     decode_op = SRL;
            10'b0100000101:     decode_op = SRA;
            10'b0000000110:     decode_op = OR;
            10'b0000000111:     decode_op = AND;
            10'b0000001000:     decode_op = (MULEXT != MUL_OFF) ? MUL    : INVALID;
            10'b0000001001:     decode_op = (MULEXT != MUL_OFF) ? MULH   : INVALID;
            10'b0000001010:     decode_op = (MULEXT != MUL_OFF) ? MULHSU : INVALID;
            10'b0000001011:     decode_op = (MULEXT != MUL_OFF) ? MULHU  : INVALID;
            10'b0000001100:     decode_op = (MULEXT == MUL_M  ) ? DIV    : INVALID;
            10'b0000001101:     decode_op = (MULEXT == MUL_M  ) ? DIVU   : INVALID;
            10'b0000001110:     decode_op = (MULEXT == MUL_M  ) ? REM    : INVALID;
            10'b0000001111:     decode_op = (MULEXT == MUL_M  ) ? REMU   : INVALID;
            10'b??10001000:     decode_op = ZKNEEnable   ? AES32ESI  : INVALID;
            10'b??10011000:     decode_op = ZKNEEnable   ? AES32ESMI : INVALID;
            10'b0000111101:     decode_op = ZICONDEnable ? CZERO_EQZ : INVALID;
            10'b0000111111:     decode_op = ZICONDEnable ? CZERO_NEZ : INVALID;

            10'b0101110000:     decode_op = ZKNHEnable   ? SIG0H : INVALID; //sha512sig0h 
            10'b0101010000:     decode_op = ZKNHEnable   ? SIG0L : INVALID; //sha512sig0l 
            10'b0101111000:     decode_op = ZKNHEnable   ? SIG1H : INVALID; //sha512sig1h
            10'b0101011000:     decode_op = ZKNHEnable   ? SIG1L : INVALID; //sha512sig1l
            10'b0101000000:     decode_op = ZKNHEnable   ? SUM0R : INVALID; //sha512sum0r
            10'b0101001000:     decode_op = ZKNHEnable   ? SUM1R : INVALID; //sha512sum1r
            // ZBKB ALU Operations
            10'b0110000001:     decode_op = (ZBKBEnable) ? ALU_ROL   : INVALID;
            10'b0110000101:     decode_op = (ZBKBEnable) ? ALU_ROR   : INVALID; 
            10'b0000100100:     decode_op = (ZBKBEnable) ? ALU_PACK  : INVALID;
            10'b0000100111:     decode_op = (ZBKBEnable) ? ALU_PACKH : INVALID; 
            10'b0100000100:     decode_op = (ZBKBEnable) ? ALU_XNOR  : INVALID;
            10'b0100000110:     decode_op = (ZBKBEnable) ? ALU_ORN   : INVALID;
            10'b0100000111:     decode_op = (ZBKBEnable) ? ALU_ANDN  : INVALID;
            default:            decode_op = INVALID;
        endcase
    end

    iType_e decode_xkyber;
    always_comb begin
        unique case (funct7)
          7'b0000000: decode_xkyber = KYBER_ADD;
          7'b0000001: decode_xkyber = KYBER_SUB;
          7'b0000010: decode_xkyber = KYBER_MUL;
          7'b0000011: decode_xkyber = KYBER_COMPRESS;
          7'b0000100: decode_xkyber = (instruction_i[24:20] == 5'd3) ? KYBER_CBD3 : KYBER_CBD2;
          default:    decode_xkyber = INVALID;
        endcase
    end

    iType_e decode_misc_mem;
    always_comb begin
        unique case (funct3)
            3'b000:     decode_misc_mem = NOP;  /* FENCE */
            default:    decode_misc_mem = INVALID;
        endcase
    end

    iType_e decode_system;
    always_comb begin
        unique case (instruction_i[31:7]) inside
            25'b0000000000000000000000000:  decode_system = ECALL;
            25'b0000000000010000000000000:  decode_system = EBREAK;
            25'b0001000000100000000000000:  decode_system = SRET;
            25'b0011000000100000000000000:  decode_system = MRET;
            25'b0001000001010000000000000:  decode_system = WFI;
            25'b?????????????????001?????:  decode_system = CSRRW;
            25'b?????????????????010?????:  decode_system = CSRRS;
            25'b?????????????????011?????:  decode_system = CSRRC;
            25'b?????????????????101?????:  decode_system = CSRRWI;
            25'b?????????????????110?????:  decode_system = CSRRSI;
            25'b?????????????????111?????:  decode_system = CSRRCI;
            default:                        decode_system = INVALID;
        endcase
    end

    logic         amo_invalid;
    iType_e       decode_atomic;
    iTypeAtomic_e amo_op_next;
    if (AMOEXT != AMO_OFF) begin : gen_amo_on
        always_comb begin
            unique case (funct7[6:2])
                5'b00010: decode_atomic = (AMOEXT != AMO_ZAAMO)  ? LR_W  : INVALID;
                5'b00011: decode_atomic = (AMOEXT != AMO_ZAAMO)  ? SC_W  : INVALID;
                default:  decode_atomic = (AMOEXT != AMO_ZALRSC) ? AMO_W : INVALID;
            endcase
        end

        if (AMOEXT != AMO_ZALRSC) begin : gen_zaamo_on
            iTypeAtomic_e decode_amo;
            always_comb begin
                unique case (funct7[6:2])
                    5'b00000: decode_amo = AMOADD;
                    5'b00001: decode_amo = AMOSWAP;
                    5'b00100: decode_amo = AMOXOR;
                    5'b01000: decode_amo = AMOOR;
                    5'b01100: decode_amo = AMOAND;
                    5'b10000: decode_amo = AMOMIN;
                    5'b10100: decode_amo = AMOMAX;
                    5'b11000: decode_amo = AMOMINU;
                    5'b11100: decode_amo = AMOMAXU;
                    default:  decode_amo = AMONOP;
                endcase
            end

            assign amo_invalid = (instruction_operation == AMO_W) && (decode_amo == AMONOP);
            assign amo_op_next = decode_amo;
        end
        else begin : gen_zaamo_off
            assign amo_invalid = 1'b0;
            assign amo_op_next = AMONOP;
        end
    end
    else begin : gen_amo_off
        assign decode_atomic = INVALID;
        assign amo_invalid   = 1'b0;
        assign amo_op_next   = AMONOP;
    end

    always_comb begin
        unique case (opcode)
            5'b01101: instruction_operation = LUI;
            5'b00101: instruction_operation = AUIPC;
            5'b11011: instruction_operation = JAL;
            5'b11001: instruction_operation = JALR;
            5'b11000: instruction_operation = decode_branch;              /* BRANCH */
            5'b00000: instruction_operation = decode_load;                /* LOAD */
            5'b01000: instruction_operation = decode_store;               /* STORE */
            5'b00100: instruction_operation = decode_op_imm;              /* OP-IMM */
            5'b01100: instruction_operation = decode_op;                  /* OP */
            5'b00011: instruction_operation = decode_misc_mem;            /* MISC-MEM */
            5'b11100: instruction_operation = decode_system;              /* SYSTEM */
            5'b10101: instruction_operation = VEnable ? VECTOR : INVALID; /* OP-V */
            5'b00001: instruction_operation = VEnable ? VLOAD  : INVALID; /* LOAD-FP */
            5'b01001: instruction_operation = VEnable ? VSTORE : INVALID; /* STORE-FP */
            5'b01011: instruction_operation = decode_atomic;
            5'b01010: instruction_operation = XKYBEREnable ? decode_xkyber : INVALID; 
            default:  instruction_operation = INVALID;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
//  Decode Vector Instruction
//////////////////////////////////////////////////////////////////////////////

    /* VNOP on an OP-V, LOAD-FP or STORE-FP opcode means the encoding is */
    /* reserved or not supported, and raises an illegal instruction.     */
    iTypeVector_e vector_operation;
    logic         vector_invalid;

    if (VEnable) begin : v_enable_decode_gen_on
        iTypeVector_e decode_vector_opcfg;
        iTypeVector_e decode_vector_opi;
        iTypeVector_e decode_vector_opm;
        iTypeVector_e decode_vector_arith;
        iTypeVector_e decode_vector_load;
        iTypeVector_e decode_vector_store;

        opCat_e     opCat;
        logic [5:0] funct6;
        logic       vm;
        logic [4:0] vd, vs1, vs2;
        logic       is_vv, is_vi;

        assign opCat  = opCat_e'(funct3);
        assign funct6 = funct7[6:1];
        assign vm     = funct7[0];
        assign vd     = instruction_i[11:7];
        assign vs1    = instruction_i[19:15];
        assign vs2    = instruction_i[24:20];
        assign is_vv  = (opCat == OPIVV);
        assign is_vi  = (opCat == OPIVI);

        ////////////////////////////////////////////////////////////////////////
        // Configuration
        ////////////////////////////////////////////////////////////////////////

        always_comb begin
            unique case (instruction_i[31:30]) inside
                2'b0?:      decode_vector_opcfg = VSETVLI;
                2'b11:      decode_vector_opcfg = VSETIVLI;
                /* vsetvl requires funct7 = 1000000 */
                2'b10:      decode_vector_opcfg = (instruction_i[29:25] == '0) ? VSETVL : VNOP;
                default:    decode_vector_opcfg = VNOP;
            endcase
        end

        ////////////////////////////////////////////////////////////////////////
        // OPIVV, OPIVX, OPIVI: each funct6 is only legal in the forms it has
        ////////////////////////////////////////////////////////////////////////

        /* vmv<nr>r.v: nr - 1 is in simm and must be 0, 1, 3 or 7 */
        logic vmvr_legal;
        assign vmvr_legal = is_vi && vm && (vs1 inside {5'd0, 5'd1, 5'd3, 5'd7})
                         && ((vd  & vs1) == '0) && ((vs2 & vs1) == '0);

        always_comb begin
            unique case (funct6) inside
                6'b000000:     decode_vector_opi = VADD;
                6'b000010:     decode_vector_opi = !is_vi ? VSUB  : VNOP;
                6'b000011:     decode_vector_opi = !is_vv ? VRSUB : VNOP;
                6'b000100:     decode_vector_opi = !is_vi ? VMINU : VNOP;
                6'b000101:     decode_vector_opi = !is_vi ? VMIN  : VNOP;
                6'b000110:     decode_vector_opi = !is_vi ? VMAXU : VNOP;
                6'b000111:     decode_vector_opi = !is_vi ? VMAX  : VNOP;
                6'b001001:     decode_vector_opi = VAND;
                6'b001010:     decode_vector_opi = VOR;
                6'b001011:     decode_vector_opi = VXOR;
                /* vmv.v.* (vm = 1) requires vs2 = 0; vmerge is the vm = 0 form */
                6'b010111:     decode_vector_opi = !vm ? VMERGE : ((vs2 == '0) ? VMV : VNOP);
                6'b011000:     decode_vector_opi = VMSEQ;
                6'b011001:     decode_vector_opi = VMSNE;
                6'b011010:     decode_vector_opi = !is_vi ? VMSLTU : VNOP;
                6'b011011:     decode_vector_opi = !is_vi ? VMSLT  : VNOP;
                6'b011100:     decode_vector_opi = VMSLEU;
                6'b011101:     decode_vector_opi = VMSLE;
                6'b011110:     decode_vector_opi = !is_vv ? VMSGTU : VNOP;
                6'b011111:     decode_vector_opi = !is_vv ? VMSGT  : VNOP;
                6'b100101:     decode_vector_opi = VSLL;
                /* .vi is vmv<nr>r; .vv and .vx are vsmul (P4) */
                6'b100111:     decode_vector_opi = vmvr_legal ? VMVR : VNOP;
                6'b101000:     decode_vector_opi = VSRL;
                6'b101001:     decode_vector_opi = VSRA;
                default:       decode_vector_opi = VNOP;
            endcase
        end

        ////////////////////////////////////////////////////////////////////////
        // OPMVV, OPMVX
        ////////////////////////////////////////////////////////////////////////

        logic is_mvv;
        assign is_mvv = (opCat == OPMVV);

        always_comb begin
            unique case (funct6) inside
                /* Reductions only exist as .vs (OPMVV) */
                6'b000000:     decode_vector_opm = is_mvv ? VREDSUM  : VNOP;
                6'b000001:     decode_vector_opm = is_mvv ? VREDAND  : VNOP;
                6'b000010:     decode_vector_opm = is_mvv ? VREDOR   : VNOP;
                6'b000011:     decode_vector_opm = is_mvv ? VREDXOR  : VNOP;
                6'b000100:     decode_vector_opm = is_mvv ? VREDMINU : VNOP;
                6'b000101:     decode_vector_opm = is_mvv ? VREDMIN  : VNOP;
                6'b000110:     decode_vector_opm = is_mvv ? VREDMAXU : VNOP;
                6'b000111:     decode_vector_opm = is_mvv ? VREDMAX  : VNOP;
                6'b001110:     decode_vector_opm = !is_mvv ? VSLIDE1UP   : VNOP;
                6'b001111:     decode_vector_opm = !is_mvv ? VSLIDE1DOWN : VNOP;
                /* OPMVV (VWXUNARY0) selects by vs1: vmv.x.s is 00000,  */
                /* vcpop and vfirst (P5) are 10000 and 10001.           */
                /* OPMVX (VRXUNARY0) is vmv.s.x, which requires vs2 = 0 */
                6'b010000:     decode_vector_opm = !vm                 ? VNOP
                                                 : !is_mvv             ? ((vs2 == '0) ? VMVSX : VNOP)
                                                 : (vs1 == '0)         ? VMVXS
                                                 :                       VNOP;
                6'b100000:     decode_vector_opm = VDIVU;
                6'b100001:     decode_vector_opm = VDIV;
                6'b100010:     decode_vector_opm = VREMU;
                6'b100011:     decode_vector_opm = VREM;
                6'b100100:     decode_vector_opm = VMULHU;
                6'b100101:     decode_vector_opm = VMUL;
                6'b100110:     decode_vector_opm = VMULHSU;
                6'b100111:     decode_vector_opm = VMULH;
                6'b101101:     decode_vector_opm = VMACC;
                6'b101111:     decode_vector_opm = VNMSAC;
                6'b101001:     decode_vector_opm = VMADD;
                6'b101011:     decode_vector_opm = VNMSUB;
                6'b111000:     decode_vector_opm = VWMULU;
                6'b111010:     decode_vector_opm = VWMULSU;
                6'b111011:     decode_vector_opm = VWMUL;
                default:       decode_vector_opm = VNOP;
            endcase
        end

        ////////////////////////////////////////////////////////////////////////
        // OP-V
        ////////////////////////////////////////////////////////////////////////

        iTypeVector_e decode_vector_opv;
        always_comb begin
            unique case (opCat) inside
                OPCFG:               decode_vector_opv = decode_vector_opcfg;
                OPIVV, OPIVX, OPIVI: decode_vector_opv = decode_vector_opi;
                OPMVV, OPMVX:        decode_vector_opv = decode_vector_opm;
                default:             decode_vector_opv = VNOP;
            endcase
        end

        /* A masked instruction cannot write v0, unless it writes a mask */
        /* (compares) or a scalar element (reductions).                  */
        logic writes_v0_masked;
        assign writes_v0_masked = (opCat != OPCFG) && !vm && (vd == '0)
                                && !(decode_vector_opv inside {VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE,
                                                               VMSGTU, VMSGT, VREDSUM, VREDAND, VREDOR, VREDXOR,
                                                               VREDMINU, VREDMIN, VREDMAXU, VREDMAX});

        assign decode_vector_arith = writes_v0_masked ? VNOP : decode_vector_opv;

        ////////////////////////////////////////////////////////////////////////
        // LOAD-FP and STORE-FP
        ////////////////////////////////////////////////////////////////////////

        logic [2:0] nf;
        logic       mew;
        logic [1:0] mop;
        logic [4:0] lumop;
        logic       eew_legal;
        logic       whole_reg_legal;
        logic       mem_legal;

        assign nf    = instruction_i[31:29];
        assign mew   = instruction_i[28];
        assign mop   = instruction_i[27:26];
        assign lumop = instruction_i[24:20];

        /* EEW 8, 16 and 32. Widths 001-100 are scalar FP (no F/D), 111 is EEW = 64 */
        assign eew_legal = (funct3 inside {3'b000, 3'b101, 3'b110}) && !mew;

        /* NFIELDS = nf + 1 must be 1, 2, 4 or 8, and vd a multiple of it */
        assign whole_reg_legal = vm && (nf inside {3'd0, 3'd1, 3'd3, 3'd7}) && ((vd[2:0] & nf) == '0);

        always_comb begin
            if (!eew_legal)
                mem_legal = 1'b0;
            else if (mop == 2'b00) begin
                unique case (lumop)
                    /* Segments (nf != 0) are P8 */
                    5'b00000:   mem_legal = (nf == '0);
                    5'b01000:   mem_legal = whole_reg_legal;
                    /* vlm.v and vsm.v are encoded with EEW = 8 */
                    5'b01011:   mem_legal = vm && (nf == '0) && (funct3 == 3'b000);
                    /* Fault-only-first (10000) is P8 */
                    default:    mem_legal = 1'b0;
                endcase
            end
            else begin
                /* Strided and indexed segments are P8 */
                mem_legal = (nf == '0);
            end
        end

        /* Whole register stores are encoded with EEW = 8 and there is no fault-only-first store */
        logic store_legal;
        assign store_legal = mem_legal && !(mop == 2'b00 && lumop == 5'b01000 && funct3 != 3'b000);

        /* A masked load cannot write v0 */
        assign decode_vector_load  = (mem_legal && !(!vm && vd == '0)) ? VLD : VNOP;
        assign decode_vector_store = store_legal                       ? VST : VNOP;

        always_comb begin
            unique case (instruction_operation)
                VECTOR:  vector_operation = decode_vector_arith;
                VLOAD:   vector_operation = decode_vector_load;
                VSTORE:  vector_operation = decode_vector_store;
                default: vector_operation = VNOP;
            endcase
        end

        assign vector_invalid = (instruction_operation inside {VECTOR, VLOAD, VSTORE}) && (vector_operation == VNOP);

    end
    else begin : v_enable_decode_gen_off
        assign vector_operation = VNOP;
        assign vector_invalid   = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
//  Decodes the instruction format
//////////////////////////////////////////////////////////////////////////////

    formatType_e instruction_format;
    always_comb begin
        unique case (opcode)
            5'b11001, 5'b00000, 5'b00100:   instruction_format = I_TYPE;        /* JALR, LOAD, OP-IMM */
            5'b01000:                       instruction_format = S_TYPE;        /* STORE */
            5'b11000:                       instruction_format = B_TYPE;        /* BRANCH */
            5'b01101, 5'b00101:             instruction_format = U_TYPE;        /* LUI, AUIPC */
            5'b11011:                       instruction_format = J_TYPE;        /* JAL */
            default:                        instruction_format = R_TYPE;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Extract the immediate based on instruction format
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] imm_i;
    logic [31:0] imm_s;
    logic [31:0] imm_b;
    logic [31:0] imm_u;
    logic [31:0] imm_j;

    assign imm_i = {{21{instruction_i[31]}}, instruction_i[30:20]};
    assign imm_s = {{21{instruction_i[31]}}, instruction_i[30:25], instruction_i[11:7]};
    assign imm_b = {{20{instruction_i[31]}}, instruction_i[7], instruction_i[30:25], instruction_i[11:8], 1'b0};
    assign imm_u = {instruction_i[31:12], 12'b0};
    assign imm_j = {{12{instruction_i[31]}}, instruction_i[19:12], instruction_i[20], instruction_i[30:25], instruction_i[24:21], 1'b0};

    logic [31:0] immediate;
    always_comb begin
        unique case (instruction_format)
            I_TYPE:     immediate = imm_i;
            S_TYPE:     immediate = imm_s;
            B_TYPE:     immediate = imm_b;
            U_TYPE:     immediate = imm_u;
            J_TYPE:     immediate = imm_j;
            default:    immediate = '0;    /* R_TYPE */
        endcase
    end

////////////////////////////////////////////////////////////////////////////////
// Branch Prediction
////////////////////////////////////////////////////////////////////////////////

    logic jump_confirmed;
    
    /* We add this adder here regardless of using BP or not */
    /* Because if we don't add here, we have to add in exec */
    assign bp_target_o = pc_i + immediate;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            jump_imm_target_o <= '0;
        else if (enable)
            jump_imm_target_o <= bp_target_o;
    end

    if (BRANCHPRED) begin : gen_bp_on
        logic bp_branch_taken;
        logic bp_jump_taken;

        /* We really can't add jalr here */
        assign bp_branch_taken = (opcode == 5'b11000 && imm_b[31]);
        assign bp_jump_taken   = (opcode == 5'b11011);

        assign bp_take_o   = (bp_jump_taken || bp_branch_taken) && !ctrl_i.jumping && !killed;

        assign jump_confirmed = should_jump_i || (ctrl_i.jumping && !jump_rollback_i);
    end
    else begin : gen_bp_off
        assign bp_take_o   = 1'b0;
        assign jump_confirmed = should_jump_i || ctrl_i.jumping;
    end

//////////////////////////////////////////////////////////////////////////////
// Registe Lock Queue (RLQ)
//////////////////////////////////////////////////////////////////////////////

    logic is_load;
    assign is_load  = (opcode == 5'b00000) || (instruction_operation == LR_W);

    logic is_store;
    assign is_store = (opcode == 5'b01000) || (instruction_operation inside {SC_W, AMO_W});

    logic           locked_memory;

    logic  [4:0]    locked_register;
    logic  [4:0]    locked_register_r;
    logic  [4:0]    rd;

    assign rd = instruction_i[11:7];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            locked_register <= '0;
        end
        else if (enable) begin
            if (hazard || killed)
                locked_register <= '0;
            else    // Read-after-write on LOAD
                locked_register <= (is_load || !FORWARDING) ? rd : '0;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            locked_register_r <= '0;
        else if (enable)
            locked_register_r <= locked_register;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            locked_memory   <= '0;
        end
        else if (enable) begin
            if (hazard || killed)
                locked_memory <= '0;
            else    // Read-after-write on STORE
                locked_memory <= is_store;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rd_o <= '0;
        else if (enable)
            rd_o <= rd;
    end

//////////////////////////////////////////////////////////////////////////////
// Addresses to RegBank
//////////////////////////////////////////////////////////////////////////////

    assign rs1_o = instruction_i[19:15];
    assign rs2_o = instruction_i[24:20];

    logic [11:0] csr_address;
    assign csr_address = instruction_i[31:20];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            csr_address_o <= '0;
        else if (enable)
            csr_address_o <= csr_address;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instr_rs1_o <= '0;
        else if (enable)
            instr_rs1_o <= rs1_o;
    end

//////////////////////////////////////////////////////////////////////////////
// Hazard signal generation
//////////////////////////////////////////////////////////////////////////////
    
    logic exception;

    logic use_rs1;
    logic use_rs2;

    logic locked_rs1;
    logic locked_rs2;

    logic hazard_mem;
    logic hazard_rs1;
    logic hazard_rs2;

    always_comb begin
        unique case (instruction_format)
            R_TYPE, B_TYPE, S_TYPE:
            /**
             * This does NOT account for SYSTEM (R_TYPE) CSRR_I instructions
             * where funct3[2] is 1, and therefore WILL generate a hazard
             * but this is rare to occur
             */
                        begin
                            use_rs1         = 1'b1;
                            use_rs2         = 1'b1;
                        end
            I_TYPE:     begin
                            use_rs1         = 1'b1;
                            use_rs2         = 1'b0;
                        end
            default:    begin /* U_TYPE and J_TYPE */
                            use_rs1         = 1'b0;
                            use_rs2         = 1'b0;
                        end
        endcase
    end

    /* I don't know why we should have this hazard                  */
    /* But removing this breaks the processor                       */
    /* It also breaks if we limit the hazard to same address access */
    assign hazard_mem = locked_memory && is_load;

    assign locked_rs1 = (locked_register != '0 && locked_register == rs1_o) || (locked_register_r != '0 && locked_register_r == rs1_o);
    assign locked_rs2 = (locked_register != '0 && locked_register == rs2_o) || (locked_register_r != '0 && locked_register_r == rs2_o);

    assign hazard_rs1 = locked_rs1 && use_rs1;
    assign hazard_rs2 = locked_rs2 && use_rs2;

    logic invalid;
    assign invalid      = jump_confirmed || ctrl_i.jump_misaligned || !ctrl_i.valid;
    assign killed       = invalid || exception;
    assign hazard       = (hazard_mem || hazard_rs1 || hazard_rs2) && !killed;
    assign dec_hazard_o = hazard;


//////////////////////////////////////////////////////////////////////////////
// Exception Detection
//////////////////////////////////////////////////////////////////////////////

    logic invalid_inst;
    assign invalid_inst = ((instruction_i[1:0] != '1) || instruction_operation == INVALID || amo_invalid || vector_invalid) && !invalid;

    logic exc_inst_access_fault;
    assign exc_inst_access_fault = ctrl_i.inst_fault && !invalid;

    assign exception = exc_inst_access_fault || invalid_inst;


//////////////////////////////////////////////////////////////////////////////
// Control of the operands based on format
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] rs1_data;
    logic [31:0] rs2_data;

    if (FORWARDING) begin : gen_forwarding_on
        always_comb begin
            if (rs1_o == rd_o && execute_we_i)  // Forwarding from execute
                rs1_data = result_i;
            else if (rs1_o == rd_mem_access_i && mem_access_we_i) // Forwarding from mem access
                rs1_data = mem_access_result_i;
            else if (rs1_o == rd_retire_i && regbank_we_i)  // Forwarding from retire on LOAD
                rs1_data = writeback_i;
            else
                rs1_data = rs1_data_read_i;
        end

        always_comb begin
            if (rs2_o == rd_o && execute_we_i)  // Forwarding from execute
                rs2_data = result_i;
            else if (rs2_o == rd_mem_access_i && mem_access_we_i) // Forwarding from mem access
                rs2_data = mem_access_result_i;
            else if (rs2_o == rd_retire_i && regbank_we_i)  // Forwarding from retire on LOAD
                rs2_data = writeback_i;
            else
                rs2_data = rs2_data_read_i;
        end
    end
    else begin : gen_forwarding_off
        always_comb begin
            if (rs1_o == rd_retire_i && regbank_we_i)  // Forwarding from retire on LOAD
                rs1_data = writeback_i;
            else
                rs1_data = rs1_data_read_i;
        end

        always_comb begin
            if (rs2_o == rd_retire_i && regbank_we_i)  // Forwarding from retire on LOAD
                rs2_data = writeback_i;
            else
                rs2_data = rs2_data_read_i;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rs1_data_o <= '0;
        else if (enable)
            rs1_data_o <= rs1_data;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rs2_data_o <= '0;
        else if (enable)
            rs2_data_o <= rs2_data;
    end

    logic [31:0] second_operand;
    always_comb begin
        unique case (instruction_format)
            I_TYPE,
            S_TYPE,
            U_TYPE:  second_operand = immediate;
            default: second_operand =  rs2_data;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            second_operand_o <= '0;
        else if (enable)
            second_operand_o <= second_operand;
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs to execution unit
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc_o <= '0;
        else if (enable)
            pc_o <= pc_i;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            instruction_o <= '0;
        else if (enable)
            instruction_o <= (!COMPRESSED && ctrl_i.compressed) ? {16'h0000, instruction_i[15:0]} : instruction_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Control struct combinational decode
//////////////////////////////////////////////////////////////////////////////

    exec_ctrl_t ctrl;

    always_comb begin
        ctrl = '0;

        ctrl.is_nop          = instruction_operation == NOP;
        ctrl.is_add          = instruction_operation == ADD;

        // Result select
        ctrl.is_csr          = instruction_operation inside {CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI};
        ctrl.is_jal_jalr     = instruction_operation inside {JAL, JALR};
        ctrl.is_jalr         = instruction_operation == JALR;
        ctrl.is_lui          = instruction_operation == LUI;
        ctrl.is_auipc        = instruction_operation == AUIPC;
        ctrl.is_slt          = instruction_operation == SLT;
        ctrl.is_sltu         = instruction_operation == SLTU;
        ctrl.is_xor          = instruction_operation == XOR;
        ctrl.is_or           = instruction_operation == OR;
        ctrl.is_and          = instruction_operation == AND;
        ctrl.is_sll          = instruction_operation == SLL;
        ctrl.is_srl          = instruction_operation == SRL;
        ctrl.is_sra          = instruction_operation == SRA;
        ctrl.is_sub          = instruction_operation == SUB;
        ctrl.is_mul          = (MULEXT != MUL_OFF) && instruction_operation inside {MUL, MULH, MULHU, MULHSU};
        ctrl.mul_low         = (MULEXT != MUL_OFF) && instruction_operation == MUL;
        ctrl.mul_signed_mode = (MULEXT != MUL_OFF) && instruction_operation == MULH   ? 2'b11 :
                               (MULEXT != MUL_OFF) && instruction_operation == MULHSU ? 2'b01 : 2'b00;
        ctrl.is_div          = (MULEXT == MUL_M)   && instruction_operation inside {DIV, DIVU};
        ctrl.is_rem          = (MULEXT == MUL_M)   && instruction_operation inside {REM, REMU};
        ctrl.div_signed      = (MULEXT == MUL_M)   && instruction_operation inside {DIV, REM};
        ctrl.is_aes          = ZKNEEnable   && instruction_operation inside {AES32ESI, AES32ESMI};
        ctrl.aes_is_mix      = ZKNEEnable   && instruction_operation == AES32ESMI;
        ctrl.is_vector       = VEnable      && instruction_operation inside {VECTOR, VLOAD, VSTORE};
        ctrl.is_vector_mem   = VEnable      && instruction_operation inside {VLOAD, VSTORE};
        ctrl.is_zicond       = ZICONDEnable && instruction_operation inside {CZERO_EQZ, CZERO_NEZ};
        ctrl.zicond_is_eqz   = ZICONDEnable && instruction_operation == CZERO_EQZ;
        ctrl.is_sha2         = ZKNHEnable   && instruction_operation inside {SIG0, SIG1, SUM0, SUM1, SIG0H, SIG0L,
                                                                             SIG1H, SIG1L, SUM0R, SUM1R};
        ctrl.is_zbkb         = ZBKBEnable   && instruction_operation inside {ALU_ROR, ALU_ROL, ALU_PACK, ALU_PACKH,
                                                                             ALU_XNOR, ALU_ORN, ALU_ANDN, ALU_ZIP,
                                                                             ALU_UNZIP, ALU_BREV8, ALU_REV8};
        ctrl.is_kyber        = XKYBEREnable && instruction_operation inside {KYBER_ADD, KYBER_SUB, KYBER_CBD2,
                                                                             KYBER_CBD3, KYBER_MUL, KYBER_COMPRESS};
        ctrl.is_sc           = (AMOEXT inside {AMO_ZALRSC, AMO_A}) && instruction_operation == SC_W;

        // Memory
        ctrl.is_load         = instruction_operation inside {LB, LBU, LH, LHU, LW};
        ctrl.is_store        = instruction_operation inside {SB, SH, SW};
        ctrl.is_lr           = (AMOEXT inside {AMO_ZALRSC, AMO_A}) && instruction_operation == LR_W;
        ctrl.is_amo          = (AMOEXT inside {AMO_ZAAMO,  AMO_A}) && instruction_operation == AMO_W;
        ctrl.is_amo_w        = (AMOEXT != AMO_OFF)                 && instruction_operation inside {AMO_W, SC_W, LR_W};

        // Memory width/sign
        ctrl.is_byte         = instruction_operation inside {LB, LBU, SB};
        ctrl.is_half         = instruction_operation inside {LH, LHU, SH};
        ctrl.is_unsigned     = instruction_operation inside {LBU, LHU};

        // Branch
        ctrl.is_beq          = instruction_operation == BEQ;
        ctrl.is_bne          = instruction_operation == BNE;
        ctrl.is_blt          = instruction_operation == BLT;
        ctrl.is_bltu         = instruction_operation == BLTU;
        ctrl.is_bge          = instruction_operation == BGE;
        ctrl.is_bgeu         = instruction_operation == BGEU;

        // Write-back suppress (instructions that never write rd)
        ctrl.rd_we           = !(instruction_operation inside {NOP, SB, SH, SW,
                                                           BEQ, BNE, BLT, BLTU, BGE, BGEU});

        // Opcode-derived system/exception flags
        ctrl.is_ecall        = instruction_operation == ECALL;
        ctrl.is_ebreak       = instruction_operation == EBREAK;
        ctrl.is_mret         = instruction_operation == MRET;
        ctrl.is_sret         = instruction_operation == SRET;
        ctrl.is_wfi          = instruction_operation == WFI;

        // CSR operation type
        unique case (instruction_operation)
            CSRRW, CSRRWI: ctrl.csr_op = WRITE;
            CSRRS, CSRRSI: ctrl.csr_op = SET;
            CSRRC, CSRRCI: ctrl.csr_op = CLEAR;
            default:       ctrl.csr_op = NONE;
        endcase

        ctrl.csr_rd_uses_rs1 = instruction_operation inside {CSRRW, CSRRS, CSRRC};
        ctrl.csr_wr_uses_rs1 = instruction_operation inside {CSRRS, CSRRC, CSRRSI, CSRRCI};

        // Zbkb sub-op
        unique case (instruction_operation)
            ALU_ROR:   ctrl.zbkb_op = ZBKBROR;
            ALU_ROL:   ctrl.zbkb_op = ZBKBROL;
            ALU_PACK:  ctrl.zbkb_op = ZBKBPACK;
            ALU_PACKH: ctrl.zbkb_op = ZBKBPACKH;
            ALU_XNOR:  ctrl.zbkb_op = ZBKBXNOR;
            ALU_ORN:   ctrl.zbkb_op = ZBKBORN;
            ALU_ANDN:  ctrl.zbkb_op = ZBKBANDN;
            ALU_ZIP:   ctrl.zbkb_op = ZBKBZIP;
            ALU_UNZIP: ctrl.zbkb_op = ZBKBUNZIP;
            ALU_BREV8: ctrl.zbkb_op = ZBKBBREV8;
            ALU_REV8:  ctrl.zbkb_op = ZBKBREV8;
            default:   ctrl.zbkb_op = ZBKBNOP;
        endcase

        ctrl.amo_op          = amo_op_next;
        ctrl.vector_op       = vector_operation;

        // SHA2 sub-op
        unique case (instruction_operation)
            SIG0:    ctrl.sha2_op = SHA2SIG0;
            SIG1:    ctrl.sha2_op = SHA2SIG1;
            SUM0:    ctrl.sha2_op = SHA2SUM0;
            SUM1:    ctrl.sha2_op = SHA2SUM1;
            SIG0H:   ctrl.sha2_op = SHA2SIG0H;
            SIG0L:   ctrl.sha2_op = SHA2SIG0L;
            SIG1H:   ctrl.sha2_op = SHA2SIG1H;
            SIG1L:   ctrl.sha2_op = SHA2SIG1L;
            SUM0R:   ctrl.sha2_op = SHA2SUM0R;
            SUM1R:   ctrl.sha2_op = SHA2SUM1R;
            default: ctrl.sha2_op = SHA2NOP;
        endcase

        // Kyber sub-op
        unique case (instruction_operation)
            KYBER_ADD:      ctrl.kyber_op = KYBADD;
            KYBER_SUB:      ctrl.kyber_op = KYBSUB;
            KYBER_CBD2:     ctrl.kyber_op = KYBCBD2;
            KYBER_CBD3:     ctrl.kyber_op = KYBCBD3;
            KYBER_MUL:      ctrl.kyber_op = KYBMUL;
            KYBER_COMPRESS: ctrl.kyber_op = KYBCOMPRESS;
            default:        ctrl.kyber_op = KYBNOP;
        endcase

        // Pipeline status fields
        ctrl.compressed            = ctrl_i.compressed;
        ctrl.bp_taken              = bp_take_o;
        ctrl.exc_ilegal_inst       = invalid_inst;
        ctrl.exc_inst_access_fault = exc_inst_access_fault;
        ctrl.exc_inst_fault_upper  = ctrl_i.inst_fault_upper;
        ctrl.hazard                = hazard;
        ctrl.killed                = killed;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            ctrl_o <= '0;
        else if (sys_reset)
            ctrl_o <= '0;
        else if (enable) begin
            if (hazard || killed) begin
                ctrl_o        <= '0;
                /* A bubble behaves as a NOP (e.g. for instruction counters) */
                ctrl_o.is_nop <= 1'b1;
                ctrl_o.hazard <= hazard;
                ctrl_o.killed <= killed;
                /* An excepting instruction is killed (turned into a NOP) */
                /* but its exception must still reach execute             */
                ctrl_o.exc_ilegal_inst       <= invalid_inst;
                ctrl_o.exc_inst_access_fault <= exc_inst_access_fault;
                ctrl_o.exc_inst_fault_upper  <= ctrl_i.inst_fault_upper;
            end
            else
                ctrl_o <= ctrl;
        end
    end

endmodule
