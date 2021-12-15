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
 */

import my_pkg::*;

module decoder(
    input logic         clk,
    input logic         reset,
    input logic         ce,                 // Used to bubble propagation (0 means hold state because a bubble is being issued)
    input logic [31:0]  NPC_in,             // Just bypass to NPC_out
    input logic [31:0]  instruction,        // Instruction Object code fetched by fetch unit
    input logic [3:0]   tag_in,             // Instruction tag (just bypass)
    output logic [31:0] NPC_out,            // Bypass of NPC_in signal
    output fmts         fmt_out,            // Signal that indicates the instruction format
    output logic [31:0] instruction_out,    // Instruction object code to Operand Fetch (to catch immediate)
    output instruction_type i_out,          // Decoded Instruction operation (OP0, OP1...)
    output xu           xu_sel,             // Decoded Instruction unity     (adder,shifter...)
    output logic [3:0]  tag_out);           // Instruction tag stream

    fmts fmt;
    i_type i;
    xu xu_int;
    instruction_type op;

///////////////////////////////////////////////// find out the type of the instruction //////////////////////////////////////////////////////////////
    always_comb begin
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

        else if (instruction[31:0]==32'h00000000) i<=NOP;
        else if (instruction[31:0]==32'h00000013) i<=NOP;

        else i<=INVALID;                        // if the opcodes are not recognized
    end

    always_comb                                 // Execution unit is extracted based on instruction type
        case (i)
            ADD, SUB, SLTU, SLT:                        xu_int <= adder;
            XOR, OR, AND:                               xu_int <= logical;
            SLL, SRL, SRA:                              xu_int <= shifter;
            BEQ, BNE, BLT, BLTU, BGE, BGEU, JAL, JALR:  xu_int <= branch;
            LB, LBU, LH, LHU, LW, SB, SH, SW:           xu_int <= memory;
            default:                                    xu_int <= bypass;
        endcase

    always_comb                                 // Execution operation is extracted based on instruction type
        case (i)
            ADD, XOR, SLL, BEQ, LB:         op<=OP0;
            SUB, OR, SRL, BNE, LBU, LUI:    op<=OP1;
            SLTU, AND, SRA, BLT, LH:        op<=OP2;
            SLT, BLTU, LHU:                 op<=OP3;
            BGE, LW:                        op<=OP4;
            BGEU, SW:                       op<=OP5;
            JAL, SH:                        op<=OP6;
            JALR, SB:                       op<=OP7;
            default:                        op<=OP0;
        endcase

/////////////////////////////////////////////////  Decodes the instruction format ///////////////////////////////////////////////////////////////////
    always_comb
        if(instruction[6:0]==7'b0010011 | instruction[6:0]==7'b1100111 | instruction[6:0]==7'b0000011) // Register-Imediate(ADDI,ORI,ANDI,JALR,LOADS)
            fmt <= I_type;                  
        else if(instruction[6:0]==7'b0100011)   // Store_type(SW,SB,SH)
            fmt <= S_type;
        else if(instruction[6:0]==7'b1100011)   // Conditional branches(BEQ,BNE,BLT, BLTU, BGE, BGEU)
            fmt <= B_type;
        else if (instruction[6:0]==7'b0110111 | instruction[6:0]==7'b0010111) // U_type(LUI,AUIPC)
            fmt <= U_type;
        else if (instruction[6:0]==7'b1101111)  // J_type(JAL)
            fmt <= J_type;
        else                                    // Register-Register instructions (ADD,SUB,AND...)
            fmt <= R_type;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if(ce==1) begin                         // Hold state when a bubble is being issued
            NPC_out <= NPC_in;
            instruction_out <= instruction;
            fmt_out <= fmt;
            i_out <= op;
            xu_sel <= xu_int;
            tag_out <= tag_in;
        end

endmodule