module vectorUnit 
    import RS5_pkg::*;
#(
    parameter int           VLEN        = 64
)
(
    input   logic           clk,
    input   logic           reset_n,

    input   logic [31:0]    instruction_i,
    input   iType_e         instruction_operation_i,
    input   iTypeVector_e   vector_operation_i,

    input   logic [31:0]    op1_scalar_i,
    input   logic [31:0]    op2_scalar_i,
    input   logic [31:0]    op3_scalar_i,

    output  logic           hold_o,

    output  logic [31:0]    vtype_o,

    output  logic [31:0]    res_scalar_o,
    output  logic           wr_en_scalar_o
);

    localparam VLENB = VLEN/8;

    // Decoding signals
    logic [ 4:0] rd, rs1, rs2;
    logic [ 2:0] funct3;
    logic [10:0] zimm;
    opCat_e      opCat;
    addrModes_e  addrMode;
    logic        reduction_instruction;

    vew_e   vsew;
    vlmul_e vlmul;
    logic[$bits(VLEN)-1:0] vl, vl_next;

    vector_states_e  state, next_state;

    logic [VLEN-1:0]  scalar_replicated, imm_replicated;
    logic [4:0]       vs1_addr, vs2_addr, vs3_addr;
    logic [VLEN-1:0]  vs1_data, vs2_data, vs3_data;
    logic [4:0]       cycle_count;
    logic             hold;

    logic [VLEN-1:0]  first_operand, second_operand, third_operand;
    
    logic [4:0]       vd_addr_int, vd_addr;
    logic [VLEN-1:0]  result;
    logic [VLENB-1:0] write_enable;

//////////////////////////////////////////////////////////////////////////////
// Decoding
//////////////////////////////////////////////////////////////////////////////

    assign rd  = instruction_i[11:7];
    assign rs1 = instruction_i[19:15];
    assign rs2 = instruction_i[24:20];

    assign funct3   = instruction_i[14:12];
    assign zimm     = {instruction_i[30:20]};
    assign opCat    = opCat_e'(funct3);
    assign addrMode = addrModes_e'(instruction_i[27:26]);

    assign reduction_instruction = (vector_operation_i inside {vredsum, vredmaxu, vredmax, vredminu, vredmin, vredand, vredor, vredxor});

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    vectorCSRs #(
        .VLEN   (VLEN),
        .VLENB  (VLENB)
    ) vectorCSRs1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .instruction_operation_i(instruction_operation_i),
        .op1_scalar_i           (op1_scalar_i),
        .op2_scalar_i           (op2_scalar_i),
        .zimm                   (zimm),
        .rs1                    (rs1),
        .rd                     (rd),
        .vtype                  (vtype_o),
        .vsew                   (vsew),
        .vlmul                  (vlmul),
        .vl                     (vl),
        .vl_next                (vl_next)
    );

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    assign hold_o = (next_state == V_EXEC || next_state == V_END);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state <= V_IDLE;
        end
        else if (!hold) begin
            state <= next_state;
        end
    end

    always_comb begin
        unique case (state)
            V_IDLE:
                if (instruction_operation_i == VECTOR)
                    next_state = V_EXEC;
                else
                    next_state = V_IDLE;

            V_EXEC:
                if ((vlmul == LMUL_2 && cycle_count < 2) || (vlmul == LMUL_4 && cycle_count < 4) || (vlmul == LMUL_8 && cycle_count < 8))
                    next_state = V_EXEC;
                else
                    next_state = V_END;

            V_END:
                next_state = V_IDLE;

            default:
                next_state = V_IDLE;
        endcase
    end
/*
    //logic   widening;
    //vew_e   vsew_effective;

    always_comb begin
        if (widening) begin
            unique case (vsew)
                EW8:  vsew_effective = EW16;
                EW16: vsew_effective = EW32;
                EW32: vsew_effective = EW64;
                EW64: vsew_effective = EW128;
                default: vsew_effective = vsew;
            endcase
        end begin
            vsew_effective = vsew;
        end
    end
*/
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            cycle_count <= 0;
        else if (next_state == V_IDLE)
            cycle_count <= 0;
        else if (next_state == V_EXEC && hold == 1'b0)
            cycle_count <= cycle_count + 1;
    end

//////////////////////////////////////////////////////////////////////////////
// Register Bank
//////////////////////////////////////////////////////////////////////////////

    // ADDRESS CALCULATION
    always_comb begin
        vs1_addr = rs1 + cycle_count;
        vs2_addr = rs2 + cycle_count;
        vs3_addr = rd  + cycle_count;
    end

    always_ff @(posedge clk) begin
        if (!hold) begin
            vd_addr_int <= vs3_addr;
            vd_addr     <= vd_addr_int;
        end
    end

    // WRITE ENABLE GENERATION
    always_ff @(posedge clk) begin
        if ((state == V_EXEC) && (vl > 0) && (hold != 1'b1)) begin
            unique case (vsew)
                EW8: begin
                    for (int i = 0; i < VLENB; i++) begin
                        write_enable[i] <= (i < vl) ? 1'b1 : 1'b0;
                    end
                end
                EW16: begin
                    for (int i = 0; i < VLENB/2; i++) begin
                        write_enable[(i*2)]   <= (i < vl) ? 1'b1 : 1'b0;
                        write_enable[(i*2)+1] <= (i < vl) ? 1'b1 : 1'b0;
                    end
                end
                default: begin
                    for (int i = 0; i < VLENB/4; i++) begin
                        write_enable[(i*4)]   <= (i < vl) ? 1'b1 : 1'b0;
                        write_enable[(i*4)+1] <= (i < vl) ? 1'b1 : 1'b0;
                        write_enable[(i*4)+2] <= (i < vl) ? 1'b1 : 1'b0;
                        write_enable[(i*4)+3] <= (i < vl) ? 1'b1 : 1'b0;
                    end
                end
            endcase
        end
        else begin
            write_enable <= '0;
        end                   
    end

    vectorRegbank #(
        .VLEN   (VLEN),
        .VLENB  (VLENB)
    ) vectorRegbank1 (
        .clk      (clk),
        .reset_n  (reset_n),
        .vs1_addr (vs1_addr),
        .vs2_addr (vs2_addr),
        .vs3_addr (vs3_addr),
        .enable   (write_enable),
        .vd_addr  (vd_addr),
        .result   (result),
        .vs1_data (vs1_data),
        .vs2_data (vs2_data),
        .vs3_data (vs3_data)
    );

//////////////////////////////////////////////////////////////////////////////
// Replicate Immediate and Scalar
//////////////////////////////////////////////////////////////////////////////

    always_comb begin 
        unique case (vsew)
            EW8:     scalar_replicated = {(VLENB){op1_scalar_i[7:0]}};
            EW16:    scalar_replicated = {(VLENB/2){op1_scalar_i[15:0]}};
            default: scalar_replicated = {(VLENB/4){op1_scalar_i[31:0]}};
        endcase
    end

    always_comb begin 
        // unsigned
        if (vector_operation_i inside {vsrl, vsll, vsra}) begin
            unique case (vsew)
                EW8:     imm_replicated = {(VLENB  ){ 3'h0, rs1}};
                EW16:    imm_replicated = {(VLENB/2){11'h0, rs1}};
                default: imm_replicated = {(VLENB/4){27'h0, rs1}};
            endcase
        // signed
        end
        else begin
            unique case (vsew)
                EW8:     imm_replicated = {(VLENB  ){{ 3{rs1[4]}}, rs1}};
                EW16:    imm_replicated = {(VLENB/2){{11{rs1[4]}}, rs1}};
                default: imm_replicated = {(VLENB/4){{27{rs1[4]}}, rs1}};
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Operands
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (!hold) begin
            first_operand  <= vs2_data;
            third_operand  <= vs3_data;
        end
    end

    always_ff @(posedge clk) begin
        if (!hold) begin
            unique case (opCat)
                OPIVX, OPFVF, OPMVX: second_operand <= scalar_replicated;
                OPIVI:               second_operand <= imm_replicated;
                default:             second_operand <= vs1_data;
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// ALU
//////////////////////////////////////////////////////////////////////////////

    vectorALU #(
        .VLEN   (VLEN),
        .VLENB  (VLENB)
    ) vectorALU1 (
        .clk                (clk),
        .reset_n            (reset_n),
        .first_operand      (first_operand),
        .second_operand     (second_operand),
        .third_operand      (third_operand),
        .vector_operation_i (vector_operation_i),
        .current_state      (state),
        .vsew               (vsew),
        .hold_o             (hold),
        .result_o           (result)
    );

//////////////////////////////////////////////////////////////////////////////
// Scalar Result
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (instruction_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
            res_scalar_o   = vl_next;
            wr_en_scalar_o = 1'b1;
        end
        else if (instruction_operation_i == VECTOR) begin
            res_scalar_o   = result[31:0];
            wr_en_scalar_o = 1'b0;
        end
        else begin
            res_scalar_o   = '0;
            wr_en_scalar_o = 1'b0;
        end
    end
endmodule