/*!\file decode.sv
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
    parameter mul_e         MULEXT      = MUL_M,
    parameter atomic_e      AMOEXT      = AMO_A,
    parameter bit           COMPRESSED  = 1'b1,
    parameter bit           ZKNEEnable  = 1'b0,
    parameter bit           VEnable     = 1'b0,
    parameter bit           BRANCHPRED  = 1'b1
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           enable,

    input   logic [31:0]    instruction_i,
    input   logic [31:0]    pc_i,
    input   logic [31:0]    rs1_data_read_i,
    input   logic [31:0]    rs2_data_read_i,
    input   logic [31:0]    writeback_i,
    input   logic [31:0]    result_i, 
    input   logic [ 4:0]    rd_retire_i,
    input   logic           regbank_we_i,
    input   logic           execute_we_i,
    input   logic           rollback_i,
    input   logic           compressed_i,

    output  logic  [4:0]    rs1_o,
    output  logic  [4:0]    rs2_o,
    output  logic  [4:0]    rd_o,
    output  logic  [4:0]    instr_rs1_o,
    output  logic [11:0]    csr_address_o,
    output  logic [31:0]    rs1_data_o,
    output  logic [31:0]    rs2_data_o,
    output  logic [31:0]    second_operand_o,
    output  logic [31:0]    pc_o,
    output  logic [31:0]    instruction_o,
    output  logic [31:0]    jump_imm_target_o,
    output  logic           compressed_o,
    output  iType_e         instruction_operation_o,
    output  iTypeAtomic_e   atomic_operation_o,
    output  iTypeVector_e   vector_operation_o,
    output  logic           hazard_o,
    output  logic           killed_o,

    /* Not used without BP */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           jump_rollback_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input   logic           ctx_switch_i,
    input   logic           jumping_i,
    /* Not used without C */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           jump_misaligned_i,
    /* verilator lint_off UNUSEDSIGNAL */
    output  logic           bp_take_o,
    output  logic           bp_taken_o,
    output  logic [31:0]    bp_target_o,

    input   logic           exc_inst_access_fault_i,
    output  logic           exc_inst_access_fault_o,
    output  logic           exc_ilegal_inst_o,
    output  logic           exc_misaligned_fetch_o
);

//////////////////////////////////////////////////////////////////////////////
// Find out the type of the instruction
//////////////////////////////////////////////////////////////////////////////

    logic   killed;
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
            10'b??10001000:     decode_op = ZKNEEnable ? AES32ESI  : INVALID;
            10'b??10011000:     decode_op = ZKNEEnable ? AES32ESMI : INVALID;
            default:            decode_op = INVALID;
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

            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n)
                    atomic_operation_o <= AMONOP;
                else if (enable)
                    atomic_operation_o <= decode_amo;
            end
        end
        else begin : gen_zaamo_off
            assign amo_invalid        = 1'b0;
            assign atomic_operation_o = AMONOP;
        end
    end
    else begin : gen_amo_off
        assign decode_atomic      = INVALID;
        assign amo_invalid        = 1'b0;
        assign atomic_operation_o = AMONOP;
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
            default:  instruction_operation = INVALID;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
//  Decode Vector Instruction
//////////////////////////////////////////////////////////////////////////////

    iTypeVector_e vector_operation;

    if (VEnable) begin : v_enable_decode_gen_on
        iTypeVector_e decode_vector_opcfg;
        iTypeVector_e decode_vector_opi;
        iTypeVector_e decode_vector_opm;

        opCat_e opCat;

        assign opCat = opCat_e'(funct3);

        always_comb begin
            unique case (instruction_i[31:30]) inside
                2'b0?:      decode_vector_opcfg = VSETVLI;
                2'b11:      decode_vector_opcfg = VSETIVLI;
                2'b10:      decode_vector_opcfg = VSETVL;
                default:    decode_vector_opcfg = VNOP;
            endcase
        end

        always_comb begin
            unique case (funct7[6:1]) inside
                6'b000000:     decode_vector_opi = VADD;
                6'b000010:     decode_vector_opi = VSUB;
                6'b000011:     decode_vector_opi = VRSUB;
                6'b000100:     decode_vector_opi = VMINU;
                6'b000101:     decode_vector_opi = VMIN;
                6'b000110:     decode_vector_opi = VMAXU;
                6'b000111:     decode_vector_opi = VMAX;
                6'b001001:     decode_vector_opi = VAND;
                6'b001010:     decode_vector_opi = VOR;
                6'b001011:     decode_vector_opi = VXOR;
                6'b010111:     decode_vector_opi = (funct7[0]) ? VMV : VMERGE;
                6'b011000:     decode_vector_opi = VMSEQ;
                6'b011001:     decode_vector_opi = VMSNE;
                6'b011010:     decode_vector_opi = VMSLTU;
                6'b011011:     decode_vector_opi = VMSLT;
                6'b011100:     decode_vector_opi = VMSLEU;
                6'b011101:     decode_vector_opi = VMSLE;
                6'b011110:     decode_vector_opi = VMSGTU;
                6'b011111:     decode_vector_opi = VMSGT;
                6'b100101:     decode_vector_opi = VSLL;
                6'b100111:     decode_vector_opi = VMVR;
                6'b101000:     decode_vector_opi = VSRL;
                6'b101001:     decode_vector_opi = VSRA;
                default:       decode_vector_opi = VNOP;
            endcase
        end

        always_comb begin
            unique case (funct7[6:1]) inside
                6'b000000:     decode_vector_opm = VREDSUM;
                6'b000001:     decode_vector_opm = VREDAND;
                6'b000010:     decode_vector_opm = VREDOR;
                6'b000011:     decode_vector_opm = VREDXOR;
                6'b000100:     decode_vector_opm = VREDMINU;
                6'b000101:     decode_vector_opm = VREDMIN;
                6'b000110:     decode_vector_opm = VREDMAXU;
                6'b000111:     decode_vector_opm = VREDMAX;
                6'b010000:     decode_vector_opm = (rs2_o == '0)
                                                ? VMVSX
                                                : VMVXS;
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

        always_comb begin
            if (instruction_operation == VECTOR) begin
                unique case (opCat) inside
                    OPCFG:               vector_operation = decode_vector_opcfg;
                    OPIVV, OPIVX, OPIVI: vector_operation = decode_vector_opi;
                    OPMVV, OPMVX:        vector_operation = decode_vector_opm;
                    default:             vector_operation = VNOP;
                endcase
            end
            else begin
                vector_operation = VNOP;
            end
        end

        always_ff @(posedge clk)
            if (instruction_operation == VECTOR && vector_operation == VNOP)
                $display("INVALID VECTOR INST!!!");

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                vector_operation_o <= VNOP;
            end
            else if (enable) begin
                if (hazard_o || killed)
                    vector_operation_o <= VNOP;
                else
                    vector_operation_o <= vector_operation;
            end
        end
    end
    else begin : v_enable_decode_gen_on
        assign vector_operation = VNOP;
        assign vector_operation_o = VNOP;
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

        assign bp_take_o   = (bp_jump_taken || bp_branch_taken) && !jumping_i && !killed;

        assign jump_confirmed = ctx_switch_i || (jumping_i && !jump_rollback_i);
        
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                bp_taken_o <= 1'b0;
            else if (enable && !hazard_o)
                bp_taken_o <= bp_take_o;
        end
    end
    else begin : gen_bp_off
        assign bp_take_o   = 1'b0;
        assign bp_taken_o  = 1'b0;
        assign jump_confirmed = ctx_switch_i || jumping_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Registe Lock Queue (RLQ)
//////////////////////////////////////////////////////////////////////////////

    logic is_load;
    logic is_store;
    logic forwardingless;

    assign is_load  = (opcode == 5'b00000) || (instruction_operation == LR_W);
    assign is_store = (opcode == 5'b01000) || (instruction_operation inside {SC_W, AMO_W});
    assign forwardingless = (instruction_operation inside {SC_W});
    
    logic           locked_memory;
    logic  [4:0]    locked_register;
    logic  [4:0]    rd;

    assign rd = instruction_i[11:7];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            locked_register <= '0;
        end
        else if (enable) begin
            if (hazard_o || killed)
                locked_register <= '0;
            else    // Read-after-write on LOAD
                locked_register <= (is_load || forwardingless) ? rd : '0;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            locked_memory <= '0;
        end
        else if (enable) begin
            if (hazard_o || killed) 
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

    assign locked_rs1 = (locked_register != '0 && locked_register == rs1_o);
    assign locked_rs2 = (locked_register != '0 && locked_register == rs2_o);

    /* I don't know why we should have this hazard                  */
    /* But removing this breaks the processor                       */
    /* It also breaks if we limit the hazard to same address access */
    assign hazard_mem = locked_memory   && is_load;

    assign hazard_rs1 = locked_rs1      && use_rs1;
    assign hazard_rs2 = locked_rs2      && use_rs2;

    assign killed   = jump_confirmed || jump_misaligned_i || rollback_i;
    assign hazard_o = (hazard_mem || hazard_rs1 || hazard_rs2) && !killed && !exception;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            killed_o <= 1'b0;
        else if (enable)
            killed_o <= killed;
    end

//////////////////////////////////////////////////////////////////////////////
// Exception Detection
//////////////////////////////////////////////////////////////////////////////

    logic invalid_inst;
    logic misaligned_fetch;
    logic exc_inst_access_fault;

    assign invalid_inst = ((instruction_i[1:0] != '1) || instruction_operation == INVALID || amo_invalid);

    if (COMPRESSED) begin : gen_compressed_on
        assign misaligned_fetch = (pc_i[0] != 1'b0);
    end
    else begin : gen_compressed_off
        assign misaligned_fetch = (pc_i[1:0] != 2'b00);
    end

    assign exc_inst_access_fault = exc_inst_access_fault_i;

    assign exception = exc_inst_access_fault || invalid_inst || misaligned_fetch;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            exc_ilegal_inst_o <= 1'b0;
        else if (enable)
            exc_ilegal_inst_o <= invalid_inst;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            exc_misaligned_fetch_o <= 1'b0;
        else if (enable)
            exc_misaligned_fetch_o <= misaligned_fetch;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            exc_inst_access_fault_o <= 1'b0;
        else if (enable)
            exc_inst_access_fault_o <= exc_inst_access_fault;
    end

//////////////////////////////////////////////////////////////////////////////
// Control of the operands based on format
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] rs1_data;
    logic [31:0] rs2_data;

    always_comb begin
        if (rs1_o == rd_o && execute_we_i)  // Forwarding from execute
            rs1_data = result_i;
        else if (rs1_o == rd_retire_i && regbank_we_i)  // Forwarding from retire on LOAD
            rs1_data = writeback_i;
        else
            rs1_data = rs1_data_read_i;
    end

    always_comb begin
        if (rs2_o == rd_o && execute_we_i)  // Forwarding from execute
            rs2_data = result_i;
        else if (rs2_o == rd_retire_i && regbank_we_i)  // Forwarding from retire on LOAD
            rs2_data = writeback_i;
        else
            rs2_data = rs2_data_read_i;
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
// Outputs do execution unit
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
            instruction_o <= instruction_i;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            compressed_o <= 1'b0;
        else if (enable)
            compressed_o <= compressed_i;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_operation_o <= NOP;
        end
        else if (enable) begin
            if (hazard_o || killed)
                instruction_operation_o <= NOP;
            else
                instruction_operation_o <= instruction_operation;
        end
    end

endmodule
