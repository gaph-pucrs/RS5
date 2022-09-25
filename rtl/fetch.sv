/*!\file fetch.sv
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
 * Fetch Unit is the first stage of the processor and fetch the instruction in memory.
 *
 * \detailed
 * Fetch Unit is the first stage of the PUCRS-RV processor. It has an
 * internal loop that contains the Program Counter(PC) that is increased by four 
 * on a new clock cycle or is replaced by a new address in case of a branch. 
 * It has a internal tag calculator that is increased in branchs and mantained
 * in regular flows, the tag leaves the unit with the instruction fetched.
 */

module fetch  #(parameter start_address='0)(  //Generic start address
    input logic         clk,
    input logic         reset,
    input logic         stall,
    input logic         hazard,                         // Chip Enable is used to bubble propagation (0 means hold state because a bubble is being issued)
    input logic         jump,                           // Indicates when a branch must be taken
    input logic [31:0]  result,                         // The branch address from retire
    output logic [31:0] i_address,                      // Instruction address in memory (PC)
    output logic [31:0] NPC,                            // PC value is propagated to be used as an operand in some instructions
    output logic [3:0]  tag_out,                        // Instruction Tag stream
    ///////////////////////////////
    input logic [31:0]  mtvec,
    input logic [31:0]  mepc,
    input logic         EXCEPTION_RAISED,
    input logic         MACHINE_RETURN,
    input logic         Interrupt_ACK
);

    logic [31:0] PC, PC_plus4;
    logic [3:0] next_tag, curr_tag;

///////////////////////////////////////////////// PC Control ////////////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if (reset)
            PC <= start_address;
        else if (MACHINE_RETURN)                                   
            PC <= mepc;
        else if (EXCEPTION_RAISED || Interrupt_ACK)                                   
            PC <= mtvec;
        else if (jump)                                   // If a branch was taken then PC receives a new value from retire unit
            PC <= result;
        else if (!hazard && !stall)                      // If there is no bubble being issued: PC <= PC+4
            PC <= PC_plus4;                              // Otherwise(when bubble==0) holds the current value

    assign PC_plus4 = PC + 4;

///////////////////////////////////////////////// Sensitive Outputs /////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if(!hazard && !stall)                            // If there is no bubble then the internal signals are assigned to the outputs
            NPC <= PC;

///////////////////////////////////////////////// TAG Calculator ////////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if (reset) begin
            curr_tag <= 0;
            next_tag <= 0;
        end else if (jump | EXCEPTION_RAISED | MACHINE_RETURN | Interrupt_ACK)  // If a Branch is taken then the instruction tag is increased
            next_tag <= curr_tag + 1;
        else if (!hazard && !stall)                      // It is increased only when a bubbles is not being propagated
            curr_tag <= next_tag;

///////////////////////////////////////////////// Non-Sensitive Outputs /////////////////////////////////////////////////////////////////////////////
    assign i_address = PC;
    assign tag_out = curr_tag;

endmodule