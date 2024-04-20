module vectorCSRs
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64,
    parameter int VLENB = 8
) (
    input   logic                   clk,
    input   logic                   reset_n,

    input   iType_e                 instruction_operation_i,
    input   logic [31:0]            op1_scalar_i,
    input   logic [31:0]            op2_scalar_i,
    input   logic [10:0]            zimm,
    input   logic [4:0]             rs1,
    input   logic [4:0]             rd,

    output  logic [31:0]            vtype,
    output  vew_e                   vsew,
    output  vlmul_e                 vlmul,
    output  logic[$bits(VLEN)-1:0]  vl,
    output  logic[$bits(VLEN)-1:0]  vl_next
);

    logic [$bits(VLENB)-1:0] elementsPerRegister;
    logic [$bits(VLEN)-1:0]  vl_max;
    logic [$bits(VLEN)-1:0]  vstart;
    logic        vill, vill_next, vma, vma_next, vta, vta_next;
    vew_e        vsew_next;
    vlmul_e      vlmul_next;

//////////////////////////////////////////////////////////////////////////////
// Combinational
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
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
    end

    // Number of elements that fit into a register for each value of VSEW by dividing vlenb by vsew
    assign elementsPerRegister = VLENB >> vsew_next;

    // Max VL value equals the max number of elements per register * LMUL.
    assign vl_max = elementsPerRegister << vlmul_next;

    always_comb begin
        if (instruction_operation_i == VSETIVLI)
            vl_next = {'0, rs1};
        else if (rd != '0 && rs1 == '0)
            vl_next = vl_max;
        else if (rd == '0 && rs1 == '0)
            vl_next = vl;
        else
            vl_next = op1_scalar_i;
            //vl_next = (instruction_operation_i == VSETVL) ? op1_scalar_i : {'0, op1_scalar_i[4:0]};
    end

//////////////////////////////////////////////////////////////////////////////
// Registers
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            vill  <= 1'b0;
            vma   <= 1'b0; 
            vta   <= 1'b0; 
            vsew  <= EW8;
            vlmul <= LMUL_1;
            vl    <= '0;
        end
        else if (instruction_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
            vill  <= vill_next;
            vma   <= vma_next; 
            vta   <= vta_next; 
            vsew  <= vsew_next; 
            vlmul <= vlmul_next;
            vl <= vl_next;

            $display("[%0t] Set VSEW = %s, VLMUL = %s, VL = %d\n", $time/1000, vsew_next, vlmul_next, vl_next);
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    assign vtype  = {vill, 23'b0, vma, vta, vsew, vlmul};
    assign vstart = '0;

endmodule