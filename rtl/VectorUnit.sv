module vectorUnit 
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

    logic [VLEN-1:0] result;
    logic [VLEN-1:0] first_operand, second_operand, third_operand;
    logic [VLEN-1:0] vs1_rd_data, vs2_rd_data, vd_rd_data;

    logic [4:0]      cycle_count;

    logic [$bits(VLEN/8)-1:0] elementsPerRegister;
    logic [$bits(VLEN)-1:0]   vl, vl_next, vl_max;
    logic [31:0] vtype, vstart;
    logic        vill, vill_next, vma, vma_next, vta, vta_next;
    vew_e        vsew, vsew_next;
    vlmul_e      vlmul, vlmul_next;

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
        case (vsew)
            EW8:     scalar_replicated = {(VLENB){op1_scalar_i[7:0]}};
            EW16:    scalar_replicated = {(VLENB/2){op1_scalar_i[15:0]}};
            default: scalar_replicated = {(VLENB/4){op1_scalar_i[31:0]}};
        endcase
    end

    always_comb begin 
        // unsigned
            if (vector_operation_i inside {vsrl, vsll, vsra}) begin
                case (vsew)
                    EW8:     imm_replicated = {(VLENB){'0, rs1}};
                    EW16:    imm_replicated = {(VLENB/2){'0, rs1}};
                    default: imm_replicated = {(VLENB/4){'0, rs1}};
                endcase
            // signed
            end
            else begin
                case (vsew)
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

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    assign hold_o = (next_state == V_EXEC);

    //logic   widening;
    //vew_e   vsew_effective;

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            state <= V_IDLE;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        case (state)
            V_IDLE:
                if (instruction_operation_i == VECTOR)
                    next_state = V_EXEC;
                else
                    next_state = V_IDLE;

            V_EXEC:
                if ((vlmul == LMUL_2 && cycle_count < 2) || (vlmul == LMUL_4 && cycle_count < 4) || (vlmul == LMUL_8 && cycle_count < 8))
                    next_state = V_EXEC;
                else
                    next_state = V_IDLE;
        endcase
    end
/*
    always_comb begin
        if (widening) begin
            case (vsew)
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
            vl_next <= vl;
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
            automatic int i;
            // Don't write to v0 (reserved for vector mask)
            if (wr_en & (vd_addr != '0)) begin
                for (i=0; i < VLENB; i++) begin
                    if (wr_en[i])
                        vregs[vd_addr][(8*(i+1))-1-:8]  <= result[(8*(i+1))-1-:8];
                end
            end
        end
    end

    // WRITE ENABLE GENERATION
    always_ff @(posedge clk) begin
        if (instruction_operation_i == VECTOR) begin
            if (vl > 0) begin
                automatic int i = 0;
                case (vsew)
                    EW8: begin
                        for (i = 0; i < VLENB; i++) begin
                            wr_en[i] <= (i < vl) ? 1'b1 : 1'b0;
                        end
                    end
                    EW16: begin
                        for (i = 0; i < VLENB/2; i++) begin
                            wr_en[(i*2)]   <= (i < vl) ? 1'b1 : 1'b0;
                            wr_en[(i*2)+1] <= (i < vl) ? 1'b1 : 1'b0;
                        end
                    end
                    default: begin
                        for (i = 0; i < VLENB/4; i++) begin
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

    logic [VLEN-1:0] summand_1, summand_2;
    logic [8:0]      result_add_bytes [VLENB-1:0];
    logic            adder_carry [VLENB-1:0];
    logic [VLEN-1:0] result_add;

    assign summand_1 = first_operand;
    assign summand_2 = (vector_operation_i == vadd) ? second_operand : -second_operand;

    always_comb begin
        automatic int i;
        for (i = 0; i < VLENB; i++) begin
            case (vsew)
                EW16:    adder_carry[i] = (i%2 == 0) ? 1'b0 : result_add_bytes[i-1][8];
                EW32:    adder_carry[i] = (i%4 == 0) ? 1'b0 : result_add_bytes[i-1][8];
                default: adder_carry[i] = 1'b0;
            endcase
        end
    end

    always_comb begin
        automatic int i;
        for (i = 0; i < VLENB; i++) begin
            result_add_bytes[i] = {1'b0, summand_1[(8*(i+1))-1-:8]} + {1'b0, summand_2[(8*(i+1))-1-:8]} + adder_carry[i];
        end
    end

    always_comb begin
        automatic int i;
        for (i = 0; i < VLENB; i++) begin
            result_add[(8*(i+1))-1-:8] = result_add_bytes[i][7:0];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case(vector_operation_i)
            vand:       result = result_and;
            vor:        result = result_or;
            vxor:       result = result_xor;
            vadd:       result = result_add;
            default:    result = '0;
        endcase
    end
endmodule