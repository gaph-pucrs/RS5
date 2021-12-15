/*!\file operandFetch.sv
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
 * Operand Fetch stage of PUCRS-RV processor.
 *
 * \detailed
 * The operand Fetch stage is responsible for fetching the
 * operands in the register bank, calculate the imediate operand
 * and also have a mechanism of hazard detection, if a hazard is
 * detected (e.g. write after read) a bubble is issued. The bubble
 * consists in a NOP (NO Operation) instruction.
 */

import my_pkg::*;

module operandFetch #(parameter DEPTH = 2)(
    input logic clk,
    input logic reset,
    input logic we,
    input fmts          fmt,                    // Instruction Format
    input logic [31:0]  instruction,            // Object code of the instruction to extract the immediate operand
    input logic [31:0]  NPC,                    // Bypassed to execute unit as an operand
    input instruction_type i,                   // Instruction operation (OP0, OP1...)
    input xu            xu_sel_in,              // Instruction unity     (adder,shifter...)
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
    output logic        bubble);                // Bubble issue indicator (0 active)

    logic [31:0] imed, opA, opB, opC, regD_add, target;
    wor [31:0] locked;
    logic [31:0] lock_queue[DEPTH];

///////////////////////////////////////////////// Extract the immediate based on instruction type ///////////////////////////////////////////////////
    always_comb
        case(fmt)
            I_type: begin
                        imed[31:11] = (instruction[31]==0) ? '0 : '1;
                        imed[10:0] <= instruction[30:20];
                    end

            S_type: begin
                        imed[31:11] = (instruction[31]==0) ? '0 : '1;
                        imed[10:5] <= instruction[30:25];
                        imed[4:0]  <= instruction[11:7];
                    end

            B_type: begin
                        imed[31:12] = (instruction[31]==0) ? '0 : '1;
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
                        imed[31:20] = (instruction[31]==0) ? '0 : '1;
                        imed[19:12] <= instruction[19:12];
                        imed[11] <= instruction[20];
                        imed[10:5] <= instruction[30:25];
                        imed[4:1] <= instruction[24:21];
                        imed[0] <= 0;
                    end

            default:      imed[31:0] <= '0;
        endcase

///////////////////////////////////////////////// Read Addresses to RegBank /////////////////////////////////////////////////////////////////////////
    assign regA_add = instruction[19:15];
    assign regB_add = instruction[24:20];

///////////////////////////////////////////////// Control of the exits based on format //////////////////////////////////////////////////////////////
    always_comb
        if(fmt==I_type) begin                               // addi, slti, andi, ori, xori, slli, slri, srai, LOADS, JALR
            opA <= dataA;
            opB <= imed;
            opC <= 32'h00000000;

        end else if(fmt==U_type | fmt==J_type) begin        // auipc, lui, jal
            opA <= NPC;
            opB <= imed;
            opC <= 32'h00000000;

        end else if(fmt==S_type) begin                      // STORES
            opA <= dataA;
            opB <= imed;
            opC <= dataB;

        end else if(fmt==R_type | fmt==B_type) begin        // Conditional branches and register-register instructions
            opA <= dataA;
            opB <= dataB;               
            opC <= imed;

        end else begin                                      //nop, invalid
            opA <= imed;
            opB <= 32'h00000000;
            opC <= 32'h00000000;   
        end

////////////////////////////////////////////////// Conversion to one-hot codification ///////////////////////////////////////////////////////////////
    always_comb begin
        regD_add <= 1 << instruction[11:7];
    ////////////////////////////////
        if(xu_sel_in==memory && (i==OP5 | i==OP6 | i==OP7)) // [0] Indicates a pending write in memory, used to avoid data hazards in memory
            regD_add[0] <= 1;
        else
            regD_add[0] <= 0;
    end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always @(*)
        if(!bubble)                                         // If a bubble is being issued then regD=0 is inserted in queue (to avoid deadlock)
            target <= '0;
        else                                                // Otherwise the instruction regD is the target to be inserted in queue
            target <=regD_add; 

////////////////////////////////////////////////// REGISTER LOCK QUEUE //////////////////////////////////////////////////////////////////////////////
    always @(posedge clk or negedge reset)  
        if(!reset)                                          // Reset clears the queue
            for (int i = 0; i < DEPTH; i++)
                lock_queue[i] <= '0;
        else begin
            for (int j = 0; j < DEPTH-1; j++)
                lock_queue[j+1] <= lock_queue[j];           // Move the queue forward
            lock_queue[0] <= target;                        // and inserts a new Target in the queue 
        end

    generate                                                // Assign to wire or (wor) signal to generate the mask of locked registers (register with pending writes)
    for(genvar w = 0; w < DEPTH; w++) 
        assign locked = lock_queue[w];
    endgenerate

    assign wrAddr = lock_queue[DEPTH-1][31:1] & {32{&we}};  // Write Address is the last position with a bitwise AND with the write enable signal

///////////////////////////////////////////////// BUBBLE SIGNAL GENERATION //////////////////////////////////////////////////////////////////////////
    always_comb
        if(locked[0]==1 && xu_sel_in==memory && (i==OP0 | i==OP1 | i==OP2 | i==OP3 | i==OP4)) //Can't read from memory if a write in memory is pending
            bubble <= 0;
        else if(locked[regA_add]==1 || locked[regB_add]==1) // Checks if rs1 and rs2 are not in the list of pending write registers
            bubble <= 0;
        else                                                // No Hazards identified
            bubble <= 1;

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

         end else if(bubble==0) begin                       // Propagate bubble
            opA_out <= '0;
            opB_out <= '0;
            opC_out <= '0;
            NPC_out <= '0;
            i_out <= OP0;
            xu_sel <= bypass;
            tag_out <= '0;

        end else if(bubble==1) begin                        // Propagate instruction
            opA_out <= opA;
            opB_out <= opB;
            opC_out <= opC;
            NPC_out <= NPC;
            i_out <= i;
            xu_sel <= xu_sel_in;
            tag_out <= tag_in;
        end

endmodule