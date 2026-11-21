/*!\file vectorDecode.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 *
 * \brief
 * Vector instruction decoder, instantiated by the decode stage.
 *
 * \detailed
 * Decodes the OP-V, LOAD-FP and STORE-FP instructions into a vector
 * operation. VNOP means the encoding is reserved or not supported, and
 * vector_invalid_o then raises an illegal instruction. It also tells
 * whether the instruction depends on vtype, so it traps when vill is set.
 */

`include "RS5_pkg.sv"

module vectorDecode
    import RS5_pkg::*;
#(
    parameter bit           VLogicEnable     = 1'b1,
    parameter bit           VMinMaxEnable    = 1'b1,
    parameter bit           VMergeEnable     = 1'b1,
    parameter bit           VDivEnable       = 1'b1,
    parameter bit           VRedLogicEnable  = 1'b1,
    parameter bit           VRedMinMaxEnable = 1'b1,
    parameter bit           VRedSumEnable    = 1'b1
)
(
    /* The opcode (bits 6:0) is decoded by the decode stage, into instruction_operation_i */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]    instruction_i,
    /* verilator lint_on UNUSEDSIGNAL */
    /* VECTOR (OP-V), VLOAD (LOAD-FP), VSTORE (STORE-FP) or any other operation */
    input   iType_e         instruction_operation_i,

    output  iTypeVector_e   vector_operation_o,
    output  logic           vector_invalid_o,
    output  logic           vector_uses_vtype_o
);

    logic [2:0] funct3;
    logic [6:0] funct7;

    assign funct3 = instruction_i[14:12];
    assign funct7 = instruction_i[31:25];

    iTypeVector_e decode_vector_opcfg;
    iTypeVector_e decode_vector_opi;
    iTypeVector_e decode_vector_opm;
    iTypeVector_e decode_vector_arith;
    iTypeVector_e decode_vector_load;
    iTypeVector_e decode_vector_store;

    opCat_e     opCat;
    logic [5:0] funct6;
    logic       vm;
    logic [4:0] vd, vs1, vs2;
    logic       is_mvv;

    assign opCat  = opCat_e'(funct3);
    assign funct6 = funct7[6:1];
    assign vm     = funct7[0];
    assign vd     = instruction_i[11:7];
    assign vs1    = instruction_i[19:15];
    assign vs2    = instruction_i[24:20];
    assign is_mvv = (opCat == OPMVV);

    ////////////////////////////////////////////////////////////////////////
    // Instruction classes
    ////////////////////////////////////////////////////////////////////////

    /* An operation of a disabled class decodes as VNOP (illegal) */
    function automatic logic class_enabled(iTypeVector_e op);
        case (op) inside
            VAND, VOR, VXOR:                        return VLogicEnable;
            VMINU, VMIN, VMAXU, VMAX:               return VMinMaxEnable;
            VMERGE:                                 return VMergeEnable;
            VDIVU, VDIV, VREMU, VREM:               return VDivEnable;
            VREDAND, VREDOR, VREDXOR:               return VRedLogicEnable;
            VREDMINU, VREDMIN, VREDMAXU, VREDMAX:   return VRedMinMaxEnable;
            VREDSUM:                                return VRedSumEnable;
            default:                                return 1'b1;
        endcase
    endfunction

    ////////////////////////////////////////////////////////////////////////
    // Forms. As in the opcode tables of the spec, each funct6 only exists
    // in some of the forms V (.vv, .vs), X (.vx) and I (.vi)
    ////////////////////////////////////////////////////////////////////////

    /* A set of forms, one bit each: {V, X, I} */
    typedef enum logic [2:0] {
        F_NONE = 3'b000,
        F_I    = 3'b001,
        F_X    = 3'b010,
        F_XI   = 3'b011,
        F_V    = 3'b100,
        F_VX   = 3'b110,
        F_VXI  = 3'b111
    } vForms_e;

    typedef struct packed {
        iTypeVector_e op;
        vForms_e      forms;
    } funct6_decode_t;

    /* The form of this instruction */
    vForms_e form;
    always_comb begin
        unique case (opCat) inside
            OPIVV, OPMVV:   form = F_V;
            OPIVX, OPMVX:   form = F_X;
            OPIVI:          form = F_I;
            default:        form = F_NONE;
        endcase
    end

    ////////////////////////////////////////////////////////////////////////
    // Configuration
    ////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_i[31:30]) inside
            2'b0?:      decode_vector_opcfg = VSETVLI;
            2'b11:      decode_vector_opcfg = VSETIVLI;
            /* vsetvl requires funct7 = 1000000 */
            2'b10:      decode_vector_opcfg = (instruction_i[29:25] == '0) ? VSETVL : VNOP;
        endcase
    end

    ////////////////////////////////////////////////////////////////////////
    // OPIVV, OPIVX, OPIVI
    ////////////////////////////////////////////////////////////////////////

    /* vmv<nr>r.v: nr - 1 is in simm and must be 0, 1, 3 or 7 */
    logic vmvr_legal;
    assign vmvr_legal = vm && (vs1 inside {5'd0, 5'd1, 5'd3, 5'd7})
                     && ((vd  & vs1) == '0) && ((vs2 & vs1) == '0);

    funct6_decode_t opi;
    always_comb begin
        unique case (funct6) inside
            6'b000000:     opi = '{VADD,   F_VXI};
            6'b000010:     opi = '{VSUB,   F_VX};
            6'b000011:     opi = '{VRSUB,  F_XI};
            6'b000100:     opi = '{VMINU,  F_VX};
            6'b000101:     opi = '{VMIN,   F_VX};
            6'b000110:     opi = '{VMAXU,  F_VX};
            6'b000111:     opi = '{VMAX,   F_VX};
            6'b001001:     opi = '{VAND,   F_VXI};
            6'b001010:     opi = '{VOR,    F_VXI};
            6'b001011:     opi = '{VXOR,   F_VXI};
            /* vmv.v.* (vm = 1) requires vs2 = 0; vmerge is the vm = 0 form */
            6'b010111:     opi = '{!vm ? VMERGE : ((vs2 == '0) ? VMV : VNOP), F_VXI};
            6'b011000:     opi = '{VMSEQ,  F_VXI};
            6'b011001:     opi = '{VMSNE,  F_VXI};
            6'b011010:     opi = '{VMSLTU, F_VX};
            6'b011011:     opi = '{VMSLT,  F_VX};
            6'b011100:     opi = '{VMSLEU, F_VXI};
            6'b011101:     opi = '{VMSLE,  F_VXI};
            6'b011110:     opi = '{VMSGTU, F_XI};
            6'b011111:     opi = '{VMSGT,  F_XI};
            6'b100101:     opi = '{VSLL,   F_VXI};
            /* .vi is vmv<nr>r; .vv and .vx are vsmul (P4) */
            6'b100111:     opi = '{vmvr_legal ? VMVR : VNOP, F_I};
            6'b101000:     opi = '{VSRL,   F_VXI};
            6'b101001:     opi = '{VSRA,   F_VXI};
            default:       opi = '{VNOP,   F_NONE};
        endcase
    end

    assign decode_vector_opi = ((opi.forms & form) != '0) ? opi.op : VNOP;

    ////////////////////////////////////////////////////////////////////////
    // OPMVV, OPMVX
    ////////////////////////////////////////////////////////////////////////

    funct6_decode_t opm;
    always_comb begin
        unique case (funct6) inside
            /* Reductions only exist as .vs (OPMVV) */
            6'b000000:     opm = '{VREDSUM,     F_V};
            6'b000001:     opm = '{VREDAND,     F_V};
            6'b000010:     opm = '{VREDOR,      F_V};
            6'b000011:     opm = '{VREDXOR,     F_V};
            6'b000100:     opm = '{VREDMINU,    F_V};
            6'b000101:     opm = '{VREDMIN,     F_V};
            6'b000110:     opm = '{VREDMAXU,    F_V};
            6'b000111:     opm = '{VREDMAX,     F_V};
            6'b001110:     opm = '{VSLIDE1UP,   F_X};
            6'b001111:     opm = '{VSLIDE1DOWN, F_X};
            /* OPMVV (VWXUNARY0) selects by vs1: vmv.x.s is 00000,  */
            /* vcpop and vfirst (P5) are 10000 and 10001.           */
            /* OPMVX (VRXUNARY0) is vmv.s.x, which requires vs2 = 0 */
            6'b010000:     opm = '{!vm        ? VNOP
                                 : !is_mvv    ? ((vs2 == '0) ? VMVSX : VNOP)
                                 : (vs1 == '0) ? VMVXS
                                 :              VNOP, F_VX};
            6'b100000:     opm = '{VDIVU,       F_VX};
            6'b100001:     opm = '{VDIV,        F_VX};
            6'b100010:     opm = '{VREMU,       F_VX};
            6'b100011:     opm = '{VREM,        F_VX};
            6'b100100:     opm = '{VMULHU,      F_VX};
            6'b100101:     opm = '{VMUL,        F_VX};
            6'b100110:     opm = '{VMULHSU,     F_VX};
            6'b100111:     opm = '{VMULH,       F_VX};
            6'b101101:     opm = '{VMACC,       F_VX};
            6'b101111:     opm = '{VNMSAC,      F_VX};
            6'b101001:     opm = '{VMADD,       F_VX};
            6'b101011:     opm = '{VNMSUB,      F_VX};
            6'b111000:     opm = '{VWMULU,      F_VX};
            6'b111010:     opm = '{VWMULSU,     F_VX};
            6'b111011:     opm = '{VWMUL,       F_VX};
            default:       opm = '{VNOP,        F_NONE};
        endcase
    end

    assign decode_vector_opm = ((opm.forms & form) != '0) ? opm.op : VNOP;

    ////////////////////////////////////////////////////////////////////////
    // OP-V
    ////////////////////////////////////////////////////////////////////////

    iTypeVector_e decode_vector_opv;
    always_comb begin
        unique case (opCat) inside
            OPCFG:               decode_vector_opv = decode_vector_opcfg;
            OPIVV, OPIVX, OPIVI: decode_vector_opv = decode_vector_opi;
            OPMVV, OPMVX:        decode_vector_opv = decode_vector_opm;
            default:             decode_vector_opv = VNOP;
        endcase
    end

    /* A masked instruction cannot write v0, unless it writes a mask */
    /* (compares) or a scalar element (reductions)                   */
    logic writes_v0_masked;
    assign writes_v0_masked = (opCat != OPCFG) && !vm && (vd == '0)
                            && !(is_mask_result(decode_vector_opv) || is_reduction(decode_vector_opv));

    assign decode_vector_arith = (writes_v0_masked || !class_enabled(decode_vector_opv)) ? VNOP : decode_vector_opv;


    ////////////////////////////////////////////////////////////////////////
    // LOAD-FP and STORE-FP
    ////////////////////////////////////////////////////////////////////////

    logic [2:0] nf;
    logic       mew;
    logic [1:0] mop;
    logic [4:0] lumop;
    logic       eew_legal;
    logic       whole_reg_legal;
    logic       mem_legal;
    logic       whole_reg;

    assign nf    = instruction_i[31:29];
    assign mew   = instruction_i[28];
    assign mop   = instruction_i[27:26];
    assign lumop = instruction_i[24:20];

    /* Whole register access: unit-stride with lumop = 01000 */
    assign whole_reg = (mop == 2'b00) && (lumop == 5'b01000);

    /* EEW 8, 16 and 32. Widths 001-100 are scalar FP (no F/D), 111 is EEW = 64 */
    assign eew_legal = (funct3 inside {3'b000, 3'b101, 3'b110}) && !mew;

    /* NFIELDS = nf + 1 must be 1, 2, 4 or 8, and vd a multiple of it */
    assign whole_reg_legal = vm && (nf inside {3'd0, 3'd1, 3'd3, 3'd7}) && ((vd[2:0] & nf) == '0);

    always_comb begin
        if (!eew_legal)
            mem_legal = 1'b0;
        else if (mop == 2'b00) begin
            unique case (lumop)
                /* Segments (nf != 0) are P8 */
                5'b00000:   mem_legal = (nf == '0);
                5'b01000:   mem_legal = whole_reg_legal;
                /* vlm.v and vsm.v are encoded with EEW = 8 */
                5'b01011:   mem_legal = vm && (nf == '0) && (funct3 == 3'b000);
                /* Fault-only-first (10000) is P8 */
                default:    mem_legal = 1'b0;
            endcase
        end
        else begin
            /* Strided and indexed segments are P8 */
            mem_legal = (nf == '0);
        end
    end

    /* Whole register stores are encoded with EEW = 8 and there is no fault-only-first store */
    logic store_legal;
    assign store_legal = mem_legal && !(whole_reg && funct3 != 3'b000);

    /* A masked load cannot write v0 */
    assign decode_vector_load  = (mem_legal && !(!vm && vd == '0)) ? VLD : VNOP;
    assign decode_vector_store = store_legal                       ? VST : VNOP;

    always_comb begin
        unique case (instruction_operation_i)
            VECTOR:  vector_operation_o = decode_vector_arith;
            VLOAD:   vector_operation_o = decode_vector_load;
            VSTORE:  vector_operation_o = decode_vector_store;
            default: vector_operation_o = VNOP;
        endcase
    end

    assign vector_invalid_o = (instruction_operation_i inside {VECTOR, VLOAD, VSTORE}) && (vector_operation_o == VNOP);

    /* vset*, whole register loads/stores and vmv<nr>r do not depend on */
    /* vtype, so they do not trap when vill is set                      */
    logic whole_reg_mem;
    assign whole_reg_mem = (instruction_operation_i inside {VLOAD, VSTORE}) && whole_reg;

    assign vector_uses_vtype_o = (vector_operation_o != VNOP) && !whole_reg_mem
                              && !(vector_operation_o inside {VSETVL, VSETVLI, VSETIVLI, VMVR});

endmodule
