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
    input logic [31:0]  opA,
    input logic [31:0]  opB,
    input instruction_type i,
    output logic [31:0] result);

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
endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    BRANCH                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module branchUnit (
    input logic [31:0]  opA,                        // In JALR is used to calculate the target and in conditional is used as condition
    input logic [31:0]  opB,                        // In JALR is used to calculate the target and in conditional is used as condition
    input logic [31:0]  offset,                     // Immediate OFFSET is added to PC value
    input logic [31:0]  NPC,                        // PC value
    input instruction_type i,                       // Instruction Type
    output logic [31:0] result,                 // Branch target
    output logic [31:0] result_jal,                 // Return addres to a JAL instruction (NPC+4)
    output logic        jump,                   // Signal that indicate a jump/branch
    output logic        we);                    // Wrtie enable to register bank (used only in JAL)

    logic [31:0]        sum;

///////////////////////////////////////////////// Result assign /////////////////////////////////////////////////////////////////////////////////////
    assign sum = opA + opB;                         // Generates the JALR target
    assign result_jal = NPC + 4;

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
            we <= '1;
        else 
            we <= '0;
endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    LOGIC                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module logicUnit (
    input logic [31:0]  opA,
    input logic [31:0]  opB,
    input instruction_type i,
    output logic [31:0] result);

    always_comb
        if(i==OP0)                      // XOR
            result <= opA ^ opB;
        else if(i==OP1)                 // OR
            result <= opA | opB;
        else                            // AND
            result <= opA & opB;
endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    MEMORY                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module memoryUnit (
    input logic [31:0]  opA,                            // Base Address
    input logic [31:0]  opB,                            // Offset
    input logic [31:0]  data,                           // Data to be Written in memory
    input instruction_type i,                           // Instruction type
    output logic [31:0] read_address,                   // Read Memory Address
    output logic        read,                           // Signal that allows memory read
    output logic [31:0] write_address,                  // Adrress to Write in memory
    output logic [31:0] DATA_wb,                        // Data to be Written in Register Bank or in memory
    output logic        write,                          // Signal that allows memory write
    output logic [1:0]  size,                           // Signal that indicates the size of Write in memory(byte(1),half(2),word(4))
    output logic        we_rb);                         // Write enable signal to register bank, in Stores=0 and in Loads=1

    logic write_int, we_int;
    logic [31:0] DATA_write, write_address_2;
    logic [1:0] size_int;

///////////////////////////////////// generate all signals for read or write ////////////////////////////////////////////////////////////////////////
    always_comb begin
        if(i==OP0 | i==OP1) begin                        // Load Byte signed and unsigned (LB | LBU)
            write <= 0;
            read <= 1;
            DATA_write <= '0;
            size <= 2'b00;

        end else if(i==OP2 | i==OP3) begin               // Load Half(16b) signed and unsigned (LH | LHU)
            write <= 0;
            read <= 1;
            DATA_write <= '0;
            size <= 2'b00;

        end else if(i==OP4) begin                        // Load Word(32b) (LW)
            write <= 0;
            read <= 1;
            DATA_write <= '0;
            size <= 2'b00;

        end else if(i==OP7) begin                       // Store Byte (SB)
            write <= 1;
            read <= 0;
            DATA_write[31:8] <= 24'h000000;
            DATA_write[7:0] <= data[7:0];               // Only the less significant byte is fullfilled with data, the rest is fullfilled with zeros
            size <= 2'b01;

        end else if(i==OP6) begin                       // Store Half(16b) (SH)
            write <= 1;
            read <= 0;
            DATA_write[31:16] <= 16'h0000;    
            DATA_write[15:0] <= data[15:0];             // Only the less significant half is fullfilled with data, the rest is fullfilled with zeros
            size <= 2'b10;

        end else if(i==OP5) begin                       // Store Word (SW)
            write <= 1;
            read <= 0;
            DATA_write[31:0] <= data[31:0];  
            size <= 2'b11;
        end
        //////////////////////////////////////////////
        if(i==OP0 | i==OP1 | i==OP2 | i==OP3 | i==OP4)
            read_address = opA + opB;
        else 
            read_address = '0;
    end

///////////////////////////////////////////////// Write enable to register bank ///////////////////////////////////////////////////////////////////////////
    always_comb
        if(i==OP5 || i==OP6 || i==OP7)                  // Stores do not write in regbank
            we_rb<='0;
        else
            we_rb<='1;

///////////////////////////////////////////////// Output registers //////////////////////////////////////////////////////////////////////////////////
    assign write_address = opA + opB;
    assign DATA_wb = DATA_write;
endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    SHIFT                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module shiftUnit (
    input logic [31:0]  opA,
    input logic [4:0]   opB,
    input instruction_type i,
    output logic [31:0] result);

    always_comb 
        if(i==OP0)                                  // Logical Left Shift (SLL)
            result <= opA << opB;
        else if(i==OP1)                             // Logical Right Shift (SRL)
            result <= opA >> opB;
        else                                        // Arithmetic Right Shift  (SRA)
            result <= $signed(opA) >>> opB;
endmodule

///////////////////////////////////////////////////////////////////////////////////////////////////
///                                    CSR                                                      ///
///////////////////////////////////////////////////////////////////////////////////////////////////

module csrUnit (
    input logic [31:0]  opA, // DATA FROM RS1
    input logic [31:0]  opB, // ADDRs
    input instruction_type i,
    output logic rd_en,
    output logic wr_en,
    output csr_ops csr_op,
    output logic [11:0] csr_add,
    output logic [31:0] data);

    logic [4:0] rd, rs1;

    assign rd  = opB[21:17];
    assign rs1 = opB[16:12];

    always_comb begin
        if (i==OP0 || i==OP1) begin     // CSSRW or CSSRWI
            wr_en = 1;
            if(rd==0)
                rd_en = 0;
            else
                rd_en = 1;

        end else if (i==OP2 || i==OP3 || i==OP4 || i==OP5) begin     // CSRRS/C and CSRRS/CI
            rd_en = 1;
            if(rs1==0)
                wr_en = 0;
            else
                wr_en = 1;
        
        end else begin
            rd_en <= 0;
            wr_en <= 0;
        end
    end

    always_comb begin
        csr_add <= opB[11:0];
        
        if(i==OP0 || i==OP2 || i==OP4)
            data <= opA;
        else
            data <= '0 & rs1;
    end

    always_comb 
        if(i==OP0 || i==OP1)               // WRITE
            csr_op <= write;
        else if(i==OP2 || i==OP3)          // SET
            csr_op <= set;
        else if(i==OP4 || i==OP5)          // CLEAR
            csr_op <= clear;
        else                               // NONE
            csr_op <= none;

endmodule