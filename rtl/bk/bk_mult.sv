/*
//////////////////////////////////////////////////////////////////////////////
// Multiplication 8 bits
//////////////////////////////////////////////////////////////////////////////

    logic [ 7:0] mult_op_a_8b  [VLENB-1:0];
    logic [ 7:0] mult_op_b_8b  [VLENB-1:0];
    logic [15:0] mac_result_8b [VLENB-1:0];
    logic [15:0] mult_op_a_16b [(VLENB/2)-1:0];
    logic [15:0] mult_op_b_16b [(VLENB/2)-1:0];
    logic [31:0] mac_result_16b[(VLENB/2)-1:0];
    logic [31:0] mult_op_a_32b [(VLENB/4)-1:0];
    logic [31:0] mult_op_b_32b [(VLENB/4)-1:0];
    logic [63:0] mac_result_32b[(VLENB/4)-1:0];

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            mult_op_a_8b[i] = {first_operand [(8*(i+1))-1-:8]};
            mult_op_b_8b[i] = {second_operand[(8*(i+1))-1-:8]};
        end
    end

    genvar i_mul8b;
    generate
        for (i_mul8b = 0; i_mul8b < VLENB; i_mul8b++) begin : MUL8B_LOOP
            if (i_mul8b < VLENB/4) begin
                assign mac_result_8b[i_mul8b] = {mac_result_32b[i_mul8b][15:0]};
            end
            else if (i_mul8b < VLENB/2) begin
                assign mac_result_8b[i_mul8b] = {mac_result_16b[i_mul8b][15:0]};
            end
            else begin
                mulNbits #(
                    .N(8)
                ) mul8b (
                    .first_operand_i (mult_op_a_8b[i_mul8b]),
                    .second_operand_i(mult_op_b_8b[i_mul8b]),
                    .signed_mode_i   (mult_signed_mode),
                    .result_o        (mac_result_8b[i_mul8b])
                );
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication 16 bits
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (vsew == EW8) begin
            for (int i = VLENB/4; i < VLENB/2; i++) begin
                mult_op_a_16b[i] = {{8{mult_op_a_8b[i][7] & mult_signed_mode[0]}}, mult_op_a_8b[i]};
                mult_op_b_16b[i] = {{8{mult_op_b_8b[i][7] & mult_signed_mode[1]}}, mult_op_b_8b[i]};
            end
        end
        else begin
            for (int i = 0; i < VLENB/2; i++) begin
                mult_op_a_16b[i] = {first_operand [(16*(i+1))-1-:16]};
                mult_op_b_16b[i] = {second_operand[(16*(i+1))-1-:16]};
            end
        end
    end

    genvar i_mul16b;
    generate
        for (i_mul16b = 0; i_mul16b < VLENB/2; i_mul16b++) begin : MUL16B_LOOP
            if (i_mul16b < VLENB/4) begin
                assign mac_result_16b[i_mul16b] = {mac_result_32b[i_mul16b][31:0]};
            end
            else begin
                mulNbits #(
                    .N(16)
                ) mul16b (
                    .first_operand_i (mult_op_a_16b[i_mul16b]),
                    .second_operand_i(mult_op_b_16b[i_mul16b]),
                    .signed_mode_i   (mult_signed_mode),
                    .result_o        (mac_result_16b[i_mul16b])
                );
            end
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication 32 bits
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (vsew == EW8) begin
            for (int i = 0; i < VLENB/4; i++) begin
                mult_op_a_32b[i] = {{24{mult_op_a_8b[i][7] & mult_signed_mode[0]}}, mult_op_a_8b[i]};
                mult_op_b_32b[i] = {{24{mult_op_b_8b[i][7] & mult_signed_mode[1]}}, mult_op_b_8b[i]};
            end
        end
        else if (vsew == EW16) begin
            for (int i = 0; i < VLENB/4; i++) begin
                mult_op_a_32b[i] = {{16{mult_op_a_16b[i][15] & mult_signed_mode[0]}}, mult_op_a_16b[i]};
                mult_op_b_32b[i] = {{16{mult_op_b_16b[i][15] & mult_signed_mode[1]}}, mult_op_b_16b[i]};
            end
        end else begin
            for (int i = 0; i < VLENB/4; i++) begin
                mult_op_a_32b[i] = {first_operand [(32*(i+1))-1-:32]};
                mult_op_b_32b[i] = {second_operand[(32*(i+1))-1-:32]};
            end
        end
    end
/*
    genvar i_mul32b;
    generate
        for (i_mul32b = 0; i_mul32b < VLENB/4; i_mul32b++) begin : MUL32B_LOOP
            mulNbits #(
                .N(32)
            ) mul32b (
                .first_operand_i (mult_op_a_32b[i_mul32b]),
                .second_operand_i(mult_op_b_32b[i_mul32b]),
                .signed_mode_i   (mult_signed_mode),
                .result_o        (mac_result_32b[i_mul32b])
            );
        end
    endgenerate
*/

    logic                 mult_enable, mult_low;
    logic [(VLENB/4)-1:0] mult_hold_int;
    logic                 mult_hold;

    assign mult_enable = ((vector_operation_i inside {vmul, vmulh, vmulhsu, vmulhu}) && (current_state == V_EXEC) && (vsew==EW32));
    assign mult_low    = (vector_operation_i == vmul);
    assign mult_hold   = |mult_hold_int;

    genvar i_mul32b;
    generate
        for (i_mul32b = 0; i_mul32b < VLENB/4; i_mul32b++) begin : MUL32B_LOOP
            mul mul32b (
                .clk             (clk),
                .reset_n         (reset_n),
                .first_operand_i (mult_op_a_32b[i_mul32b]),
                .second_operand_i(mult_op_b_32b[i_mul32b]),
                .signed_mode_i   (mult_signed_mode),
                .enable_i        (mult_enable),
                .mul_low_i       (mult_low),
                .hold_o          (mult_hold_int[i_mul32b]),
                .result_o        (mac_result_32b[i_mul32b])
            );
        end
    endgenerate

//////////////////////////////////////////////////////////////////////////////
// Multiplication Demux
//////////////////////////////////////////////////////////////////////////////
    always_comb begin

        unique case (vsew)
            EW8: begin
                for (int i = 0; i < VLENB; i++)
                    if (widening_i)
                        result_mult[(16*(i+1))-1-:16] = mac_result_8b[i][15:0];
                    else if (vector_operation_i == vmul)
                        result_mult[(8*(i+1))-1-:8] = mac_result_8b[i][7:0];
                    else
                        result_mult[(8*(i+1))-1-:8] = mac_result_8b[i][15:8];
            end
            EW16: begin
                for (int i = 0; i < VLENB/2; i++)
                    if (widening_i)
                        result_mult[(32*(i+1))-1-:32] = mac_result_16b[i][31:0];
                    else if (vector_operation_i == vmul)
                        result_mult[(16*(i+1))-1-:16] = mac_result_16b[i][15:0];
                    else
                        result_mult[(16*(i+1))-1-:16] = mac_result_16b[i][31:16];
            end
            default: begin
                for (int i = 0; i < VLENB/4; i++)
                    if (vector_operation_i == vmul)
                        result_mult[(32*(i+1))-1-:32] = mac_result_32b[i][31:0];
                    else
                        result_mult[(32*(i+1))-1-:32] = mac_result_32b[i][63:32];
            end
        endcase
    end
*/