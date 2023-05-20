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

    input   logic [31:0]    instruction_i,          // Object code of the instruction to extract the immediate operand
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
    output  logic           exception_o,
    output  logic           predicted_branch_o,

    output  logic           predict_branch_taken_o,
    output  logic [31:0]    predict_branch_pc_o
    );

    logic   [31:0]  instruction, instruction_r;
    formatType_e    instruction_format;
    iType_e         instruction_operation;
    logic   [31:0]  immediate, first_operand_int, second_operand_int, third_operand_int;
    logic           hazard_r;
    logic    [4:0]  locked_registers[2];
    logic    [4:0]  target_register;
    logic           is_store;
    logic           locked_memory[2];

    logic           inconditional_branch, conditional_branch;
    logic           negative_offset, conditional_branch_taken, predict_branch_taken;

//////////////////////////////////////////////////////////////////////////////
// Re-Decode instruction on hazard
//////////////////////////////////////////////////////////////////////////////

    assign instruction = (hazard_r) ? instruction_r : instruction_i;

    always_ff @(posedge clk ) begin
        instruction_r <= instruction;
        hazard_r      <= hazard_o;
    end

//////////////////////////////////////////////////////////////////////////////
// Find out the type of the instruction
//////////////////////////////////////////////////////////////////////////////

    always_comb begin 
        if (instruction[6:0] == 7'b0110111) instruction_operation = LUI;
        else if (instruction[6:0] == 7'b0010111) instruction_operation = ADD;    //AUIPC
        
        else if (instruction[6:0] == 7'b1101111) instruction_operation = JAL;
        else if (instruction[14:12] == 3'b000 && instruction[6:0] == 7'b1100111) instruction_operation = JALR;

        else if (instruction[14:12] == 3'b000 && instruction[6:0] == 7'b1100011) instruction_operation = BEQ;
        else if (instruction[14:12] == 3'b001 && instruction[6:0] == 7'b1100011) instruction_operation = BNE;
        else if (instruction[14:12] == 3'b100 && instruction[6:0] == 7'b1100011) instruction_operation = BLT;
        else if (instruction[14:12] == 3'b101 && instruction[6:0] == 7'b1100011) instruction_operation = BGE;
        else if (instruction[14:12] == 3'b110 && instruction[6:0] == 7'b1100011) instruction_operation = BLTU;
        else if (instruction[14:12] == 3'b111 && instruction[6:0] == 7'b1100011) instruction_operation = BGEU;

        else if (instruction[14:12] == 3'b000 && instruction[6:0] == 7'b0000011) instruction_operation = LB;
        else if (instruction[14:12] == 3'b001 && instruction[6:0] == 7'b0000011) instruction_operation = LH;
        else if (instruction[14:12] == 3'b010 && instruction[6:0] == 7'b0000011) instruction_operation = LW;
        else if (instruction[14:12] == 3'b100 && instruction[6:0] == 7'b0000011) instruction_operation = LBU;
        else if (instruction[14:12] == 3'b101 && instruction[6:0] == 7'b0000011) instruction_operation = LHU;

        else if (instruction[14:12] == 3'b000 && instruction[6:0] == 7'b0100011) instruction_operation = SB;
        else if (instruction[14:12] == 3'b001 && instruction[6:0] == 7'b0100011) instruction_operation = SH;
        else if (instruction[14:12] == 3'b010 && instruction[6:0] == 7'b0100011) instruction_operation = SW;
        
        else if (instruction[14:12] == 3'b000 && instruction[6:0] == 7'b0010011) instruction_operation = ADD;     // ADDI
        else if (instruction[14:12] == 3'b010 && instruction[6:0] == 7'b0010011) instruction_operation = SLT;     // SLTI
        else if (instruction[14:12] == 3'b011 && instruction[6:0] == 7'b0010011) instruction_operation = SLTU;    // SLTIU
        else if (instruction[14:12] == 3'b100 && instruction[6:0] == 7'b0010011) instruction_operation = XOR;     // XORI
        else if (instruction[14:12] == 3'b110 && instruction[6:0] == 7'b0010011) instruction_operation = OR;      // ORI
        else if (instruction[14:12] == 3'b111 && instruction[6:0] == 7'b0010011) instruction_operation = AND;     // ANDI

        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b001 && instruction[6:0] == 7'b0010011) instruction_operation = SLL;    // SLLI
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b101 && instruction[6:0] == 7'b0010011) instruction_operation = SRL;    // SRLI
        else if (instruction[31:25] == 7'b0100000 && instruction[14:12] == 3'b101 && instruction[6:0] == 7'b0010011) instruction_operation = SRA;    // SRAI

        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b000 && instruction[6:0] == 7'b0110011) instruction_operation = ADD;
        else if (instruction[31:25] == 7'b0100000 && instruction[14:12] == 3'b000 && instruction[6:0] == 7'b0110011) instruction_operation = SUB;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b001 && instruction[6:0] == 7'b0110011) instruction_operation = SLL;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b010 && instruction[6:0] == 7'b0110011) instruction_operation = SLT;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b011 && instruction[6:0] == 7'b0110011) instruction_operation = SLTU;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b100 && instruction[6:0] == 7'b0110011) instruction_operation = XOR;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b101 && instruction[6:0] == 7'b0110011) instruction_operation = SRL;
        else if (instruction[31:25] == 7'b0100000 && instruction[14:12] == 3'b101 && instruction[6:0] == 7'b0110011) instruction_operation = SRA;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b110 && instruction[6:0] == 7'b0110011) instruction_operation = OR;
        else if (instruction[31:25] == 7'b0000000 && instruction[14:12] == 3'b111 && instruction[6:0] == 7'b0110011) instruction_operation = AND;

        else if (instruction[14:12] == 3'b000 && instruction[6:0] == 7'b0001111) instruction_operation = NOP;          // FENCE

        else if (instruction[14:12] == 3'b001 && instruction[6:0] == 7'b1110011) instruction_operation = CSRRW;
        else if (instruction[14:12] == 3'b010 && instruction[6:0] == 7'b1110011) instruction_operation = CSRRS;
        else if (instruction[14:12] == 3'b011 && instruction[6:0] == 7'b1110011) instruction_operation = CSRRC;
        else if (instruction[14:12] == 3'b101 && instruction[6:0] == 7'b1110011) instruction_operation = CSRRWI;
        else if (instruction[14:12] == 3'b110 && instruction[6:0] == 7'b1110011) instruction_operation = CSRRSI;
        else if (instruction[14:12] == 3'b111 && instruction[6:0] == 7'b1110011) instruction_operation = CSRRCI;

        else if (instruction[31:0] == 32'h00000073) instruction_operation = ECALL;
        else if (instruction[31:0] == 32'h00100073) instruction_operation = EBREAK;

        else if (instruction[31:0] == 32'h10200073) instruction_operation = SRET;
        else if (instruction[31:0] == 32'h30200073) instruction_operation = MRET;

        else if (instruction[31:0] == 32'h10500073) instruction_operation = WFI;

        else if (instruction[31:0] == 32'h00000013) instruction_operation = NOP;

        else instruction_operation = INVALID;
    end

//////////////////////////////////////////////////////////////////////////////
//  Decodes the instruction format
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        case (instruction[6:0])
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
                        immediate[31:11] = (!instruction[31]) 
                                            ? '0 
                                            : '1;
                        immediate[10:0]  = instruction[30:20];
                    end

            S_TYPE: begin
                        immediate[31:11] = (!instruction[31]) 
                                            ? '0 
                                            : '1;
                        immediate[10:5]  = instruction[30:25];
                        immediate[4:0]   = instruction[11:7];
                    end

            B_TYPE: begin
                        immediate[31:12] = (!instruction[31]) 
                                            ? '0 
                                            : '1;
                        immediate[11]    = instruction[7];
                        immediate[10:5]  = instruction[30:25];
                        immediate[4:1]   = instruction[11:8];
                        immediate[0]     = 0;
                    end

            U_TYPE: begin
                        immediate[31:12] = instruction[31:12];
                        immediate[11:0]  = '0;
                    end

            J_TYPE: begin
                        immediate[31:20] = (!instruction[31]) 
                                            ? '0 
                                            : '1;
                        immediate[19:12] = instruction[19:12];
                        immediate[11]    = instruction[20];
                        immediate[10:5]  = instruction[30:25];
                        immediate[4:1]   = instruction[24:21];
                        immediate[0]     = 0;
                    end

            default:    immediate        = '0;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Addresses to RegBank
//////////////////////////////////////////////////////////////////////////////

    assign rs1_o = instruction[19:15];
    assign rs2_o = instruction[24:20];
    assign rd_o  = locked_registers[1];

//////////////////////////////////////////////////////////////////////////////
// Target definitions
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (!hazard_o) begin
            target_register = instruction[11:7];
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
// Branch Prediction
//////////////////////////////////////////////////////////////////////////////
/*
 * This implements static branch prediction. It takes an instruction and its PC and determines if
 * it's a branch or a jump and calculates its target. For jumps it will always predict taken. For
 * branches it will predict taken if the PC offset is negative.
 */
    always_comb begin
        if (executionUnit_e'(instruction_operation[5:3]) == BRANCH_UNIT) begin
            if (instruction_operation == JAL || instruction_operation == JALR) begin
                inconditional_branch    <= 1'b1;
                conditional_branch      <= 1'b0;
            end
            else begin
                inconditional_branch    <= 1'b0;
                conditional_branch      <= 1'b1;
            end
        end
        else begin
            inconditional_branch    <= 1'b0;
            conditional_branch      <= 1'b0;
        end
    end

    assign negative_offset          = immediate[31];
    assign conditional_branch_taken = conditional_branch   & negative_offset;
    assign predict_branch_taken     = inconditional_branch | conditional_branch_taken;

    assign predict_branch_pc_o      = pc_i + immediate;
    assign predict_branch_taken_o   = predict_branch_taken;

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
        predicted_branch_o <= predict_branch_taken;
        if (reset) begin
            first_operand_o         <= '0;
            second_operand_o        <= '0;
            third_operand_o         <= '0;
            pc_o                    <= '0;
            instruction_o           <= '0;
            instruction_operation_o <= NOP;
            tag_o                   <= '0;
            exception_o             <= 0;
        end 
        else if (stall) begin
            first_operand_o         <= first_operand_o;
            second_operand_o        <= second_operand_o;
            third_operand_o         <= third_operand_o;
            pc_o                    <= pc_o;
            instruction_o           <= instruction_o;
            instruction_operation_o <= instruction_operation_o;
            tag_o                   <= tag_o;
            exception_o             <= exception_o;
        end 
        else if (hazard_o) begin
            first_operand_o         <= '0;
            second_operand_o        <= '0;
            third_operand_o         <= '0;
            pc_o                    <= '0;
            instruction_o           <= '0;
            instruction_operation_o <= NOP;
            tag_o                   <= tag_i;
            exception_o             <= 0;
        end 
        else if (!stall) begin
            first_operand_o         <= first_operand_int;
            second_operand_o        <= second_operand_int;
            third_operand_o         <= third_operand_int;
            pc_o                    <= pc_i;
            instruction_o           <= instruction;
            instruction_operation_o <= instruction_operation;
            tag_o                   <= tag_i;
            exception_o             <= (instruction_operation==INVALID) ? 1 : 0;
        end
    end

endmodule
