/*!\file execute.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
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
 * Execute Unit is the third stage of the RS5 processor core.
 *
 * \detailed
 * Execute Unit is the third stage of the RS5 processor core. It implements
 * an Arithmetic Logic Unit (ALU) responsible for calculations, it also have
 * a Branch Unit that makes the decision of branching based on instruction
 * operation and operands. Also implements the Memory Load and Store mechanism.
 * Lastly it implements the CSR access logic.
 */

`include "RS5_pkg.sv"

module execute
    import RS5_pkg::*;
#(
    parameter environment_e Environment  = ASIC,
    parameter mul_e         MULEXT       = MUL_M,
    parameter atomic_e      AMOEXT       = AMO_A,
    parameter bit           COMPRESSED   = 1'b1,
    parameter bit           ZKNEEnable   = 1'b0,
    parameter bit           ZBKBEnable   = 1'b0,
    parameter bit           ZKNHEnable   = 1'b0,
    parameter bit           XKYBEREnable = 1'b0,
    parameter bit           ZICONDEnable = 1'b0,
    parameter bit           VEnable      = 1'b0,
    parameter int           VLEN         = 64,
    parameter int           LLEN         = 32,
    parameter int           BUS_WIDTH    = 32,
    parameter bit           BRANCHPRED   = 1'b1
)
(
    input   logic                   clk,
    input   logic                   reset_n,
    input   logic                   stall,

    /* Registered inputs from decode */
    input   logic                   valid_i,
    input   logic  [4:0]            rd_i,
    input   logic  [4:0]            rs1_i,
    input   logic [31:0]            pc_i,
    input   logic [31:0]            rs1_data_i,
    input   logic [31:0]            rs2_data_i,
    input   logic [31:0]            second_operand_i,
    input   logic [31:0]            jump_imm_target_i,
    /* Not used without branch prediction */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic                   bp_ack_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* Some bits of the control signals are not used depending on the ISEs */
    /* verilator lint_off UNUSEDSIGNAL */
    input   exec_ctrl_t             ctrl_i,
    input   logic [11:0]            csr_address_i,
    input   logic [31:0]            instruction_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* Combinational inputs from mem_access */
    input   logic                   exc_load_access_fault_i,
    /* Not used without zalrsc */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]            reservation_data_i,
    /* verilator lint_on UNUSEDSIGNAL */
    
    /* CSR interface */
    input   privilegeLevel_e        privilege_i,
    input   logic                   interrupt_pending_i,
    output  logic                   interrupt_ack_o,
    output  logic                   machine_return_o,
    output  logic                   raise_exception_o,
    output  logic                   csr_read_enable_o,
    output  logic                   csr_write_enable_o,
    output  csrOperation_e          csr_operation_o,
    output  exceptionCode_e         exception_code_o,
    input   logic [31:0]            csr_data_read_i,
    output  logic [31:0]            csr_data_o,
    input   logic [31:0]            mtvec_i,
    input   logic [31:0]            mepc_i,
    output  logic [31:0]            vtype_o,
    output  logic [31:0]            vlen_o,
    output  logic [31:0]            pc_irq_o,
    output  logic [31:0]            pc_exc_o,

    /* Memory interface */
    output  logic [31:0]            mem_address_exec_o,
    output  logic [31:0]            mem_address_o,
    output  logic                   mem_enable_o,
    output  logic [BUS_WIDTH/8-1:0] mem_write_enable_o,
    output  logic [BUS_WIDTH-1:0]   mem_write_data_o,
    /* Not used if VEnable or AMO is 0 */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [BUS_WIDTH-1:0]   mem_read_data_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* Combinational outputs to previous stages */
    output  logic                   hold_o,
    output  logic                   write_enable_fwd_o,
    output  logic                   jump_rollback_o,
    output  logic                   ctx_switch_o,
    output  logic                   jump_o,
    output  logic                   should_jump_o,
    output  logic   [31:0]          ctx_switch_target_o,
    output  logic   [31:0]          jump_target_o,
    output  logic   [31:0]          result_fwd_o,

    /* Registered outputs to mem_access */
    output  wb_ctrl_t               ctrl_o,
    output  logic   [ 4:0]          rd_o,
    output  logic   [31:0]          result_o
);

    logic [31:0]    result;
    logic           write_enable;
    logic           exc_ilegal_csr_inst;

//////////////////////////////////////////////////////////////////////////////
// ALU
//////////////////////////////////////////////////////////////////////////////

    logic [31:0]    sum_result;
    logic [31:0]    and_result;
    logic [31:0]    or_result;
    logic [31:0]    xor_result;
    logic [31:0]    sll_result;
    logic [31:0]    srl_result;
    logic [31:0]    sra_result;

    logic           equal;
    logic           less_than;
    logic           less_than_unsigned;
    logic           greater_equal;
    logic           greater_equal_unsigned;

    logic [31:0] sum_opB;

    // Can be assigned by atomic instructions or rs1_data_i
    logic [31:0] first_operand;
    logic [31:0] equal_opA;
    logic [31:0] equal_opB;

    /* Unmuxed operators */
    assign less_than_unsigned     = rs1_data_i <  second_operand_i;
    assign greater_equal_unsigned = rs1_data_i >= second_operand_i;
    assign less_than              = $signed(rs1_data_i) <  $signed(second_operand_i);
    assign greater_equal          = $signed(rs1_data_i) >= $signed(second_operand_i);
    assign sll_result             = rs1_data_i << second_operand_i[4:0];
    assign srl_result             = rs1_data_i >> second_operand_i[4:0];
    assign sra_result             = $signed(rs1_data_i) >>> second_operand_i[4:0];

    logic [31:0] amo_operand;

    logic [31:0] xkyber_alu_operand_a, xkyber_alu_operand_b;

    /* Both arms fold to constant 0 when AMO and XKYBER are disabled */
    /* verilator lint_off CASEOVERLAP */
    always_comb begin
        unique case (1'b1)
            (AMOEXT inside {AMO_A, AMO_ZAAMO} && ctrl_i.is_amo):
                first_operand = amo_operand;
            (XKYBEREnable && ctrl_i.is_kyber):
                first_operand = xkyber_alu_operand_a;
            default:
                first_operand = rs1_data_i;
        endcase
    end
    /* verilator lint_on CASEOVERLAP */

    logic kyber_uses_opB;
    assign kyber_uses_opB = ctrl_i.kyber_op inside {KYBSUB, KYBMUL, KYBCOMPRESS};

    always_comb begin
        unique case (1'b1)
            ctrl_i.is_sub:
                sum_opB = -second_operand_i;
            (XKYBEREnable && kyber_uses_opB):
                sum_opB = xkyber_alu_operand_b;
            default:
                sum_opB = second_operand_i;
        endcase
    end

    /* Muxed operators */
    assign sum_result = first_operand + sum_opB;
    assign and_result = first_operand & second_operand_i;
    assign or_result  = first_operand | second_operand_i;
    assign xor_result = first_operand ^ second_operand_i;
    assign equal      = equal_opA == equal_opB;

    /* We can't obtain the PC from fetch stage because it can be modified due */
    /* to load/store stalls when the current instruction is JAL[R]            */
    logic [31:0] pc_next;
    assign pc_next = pc_i + (ctrl_i.compressed ? 32'h00000002 : 32'h00000004);

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] mem_address_vector;
    /* verilator lint_on UNUSEDSIGNAL */
    logic [31:0] mem_address;

    logic        mem_read_enable_vector;

    logic  [3:0]             mem_write_enable;
    logic  [BUS_WIDTH/8-1:0] mem_write_enable_vector;

    logic [31:0]          mem_write_data;
    logic [BUS_WIDTH-1:0] mem_write_data_vector;

    logic        atomic_mem_read_enable;
    logic        atomic_mem_write_enable;

    always_comb begin
        unique case (1'b1)
            ctrl_i.is_amo_w:  mem_address = rs1_data_i;
            ctrl_i.is_vector: mem_address = mem_address_vector;
            default:          mem_address = sum_result;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mem_address_o <= '0;
        else if (!stall)
            mem_address_o <= mem_address;
    end

    logic misaligned_sh;
    assign misaligned_sh = mem_address[0] && ctrl_i.is_half && ctrl_i.is_store;

    logic misaligned_sw;
    assign misaligned_sw = (mem_address[1:0] != '0) && (ctrl_i.is_amo_w || (ctrl_i.is_store && !ctrl_i.is_half && !ctrl_i.is_byte));

    logic misaligned_lh;
    assign misaligned_lh = mem_address[0] && ctrl_i.is_half && ctrl_i.is_load;

    logic misaligned_lw;
    assign misaligned_lw = (mem_address[1:0] != '0) && ctrl_i.is_load && !ctrl_i.is_half && !ctrl_i.is_byte;

    logic laddr_misaligned;
    assign laddr_misaligned = (misaligned_lh || misaligned_lw);

    logic saddr_misaligned;
    assign saddr_misaligned = (misaligned_sh || misaligned_sw);

    logic mem_read_enable_vector_inst;
    assign mem_read_enable_vector_inst = mem_read_enable_vector && ctrl_i.is_vector;

    logic mem_read_enable;
    assign mem_read_enable = ctrl_i.is_load || ctrl_i.is_lr;

    logic pmem_read_enable;
    assign pmem_read_enable = (mem_read_enable || atomic_mem_read_enable || mem_read_enable_vector_inst);

    always_comb begin
        unique case (1'b1)
            ctrl_i.is_byte: mem_write_data = {4{rs2_data_i[7:0]}};
            ctrl_i.is_half: mem_write_data = {2{rs2_data_i[15:0]}};
            default:        mem_write_data = rs2_data_i;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            mem_write_data_o <= '0;
        end
        else if (!stall) begin
            unique case (1'b1)
                ctrl_i.is_vector: mem_write_data_o <= mem_write_data_vector;
                ctrl_i.is_amo:    mem_write_data_o <= {{(BUS_WIDTH-32){1'b0}}, amo_operand};
                default:          mem_write_data_o <= {{(BUS_WIDTH-32){1'b0}}, mem_write_data};
            endcase
        end
    end

    always_comb begin
        mem_write_enable = '0;
        if (ctrl_i.is_store) begin
            unique case (1'b1)
                ctrl_i.is_byte: mem_write_enable[sum_result[1:0]]      = 1'b1;
                ctrl_i.is_half: mem_write_enable[sum_result[1:0]+1-:2] = 2'b11;
                default:        mem_write_enable                       = 4'b1111;
            endcase
        end
    end

    logic [BUS_WIDTH/8-1:0] pmem_write_enable;
    assign pmem_write_enable = {{(BUS_WIDTH/8-4){1'b0}}, (mem_write_enable | {4{atomic_mem_write_enable}})}  | mem_write_enable_vector;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mem_write_enable_o <= '0;
        else if (!stall)
            mem_write_enable_o <= pmem_write_enable;
    end

    logic mem_enable;
    assign mem_enable = pmem_read_enable || (pmem_write_enable != '0);


    logic raise_exception;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            mem_enable_o <= '0;
        else if (!stall)
            mem_enable_o <= mem_enable && !raise_exception;
    end

    assign mem_address_exec_o = mem_address;

//////////////////////////////////////////////////////////////////////////////
// CSR access signals
//////////////////////////////////////////////////////////////////////////////

    logic csr_read_enable, csr_write_enable;

    assign csr_read_enable_o  = csr_read_enable  && !exc_ilegal_csr_inst && !stall;
    assign csr_write_enable_o = csr_write_enable && !exc_ilegal_csr_inst && !stall;

    assign csr_read_enable  = ctrl_i.is_csr && (ctrl_i.csr_op == WRITE ? (rd_i  != '0) : 1'b1);
    assign csr_write_enable = ctrl_i.is_csr && (ctrl_i.csr_wr_uses_rs1 ? (rs1_i != '0) : 1'b1);
    assign csr_data_o       = ctrl_i.csr_rd_uses_rs1 ? rs1_data_i : {27'b0, rs1_i};
    assign csr_operation_o  = ctrl_i.csr_op;

    assign exc_ilegal_csr_inst = (
        (csr_write_enable && csr_address_i[11:10] == 2'b11) ||
        ((csr_read_enable || csr_write_enable) && csr_address_i[9:8] > privilege_i)
    );

/////////////////////////////////////////////////////////////////////////////
// Multiplication signals
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] mul_result;
    logic        hold_mul;
    logic        hold_div;

/////////////////////////////////////////////////////////////////////////////
// Xkyber signals
//////////////////////////////////////////////////////////////////////////////

    logic hold_xkyber;
    logic [31:0] xkyber_result;
    logic [15:0] mult_kyber_op_a, mult_kyber_op_b;

    if (XKYBEREnable) begin : gen_xkyber_on

        logic [2:0]  cbd_result_high;
        logic [2:0]  cbd_result_low;

        logic eta_is_3;
        assign eta_is_3 = (ctrl_i.kyber_op == KYBCBD3);

        assign cbd_result_high = eta_is_3 ?
            (3'(first_operand[6]) + 3'(first_operand[7]) + 3'(first_operand[8])) -
            (3'(first_operand[9]) + 3'(first_operand[10]) + 3'(first_operand[11])) :
            (3'(first_operand[4]) + 3'(first_operand[5])) -
            (3'(first_operand[6]) + 3'(first_operand[7]));

        assign cbd_result_low = eta_is_3 ?
            (3'(first_operand[0]) + 3'(first_operand[1]) + 3'(first_operand[2])) -
            (3'(first_operand[3]) + 3'(first_operand[4]) + 3'(first_operand[5])) :
            (3'(first_operand[0]) + 3'(first_operand[1])) -
            (3'(first_operand[2]) + 3'(first_operand[3]));

        logic [3:0] kyber_compress_bits;
        assign kyber_compress_bits = second_operand_i[3:0] & {4{ctrl_i.kyber_op == KYBCOMPRESS}};

        xkyber xkyber1 (
            .clk                   (clk),
            .reset_n               (reset_n),
            .stall                 (stall),
            .alu_adder_i           (sum_result),
            .operator_i            (ctrl_i.kyber_op),
            .first_operand_i       (rs1_data_i),
            .second_operand_i      (rs2_data_i),
            .is_xkyber_i           (ctrl_i.is_kyber),
            .hold_o                (hold_xkyber),
            .alu_operand_a_kyber_o (xkyber_alu_operand_a),
            .alu_operand_b_kyber_o (xkyber_alu_operand_b),
            .result_mul_i          (mul_result),
            .alu_cbd_high_i        (cbd_result_high),
            .alu_cbd_low_i         (cbd_result_low),
            .mult_kyber_op_a       (mult_kyber_op_a),
            .mult_kyber_op_b       (mult_kyber_op_b),
            .kyber_compress_bits_i (kyber_compress_bits),
            .result_o              (xkyber_result)
        );     
    end
    else begin : gen_xkyber_off
        assign hold_xkyber          = 1'b0;
        assign xkyber_result        = '0;
        assign mult_kyber_op_a      = '0;
        assign mult_kyber_op_b      = '0;
        assign xkyber_alu_operand_a = '0;
        assign xkyber_alu_operand_b = '0;
    end

    if ((MULEXT != MUL_OFF) || XKYBEREnable) begin : gen_zmmul_on
        logic [1:0] signed_mode_mul;
        logic       enable_mul;
        logic       mul_low;

        assign signed_mode_mul = ctrl_i.mul_signed_mode;
        assign enable_mul      = ctrl_i.is_mul;
        assign mul_low         = ctrl_i.mul_low;

        logic [31:0] mul_first_operand, mul_second_operand;

        assign mul_first_operand  = (XKYBEREnable && ctrl_i.is_kyber) ? {16'b0, mult_kyber_op_a} : rs1_data_i;
        assign mul_second_operand = (XKYBEREnable && ctrl_i.is_kyber) ? {16'b0, mult_kyber_op_b} : rs2_data_i; 

        mul mul1 (
            .clk              (clk),
            .reset_n          (reset_n),
            .stall            (stall),
            .first_operand_i  (mul_first_operand),
            .second_operand_i (mul_second_operand),
            .signed_mode_i    (signed_mode_mul),
            .enable_i         (enable_mul),
            .mul_low_i        (mul_low),
            .hold_o           (hold_mul),
            .single_cycle_i   (1'b0),
            .result_o         (mul_result)
        );
    end
    else begin : gen_zmmul_off
        assign hold_mul   = 1'b0;
        assign mul_result = '0;
    end    


/////////////////////////////////////////////////////////////////////////////
// Division
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] div_result;
    logic [31:0] rem_result;

    if (MULEXT == MUL_M) begin : gen_div_on
        logic enable_div;
        logic signed_div;

        assign enable_div = ctrl_i.is_div || ctrl_i.is_rem;
        assign signed_div = ctrl_i.div_signed;

        div div1 (
            .clk              (clk),
            .reset_n          (reset_n),
            .first_operand_i  (rs1_data_i),
            .second_operand_i (rs2_data_i),
            .enable_i         (enable_div),
            .signed_i         (signed_div),
            .hold_o           (hold_div),
            .div_result_o     (div_result),
            .rem_result_o     (rem_result)
        );
    end
    else begin : gen_div_off
        assign hold_div         = 1'b0;
        assign div_result       = '0;
        assign rem_result       = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// AES
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] aes_result;

    if (ZKNEEnable) begin: zkne_gen_on
        logic aes_mix;
        logic aes_valid;

        assign aes_mix   = ctrl_i.aes_is_mix;
        assign aes_valid = ctrl_i.is_aes;

        aes_unit #(
            .Environment (Environment),
            .LOGIC_GATING(1'b1)  // Gate sub-module inputs to save toggling
        ) u_aes_unit (
            .rs1_in   (rs1_data_i),           // Source register 1
            .rs2_in   (rs2_data_i),           // Source register 2
            .bs_in    (instruction_i[31:30]), // Byte select immediate
            .mix_in   (aes_mix),              // SubBytes + MixColumn or just SubBytes
            .valid_in (aes_valid),            // Are the inputs valid?
            .rd_out   (aes_result)            // Output destination register value
        );
    end
    else begin : zkne_gen_off
        assign aes_result = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// SHA2
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] sha2_result;

    if (ZKNHEnable) begin: zknh_gen_on
        sha2_unit #(
            .LOGIC_GATING(1'b1)
        ) u_sha2_unit (
            .sha2_en_i(ctrl_i.is_sha2),
            .sha2_op_i(ctrl_i.sha2_op),
            .op_a_i(first_operand),
            .op_b_i(second_operand_i),
            .sha2_result_o(sha2_result)
        );
    end
    else begin : zknh_gen_off
        assign sha2_result = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Vector Extension
//////////////////////////////////////////////////////////////////////////////
    logic [31:0] vector_scalar_result;
    logic        vector_wr_en;
    logic        hold_vector;

    if (VEnable) begin : v_gen_on
        vectorUnit #(
            .Environment (Environment),
            .VLEN        (VLEN       ),
            .LLEN        (LLEN       ),
            .BUS_WIDTH   (BUS_WIDTH  )
        ) vector (
            .clk                    (clk),
            .reset_n                (reset_n),
            .instruction_i          (instruction_i),
            .enable_i               (ctrl_i.is_vector),
            .vector_operation_i     (ctrl_i.vector_op),
            .op1_scalar_i           (rs1_data_i),
            .op2_scalar_i           (rs2_data_i),
            .hold_o                 (hold_vector),
            .vtype_o                (vtype_o),
            .vlen_o                 (vlen_o),
            .mem_address_o          (mem_address_vector),
            .mem_read_enable_o      (mem_read_enable_vector),
            .mem_write_enable_o     (mem_write_enable_vector),
            .mem_write_data_o       (mem_write_data_vector),
            .mem_read_data_i        (mem_read_data_i),
            .res_scalar_o           (vector_scalar_result),
            .wr_en_scalar_o         (vector_wr_en)
        );
    end
    else begin : v_gen_off
        assign hold_vector  = '0;
        assign vector_wr_en = '0;
        assign vector_scalar_result     = '0;
        assign mem_address_vector       = '0;
        assign mem_read_enable_vector   = '0;
        assign mem_write_enable_vector  = '0;
        assign mem_write_data_vector    = '0;
        assign vtype_o = '0;
        assign vlen_o  = '0;
    end

////////////////////////////////////////////////////////////////////////////////
// Atomic Extension
////////////////////////////////////////////////////////////////////////////////

    logic        atomic_hold;
    logic        atomic_write_enable;
    logic        lrsc_result;

    if (AMOEXT != AMO_OFF) begin : gen_atomic_on
        logic lrsc_write_enable;
        logic lrsc_hold;
        logic lrsc_mem_read_enable;
        logic lrsc_mem_write_enable;

        if (AMOEXT != AMO_ZAAMO) begin : gen_zalrsc_on
            logic [31:0] reservation_addr;
            always_ff @(posedge clk or negedge reset_n) begin
                if (!reset_n) begin
                    reservation_addr <= '0;
                end
                else if (!stall) begin
                    unique case (1'b1)
                        ctrl_i.is_lr: reservation_addr <= rs1_data_i;
                        ctrl_i.is_sc: reservation_addr <= lrsc_hold ? reservation_addr : '0;
                        default: ;
                    endcase
                end
            end

            logic lrsc_enable;
            assign lrsc_enable = ctrl_i.is_sc && (rs1_data_i[1:0] == '0);

            logic [31:0] cmp_opA;
            logic [31:0] cmp_opB;

            lrsc lrsc_m (
                .clk               (clk                    ),
                .reset_n           (reset_n                ),
                .stall             (stall                  ),
                .equal_i           (equal                  ),
                .enable_i          (lrsc_enable            ),
                .exception_i       (exc_load_access_fault_i),
                .rs1_data_i        (rs1_data_i             ),
                .data_i            (mem_read_data_i[31:0]  ),
                .reservation_addr_i(reservation_addr       ),
                .reservation_data_i(reservation_data_i     ),
                .hold_o            (lrsc_hold              ),
                .write_enable_o    (lrsc_write_enable      ),
                .mem_read_enable_o (lrsc_mem_read_enable   ),
                .mem_write_enable_o(lrsc_mem_write_enable  ),
                .result_o          (lrsc_result            ),
                .cmp_opA_o         (cmp_opA                ),
                .cmp_opB_o         (cmp_opB                )
            );

            assign equal_opA = lrsc_enable ? cmp_opA : rs1_data_i;
            assign equal_opB = lrsc_enable ? cmp_opB : second_operand_i;
        end
        else begin : gen_zalrsc_off
            assign lrsc_result           = 1'b0;
            assign lrsc_hold             = 1'b0;
            assign lrsc_mem_read_enable  = 1'b0;
            assign lrsc_mem_write_enable = 1'b0;
            assign lrsc_write_enable     = 1'b0;
            assign equal_opA             = rs1_data_i;
            assign equal_opB             = second_operand_i;
        end

        logic amo_write_enable;
        logic amo_hold;
        logic amo_mem_read_enable;
        logic amo_mem_write_enable;

        if (AMOEXT != AMO_ZALRSC) begin : gen_zaamo_on
            logic amo_enable;
            assign amo_enable = ctrl_i.is_amo && (rs1_data_i[1:0] == '0);

            logic amo_lt;
            assign amo_lt = $signed(amo_operand) < $signed(rs2_data_i);

            logic amo_ltu;
            assign amo_ltu = amo_operand < rs2_data_i;

            logic [31:0] amo_result;
            always_comb begin
                unique case (ctrl_i.amo_op)
                    AMOADD:  amo_result = sum_result;
                    AMOAND:  amo_result = and_result;
                    AMOXOR:  amo_result = xor_result;
                    AMOOR:   amo_result = or_result;
                    AMOMAX:  amo_result = amo_lt  ? rs2_data_i  : amo_operand;
                    AMOMIN:  amo_result = amo_lt  ? amo_operand : rs2_data_i;
                    AMOMAXU: amo_result = amo_ltu ? rs2_data_i  : amo_operand;
                    AMOMINU: amo_result = amo_ltu ? amo_operand : rs2_data_i;
                    AMOSWAP: amo_result = rs2_data_i;
                    default: amo_result = '0;
                endcase
            end

            amo amo_m (
                .clk               (clk                    ),
                .reset_n           (reset_n                ),
                .stall             (stall                  ),
                .enable_i          (amo_enable             ),
                .exception_i       (exc_load_access_fault_i),
                .data_i            (mem_read_data_i[31:0]  ),
                .amo_result_i      (amo_result             ),
                .hold_o            (amo_hold               ),
                .write_enable_o    (amo_write_enable       ),
                .mem_read_enable_o (amo_mem_read_enable    ),
                .mem_write_enable_o(amo_mem_write_enable   ),
                .opA_o             (amo_operand            )
            );

        end
        else begin : gen_zaamo_off
            assign amo_hold             = 1'b0;
            assign amo_mem_read_enable  = 1'b0;
            assign amo_mem_write_enable = 1'b0;
            assign amo_operand          = '0;
            assign amo_write_enable     = 1'b0;
        end

        assign atomic_hold             = lrsc_hold             || amo_hold;
        assign atomic_write_enable     = lrsc_write_enable     || amo_write_enable;
        assign atomic_mem_read_enable  = lrsc_mem_read_enable  || amo_mem_read_enable;
        assign atomic_mem_write_enable = lrsc_mem_write_enable || amo_mem_write_enable;
    end
    else begin : gen_atomic_off
        assign amo_operand             = '0;
        assign atomic_hold             = 1'b0;
        assign atomic_mem_read_enable  = 1'b0;
        assign atomic_mem_write_enable = 1'b0;
        assign lrsc_result             = 1'b0;
        assign atomic_write_enable     = 1'b0;
        assign equal_opA               = rs1_data_i;
        assign equal_opB               = second_operand_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Zicond Extension
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] result_zicond;

    if (ZICONDEnable) begin : gen_zicond_on
        assign result_zicond = ctrl_i.zicond_is_eqz
            ? (rs2_data_i == '0 ? '0 : rs1_data_i)   // CZERO_EQZ
            : (rs2_data_i != '0 ? '0 : rs1_data_i);  // CZERO_NEZ
    end
    else begin : gen_zicond_off
        assign result_zicond = '0;
    end

    ////////////////////////////////////////////////////////////////////////////////
    // ZBKB Extension
    ////////////////////////////////////////////////////////////////////////////////

    logic [31:0] zbkb_result;

    if (ZBKBEnable) begin: zbkb_gen_on

        ///////////////////
        // Bitwise Logic //
        ///////////////////
        logic [31:0] bwlogic_operand_b;
        logic [31:0] bwlogic_or_result;
        logic [31:0] bwlogic_and_result;
        logic [31:0] bwlogic_xor_result;

        assign bwlogic_operand_b = second_operand_i ^ {32{1'b1}};

        assign bwlogic_or_result  = rs1_data_i | bwlogic_operand_b;
        assign bwlogic_and_result = rs1_data_i & bwlogic_operand_b;
        assign bwlogic_xor_result = rs1_data_i ^ bwlogic_operand_b;

        /////////////////
        // Bit reverse //
        /////////////////
        logic [4:0] shift_amt;
        assign shift_amt[4:0] = second_operand_i[4:0];

        logic [4:0] zbp_shift_amt;
        assign zbp_shift_amt[2:0] = shift_amt[2:0];
        assign zbp_shift_amt[4:3] = shift_amt[4:3];

        logic [31:0] rev_result;
        always_comb begin
            rev_result = rs1_data_i;

            if (zbp_shift_amt[0]) begin
                rev_result = ((rev_result & 32'h5555_5555) <<  1) |
                            ((rev_result & 32'haaaa_aaaa) >>  1);
            end

            if (zbp_shift_amt[1]) begin
                rev_result = ((rev_result & 32'h3333_3333) <<  2) |
                            ((rev_result & 32'hcccc_cccc) >>  2);
            end

            if (zbp_shift_amt[2]) begin
                rev_result = ((rev_result & 32'h0f0f_0f0f) <<  4) |
                            ((rev_result & 32'hf0f0_f0f0) >>  4);
            end

            if (zbp_shift_amt[3]) begin
                rev_result = ((rev_result & 32'h00ff_00ff) <<  8) |
                            ((rev_result & 32'hff00_ff00) >>  8);
            end

            if (zbp_shift_amt[4]) begin
                rev_result = ((rev_result & 32'h0000_ffff) << 16) |
                            ((rev_result & 32'hffff_0000) >> 16);
            end
        end

        ///////////////
        // Zip/Unzip //
        ///////////////
        logic [31:0] zip_result;
        logic [31:0] unzip_result;
        always_comb begin
            for (int i = 0; i < 16; i++) begin
                zip_result[2*i]        = rs1_data_i[i];
                zip_result[2*i + 1]    = rs1_data_i[i + 16];
                unzip_result[i]        = rs1_data_i[2*i];
                unzip_result[i + 16]   = rs1_data_i[2*i + 1];
            end
        end

        ////////////
        // Rotate //
        ////////////
        logic [4:0] shift_amt_compl; // complementary shift amount (32 - shift_amt)
        assign shift_amt_compl = 5'(6'd32 - {1'b0, second_operand_i[4:0]});

        logic [31:0] ror_result, rol_result;
        assign ror_result   =  srl_result | (rs1_data_i << shift_amt_compl);
        assign rol_result   =  sll_result | (rs1_data_i >> shift_amt_compl);

        always_comb begin
            unique case (ctrl_i.zbkb_op)
                ZBKBROR:   zbkb_result = ror_result;
                ZBKBROL:   zbkb_result = rol_result;
                ZBKBORN:   zbkb_result = bwlogic_or_result;
                ZBKBANDN:  zbkb_result = bwlogic_and_result;
                ZBKBXNOR:  zbkb_result = bwlogic_xor_result;
                ZBKBREV8,
                ZBKBBREV8: zbkb_result = rev_result;
                ZBKBZIP:   zbkb_result = zip_result;
                ZBKBUNZIP: zbkb_result = unzip_result;
                ZBKBPACKH: zbkb_result = {16'h0, second_operand_i[7:0], rs1_data_i[7:0]};
                default:   zbkb_result = {second_operand_i[15:0], rs1_data_i[15:0]};
            endcase
        end
    end
    else begin : gen_zbkb_off
        assign zbkb_result = '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Demux
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (1'b1)
            ctrl_i.is_csr:                                       result = csr_data_read_i;
            ctrl_i.is_jal_jalr:                                  result = pc_next;
            ctrl_i.is_slt:                                       result = {31'b0, less_than};
            ctrl_i.is_sltu:                                      result = {31'b0, less_than_unsigned};
            ctrl_i.is_xor:                                       result = xor_result;
            ctrl_i.is_or:                                        result = or_result;
            ctrl_i.is_and:                                       result = and_result;
            ctrl_i.is_sll:                                       result = sll_result;
            ctrl_i.is_srl:                                       result = srl_result;
            ctrl_i.is_sra:                                       result = sra_result;
            ctrl_i.is_lui:                                       result = second_operand_i;
            ctrl_i.is_auipc:                                     result = jump_imm_target_i;
            (MULEXT == MUL_M && ctrl_i.is_div):                  result = div_result;
            (MULEXT == MUL_M && ctrl_i.is_rem):                  result = rem_result;
            (MULEXT != MUL_OFF && ctrl_i.is_mul):                result = mul_result;
            (AMOEXT inside {AMO_ZALRSC, AMO_A} && ctrl_i.is_sc): result = {31'h0, lrsc_result};
            (ZICONDEnable && ctrl_i.is_zicond):                  result = result_zicond;
            (ZBKBEnable && ctrl_i.is_zbkb):                      result = zbkb_result;
            (ZKNEEnable && ctrl_i.is_aes):                       result = aes_result;
            (ZKNHEnable && ctrl_i.is_sha2):                      result = sha2_result;
            (VEnable && ctrl_i.is_vector):                       result = vector_scalar_result;
            (XKYBEREnable && ctrl_i.is_kyber):                   result = xkyber_result;
            default:                                             result = sum_result;
        endcase
    end

    logic we_atomic;
    assign we_atomic  = (rd_i != '0 && atomic_write_enable);

    logic we_default;
    assign we_default = (ctrl_i.rd_we && rd_i != '0 && !hold_o && !raise_exception);

    always_comb begin
        unique case (1'b1)
            ctrl_i.is_vector:   write_enable = ctrl_i.rd_we && rd_i != '0 && vector_wr_en;
            ctrl_i.is_sc:       write_enable = we_atomic;
            ctrl_i.is_amo:      write_enable = we_atomic;
            default:            write_enable = we_default;
        endcase
    end

    assign write_enable_fwd_o = write_enable;

////////////////////////////////////////////////////////////////////////////////
// Output Registers
////////////////////////////////////////////////////////////////////////////////

    assign hold_o = (hold_div || hold_mul  || hold_xkyber || hold_vector || atomic_hold) && !exc_load_access_fault_i;

    wb_ctrl_t wb_ctrl_next;
    always_comb begin
        wb_ctrl_next.rd_we       = write_enable;
        wb_ctrl_next.is_load     = ctrl_i.is_load || (ctrl_i.is_sc && !atomic_write_enable)
                                                   || (ctrl_i.is_amo && atomic_write_enable);
        wb_ctrl_next.is_lr       = ctrl_i.is_lr;
        wb_ctrl_next.is_sc       = ctrl_i.is_sc;
        wb_ctrl_next.is_byte     = ctrl_i.is_byte;
        wb_ctrl_next.is_half     = ctrl_i.is_half;
        wb_ctrl_next.is_unsigned = ctrl_i.is_unsigned;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            ctrl_o <= '0;
        else if (!stall)
            ctrl_o <= wb_ctrl_next;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            result_o <= '0;
        else if (!stall)
            result_o <= result;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            rd_o <= '0;
        else if (!stall)
            rd_o <= rd_i;
    end

    assign result_fwd_o = result;

//////////////////////////////////////////////////////////////////////////////
// BRANCH CONTROL
//////////////////////////////////////////////////////////////////////////////

    assign jump_target_o = ctrl_i.is_jalr ? {sum_result[31:1], 1'b0} : jump_imm_target_i;

    logic should_jump;
    always_comb begin
        unique case (1'b1)
            ctrl_i.is_beq:      should_jump = equal;
            ctrl_i.is_bne:      should_jump = !equal;
            ctrl_i.is_blt:      should_jump = less_than;
            ctrl_i.is_bltu:     should_jump = less_than_unsigned;
            ctrl_i.is_bge:      should_jump = greater_equal;
            ctrl_i.is_bgeu:     should_jump = greater_equal_unsigned;
            ctrl_i.is_jal_jalr: should_jump = 1'b1;
            default:            should_jump = 1'b0;
        endcase
    end

    logic machine_return;
    always_comb begin
        if (machine_return)
            ctx_switch_target_o = mepc_i;
        else
            ctx_switch_target_o = mtvec_i;
    end

    /* Two jumps in sequence never occur, but the exec stage can be stalled */
    /* So we only consider a new jump on posedge, so we can keep fetching   */
    /* (and decoding)                                                       */
    logic jump;
    if (BRANCHPRED) begin : gen_bp_on
        assign jump            = ( should_jump && !(ctrl_i.bp_taken && bp_ack_i));
        assign jump_rollback_o = (!should_jump &&  (ctrl_i.bp_taken && bp_ack_i));
    end
    else begin : gen_bp_off
        assign jump            = should_jump;
        assign jump_rollback_o = 1'b0;
    end

    logic jump_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            jump_r <= 1'b0;
        end
        else begin;
            if (!stall)
                jump_r <= 1'b0;
            else if (jump)
                jump_r <= 1'b1;
        end
    end
    assign jump_o = jump && !jump_r;

    logic interrupt_ack;
    assign ctx_switch_o = (machine_return || raise_exception || interrupt_ack) && !stall;

    assign should_jump_o = jump_o || ctx_switch_o;
    assign pc_irq_o      = should_jump ? jump_target_o : pc_next;

    logic iaddr_misaligned;
    assign iaddr_misaligned = (!COMPRESSED && jump_target_o[1] && should_jump);

//////////////////////////////////////////////////////////////////////////////
// Privileged Architecture Control
//////////////////////////////////////////////////////////////////////////////

    logic illegal_mret;
    assign illegal_mret = ctrl_i.is_mret && (privilege_i != 2'b11);

    /* We can't change privilege until the end of the instruction */
    /* Hence, exception, ret and irq must be masked by stall      */
    assign raise_exception = (
        ctrl_i.exc_inst_access_fault ||
        ctrl_i.exc_ilegal_inst ||
        exc_load_access_fault_i ||
        illegal_mret ||
        ctrl_i.is_ecall || ctrl_i.is_ebreak ||
        exc_ilegal_csr_inst ||
        iaddr_misaligned ||
        laddr_misaligned ||
        saddr_misaligned
    );
    assign raise_exception_o = raise_exception && !stall;

    assign machine_return   = ctrl_i.is_mret && (privilege_i == 2'b11);
    assign machine_return_o = machine_return && !stall;

    assign interrupt_ack = (
        interrupt_pending_i &&
        valid_i &&    /* We need a valid pc reference to ack an IRQ */
        !machine_return &&
        !raise_exception &&
        !hold_o
    );

    assign interrupt_ack_o = interrupt_ack && !stall;

    always_comb begin
        if (exc_load_access_fault_i)    /* Highest priority because it happened last cycle */
            exception_code_o  = LOAD_ACCESS_FAULT;
        else if (ctrl_i.exc_inst_access_fault)
            exception_code_o  = INSTRUCTION_ACCESS_FAULT;
        else if (ctrl_i.exc_ilegal_inst || exc_ilegal_csr_inst || illegal_mret)
            exception_code_o  = ILLEGAL_INSTRUCTION;
        else if (iaddr_misaligned)
            exception_code_o  = INSTRUCTION_ADDRESS_MISALIGNED;
        else if (ctrl_i.is_ecall)
            exception_code_o  = (privilege_i == USER) ? ECALL_FROM_UMODE : ECALL_FROM_MMODE;
        else if (ctrl_i.is_ebreak)
            exception_code_o  = BREAKPOINT;
        else if (laddr_misaligned)
            exception_code_o  = LOAD_ADDRESS_MISALIGNED;
        else if (saddr_misaligned)
            exception_code_o  = STORE_AMO_ADDRESS_MISALIGNED;
        else
            exception_code_o  = NE;
    end

    logic [31:0] pc_r;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            pc_r <= '0;
        else if (!stall)
            pc_r <= pc_i;
    end

    assign pc_exc_o = exc_load_access_fault_i ? pc_r : pc_i;

endmodule
