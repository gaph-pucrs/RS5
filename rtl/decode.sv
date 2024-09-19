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
    parameter bit           ZKNEEnable  = 1'b0,
    parameter bit           VEnable     = 1'b0,
    parameter atomic_ext_e  AEnable     = OFF,
    parameter bit           COMPRESSED  = 1'b0
)
(
    input   logic           clk,
    input   logic           reset_n,
    input   logic           enable,

    input   logic [31:0]    instruction_i,
    input   logic [31:0]    pc_i,
    input   logic  [2:0]    tag_i,
    input   logic [31:0]    rs1_data_read_i,
    input   logic [31:0]    rs2_data_read_i,
    input   logic           compressed_i,
    input   logic           jumped_i,

    output  logic  [4:0]    rs1_o,
    output  logic  [4:0]    rs2_o,
    output  logic  [4:0]    rd_o,
    output  logic [31:0]    first_operand_o,
    output  logic [31:0]    second_operand_o,
    output  logic [31:0]    third_operand_o,
    output  logic [31:0]    pc_o,
    output  logic [31:0]    instruction_o,
    output  logic           compressed_o,
    output  logic  [2:0]    tag_o,
    output  iType_e         instruction_operation_o,
    output  iTypeVector_e   vector_operation_o,
    output  iTypeAtomic_e   atomic_operation_o,
    output  logic           hazard_o,

    input   logic           exc_inst_access_fault_i,
    output  logic           exc_inst_access_fault_o,
    output  logic           exc_ilegal_inst_o,
    output  logic           exc_misaligned_fetch_o
);

    logic [31:0]    first_operand, second_operand, third_operand, immediate;
    logic [31:0]    instruction;
    logic [31:0]    last_instruction;
    logic           last_hazard;
    logic           last_stall;
    logic           locked_memory;
    logic  [4:0]    locked_register;

    formatType_e    instruction_format;
    iType_e         instruction_operation;


//////////////////////////////////////////////////////////////////////////////
// Re-Decode isntruction on hazard or stall
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            last_instruction <= 32'h00000013;
        else
            last_instruction <= instruction;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            last_hazard <= 1'b1;
        else
            last_hazard <= hazard_o;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            last_stall <= 1'b1;
        else
            last_stall <= !enable;
    end

    always_comb begin
        if ((last_hazard || last_stall)) begin
            instruction = last_instruction;
        end
        else begin
            instruction = instruction_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Find out the type of the instruction
//////////////////////////////////////////////////////////////////////////////

    iType_e decode_branch;
    iType_e decode_load;
    iType_e decode_store;
    iType_e decode_op_imm;
    iType_e decode_op;
    iType_e decode_misc_mem;
    iType_e decode_system;
    iType_e decode_atomic;

    logic [2:0] funct3;
    logic [6:0] funct7;
    logic [6:0] opcode;

    assign opcode = instruction[6:0];
    assign funct3 = instruction[14:12];
    assign funct7 = instruction[31:25];

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

    always_comb begin
        unique case (funct3)
            3'b000:     decode_store = SB;
            3'b001:     decode_store = SH;
            3'b010:     decode_store = SW;
            default:    decode_store = INVALID;
        endcase
    end

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
            10'b0000001000:     decode_op = MUL;
            10'b0000001001:     decode_op = MULH;
            10'b0000001010:     decode_op = MULHSU;
            10'b0000001011:     decode_op = MULHU;
            10'b0000001100:     decode_op = DIV;
            10'b0000001101:     decode_op = DIVU;
            10'b0000001110:     decode_op = REM;
            10'b0000001111:     decode_op = REMU;
            10'b??10001000:     decode_op = ZKNEEnable ? AES32ESI : INVALID;
            10'b??10011000:     decode_op = ZKNEEnable ? AES32ESMI : INVALID;
            default:            decode_op = INVALID;
        endcase
    end

    always_comb begin
        unique case (funct3)
            3'b000:     decode_misc_mem = NOP;  /* FENCE */
            default:    decode_misc_mem = INVALID;
        endcase
    end

    always_comb begin
        unique case (instruction[31:7]) inside
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

    assign decode_atomic = funct7[3] == 1'b1 ? ATOMIC_LRSC : ATOMIC_AMO;

    always_comb begin
        unique case (opcode)
            7'b0110111: instruction_operation = LUI;
            7'b0010111: instruction_operation = ADD;                        /* AUIPC */
            7'b1101111: instruction_operation = JAL;
            7'b1100111: instruction_operation = JALR;
            7'b1100011: instruction_operation = decode_branch;              /* BRANCH */
            7'b0000011: instruction_operation = decode_load;                /* LOAD */
            7'b0100011: instruction_operation = decode_store;               /* STORE */
            7'b0010011: instruction_operation = decode_op_imm;              /* OP-IMM */
            7'b0110011: instruction_operation = decode_op;                  /* OP */
            7'b0001111: instruction_operation = decode_misc_mem;            /* MISC-MEM */
            7'b1110011: instruction_operation = decode_system;              /* SYSTEM */
            7'b1010111: instruction_operation = VEnable ? VECTOR : INVALID; /* OP-V */
            7'b0000111: instruction_operation = VEnable ? VLOAD  : INVALID; /* LOAD-FP */
            7'b0100111: instruction_operation = VEnable ? VSTORE : INVALID; /* STORE-FP */
            7'b0101111: instruction_operation = AEnable != OFF ? decode_atomic : INVALID;
            default:    instruction_operation = INVALID;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
//  Decode Atomic Instruction
//////////////////////////////////////////////////////////////////////////////
    iTypeAtomic_e atomic_operation;
    if (AEnable != OFF) begin : a_enable_decode_gen_on

        always_comb begin
            if (instruction_operation == ATOMIC_LRSC) begin
                unique case (funct7[6:2]) inside
                    5'b00010: atomic_operation = LR;
                    5'b00011: atomic_operation = SC;
                    default:  atomic_operation = ANOP;
                endcase
            end
            else if (instruction_operation == ATOMIC_AMO) begin
                unique case (funct7[6:2]) inside
                    5'b00001: atomic_operation = AMOSWAP;
                    5'b00000: atomic_operation = AMOADD;
                    5'b00100: atomic_operation = AMOXOR;
                    5'b01100: atomic_operation = AMOAND;
                    5'b01000: atomic_operation = AMOOR;
                    5'b10000: atomic_operation = AMOMIN;
                    5'b10100: atomic_operation = AMOMAX;
                    5'b11000: atomic_operation = AMOMINU;
                    5'b11100: atomic_operation = AMOMAXU;
                    default:  atomic_operation = ANOP;
                endcase
            end
            else begin
                atomic_operation = ANOP;
            end
        end
        
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
            unique case (instruction[31:30]) inside
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
                6'b010111:     decode_vector_opi = VMV;
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

    end
    else begin : v_enable_decode_gen_on
        assign vector_operation = VNOP;
    end

//////////////////////////////////////////////////////////////////////////////
//  Decodes the instruction format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (opcode[6:2])
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

    assign imm_i = {{21{instruction[31]}}, instruction[30:20]};
    assign imm_s = {{21{instruction[31]}}, instruction[30:25], instruction[11:7]};
    assign imm_b = {{20{instruction[31]}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
    assign imm_u = {instruction[31:12], 12'b0};
    assign imm_j = {{12{instruction[31]}}, instruction[19:12], instruction[20], instruction[30:25], instruction[24:21], 1'b0};

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

//////////////////////////////////////////////////////////////////////////////
// Registe Lock Queue (RLQ)
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            locked_register <= '0;
            locked_memory   <= '0;
        end
        else if (hazard_o) begin
            locked_register <= '0;
            locked_memory   <= '0;
        end
        else if (enable) begin
            locked_register <= instruction[11:7];
            locked_memory   <= (opcode[6:2] == 5'b01000);
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Addresses to RegBank
//////////////////////////////////////////////////////////////////////////////

    assign rs1_o = instruction[19:15];
    assign rs2_o = instruction[24:20];

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rd_o <= '0;
        else if (enable)
            rd_o <= locked_register;
    end

//////////////////////////////////////////////////////////////////////////////
// Hazard signal generation
//////////////////////////////////////////////////////////////////////////////

    logic use_mem;
    logic use_rs1;
    logic use_rs2;

    logic locked_rs1;
    logic locked_rs2;

    logic hazard_mem;
    logic hazard_rs1;
    logic hazard_rs2;

    assign use_mem = ({opcode[6], opcode[4:2]} == '0) ? 1'b1 : 1'b0;

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

    assign locked_rs1 = (locked_register == rs1_o && rs1_o != '0) ? 1'b1 : 1'b0;
    assign locked_rs2 = (locked_register == rs2_o && rs2_o != '0) ? 1'b1 : 1'b0;

    assign hazard_mem = locked_memory   & use_mem;
    assign hazard_rs1 = locked_rs1      & use_rs1;
    assign hazard_rs2 = locked_rs2      & use_rs2;

    assign hazard_o   = (hazard_mem || hazard_rs1 || hazard_rs2) && enable && !jumped_i;

//////////////////////////////////////////////////////////////////////////////
// Exception Detection
//////////////////////////////////////////////////////////////////////////////

    logic invalid_inst;
    logic misaligned_fetch;

    assign invalid_inst     = instruction_operation == INVALID;

    if (COMPRESSED) begin : gen_misaligned_check_c
        assign misaligned_fetch = pc_i[0] != 1'b0;
    end
    else begin : gen_misaligned_check_nc
        assign misaligned_fetch = pc_i[1:0] != 2'b00;
    end

//////////////////////////////////////////////////////////////////////////////
// Control of the exits based on format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_format)
            U_TYPE, J_TYPE:     first_operand   = pc_i;
            default:            first_operand   = rs1_data_read_i;
        endcase
    end

    always_comb begin
        unique case (instruction_format)
            R_TYPE, B_TYPE:     second_operand   = rs2_data_read_i;
            default:            second_operand   = immediate;
        endcase
    end

    always_comb begin
        unique case (instruction_format)
            S_TYPE:             third_operand   = rs2_data_read_i;
            default:            third_operand   = immediate;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            first_operand_o         <= '0;
            second_operand_o        <= '0;
            third_operand_o         <= '0;
            pc_o                    <= '0;
            instruction_o           <= '0;
            compressed_o            <= 1'b0;
            instruction_operation_o <= NOP;
            tag_o                   <= '0;
            exc_ilegal_inst_o       <= 1'b0;
            exc_misaligned_fetch_o  <= 1'b0;
            exc_inst_access_fault_o <= 1'b0;
            vector_operation_o      <= VNOP;
            atomic_operation_o      <= ANOP;
        end
        else if (hazard_o) begin
            first_operand_o         <= '0;
            second_operand_o        <= '0;
            third_operand_o         <= '0;
            pc_o                    <= '0;
            instruction_o           <= '0;
            compressed_o            <= 1'b0;
            instruction_operation_o <= NOP;
            tag_o                   <= tag_i;
            exc_ilegal_inst_o       <= 1'b0;
            exc_misaligned_fetch_o  <= 1'b0;
            exc_inst_access_fault_o <= 1'b0;
            vector_operation_o      <= VNOP;
            atomic_operation_o      <= ANOP;
        end
        else if (enable) begin
            first_operand_o         <= first_operand;
            second_operand_o        <= second_operand;
            third_operand_o         <= third_operand;
            pc_o                    <= pc_i;
            instruction_o           <= instruction;
            compressed_o            <= compressed_i;
            instruction_operation_o <= instruction_operation;
            tag_o                   <= tag_i;
            exc_ilegal_inst_o       <= invalid_inst;
            exc_misaligned_fetch_o  <= misaligned_fetch;
            exc_inst_access_fault_o <= exc_inst_access_fault_i;
            vector_operation_o      <= vector_operation;
            atomic_operation_o      <= atomic_operation;
        end
    end

endmodule
