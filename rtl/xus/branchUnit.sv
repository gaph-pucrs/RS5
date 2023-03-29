//--------------------------------------------------------------------------------------------------
// BRANCH UNIT
//--------------------------------------------------------------------------------------------------

module branchUnit 
    import my_pkg::*;
(
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
            result_o = sum;
        end
        else if (operation_i == OP7) begin                  // JALR - Branch target is first_operand_i+second_operand_i with
            result_o[31:1] = sum[31:1];
            result_o[0]    = 0;
        end 
        else begin                                          // Conditional Branches - Branch target is PC + immediate
            result_o = pc_i + offset_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Genarates the branch signal
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (operation_i == OP0) begin                                    // Branch if equals (BEQ)
            jump_o = (first_operand_i == second_operand_i);
        end
        
        else if (operation_i == OP1) begin                               // Branch if not equal (BNE)
            jump_o = (first_operand_i != second_operand_i);
        end
        
        else if (operation_i == OP2) begin                               // Branch if less than (BLT)
            jump_o = ($signed(first_operand_i) < $signed(second_operand_i));
        end
        
        else if (operation_i == OP3) begin                               // Branch if less than unsigned (BLTU)
            jump_o = ($unsigned(first_operand_i) < $unsigned(second_operand_i));
        end
        
        else if (operation_i == OP4) begin                               // Branch if greather or equals than (BGE)
            jump_o = ($signed(first_operand_i) >= $signed(second_operand_i));
        end
        
        else if (operation_i == OP5) begin                               // Branch if greather or equals than unsigned (BGEU)
            jump_o = ($unsigned(first_operand_i) >= $unsigned(second_operand_i));
        end
        
        else if (operation_i == OP6 || operation_i == OP7) begin         // Unconditional Branches
            jump_o = 1;
        end
        
        else begin
            jump_o = 0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Write enable signal generator
//////////////////////////////////////////////////////////////////////////////

    always_comb begin  // Register write enable is 1 in JAL and JALR instructions
        if (operation_i == OP6 || operation_i == OP7) begin
            write_enable_o = '1;
        end
        else begin
            write_enable_o = '0;
        end
    end

endmodule
