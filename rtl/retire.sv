/*!\file retire.sv
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
 * Retire is the last stage of the PUCRS-RV processor.
 *
 * \detailed
 * Retire is the last stage of the PUCRS-RV processor and is reponsible for closing the loops.
 * First compares the instruction tag and the internal tag, if they does not match then the 
 * instruction is killed and no operation is performed, otherwise it sends the data received 
 * to the designed outputs, they are: 
 * 1) Register bank write data and write enable
 * 2) Branch address (New_PC)
 * 3) Memory write signals (Data, address and write enable)
 */

import my_pkg::*;

module retire(
    input logic         clk,
    input logic         reset,
    input logic [31:0]  result [1:0],               // Results array
    input logic         jump,                       // Jump signal from branch unit 
    input logic         we,                         // Write enable from Execute(based on instruction type)
    input logic [3:0]   tag_in,                     // Instruction tag to be compared with retire tag
    input logic [3:0]   write_in,                   // Write enable memory
    output logic        reg_we,                     // Write Enable to Register Bank
    output logic [31:0] WrData,                     // WriteBack data to Register Bank
    output logic        jump_out,                   // Jump signal to Fetch Unit
    output logic [31:0] New_pc,                     // Branch target to fetch Unit
    output logic [31:0] write_address,              // Memory write address
    output logic [31:0] DATA_out,                   // Memory data to be written
    output logic [3:0]  write);                      // Memory write enable

    logic [31:0] data;
    logic [3:0] next_tag;
    logic [3:0] curr_tag;
    logic killed;

///////////////////////////////////////////////// Assign to Register Bank Write Back ////////////////////////////////////////////////////////////////
    assign WrData = result[0];

///////////////////////////////////////////////// Killed signal generation //////////////////////////////////////////////////////////////////////////
    always_comb
        if (curr_tag != tag_in)                     // If tags don't match then kill the instruction
            killed <= 1;
        else
            killed <= 0;

///////////////////////////////////////////////// TAG control based on signals Jump and Killed //////////////////////////////////////////////////////
    always @(posedge clk or negedge reset)
        if(!reset)
            curr_tag <= 0;
        else if (jump_out==1 && killed==0)          // If a jump was taken and the tag is correct then increases the internal tag
            curr_tag <= curr_tag + 1;

///////////////////////////////////////////////// Flow Control //////////////////////////////////////////////////////////////////////////////////////
    always_comb
        if(killed)                                  // If tags mismatch then do not write back
          reg_we <= 0;
        else                                        // Otherwise depends on instruction type
          reg_we <= we;

///////////////////////////////////////////////// PC Flow control signal generation /////////////////////////////////////////////////////////////////
    always_comb
        if (jump==1 && killed==0) begin             // If it is a branch instruction and tag is valid then effectuate the branch
            New_pc <= result[1];
            jump_out <= 1;
        end else begin                              // Otherwise do nothing
            New_pc <= '0;
            jump_out <= '0;
        end
///////////////////////////////////////////////// Memory write control //////////////////////////////////////////////////////////////////////////////
    always@(posedge clk)
        if(write_in!=0 && killed==0) begin          // If is a Store instruction and tag is valid then effectuate the Write
            write <= write_in;
            write_address <= result[1];
            DATA_out <= result[0];
        end else begin                              // Otherwise do nothing
            write <= 'Z;
            write_address <= 'Z;
            DATA_out <= 'Z;
        end

endmodule