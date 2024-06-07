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
    parameter bit           ZKNEEnable  = 1'b1,
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
    input   logic           jump_misaligned_i,

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
    output  logic           hazard_o,
    output  logic           instruction_prefetched_o,

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
    logic [31:0]    pc_decode;
    logic [31:0]    instruction_decode;

    formatType_e    instruction_format;
    iType_e         instruction_operation;

//////////////////////////////////////////////////////////////////////////////
// Compressed extension
//////////////////////////////////////////////////////////////////////////////

    logic instruction_compressed;
    logic enable_decode;

    if (COMPRESSED) begin : gen_compressed_on

        logic [31:0] instruction_fetched;
        logic [31:0] instruction_decompressed;

        assign enable_decode = enable && !jump_misaligned_i;
        assign instruction_decode = instruction_compressed ? instruction_decompressed : instruction_fetched;

        iprefetch prefetch (
            .clk                (clk),
            .reset_n            (reset_n),
            .enable_i           (enable),
            .hazard_i           (hazard_o),
            .tag_i              (tag_i),
            .pc_i               (pc_i),
            .instruction_i      (instruction),
            .prefetched_o       (instruction_prefetched_o),
            .compressed_o       (instruction_compressed),
            .pc_o               (pc_decode),
            .instruction_o      (instruction_fetched)
        );

        decompresser decompresser (
            .instruction_i (instruction_fetched[15:0]),
            .instruction_o (instruction_decompressed)
        );
    end
    else begin : gen_compressed_off
        assign enable_decode = enable;
        assign instruction_decode = instruction;
        assign instruction_compressed = 1'b0;
        assign pc_decode = pc_i;
        assign instruction_prefetched_o = 1'b0;
    end


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
        if (reset_n == 1'b0)
            last_hazard <= 1'b1;
        else
            last_hazard <= hazard_o;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (reset_n == 1'b0)
            last_stall <= 1'b1;
        else
            last_stall <= ~enable;
    end

    always_comb begin
        if ((last_hazard | last_stall) == 1'b1) begin
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

    logic [2:0] funct3;
    logic [6:0] funct7;
    logic [6:0] opcode;

    assign opcode = instruction_decode[6:0];
    assign funct3 = instruction_decode[14:12];
    assign funct7 = instruction_decode[31:25];

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
        unique case (instruction_decode[31:7]) inside
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

    always_comb begin
        unique case (opcode)
            7'b0110111: instruction_operation = LUI;
            7'b0010111: instruction_operation = ADD;                /* AUIPC */
            7'b1101111: instruction_operation = JAL;
            7'b1100111: instruction_operation = JALR;
            7'b1100011: instruction_operation = decode_branch;      /* BRANCH */
            7'b0000011: instruction_operation = decode_load;        /* LOAD */
            7'b0100011: instruction_operation = decode_store;       /* STORE */
            7'b0010011: instruction_operation = decode_op_imm;      /* OP-IMM */
            7'b0110011: instruction_operation = decode_op;          /* OP */
            7'b0001111: instruction_operation = decode_misc_mem;    /* MISC-MEM */
            7'b1110011: instruction_operation = decode_system;      /* SYSTEM */
            default:    instruction_operation = INVALID;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
//  Decodes the instruction format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (opcode[6:2])
            5'b11001, 5'b00000, 5'b00100:   instruction_format = I_TYPE;    /* JALR, LOAD, OP-IMM */
            5'b01000:                       instruction_format = S_TYPE;    /* STORE */
            5'b11000:                       instruction_format = B_TYPE;    /* BRANCH */
            5'b01101, 5'b00101:             instruction_format = U_TYPE;    /* LUI, AUIPC */
            5'b11011:                       instruction_format = J_TYPE;    /* JAL */
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
    logic [31:0] imm_r;

    assign imm_i = {{21{instruction_decode[31]}}, instruction_decode[30:20]};
    assign imm_s = {{21{instruction_decode[31]}}, instruction_decode[30:25], instruction_decode[11:7]};
    assign imm_b = {{20{instruction_decode[31]}}, instruction_decode[7], instruction_decode[30:25], instruction_decode[11:8], 1'b0};
    assign imm_u = {instruction_decode[31:12], 12'b0};
    assign imm_j = {{12{instruction_decode[31]}}, instruction_decode[19:12], instruction_decode[20], instruction_decode[30:25], instruction_decode[24:21], 1'b0};
    assign imm_r = '0;

    always_comb begin
        unique case (instruction_format)
            I_TYPE:     immediate = imm_i;
            S_TYPE:     immediate = imm_s;
            B_TYPE:     immediate = imm_b;
            U_TYPE:     immediate = imm_u;
            J_TYPE:     immediate = imm_j;
            default:    immediate = imm_r;  /* R_TYPE */
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
        else if (hazard_o == 1'b1) begin
            locked_register <= '0;
            locked_memory   <= '0;
        end
        else if (enable_decode == 1'b1) begin
            locked_register <= instruction_decode[11:7];
            locked_memory   <= (opcode[6:2] == 5'b01000);
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Addresses to RegBank
//////////////////////////////////////////////////////////////////////////////

    assign rs1_o = instruction_decode[19:15];
    assign rs2_o = instruction_decode[24:20];

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

    assign hazard_o   = (hazard_mem | hazard_rs1 | hazard_rs2) & enable_decode;

//////////////////////////////////////////////////////////////////////////////
// Exception Detection
//////////////////////////////////////////////////////////////////////////////

    logic invalid_inst;
    logic misaligned_fetch;

    assign invalid_inst     = instruction_operation == INVALID;
    assign misaligned_fetch = pc_decode[0] != 1'b0;

//////////////////////////////////////////////////////////////////////////////
// Control of the exits based on format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_format)
            U_TYPE, J_TYPE: begin
                                first_operand   = pc_decode;
                                second_operand  = immediate;
                                third_operand   = immediate;
                            end
            R_TYPE, B_TYPE: begin
                                first_operand   = rs1_data_read_i;
                                second_operand  = rs2_data_read_i;
                                third_operand   = immediate;
                            end
            S_TYPE:         begin
                                first_operand   = rs1_data_read_i;
                                second_operand  = immediate;
                                third_operand   = rs2_data_read_i;
                            end
            default:        begin
                                first_operand   = rs1_data_read_i;
                                second_operand  = immediate;
                                third_operand   = immediate;
                            end
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
        end
        else if (hazard_o == 1'b1) begin
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
        end 
        else if (enable_decode == 1'b1) begin
            first_operand_o         <= first_operand;
            second_operand_o        <= second_operand;
            third_operand_o         <= third_operand;
            pc_o                    <= pc_decode;
            instruction_o           <= instruction_decode;
            compressed_o            <= instruction_compressed;
            instruction_operation_o <= instruction_operation;
            tag_o                   <= tag_i;
            exc_ilegal_inst_o       <= invalid_inst;
            exc_misaligned_fetch_o  <= misaligned_fetch;
            exc_inst_access_fault_o <= exc_inst_access_fault_i;
        end
    end

endmodule
