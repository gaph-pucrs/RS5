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
    logic       is_vv, is_vi;

    assign opCat  = opCat_e'(funct3);
    assign funct6 = funct7[6:1];
    assign vm     = funct7[0];
    assign vd     = instruction_i[11:7];
    assign vs1    = instruction_i[19:15];
    assign vs2    = instruction_i[24:20];
    assign is_vv  = (opCat == OPIVV);
    assign is_vi  = (opCat == OPIVI);

    ////////////////////////////////////////////////////////////////////////
    // Configuration
    ////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_i[31:30]) inside
            2'b0?:      decode_vector_opcfg = VSETVLI;
            2'b11:      decode_vector_opcfg = VSETIVLI;
            /* vsetvl requires funct7 = 1000000 */
            2'b10:      decode_vector_opcfg = (instruction_i[29:25] == '0) ? VSETVL : VNOP;
            default:    decode_vector_opcfg = VNOP;
        endcase
    end

    ////////////////////////////////////////////////////////////////////////
    // OPIVV, OPIVX, OPIVI: each funct6 is only legal in the forms it has,
    // and only when its class is enabled
    ////////////////////////////////////////////////////////////////////////

    /* vmv<nr>r.v: nr - 1 is in simm and must be 0, 1, 3 or 7 */
    logic vmvr_legal;
    assign vmvr_legal = is_vi && vm && (vs1 inside {5'd0, 5'd1, 5'd3, 5'd7})
                     && ((vd  & vs1) == '0) && ((vs2 & vs1) == '0);

    always_comb begin
        unique case (funct6) inside
            6'b000000:     decode_vector_opi = VADD;
            6'b000010:     decode_vector_opi = !is_vi ? VSUB  : VNOP;
            6'b000011:     decode_vector_opi = !is_vv ? VRSUB : VNOP;
            6'b000100:     decode_vector_opi = (VMinMaxEnable && !is_vi) ? VMINU : VNOP;
            6'b000101:     decode_vector_opi = (VMinMaxEnable && !is_vi) ? VMIN  : VNOP;
            6'b000110:     decode_vector_opi = (VMinMaxEnable && !is_vi) ? VMAXU : VNOP;
            6'b000111:     decode_vector_opi = (VMinMaxEnable && !is_vi) ? VMAX  : VNOP;
            6'b001001:     decode_vector_opi = VLogicEnable ? VAND : VNOP;
            6'b001010:     decode_vector_opi = VLogicEnable ? VOR  : VNOP;
            6'b001011:     decode_vector_opi = VLogicEnable ? VXOR : VNOP;
            /* vmv.v.* (vm = 1) requires vs2 = 0; vmerge is the vm = 0 form */
            6'b010111:     decode_vector_opi = !vm ? (VMergeEnable ? VMERGE : VNOP)
                                             : ((vs2 == '0) ? VMV : VNOP);
            6'b011000:     decode_vector_opi = VMSEQ;
            6'b011001:     decode_vector_opi = VMSNE;
            6'b011010:     decode_vector_opi = !is_vi ? VMSLTU : VNOP;
            6'b011011:     decode_vector_opi = !is_vi ? VMSLT  : VNOP;
            6'b011100:     decode_vector_opi = VMSLEU;
            6'b011101:     decode_vector_opi = VMSLE;
            6'b011110:     decode_vector_opi = !is_vv ? VMSGTU : VNOP;
            6'b011111:     decode_vector_opi = !is_vv ? VMSGT  : VNOP;
            6'b100101:     decode_vector_opi = VSLL;
            /* .vi is vmv<nr>r; .vv and .vx are vsmul (P4) */
            6'b100111:     decode_vector_opi = vmvr_legal ? VMVR : VNOP;
            6'b101000:     decode_vector_opi = VSRL;
            6'b101001:     decode_vector_opi = VSRA;
            default:       decode_vector_opi = VNOP;
        endcase
    end

    ////////////////////////////////////////////////////////////////////////
    // OPMVV, OPMVX
    ////////////////////////////////////////////////////////////////////////

    logic is_mvv;
    assign is_mvv = (opCat == OPMVV);

    always_comb begin
        unique case (funct6) inside
            /* Reductions only exist as .vs (OPMVV) */
            6'b000000:     decode_vector_opm = (VRedSumEnable    && is_mvv) ? VREDSUM  : VNOP;
            6'b000001:     decode_vector_opm = (VRedLogicEnable  && is_mvv) ? VREDAND  : VNOP;
            6'b000010:     decode_vector_opm = (VRedLogicEnable  && is_mvv) ? VREDOR   : VNOP;
            6'b000011:     decode_vector_opm = (VRedLogicEnable  && is_mvv) ? VREDXOR  : VNOP;
            6'b000100:     decode_vector_opm = (VRedMinMaxEnable && is_mvv) ? VREDMINU : VNOP;
            6'b000101:     decode_vector_opm = (VRedMinMaxEnable && is_mvv) ? VREDMIN  : VNOP;
            6'b000110:     decode_vector_opm = (VRedMinMaxEnable && is_mvv) ? VREDMAXU : VNOP;
            6'b000111:     decode_vector_opm = (VRedMinMaxEnable && is_mvv) ? VREDMAX  : VNOP;
            6'b001110:     decode_vector_opm = !is_mvv ? VSLIDE1UP   : VNOP;
            6'b001111:     decode_vector_opm = !is_mvv ? VSLIDE1DOWN : VNOP;
            /* OPMVV (VWXUNARY0) selects by vs1: vmv.x.s is 00000,  */
            /* vcpop and vfirst (P5) are 10000 and 10001.           */
            /* OPMVX (VRXUNARY0) is vmv.s.x, which requires vs2 = 0 */
            6'b010000:     decode_vector_opm = !vm                 ? VNOP
                                             : !is_mvv             ? ((vs2 == '0) ? VMVSX : VNOP)
                                             : (vs1 == '0)         ? VMVXS
                                             :                       VNOP;
            6'b100000:     decode_vector_opm = VDivEnable ? VDIVU : VNOP;
            6'b100001:     decode_vector_opm = VDivEnable ? VDIV  : VNOP;
            6'b100010:     decode_vector_opm = VDivEnable ? VREMU : VNOP;
            6'b100011:     decode_vector_opm = VDivEnable ? VREM  : VNOP;
            6'b100100:     decode_vector_opm = VMULHU;
            6'b100101:     decode_vector_opm = VMUL;
            6'b100110:     decode_vector_opm = VMULHSU;
            6'b100111:     decode_vector_opm = VMULH;
            6'b101101:     decode_vector_opm = VMACC;
            6'b101111:     decode_vector_opm = VNMSAC;
            6'b101001:     decode_vector_opm = VMADD;
            6'b101011:     decode_vector_opm = VNMSUB;
            6'b111000:     decode_vector_opm = VWMULU;
            6'b111010:     decode_vector_opm = VWMULSU;
            6'b111011:     decode_vector_opm = VWMUL;
            default:       decode_vector_opm = VNOP;
        endcase
    end

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
    /* (compares) or a scalar element (reductions).                  */
    logic writes_v0_masked;
    assign writes_v0_masked = (opCat != OPCFG) && !vm && (vd == '0)
                            && !(decode_vector_opv inside {VMSEQ, VMSNE, VMSLTU, VMSLT, VMSLEU, VMSLE,
                                                           VMSGTU, VMSGT, VREDSUM, VREDAND, VREDOR, VREDXOR,
                                                           VREDMINU, VREDMIN, VREDMAXU, VREDMAX});

    assign decode_vector_arith = writes_v0_masked ? VNOP : decode_vector_opv;

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

    assign nf    = instruction_i[31:29];
    assign mew   = instruction_i[28];
    assign mop   = instruction_i[27:26];
    assign lumop = instruction_i[24:20];

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
    assign store_legal = mem_legal && !(mop == 2'b00 && lumop == 5'b01000 && funct3 != 3'b000);

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
    assign whole_reg_mem = (instruction_operation_i inside {VLOAD, VSTORE}) && (mop == 2'b00) && (lumop == 5'b01000);

    assign vector_uses_vtype_o = (vector_operation_o != VNOP) && !whole_reg_mem
                              && !(vector_operation_o inside {VSETVL, VSETVLI, VSETIVLI, VMVR});

endmodule
