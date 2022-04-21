/*!\file xus.sv
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
 * Execution Units.
 *
 * \detailed
 * All Execution units are now in a single file.
 */

import my_pkg::*;

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    ADDER                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module adderUnit (
    input logic         clk,
    input logic [31:0]  opA,
    input logic [31:0]  opB,
    input instruction_type i,
    output logic [31:0] result_out);

    logic [31:0] result;

    always_comb
        if(i==OP3)                              // Set if opA is less than opB (SLT)
            if($signed(opA) < $signed(opB))
                result <= 32'b1;
            else
                result <= 32'b0;

        else if(i==OP2)                         // Set if opA is less than opB UNSIGNED (SLTU)
            if($unsigned(opA) < $unsigned(opB))
                result <= 32'b1;
            else
                result <= 32'b0;

        else if(i==OP1)                         // SUBTRACT (SUB)
            result <= opA - opB;

        else                                    // ADD (ADD,ADDI and AUIPC)
            result <= opA + opB;

    always @(posedge clk)
        result_out <= result;

endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    BRANCH                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module branchUnit (
    input logic         clk,
    input logic [31:0]  opA,                        // In JALR is used to calculate the target and in conditional is used as condition
    input logic [31:0]  opB,                        // In JALR is used to calculate the target and in conditional is used as condition
    input logic [31:0]  offset,                     // Immediate OFFSET is added to PC value
    input logic [31:0]  NPC,                        // PC value
    input instruction_type i,                       // Instruction Type
    output logic [31:0] result_out,                 // Branch target
    output logic [31:0] result_jal,                 // Return addres to a JAL instruction (NPC+4)
    output logic        jump_out,                   // Signal that indicate a jump/branch
    output logic        we_out);                    // Wrtie enable to register bank (used only in JAL)

    logic [31:0]        result, sum;
    logic               jump, we_int;

///////////////////////////////////////////////// Result assign /////////////////////////////////////////////////////////////////////////////////////
    assign sum = opA + opB;                         // Generates the JALR target

    always_comb
        if(i==OP6)                                  // JAL
            result <= sum;                          // Branch target is Sum of opA and opB

        else if(i==OP7) begin                       // JALR
            result[31:1] <= sum[31:1];              // Branch target is opA+opB with
            result[0]<=0;                           // The less significant digit in 0

        end else                                    // Conditional Branches
            result <= NPC + offset;                 // Branch target is PC + immediate

///////////////////////////////////////////////// Genarates the branch signal ///////////////////////////////////////////////////////////////////////
    always_comb
      if(i==OP0)                                    // Branch if equals (BEQ)
        jump <= (opA == opB);
      else if(i==OP1)                               // Branch if not equal (BNE)
        jump <= (opA != opB);
      else if(i==OP2)                               // Branch if less than (BLT)
        jump <= ($signed(opA) < $signed(opB));
      else if(i==OP3)                               // Branch if less than unsigned (BLTU)
        jump <= ($unsigned(opA) < $unsigned(opB));
      else if(i==OP4)                               // Branch if greather or equals than (BGE)
        jump <= ($signed(opA) >= $signed(opB));
      else if(i==OP5)                               // Branch if greather or equals than unsigned (BGEU)
        jump <= ($unsigned(opA) >= $unsigned(opB));
      else if(i==OP6 || i==OP7)                     // Unconditional Branches
        jump <= 1;
      else
        jump <= 0;

///////////////////////////////////////////////// Write enable signal generator /////////////////////////////////////////////////////////////////////
    always_comb                                     // Register write enable is 1 in JAL and JALR instructions
        if(i==OP6 || i==OP7)
            we_int <= '1;
        else 
            we_int <= '0;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
   always @(posedge clk) begin
        result_out <= result;
        result_jal <= NPC+4;
        jump_out <= jump;
        we_out <= we_int;
     end

endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    BYPASS                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module bypassUnit (                    // LUI, NOP and INVALID
    input logic         clk,
    input logic [31:0]  opA,
    output logic [31:0] result_out);

    always @(posedge clk)
        result_out <= opA;

endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    LOGIC                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module logicUnit (
    input logic         clk,
    input logic [31:0]  opA,
    input logic [31:0]  opB,
    input instruction_type i,
    output logic [31:0] result_out);

    logic [31:0] result;

    always_comb
        if(i==OP0)                      // XOR
            result <= opA ^ opB;
        else if(i==OP1)                 // OR
            result <= opA | opB;
        else                            // AND
            result <= opA & opB;

    always @(posedge clk)
        result_out <= result;

endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    MEMORY                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module memoryUnit (
    input logic         clk,
    input logic [31:0]  opA,                            // Base Address
    input logic [31:0]  opB,                            // Offset
    input logic [31:0]  data,                           // Data to be Written in memory
    input instruction_type i,                           // Instruction type
    output logic [31:0] read_address,                   // Read Memory Address
    output logic        read,                           // Signal that allows memory read
    input logic [31:0]  DATA_in,                        // Data received from memory
    output logic [31:0] write_address,                  // Adrress to Write in memory
    output logic [31:0] DATA_wb,                        // Data to be Written in Register Bank or in memory
    output logic        write,                          // Signal that allows memory write
    output logic [1:0]  size,                           // Signal that indicates the size of Write in memory(byte(1),half(2),word(4))
    output logic        we_out);                        // Write enable signal to register bank, in Stores=0 and in Loads=1

    logic write_int, we_int;
    logic [31:0] DATA_write, write_address_2;
    logic [1:0] size_int;

///////////////////////////////////// generate all signals for read or write ////////////////////////////////////////////////////////////////////////
    always_comb begin
        if(i==OP0 | i==OP1) begin                        // Load Byte signed and unsigned (LB | LBU)
            write_int <= 0;
            read <= 1;
            DATA_write <= '0;
            size_int <= 2'b00;

        end else if(i==OP2 | i==OP3) begin               // Load Half(16b) signed and unsigned (LH | LHU)
            write_int <= 0;
            read <= 1;
            DATA_write <= '0;
            size_int <= 2'b00;

        end else if(i==OP4) begin                        // Load Word(32b) (LW)
            write_int <= 0;
            read <= 1;
            DATA_write <= '0;
            size_int <= 2'b00;

        end else if(i==OP7) begin                       // Store Byte (SB)
            write_int <= 1;
            read <= 0;
            DATA_write[31:8] <= 24'h000000;
            DATA_write[7:0] <= data[7:0];               // Only the less significant byte is fullfilled with data, the rest is fullfilled with zeros
            size_int <= 2'b01;

        end else if(i==OP6) begin                       // Store Half(16b) (SH)
            write_int <= 1;
            read <= 0;
            DATA_write[31:16] <= 16'h0000;    
            DATA_write[15:0] <= data[15:0];             // Only the less significant half is fullfilled with data, the rest is fullfilled with zeros
            size_int <= 2'b10;

        end else if(i==OP5) begin                       // Store Word (SW)
            write_int <= 1;
            read <= 0;
            DATA_write[31:0] <= data[31:0];  
            size_int <= 2'b11;
        end
        //////////////////////////////////////////////
        if(i==OP0 | i==OP1 | i==OP2 | i==OP3 | i==OP4)
            read_address = opA + opB;
        else 
            read_address = '0;
    end

///////////////////////////////////////////////// Data Write Back parsing ///////////////////////////////////////////////////////////////////////////
    always @(posedge clk) begin
        if(i==OP0 | i==OP1) begin                       // LB | LBU
            if(DATA_in[7]==1 & i==OP0)                  // Signal extension
                DATA_wb[31:8] <= 24'hFFFFFF;
            else                                        // 0's extension
                DATA_wb[31:8] <= 24'h000000;
            DATA_wb[7:0] <= DATA_in[7:0];

        end else if(i==OP2 | i==OP3) begin              // LH | LHU
            if(DATA_in[15]==1 & i==OP2)                 // Signal extension
                DATA_wb[31:16] <= 16'hFFFF;
            else                                        // 0's extension
                DATA_wb[31:16] <= 16'h0000; 
            DATA_wb[15:0] <= DATA_in[15:0];

        end else if(i==OP4)                             // LW
            DATA_wb <= DATA_in;

        else                                            // STORES
            DATA_wb <= DATA_write;
    end

///////////////////////////////////////////////// Write enable to register bank ///////////////////////////////////////////////////////////////////////////
    always_comb
        if(i==OP5 || i==OP6 || i==OP7)                  // Stores do not write in regbank
            we_int<='0;
        else
            we_int<='1;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
    always@(posedge clk) begin
        write_address <= opA + opB;
        write <= write_int;
        size <= size_int;
        we_out <= we_int;
    end

endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    SHIFT                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module shiftUnit (
    input logic         clk,
    input logic [31:0]  opA,
    input logic [4:0]   opB,
    input instruction_type i,
    output logic [31:0] result_out);

    logic [31:0] result;

    always_comb 
        if(i==OP0)                                  // Logical Left Shift (SLL)
            result <= opA << opB;
        else if(i==OP1)                             // Logical Right Shift (SRL)
            result <= opA >> opB;
        else                                        // Arithmetic Right Shift  (SRA)
            result <= $signed(opA) >>> opB;

    always @(posedge clk)
        result_out <= result;

endmodule