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
    input logic         exception_in,
    input logic [31:0]  instruction_in,
    input logic [31:0]  NPC,                // Operand from Operand Fetch stage
    input logic [31:0]  opA,                //              ||
    input logic [31:0]  opB,                //              ||
    input logic [31:0]  opC,                //              ||
    input instruction_type i,               // Operation selector
    input xu            xu_sel,             // Execute Unit selector
    input logic [3:0]   tag_in,             // Instruction tag
    output logic        LS_operation,
    output logic [31:0] instruction_out,
    output logic [31:0] NPC_out,
    output instruction_type i_out,
    output logic [31:0] result_out [1:0],   // Results array
    output logic        jump_out,           // Signal that indicates a branch taken
    output logic [3:0]  tag_out,            // Instruction tag
    output logic        we_out,             // Write enable to regbank
    output logic [31:0] read_address,       // Memory Read Address
    output logic        read,               // Allows memory read
    output logic [3:0]  we_mem,             // Signal that indicates the write memory operation to retire
    output logic        exception_out,
    //////////////////////////////////
    output logic csr_rd_en,
    output logic csr_wr_en,
    output csr_ops csr_op,
    output logic [11:0] csr_addr,
    output logic [31:0] csr_data
    );
    
    logic jump_int;
    logic csr_exception;
    logic [3:0] we_mem_int;
    logic [31:0] result [7:0];
    instruction_type adder_i, logic_i, shift_i, branch_i, memory_i, csrU_i;

///////////////////////////////////////////////////// Instantiation of execution units  ////////////////////
    adderUnit   adder1 (.opA(opA), .opB(opB), .i(adder_i), .result(result[0]));
    logicUnit   logical1 (.opA(opA), .opB(opB), .i(logic_i), .result(result[1]));
    shiftUnit   shift1 (.opA(opA), .opB(opB[4:0]), .i(shift_i), .result(result[2]));
    branchUnit  branch1 (.opA(opA), .opB(opB), .offset(opC), .NPC(NPC), .i(branch_i),
                .result(result[4]), .result_jal(result[3]), .jump(jump_int), .we(we_branchUnit));
    LSUnit      memory1 (.opA(opA), .opB(opB), .data(opC), .i(memory_i), 
                .read_address(read_address), .read(read),
                .write_address(result[7]), .DATA_wb(result[6]),  .we_mem(we_mem_int), .we_rb(we_memoryUnit));
    csrUnit     CSRaccess (.opA(opA), .instruction(instruction_in), .i(csrU_i), .privilege(2'b11), .csr_exception(csr_exception),
                .csr_rd_en(csr_rd_en), .csr_wr_en(csr_wr_en), .csr_op(csr_op), .csr_addr(csr_addr), .csr_data(csr_data) );

    assign result[5] = opB; // bypass

////////////////////////////////////////////////////////////////////////////////////////////////////////////
    assign adder_i  = (xu_sel==adder)   ? i : NOTOKEN;
    assign logic_i  = (xu_sel==logical) ? i : NOTOKEN;
    assign shift_i  = (xu_sel==shifter) ? i : NOTOKEN;
    assign branch_i = (xu_sel==branch)  ? i : NOTOKEN;
    assign memory_i = (xu_sel==memory)  ? i : NOTOKEN;
    assign csr_i    = (xu_sel==csri)    ? i : NOTOKEN;

///////////////////////////////////////////////// DEMUX ////////////////////////////////////////////////////
    always@(posedge clk) begin                    // RESULT[0]
        if(xu_sel==adder)
            result_out[0] <= result[0];
        else if(xu_sel==logical)
            result_out[0] <= result[1];
        else if(xu_sel==shifter)
            result_out[0] <= result[2];
        else if(xu_sel==branch)
            result_out[0] <= result[3];
        else if(xu_sel==memory)
            result_out[0] <= result[6];
        else
            result_out[0] <= result[5];
   ////////////////////////////////////
        if(xu_sel==branch)             // RESULT[1]
            result_out[1] <= result[4];
        else if(xu_sel==memory)
            result_out[1] <= result[7];
        else 
            result_out[1] <= '0;
   ////////////////////////////////////
        if(xu_sel==branch)             // JUMP_OUT
            jump_out <= jump_int;
        else
            jump_out <= '0;
   ////////////////////////////////////
        if(xu_sel==memory)  begin           // WRITE
            LS_operation <= 1;            
            we_mem <= we_mem_int;
        end else begin
            LS_operation <= 0;  
            we_mem <= '0;
        end
   ////////////////////////////////////
        if(xu_sel==branch)             // WE_OUT
            we_out <= we_branchUnit;
        else if(xu_sel==memory)
            we_out <= we_memoryUnit;
        else
            we_out <= 1;
   ////////////////////////////////////
        tag_out <= tag_in;
        i_out <= i;
        instruction_out <= instruction_in;
        NPC_out <= NPC;
        exception_out <= exception_in | csr_exception;
    end

endmodule