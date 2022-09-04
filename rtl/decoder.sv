/*!\file decoder.sv
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
 * Decoder Unit is the second stage of PUCRS-RV processor.
 *
 * \detailed
 * The decoder unit is the second stage of the PUCRS-RV processor and 
 * is responsible for identify the instruction type and based on that 
 * extracts the execute module of the instruction and the operation. 
 * Also fetch the operands in the register bank, calculate the imediate
 * operand and also have a mechanism of hazard detection, if a hazard is
 * detected (e.g. write after read) a bubble is issued. The bubble
 * consists in a NOP (NO Operation) instruction.
 */

import my_pkg::*;

module decoder (
    input logic clk,
    input logic reset,
    input logic we,
    input logic [31:0]  instruction_in,         // Object code of the instruction to extract the immediate operand
    input logic [31:0]  NPC,                    // Bypassed to execute unit as an operand
    input logic [3:0]   tag_in,                 // Instruction Tag
    input logic [31:0]  dataA,                  // Data read from register bank
    input logic [31:0]  dataB,                  // Data read from register bank
    output logic [4:0]  regA_add,               // Address of the 1st register, conected directly in the register bank
    output logic [4:0]  regB_add,               // Address of the 2nd register, conected directly in the register bank
    output logic [4:0] wrAddr,                  // Write Address to register bank
    output logic [31:0] opA_out,                // First operand output register
    output logic [31:0] opB_out,                // Second operand output register
    output logic [31:0] opC_out,                // Third operand output register
    output logic [31:0] NPC_out,                // PC operand output register
    output logic [31:0] instruction_out,        // Instruction Used in exceptions and CSR operations
    output i_type i_out,                        // Instruction operation (OP0, OP1...)
    output logic [3:0]  tag_out,                // Instruction Tag
    output logic        hazard,                 // Bubble issue indicator (0 active)
    output logic        exception
);

    logic [31:0] imed, opA, opB, opC, instruction, last_inst;
    logic hazard_r;
    logic [4:0] lock_reg[2];
    logic [4:0] regD_add;
    logic is_store;
    logic lock_mem[2];

    fmts fmt;
    i_type i;

///////////////////////////////////////////////// RE-DECODE INST TEST //////////////////////////////////////////////////////////////
    always @(posedge clk ) begin
        last_inst <= instruction;               // Holds the last cycle instruction
        hazard_r <= hazard;                     // Holds the last cycle state
    end

    always_comb
        if (hazard_r == 1)                      // If last cycle had a pipe stall
            instruction = last_inst;            // Re-decode last cycle instruction
        else
            instruction = instruction_in;

///////////////////////////////////////////////// find out the type of the instruction //////////////////////////////////////////////////////////////
    always_comb
             if (instruction[6:0]==7'b0110111) i<=LUI;
        else if (instruction[6:0]==7'b0010111) i<=ADD;    //AUIPC
        
        else if (instruction[6:0]==7'b1101111) i<=JAL;
        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b1100111) i<=JALR;

        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b1100011) i<=BEQ;
        else if (instruction[14:12]==3'b001 & instruction[6:0]==7'b1100011) i<=BNE;
        else if (instruction[14:12]==3'b100 & instruction[6:0]==7'b1100011) i<=BLT;
        else if (instruction[14:12]==3'b101 & instruction[6:0]==7'b1100011) i<=BGE;
        else if (instruction[14:12]==3'b110 & instruction[6:0]==7'b1100011) i<=BLTU;
        else if (instruction[14:12]==3'b111 & instruction[6:0]==7'b1100011) i<=BGEU;

        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b0000011) i<=LB;
        else if (instruction[14:12]==3'b001 & instruction[6:0]==7'b0000011) i<=LH;
        else if (instruction[14:12]==3'b010 & instruction[6:0]==7'b0000011) i<=LW;
        else if (instruction[14:12]==3'b100 & instruction[6:0]==7'b0000011) i<=LBU;
        else if (instruction[14:12]==3'b101 & instruction[6:0]==7'b0000011) i<=LHU;

        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b0100011) i<=SB;
        else if (instruction[14:12]==3'b001 & instruction[6:0]==7'b0100011) i<=SH;
        else if (instruction[14:12]==3'b010 & instruction[6:0]==7'b0100011) i<=SW;
        
        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b0010011) i<=ADD;     // ADDI
        else if (instruction[14:12]==3'b010 & instruction[6:0]==7'b0010011) i<=SLT;     // SLTI
        else if (instruction[14:12]==3'b011 & instruction[6:0]==7'b0010011) i<=SLTU;    // SLTIU
        else if (instruction[14:12]==3'b100 & instruction[6:0]==7'b0010011) i<=XOR;     // XORI
        else if (instruction[14:12]==3'b110 & instruction[6:0]==7'b0010011) i<=OR;      // ORI
        else if (instruction[14:12]==3'b111 & instruction[6:0]==7'b0010011) i<=AND;     // ANDI

        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b001 & instruction[6:0]==7'b0010011) i<=SLL;    // SLLI
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b101 & instruction[6:0]==7'b0010011) i<=SRL;    // SRLI
        else if (instruction[31:25]==7'b0100000 & instruction[14:12]==3'b101 & instruction[6:0]==7'b0010011) i<=SRA;    // SRAI

        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b000 & instruction[6:0]==7'b0110011) i<=ADD;
        else if (instruction[31:25]==7'b0100000 & instruction[14:12]==3'b000 & instruction[6:0]==7'b0110011) i<=SUB;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b001 & instruction[6:0]==7'b0110011) i<=SLL;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b010 & instruction[6:0]==7'b0110011) i<=SLT;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b011 & instruction[6:0]==7'b0110011) i<=SLTU;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b100 & instruction[6:0]==7'b0110011) i<=XOR;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b101 & instruction[6:0]==7'b0110011) i<=SRL;
        else if (instruction[31:25]==7'b0100000 & instruction[14:12]==3'b101 & instruction[6:0]==7'b0110011) i<=SRA;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b110 & instruction[6:0]==7'b0110011) i<=OR;
        else if (instruction[31:25]==7'b0000000 & instruction[14:12]==3'b111 & instruction[6:0]==7'b0110011) i<=AND;

        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b0001111) i<=NOP;          // FENCE

        else if (instruction[14:12]==3'b001 & instruction[6:0]==7'b1110011) i<=CSRRW;
        else if (instruction[14:12]==3'b010 & instruction[6:0]==7'b1110011) i<=CSRRS;
        else if (instruction[14:12]==3'b011 & instruction[6:0]==7'b1110011) i<=CSRRC;
        else if (instruction[14:12]==3'b101 & instruction[6:0]==7'b1110011) i<=CSRRWI;
        else if (instruction[14:12]==3'b110 & instruction[6:0]==7'b1110011) i<=CSRRSI;
        else if (instruction[14:12]==3'b111 & instruction[6:0]==7'b1110011) i<=CSRRCI;

        else if (instruction[31:0]==32'h00000073) i<=ECALL;
        else if (instruction[31:0]==32'h00100073) i<=EBREAK;

        else if (instruction[31:0]==32'h10200073) i<=SRET;
        else if (instruction[31:0]==32'h30200073) i<=MRET;

        else if (instruction[31:0]==32'h10500073) i<=WFI;

        else if (instruction[31:0]==32'h00000013) i<=NOP;

        else i<=INVALID;                        // if the opcodes are not recognized

/////////////////////////////////////////////////  Decodes the instruction format ///////////////////////////////////////////////////////////////////
    always_comb
        case (instruction[6:0])
            7'b0010011, 7'b1100111, 7'b0000011:     fmt <= I_type;
            7'b0100011:                             fmt <= S_type;
            7'b1100011:                             fmt <= B_type;
            7'b0110111, 7'b0010111:                 fmt <= U_type;
            7'b1101111:                             fmt <= J_type;
            default:                                fmt <= R_type;
        endcase

///////////////////////////////////////////////// Addresses to RegBank //////////////////////////////////////////////////////////////////////////////
    assign regA_add = instruction[19:15];
    assign regB_add = instruction[24:20];
    assign wrAddr = lock_reg[1];

///////////////////////////////////////////////// Extract the immediate based on instruction type ///////////////////////////////////////////////////
    always_comb
        case (fmt)
            I_type: begin
                        imed[31:11] <= (instruction[31]==0) ? '0 : '1;
                        imed[10:0] <= instruction[30:20];
                    end

            S_type: begin
                        imed[31:11] <= (instruction[31]==0) ? '0 : '1;
                        imed[10:5] <= instruction[30:25];
                        imed[4:0]  <= instruction[11:7];
                    end

            B_type: begin
                        imed[31:12] <= (instruction[31]==0) ? '0 : '1;
                        imed[11] <= instruction[7];
                        imed[10:5] <= instruction[30:25];
                        imed[4:1] <= instruction[11:8];
                        imed[0] <= 0;
                    end

            U_type: begin
                        imed[31:12] <= instruction[31:12];
                        imed[11:0] <= '0;
                    end

            J_type: begin
                        imed[31:20] <= (instruction[31]==0) ? '0 : '1;
                        imed[19:12] <= instruction[19:12];
                        imed[11] <= instruction[20];
                        imed[10:5] <= instruction[30:25];
                        imed[4:1] <= instruction[24:21];
                        imed[0] <= 0;
                    end

            default:      imed <= '0;
        endcase

///////////////////////////////////////////////// Control of the exits based on format //////////////////////////////////////////////////////////////
    always_comb begin
        opA <= (fmt==U_type | fmt==J_type) ? NPC   : dataA;
        opB <= (fmt==R_type | fmt==B_type) ? dataB : imed;
        opC <= (fmt==S_type)               ? dataB : imed;
    end

////////////////////////////////////////////////// TARGET DEFINITIONS ///////////////////////////////////////////////////////////////////////////////
    always_comb
        if (!hazard) begin
            regD_add <= instruction[11:7];
            ///////////////////////////////////
            if (i==SB || i==SH || i==SW)                    // Indicates a pending write in memory, used to avoid data hazards in memory
                is_store <= 1;
            else
                is_store <= 0;
        
        end else begin
            regD_add <= '0;
            is_store <= 0;
        end

////////////////////////////////////////////////// REGISTER LOCK QUEUE //////////////////////////////////////////////////////////////////////////////
    always @(posedge clk or negedge reset)  
        if (!reset) begin                               // Reset clears the queues
            lock_reg[0] <= '0;
            lock_reg[1] <= '0;
            lock_mem[0] <= '0;
            lock_mem[1] <= '0;

        end else begin
            lock_reg[0] <= regD_add;                    // Inserts a new Target in the queue 
            lock_mem[0] <= is_store;
            lock_reg[1] <= lock_reg[0];                 // Move the queue forward
            lock_mem[1] <= lock_mem[0];
        end

///////////////////////////////////////////////// HAZARD SIGNAL GENERATION //////////////////////////////////////////////////////////////////////////
    always_comb
        if ((lock_mem[0] || lock_mem[1]) && (i==LB || i==LBU || i==LH || i==LH || i==LW))
            hazard <= 1;
        else if ((lock_reg[0]==regA_add || lock_reg[1]==regA_add) && regA_add!=0)
            hazard <= 1;
        else if ((lock_reg[0]==regB_add || lock_reg[1]==regB_add) && regB_add!=0)
            hazard <= 1;
        else
            hazard <= 0;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk or negedge reset)
        if (!reset) begin                                   // Reset
            opA_out <= '0;
            opB_out <= '0;
            opC_out <= '0;
            NPC_out <= '0;
            instruction_out <= '0;
            i_out <= NOP;
            tag_out <= '0;
            exception <= 0;

         end else if (hazard) begin                     // Propagate bubble
            opA_out <= '0;
            opB_out <= '0;
            opC_out <= '0;
            NPC_out <= '0;
            instruction_out <= '0;
            i_out <= NOP;
            tag_out <= '0;
            exception <= 0;

        end else begin                       // Propagate instruction
            opA_out <= opA;
            opB_out <= opB;
            opC_out <= opC;
            NPC_out <= NPC;
            instruction_out <= instruction;
            i_out <= i;
            tag_out <= tag_in;
            exception <= (i==INVALID) ? 1 : 0;
        end
    
endmodule
