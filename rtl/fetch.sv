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
    input logic         hazard,
    input logic         jump,
    input logic [31:0]  result,
    output logic [31:0] i_address,
    output logic [31:0] NPC,
    output logic [3:0]  tag_out,
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
        else if (jump)
            PC <= result;
        else if (!hazard && !stall)
            PC <= PC_plus4;

    assign PC_plus4 = PC + 4;

///////////////////////////////////////////////// Sensitive Outputs /////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if(!hazard && !stall)
            NPC <= PC;

///////////////////////////////////////////////// TAG Calculator ////////////////////////////////////////////////////////////////////////////////////
    always @(posedge clk)
        if (reset) begin
            curr_tag <= 0;
            next_tag <= 0;
        end else if (jump | EXCEPTION_RAISED | MACHINE_RETURN | Interrupt_ACK)
            next_tag <= curr_tag + 1;
        else if (!hazard && !stall)
            curr_tag <= next_tag;

///////////////////////////////////////////////// Non-Sensitive Outputs /////////////////////////////////////////////////////////////////////////////
    assign i_address = PC;
    assign tag_out = curr_tag;

endmodule