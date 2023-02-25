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

//--------------------------------------------------------------------------------------------------
// ADDER UNIT
//--------------------------------------------------------------------------------------------------

module adderUnit (
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   operationType_e     operation_i,

    output  logic [31:0]        result_o
);

    always_comb begin
        if (operation_i == OP3) begin
            if ($signed(first_operand_i) < $signed(second_operand_i)) begin
                result_o <= 32'b1;
            end
            else begin
                result_o <= 32'b0;
            end
        end
        else if (operation_i == OP2) begin
            if ($unsigned(first_operand_i) < $unsigned(second_operand_i)) begin
                result_o <= 32'b1;
            end
            else begin
                result_o <= 32'b0;
            end
        end
        else if (operation_i == OP1) begin
            result_o <= first_operand_i - second_operand_i;
        end
        else begin
            result_o <= first_operand_i + second_operand_i;
        end
    end
endmodule

//--------------------------------------------------------------------------------------------------
// BRANCH UNIT
//--------------------------------------------------------------------------------------------------

module branchUnit (
    input   logic [31:0]        first_operand_i,                // In JALR is used to calculate the target and in conditional is used as condition
    input   logic [31:0]        second_operand_i,               // In JALR is used to calculate the target and in conditional is used as condition
    input   logic [31:0]        offset_i,                       // Immediate OFFSET is added to PC value
    input   logic [31:0]        pc_i,                           // PC value
    input   operationType_e     operation_i,                    // Operation Type

    output  logic [31:0]        result_o,                       // Branch target
    output  logic [31:0]        result_jal_o,                   // Return csr_addres to a JAL instruction (pc_i+4)
    output  logic               jump_o,                         // Signal that indicate a jump/branch
    output  logic               write_enable_o                  // Write enable to register bank (used only in JAL)
);

    logic [31:0]        sum;

//////////////////////////////////////////////////////////////////////////////
// Result assignment
//////////////////////////////////////////////////////////////////////////////

    assign sum          = first_operand_i + second_operand_i;
    assign result_jal_o = pc_i + 4;

    always_comb begin
        if (operation_i == OP6) begin                       // JAL - Branch target is Sum of first_operand_i and second_operand_i
            result_o <= sum;
        end
        else if (operation_i == OP7) begin                  // JALR - Branch target is first_operand_i+second_operand_i with
            result_o[31:1] <= sum[31:1];
            result_o[0]    <= 0;
        end 
        else begin                                          // Conditional Branches - Branch target is PC + immediate
            result_o <= pc_i + offset_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Genarates the branch signal
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (operation_i == OP0) begin                                    // Branch if equals (BEQ)
            jump_o <= (first_operand_i == second_operand_i);
        end
        
        else if (operation_i == OP1) begin                               // Branch if not equal (BNE)
            jump_o <= (first_operand_i != second_operand_i);
        end
        
        else if (operation_i == OP2) begin                               // Branch if less than (BLT)
            jump_o <= ($signed(first_operand_i) < $signed(second_operand_i));
        end
        
        else if (operation_i == OP3) begin                               // Branch if less than unsigned (BLTU)
            jump_o <= ($unsigned(first_operand_i) < $unsigned(second_operand_i));
        end
        
        else if (operation_i == OP4) begin                               // Branch if greather or equals than (BGE)
            jump_o <= ($signed(first_operand_i) >= $signed(second_operand_i));
        end
        
        else if (operation_i == OP5) begin                               // Branch if greather or equals than unsigned (BGEU)
            jump_o <= ($unsigned(first_operand_i) >= $unsigned(second_operand_i));
        end
        
        else if (operation_i == OP6 || operation_i == OP7) begin         // Unconditional Branches
            jump_o <= 1;
        end
        
        else begin
            jump_o <= 0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Write enable signal generator
//////////////////////////////////////////////////////////////////////////////

    always_comb begin  // Register write enable is 1 in JAL and JALR instructions
        if (operation_i == OP6 || operation_i == OP7) begin
            write_enable_o <= '1;
        end
        else begin
            write_enable_o <= '0;
        end
    end

endmodule

//--------------------------------------------------------------------------------------------------
// LOGIC UNIT
//--------------------------------------------------------------------------------------------------

module logicUnit (
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   operationType_e     operation_i,
    output  logic [31:0]        result_o
);

    always_comb begin
        if (operation_i == OP0) begin
            result_o <= first_operand_i ^ second_operand_i;
        end
        else if (operation_i == OP1) begin
            result_o <= first_operand_i | second_operand_i;
        end
        else begin
            result_o <= first_operand_i & second_operand_i;
        end
    end
endmodule

//--------------------------------------------------------------------------------------------------
// LOAD-STORE UNIT
//--------------------------------------------------------------------------------------------------

module LSUnit (
    input   logic [31:0]        first_operand_i,                // Base csr_address
    input   logic [31:0]        second_operand_i,               // Offset
    input   logic [31:0]        data_i,                         // Data to be Written in memory
    input   operationType_e     operation_i,
    input   logic               enable_i,                       // enable memory operation based on instruction

    output  logic [31:0]        read_address_o,                 // Read Memory csr_address
    output  logic               read_o,                         // Signal that allows memory read
    output  logic [31:0]        write_address_o,                // Adrress to Write in memory
    output  logic [31:0]        write_data_o,                   // Data to be Written in Register Bank or in memory
    output  logic [3:0]         write_enable_o,                 // Signal that indicates the size of Write in memory(byte(1),half(2),word(4))
    output  logic               write_enable_regBank            // Write enable signal to register bank, in Stores=0 and in Loads=1
);

    logic [31:0] sum;

//--------------------------------------------------------------------------------------------------
// Generate all signals for read or write
//--------------------------------------------------------------------------------------------------

    always_comb begin
        if (enable_i == 1) begin
            if (operation_i == OP0 || operation_i == OP1) begin // LB | LBU
                read_o          <= 1;
                write_data_o    <= '0;
                write_enable_o  <= 4'b0000;
            end 
            else if (operation_i == OP2 || operation_i == OP3) begin // LH | LHU
                read_o          <= 1;
                write_data_o    <= '0;
                write_enable_o  <= 4'b0000;
            end 
            else if (operation_i == OP4) begin // LW
                read_o          <= 1;
                write_data_o    <= '0;
                write_enable_o  <= 4'b0000;
            end 
            else if (operation_i == OP5) begin // SB
                read_o <= 0;
                write_data_o[31:24] <= data_i[7:0];
                write_data_o[23:16] <= data_i[7:0];
                write_data_o[15:8]  <= data_i[7:0];
                write_data_o[7:0]   <= data_i[7:0];
                case (sum[1:0])
                    2'b11:   write_enable_o <= 4'b1000;
                    2'b10:   write_enable_o <= 4'b0100;
                    2'b01:   write_enable_o <= 4'b0010;
                    default: write_enable_o <= 4'b0001;
                endcase
            end 
            else if (operation_i == OP6) begin // SH
                read_o              <= 0;
                write_data_o[31:16] <= data_i[15:0];    
                write_data_o[15:0]  <= data_i[15:0];
                write_enable_o      <= (write_address_o[1] == 1) 
                                        ? 4'b1100 
                                        : 4'b0011;
            end 
            else if (operation_i == OP7) begin // SW
                read_o              <= 0;
                write_data_o[31:0]  <= data_i[31:0];  
                write_enable_o      <= 4'b1111;
            end 
            else begin
                read_o              <= 0;
                write_data_o[31:0]  <= '0;  
                write_enable_o      <= '0;
            end
        end 
        else begin
            read_o              <= 0;
            write_data_o[31:0]  <= '0;  
            write_enable_o      <= '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Write enable to register bank
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (operation_i == OP5 || operation_i == OP6 || operation_i == OP7) begin
            write_enable_regBank <= '0;
        end
        else begin
            write_enable_regBank <= '1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Outputs assignment
//////////////////////////////////////////////////////////////////////////////

    assign sum = first_operand_i + second_operand_i;

    assign write_address_o = sum;
    assign read_address_o  = sum;

endmodule

//--------------------------------------------------------------------------------------------------
// SHIFT UNIT
//--------------------------------------------------------------------------------------------------

module shiftUnit (
    input   logic [31:0]        first_operand_i,
    input   logic [4:0]         second_operand_i,
    input   operationType_e     operation_i,

    output  logic [31:0]        result_o
);

    always_comb begin
        if (operation_i == OP0) begin  // SLL
            result_o <= first_operand_i << second_operand_i;
        end
        else if (operation_i == OP1) begin // SRL
            result_o <= first_operand_i >> second_operand_i;
        end
        else begin // SRA
            result_o <= $signed(first_operand_i) >>> second_operand_i;
        end
    end
endmodule

//--------------------------------------------------------------------------------------------------
// CSR UNIT
//--------------------------------------------------------------------------------------------------

module csrUnit (
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        instruction_i,
    input   operationType_e     operation_i,
    input   privilegeLevel_e    privilege_i,

    output  logic               read_enable_o,
    output  logic               write_enable_o,
    output  csrOperation_e      operation_o,
    output  logic [11:0]        address_o,
    output  logic [31:0]        data_o,
    output  logic               exception_o
);

    logic csr_rd_en_int, csr_wr_en_int;
    logic [4:0] rd, rs1;

    assign rd  = instruction_i[11:7];
    assign rs1 = instruction_i[19:15];

    assign address_o = instruction_i[31:20];

    assign read_enable_o = csr_rd_en_int & !exception_o;
    assign write_enable_o = csr_wr_en_int & !exception_o;

    always_comb begin
        if (operation_i == OP0 || operation_i == OP3) begin // CSSRW | CSSRWI
            csr_wr_en_int = 1;
            if (rd == 0)
                csr_rd_en_int = 0;
            else
                csr_rd_en_int = 1;

        end 
        else if (operation_i == OP1 || operation_i == OP2 || operation_i == OP4 || operation_i == OP5) begin // CSRRS/C | CSRRS/CI
            csr_rd_en_int = 1;
            if (rs1 == 0)
                csr_wr_en_int <= 0;
            else
                csr_wr_en_int <= 1;
        end 
        else begin
            csr_rd_en_int <= 0;
            csr_wr_en_int <= 0;
        end
    end

    always_comb begin      
        if (operation_i == OP0 || operation_i == OP1 || operation_i == OP2) begin
            data_o <= first_operand_i;
        end
        else begin
            data_o <= '0 & rs1;
        end
    end

    always_comb begin
        if (operation_i == OP0 || operation_i == OP3) begin
            operation_o <= WRITE;
        end
        else if (operation_i == OP1 || operation_i == OP4) begin
            operation_o <= SET;
        end
        else if (operation_i == OP2 || operation_i == OP5) begin
            operation_o <= CLEAR;
        end
        else begin
            operation_o <= NONE;
        end
    end
    
    always_comb begin
        // Raise exeption if CSR is read only and write enable is true
        if (address_o[11:10] == 2'b11 && csr_wr_en_int == 1) begin
            exception_o <= 1;
        end
        // Check Level privileges
        else if (address_o[9:8] < privilege_i && (csr_rd_en_int == 1 || csr_wr_en_int == 1)) begin
            exception_o <= 1;
        end
        // No exception is raised
        else begin
            exception_o <= 0;
        end
    end

endmodule
