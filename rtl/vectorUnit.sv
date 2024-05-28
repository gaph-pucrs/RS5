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
    output  logic [31:0]    vlen_o,

    output logic [31:0]     mem_address_o,
    output logic            mem_read_enable_o,
    output logic [ 3:0]     mem_write_enable_o,
    output logic [31:0]     mem_write_data_o,
    input  logic [31:0]     mem_read_data_i,

    output  logic [31:0]    res_scalar_o,
    output  logic           wr_en_scalar_o
);

    localparam VLENB = VLEN/8;

    // Decoding signals
    logic [ 4:0] rd, rs1, rs2;
    logic [10:0] zimm;
    logic        vm;
    opCat_e      opCat;
    logic        reduction_instruction;
    logic        accumulate_instruction;
    logic        compare_instruction;
    logic        widening_instruction;

    vew_e   vsew, vsew_effective;
    vlmul_e vlmul, vlmul_effective;
    logic[$bits(VLEN )-1:0] vl, vl_curr_reg, vl_next;
    logic[$bits(VLENB)-1:0] elements_per_reg;

    vector_states_e  state, next_state;

    logic [VLEN-1:0]  scalar_replicated, imm_replicated;
    logic [VLEN-1:0]  v0_mask;

    logic [4:0]       vs1_addr, vs2_addr, vs3_addr;
    logic [VLEN-1:0]  vs1_data, vs2_data, vs3_data;
    logic [4:0]       cycle_count, cycle_count_r, cycle_count_vd;
    logic             hold, hold_widening, hold_alu, hold_lsu;

    logic [VLEN-1:0]  first_operand, second_operand, third_operand;

    logic [4:0]       vd_addr, vd_addr_r;
    logic [VLEN-1:0]  result_alu, result_lsu, result;
    logic [VLENB-1:0] write_enable;

    assign hold = hold_alu | hold_lsu;

//////////////////////////////////////////////////////////////////////////////
// Decoding
//////////////////////////////////////////////////////////////////////////////

    assign rd  = instruction_i[11:7];
    assign rs1 = instruction_i[19:15];
    assign rs2 = instruction_i[24:20];
    assign vm  = instruction_i[25];

    assign zimm     = {instruction_i[30:20]};
    assign opCat    = opCat_e'(instruction_i[14:12]);

    assign accumulate_instruction = (vector_operation_i inside {VMACC, VNMSAC, VMADD, VNMSUB});
    assign reduction_instruction  = (vector_operation_i inside {VREDSUM, VREDMAXU, VREDMAX, VREDMINU, VREDMIN, VREDAND, VREDOR, VREDXOR});
    assign compare_instruction    = (vector_operation_i inside {VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT});
    assign widening_instruction   = (vector_operation_i inside {VWMUL, VWMULU, VWMULSU});

    assign elements_per_reg = VLENB >> vsew;

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    vectorCSRs #(
        .VLEN   (VLEN),
        .VLENB  (VLENB)
    ) vectorCSRs1 (
        .clk                (clk),
        .reset_n            (reset_n),
        .vector_operation_i (vector_operation_i),
        .op1_scalar_i       (op1_scalar_i),
        .op2_scalar_i       (op2_scalar_i),
        .zimm               (zimm),
        .rs1                (rs1),
        .rd                 (rd),
        .vtype_o            (vtype_o),
        .vlen_o             (vlen_o),
        .vsew               (vsew),
        .vlmul              (vlmul),
        .vl                 (vl),
        .vl_next            (vl_next)
    );

//////////////////////////////////////////////////////////////////////////////
// MASKs
//////////////////////////////////////////////////////////////////////////////

    logic [ VLENB   -1:0] mask_sew8 [8];
    logic [(VLENB/2)-1:0] mask_sew16[8];
    logic [(VLENB/4)-1:0] mask_sew32[8];

    always_comb begin
        for (int i = 0; i < 8; i++) begin
            mask_sew8 [i] = v0_mask[( VLENB   *(i+1))-1-:VLENB];
            mask_sew16[i] = v0_mask[((VLENB/2)*(i+1))-1-:VLENB/2];
            mask_sew32[i] = v0_mask[((VLENB/4)*(i+1))-1-:VLENB/4];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    assign hold_o = (next_state inside {V_EXEC, V_END});

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
                if (
                    (instruction_operation_i == VECTOR && !(vector_operation_i inside {VNOP, VSETVL, VSETVLI, VSETIVLI}))
                ||  (instruction_operation_i inside {VLOAD, VSTORE})
                )
                    next_state = V_EXEC;
                else
                    next_state = V_IDLE;

            V_EXEC:
                if (
                    (vlmul_effective == LMUL_1  && cycle_count_vd < 1)
                ||  (vlmul_effective == LMUL_2  && cycle_count_vd < 2)
                ||  (vlmul_effective == LMUL_4  && cycle_count_vd < 4)
                ||  (vlmul_effective == LMUL_8  && cycle_count_vd < 8)
                )
                    next_state = V_EXEC;
                else
                    next_state = V_END;

            V_END:
                next_state = V_IDLE;

            default:
                next_state = V_IDLE;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// SEW and VLMUL Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (widening_instruction) begin
            unique case (vsew)
                EW8:
                    vsew_effective = EW16;
                EW16:
                    vsew_effective = EW32;
                default: begin
                    vsew_effective = vsew;
                    $error("Widening operations with VSEW=32b are not supported");
                end
            endcase
        end
        else begin
            vsew_effective = vsew;
        end
    end

    always_comb begin
        if (widening_instruction) begin
            unique case (vlmul)
                LMUL_1:
                    vlmul_effective = LMUL_2;
                LMUL_2:
                    vlmul_effective = LMUL_4;
                LMUL_4:
                    vlmul_effective = LMUL_8;
                LMUL_8: begin
                    vlmul_effective = LMUL_8;
                    $error("Widening operations with LMUL=8 are not supported");
                end
                default:
                    vlmul_effective = vlmul;
            endcase
        end
        else begin
            vlmul_effective = vlmul;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Cycle Count Control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count <= 0;
        else if (next_state == V_IDLE)
            cycle_count <= 0;
        else if (next_state == V_EXEC && hold == 1'b0)
            cycle_count <= cycle_count + 1;

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count_vd <= 0;
        else if ((next_state == V_IDLE) || (accumulate_instruction && state == V_IDLE && next_state == V_EXEC))
            cycle_count_vd <= 0;
        else if (next_state == V_EXEC && (!hold || hold_widening))
            cycle_count_vd <= cycle_count_vd + 1;

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count_r <= 0;
        else if (widening_instruction || accumulate_instruction)
            cycle_count_r <= cycle_count_vd;
        else if (!hold)
            cycle_count_r <= cycle_count;

//////////////////////////////////////////////////////////////////////////////
// Vector Length Control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            vl_curr_reg <= '0;
        else if (next_state == V_IDLE)
            vl_curr_reg <= 0;
        else if ((state == V_IDLE && next_state == V_EXEC) || (accumulate_instruction && cycle_count_vd == 0))
            vl_curr_reg <= vl;
        else if (next_state == V_EXEC && (hold == 1'b0))
            if ($signed(vl_curr_reg - elements_per_reg) >= 0)
                vl_curr_reg <= vl_curr_reg - elements_per_reg;
            else
                vl_curr_reg <= 0;

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
        if (!hold || hold_widening) begin
            vd_addr   <= (reduction_instruction)
                        ? rd
                        : rd + cycle_count_vd;
            vd_addr_r <= vd_addr;
        end
    end

    // WRITE ENABLE GENERATION
    always_ff @(posedge clk) begin
        if ((state == V_EXEC) && (!hold || hold_widening) && instruction_operation_i != VSTORE) begin
            if (reduction_instruction) begin
                unique case (vsew_effective)
                    EW8:     write_enable <= {'0, 1'b1};
                    EW16:    write_enable <= {'0, 2'b11};
                    default: write_enable <= {'0, 4'b1111};
                endcase
            end
            else begin
                unique case (vsew_effective)
                    EW8:
                        for (int i = 0; i < VLENB; i++)
                            if ((vm || mask_sew8[cycle_count_r][i]) && (i < vl_curr_reg))
                                write_enable[i] <= 1'b1;
                            else
                                write_enable[i] <= 1'b0;

                    EW16:
                        for (int i = 0; i < VLENB/2; i++)
                            if ((vm || mask_sew16[cycle_count_r][i]) && (i < vl_curr_reg)) 
                                write_enable[(i*2)+:2] <= 2'b11;
                            else
                                write_enable[(i*2)+:2] <= 2'b00;

                    default:
                        for (int i = 0; i < VLENB/4; i++)
                            if ((vm || mask_sew32[cycle_count_r][i]) && (i < vl_curr_reg))
                                write_enable[(i*4)+:4] <= 4'b1111;
                            else
                                write_enable[(i*4)+:4] <= 4'b0000;
                endcase
            end
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
        .vd_addr  (vd_addr_r),
        .result   (result),
        .v0_mask  (v0_mask),
        .vs1_data (vs1_data),
        .vs2_data (vs2_data),
        .vs3_data (vs3_data)
    );

//////////////////////////////////////////////////////////////////////////////
// Replicate Immediate and Scalar
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (vsew)
            EW8:     scalar_replicated = {(VLENB)  {op1_scalar_i[ 7:0]}};
            EW16:    scalar_replicated = {(VLENB/2){op1_scalar_i[15:0]}};
            default: scalar_replicated = {(VLENB/4){op1_scalar_i[31:0]}};
        endcase
    end

    always_comb begin
        // unsigned
        if (vector_operation_i inside {VSRL, VSLL, VSRA}) begin
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
            first_operand  <= (vector_operation_i inside {VMADD, VNMSUB})  ? vs3_data : vs2_data;
            third_operand  <= (vector_operation_i inside {VMADD, VNMSUB})  ? vs2_data : vs3_data;
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
// LOAD AND STORE UNIT
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] lsu_data_read;

    vectorLSU #(
        .VLEN   (VLEN),
        .VLENB  (VLENB)
    ) vectorLSU1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .instruction_i          (instruction_i),
        .base_address_i         (op1_scalar_i),
        .stride_i               (op2_scalar_i),
        .indexed_offsets_i      (first_operand),
        .write_data_i           (third_operand),
        .current_state          (state),
        .cycle_count            (cycle_count),
        .instruction_operation_i(instruction_operation_i),
        .vsew                   (vsew),
        .vlmul                  (vlmul),
        .cycle_count_r          (cycle_count_r),
        .vl_curr_reg            (vl_curr_reg),
        .vm                     (vm),
        .mask_sew8              (mask_sew8),
        .mask_sew16             (mask_sew16),
        .mask_sew32             (mask_sew32),
        .hold_o                 (hold_lsu),

        .mem_address_o          (mem_address_o),
        .mem_read_enable_o      (mem_read_enable_o),
        .mem_write_enable_o     (mem_write_enable_o),
        .mem_write_data_o       (mem_write_data_o),
        .mem_read_data_i        (mem_read_data_i),
        .read_data_o            (result_lsu)
    );

//////////////////////////////////////////////////////////////////////////////
// ALU
//////////////////////////////////////////////////////////////////////////////

    logic [$bits(VLEN )-1:0] vl_reductions;
    assign vl_reductions = (vl_curr_reg > elements_per_reg)
                            ? elements_per_reg
                            : vl_curr_reg;

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
        .cycle_count        (cycle_count),
        .cycle_count_r      (cycle_count_r),
        .vlmul              (vlmul),
        .vl                 (vl_reductions),
        .vm                 (vm),
        .mask_sew8          (mask_sew8),
        .mask_sew16         (mask_sew16),
        .mask_sew32         (mask_sew32),
        .current_state      (state),
        .vsew               (vsew),
        .hold_o             (hold_alu),
        .hold_widening_o    (hold_widening),
        .result_o           (result_alu)
    );

    assign result = (instruction_operation_i == VLOAD) ? result_lsu : result_alu;

//////////////////////////////////////////////////////////////////////////////
// Scalar Result
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (vector_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
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
