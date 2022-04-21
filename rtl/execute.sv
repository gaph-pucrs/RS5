/*!\file execute.sv
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
 * Execute Unit is the fourth stage of the processor.
 *
 * \detailed
 * Execute Unit is the fourth stage of the PUCRS-RV processor. At the
 * entry it implements a dispatcher that assigns the operands only to the
 * module responsible for that kind of instruction, the modules are: 
 * 1) Adder 2) Branch 3) Bypass 4) Logic 5) Memory 6) Shift. Each module is
 * defined in a separeted file. These files must be included in this Unit
 * if not compiled separately. At the other end it has a demux that collects
 * the result only from the given module and bypass it to the next stage.
 */

import my_pkg::*;

module execute(
    input logic         clk,
    input logic         reset,
    input logic [31:0]  NPC,                // Operand from Operand Fetch stage
    input logic [31:0]  opA,                //              ||
    input logic [31:0]  opB,                //              ||
    input logic [31:0]  opC,                //              ||
    input instruction_type i,               // Operation selector
    input xu            xu_sel,             // Execute Unit selector
    input logic [3:0]   tag_in,             // Instruction tag
    output logic [31:0] result_out [1:0],   // Results array
    output logic        jump_out,           // Signal that indicates a branch taken
    output logic [3:0]  tag_out,            // Instruction tag
    output logic        we_out,             // Write enable to regbank
    output logic [31:0] read_address,       // Memory Read Address
    output logic        read,               // Allows memory read
    input  logic [31:0] DATA_in,            // Data returned from memory
    output logic [3:0]  write);             // Signal that indicates the write memory operation to retire

    logic jump_int;
    logic [3:0] write_int;
    logic [31:0] adderA, adderB, logicA, logicB, shiftA, branchA, branchB, branchC, memoryA, memoryB, memoryC, bypassB, NPCbranch;
    logic [4:0] shiftB;
    logic [31:0] result [7:0];
    instruction_type adder_i, logic_i, shift_i, branch_i, memory_i, queue_i;
    xu xu_stage2; 

///////////////////////////////////////////////////// Instantiation of execution units  ////////////////////
    adderUnit   adder1 (.clk(clk), .opA(adderA), .opB(adderB), .i(adder_i), .result_out(result[0]));
    logicUnit   logical1 (.clk(clk), .opA(logicA), .opB(logicB), .i(logic_i), .result_out(result[1]));
    shiftUnit   shift1 (.clk(clk), .opA(shiftA), .opB(shiftB), .i(shift_i), .result_out(result[2]));
    branchUnit  branch1 (.clk(clk), .opA(branchA), .opB(branchB), .offset(branchC), .NPC(NPCbranch), .i(branch_i),
                .result_out(result[4]), .result_jal(result[3]), .jump_out(jump_int), .we_out(we_branchUnit));
    memoryUnit  memory1 (.clk(clk), .opA(memoryA), .opB(memoryB), .data(memoryC), .i(memory_i), .read_address(read_address), .read(read),
                .DATA_in(DATA_in), .write_address(result[7]), .DATA_wb(result[6]),  .write(write_int), .we_out(we_memoryUnit));
    bypassUnit  bypassUnit1 (.clk(clk), .opA(bypassB), .result_out(result[5]));
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always@(posedge clk) begin  // Generates a internal second stage to DEMUX operation
        xu_stage2 <= xu_sel;
        tag_out <= tag_in;
    end
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    always_comb begin
      ////////////////////////////////////// adder /////////////////////////////////////////////////////////
        if(xu_sel==adder) begin
            adder_i <= i;
            adderA <= opA;
            adderB <= opB;
        end else begin
            adder_i <= NOTOKEN;
            adderA <= 'Z;
            adderB <= 'Z;
        end
      ////////////////////////////////////// logic /////////////////////////////////////////////////////////
        if (xu_sel==logical) begin
            logic_i <= i;
            logicA <= opA;
            logicB <= opB;
        end else begin
            logic_i <= NOTOKEN;
            logicA <= 'Z;
            logicB <= 'Z;
        end
      ////////////////////////////////////// shift /////////////////////////////////////////////////////////
        if (xu_sel==shifter) begin
            shift_i <= i;
            shiftA <= opA;
            shiftB <= opB[4:0];
        end else begin
            shift_i <= NOTOKEN;
            shiftA <= 'Z;
            shiftB <= 'Z;
        end
      ////////////////////////////////////// branch ////////////////////////////////////////////////////////
        if (xu_sel==branch) begin
            branch_i <= i;
            branchA <= opA;
            branchB <= opB;
            branchC <= opC;
            NPCbranch <= NPC;
        end else begin
            branch_i <= NOTOKEN;
            branchA <= 'Z;
            branchB <= 'Z;
            branchC <= 'Z;
            NPCbranch <= 'Z;
        end
      ////////////////////////////////////// memory ////////////////////////////////////////////////////////
        if (xu_sel==memory) begin
            memory_i <= i;
            memoryA <= opA;
            memoryB <= opB;
            memoryC <= opC;
        end else begin
            memory_i <= NOTOKEN;
            memoryA <= 'Z;
            memoryB <= 'Z;
            memoryC <= 'Z;
        end
      ////////////////////////////////////// bypass ////////////////////////////////////////////////////////
        if(xu_sel==bypass)
            bypassB <= opB;
        else
            bypassB <= 'Z;
        end

///////////////////////////////////////////////// DEMUX ////////////////////////////////////////////////////
    always_comb begin                    // RESULT[0]
        if(xu_stage2==adder)
            result_out[0] <= result[0];
        else if(xu_stage2==logical)
            result_out[0] <= result[1];
        else if(xu_stage2==shifter)
            result_out[0] <= result[2];
        else if(xu_stage2==branch)
            result_out[0] <= result[3];
        else if(xu_stage2==memory)
            result_out[0] <= result[6];
        else
            result_out[0] <= result[5];
   ////////////////////////////////////
        if(xu_stage2==branch)             // RESULT[1]
            result_out[1] <= result[4];
        else if(xu_stage2==memory)
            result_out[1] <= result[7];
        else 
            result_out[1] <= '0;
   ////////////////////////////////////
        if(xu_stage2==branch)             // JUMP_OUT
            jump_out <= jump_int;
        else
            jump_out <= '0;
   ////////////////////////////////////
        if(xu_stage2==memory)             // WRITE
            write <= write_int;
        else
            write <= '0;
   ////////////////////////////////////
        if(xu_stage2==branch)             // WE_OUT
            we_out <= we_branchUnit;
        else if(xu_stage2==memory)
            we_out <= we_memoryUnit;
        else
            we_out <= 1;
    end
endmodule