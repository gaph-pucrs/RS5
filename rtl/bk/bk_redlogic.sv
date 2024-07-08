/*
    logic [VLEN-1:0] first_operand_logic, second_operand_logic;
    logic [VLEN-1:0] result_and, result_or, result_xor, result_logic;

    always_comb begin
        automatic int i = 0;
        if (instruction_operation inside{vand, vor, vxor}) begin
            first_operand_logic  = first_operand;
            second_operand_logic = second_operand;
        end
        else begin
            first_operand_logic[(VLEN/2)-1:0]  = first_operand[(VLEN/2)-1:0];
            second_operand_logic[(VLEN/2)-1:0] = second_operand[VLEN-1:(VLEN/2)];

            first_operand_logic[((VLEN/4)*3)-1:(VLEN/2)]  = result_logic[(VLEN/4)-1:0];
            second_operand_logic[((VLEN/4)*3)-1:(VLEN/2)] = result_logic[(VLEN/2)-1:(VLEN/4)];

            first_operand_logic[VLEN-1:((VLEN/4)*3)]  = result_logic[(VLEN/2)-1:(VLEN/4)];
            second_operand_logic[VLEN-1:((VLEN/4)*3)] = result_logic[(VLEN/2)-1:(VLEN/4)];
        end
    end

    always_comb begin
        result_and = first_operand_logic & second_operand_logic;
        result_or  = first_operand_logic | second_operand_logic;
        result_xor = first_operand_logic ^ second_operand_logic;
    end

    always_comb begin
        unique case(vector_operation_i)
            vor:     result_logic = result_or;
            vxor:    result_logic = result_xor;
            default: result_logic = result_and;
        endcase
    end









//////////////////////////////////////////////////////////////////////////////
// Logical
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] second_operand_and, second_operand_or, second_operand_xor;

    logic [VLEN-1:0] result_and, result_or, result_xor;
    logic [31:0]     result_redand, result_redor, result_redxor;

    always_comb begin
        if (vector_operation_i inside {vredand, vredor, vredxor}) begin
            unique case (vsew)
                EW8:
                    for (int i = 0; i < VLENB; i++)
                        if (i == 0) begin
                            second_operand_and[7:0] = second_operand[7:0];
                            second_operand_or [7:0] = second_operand[7:0];
                            second_operand_xor[7:0] = second_operand[7:0];
                        end
                        else begin
                            second_operand_and[(8*(i+1))-1-:8] = result_and[(8*(i))-1-:8];
                            second_operand_or [(8*(i+1))-1-:8] = result_or [(8*(i))-1-:8];
                            second_operand_xor[(8*(i+1))-1-:8] = result_xor[(8*(i))-1-:8];
                        end
                EW16:
                    for (int i = 0; i < VLENB/2; i++)
                        if (i == 0) begin
                            second_operand_and[15:0] = second_operand[15:0];
                            second_operand_or [15:0] = second_operand[15:0];
                            second_operand_xor[15:0] = second_operand[15:0];
                        end
                        else begin
                            second_operand_and[(16*(i+1))-1-:16] = result_and[(16*(i))-1-:16];
                            second_operand_or [(16*(i+1))-1-:16] = result_or [(16*(i))-1-:16];
                            second_operand_xor[(16*(i+1))-1-:16] = result_xor[(16*(i))-1-:16];
                            
                        end
                default:
                    for (int i = 0; i < VLENB/4; i++)
                        if (i == 0) begin
                            second_operand_and[31:0] = second_operand[31:0];
                            second_operand_or [31:0] = second_operand[31:0];
                            second_operand_xor[31:0] = second_operand[31:0];
                        end
                        else begin
                            second_operand_and[(32*(i+1))-1-:32] = result_and[(32*(i))-1-:32];
                            second_operand_or [(32*(i+1))-1-:32] = result_or [(32*(i))-1-:32];
                            second_operand_xor[(32*(i+1))-1-:32] = result_xor[(32*(i))-1-:32];
                        end
            endcase
        end
        else begin
            second_operand_and = second_operand;
        end
    end

    always_comb begin
        result_and = first_operand & second_operand_and;
        result_or  = first_operand | second_operand_or;
        result_xor = first_operand ^ second_operand_xor;
    end

    always_comb begin
        unique case (vsew)
            EW8:     result_redand = {24'h000000, result_and[VLEN-1-:8]};
            EW16:    result_redand = {16'h0000,   result_and[VLEN-1-:16]};
            default: result_redand = {result_and[VLEN-1-:32]};
        endcase
         
    end













//////////////////////////////////////////////////////////////////////////////
// Logical
//////////////////////////////////////////////////////////////////////////////
    // TODO: ADAPT for 128
    logic [VLEN-1:0] op1_logical, op2_logical, op3_logical;
    logic [VLEN-1:0] result_and, result_or, result_xor;
    logic [3:0] sub_cycle_count;

    always @(posedge clk ) begin
        result_r <= result;
    end

    logic [VLEN-1:0]        second_operand_scalar;

    always_comb begin
        unique case (vsew)
            EW8:        second_operand_scalar = {'0, second_operand[7:0]};
            EW16:       second_operand_scalar = {'0, second_operand[15:0]};
            default:    second_operand_scalar = {'0, second_operand[31:0]};
        endcase
    end

    always_comb begin
        if (!reduction_instruction) begin
            op1_logical = first_operand;
            op2_logical = second_operand;
            op3_logical = (vector_operation_i == vand) ? '1 : '0;
        end
        else begin
            if (sub_cycle_count == 0) begin // 32 x 32 x 32
                op1_logical = first_operand[31:0];
                op2_logical = first_operand[63:32];
                op3_logical = {'1, second_operand_scalar};
            end
            else if (sub_cycle_count == 1) begin // 16 x 16
                op1_logical = result_r[15:0];
                op2_logical = result_r[31:0];
                op3_logical = (vector_operation_i == vand) ? '1 : '0;
            end
            else begin  // 8 x 8
                op1_logical = result_r[7:0];
                op2_logical = result_r[15:0];
                op3_logical = (vector_operation_i == vand) ? '1 : '0;
            end
        end
    end

    always_comb begin
        result_and = op1_logical & op2_logical & op3_logical;
        result_or  = op1_logical | op2_logical | op3_logical;
        result_xor = op1_logical ^ op2_logical ^ op3_logical;
    end













    logic [31:0]        second_operand_scalar;
    logic [3:0] sub_cycle_count;

    always_ff @(posedge clk) begin
        if (reset == 1'b1)
            sub_cycle_count <= 0;
        else if (next_state == V_EXEC)
            sub_cycle_count <= sub_cycle_count + 1;
    end

    always_comb begin
        unique case (vsew)
            EW8:        second_operand_scalar = {'0, second_operand[7:0]};
            EW16:       second_operand_scalar = {'0, second_operand[15:0]};
            default:    second_operand_scalar = second_operand[31:0];
        endcase
    end
/*
    always_comb begin
        if (!reduction_instruction) begin
            result_and = first_operand & second_operand;
            result_or  = first_operand | second_operand;
            result_xor = first_operand ^ second_operand;
        end
        else begin
            if (sub_cycle_count == 0) begin // 32 x 32 x 32
                result_and = first_operand[31:0] & first_operand[63:32] & second_operand_scalar;
                result_or  = first_operand[31:0] | first_operand[63:32] | second_operand_scalar;
                result_xor = first_operand[31:0] ^ first_operand[63:32] ^ second_operand_scalar;
            end
            else if (sub_cycle_count == 1) begin // 16 x 16
                result_and = result[15:0] & result[31:16];
                result_or  = result[15:0] | result[31:16];
                result_xor = result[15:0] ^ result[31:16];
            end
            else begin  // 8 x 8
                result_and = result[7:0] & result[15:8];
                result_or  = result[7:0] | result[15:8];
                result_xor = result[7:0] ^ result[15:8];
            end
        end
    end
*/
/*
    logic [VLEN-1:0] result_and, result_or, result_xor;
    logic [VLEN-1:0] result_and_64, result_or_64, result_xor_64;
    logic [31:0] result_and_32, result_or_32, result_xor_32;
    logic [15:0] result_and_16, result_or_16, result_xor_16;
    logic [7:0]  result_and_8, result_or_8, result_xor_8;

    always_comb begin
        result_and_64 = first_operand & second_operand;
        result_or_64  = first_operand | second_operand;
        result_xor_64 = first_operand ^ second_operand;
    end

    always @(posedge clk ) begin
        if (sub_cycle_count == 0) begin // 32 x 32 x 32
            result_and_32 = first_operand[31:0] & first_operand[63:32] & second_operand_scalar;
            result_or_32  = first_operand[31:0] | first_operand[63:32] | second_operand_scalar;
            result_xor_32 = first_operand[31:0] ^ first_operand[63:32] ^ second_operand_scalar;
        end
        else if (sub_cycle_count == 1) begin // 16 x 16
            result_and_16 = result_and_32[15:0] & result_and_32[31:16];
            result_or_16  = result_or_32 [15:0] | result_or_32 [31:16];
            result_xor_16 = result_xor_32[15:0] ^ result_xor_32[31:16];
        end
        else begin  // 8 x 8
            result_and_8 = result_and_16[7:0] &  result_and_16[15:8];
            result_or_8  = result_or_16 [7:0] |  result_or_16 [15:8];
            result_xor_8 = result_xor_16[7:0] ^  result_xor_16[15:8];
        end
    end

    always_comb begin
        if (!reduction_instruction) begin
            result_and = result_and_64;   
            result_or  = result_or_64;   
            result_xor = result_xor_64;   
        end
        else begin
            if (vsew == EW8) begin
                result_and = {'0, result_and_8};   
                result_or  = {'0, result_or_8};   
                result_xor = {'0, result_xor_8};  
            end
            else if (vsew == EW16) begin
                result_and = {'0, result_and_16};   
                result_or  = {'0, result_or_16};   
                result_xor = {'0, result_xor_16};  
            end
            else begin
                result_and = {'0, result_and_32};   
                result_or  = {'0, result_or_32};   
                result_xor = {'0, result_xor_32};  
            end
        end
    end
*/
