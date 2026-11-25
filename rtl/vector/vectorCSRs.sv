/*!\file vectorCSRs.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 */

`include "../RS5_pkg.sv"

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

    input   logic                   is_vector_op_i,
    input   iTypeVector_e           vector_operation_i,
    input   logic [31:0]            op1_scalar_i,
    input   logic [31:0]            op2_scalar_i,
    input   logic [10:0]            zimm,
    input   logic [4:0]             rs1,
    input   logic [4:0]             rd,

    output  logic [31:0]            vtype_o,
    output  logic [31:0]            vlen_o,
    output  logic                   vill_o,

    output  vew_e                   vsew,
    output  vlmul_e                 vlmul,
    output  logic[$bits(VLEN)-1:0]  vl,
    output  logic[$bits(VLEN)-1:0]  vl_next
);

    logic [$bits(VLENB)-1:0] elementsPerRegister;
    logic [$bits(VLEN)-1:0]  vl_max;
    logic        vill, vma, vma_next, vta, vta_next;
    vew_e        vsew_next;
    vlmul_e      vlmul_next;
    logic        cfg_error, reserved_bits;
    logic [$bits(VLEN)-1:0] vl_requested;

//////////////////////////////////////////////////////////////////////////////
// Combinational
//////////////////////////////////////////////////////////////////////////////

    /* vill is set for SEW > ELEN = 32, the reserved LMUL, the reserved vtype */
    /* bits, and for fractional LMUL with SEW > LMUL * ELEN (the minimum the  */
    /* spec requires): mf8 never, mf4 only with e8, mf2 with e8 and e16.      */
    always_comb begin
        if (reserved_bits || !(vsew_next inside {EW8, EW16, EW32}))
            cfg_error = 1'b1;
        else begin
            unique case (vlmul_next)
                LMUL_RSVD:  cfg_error = 1'b1;
                LMUL_1_8:   cfg_error = 1'b1;
                LMUL_1_4:   cfg_error = (vsew_next != EW8);
                LMUL_1_2:   cfg_error = (vsew_next == EW32);
                default:    cfg_error = 1'b0;
            endcase
        end
    end

    /* vsetvl takes vtype from rs2, where bit 31 (vill) and bits 30:8 are   */
    /* reserved. vsetvli has an 11-bit zimm and vsetivli a 10-bit one (zimm */
    /* bit 10 is then part of the opcode); bits 8 and up are reserved.      */
    always_comb begin
        unique case (vector_operation_i)
            VSETVL:     reserved_bits = (op2_scalar_i[31:8] != '0);
            VSETIVLI:   reserved_bits = (zimm[9:8] != '0);
            default:    reserved_bits = (zimm[10:8] != '0);
        endcase
    end

    always_comb begin
        if (vector_operation_i == VSETVL) begin
            vma_next   = op2_scalar_i[7];
            vta_next   = op2_scalar_i[6];
            vsew_next  = vew_e'(op2_scalar_i[5:3]);
            vlmul_next = vlmul_e'(op2_scalar_i[2:0]);
        end
        else begin
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
            vl_requested = ({'0, rs1} > vl_max) ? vl_max : {'0, rs1};
        else if (rd != '0 && rs1 == '0)
            vl_requested = vl_max;
        else if (rd == '0 && rs1 == '0)
            vl_requested = vl;
        else
            vl_requested = (op1_scalar_i > vl_max) ? vl_max : op1_scalar_i;
    end

    /* With vill set, vl and rd are 0 */
    assign vl_next = cfg_error ? '0 : vl_requested;

//////////////////////////////////////////////////////////////////////////////
// Registers
//////////////////////////////////////////////////////////////////////////////

    /* vtype resets with vill = 1 and vl = 0, as the spec recommends. With */
    /* vill set the other vtype fields read as 0.                          */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            vill        <= 1'b1;
            vma         <= 1'b0;
            vta         <= 1'b0;
            vsew        <= EW8;
            vlmul       <= LMUL_1;
            vl          <= '0;
        end
        else if (is_vector_op_i && vector_operation_i inside {VSETVL, VSETVLI, VSETIVLI}) begin
            vill        <= cfg_error;
            vma         <= cfg_error ? 1'b0   : vma_next;
            vta         <= cfg_error ? 1'b0   : vta_next;
            vsew        <= cfg_error ? EW8    : vsew_next;
            vlmul       <= cfg_error ? LMUL_1 : vlmul_next;
            vl          <= vl_next;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    assign vlen_o   = {'0, vl};
    assign vtype_o  = {vill, 23'b0, vma, vta, vsew, vlmul};
    assign vill_o   = vill;

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
