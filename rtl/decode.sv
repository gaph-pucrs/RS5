/*!\file decode.sv
 * PUC-RS5 VERSION - 1.0.0 - Public Release
 *
 * Distribution:  March 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Decoder Unit is the second stage of PUC-RS5 processor core.
 *
 * \detailed
 * The decoder unit is the second stage of the PUC-RS5 processor core and 
 * is responsible for identify the instruction operation and based on that 
 * extracts the execution unit for that kind of instruction and
 * also fetches the operands in the register bank, calculate the immediate
 * operand and contains the mechanism of hazard detection, if a hazard is
 * detected (e.g. write after read) a bubble is issued which
 * consists in a NOP (NO Operation) instruction.
 */

module decode 
    import my_pkg::*;
(
    input   logic           clk,
    input   logic           reset,
    input   logic           stall,

    input   logic [31:0]    instruction_i,          // Object code of the instruction_int to extract the immediate operand
    input   logic [31:0]    pc_i,                   // Bypassed to execute unit as an operand
    input   logic [2:0]     tag_i,                  // Instruction tag_o
    input   logic [31:0]    rs1_data_read_i,        // Data read from register bank
    input   logic [31:0]    rs2_data_read_i,        // Data read from register bank

    output  logic [4:0]     rs1_o,                  // Address of the 1st register, conected directly in the register bank
    output  logic [4:0]     rs2_o,                  // Address of the 2nd register, conected directly in the register bank
    output  logic [4:0]     rd_o,                   // Write Address to register bank
    output  logic [31:0]    first_operand_o,        // First operand output register
    output  logic [31:0]    second_operand_o,       // Second operand output register
    output  logic [31:0]    third_operand_o,        // Third operand output register
    output  logic [31:0]    pc_o,                   // PC operand output register
    output  logic [31:0]    instruction_o,          // Instruction Used in exception_os and CSR operations
    output  logic [2:0]     tag_o,                  // Instruction tag_o
    output  iType_e         instruction_operation_o,// Instruction operation
    output  logic           hazard_o,               // Bubble issue indicator (0 active)
    output  logic           exception_o
    );

    logic [31:0] immediate, first_operand_int, second_operand_int, third_operand_int, instruction_int, last_instruction;
    logic last_hazard;
    logic [4:0] locked_registers[2];
    logic [4:0] target_register;
    logic is_store;
    logic locked_memory[2];

    formatType_e instruction_format;
    iType_e instruction_operation;

//////////////////////////////////////////////////////////////////////////////
// Re-Decode isntruction on hazard
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk ) begin
        last_instruction <= instruction_int;
        last_hazard      <= hazard_o;
    end

    always_comb begin
        if (last_hazard) begin
            instruction_int = last_instruction;
        end
        else begin
            instruction_int = instruction_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Find out the type of the instruction
//////////////////////////////////////////////////////////////////////////////

    iType_e decode_imm;
    iType_e decode_op;
    iType_e decode_branch;
    iType_e decode_load;
    iType_e decode_store;
    iType_e decode_system;
    iType_e decode_priv;

    logic [2:0] funct3;
    logic [6:0] funct7;
    logic [6:0] opcode;

    assign opcode = instruction_int[6:0];
    assign funct3 = instruction_int[14:12];
    assign funct7 = instruction_int[31:25];

    always_comb begin
        case (funct3_imm_e'(funct3))
            F3_ADDI:            decode_imm = ADD;
            F3_SLTI:            decode_imm = SLT;
            F3_SLTIU:           decode_imm = SLTU;
            F3_XORI:            decode_imm = XOR;
            F3_ORI:             decode_imm = OR;
            F3_ANDI:            decode_imm = AND;
            F3_SLLI:        begin
                case (funct7_sl_e'(funct7))
                    F7_SLLI:    decode_imm = SLL;
                    default:    decode_imm = INVALID;
                endcase
            end
            F3_SRLI_SRAI:   begin
                case (funct7_sr_e'(funct7))
                    F7_SRAI:    decode_imm = SRA;
                    F7_SRLI:    decode_imm = SRL;
                    default:    decode_imm = INVALID;
                endcase
            end
            default:            decode_imm = INVALID;
        endcase
    end

    always_comb begin
        case (funct7_sub_sra_e'(funct7))
            '0:         begin
                case (funct3_op_e'(funct3))
                    F3_ADD:     decode_op = ADD;
                    F3_SLL:     decode_op = SLL;
                    F3_SLT:     decode_op = SLT;
                    F3_SLTU:    decode_op = SLTU;
                    F3_XOR:     decode_op = XOR;
                    F3_SR:      decode_op = SRL;
                    F3_OR:      decode_op = OR;
                    F3_AND:     decode_op = AND;
                    default:    decode_op = INVALID;
                endcase
            end
            F7_SUB_SRA: begin
                case (funct3_op_e'(funct3))
                    F3_ADD:     decode_op = SUB;
                    F3_SR:      decode_op = SRA;
                    default:    decode_op = INVALID;
                endcase
            end
            default:            decode_op = INVALID;
        endcase
    end

    always_comb begin
        case (funct3_branch_e'(funct3))
            F3_BEQ:             decode_branch = BEQ;
            F3_BNE:             decode_branch = BNE;
            F3_BLT:             decode_branch = BLT;
            F3_BGE:             decode_branch = BGE;
            F3_BLTU:            decode_branch = BLTU;
            F3_BGEU:            decode_branch = BGEU;
            default:            decode_branch = INVALID;
        endcase
    end

    always_comb begin
        case (funct3_load_e'(funct3))
            F3_LB:              decode_load = LB;
            F3_LH:              decode_load = LH;
            F3_LW:              decode_load = LW;
            F3_LBU:             decode_load = LBU;
            F3_LHU:             decode_load = LHU;
            default:            decode_load = INVALID;
        endcase
    end

    always_comb begin
        case (funct3_store_e'(funct3))
            F3_SB:              decode_store = SB;
            F3_SH:              decode_store = SH;
            F3_SW:              decode_store = SW;
            default:            decode_store = INVALID;
        endcase
    end

    always_comb begin
        if (instruction_int[11:7] == '0 && rs1_o == '0) begin
            case (funct7_priv_e'(funct7))
                F7_ECALL_EBREAK:    begin
                    case (rs2Op_e'(rs2_o))
                        RS2_ECALL:  decode_priv = ECALL;
                        RS2_EBREAK: decode_priv = EBREAK;
                        default:    decode_priv = INVALID;
                    endcase
                end
                F7_WFI:        begin
                    case (rs2Op_e'(rs2_o))
                        RS2_WFI:    decode_priv = WFI;
                        default:    decode_priv = INVALID;
                    endcase
                end
                F7_MRET:
                    case (rs2Op_e'(rs2_o))
                        RS2_RET:    decode_priv = MRET;
                        default:    decode_priv = INVALID;
                    endcase
                default:            decode_priv = INVALID;
            endcase
        end
        else begin
                                    decode_priv = INVALID;
        end
    end

    always_comb begin
        case (funct3_system_e'(funct3))
            F3_CSRRW:               decode_system = CSRRW;
            F3_CSRRS:               decode_system = CSRRS;
            F3_CSRRC:               decode_system = CSRRC;
            F3_CSRRWI:              decode_system = CSRRWI;
            F3_CSRRSI:              decode_system = CSRRSI;
            F3_CSRRCI:              decode_system = CSRRCI;
            F3_PRIV:                decode_system = decode_priv;
            default:                decode_system = INVALID;
        endcase
    end

    always_comb begin 
        case (opcodes_e'(opcode))
            OP_LUI:                 instruction_operation = LUI;
            OP_AUIPC:               instruction_operation = ADD;
            OP_JAL:                 instruction_operation = JAL;
            OP_IMM:                 instruction_operation = decode_imm;
            OP_OP:                  instruction_operation = decode_op;
            OP_BRANCH:              instruction_operation = decode_branch;
            OP_LOAD:                instruction_operation = decode_load;
            OP_STORE:               instruction_operation = decode_store;
            OP_SYSTEM:              instruction_operation = decode_system;
            OP_MISC_MEM:    begin   
                case (funct3_misc_mem_e'(funct3))
                    F3_FENCE:       instruction_operation = NOP;
                    default:        instruction_operation = INVALID;
                endcase
            end
            OP_JALR:        begin
                case (funct3_jalr_e'(funct3))
                    F3_JALR:        instruction_operation = JALR;
                    default:        instruction_operation = INVALID;
                endcase
            end
            default:                instruction_operation = INVALID;
        endcase
    end        
    // else if (instruction_int[31:0] == 32'h00000013) instruction_operation = NOP; ???

//////////////////////////////////////////////////////////////////////////////
//  Decodes the instruction format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        case (opcode)
            7'b0010011, 7'b1100111, 7'b0000011:     instruction_format = I_TYPE;
            7'b0100011:                             instruction_format = S_TYPE;
            7'b1100011:                             instruction_format = B_TYPE;
            7'b0110111, 7'b0010111:                 instruction_format = U_TYPE;
            7'b1101111:                             instruction_format = J_TYPE;
            default:                                instruction_format = R_TYPE;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Extract the immediate based on instruction format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        case (instruction_format)
            I_TYPE: begin
                        immediate[31:11] = (!instruction_int[31]) 
                                            ? '0 
                                            : '1;
                        immediate[10:0]  = instruction_int[30:20];
                    end

            S_TYPE: begin
                        immediate[31:11] = (!instruction_int[31]) 
                                            ? '0 
                                            : '1;
                        immediate[10:5]  = instruction_int[30:25];
                        immediate[4:0]   = instruction_int[11:7];
                    end

            B_TYPE: begin
                        immediate[31:12] = (!instruction_int[31]) 
                                            ? '0 
                                            : '1;
                        immediate[11]    = instruction_int[7];
                        immediate[10:5]  = instruction_int[30:25];
                        immediate[4:1]   = instruction_int[11:8];
                        immediate[0]     = 0;
                    end

            U_TYPE: begin
                        immediate[31:12] = instruction_int[31:12];
                        immediate[11:0]  = '0;
                    end

            J_TYPE: begin
                        immediate[31:20] = (!instruction_int[31]) 
                                            ? '0 
                                            : '1;
                        immediate[19:12] = instruction_int[19:12];
                        immediate[11]    = instruction_int[20];
                        immediate[10:5]  = instruction_int[30:25];
                        immediate[4:1]   = instruction_int[24:21];
                        immediate[0]     = 0;
                    end

            default:    immediate        = '0;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Addresses to RegBank
//////////////////////////////////////////////////////////////////////////////

    assign rs1_o = instruction_int[19:15];
    assign rs2_o = instruction_int[24:20];
    assign rd_o  = locked_registers[1];

//////////////////////////////////////////////////////////////////////////////
// Target definitions
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (!hazard_o) begin
            target_register = instruction_int[11:7];
            ///////////////////////////////////
            if (instruction_operation == SB || instruction_operation == SH || instruction_operation == SW) begin
                is_store = 1;
            end
            else begin
                is_store = 0;
            end
        end
        else begin
            target_register = '0;
            is_store        = 0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Registe Lock Queue (RLQ)
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset) begin
            locked_registers[0] <= '0;
            locked_registers[1] <= '0;
            locked_memory[0]    <= '0;
            locked_memory[1]    <= '0;
        end 
        else if (!stall) begin
            locked_registers[0] <= target_register;
            locked_memory[0]    <= is_store;
            locked_registers[1] <= locked_registers[0];
            locked_memory[1]    <= locked_memory[0];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Hazard signal generation
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if ((locked_memory[0] || locked_memory[1]) && (executionUnit_e'(instruction_operation[5:3]) == MEMORY_UNIT)) begin
            hazard_o = 1;
        end
        else if (locked_registers[0] == rs1_o && rs1_o != '0) begin
            hazard_o = 1;
        end
        else if (locked_registers[0] == rs2_o && rs2_o != '0) begin
            hazard_o = 1;
        end
        else begin
            hazard_o = 0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Control of the exits based on format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        first_operand_int = (instruction_format == U_TYPE || instruction_format==J_TYPE) 
                            ? pc_i  
                            : rs1_data_read_i;

        second_operand_int = (instruction_format == R_TYPE || instruction_format==B_TYPE) 
                            ? rs2_data_read_i 
                            : immediate;

        third_operand_int  = (instruction_format == S_TYPE) 
                            ? rs2_data_read_i 
                            : immediate;
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset) begin
            first_operand_o  <= '0;
            second_operand_o <= '0;
            third_operand_o  <= '0;
            pc_o             <= '0;
            instruction_o    <= '0;
            instruction_operation_o <= NOP;
            tag_o            <= '0;
            exception_o      <= 0;
        end 
        else if (stall) begin
            first_operand_o   <= first_operand_o;
            second_operand_o  <= second_operand_o;
            third_operand_o   <= third_operand_o;
            pc_o              <= pc_o;
            instruction_o     <= instruction_o;
            instruction_operation_o <= instruction_operation_o;
            tag_o             <= tag_o;
            exception_o       <= exception_o;
        end 
        else if (hazard_o) begin
            first_operand_o  <= '0;
            second_operand_o <= '0;
            third_operand_o  <= '0;
            pc_o             <= '0;
            instruction_o    <= '0;
            instruction_operation_o <= NOP;
            tag_o            <= tag_i;
            exception_o      <= 0;
        end 
        else if (!stall) begin
            first_operand_o  <= first_operand_int;
            second_operand_o <= second_operand_int;
            third_operand_o  <= third_operand_int;
            pc_o             <= pc_i;
            instruction_o    <= instruction_int;
            instruction_operation_o <= instruction_operation;
            tag_o            <= tag_i;
            exception_o      <= (instruction_operation==INVALID) ? 1 : 0;
        end
    end

endmodule
