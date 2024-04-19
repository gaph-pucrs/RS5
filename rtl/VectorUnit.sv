module VectorUnit 
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
    parameter rv32_e        RV32        = RV32I,
    parameter int           VLEN        = 64
)
(
    input   logic           clk,
    input   logic           reset,

    input   logic [31:0]    instruction_i,
    input   iType_e         instruction_operation_i,
    input   iTypeVector_e   vector_operation_i,

    input   logic [31:0]    op1_scalar_i,
    input   logic [31:0]    op2_scalar_i,
    input   logic [31:0]    op3_scalar_i,

    output  logic           hold_o,

    output  logic [31:0]    res_scalar_o,
    output  logic           wr_en_scalar_o
);

    localparam VLENB = VLEN/8;

    vector_states_e  state, next_state;

    logic [VLEN-1:0]        result;
    logic [VLEN-1:0]        first_operand, second_operand, third_operand;
    logic signed [VLEN-1:0] first_operand_signed, second_operand_signed, third_operand_signed;

    logic [VLEN-1:0]        vs1_rd_data, vs2_rd_data, vd_rd_data;
    logic [4:0]             cycle_count;
    logic reduction_instruction;

    logic [$bits(VLEN/8)-1:0] elementsPerRegister;
    logic [$bits(VLEN)-1:0]   vl, vl_next, vl_max;
    logic [31:0] vtype, vstart;
    logic        vill, vill_next, vma, vma_next, vta, vta_next;
    vew_e        vsew, vsew_next;
    vlmul_e      vlmul, vlmul_next;

    assign reduction_instruction = (vector_operation_i inside {vredsum, vredmaxu, vredmax, vredminu, vredmin, vredand, vredor, vredxor});

//////////////////////////////////////////////////////////////////////////////
// Decoding
//////////////////////////////////////////////////////////////////////////////

    logic [ 4:0] rd, rs1, rs2;
    logic [ 2:0] funct3;
    logic [10:0] zimm;
    opCat_e      opCat;
    addrModes_e  addrMode;

    assign rd  = instruction_i[11:7];
    assign rs1 = instruction_i[19:15];
    assign rs2 = instruction_i[24:20];

    assign funct3   = instruction_i[14:12];
    assign zimm     = {instruction_i[30:20]};
    assign opCat    = opCat_e'(funct3);
    assign addrMode = addrModes_e'(instruction_i[27:26]);

//////////////////////////////////////////////////////////////////////////////
// Replicate Operands
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] scalar_replicated, imm_replicated;

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
                    EW8:     imm_replicated = {(VLENB){'0, rs1}};
                    EW16:    imm_replicated = {(VLENB/2){'0, rs1}};
                    default: imm_replicated = {(VLENB/4){'0, rs1}};
                endcase
            // signed
            end
            else begin
                unique case (vsew)
                    EW8:     imm_replicated = {(VLENB){{3{rs1[4]}}, rs1}};
                    EW16:    imm_replicated = {(VLENB/2){{11{rs1[4]}}, rs1}};
                    default: imm_replicated = {(VLENB/4){{27{rs1[4]}}, rs1}};
                endcase
            end
    end

//////////////////////////////////////////////////////////////////////////////
// Operands
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        // First Operand
        first_operand  <= vs2_rd_data;

        // Second Operand
        if (opCat inside {OPIVX, OPFVF, OPMVX}) begin
            second_operand <= scalar_replicated;
        end
        else if (opCat == OPIVI) begin
            second_operand <= imm_replicated;
        end
        else begin
            second_operand <= vs1_rd_data;
        end

        // Third Operand
        third_operand  <= vd_rd_data;
    end

    assign first_operand_signed  = first_operand;
    assign second_operand_signed = second_operand;
    assign third_operand_signed  = third_operand;

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    assign hold_o = (next_state == V_EXEC || next_state == V_END);

    //logic   widening;
    //vew_e   vsew_effective;

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            state <= V_IDLE;
        end
        else begin
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
    always_ff @(posedge clk) begin
        if (reset == 1'b1)
            cycle_count <= 0;
        else if (next_state == V_IDLE)
            cycle_count <= 0;
        else if (next_state == V_EXEC)
            cycle_count <= cycle_count + 1;
    end

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    // VLEN B

    assign vtype = {vill, 23'b0, vma, vta, vsew, vlmul};

    always_comb begin
        // VTYPE Next
        if (instruction_operation_i == VSETVL) begin
            vill_next  = op2_scalar_i[31];
            vma_next   = op2_scalar_i[7];
            vta_next   = op2_scalar_i[6];
            vsew_next  = vew_e'(op2_scalar_i[5:3]);
            vlmul_next = vlmul_e'(op2_scalar_i[2:0]);
        end
        else begin
            vill_next  = zimm[8];
            vma_next   = zimm[7];
            vta_next   = zimm[6];
            vsew_next  = vew_e'(zimm[5:3]);
            vlmul_next = vlmul_e'(zimm[2:0]);
        end

        // Number of elements that fit into a register for each value of VSEW by dividing vlenb by vsew
        elementsPerRegister = VLENB >> vsew_next;
        
        // Max VL value equals the max number of elements per register * LMUL.
        vl_max = elementsPerRegister << vlmul_next;

        // VL Next
        if (instruction_operation_i == VSETIVLI) begin
            vl_next = {'0, rs1};
        end
        else if (instruction_operation_i inside {VSETVL, VSETVLI}) begin
            if (rd != '0 && rs1 == '0)
                vl_next = vl_max;
            else if (rd == '0 && rs1 == '0)
                vl_next = vl;
            else
                vl_next = (instruction_operation_i == VSETVL) ? op1_scalar_i : {'0, op1_scalar_i[4:0]};
        end
        else begin
            vl_next = vl;
        end
    end

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            vill  <= 1'b0;
            vma   <= 1'b0; 
            vta   <= 1'b0; 
            vsew  <= vew_e'('0);
            vlmul <= vlmul_e'('0);
            vl    <= '0;
        end
        else if (instruction_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
            vill  <= vill_next;
            vma   <= vma_next; 
            vta   <= vta_next; 
            vsew  <= vsew_next; 
            vlmul <= vlmul_next;

            if (!(rd == '0 && rs1 == '0)) begin
                vl <= vl_next;
            end

            $display("[%0t] Set VSEW = %s, VLMUL = %s, VL = %d\n", $time/1000, vsew_next, vlmul_next, vl_next);
        end
    end

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

//////////////////////////////////////////////////////////////////////////////
// Registers
//////////////////////////////////////////////////////////////////////////////

    logic [31:0][VLEN-1:0] vregs;

    logic [4:0] vs1_addr;
    logic [4:0] vs2_addr;
    logic [4:0] vd_addr;

    logic [VLENB-1:0] wr_en;

    // ADDRESS CALCULATION
    always_comb begin
        vs1_addr = rs1 + cycle_count;
        vs2_addr = rs2 + cycle_count;
        vd_addr  = rd  + cycle_count - 1;
    end

    // REGISTER READ
    assign vs1_rd_data = vregs[vs1_addr];
    assign vs2_rd_data = vregs[vs2_addr];
    assign vd_rd_data  = vregs[vd_addr];

    // REGISTER WRITE
    always_ff @(posedge clk) begin
        if (reset == 1'b1)
            vregs <= '{32{'0}};
        else begin
            // Don't write to v0 (reserved for vector mask)
            if ((wr_en != '0) && (vd_addr != '0)) begin
                for (int i = 0; i < VLENB; i++) begin
                    if (wr_en[i])
                        vregs[vd_addr][(8*(i+1))-1-:8]  <= result[(8*(i+1))-1-:8];
                end
            end
        end
    end

    // WRITE ENABLE GENERATION
    always_ff @(posedge clk) begin
        if (instruction_operation_i == VECTOR && state == V_EXEC) begin
            if (vl > 0) begin
                unique case (vsew)
                    EW8: begin
                        for (int i = 0; i < VLENB; i++) begin
                            wr_en[i] <= (i < vl) ? 1'b1 : 1'b0;
                        end
                    end
                    EW16: begin
                        for (int i = 0; i < VLENB/2; i++) begin
                            wr_en[(i*2)]   <= (i < vl) ? 1'b1 : 1'b0;
                            wr_en[(i*2)+1] <= (i < vl) ? 1'b1 : 1'b0;
                        end
                    end
                    default: begin
                        for (int i = 0; i < VLENB/4; i++) begin
                            wr_en[(i*4)]   <= (i < vl) ? 1'b1 : 1'b0;
                            wr_en[(i*4)+1] <= (i < vl) ? 1'b1 : 1'b0;
                            wr_en[(i*4)+2] <= (i < vl) ? 1'b1 : 1'b0;
                            wr_en[(i*4)+3] <= (i < vl) ? 1'b1 : 1'b0;
                        end
                    end
                endcase
            end
            else begin
                wr_en <= '0;
            end             
        end
        else begin
            wr_en <= '0;
        end       
    end

//////////////////////////////////////////////////////////////////////////////
// Logical
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_and, result_or, result_xor;

    always_comb begin
        result_and = first_operand & second_operand;
        result_or  = first_operand | second_operand;
        result_xor = first_operand ^ second_operand;
    end

//////////////////////////////////////////////////////////////////////////////
// Arithmetic
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] subtraend_neg;
    logic [VLEN-1:0] subtraend_8b, subtraend_16b, subtraend_32b;
    logic [VLEN-1:0] summand_1, summand_2_8b, summand_2_16b, summand_2_32b;
    logic [VLEN-1:0] result_add_8b, result_add_16b, result_add_32b;
    logic [VLEN-1:0] result_add;

    assign subtraend_neg = ~second_operand;

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            subtraend_8b[(8*(i+1))-1-:8]    = subtraend_neg[(8*(i+1))-1-:8] + 1'b1;
        for (int i = 0; i < VLENB/2; i++)
            subtraend_16b[(16*(i+1))-1-:16] = subtraend_neg[(16*(i+1))-1-:16] + 1'b1;
        for (int i = 0; i < VLENB/4; i++)
            subtraend_32b[(32*(i+1))-1-:32] = subtraend_neg[(32*(i+1))-1-:32] + 1'b1;
    end

    assign summand_1 = first_operand;
    assign summand_2_8b = (vector_operation_i == vsub)  ? subtraend_8b : second_operand;
    assign summand_2_16b = (vector_operation_i == vsub)  ? subtraend_16b : second_operand;
    assign summand_2_32b = (vector_operation_i == vsub)  ? subtraend_32b : second_operand;

    always_comb begin
        for (int i = 0; i < VLENB; i++)
            result_add_8b[(8*(i+1))-1-:8]    = summand_1[(8*(i+1))-1-:8] + summand_2_8b[(8*(i+1))-1-:8];
        for (int i = 0; i < VLENB/2; i++)
            result_add_16b[(16*(i+1))-1-:16] = summand_1[(16*(i+1))-1-:16] + summand_2_16b[(16*(i+1))-1-:16];
        for (int i = 0; i < VLENB/4; i++)
            result_add_32b[(32*(i+1))-1-:32] = summand_1[(32*(i+1))-1-:32] + summand_2_32b[(32*(i+1))-1-:32];
    end

    always_comb begin
        unique case (vsew)
            EW8:    result_add = result_add_8b;
            EW16:   result_add = result_add_16b;
            default:result_add = result_add_32b;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Shifts
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_sll, result_srl, result_sra;

    always_comb begin
        unique case (vsew)
            EW8:
                for (int i = 0; i < VLENB; i++) begin
                    automatic logic [7:0] operand_sliced, operand_sliced_signed;
                    operand_sliced        = second_operand[(8*(i+1))-1-:8];
                    operand_sliced_signed = second_operand_signed[(8*(i+1))-1-:8];

                    result_sll[(8*(i+1))-1-:8]   = first_operand[(8*(i+1))-1-:8]           <<  operand_sliced[2:0];
                    result_srl[(8*(i+1))-1-:8]   = first_operand[(8*(i+1))-1-:8]           >>  operand_sliced[2:0];
                    result_sra[(8*(i+1))-1-:8]   = first_operand_signed[(8*(i+1))-1-:8]    >>> operand_sliced_signed[2:0];
                end
            EW16:
                for (int i = 0; i < VLENB/2; i++) begin
                    automatic logic [15:0] operand_sliced, operand_sliced_signed;
                    operand_sliced        = second_operand[(16*(i+1))-1-:16];
                    operand_sliced_signed = second_operand_signed[(16*(i+1))-1-:16];

                    result_sll[(16*(i+1))-1-:16] = first_operand[(16*(i+1))-1-:16]         <<  operand_sliced[3:0];
                    result_srl[(16*(i+1))-1-:16] = first_operand[(16*(i+1))-1-:16]         >>  operand_sliced[3:0];
                    result_sra[(16*(i+1))-1-:16] = first_operand_signed[(16*(i+1))-1-:16]  >>> operand_sliced_signed[3:0];
                end
            default:
                for (int i = 0; i < VLENB/4; i++) begin
                    automatic logic [31:0] operand_sliced, operand_sliced_signed;
                    operand_sliced        = second_operand[(32*(i+1))-1-:32];
                    operand_sliced_signed = second_operand_signed[(32*(i+1))-1-:32];

                    result_sll[(32*(i+1))-1-:32] = first_operand[(32*(i+1))-1-:32]         <<  operand_sliced[4:0];
                    result_srl[(32*(i+1))-1-:32] = first_operand[(32*(i+1))-1-:32]         >>  operand_sliced[4:0];
                    result_sra[(32*(i+1))-1-:32] = first_operand_signed[(32*(i+1))-1-:32]  >>> operand_sliced_signed[4:0];
                end
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Compare
//////////////////////////////////////////////////////////////////////////////

    logic [VLENB-1:0]     equal_8b,  greater_than_8b,  greater_than_signed_8b,  result_comparison_8b;
    logic [(VLENB/2)-1:0] equal_16b, greater_than_16b, greater_than_signed_16b, result_comparison_16b;
    logic [(VLENB/4)-1:0] equal_32b, greater_than_32b, greater_than_signed_32b, result_comparison_32b;

    always_comb begin
        for (int i = 0; i < VLENB; i++) begin
            equal_8b[i]                 = first_operand[(8*(i+1))-1-:8] == second_operand[(8*(i+1))-1-:8];
            greater_than_8b[i]          = first_operand[(8*(i+1))-1-:8] >  second_operand[(8*(i+1))-1-:8];
            greater_than_signed_8b[i]   = first_operand_signed[(8*(i+1))-1-:8] > second_operand_signed[(8*(i+1))-1-:8];
        end

        for (int i = 0; i < VLENB/2; i++) begin
            equal_16b[i]                 = first_operand[(16*(i+1))-1-:16] == second_operand[(16*(i+1))-1-:16];
            greater_than_16b[i]          = first_operand[(16*(i+1))-1-:16] >  second_operand[(16*(i+1))-1-:16];
            greater_than_signed_16b[i]   = first_operand_signed[(16*(i+1))-1-:16] > second_operand_signed[(16*(i+1))-1-:16];
        end

        for (int i = 0; i < VLENB/4; i++) begin
            equal_32b[i]               = first_operand[(32*(i+1))-1-:32] == second_operand[(32*(i+1))-1-:32];
            greater_than_32b[i]        = first_operand[(32*(i+1))-1-:32] >  second_operand[(32*(i+1))-1-:32];
            greater_than_signed_32b[i] = first_operand_signed[(32*(i+1))-1-:32] > second_operand_signed[(32*(i+1))-1-:32];
        end
    end

    always_comb begin
        unique case(vector_operation_i)
            vmsne:  begin 
                        result_comparison_8b  = ~equal_8b;
                        result_comparison_16b = ~equal_16b;
                        result_comparison_32b = ~equal_32b;
                    end 
            vmsltu: begin 
                        result_comparison_8b  = ~equal_8b  & ~greater_than_8b;
                        result_comparison_16b = ~equal_16b & ~greater_than_16b;
                        result_comparison_32b = ~equal_32b & ~greater_than_32b;
                    end 
            vmslt:  begin 
                        result_comparison_8b  = ~equal_8b  & ~greater_than_signed_8b;
                        result_comparison_16b = ~equal_16b & ~greater_than_signed_16b;
                        result_comparison_32b = ~equal_32b & ~greater_than_signed_32b;
                    end 
            vmsleu: begin 
                        result_comparison_8b  = equal_8b  | ~greater_than_8b;
                        result_comparison_16b = equal_16b | ~greater_than_16b;
                        result_comparison_32b = equal_32b | ~greater_than_32b;
                    end 
            vmsle:  begin 
                        result_comparison_8b  = equal_8b  | ~greater_than_signed_8b;
                        result_comparison_16b = equal_16b | ~greater_than_signed_16b;
                        result_comparison_32b = equal_32b | ~greater_than_signed_32b;
                    end 
            vmsgtu: begin 
                        result_comparison_8b  = greater_than_8b;
                        result_comparison_16b = greater_than_16b;
                        result_comparison_32b = greater_than_32b;
                    end 
            vmsgt : begin 
                        result_comparison_8b  = greater_than_signed_8b;
                        result_comparison_16b = greater_than_signed_16b;
                        result_comparison_32b = greater_than_signed_32b;
                    end 
            default:begin 
                        result_comparison_8b  = equal_8b;
                        result_comparison_16b = equal_16b;
                        result_comparison_32b = equal_32b;
                    end 
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Min/Max
//////////////////////////////////////////////////////////////////////////////

    logic [VLEN-1:0] result_minu, result_min, result_maxu, result_max;

    always_comb begin
        unique case (vsew)
            EW8:    begin
                        for (int i = 0; i < VLENB; i++) begin
                            result_minu[(8*(i+1))-1-:8] = (greater_than_8b[i])         ? second_operand[(8*(i+1))-1-:8] : first_operand [(8*(i+1))-1-:8];
                            result_min [(8*(i+1))-1-:8] = (greater_than_signed_8b[i])  ? second_operand[(8*(i+1))-1-:8] : first_operand [(8*(i+1))-1-:8];
                            result_maxu[(8*(i+1))-1-:8] = (greater_than_8b[i])         ? first_operand [(8*(i+1))-1-:8] : second_operand[(8*(i+1))-1-:8];
                            result_max [(8*(i+1))-1-:8] = (greater_than_signed_8b[i])  ? first_operand [(8*(i+1))-1-:8] : second_operand[(8*(i+1))-1-:8];
                        end
                    end

            EW16:   begin
                        for (int i = 0; i < VLENB/2; i++) begin
                            result_minu[(16*(i+1))-1-:16] = (greater_than_16b[i])         ? second_operand[(16*(i+1))-1-:16] : first_operand [(16*(i+1))-1-:16];
                            result_min [(16*(i+1))-1-:16] = (greater_than_signed_16b[i])  ? second_operand[(16*(i+1))-1-:16] : first_operand [(16*(i+1))-1-:16];
                            result_maxu[(16*(i+1))-1-:16] = (greater_than_16b[i])         ? first_operand [(16*(i+1))-1-:16] : second_operand[(16*(i+1))-1-:16];
                            result_max [(16*(i+1))-1-:16] = (greater_than_signed_16b[i])  ? first_operand [(16*(i+1))-1-:16] : second_operand[(16*(i+1))-1-:16];
                        end
                    end

            default:begin
                        for (int i = 0; i < VLENB/4; i++) begin
                            result_minu[(32*(i+1))-1-:32] = (greater_than_32b[i])         ? second_operand[(32*(i+1))-1-:32] : first_operand [(32*(i+1))-1-:32];
                            result_min [(32*(i+1))-1-:32] = (greater_than_signed_32b[i])  ? second_operand[(32*(i+1))-1-:32] : first_operand [(32*(i+1))-1-:32];
                            result_maxu[(32*(i+1))-1-:32] = (greater_than_32b[i])         ? first_operand [(32*(i+1))-1-:32] : second_operand[(32*(i+1))-1-:32];
                            result_max [(32*(i+1))-1-:32] = (greater_than_signed_32b[i])  ? first_operand [(32*(i+1))-1-:32] : second_operand[(32*(i+1))-1-:32];
                        end
                    end
        endcase
        
    end

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    always @(posedge clk ) begin
        if (reset == 1'b1) begin
            result <= '0;
        end        
        else begin
            unique case(vector_operation_i)
                vand:       result <= result_and;
                vor:        result <= result_or;
                vxor:       result <= result_xor;
                vadd, 
                //vrsub,
                vsub:       result <= result_add;
                vsll:       result <= result_sll;
                vsrl:       result <= result_srl;
                vsra:       result <= result_sra;
                vmin:       result <= result_min;
                vminu:      result <= result_minu;
                vmax:       result <= result_max;
                vmaxu:      result <= result_maxu;
                default:    result <= '0;
            endcase
        end
    end
endmodule