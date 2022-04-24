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

module decoder #(parameter DEPTH = 2)(
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
    output logic [31:1] wrAddr,                 // Write Address to register bank
    output logic [31:0] opA_out,                // First operand output register
    output logic [31:0] opB_out,                // Second operand output register
    output logic [31:0] opC_out,                // Third operand output register
    output logic [31:0] NPC_out,                // PC operand output register
    output instruction_type i_out,              // Instruction operation (OP0, OP1...)
    output xu           xu_sel,                 // Instruction unity     (adder,shifter...)
    output logic [3:0]  tag_out,                // Instruction Tag
    output logic        hazard,                 // Bubble issue indicator (0 active)
    input logic pipe_clear
    );

    logic [31:0] imed, opA, opB, opC, regD_add, target, instruction, last_inst;
    logic pipe_clear_r;
    wor [31:0] locked;
    logic [31:0] lock_queue[DEPTH];

    fmts fmt;
    i_type i;
    xu xu_int;
    instruction_type op;

///////////////////////////////////////////////// REDECODE INST TEST //////////////////////////////////////////////////////////////
    always @(posedge clk ) begin
        last_inst <= instruction;               // Holds the last cycle instruction
        pipe_clear_r <= pipe_clear;             // Holds the last cycle state
    end

    always_comb
        if (pipe_clear_r == 0)                   // If last cycle had a pipe stall
            instruction = last_inst;             // Re-decode last cycle instruction
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

        else if (instruction[14:12]==3'b000 & instruction[6:0]==7'b0001111) i<=NOP;     // FENCE
        else if (instruction[31:8]==24'h000000 & instruction[7:0]==8'b01110011) i<=NOP;    // ECALL
        else if (instruction[31:8]==24'h001000 & instruction[7:0]==8'b01110011) i<=NOP;    // EBREAK

        else if (instruction[14:12]==3'b001 & instruction[6:0]==7'b1110011) i<=CSRRW;
        else if (instruction[14:12]==3'b010 & instruction[6:0]==7'b1110011) i<=CSRRS;
        else if (instruction[14:12]==3'b011 & instruction[6:0]==7'b1110011) i<=CSRRC;
        else if (instruction[14:12]==3'b101 & instruction[6:0]==7'b1110011) i<=CSRRWI;
        else if (instruction[14:12]==3'b110 & instruction[6:0]==7'b1110011) i<=CSRRSI;
        else if (instruction[14:12]==3'b111 & instruction[6:0]==7'b1110011) i<=CSRRCI;

        else if (instruction[31:0]==32'h00000000) i<=NOP;
        else if (instruction[31:0]==32'h00000013) i<=NOP;

        else i<=INVALID;                        // if the opcodes are not recognized

    always_comb                                 // Execution unit is extracted based on instruction type
        case (i)
            ADD, SUB, SLTU, SLT:                        xu_int <= adder;
            XOR, OR, AND:                               xu_int <= logical;
            SLL, SRL, SRA:                              xu_int <= shifter;
            BEQ, BNE, BLT, BLTU, BGE, BGEU, JAL, JALR:  xu_int <= branch;
            LB, LBU, LH, LHU, LW, SB, SH, SW:           xu_int <= memory;
            CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI:xu_int <= csri;
            default:                                    xu_int <= bypass;
        endcase

    always_comb                                 // Execution operation is extracted based on instruction type
        case (i)
            ADD, XOR, SLL, BEQ, LB, CSRRW:      op<=OP0;
            SUB, OR, SRL, BNE, LBU, LUI, CSRRWI:op<=OP1;
            SLTU, AND, SRA, BLT, LH, CSRRS:     op<=OP2;
            SLT, BLTU, LHU, CSRRSI:             op<=OP3;
            BGE, LW, CSRRC:                     op<=OP4;
            BGEU, SW, CSRRCI:                   op<=OP5;
            JAL, SH:                            op<=OP6;
            JALR, SB:                           op<=OP7;
            default:                            op<=OP0;
        endcase


/////////////////////////////////////////////////  Decodes the instruction format ///////////////////////////////////////////////////////////////////
    always_comb
        case (instruction[6:0])
            7'b0010011, 7'b1100111, 7'b0000011:     fmt <= I_type;
            7'b0100011:                             fmt <= S_type;
            7'b1100011:                             fmt <= B_type;
            7'b0110111, 7'b0010111:                 fmt <= U_type;
            7'b1101111:                             fmt <= J_type;
            7'b1110011:                             fmt <= CSR_type;
            default:                                fmt <= R_type;
        endcase

///////////////////////////////////////////////// Read Addresses to RegBank /////////////////////////////////////////////////////////////////////////
    assign regA_add = instruction[19:15];
    assign regB_add = instruction[24:20];

///////////////////////////////////////////////// Extract the immediate based on instruction type ///////////////////////////////////////////////////
    always_comb
        case(fmt)
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
            
            CSR_type: begin
                        imed[21:17] <= instruction[11:7];
                        imed[16:12] <= instruction[19:15];
                        imed[11:0]  <= instruction[31:20];
            end

            default:      imed[31:0] <= '0;
        endcase

///////////////////////////////////////////////// Control of the exits based on format //////////////////////////////////////////////////////////////
    always_comb begin
        opA <= (fmt==U_type | fmt==J_type) ? NPC   : dataA;
        opB <= (fmt==R_type | fmt==B_type) ? dataB : imed;
        opC <= (fmt==S_type)               ? dataB : imed;
    end

////////////////////////////////////////////////// Conversion to one-hot codification ///////////////////////////////////////////////////////////////
    always_comb begin
        regD_add <= 1 << instruction[11:7];
        ///////////////////////////////////
        if(xu_int==memory && (op==OP5 | op==OP6 | op==OP7)) // [0] Indicates a pending write in memory, used to avoid data hazards in memory
            regD_add[0] <= 1;
        else
            regD_add[0] <= 0;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always @(*)
        if(!hazard)                                         // If a bubble is being issued then regD=0 is inserted in queue (to avoid deadlock)
            target <= '0;
        else                                                // Otherwise the instruction regD is the target to be inserted in queue
            target <=regD_add; 

////////////////////////////////////////////////// REGISTER LOCK QUEUE //////////////////////////////////////////////////////////////////////////////
    always @(posedge clk or negedge reset)  
        if(!reset)                                          // Reset clears the queue
            for (int j = 0; j < DEPTH; j++)
                lock_queue[j] <= '0;
        else begin
            for (int k = 0; k < DEPTH-1; k++)
                lock_queue[k+1] <= lock_queue[k];           // Move the queue forward
            lock_queue[0] <= target;                        // and inserts a new Target in the queue 
        end

    generate                                                // Assign to wire or (wor) signal to generate the mask of locked registers (register with pending writes)
    for(genvar w = 0; w < DEPTH; w++) 
        assign locked = lock_queue[w];
    endgenerate

    assign wrAddr = lock_queue[DEPTH-1][31:1] & {32{&we}};  // Write Address is the last position with a bitwise AND with the write enable signal

///////////////////////////////////////////////// HAZARD SIGNAL GENERATION //////////////////////////////////////////////////////////////////////////
    always_comb
        if(locked[0]==1 && xu_int==memory && (op==OP0 | op==OP1 | op==OP2 | op==OP3 | op==OP4)) //Can't read from memory if a write in memory is pending
            hazard <= 0;
        else if(locked[regA_add]==1 || locked[regB_add]==1) // Checks if rs1 and rs2 are not in the list of pending write registers
            hazard <= 0;
        else                                                // No Hazards identified
            hazard <= 1;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk or negedge reset)
        if (!reset) begin                                   // Reset
            opA_out <= '0;
            opB_out <= '0;
            opC_out <= '0;
            NPC_out <= '0;
            i_out <= OP0;
            xu_sel <= bypass;
            tag_out <= '0;

         end else if(pipe_clear==0) begin                       // Propagate bubble
            opA_out <= '0;
            opB_out <= '0;
            opC_out <= '0;
            NPC_out <= '0;
            i_out <= OP0;
            xu_sel <= bypass;
            tag_out <= '0;

        end else if(pipe_clear==1) begin                        // Propagate instruction
            opA_out <= opA;
            opB_out <= opB;
            opC_out <= opC;
            NPC_out <= NPC;
            i_out <= op;
            xu_sel <= xu_int;
            tag_out <= tag_in;
        end
    
endmodule
