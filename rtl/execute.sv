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

module execute
    import RS5_pkg::*;
#(
    parameter environment_e Environment = ASIC,
    parameter rv32_e        RV32        = RV32I
)
(
    input   logic               clk,
    input   logic               reset,
    input   logic               stall,

    input   logic [31:0]        instruction_i,
    input   logic [31:0]        pc_i,
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   logic [31:0]        third_operand_i,
    input   iType_e             instruction_operation_i,
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

    output  logic [63:0]        mul_result_o, 
    output  logic [63:0]        mulh_result_o, 
    output  logic [63:0]        mulhsu_result_o,


    // AXI signals for load/store
    output logic                           mem_awvalid_o,
    output logic                           mem_arvalid_o,
    output logic                           mem_rready_o,
    input  logic                           mem_awready_i,
    input  logic                           mem_wready_i,
    output logic        [32-1:0] mem_awaddr_o,
    output logic        [32-1:0] mem_araddr_o,
    output logic        [ 32/8-1:0] mem_wstrb_o,
    output logic        [   32-1:0] mem_wdata_o, 
    output logic                           mem_wvalid_o,
    input  logic                           mem_arready_i,
    input  logic                           mem_rvalid_i,
    input  logic                           mem_bvalid_i,
    output logic                           mem_bready_o,
    input logic         [   32-1:0] mem_rdata_i,
    input logic                    [1:0]   mem_bresp_i,
    input logic                    [1:0]   mem_rresp_i,
    output logic                   [2:0]   mem_arprot_o,
    output logic                   [2:0]   mem_awprot_o,
    /////////////////////////////////////////////////////

    //output  logic [31:0]        mem_address_o,
    //output  logic               mem_read_enable_o,
    //output  logic [31:0]        mem_write_data_o,

    output  logic [11:0]        csr_address_o,
    output  logic               csr_read_enable_o,
    input   logic [31:0]        csr_data_read_i,
    output  logic               csr_write_enable_o,
    output  csrOperation_e      csr_operation_o,
    output  logic [31:0]        csr_data_o,

    output  logic               jump_o,
    output  logic [31:0]        jump_target_o,

    input   logic               interrupt_pending_i,
    output  logic               interrupt_ack_o,
    output  logic               machine_return_o,
    output  logic               raise_exception_o,
    output  exceptionCode_e     exception_code_o
);

    logic  [2:0]    curr_tag;
    logic [31:0]    result;
    logic           killed;
    logic           write_enable;
    logic           exc_ilegal_csr_inst;

    logic signed [31:0]  first_operand_signed;
    logic signed [31:0]  second_operand_signed;

    assign first_operand_signed  = first_operand_i;
    assign second_operand_signed = second_operand_i;

    // AXI
    assign mem_bready_o = 1'b1;
    assign mem_arprot_o = 3'b000;  
    assign mem_awprot_o = 3'b000;  

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

    logic           equal;
    logic           less_than;
    logic           less_than_unsigned;
    logic           greater_equal;
    logic           greater_equal_unsigned;
    logic           jump;

    always_comb begin
        unique case (instruction_operation_i)
            SUB:      sum2_opA = first_operand_i;
            default:  sum2_opA = pc_i;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            JAL, JALR:  sum2_opB = 4;
            SUB:        sum2_opB = -second_operand_i;
            default:    sum2_opB = third_operand_i;
        endcase
    end

    always_comb begin
        sum_result              = first_operand_i + second_operand_i;
        sum2_result             = sum2_opA + sum2_opB;
        and_result              = first_operand_i & second_operand_i;
        or_result               = first_operand_i | second_operand_i;
        xor_result              = first_operand_i ^ second_operand_i;
        sll_result              = first_operand_i << second_operand_i[4:0];
        srl_result              = first_operand_i >> second_operand_i[4:0];
        sra_result              = first_operand_signed >>> second_operand_i[4:0];

        equal                   = first_operand_i == second_operand_i;
        less_than               = first_operand_signed < second_operand_signed;
        less_than_unsigned      = first_operand_i < second_operand_i;
        greater_equal           = first_operand_signed >= second_operand_signed;
        greater_equal_unsigned  = first_operand_i >= second_operand_i;
    end

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    assign mem_araddr_o[31:2]  = sum_result[31:2];
    assign mem_araddr_o [1:0]  = '0;
    assign mem_awaddr_o[31:2]  = sum_result[31:2];
    assign mem_awaddr_o [1:0]  = '0;

    logic mem_read_enable;
    assign mem_read_enable    = instruction_operation_i inside {LB, LBU, LH, LHU, LW};
    logic mem_enable;
    assign mem_enable = instruction_operation_i inside {LB, LBU, LH, LHU, LW, SB, SH, SW};

    //logic hold_lsu;

    enum logic[1:0] {LSU_IDLE = 0, LSU_WAIT_READ = 1, LSU_WAIT_WRITE = 2} lsu_state, lsu_next_state;

    always_comb begin
        lsu_next_state = LSU_IDLE;
        //hold_lsu = 1'b0;
        case (lsu_state)
            LSU_IDLE: begin
                if (mem_enable && mem_read_enable && !mem_arready_i) begin
                    lsu_next_state = LSU_WAIT_READ;
                    //hold_lsu = 1'b1;
                end
                else if (mem_enable && !mem_read_enable && (!mem_awready_i || !mem_wready_i)) begin
                    lsu_next_state = LSU_WAIT_WRITE;
                    //hold_lsu = 1'b1;
                end
            end
            LSU_WAIT_READ: begin
                if (mem_arready_i) lsu_next_state = LSU_IDLE;
            end
            LSU_WAIT_WRITE: begin
                if (mem_awready_i || mem_wready_i) lsu_next_state = LSU_IDLE;
            end
            default: lsu_next_state = LSU_IDLE;
        endcase
    end

    always_ff @(posedge clk) begin
        if (reset) begin
            lsu_state <= LSU_IDLE;
        end
        else begin
            lsu_state <= lsu_next_state;
        end
    end

    always_comb begin

        mem_awvalid_o      = 1'b0;
        mem_arvalid_o      = 1'b0;
        mem_wvalid_o       = 1'b0;
        mem_rready_o       = 1'b1;


        if (lsu_state == LSU_WAIT_WRITE) begin
            mem_awvalid_o = 1'b1;
            mem_wvalid_o  = 1'b1;
        end else if (lsu_state == LSU_WAIT_READ) begin
            mem_arvalid_o = 1'b1;
            mem_rready_o = 1'b1;
        end else begin
            if (mem_enable) begin
                if (mem_read_enable) begin
                    mem_arvalid_o = 1'b1;
                    mem_rready_o = 1'b1;
                end
                else begin
                    mem_awvalid_o = 1'b1;
                    mem_wvalid_o  = 1'b1;
                end
            end
        end

    end

    always_comb begin
        unique case (instruction_operation_i)
            SB:         mem_wdata_o = {4{third_operand_i[7:0]}};
            SH:         mem_wdata_o = {2{third_operand_i[15:0]}};
            default:    mem_wdata_o = third_operand_i;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            SB: unique case (sum_result[1:0])
                    2'b11:   mem_wstrb_o = 4'b1000;
                    2'b10:   mem_wstrb_o = 4'b0100;
                    2'b01:   mem_wstrb_o = 4'b0010;
                    default: mem_wstrb_o = 4'b0001;
                endcase
            SH:              mem_wstrb_o = (sum_result[1]) 
                                                ? 4'b1100 
                                                : 4'b0011;
            SW:              mem_wstrb_o = 4'b1111;
            default:         mem_wstrb_o = 4'b0000;
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
// Multiplication and Division Operations
//////////////////////////////////////////////////////////////////////////////
    
    logic [31:0] div_result;
    logic [31:0] divu_result;
    logic [31:0] rem_result;
    logic [31:0] remu_result;

    if (RV32 == RV32M || RV32 == RV32ZMMUL) begin
        muldiv #(
            .Environment    (Environment),
            .RV32           (RV32)
        ) muldiv1 (
            .clk                        (clk),
            .reset                      (reset),
            .first_operand_i            (first_operand_i),
            .second_operand_i           (second_operand_i),
            .instruction_operation_i    (instruction_operation_i),
            .hold_o                     (hold_o),
            .div_result_o               (div_result),
            .divu_result_o              (divu_result),
            .rem_result_o               (rem_result),
            .remu_result_o              (remu_result),
            .mul_result_o               (mul_result_o),
            .mulh_result_o              (mulh_result_o),
            .mulhsu_result_o            (mulhsu_result_o)
        );
    end 
    else begin
        assign hold_o           = '0;
        assign mul_result_o     = '0;
        assign mulh_result_o    = '0;
        assign mulhsu_result_o  = '0;
        assign div_result       = '0;
        assign divu_result      = '0;
        assign rem_result       = '0;
        assign remu_result      = '0;
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
            DIV:                    result = div_result;
            DIVU:                   result = divu_result;
            REM:                    result = rem_result;
            REMU:                   result = remu_result;
            default:                result = sum_result;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            SB,SH,SW,
            BEQ,BNE,
            BLT,BLTU,
            BGE,BGEU:  write_enable = 1'b0;
            default:   write_enable = !killed;
        endcase
    end 

//////////////////////////////////////////////////////////////////////////////
// Output Registers
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (
            stall == 1'b0 & hold_o == 1'b0
        ) begin
            write_enable_o          <= write_enable;
            instruction_operation_o <= instruction_operation_i;
            result_o                <= result;             
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Killed signal generation
//////////////////////////////////////////////////////////////////////////////

    assign killed   = (curr_tag != tag_i);

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

    always_ff @(posedge clk) begin
        if (reset == 1'b1) begin
            curr_tag <= 0;
        end
        else if ((jump_o | raise_exception_o | machine_return_o | interrupt_ack_o) == 1'b1) begin
            curr_tag <= curr_tag + 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Privileged Architecture Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if ((reset | killed) == 1'b0) begin
            if (exc_inst_access_fault_i == 1'b1) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                //exception_code_o  = ILLEGAL_INSTRUCTION;
                exception_code_o  = INSTRUCTION_ACCESS_FAULT;
                // $write("[%0d] EXCEPTION - INSTRUCTION ACCESS FAULT: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else
            if ((exc_ilegal_inst_i | exc_ilegal_csr_inst) == 1'b1) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = ILLEGAL_INSTRUCTION;
                // $write("[%0d] EXCEPTION - ILLEGAL INSTRUCTION: %8h %8h\n", $time, pc_i, instruction_i);
            end 
            else if (exc_misaligned_fetch_i == 1'b1) begin
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
                exception_code_o  = ECALL_FROM_MMODE;
                // $write("[%0d] EXCEPTION - ECALL_FROM_MMODE: %8h %8h\n", $time, pc_i, instruction_i);
            end 
            else if (instruction_operation_i == EBREAK) begin
                raise_exception_o = 1'b1;
                machine_return_o  = 1'b0;
                interrupt_ack_o   = 1'b0;
                exception_code_o  = BREAKPOINT;
                // $write("[%0d] EXCEPTION - EBREAK: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else if (exc_load_access_fault_i == 1'b1 && (mem_wstrb_o != '0 || mem_read_enable == 1'b1)) begin
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
            else if (interrupt_pending_i == 1'b1 && instruction_operation_i != NOP) begin
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
