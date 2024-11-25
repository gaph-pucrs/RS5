/*!\file execute.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
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
    parameter environment_e Environment = ASIC,
    parameter mul_e         MULEXT      = MUL_M,
    parameter atomic_e      AMOEXT      = AMO_A,
    parameter bit           ZKNEEnable  = 1'b0,
    parameter bit           VEnable     = 1'b0,
    parameter int           VLEN        = 64,
    parameter bit           BRANCHPRED  = 1'b1
)
(
    input   logic               clk,
    input   logic               reset_n,
    input   logic               stall,

    /* Bits 14:12 and 6:0 are not used in this module */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        instruction_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   logic [31:0]        pc_i,
    input   logic [31:0]        rs1_data_i,
    input   logic [31:0]        rs2_data_i,
    input   logic [31:0]        second_operand_i,
    input   logic  [4:0]        rd_i,
    input   logic  [4:0]        rs1_i,
    input   iType_e             instruction_operation_i,
    input   logic               instruction_compressed_i,
    
    /* Not used without zaamo */
    /* verilator lint_off UNUSEDSIGNAL */
    input   iTypeAtomic_e       atomic_operation_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* Not used if VEnable is 0 */
    /* verilator lint_off UNUSEDSIGNAL */
    input   iTypeVector_e       vector_operation_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   privilegeLevel_e    privilege_i,
    input   logic               exc_ilegal_inst_i,
    input   logic               exc_misaligned_fetch_i,
    input   logic               exc_inst_access_fault_i,
    input   logic               exc_load_access_fault_i,

    output  logic               hold_o,
    output  logic               write_enable_o,
    output  logic               write_enable_fwd_o,
    output  iType_e             instruction_operation_o,
    output  logic   [31:0]      result_o,
    output  logic   [31:0]      result_fwd_o,
    output  logic   [ 4:0]      rd_o,

    output  logic [31:0]        mem_address_o,
    output  logic               mem_read_enable_o,
    output  logic  [3:0]        mem_write_enable_o,
    output  logic [31:0]        mem_write_data_o,
    /* Not used if VEnable is 0 */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        mem_read_data_i,
    /* verilator lint_on UNUSEDSIGNAL */

    /* We only use some bits of this signal here */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [11:0]        csr_address_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output  logic               csr_read_enable_o,
    input   logic [31:0]        csr_data_read_i,
    output  logic               csr_write_enable_o,
    output  csrOperation_e      csr_operation_o,
    output  logic [31:0]        csr_data_o,

    output  logic [31:0]        vtype_o,
    output  logic [31:0]        vlen_o,

    /* Not used if BP is off */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic               bp_taken_i,
    /* verilator lint_on UNUSEDSIGNAL */
    output  logic               jump_rollback_o,
    output  logic               ctx_switch_o,
    output  logic [31:0]        ctx_switch_target_o,

    input   logic               interrupt_pending_i,
    input   logic [31:0]        mtvec_i,
    input   logic [31:0]        mepc_i,
    input   logic [31:0]        jump_imm_target_i,

    /* Not used without zalrsc */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        reservation_data_i,
    /* verilator lint_on UNUSEDSIGNAL */

    output  logic               jump_o,
    output  logic               interrupt_ack_o,
    output  logic               machine_return_o,
    output  logic               raise_exception_o,
    output  logic [31:0]        jump_target_o,
    output  exceptionCode_e     exception_code_o
);

    logic [31:0]    result;
    logic           write_enable;
    logic           exc_ilegal_csr_inst;

//////////////////////////////////////////////////////////////////////////////
// ALU
//////////////////////////////////////////////////////////////////////////////

    logic [31:0]    sum_result;
    logic [31:0]    sum2_result;
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

    logic [31:0] first_operand;

    logic [31:0] sum2_opA;
    always_comb begin
        unique case (instruction_operation_i)
            // To link register. Maybe we can remove this by using the PC in decode stage
            JAL, JALR: sum2_opA = pc_i;
            default:   sum2_opA = first_operand;
        endcase
    end

    logic [31:0] sum2_opB;
    always_comb begin
        unique case (instruction_operation_i)
            // To link register. Maybe we can remove this by using the PC in decode stage
            JAL, JALR: sum2_opB = instruction_compressed_i ? 32'd2 : 32'd4;
            SUB:       sum2_opB = -second_operand_i;
            default:   sum2_opB = second_operand_i; // AMO_W
        endcase
    end

    always_comb begin
        /* "Unmuxable" operators */
        sum_result              = rs1_data_i +  second_operand_i;
        equal                   = rs1_data_i == second_operand_i;
        less_than_unsigned      = rs1_data_i <  second_operand_i;
        greater_equal_unsigned  = rs1_data_i >= second_operand_i;
        less_than               = $signed(rs1_data_i) <  $signed(second_operand_i);
        greater_equal           = $signed(rs1_data_i) >= $signed(second_operand_i);

        sll_result              = rs1_data_i << second_operand_i[4:0];
        srl_result              = rs1_data_i >> second_operand_i[4:0];
        sra_result              = $signed(rs1_data_i) >>> second_operand_i[4:0];

        /* "Muxable" operators */
        sum2_result             = sum2_opA      + sum2_opB;
        and_result              = first_operand & second_operand_i;
        or_result               = first_operand | second_operand_i;
        xor_result              = first_operand ^ second_operand_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] amo_operand;

    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] mem_address_vector;
    logic [31:0] mem_address;
    /* verilator lint_on UNUSEDSIGNAL */

    logic        mem_read_enable;
    logic        mem_read_enable_vector;

    logic  [3:0] mem_write_enable;
    logic  [3:0] mem_write_enable_vector;

    logic [31:0] mem_write_data;
    logic [31:0] mem_write_data_vector;

    logic        atomic_mem_read_enable;
    logic        atomic_mem_write_enable;

    always_comb begin
        unique case (instruction_operation_i)
            VLOAD,
            VSTORE:  mem_address_o = {mem_address_vector[31:2], 2'b00};
            AMO_W,
            LR_W,
            SC_W:    mem_address_o = rs1_data_i;
            default: mem_address_o = mem_address;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            VLOAD,
            VSTORE:  mem_read_enable_o = mem_read_enable_vector;
            default: mem_read_enable_o = mem_read_enable || atomic_mem_read_enable;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            VLOAD,
            VSTORE:  mem_write_enable_o = mem_write_enable_vector;
            default: mem_write_enable_o = mem_write_enable | {4{atomic_mem_write_enable}};
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            VLOAD,
            VSTORE:  mem_write_data_o = mem_write_data_vector;
            AMO_W:   mem_write_data_o = amo_operand;
            default: mem_write_data_o = mem_write_data;
        endcase
    end

    assign mem_address     = {sum_result[31:2], 2'b00};
    assign mem_read_enable = instruction_operation_i inside {LB, LBU, LH, LHU, LW, LR_W};

    always_comb begin
        unique case (instruction_operation_i)
            SB:         mem_write_data = {4{rs2_data_i[7:0]}};
            SH:         mem_write_data = {2{rs2_data_i[15:0]}};
            default:    mem_write_data = rs2_data_i;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            SB: unique case (sum_result[1:0])
                    2'b11:   mem_write_enable = 4'b1000;
                    2'b10:   mem_write_enable = 4'b0100;
                    2'b01:   mem_write_enable = 4'b0010;
                    default: mem_write_enable = 4'b0001;
                endcase
            SH:              mem_write_enable = (sum_result[1])
                                                ? 4'b1100
                                                : 4'b0011;
            SW:              mem_write_enable = 4'b1111;
            default:         mem_write_enable = 4'b0000;
        endcase
end

//////////////////////////////////////////////////////////////////////////////
// CSR access signals
//////////////////////////////////////////////////////////////////////////////

    logic       csr_read_enable, csr_write_enable;

    assign csr_read_enable_o = csr_read_enable & !exc_ilegal_csr_inst;
    assign csr_write_enable_o = csr_write_enable & !exc_ilegal_csr_inst;

    always_comb begin
        unique case (instruction_operation_i)
            CSRRW, CSRRWI: begin
                csr_read_enable  = (rd_i != '0);
                csr_write_enable = 1'b1;
            end
            CSRRS, CSRRC, CSRRSI, CSRRCI: begin
                csr_read_enable  = 1'b1;
                csr_write_enable = (rs1_i != '0);
            end
            default: begin
                csr_read_enable  = 1'b0;
                csr_write_enable = 1'b0;
            end
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            CSRRW, CSRRS, CSRRC:    csr_data_o = rs1_data_i;
            default:                csr_data_o = {27'b0, rs1_i};
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            CSRRW, CSRRWI:  csr_operation_o = WRITE;
            CSRRS, CSRRSI:  csr_operation_o = SET;
            CSRRC, CSRRCI:  csr_operation_o = CLEAR;
            default:        csr_operation_o = NONE;
        endcase
    end

    always_comb begin
        // Raise exeption if CSR is read only and write enable is true
        if (csr_address_i[11:10] == 2'b11 && csr_write_enable == 1'b1) begin
            exc_ilegal_csr_inst = 1;
        end
        // Check Level privileges
        else if (csr_address_i[9:8] > privilege_i && ((csr_read_enable | csr_write_enable) == 1'b1)) begin
            exc_ilegal_csr_inst = 1;
        end
        // No exception is raised
        else begin
            exc_ilegal_csr_inst = 0;
        end
    end

/////////////////////////////////////////////////////////////////////////////
// Multiplication signals
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] mul_result;
    logic        hold_mul;
    logic        hold_div;

    if (MULEXT != MUL_OFF) begin : gen_zmmul_on

        logic [1:0] signed_mode_mul;
        logic       enable_mul;
        logic       mul_low;

        always_comb begin
            unique case (instruction_operation_i)
                MULH:    signed_mode_mul = 2'b11;
                MULHSU:  signed_mode_mul = 2'b01;
                default: signed_mode_mul = 2'b00;
            endcase
        end

        assign enable_mul = (instruction_operation_i inside {MUL, MULH, MULHU, MULHSU});
        assign mul_low    = (instruction_operation_i == MUL);

        mul mul1 (
            .clk              (clk),
            .reset_n          (reset_n),
            .stall            (stall),
            .first_operand_i  (rs1_data_i),
            .second_operand_i (rs2_data_i),
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

        assign enable_div = (instruction_operation_i inside {DIV, DIVU, REM, REMU});
        assign signed_div = (instruction_operation_i inside {DIV, REM});

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

        assign aes_mix = (instruction_operation_i == AES32ESMI);
        assign aes_valid = (instruction_operation_i inside {AES32ESMI, AES32ESI});

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
// Vector Extension
//////////////////////////////////////////////////////////////////////////////
    logic [31:0] vector_scalar_result;
    logic        vector_wr_en;
    logic        hold_vector;

    if (VEnable) begin : v_gen_on
        vectorUnit #(
            .Environment (Environment),
            .VLEN        (VLEN)
        ) vector (
            .clk                    (clk),
            .reset_n                (reset_n),
            .instruction_i          (instruction_i),
            .instruction_operation_i(instruction_operation_i),
            .vector_operation_i     (vector_operation_i),
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
                    unique case (instruction_operation_i)
                        LR_W: reservation_addr <= rs1_data_i;
                        SC_W: reservation_addr <= lrsc_hold ? reservation_addr : '0;
                        default: ;
                    endcase
                end
            end

            logic lrsc_enable;
            assign lrsc_enable = (instruction_operation_i == SC_W);

            lrsc lrsc_m (
                .clk               (clk                  ),
                .reset_n           (reset_n              ),
                .stall             (stall                ),
                .enable_i          (lrsc_enable          ),
                .rs1_data_i        (rs1_data_i           ),
                .data_i            (mem_read_data_i      ),
                .reservation_addr_i(reservation_addr     ),
                .reservation_data_i(reservation_data_i   ),
                .hold_o            (lrsc_hold            ),
                .write_enable_o    (lrsc_write_enable    ),
                .mem_read_enable_o (lrsc_mem_read_enable ),
                .mem_write_enable_o(lrsc_mem_write_enable),
                .result_o          (lrsc_result          )
            );
        end
        else begin : gen_zalrsc_off
            assign lrsc_result           = 1'b0;
            assign lrsc_hold             = 1'b0;
            assign lrsc_mem_read_enable  = 1'b0;
            assign lrsc_mem_write_enable = 1'b0;
            assign lrsc_write_enable     = 1'b0;
        end

        logic amo_write_enable;
        logic amo_hold;
        logic amo_mem_read_enable;
        logic amo_mem_write_enable;

        if (AMOEXT != AMO_ZALRSC) begin : gen_zaamo_on
            logic amo_enable;
            assign amo_enable = (instruction_operation_i == AMO_W);

            logic amo_lt;
            assign amo_lt = $signed(amo_operand) < $signed(rs2_data_i);
            
            logic amo_ltu;
            assign amo_ltu = amo_operand < rs2_data_i;

            logic [31:0] amo_result;
            always_comb begin
                unique case (atomic_operation_i)
                    AMOADD:  amo_result = sum2_result;
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
                .clk               (clk                 ),
                .reset_n           (reset_n             ),
                .stall             (stall               ),
                .enable_i          (amo_enable          ),
                .data_i            (mem_read_data_i     ),
                .amo_result_i      (amo_result          ),
                .hold_o            (amo_hold            ),
                .write_enable_o    (amo_write_enable    ),
                .mem_read_enable_o (amo_mem_read_enable ),
                .mem_write_enable_o(amo_mem_write_enable),
                .opA_o             (amo_operand         )
            );

            assign first_operand = amo_enable ? amo_operand : rs1_data_i;
        end
        else begin : gen_zaamo_off
            assign amo_hold             = 1'b0;
            assign amo_mem_read_enable  = 1'b0;
            assign amo_mem_write_enable = 1'b0;
            assign first_operand        = rs1_data_i;
            assign amo_operand          = '0;
            assign amo_write_enable     = 1'b0;
        end

        assign atomic_hold             = lrsc_hold             || amo_hold;
        assign atomic_write_enable     = lrsc_write_enable     || amo_write_enable;
        assign atomic_mem_read_enable  = lrsc_mem_read_enable  || amo_mem_read_enable;
        assign atomic_mem_write_enable = lrsc_mem_write_enable || amo_mem_write_enable;
    end
    else begin : gen_atomic_off
        assign first_operand           = rs1_data_i;
        assign amo_operand             = '0;
        assign atomic_hold             = 1'b0;
        assign atomic_mem_read_enable  = 1'b0;
        assign atomic_mem_write_enable = 1'b0;
        assign lrsc_result             = 1'b0;
        assign atomic_write_enable     = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// Demux
//////////////////////////////////////////////////////lrsc_result////////////////////////

    always_comb begin
        unique case (instruction_operation_i)
            CSRRW, CSRRS, CSRRC,
            CSRRWI,CSRRSI,CSRRCI:   result = csr_data_read_i;
            JAL,JALR,SUB:           result = sum2_result;
            SLT:                    result = {31'b0, less_than};
            SLTU:                   result = {31'b0, less_than_unsigned};
            XOR:                    result = xor_result;
            OR:                     result = or_result;
            AND:                    result = and_result;
            SLL:                    result = sll_result;
            SRL:                    result = srl_result;
            SRA:                    result = sra_result;
            LUI:                    result = second_operand_i;
            AUIPC:                  result = jump_imm_target_i;
            DIV,DIVU:               result = div_result;
            REM,REMU:               result = rem_result;
            MUL,MULH,MULHU,MULHSU:  result = mul_result;
            AES32ESI, AES32ESMI:    result = aes_result;
            VECTOR, VLOAD, VSTORE:  result = vector_scalar_result;
            default:                result = sum_result;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            NOP,
            SC_W,AMO_W,
            SB,SH,SW, 
            BEQ,BNE,
            BLT,BLTU,
            BGE,BGEU:   write_enable = 1'b0;
            VECTOR,
            VLOAD,
            VSTORE:     write_enable = vector_wr_en;
            default:    write_enable = (rd_i != '0 && !hold_o && !raise_exception_o);
        endcase
    end

    assign write_enable_fwd_o = write_enable;

////////////////////////////////////////////////////////////////////////////////
// Output Registers
////////////////////////////////////////////////////////////////////////////////
    
    assign hold_o = hold_div || hold_mul || hold_vector || atomic_hold;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            write_enable_o <= 1'b0;
        end
        else if (!stall) begin
            /* Non-default cases have no forwarding */
            unique case (instruction_operation_i)
                SC_W,
                AMO_W:   write_enable_o <= (rd_i != '0 && atomic_write_enable && !raise_exception_o);
                default: write_enable_o <= write_enable;
            endcase
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            instruction_operation_o <= NOP;
        end
        else if (!stall) begin
            unique case (instruction_operation_i)
                SC_W:    instruction_operation_o <=  atomic_write_enable ? instruction_operation_i : LW;
                AMO_W:   instruction_operation_o <= !atomic_write_enable ? instruction_operation_i : LW;
                default: instruction_operation_o <= instruction_operation_i;
            endcase
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            result_o <= '0;
        end
        else if (!stall) begin
            /* Non-default cases have no forwarding */
            unique case (instruction_operation_i)
                SC_W:    result_o <= {31'h0, lrsc_result};
                // AMO_W has no result
                default: result_o <= result;
            endcase
        end
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

    always_comb begin
        unique case (instruction_operation_i)
            JALR:       jump_target_o = {sum_result[31:1], 1'b0};
            default:    jump_target_o = jump_imm_target_i;
        endcase
    end

    logic should_jump;
    always_comb begin
        unique case (instruction_operation_i)
            BEQ:        should_jump = equal;
            BNE:        should_jump = !equal;
            BLT:        should_jump = less_than;
            BLTU:       should_jump = less_than_unsigned;
            BGE:        should_jump = greater_equal;
            BGEU:       should_jump = greater_equal_unsigned;
            JAL, JALR:  should_jump = 1'b1;
            default:    should_jump = 1'b0;
        endcase
    end

    always_comb begin
        if (machine_return_o)
            ctx_switch_target_o = mepc_i;
        else if (raise_exception_o || interrupt_ack_o)
            ctx_switch_target_o = mtvec_i;
        else
            ctx_switch_target_o = jump_target_o;
    end

    assign ctx_switch_o = machine_return_o || raise_exception_o || interrupt_ack_o || jump_o;

    if (BRANCHPRED) begin : gen_bp_on
        assign jump_o          = ( should_jump && (!bp_taken_i ||  interrupt_ack_o));
        assign jump_rollback_o = (!should_jump && ( bp_taken_i && !interrupt_ack_o));
    end
    else begin : gen_bp_off
        assign jump_o          = should_jump;
        assign jump_rollback_o = 1'b0;
    end

//////////////////////////////////////////////////////////////////////////////
// Privileged Architecture Control
//////////////////////////////////////////////////////////////////////////////

    assign raise_exception_o = (
        (
            exc_inst_access_fault_i 
            || exc_ilegal_inst_i 
            || exc_ilegal_csr_inst 
            || exc_misaligned_fetch_i
            || (instruction_operation_i inside {ECALL, EBREAK})
            || (exc_load_access_fault_i && (mem_read_enable_o || (mem_write_enable_o != '0)))
        )
        && (instruction_operation_i != NOP)
    );

    assign machine_return_o = !raise_exception_o && (instruction_operation_i == MRET);

    assign interrupt_ack_o = (
           !machine_return_o 
        && !raise_exception_o 
        && (interrupt_pending_i && instruction_operation_i != NOP && !hold_o)
    );

    always_comb begin
        if (exc_inst_access_fault_i)
            exception_code_o  = INSTRUCTION_ACCESS_FAULT;
        else if ((exc_ilegal_inst_i || exc_ilegal_csr_inst)) 
            exception_code_o  = ILLEGAL_INSTRUCTION;
        else if (exc_misaligned_fetch_i)
            exception_code_o  = INSTRUCTION_ADDRESS_MISALIGNED;
        else if (instruction_operation_i == ECALL)
            exception_code_o  = (privilege_i == USER) ? ECALL_FROM_UMODE : ECALL_FROM_MMODE;
        else if (instruction_operation_i == EBREAK)
            exception_code_o  = BREAKPOINT;
        else if (exc_load_access_fault_i)
            exception_code_o  = LOAD_ACCESS_FAULT;
        else
            exception_code_o  = NE;
    end

endmodule
