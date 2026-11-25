/*!\file vectorUnit.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 */

`include "RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorUnit
    import RS5_pkg::*;
#(
    parameter environment_e Environment           = ASIC,
    parameter int           VLEN                  = 64,
    parameter int           LLEN                  = 32,
    parameter int           BUS_WIDTH             = 32,
    parameter bit           VLogicEnable          = 1'b1,
    parameter bit           VMinMaxEnable         = 1'b1,
    parameter bit           VMergeEnable          = 1'b1,
    parameter bit           VCarryEnable          = 1'b1,
    parameter bit           VDivEnable            = 1'b1,
    parameter bit           VRedLogicEnable       = 1'b1,
    parameter bit           VRedMinMaxEnable      = 1'b1,
    parameter bit           VRedSumEnable         = 1'b1,
    parameter bit           VMultiCycleReductions = 1'b0
)
(
    input   logic                  clk,
    input   logic                  reset_n,
    input   logic                  stall,

    input   logic [31:0]           instruction_i,
    input   logic                  enable_i,
    input   iTypeVector_e          vector_operation_i,

    input   logic [31:0]           op1_scalar_i,
    input   logic [31:0]           op2_scalar_i,

    output  logic                  hold_o,

    output  logic [31:0]           vtype_o,
    output  logic [31:0]           vlen_o,
    output  logic                  vill_o,
    /* Reserved register group or SEW/LMUL for the instruction (traps) */
    output  logic                  illegal_cfg_o,

    output logic [31:0]            mem_address_o,
    output logic                   mem_read_enable_o,
    output logic [BUS_WIDTH/8-1:0] mem_write_enable_o,
    output logic [BUS_WIDTH-1:0]   mem_write_data_o,
    input  logic [BUS_WIDTH-1:0]   mem_read_data_i,

    output  logic [31:0]           res_scalar_o,
    output  logic                  wr_en_scalar_o
);

    localparam VLENB = VLEN/8;

    // Decoding signals
    logic [ 4:0] rd, rs1, rs2;
    logic [10:0] zimm;
    logic        vm;
    opCat_e      opCat;
    logic        op_vector, op_vload, op_vstore;
    logic        accumulate_instruction;
    logic        mask_instruction;
    logic        multiply_instruction;
    logic        reduction_instruction;
    logic        widening_instruction;
    logic        widening_multiply;
    logic        integer_extension;
    logic        widening_reduction;
    logic        whole_reg_load_store;
    logic        whole_reg_instruction;
    logic        mask_load_store;

    logic        accumulate_instruction_r;
    logic        mask_instruction_nr;
    logic        multiply_instruction_r;
    logic        reduction_instruction_r;
    logic        widening_multiply_r;

    /* Control decoded once from the operation (fields are added per package) */
    vector_ctrl_t vctrl;

    vew_e   vsew, vsew_effective;
    vlmul_e vlmul, vlmul_effective;
    logic[$bits(VLEN )-1:0] vl, vl_curr_reg, vl_next_reg, vl_next;
    logic[$bits(VLENB)-1:0] elements_per_reg;
    logic[$bits(VLEN )-1:0] total_elements_processed;
    logic                   vector_process_done;

    vector_states_e  state, next_state;

    logic [VLEN-1:0]  scalar_replicated, imm_replicated;
    logic [VLEN-1:0]  v0_mask;

    logic [4:0]       rs1_addr, rs2_addr, rd_addr;
    logic [4:0]       vs1_addr, vs2_addr;
    logic [VLEN-1:0]  vs1_data, vs2_data;
    logic [3:0]       cycle_count, cycle_count_r;
    /* Up to 16: vwredsum with LMUL = 8 reads each source register twice */
    logic [4:0]       cycle_count_vd;
    logic             hazard_detected;
    logic             hold, hold_widening, hold_alu, hold_lsu;
    logic             should_stall;

    logic [VLEN-1:0]  first_operand, second_operand, third_operand;

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

    assign op_vload  = enable_i && (vector_operation_i == VLD);
    assign op_vstore = enable_i && (vector_operation_i == VST);
    assign op_vector = enable_i && !(vector_operation_i == VLD) && !(vector_operation_i == VST);

    assign accumulate_instruction = (vector_operation_i inside {VMACC, VNMSAC, VMADD, VNMSUB});
    assign multiply_instruction   = (vector_operation_i inside {VMUL, VMULH, VMULHSU, VMULHU} | accumulate_instruction | widening_multiply);
    assign reduction_instruction  = is_reduction(vector_operation_i);
    /* Widening: the destination has EEW = 2*SEW and EMUL = 2*LMUL. The */
    /* widening multiply and multiply-add write both destination        */
    /* registers of a source register from one product (hold_widening); */
    /* the widening add and subtract extend their sources and iterate   */
    /* over the destination                                             */
    assign widening_multiply      = (vector_operation_i inside {VWMUL, VWMULU, VWMULSU,
                                                                VWMACCU, VWMACC, VWMACCSU, VWMACCUS});
    assign widening_instruction   = widening_multiply || (vector_operation_i inside {VWADDU, VWADD, VWSUBU, VWSUB,
                                                                                      VWADDU_W, VWADD_W, VWSUBU_W, VWSUB_W});
    assign integer_extension      = (vector_operation_i inside {VZEXT, VSEXT});
    /* The widening sum reductions extend vs2 and reduce it at 2*SEW */
    assign widening_reduction     = (vector_operation_i inside {VWREDSUMU, VWREDSUM});
    assign whole_reg_load_store   = (instruction_i[24:20] == 5'b01000 && (op_vload || op_vstore) && instruction_i[27:26] == 2'b00);
    assign mask_load_store        = (instruction_i[24:20] == 5'b01011 && (op_vload || op_vstore) && instruction_i[27:26] == 2'b00);
    /* Whole register loads/stores and vmv<nr>r ignore vl and vtype */
    assign whole_reg_instruction  = whole_reg_load_store || (op_vector && vector_operation_i == VMVR);
    assign mask_instruction       = is_mask_result(vector_operation_i);

    /* Elements done per cycle: one destination register, or one source */
    /* register for the widening multiply, which writes two per cycle    */
    assign elements_per_reg = widening_multiply ? (VLENB >> vsew) : (VLENB >> vsew_effective);

    /* The adder computes a - b as a + ~b + 1. The magnitude compares and */
    /* min/max subtract too, and the lanes take a >= b from the carry-out */
    assign vctrl.is_sub       = (vector_operation_i inside {VSUB, VRSUB, VNMSAC, VNMSUB, VSBC, VMSBC,
                                                            VWSUBU, VWSUB, VWSUBU_W, VWSUB_W,
                                                            VMSLTU, VMSLT, VMSLEU, VMSLE, VMSGTU, VMSGT,
                                                            VMINU, VMIN, VMAXU, VMAX});

    /* vadc, vsbc, and vmadc, vmsbc with vm = 0, take each element's carry */
    /* or borrow from v0                                                    */
    assign vctrl.use_carry_in = !vm && (vector_operation_i inside {VADC, VMADC, VSBC, VMSBC});

    /* v0 is data, not a mask: every body element is written */
    assign vctrl.mask_is_data = (vector_operation_i == VMERGE)
                             || (VCarryEnable && (vector_operation_i inside {VADC, VMADC, VSBC, VMSBC}));

    logic vm_effective;
    assign vm_effective = vm || vctrl.mask_is_data;

    /* The sources are extended to the destination SEW: by 2 for the     */
    /* widening add and subtract; for vzext and vsext, vs1 bit 1 is set  */
    /* for the extension by 2 (00110, 00111) and clear for the extension */
    /* by 4 (00100, 00101)                                               */
    vext_sel_e ext_sel;
    always_comb begin
        if (integer_extension) begin
            if (rs1[1])
                ext_sel = EXT_VF2;
            else
                ext_sel = EXT_VF4;
        end
        else if ((widening_instruction && !widening_multiply) || widening_reduction)
            ext_sel = EXT_VF2;
        else
            ext_sel = EXT_NONE;
    end

    assign vctrl.ext_sel    = ext_sel;
    assign vctrl.ext_signed = (vector_operation_i inside {VSEXT, VWADD, VWSUB, VWADD_W, VWSUB_W, VWREDSUM});
    assign vctrl.src2_wide  = (vector_operation_i inside {VWADDU_W, VWADD_W, VWSUBU_W, VWSUB_W});

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            accumulate_instruction_r <= 1'b0;
            mask_instruction_nr      <= 1'b0;
            multiply_instruction_r   <= 1'b0;
            reduction_instruction_r  <= 1'b0;
            widening_multiply_r      <= 1'b0;
        end
        else if (!should_stall) begin
            if (next_state == V_EXEC) begin
                accumulate_instruction_r <= accumulate_instruction;
                mask_instruction_nr      <= mask_instruction;
                multiply_instruction_r   <= multiply_instruction;
                reduction_instruction_r  <= reduction_instruction;
                widening_multiply_r      <= widening_multiply;
            end
            else begin
                accumulate_instruction_r <= 1'b0;
                mask_instruction_nr      <= 1'b0;
                multiply_instruction_r   <= 1'b0;
                reduction_instruction_r  <= 1'b0;
                widening_multiply_r      <= 1'b0;
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// CSRs
//////////////////////////////////////////////////////////////////////////////

    vectorCSRs #(
        .VLEN   (VLEN),
        .VLENB  (VLENB)
    ) vectorCSRs1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .is_vector_op_i         (enable_i),
        .vector_operation_i     (vector_operation_i),
        .op1_scalar_i           (op1_scalar_i),
        .op2_scalar_i           (op2_scalar_i),
        .zimm                   (zimm),
        .rs1                    (rs1),
        .rd                     (rd),
        .vtype_o                (vtype_o),
        .vlen_o                 (vlen_o),
        .vill_o                 (vill_o),
        .vsew                   (vsew),
        .vlmul                  (vlmul),
        .vl                     (vl),
        .vl_next                (vl_next)
    );

//////////////////////////////////////////////////////////////////////////////
// Illegal configurations: checks that depend on vtype (the encoding-only
// checks are in the decoder). Does not depend on enable_i, which execute
// gates with this output.
//////////////////////////////////////////////////////////////////////////////

    /* Registers in a group of LMUL; a fractional LMUL uses one register */
    logic [3:0] lmul_regs;
    logic       lmul_ge1;
    always_comb begin
        unique case (vlmul)
            LMUL_2:  lmul_regs = 4'd2;
            LMUL_4:  lmul_regs = 4'd4;
            LMUL_8:  lmul_regs = 4'd8;
            default: lmul_regs = 4'd1;
        endcase
    end
    assign lmul_ge1 = (vlmul inside {LMUL_1, LMUL_2, LMUL_4, LMUL_8});

    /* Group sizes are powers of two, so alignment is a mask of the low bits */
    function automatic logic misaligned(logic [4:0] reg_num, logic [4:0] group_regs);
        return (reg_num & (group_regs - 5'd1)) != '0;
    endfunction

    function automatic logic groups_overlap(logic [4:0] a, logic [4:0] a_regs, logic [4:0] b, logic [4:0] b_regs);
        return ({1'b0, a} < {1'b0, b} + {1'b0, b_regs}) && ({1'b0, b} < {1'b0, a} + {1'b0, a_regs});
    endfunction

    /* Widening: EEW = 2*SEW and EMUL = 2*LMUL must be legal (SEW <= 16, LMUL <= 4). */
    logic [4:0] vd_regs;
    assign vd_regs = widening_instruction ? (lmul_ge1 ? {lmul_regs, 1'b0} : 5'd1) : {1'b0, lmul_regs};

    /* The destination may overlap a source of a narrower EEW (widening,  */
    /* extension) only in its highest-numbered part, and only when the    */
    /* source EMUL is at least 1                                          */
    function automatic logic widening_overlap(logic [4:0] dst, logic [4:0] dst_regs, logic [4:0] src, logic [4:0] src_regs, logic src_emul_ge1);
        return groups_overlap(dst, dst_regs, src, src_regs)
            && !(src_emul_ge1 && ({1'b0, src} + {1'b0, src_regs} == {1'b0, dst} + {1'b0, dst_regs}));
    endfunction

    /* vzext and vsext read vs2 with EEW = SEW/f and EMUL = LMUL/f: a group of */
    /* LMUL/f registers, or one register when EMUL < 1. In vwadd.w* and        */
    /* vwsub.w* vs2 has the destination EEW and EMUL                           */
    logic [4:0] vs2_regs;
    logic       vs2_emul_ge1;
    always_comb begin
        vs2_regs     = {1'b0, lmul_regs};
        vs2_emul_ge1 = lmul_ge1;
        if (integer_extension) begin
            unique case (ext_sel)
                EXT_VF2: begin
                    vs2_emul_ge1 = (vlmul inside {LMUL_2, LMUL_4, LMUL_8});
                    if (vs2_emul_ge1)
                        vs2_regs = {2'b0, lmul_regs[3:1]};
                    else
                        vs2_regs = 5'd1;
                end
                EXT_VF4: begin
                    vs2_emul_ge1 = (vlmul inside {LMUL_4, LMUL_8});
                    if (vs2_emul_ge1)
                        vs2_regs = {3'b0, lmul_regs[3:2]};
                    else
                        vs2_regs = 5'd1;
                end
                default: ;
            endcase
        end
        else if (vctrl.src2_wide) begin
            vs2_regs = vd_regs;
        end
    end

    /* Compares write one mask register, which may only overlap the lowest-numbered */
    /* register of a source group                                                   */
    function automatic logic mask_dest_overlap(logic [4:0] dst, logic [4:0] src, logic [4:0] src_regs);
        return (dst > src) && ({1'b0, dst} < {1'b0, src} + {1'b0, src_regs});
    endfunction

    logic arith_checked;
    logic vs1_is_vector;
    logic check_vd, check_vs2, check_vs1;
    logic arith_illegal;

    assign arith_checked = !(vector_operation_i inside {VNOP, VSETVL, VSETVLI, VSETIVLI, VMVR, VMVXS, VMVSX, VLD, VST});
    assign vs1_is_vector = (opCat inside {OPIVV, OPMVV});
    assign check_vd      = !(mask_instruction || reduction_instruction);
    assign check_vs2     = (vector_operation_i != VMV);
    /* In vzext and vsext the vs1 field selects the extension */
    assign check_vs1     = vs1_is_vector && !reduction_instruction && !integer_extension;

    always_comb begin
        arith_illegal = 1'b0;
        if (check_vd  && misaligned(rd,  vd_regs))           arith_illegal = 1'b1;
        if (check_vs2 && misaligned(rs2, vs2_regs))          arith_illegal = 1'b1;
        if (check_vs1 && misaligned(rs1, {1'b0, lmul_regs})) arith_illegal = 1'b1;

        if (widening_instruction) begin
            if (vsew != EW8 && vsew != EW16)                 arith_illegal = 1'b1;
            if (vlmul == LMUL_8)                             arith_illegal = 1'b1;
            /* vs2 of vwadd.w* and vwsub.w* has the destination EEW: it may overlap vd */
            if (!vctrl.src2_wide && widening_overlap(rd, vd_regs, rs2, {1'b0, lmul_regs}, lmul_ge1))
                                                             arith_illegal = 1'b1;
            if (vs1_is_vector && widening_overlap(rd, vd_regs, rs1, {1'b0, lmul_regs}, lmul_ge1))
                                                             arith_illegal = 1'b1;
        end

        /* The source EEW = SEW/f must be at least 8 */
        /* The widening sum reductions take any LMUL: vd is one element */
        if (widening_reduction && vsew == EW32)              arith_illegal = 1'b1;

        if (integer_extension) begin
            if (ext_sel == EXT_VF2 && vsew == EW8)           arith_illegal = 1'b1;
            if (ext_sel == EXT_VF4 && vsew != EW32)          arith_illegal = 1'b1;
            if (widening_overlap(rd, vd_regs, rs2, vs2_regs, vs2_emul_ge1))
                                                             arith_illegal = 1'b1;
        end

        if (mask_instruction) begin
            if (mask_dest_overlap(rd, rs2, {1'b0, lmul_regs}))                  arith_illegal = 1'b1;
            if (vs1_is_vector && mask_dest_overlap(rd, rs1, {1'b0, lmul_regs})) arith_illegal = 1'b1;
        end

        /* vslide1up cannot write over its source */
        if (vector_operation_i == VSLIDE1UP && groups_overlap(rd, {1'b0, lmul_regs}, rs2, {1'b0, lmul_regs}))
                                                             arith_illegal = 1'b1;
    end

    /* Unit-stride and strided loads/stores: data group aligned to EMUL, checked */
    /* only for EEW = SEW (EMUL = LMUL). Indexed: data (EEW = SEW) aligned to     */
    /* LMUL, offsets checked only for an index EEW = SEW. The other EEW != SEW    */
    /* cases and the destination/index overlap rules are not implemented yet.     */
    logic mem_illegal;
    logic mem_eew_is_sew;
    logic mem_checked;
    logic mem_indexed;
    always_comb begin
        unique case (instruction_i[14:12])
            3'b000:  mem_eew_is_sew = (vsew == EW8);
            3'b101:  mem_eew_is_sew = (vsew == EW16);
            default: mem_eew_is_sew = (vsew == EW32);
        endcase
    end
    /* Whole register and mask accesses (unit-stride, lumop 01000 and 01011) */
    /* are not checked here. Decoded from the instruction, not enable_i.     */
    assign mem_indexed = instruction_i[26];
    assign mem_checked = (vector_operation_i inside {VLD, VST})
                      && !(instruction_i[27:26] == 2'b00 && instruction_i[24:20] inside {5'b01000, 5'b01011});
    assign mem_illegal = mem_checked && (
                            ((mem_indexed || mem_eew_is_sew) && misaligned(rd,  {1'b0, lmul_regs}))
                        ||  ( mem_indexed && mem_eew_is_sew  && misaligned(rs2, {1'b0, lmul_regs}))
                        );

    assign illegal_cfg_o = (arith_checked && arith_illegal) || mem_illegal;

//////////////////////////////////////////////////////////////////////////////
// MASKs
//////////////////////////////////////////////////////////////////////////////

    logic [7:0][ VLENB   -1:0] mask_sew8;
    logic [7:0][(VLENB/2)-1:0] mask_sew16;
    logic [7:0][(VLENB/4)-1:0] mask_sew32;

    /* A compare can write v0 while v0 is its mask, and with LMUL > 1 it    */
    /* writes the destination once per source register. The mask then comes */
    /* from the copy of the old destination taken before the first write.   */
    logic [VLEN-1:0] mask_source;
    logic            old_vd_valid;

    assign mask_source = (mask_instruction && rd == '0 && old_vd_valid) ? third_operand : v0_mask;

    always_comb begin
        for (int i = 0; i < 8; i++) begin
            mask_sew8 [i] = mask_source[( VLENB   *(i+1))-1-:VLENB];
            mask_sew16[i] = mask_source[((VLENB/2)*(i+1))-1-:VLENB/2];
            mask_sew32[i] = mask_source[((VLENB/4)*(i+1))-1-:VLENB/4];
        end
    end

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    assign hazard_detected = (state == V_IDLE && |write_enable == 1'b1 && (vs1_addr == vd_addr_r || vs2_addr == vd_addr_r));

    assign hold_o = enable_i && (next_state == V_EXEC || hazard_detected == 1'b1);

    /* The instruction stays in execute while the bus is stalled: hold its last
     * cycle so it is not restarted; earlier cycles keep computing. Loads and
     * stores hold every cycle: they wait for the bus, and this FSM sequences
     * the LSU (register count, store data). */
    assign should_stall = stall && (op_vload || op_vstore || (state == V_EXEC && next_state == V_IDLE));

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state <= V_IDLE;
        end
        else if (!should_stall && !hold) begin
            state <= next_state;
        end
    end

    always_comb begin
        unique case (state)
            V_IDLE:
                if ((
                    (op_vector && !(vector_operation_i inside {VNOP, VSETVL, VSETVLI, VSETIVLI}))
                ||  (op_vload || op_vstore)
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
                /* vwredsum with LMUL = 8 reads each source register twice */
                ||  (widening_reduction && vlmul == LMUL_8 && cycle_count_vd < 16)
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
        if (widening_instruction || widening_reduction) begin
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
        else if (mask_load_store) begin
            vlmul_effective = LMUL_1;
        end
        else if (widening_instruction || widening_reduction) begin
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
        else if (!should_stall) begin
            if (next_state == V_IDLE)
                cycle_count <= 0;
            else if (next_state == V_EXEC && !hold)
                cycle_count <= cycle_count + 1;
        end

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count_vd <= 0;
        else if (!should_stall) begin
            if (next_state == V_IDLE)
                cycle_count_vd <= 0;
            else if (next_state == V_EXEC && (!hold || hold_widening))
                cycle_count_vd <= cycle_count_vd + 1;
        end

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            cycle_count_r <= 0;
        else if (!should_stall) begin
            if (widening_multiply && (!hold || hold_widening))
                cycle_count_r <= cycle_count_vd;
            else if (!hold)
                cycle_count_r <= cycle_count;
        end

//////////////////////////////////////////////////////////////////////////////
// Vector Length Control
//////////////////////////////////////////////////////////////////////////////

    assign vl_next_reg = ($signed(vl_curr_reg - elements_per_reg) >= 0)
                        ? vl_curr_reg - elements_per_reg
                        : 0;

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            vl_curr_reg <= '0;
        else if (!should_stall) begin
            if (next_state == V_IDLE)
                vl_curr_reg <= 0;
            else if (whole_reg_instruction)
                vl_curr_reg <= '1;
            else if (mask_load_store)
                vl_curr_reg <= (vl >> 3) + ((vl[2:0] & 3'h7) != 3'h0 ? 1 : 0);
            else if (state == V_IDLE && next_state == V_EXEC)
                vl_curr_reg <= vl;
            else if (next_state == V_EXEC && !hold)
                vl_curr_reg <= vl_next_reg;
        end

    always_ff @(posedge clk or negedge reset_n)
        if (!reset_n)
            total_elements_processed <= 0;
        else if (!should_stall) begin
            if (next_state == V_IDLE)
                total_elements_processed <= 0;
            else if (!hold)
                total_elements_processed <= total_elements_processed + elements_per_reg;
        end

    assign vector_process_done = (total_elements_processed >= vl && !whole_reg_instruction && op_vector);

//////////////////////////////////////////////////////////////////////////////
// Register Bank
//////////////////////////////////////////////////////////////////////////////

    // ADDRESS CALCULATION
    /* Operations that extend their sources iterate over the destination */
    /* registers: each source register is read for f of them, one slice  */
    /* of it each time                                                   */
    logic [3:0] src_reg_offset;
    logic [1:0] ext_slice;
    always_comb begin
        unique case (ext_sel)
            EXT_VF2: begin
                src_reg_offset = {1'b0, cycle_count[3:1]};
                ext_slice      = {1'b0, cycle_count[0]};
            end
            EXT_VF4: begin
                src_reg_offset = {2'b0, cycle_count[3:2]};
                ext_slice      = cycle_count[1:0];
            end
            default: begin
                src_reg_offset = cycle_count;
                ext_slice      = '0;
            end
        endcase
    end

    /* The 2*SEW vs2 of vwadd.w* and vwsub.w* is read with the destination */
    logic [3:0] src2_reg_offset;
    always_comb begin
        if (vctrl.src2_wide)
            src2_reg_offset = cycle_count;
        else
            src2_reg_offset = src_reg_offset;
    end

    assign rs1_addr = src_reg_offset + rs1;
    assign rs2_addr = src2_reg_offset + rs2;
    assign rd_addr  = cycle_count + rd;

    always_comb begin
        // VS1 Address
        if (op_vstore) begin
            vs1_addr = rd_addr;
        end
        else if (vector_operation_i inside {VSLIDE1UP, VSLIDE1DOWN}) begin
            vs1_addr = rs2_addr + 1;
        end
        else begin
            vs1_addr = rs1_addr;
        end

        // VS2 Address
        if (accumulate_instruction) begin
            if (!hold) begin
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
        /* Compares read the old destination on their first hold cycle */
        else if (mask_instruction && hold) begin
            vs2_addr = rd;
        end
        /* The widening multiply-add reads the old vd[2c] while it multiplies, */
        /* and vd[2c+1] in the hold_widening cycle, when it adds to vd[2c]     */
        else if (vector_operation_i inside {VWMACCU, VWMACC, VWMACCSU, VWMACCUS} && hold) begin
            vs2_addr = vd_addr + hold_widening;
        end
        else begin
            vs2_addr = rs2_addr;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            vd_addr   <= '0;
            vd_addr_r <= '0;
        end
        else if (!should_stall && (!hold || hold_widening)) begin
            vd_addr   <= (reduction_instruction || mask_instruction)
                        ? rd
                        : rd + cycle_count_vd;
            vd_addr_r <= vd_addr;
        end
    end

    // WRITE ENABLE GENERATION
    /* Elements below vl in the destination register being written. In   */
    /* the hold_widening scheme, vl_curr_reg counts from the first       */
    /* element of the source register, so the second destination         */
    /* register (odd cycle_count_r) starts half a source register later  */
    logic [$bits(VLEN)-1:0] vl_write;
    always_comb begin
        if (!(widening_multiply && cycle_count_r[0]))
            vl_write = vl_curr_reg;
        else if (vl_curr_reg > (elements_per_reg >> 1))
            vl_write = vl_curr_reg - (elements_per_reg >> 1);
        else
            vl_write = '0;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            write_enable <= '0;
        end
        else if (!should_stall && (state == V_EXEC) && (!hold || hold_widening) && !op_vstore && vector_operation_i != VMVXS) begin
            if (reduction_instruction || vector_operation_i == VMVSX) begin
                /* With vl = 0 they do not write the destination */
                if (vl == '0)
                    write_enable <= '0;
                else begin
                    unique case (vsew_effective)
                        EW8:     write_enable <= {'0, 1'b1};
                        EW16:    write_enable <= {'0, 2'b11};
                        default: write_enable <= {'0, 4'b1111};
                    endcase
                end
            end
            else if (whole_reg_instruction || mask_instruction) begin
                write_enable <= '1;
            end
            else begin
                unique case (vsew_effective)
                    EW8:
                        for (int i = 0; i < VLENB; i++)
                            if ((vm_effective || mask_sew8[cycle_count_r][i]) && (i < vl_write))
                                write_enable[i] <= 1'b1;
                            else
                                write_enable[i] <= 1'b0;

                    EW16:
                        for (int i = 0; i < VLENB/2; i++)
                            if ((vm_effective || mask_sew16[cycle_count_r][i]) && (i < vl_write))
                                write_enable[(i*2)+:2] <= 2'b11;
                            else
                                write_enable[(i*2)+:2] <= 2'b00;

                    default:
                        for (int i = 0; i < VLENB/4; i++)
                            if ((vm_effective || mask_sew32[cycle_count_r][i]) && (i < vl_write))
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

    /* The widening add and subtract truncate the scalar to SEW and extend */
    /* it to 2*SEW, like their vector sources                              */
    always_comb begin
        if (ext_sel == EXT_NONE) begin
            unique case (vsew)
                EW8:     scalar_replicated = {(VLENB)  {op1_scalar_i[ 7:0]}};
                EW16:    scalar_replicated = {(VLENB/2){op1_scalar_i[15:0]}};
                default: scalar_replicated = {(VLENB/4){op1_scalar_i[31:0]}};
            endcase
        end
        else begin
            unique case (vsew)
                EW8:     scalar_replicated = {(VLENB/2){{ 8{vctrl.ext_signed && op1_scalar_i[ 7]}}, op1_scalar_i[ 7:0]}};
                default: scalar_replicated = {(VLENB/4){{16{vctrl.ext_signed && op1_scalar_i[15]}}, op1_scalar_i[15:0]}};
            endcase
        end
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

    /* The sources extended to the destination SEW (vzext, vsext, widening */
    /* add and subtract); unchanged for the other operations               */
    logic [VLEN-1:0] vs2_extended, vs1_extended;
    vext_sel_e       vs2_ext_sel, vs1_ext_sel;

    /* vs2 of vwadd.w* and vwsub.w* is not extended, and neither is vs1[0] */
    /* of vwredsum, which already has EEW = 2*SEW                          */
    assign vs2_ext_sel = vctrl.src2_wide   ? EXT_NONE : vctrl.ext_sel;
    assign vs1_ext_sel = widening_reduction ? EXT_NONE : vctrl.ext_sel;

    vectorExtend #(
        .VLEN (VLEN)
    ) vectorExtendVs2 (
        .data_i       (vs2_data),
        .ext_sel_i    (vs2_ext_sel),
        .ext_signed_i (vctrl.ext_signed),
        .slice_i      (ext_slice),
        .vsew_i       (vsew_effective),
        .data_o       (vs2_extended)
    );

    vectorExtend #(
        .VLEN (VLEN)
    ) vectorExtendVs1 (
        .data_i       (vs1_data),
        .ext_sel_i    (vs1_ext_sel),
        .ext_signed_i (vctrl.ext_signed),
        .slice_i      (ext_slice),
        .vsew_i       (vsew_effective),
        .data_o       (vs1_extended)
    );

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            first_operand <= '0;
        end
        else if (!should_stall && !hold) begin
            first_operand  <= vs2_extended;
        end
    end

    /* For compares, third_operand keeps the old destination: it is taken */
    /* on the first hold cycle, before the instruction writes vd.          */
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            third_operand <= '0;
        end
        else if (!should_stall && hold && !(mask_instruction && old_vd_valid)) begin
            third_operand <= vs2_data;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            old_vd_valid <= 1'b0;
        end
        else if (!should_stall) begin
            if (next_state == V_IDLE)
                old_vd_valid <= 1'b0;
            else if (mask_instruction && hold)
                old_vd_valid <= 1'b1;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            second_operand <= '0;
        end
        else if (!should_stall && !hold) begin
            if (op_vstore) begin
                second_operand <= vs1_data;
            end
            else if (op_vector && vector_operation_i inside {VSLIDE1UP, VSLIDE1DOWN}) begin
                second_operand <= vs1_data;
            end
            else begin
                unique case (opCat)
                    OPIVX, OPFVF, OPMVX: second_operand <= scalar_replicated;
                    OPIVI:               second_operand <= imm_replicated;
                    default:             second_operand <= vs1_extended;
                endcase
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// LOAD AND STORE UNIT
//////////////////////////////////////////////////////////////////////////////

    vectorLSU #(
        .VLEN      (VLEN     ),
        .VLENB     (VLENB    ),
        .BUS_WIDTH (BUS_WIDTH)
    ) vectorLSU1 (
        .clk                    (clk),
        .reset_n                (reset_n),
        .stall                  (stall),
        .instruction_i          (instruction_i),
        .base_address_i         (op1_scalar_i),
        .stride_i               (op2_scalar_i),
        .indexed_offsets_i      (first_operand),
        .write_data_i           (second_operand),
        .current_state          (state),
        .hazard_detected_i      (hazard_detected),
        .is_vload_i             (op_vload),
        .is_vstore_i            (op_vstore),
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

    /* The operations that extend their sources compute at the destination SEW */
    vew_e vsew_alu;
    assign vsew_alu = (ext_sel == EXT_NONE) ? vsew : vsew_effective;

    logic [$bits(VLEN )-1:0] vl_reductions;
    assign vl_reductions = (vl_curr_reg > elements_per_reg)
                            ? elements_per_reg
                            : vl_curr_reg;

    vectorALU #(
        .VLEN                  (VLEN                 ),
        .LLEN                  (LLEN                 ),
        .VLENB                 (VLENB                ),
        .VLogicEnable          (VLogicEnable         ),
        .VMinMaxEnable         (VMinMaxEnable        ),
        .VRedLogicEnable       (VRedLogicEnable      ),
        .VRedMinMaxEnable      (VRedMinMaxEnable     ),
        .VRedSumEnable         (VRedSumEnable        ),
        .VMergeEnable          (VMergeEnable         ),
        .VCarryEnable          (VCarryEnable         ),
        .VDivEnable            (VDivEnable           ),
        .VMultiCycleReductions (VMultiCycleReductions)
    ) vectorALU1 (
        .clk                   (clk),
        .reset_n               (reset_n),
        .stall                 (should_stall),
        .first_operand         (first_operand),
        .second_operand        (second_operand),
        .third_operand         (third_operand),
        .scalar_operand        (op1_scalar_i),
        .vector_operation_i    (vector_operation_i),
        .vctrl_i               (vctrl),
        .cycle_count           (cycle_count),
        .cycle_count_r         (cycle_count_r),
        .vlmul                 (vlmul),
        .vl                    (vl_reductions),
        .vl_next               (vl_next_reg),
        .vm                    (vm),
        .mask_sew8             (mask_sew8),
        .mask_sew16            (mask_sew16),
        .mask_sew32            (mask_sew32),
        .accumulate_instruction(accumulate_instruction_r),
        .mask_instruction      (mask_instruction_nr),
        .multiply_instruction  (multiply_instruction_r),
        .reduction_instruction (reduction_instruction_r),
        .widening_instruction  (widening_multiply_r),
        .current_state         (state),
        .vsew                  (vsew_alu),
        .hold_o                (hold_alu),
        .hold_widening_o       (hold_widening),
        .result_mask_o         (result_alu_mask),
        .result_o              (result_alu)
    );

//////////////////////////////////////////////////////////////////////////////
// Result Demux
//////////////////////////////////////////////////////////////////////////////

    logic   op_vload_r;
    logic   mask_instruction_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            op_vload_r         <= 1'b0;
            mask_instruction_r <= '0;
        end
        else if (!should_stall) begin
            op_vload_r         <= op_vload;
            mask_instruction_r <= mask_instruction;
        end
    end

    /* A compare writes only its active body elements: masked-off elements */
    /* and the tail keep the old destination (undisturbed is always legal). */
    /* The write happens one cycle after the compare computed it, when the  */
    /* next instruction may already be in execute, so vm and the mask      */
    /* source are registered like mask_instruction_r.                       */
    logic            compare_vm_r;
    logic            compare_v0_copy_r;
    logic [VLEN-1:0] compare_body;
    logic [VLEN-1:0] compare_active;
    logic [VLEN-1:0] result_compare;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            compare_vm_r      <= 1'b0;
            compare_v0_copy_r <= 1'b0;
        end
        else if (!should_stall) begin
            compare_vm_r      <= vm_effective;
            compare_v0_copy_r <= mask_instruction && rd == '0 && old_vd_valid;
        end
    end

    /* Elements below vl (VLEN + 1 bits so vl = VLEN fits; truncated) */
    assign compare_body   = ~({(VLEN+1){1'b1}} << vl);
    assign compare_active = compare_body & (compare_vm_r ? '1 : (compare_v0_copy_r ? third_operand : v0_mask));
    assign result_compare = (third_operand & ~compare_active) | (result_alu_mask & compare_active);

    always_comb begin
        if (op_vload_r)
            result = result_lsu;
        else if (mask_instruction_r)
            result = result_compare;
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
            /* SEW < XLEN is sign-extended */
            unique case (vsew_effective)
                EW8:     res_scalar_o = {{24{first_operand[ 7]}}, first_operand[ 7:0]};
                EW16:    res_scalar_o = {{16{first_operand[15]}}, first_operand[15:0]};
                default: res_scalar_o =                           first_operand[31:0];
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
