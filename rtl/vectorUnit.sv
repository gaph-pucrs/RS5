`include "RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorUnit
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
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
    logic        widening_instruction;
    logic        whole_reg_load_store;
    logic        mask_instruction;

    vew_e   vsew, vsew_effective;
    vlmul_e vlmul, vlmul_effective;
    logic[$bits(VLEN )-1:0] vl, vl_curr_reg, vl_next;
    logic[$bits(VLENB)-1:0] elements_per_reg;
    logic[$bits(VLEN )-1:0] total_elements_processed;
    logic                   vector_process_done;

    vector_states_e  state, next_state;

    logic [VLEN-1:0]  scalar_replicated, imm_replicated;
    logic [VLEN-1:0]  v0_mask;

    logic [4:0]       rs1_addr, rs2_addr, rd_addr;
    logic [4:0]       vs1_addr, vs2_addr;
    logic [VLEN-1:0]  vs1_data, vs2_data;
    logic [3:0]       cycle_count, cycle_count_r, cycle_count_vd;
    logic             hazard_detected;
    logic             hold, hold_widening, hold_accumulation, hold_alu, hold_lsu;

    logic [VLEN-1:0]  first_operand, second_operand;

    logic [4:0]       vd_addr, vd_addr_r;
    logic [VLEN-1:0]  result_alu, result_alu_mask, result_lsu, result;
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
    assign widening_instruction   = (vector_operation_i inside {VWMUL, VWMULU, VWMULSU});
    assign whole_reg_load_store   = (instruction_i[24:20] == 5'b01000 && instruction_operation_i inside {VLOAD, VSTORE});
    assign mask_instruction       = (vector_operation_i inside {VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT});

    assign elements_per_reg = VLENB >> vsew;

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
        .vector_operation_i     (vector_operation_i),
        .op1_scalar_i           (op1_scalar_i),
        .op2_scalar_i           (op2_scalar_i),
        .zimm                   (zimm),
        .rs1                    (rs1),
        .rd                     (rd),
        .vtype_o                (vtype_o),
        .vlen_o                 (vlen_o),
        .vsew                   (vsew),
        .vlmul                  (vlmul),
        .vl                     (vl),
        .vl_next                (vl_next)
    );

//////////////////////////////////////////////////////////////////////////////
// MASKs
//////////////////////////////////////////////////////////////////////////////

    logic [7:0][ VLENB   -1:0] mask_sew8;
    logic [7:0][(VLENB/2)-1:0] mask_sew16;
    logic [7:0][(VLENB/4)-1:0] mask_sew32;

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

    assign hazard_detected = (state == V_IDLE && |write_enable == 1'b1 && (vs1_addr == vd_addr_r || vs2_addr == vd_addr_r));

    assign hold_o = (next_state == V_EXEC || hazard_detected == 1'b1);

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
                if ((
                    (instruction_operation_i == VECTOR && !(vector_operation_i inside {VNOP, VSETVL, VSETVLI, VSETIVLI}))
                ||  (instruction_operation_i inside {VLOAD, VSTORE})
                ) && !hazard_detected)
                    next_state = V_EXEC;
                else
                    next_state = V_IDLE;

            V_EXEC:
                if ((
                    (vlmul_effective inside {LMUL_1, LMUL_1_2, LMUL_1_4, LMUL_1_8}  && cycle_count_vd < 1)
                ||  (vlmul_effective == LMUL_2  && cycle_count_vd < 2)
                ||  (vlmul_effective == LMUL_4  && cycle_count_vd < 4)
                ||  (vlmul_effective == LMUL_8  && cycle_count_vd < 8)
                )
                && (!vector_process_done)
                )
                    next_state = V_EXEC;
                else if (!hold)
                    next_state = V_IDLE;
                else
                    next_state = V_EXEC;

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
                    //$error("Widening operations with VSEW=32b are not supported");
                end
            endcase
        end
        else begin
            vsew_effective = vsew;
        end
    end

    always_comb begin
        if (vector_operation_i inside {VMVXS, VMVSX}) begin
            vlmul_effective = LMUL_1;
        end
        else if (vector_operation_i == VMVR) begin
            unique case (instruction_i[17:15])
                3'h1:    vlmul_effective = LMUL_2;
                3'h3:    vlmul_effective = LMUL_4;
                3'h7:    vlmul_effective = LMUL_8;
                default: vlmul_effective = LMUL_1;
            endcase
        end
        else if (whole_reg_load_store) begin
            unique case (instruction_i[31:29])
                3'h1:    vlmul_effective = LMUL_2;
                3'h3:    vlmul_effective = LMUL_4;
                3'h7:    vlmul_effective = LMUL_8;
                default: vlmul_effective = LMUL_1;
            endcase
        end
        else if (widening_instruction) begin
            unique case (vlmul)
                LMUL_1:
                    vlmul_effective = LMUL_2;
                LMUL_2:
                    vlmul_effective = LMUL_4;
                LMUL_4:
                    vlmul_effective = LMUL_8;
                LMUL_8: begin
                    vlmul_effective = LMUL_8;
                    //$error("Widening operations with LMUL=8 are not supported");
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
        else if (next_state == V_EXEC && !hold)
            cycle_count <= cycle_count + 1;

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count_vd <= 0;
        else if (next_state == V_IDLE)
            cycle_count_vd <= 0;
        else if (next_state == V_EXEC && (!hold || hold_widening))
            cycle_count_vd <= cycle_count_vd + 1;

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count_r <= 0;
        else if (widening_instruction)
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
        else if (whole_reg_load_store)
            vl_curr_reg <= '1;
        else if (state == V_IDLE && next_state == V_EXEC)
            vl_curr_reg <= vl;
        else if (next_state == V_EXEC && !hold)
            if ($signed(vl_curr_reg - elements_per_reg) >= 0)
                vl_curr_reg <= vl_curr_reg - elements_per_reg;
            else
                vl_curr_reg <= 0;

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            total_elements_processed <= 0;
        else if (next_state == V_IDLE)
            total_elements_processed <= 0;
        else if (!hold)
            total_elements_processed <= total_elements_processed + elements_per_reg;

    assign vector_process_done = (total_elements_processed >= vl && !whole_reg_load_store && instruction_operation_i == VECTOR);

//////////////////////////////////////////////////////////////////////////////
// Register Bank
//////////////////////////////////////////////////////////////////////////////

    // ADDRESS CALCULATION
    assign rs1_addr = cycle_count + rs1;
    assign rs2_addr = cycle_count + rs2;
    assign rd_addr  = cycle_count + rd;

    always_comb begin
        // VS1 Address
        vs1_addr =  (instruction_operation_i == VSTORE)
                    ? rd_addr
                    : rs1_addr;

        // VS2 Address
        if (accumulate_instruction) begin
            if (!hold_accumulation) begin
                unique case (vector_operation_i)
                    VMADD, VNMSUB: vs2_addr = rd_addr;
                    default:       vs2_addr = rs2_addr;
                endcase
            end
            else begin
                unique case (vector_operation_i)
                    VMADD, VNMSUB: vs2_addr = rs2_addr - 1;
                    default:       vs2_addr = vd_addr;
                endcase
            end
        end
        else begin
            vs2_addr = rs2_addr;
        end
    end

    always_ff @(posedge clk) begin
        if (!hold || hold_widening) begin
            vd_addr   <= (reduction_instruction || mask_instruction)
                        ? rd
                        : rd + cycle_count_vd;
            vd_addr_r <= vd_addr;
        end
    end

    // WRITE ENABLE GENERATION
    always_ff @(posedge clk) begin
        if ((state == V_EXEC) && (!hold || hold_widening) && instruction_operation_i != VSTORE && vector_operation_i != VMVXS) begin
            if (reduction_instruction || vector_operation_i == VMVSX) begin
                unique case (vsew_effective)
                    EW8:     write_enable <= {'0, 1'b1};
                    EW16:    write_enable <= {'0, 2'b11};
                    default: write_enable <= {'0, 4'b1111};
                endcase
            end
            else if (whole_reg_load_store || mask_instruction) begin
                write_enable <= '1;
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
        .Environment (Environment),
        .VLEN        (VLEN),
        .VLENB       (VLENB)
    ) vectorRegbank1 (
        .clk      (clk),
        .reset_n  (reset_n),
        .vs1_addr (vs1_addr),
        .vs2_addr (vs2_addr),
        .enable   (write_enable),
        .vd_addr  (vd_addr_r),
        .result   (result),
        .v0_mask  (v0_mask),
        .vs1_data (vs1_data),
        .vs2_data (vs2_data)
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
        if (!hold || hold_accumulation) begin
            first_operand  <= vs2_data;
        end
    end

    always_ff @(posedge clk) begin
        if (!hold || hold_accumulation) begin
            if (instruction_operation_i == VSTORE) begin
                second_operand <= vs1_data;
            end
            else begin
                unique case (opCat)
                    OPIVX, OPFVF, OPMVX: second_operand <= scalar_replicated;
                    OPIVI:               second_operand <= imm_replicated;
                    default:             second_operand <= vs1_data;
                endcase
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// LOAD AND STORE UNIT
//////////////////////////////////////////////////////////////////////////////

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
        .write_data_i           (second_operand),
        .current_state          (state),
        .hazard_detected_i      (hazard_detected),
        .instruction_operation_i(instruction_operation_i),
        .whole_reg_load_store   (whole_reg_load_store),
        .vlmul                  (vlmul_effective),
        .cycle_count_r          (cycle_count_r),
        .vl                     (vl),
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
        .hold_accumulation_o(hold_accumulation),
        .result_mask_o      (result_alu_mask),
        .result_o           (result_alu)
    );

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    iType_e instruction_operation_r;
    logic   mask_instruction_r;

    always_ff @(posedge clk) begin
        instruction_operation_r <= instruction_operation_i;
        mask_instruction_r      <= mask_instruction;
    end

    always_comb begin
        if (instruction_operation_r == VLOAD)
            result = result_lsu;
        else if (mask_instruction_r)
            result = result_alu_mask;
        else
            result = result_alu;
    end

//////////////////////////////////////////////////////////////////////////////
// Scalar Result
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (vector_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
            res_scalar_o   = vl_next;
            wr_en_scalar_o = 1'b1;
        end
        else if (vector_operation_i == VMVXS) begin
            unique case (vsew_effective)
                EW8:     res_scalar_o = {'0, first_operand[7:0]};
                EW16:    res_scalar_o = {'0, first_operand[15:0]};
                default: res_scalar_o =      first_operand[31:0];
            endcase
            wr_en_scalar_o = 1'b1;
        end
        else begin
            res_scalar_o   = '0;
            wr_en_scalar_o = 1'b0;
        end
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC */
