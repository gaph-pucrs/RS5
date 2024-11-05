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
 * The operations are performed based on Tag comparisons between this unit's tag
 * and the instruction tag, if they mismatch the instruction is killed and its
 * operation is not performed. A performed branch causes the internal tag to be
 * increased, causing the tag mismatch on the following instructions until an
 * instruction fetched from the new flow arrives with the updated tag.
 */

`include "RS5_pkg.sv"

module execute
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
    parameter rv32_e        RV32        = RV32I,
    parameter bit           ZKNEEnable  = 1'b0,
    parameter atomic_ext_e  AMOEXT      = AMO_OFF,
    parameter bit           VEnable     = 1'b0,
    parameter int           VLEN        = 64
)
(
    input   logic               clk,
    input   logic               reset_n,
    input   logic               sys_reset,
    input   logic               stall,

    /* Bits 14:12 and 6:0 are not used in this module */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        instruction_i,
    /* verilator lint_on UNUSEDSIGNAL */

    input   logic [31:0]        pc_i,
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   logic [31:0]        third_operand_i,
    input   iType_e             instruction_operation_i,
    input   logic               instruction_compressed_i,
    /* Not used if VEnable is 0 */
    /* verilator lint_off UNUSEDSIGNAL */
    input   iTypeVector_e       vector_operation_i,
    /* verilator lint_on UNUSEDSIGNAL */
    /* Not used if AMOEXT is AMO_OFF */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        atomic_read_value_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input   logic  [2:0]        tag_i,
    input   privilegeLevel_e    privilege_i,

    input   logic               exc_ilegal_inst_i,
    input   logic               exc_misaligned_fetch_i,
    input   logic               exc_inst_access_fault_i,
    input   logic               exc_load_access_fault_i,

    output  logic               hold_o,
    output  logic               killed_o,
    output  logic               write_enable_o,
    output  iType_e             instruction_operation_o,
    output  logic [31:0]        result_o,

    output  logic [31:0]        mem_address_o,
    output  logic               mem_read_enable_o,
    output  logic  [3:0]        mem_write_enable_o,
    output  logic [31:0]        mem_write_data_o,
    /* Not used if VEnable is 0 */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic [31:0]        mem_read_data_i,
    /* verilator lint_on UNUSEDSIGNAL */

    output  logic [11:0]        csr_address_o,
    output  logic               csr_read_enable_o,
    input   logic [31:0]        csr_data_read_i,
    output  logic               csr_write_enable_o,
    output  csrOperation_e      csr_operation_o,
    output  logic [31:0]        csr_data_o,

    output  logic [31:0]        vtype_o,
    output  logic [31:0]        vlen_o,

    output  logic               jump_o,
    output  logic [31:0]        jump_target_o,

    input   logic               interrupt_pending_i,
    output  logic               interrupt_ack_o,
    output  logic               machine_return_o,
    output  logic               raise_exception_o,

    /* ATOMIC OUTPUT */
    output logic [4:0]          rd_atomic_o,
    output logic                atomic_write_reg_o,

    output  exceptionCode_e     exception_code_o
);

    logic  [2:0]    curr_tag;
    logic [31:0]    result;
    logic [31:0]    atomic_read_value;
    logic           killed;
    logic           write_enable;
    logic           exc_ilegal_csr_inst;
    logic           atomic_write;
    logic           atomic_write_reg;

    logic signed [31:0]  first_operand_signed;
    logic signed [31:0]  second_operand_signed;

    assign second_operand_signed = second_operand_i;

//////////////////////////////////////////////////////////////////////////////
// ALU
//////////////////////////////////////////////////////////////////////////////

    logic [31:0]    sum2_opA;
    logic [31:0]    sum2_opB;
    logic [31:0]    sum_result;
    logic [31:0]    sum2_result;
    logic [31:0]    and_result;
    logic [31:0]    or_result;
    logic [31:0]    xor_result;
    logic [31:0]    sll_result;
    logic [31:0]    srl_result;
    logic [31:0]    sra_result;

    logic        [31:0]    first_operand;

    logic           equal;
    logic           less_than;
    logic           less_than_unsigned;
    logic           greater_equal;
    logic           greater_equal_unsigned;
    logic           jump;

    assign first_operand        = atomic_write_reg ? atomic_read_value : first_operand_i;
    assign first_operand_signed = first_operand;

    always_comb begin
        unique case (instruction_operation_i)
            SUB:      sum2_opA = first_operand_i;
            default:  sum2_opA = pc_i;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            JAL, JALR:  sum2_opB = instruction_compressed_i ? 2 : 4;
            SUB:        sum2_opB = -second_operand_i;
            default:    sum2_opB = third_operand_i;
        endcase
    end

    always_comb begin
        sum_result              = first_operand + second_operand_i;
        sum2_result             = sum2_opA + sum2_opB;
        and_result              = first_operand & second_operand_i;
        or_result               = first_operand | second_operand_i;
        xor_result              = first_operand ^ second_operand_i;
        sll_result              = first_operand_i << second_operand_i[4:0];
        srl_result              = first_operand_i >> second_operand_i[4:0];
        sra_result              = first_operand_signed >>> second_operand_i[4:0];

        equal                   = first_operand_i == second_operand_i;
        less_than               = first_operand_signed < second_operand_signed;
        less_than_unsigned      = first_operand < second_operand_i;
        greater_equal           = first_operand_signed >= second_operand_signed;
        greater_equal_unsigned  = first_operand >= second_operand_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    /* verilator lint_off UNUSEDSIGNAL */
    logic [31:0] mem_address_vector;
    logic [31:0] mem_address;
    /* verilator lint_on UNUSEDSIGNAL */

    logic        mem_read_enable;
    logic        mem_read_enable_vector;
    logic        mem_read_enable_atomic;

    logic  [3:0] mem_write_enable;
    logic  [3:0] mem_write_enable_vector;

    logic [31:0] mem_write_data;
    logic [31:0] mem_write_data_vector;

    always_comb begin
        case (instruction_operation_i)
            VLOAD, VSTORE:
                mem_address_o = {mem_address_vector[31:2], 2'b00};
            AMOSWAP, AMOADD, AMOXOR, AMOAND, AMOOR, AMOMIN, AMOMAX, AMOMINU, AMOMAXU, LR, SC:
                mem_address_o = {first_operand_i[31:2], 2'b00};
            default:
                mem_address_o = mem_address;
        endcase
    end

    always_comb begin
        case (instruction_operation_i)
            VLOAD, VSTORE:
                mem_read_enable_o  = mem_read_enable_vector;
            AMOSWAP, AMOADD, AMOXOR, AMOAND, AMOOR, AMOMIN, AMOMAX, AMOMINU, AMOMAXU, LR, SC:
                mem_read_enable_o  = mem_read_enable_atomic;
            default:
                mem_read_enable_o  = mem_read_enable;
        endcase
    end

    always_comb begin
        case (instruction_operation_i)
            VLOAD, VSTORE:
                mem_write_enable_o = mem_write_enable_vector;
            AMOSWAP, AMOADD, AMOXOR, AMOAND, AMOOR, AMOMIN, AMOMAX, AMOMINU, AMOMAXU, LR, SC:
                mem_write_enable_o = {4{atomic_write}};
            default:
                mem_write_enable_o = mem_write_enable;
        endcase
    end

    always_comb begin
        case (instruction_operation_i)
            VLOAD, 
            VSTORE:  mem_write_data_o = mem_write_data_vector;
            LR,
            SC,
            AMOSWAP: mem_write_data_o = second_operand_i;
            AMOADD:  mem_write_data_o = sum_result;
            AMOXOR:  mem_write_data_o = xor_result;
            AMOAND:  mem_write_data_o = and_result;
            AMOOR:   mem_write_data_o = or_result;
            AMOMIN:  mem_write_data_o = less_than  ? first_operand : second_operand_i;
            AMOMAX:  mem_write_data_o = !less_than ? first_operand : second_operand_i;
            AMOMINU: mem_write_data_o = less_than_unsigned  ? first_operand : second_operand_i;
            AMOMAXU: mem_write_data_o = !less_than_unsigned ? first_operand : second_operand_i;
            default: mem_write_data_o = mem_write_data;
        endcase
    end

    assign mem_address[31:2]  = sum_result[31:2];
    assign mem_address [1:0]  = '0;
    assign mem_read_enable    = instruction_operation_i inside {LB, LBU, LH, LHU, LW};

    always_comb begin
        unique case (instruction_operation_i)
            SB:         mem_write_data = {4{third_operand_i[7:0]}};
            SH:         mem_write_data = {2{third_operand_i[15:0]}};
            default:    mem_write_data = third_operand_i;
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

    logic [4:0] rd, rs1;
    logic       csr_read_enable, csr_write_enable;

    assign rd  = instruction_i[11:7];
    assign rs1 = instruction_i[19:15];

    assign csr_address_o = instruction_i[31:20];

    assign csr_read_enable_o = csr_read_enable & !exc_ilegal_csr_inst;
    assign csr_write_enable_o = csr_write_enable & !exc_ilegal_csr_inst;

    always_comb begin
        unique case (instruction_operation_i)
            CSRRW, CSRRWI: begin
                csr_read_enable  = (rd == '0) ? 1'b0 : 1'b1;
                csr_write_enable = 1'b1;
            end
            CSRRS, CSRRC, CSRRSI, CSRRCI: begin
                csr_read_enable  = 1'b1;
                csr_write_enable = (rs1 == '0) ? 1'b0 : 1'b1;
            end
            default: begin
                csr_read_enable  = 1'b0;
                csr_write_enable = 1'b0;
            end
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            CSRRW, CSRRS, CSRRC:    csr_data_o = first_operand_i;
            default:                csr_data_o = {27'b0, rs1};
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
        if (csr_address_o[11:10] == 2'b11 && csr_write_enable == 1'b1) begin
            exc_ilegal_csr_inst = 1;
        end
        // Check Level privileges
        else if (csr_address_o[9:8] > privilege_i && ((csr_read_enable | csr_write_enable) == 1'b1)) begin
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

    if (RV32 == RV32M || RV32 == RV32ZMMUL) begin : gen_zmmul_on

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

        assign enable_mul = (instruction_operation_i inside {MUL, MULH, MULHU, MULHSU}) && !killed;
        assign mul_low    = (instruction_operation_i == MUL) && !killed;

        mul mul1 (
            .clk              (clk),
            .reset_n          (reset_n),
            .first_operand_i  (first_operand_i),
            .second_operand_i (second_operand_i),
            .signed_mode_i    (signed_mode_mul),
            .enable_i         (enable_mul),
            .mul_low_i        (mul_low),
            .single_cycle_i   (1'b0),
            .hold_o           (hold_mul),
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

    if (RV32 == RV32M) begin : gen_div_on
        logic enable_div;
        logic signed_div;

        assign enable_div = (instruction_operation_i inside {DIV, DIVU, REM, REMU}) && !killed;
        assign signed_div = (instruction_operation_i inside {DIV, REM}) && !killed;

        div div1 (
            .clk              (clk),
            .reset_n          (reset_n),
            .first_operand_i  (first_operand_i),
            .second_operand_i (second_operand_i),
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
            .rs1_in   (first_operand_i),      // Source register 1
            .rs2_in   (second_operand_i),     // Source register 2
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
// Atomic Extension
//////////////////////////////////////////////////////////////////////////////

    logic atomic_result;
    logic hold_atomic;
    logic amo_enable;
    logic lrsc_enable;

    if (AMOEXT != AMO_OFF) begin: atomic_gen_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n)
                atomic_read_value <= '0;
            else
                atomic_read_value <= atomic_read_value_i;
        end

        logic amo_mem_read_enable;
        logic amo_write_reg;
        logic amo_write;
        logic amo_hold;

        if (AMOEXT != AMO_ZALRSC) begin : gen_zaamo_on
            assign amo_enable = !killed && instruction_operation_i inside {AMOSWAP, AMOADD, AMOXOR, AMOAND, AMOOR, AMOMIN, AMOMAX, AMOMINU, AMOMAXU};

            logic amo_enable_stall;
            assign amo_enable_stall = !stall && amo_enable;

            amo atomic_amo (
                .clk                     (clk),
                .reset_n                 (reset_n),
                .en_i                    (amo_enable_stall),
                .atomic_read_o           (amo_mem_read_enable),
                .atomic_write_o          (amo_write),
                .hold_o                  (amo_hold),
                .atomic_write_reg_o      (amo_write_reg)
            );
        end
        else begin : gen_zaamo_off
            assign amo_enable           = 1'b0;
            assign amo_mem_read_enable  = 1'b0;
            assign amo_write_reg        = 1'b0;
            assign amo_write            = 1'b0;
            assign amo_hold             = 1'b0;
        end

        logic lrsc_mem_read_enable;
        logic lrsc_write_reg;
        logic lrsc_write;
        logic lrsc_hold;

        if (AMOEXT != AMO_ZAAMO) begin : gen_zalrsc_on
            assign lrsc_enable = !killed && instruction_operation_i inside {LR, SC};

            logic lrsc_enable_stall;     
            assign lrsc_enable_stall = !stall && lrsc_enable;

            lrsc atomic_lrsc (
                .clk                     (clk),
                .reset_n                 (reset_n),
                .en_i                    (lrsc_enable_stall),
                .instruction_operation_i (instruction_operation_i),
                .lrsc_address            (first_operand_i),
                .lrsc_data               (atomic_read_value),
                .atomic_read_o           (lrsc_mem_read_enable),
                .atomic_write_o          (lrsc_write),
                .hold_o                  (lrsc_hold),
                .atomic_write_reg_o      (lrsc_write_reg),
                .result_o                (atomic_result)
            );
        end
        else begin : gen_zalrsc_off
            assign lrsc_enable          = 1'b0;
            assign lrsc_mem_read_enable = 1'b0;
            assign lrsc_write_reg       = 1'b0;
            assign lrsc_write           = 1'b0;
            assign lrsc_hold            = 1'b0;
            assign atomic_result        = '0;
        end

        assign mem_read_enable_atomic = (amo_mem_read_enable && amo_enable) || (lrsc_mem_read_enable && lrsc_enable);
        assign atomic_write_reg       = (amo_write_reg       && amo_enable) || (lrsc_write_reg       && lrsc_enable);
        assign atomic_write           = (amo_write           && amo_enable) || (lrsc_write           && lrsc_enable);
        assign hold_atomic            = (amo_hold            && amo_enable) || (lrsc_hold            && lrsc_enable);
    end
    else begin: atomic_gen_off
        assign hold_atomic            = 1'b0;
        assign atomic_result          = '0;
        assign atomic_write_reg       = '0;
        assign atomic_write           = '0;
        assign mem_read_enable_atomic = '0;
        assign atomic_read_value      = '0;
        assign amo_enable             = 1'b0;
        assign lrsc_enable            = 1'b0;
    end


//////////////////////////////////////////////////////////////////////////////
// Vector Extension
//////////////////////////////////////////////////////////////////////////////
    logic [31:0] vector_scalar_result;
    logic        vector_wr_en;
    logic        hold_vector;

    if (VEnable) begin : v_gen_on
        iType_e vector_inst;

        assign vector_inst = (killed) ? NOP : instruction_operation_i;
        vectorUnit #(
            .Environment (Environment),
            .VLEN        (VLEN)
        ) vector (
            .clk                    (clk),
            .reset_n                (reset_n),
            .instruction_i          (instruction_i),
            .instruction_operation_i(vector_inst),
            .vector_operation_i     (vector_operation_i),
            .op1_scalar_i           (first_operand_i),
            .op2_scalar_i           (second_operand_i),
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

//////////////////////////////////////////////////////////////////////////////
// Demux
//////////////////////////////////////////////////////////////////////////////

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
            SB,SH,SW,
            BEQ,BNE,
            BLT,BLTU,
            BGE,BGEU:    write_enable = 1'b0;
            VECTOR,
            VLOAD,
            VSTORE:      write_enable = vector_wr_en;
            LR,
            SC:          write_enable = atomic_write_reg;
            default:     write_enable = ~(killed | raise_exception_o);
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Output Registers
//////////////////////////////////////////////////////////////////////////////
    
    assign hold_o = hold_div | hold_mul | hold_vector | hold_atomic;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            write_enable_o          <= 1'b0;
            instruction_operation_o <= NOP;
            result_o                <= '0;
            atomic_write_reg_o      <= 1'b0;
            rd_atomic_o             <= '0;
        end
        else if (!stall) begin
            if (amo_enable) begin
                write_enable_o          <= write_enable;
                instruction_operation_o <= mem_read_enable_atomic ? LW : instruction_operation_i;
                result_o                <= atomic_write ? atomic_read_value : '0;
                atomic_write_reg_o      <= 1'b0;
                rd_atomic_o             <= '0;
            end
            else if (lrsc_enable) begin
                write_enable_o          <= write_enable;
                instruction_operation_o <= mem_read_enable_atomic ? LW : instruction_operation_i;
                result_o                <= (instruction_operation_i == SC) ? {31'b0, atomic_result} : atomic_read_value;
                atomic_write_reg_o      <= atomic_write_reg;
                rd_atomic_o             <= rd;
            end
            else if (!hold_o) begin
                write_enable_o          <= write_enable;
                instruction_operation_o <= instruction_operation_i;
                result_o                <= result;
                atomic_write_reg_o      <= 1'b0;
                rd_atomic_o             <= '0;
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Killed signal generation
//////////////////////////////////////////////////////////////////////////////

    assign killed   = (curr_tag != tag_i) | sys_reset;

    assign killed_o = killed;

//////////////////////////////////////////////////////////////////////////////
// BRANCH CONTROL
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_operation_i)
            JALR:       jump_target_o = {sum_result[31:1], 1'b0};
            JAL:        jump_target_o = sum_result;
            default:    jump_target_o = sum2_result;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            BEQ:        jump = equal;
            BNE:        jump = ~equal;
            BLT:        jump = less_than;
            BLTU:       jump = less_than_unsigned;
            BGE:        jump = greater_equal;
            BGEU:       jump = greater_equal_unsigned;
            JAL, JALR:  jump = 1'b1;
            default:    jump = 1'b0;
        endcase
    end

    assign jump_o = (jump && !killed);

//////////////////////////////////////////////////////////////////////////////
// TAG control based on signals Jump and Killed
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            curr_tag <= '0;
        end
        else if ((jump_o || raise_exception_o || machine_return_o || interrupt_ack_o)) begin
            curr_tag <= curr_tag + 1'b1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Privileged Architecture Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if ((killed) == 1'b0) begin
            if (exc_inst_access_fault_i) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                //exception_code_o  = ILLEGAL_INSTRUCTION;
                exception_code_o  = INSTRUCTION_ACCESS_FAULT;
                // $write("[%0d] EXCEPTION - INSTRUCTION ACCESS FAULT: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else
            if ((exc_ilegal_inst_i || exc_ilegal_csr_inst)) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = ILLEGAL_INSTRUCTION;
                // $write("[%0d] EXCEPTION - ILLEGAL INSTRUCTION: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else if (exc_misaligned_fetch_i) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = INSTRUCTION_ADDRESS_MISALIGNED;
                // $write("[%0d] EXCEPTION - INSTRUCTION ADDRESS MISALIGNED: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else if (instruction_operation_i == ECALL) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = (privilege_i == USER) ? ECALL_FROM_UMODE : ECALL_FROM_MMODE;
                // $write("[%0d] EXCEPTION - ECALL_FROM_MMODE: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else if (instruction_operation_i == EBREAK) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = BREAKPOINT;
                // $write("[%0d] EXCEPTION - EBREAK: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else if (exc_load_access_fault_i == 1'b1 && (mem_write_enable_o != '0 || mem_read_enable_o == 1'b1)) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = LOAD_ACCESS_FAULT;
                // $write("[%0d] EXCEPTION - LOAD ACCESS FAULT: %8h %8h %8h\n", $time, pc_i, instruction_i, mem_address_o);
            end
            else if (instruction_operation_i == MRET) begin
                raise_exception_o = 1'b0;
                machine_return_o  = 1'b1;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = NE;
                // $write("[%0d] MRET: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else if (interrupt_pending_i == 1'b1 && instruction_operation_i != NOP && !hold_o) begin
                raise_exception_o = 1'b0;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b1;
                exception_code_o  = NE;
                // $write("[%0d] Interrupt Acked\n", $time);
            end
            else begin
                raise_exception_o = 1'b0;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = NE;
            end
        end
        else begin
            raise_exception_o = 1'b0;
            machine_return_o  = 1'b0;
            interrupt_ack_o   = 1'b0;
            exception_code_o  = NE;
        end
    end

endmodule
