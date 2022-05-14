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
    output logic [31:0] result_jal,                 // Return csr_addres to a JAL instruction (NPC+4)
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

module LSUnit (
    input logic [31:0]  opA,                            // Base csr_address
    input logic [31:0]  opB,                            // Offset
    input logic [31:0]  data,                           // Data to be Written in memory
    input instruction_type i,                           // Instruction type
    output logic [31:0] read_address,                   // Read Memory csr_address
    output logic        read,                           // Signal that allows memory read
    output logic [31:0] write_address,                  // Adrress to Write in memory
    output logic [31:0] DATA_wb,                        // Data to be Written in Register Bank or in memory
    output logic [3:0]  we_mem,                           // Signal that indicates the size of Write in memory(byte(1),half(2),word(4))
    output logic        we_rb);                         // Write enable signal to register bank, in Stores=0 and in Loads=1

    logic [31:0] DATA_write;

///////////////////////////////////// generate all signals for read or write ////////////////////////////////////////////////////////////////////////
    always_comb begin
        if(i==OP0 | i==OP1) begin                        // Load Byte signed and unsigned (LB | LBU)
            read <= 1;
            DATA_write <= '0;
            we_mem <= 4'b0000;

        end else if(i==OP2 | i==OP3) begin               // Load Half(16b) signed and unsigned (LH | LHU)
            read <= 1;
            DATA_write <= '0;
            we_mem <= 4'b0000;

        end else if(i==OP4) begin                        // Load Word(32b) (LW)
            read <= 1;
            DATA_write <= '0;
            we_mem <= 4'b0000;

        end else if(i==OP7) begin                       // Store Byte (SB)
            read <= 0;
            DATA_write[31:8] <= 24'h000000;
            DATA_write[7:0] <= data[7:0];               // Only the less significant byte is fullfilled with data, the rest is fullfilled with zeros
            we_mem <= 4'b0001;

        end else if(i==OP6) begin                       // Store Half(16b) (SH)
            read <= 0;
            DATA_write[31:16] <= 16'h0000;    
            DATA_write[15:0] <= data[15:0];             // Only the less significant half is fullfilled with data, the rest is fullfilled with zeros
            we_mem <= 4'b0011;

        end else if(i==OP5) begin                       // Store Word (SW)
            read <= 0;
            DATA_write[31:0] <= data[31:0];  
            we_mem <= 4'b1111;

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
    input logic [31:0]  opA,            // DATA FROM REGBANK 
    input logic [31:0]  instruction,
    input instruction_type i,
    input Privilege privilege,
    output logic csr_rd_en,
    output logic csr_wr_en,
    output csr_ops csr_op,
    output logic [11:0] csr_addr,
    output logic [31:0] csr_data,
    output logic csr_exception);

    logic csr_rd_en_int, csr_wr_en_int;
    logic [4:0] rd, rs1;
    logic [11:0] csr_addr_int;

    assign rd  = instruction[11:7];
    assign rs1 = instruction[19:15];
    assign csr_addr_int = instruction[31:20];

    assign csr_rd_en = csr_rd_en_int & !csr_exception;
    assign csr_wr_en = csr_wr_en_int & !csr_exception;

    always_comb begin
        if (i==OP0 || i==OP1) begin     // CSSRW or CSSRWI
            csr_wr_en_int = 1;
            if(rd==0)
                csr_rd_en_int = 0;
            else
                csr_rd_en_int = 1;

        end else if (i==OP2 || i==OP3 || i==OP4 || i==OP5) begin     // CSRRS/C and CSRRS/CI
            csr_rd_en_int = 1;
            if(rs1==0)
                csr_wr_en_int = 0;
            else
                csr_wr_en_int = 1;
        
        end else begin
            csr_rd_en_int <= 0;
            csr_wr_en_int <= 0;
        end
    end

    always_comb begin
        csr_addr <= csr_addr_int;
        
        if(i==OP0 || i==OP2 || i==OP4)
            csr_data <= opA;
        else
            csr_data <= '0 & rs1;
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

    
    always_comb begin
        // Raise exeption if CSR is read only and write enable is true
        if((csr_addr[11:10] == 2'b11) && (csr_wr_en_int == 1))
            csr_exception <= 1;
        // Check Level privileges
        else if(csr_addr[9:8] < privilege)
            csr_exception <= 1;
        // No exception is raised
        else
            csr_exception <= 0;
    end
endmodule
