`include "RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorCSRs
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64,
    parameter int VLENB = 8
) (
    input   logic                   clk,
    input   logic                   reset_n,

    input   iType_e                 instruction_operation_i,
    input   iTypeVector_e           vector_operation_i,
    input   logic [31:0]            op1_scalar_i,
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]            op2_scalar_i,
    input   logic [10:0]            zimm,
    /* verilator lint_on UNUSEDSIGNAL */
    input   logic [4:0]             rs1,
    input   logic [4:0]             rd,

    output  logic [31:0]            vtype_o,
    output  logic [31:0]            vlen_o,

    output  vew_e                   vsew,
    output  vlmul_e                 vlmul,
    output  logic[$bits(VLEN)-1:0]  vl,
    output  logic[$bits(VLEN)-1:0]  vl_next
);

    logic [$bits(VLENB)-1:0] elementsPerRegister;
    logic [$bits(VLEN)-1:0]  vl_max;
    logic        vill, vill_next, vma, vma_next, vta, vta_next;
    vew_e        vsew_next;
    vlmul_e      vlmul_next;
    logic        cfg_error, cfg_error_r;

//////////////////////////////////////////////////////////////////////////////
// Combinational
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        case (vlmul_next)
            LMUL_1_8:   cfg_error = (vsew_next inside {EW16, EW32, EW64})
                                    ? 1'b1
                                    : 1'b0;
            LMUL_1_4:   cfg_error = (vsew_next inside {EW32, EW64})
                                    ? 1'b1
                                    : 1'b0;
            LMUL_1_2:   cfg_error = (vsew_next == EW64)
                                    ? 1'b1
                                    : 1'b0;
            default:    cfg_error   = 1'b0;
        endcase
    end

    always_comb begin
        if (vector_operation_i == VSETVL) begin
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
    always_comb begin
        case (vlmul_next)
            LMUL_1_8:   vl_max = VLENB/8;
            LMUL_1_4:   vl_max = (vsew_next == EW8) ? VLENB/4 : VLENB/8;
            LMUL_1_2:   vl_max = (vsew_next == EW8) ? VLENB/2 : (vsew_next == EW16) ? VLENB/4 : VLENB/8;
            default:    vl_max   = elementsPerRegister << vlmul_next;
        endcase
    end

    always_comb begin
        if (vector_operation_i == VSETIVLI)
            vl_next = ({'0, rs1} > vl_max) ? vl_max : {'0, rs1};
        else if (rd != '0 && rs1 == '0)
            vl_next = vl_max;
        else if (rd == '0 && rs1 == '0)
            vl_next = vl;
        else
            vl_next = (op1_scalar_i > vl_max) ? vl_max : op1_scalar_i;
            //vl_next = (vector_operation_i == VSETVL) ? op1_scalar_i : {'0, op1_scalar_i[4:0]};
    end

//////////////////////////////////////////////////////////////////////////////
// Registers
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            cfg_error_r <= 1'b0;
            vill        <= 1'b0;
            vma         <= 1'b0;
            vta         <= 1'b0;
            vsew        <= EW8;
            vlmul       <= LMUL_1;
            vl          <= '0;
        end
        else if (instruction_operation_i == VECTOR && vector_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
            cfg_error_r <= cfg_error;
            vill        <= vill_next | cfg_error;
            vma         <= vma_next;
            vta         <= vta_next;
            vsew        <= vsew_next;
            vlmul       <= vlmul_next;
            vl          <=  (cfg_error)
                            ? '0
                            : vl_next;

            //$display("[%0t] Set VSEW = %s, VLMUL = %s, VL = %d\n", $time, vsew_next, vlmul_next, vl_next);
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    assign vlen_o   = {'0, vl};
    assign vtype_o  = (cfg_error_r)
                    ? {1'b1, 31'b0}
                    : {vill, 23'b0, vma, vta, vsew, vlmul};

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
