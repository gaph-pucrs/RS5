/*!\file execute.sv
 * PUC-RS5 VERSION - 1.0.0 - Public Release
 *
 * Distribution:  March 2023
 *
 * Willian Nunes   <willian.nunes@edu.pucrs.br>
 * Marcos Sartori  <marcos.sartori@acad.pucrs.br>
 * Ney calazans    <ney.calazans@pucrs.br>
 *
 * Research group: GAPH-PUCRS  <>
 *
 * \brief
 * Execute Unit is the third stage of the processor core.
 *
 * \detailed
 * Execute Unit is the third stage of the PUC-RS5 processor core. At the
 * entry it implements a dispatcher that assigns the operands to the
 * execution units that are: 
 * 1) Adder 2) Branch 3) Bypass 4) Logic 5) Memory 6) Shift 7) CSR access. 
 * Each module is defined in a separeted file. At the other end it has a 
 * demultiplexer that collects the result only from the given module and 
 * pass it to the retirement stage.
 */

module execute
    import my_pkg::*;
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
`ifdef XOSVM
    input   logic               exc_inst_access_fault_i,
    input   logic               exc_load_access_fault_i,
`endif

    output  logic               killed_o,
    output  logic               write_enable_o,
    output  iType_e             instruction_operation_o,
    output  logic [31:0]        result_o,

    output  logic [31:0]        mem_address_o,
    output  logic               mem_read_enable_o,
    output  logic  [3:0]        mem_write_enable_o,
    output  logic [31:0]        mem_write_data_o,

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
        sra_result              = $signed(first_operand_i) >>> second_operand_i[4:0];

        equal                   = first_operand_i == second_operand_i;
        less_than               = $signed(first_operand_i) < $signed(second_operand_i);
        less_than_unsigned      = $unsigned(first_operand_i) < $unsigned(second_operand_i);
        greater_equal           = $signed(first_operand_i) >= $signed(second_operand_i);
        greater_equal_unsigned  = $unsigned(first_operand_i) >= $unsigned(second_operand_i);
    end

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    assign mem_address_o[31:2]  = sum_result[31:2];
    assign mem_address_o [1:0]  = '0;
    assign mem_read_enable_o    = instruction_operation_i inside {LB, LBU, LH, LHU, LW};

    always_comb begin
        unique case (instruction_operation_i)
            SB:         mem_write_data_o = {4{third_operand_i[7:0]}};
            SH:         mem_write_data_o = {2{third_operand_i[15:0]}};
            default:    mem_write_data_o = third_operand_i;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            SB: unique case (sum_result[1:0])
                    2'b11:   mem_write_enable_o = 4'b1000;
                    2'b10:   mem_write_enable_o = 4'b0100;
                    2'b01:   mem_write_enable_o = 4'b0010;
                    default: mem_write_enable_o = 4'b0001;
                endcase
            SH:              mem_write_enable_o = (sum_result[1]) 
                                                ? 4'b1100 
                                                : 4'b0011;
            SW:              mem_write_enable_o = 4'b1111;
            default:         mem_write_enable_o = 4'b0000;
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
                csr_write_enable = 1;
            end
            CSRRS, CSRRC, CSRRSI, CSRRCI: begin
                csr_read_enable  = 1;
                csr_write_enable = (rs1 == '0) ? 1'b0 : 1'b1;
            end
            default: begin
                csr_read_enable  = 0;
                csr_write_enable = 0;
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
        if (csr_address_o[11:10] == 2'b11 && csr_write_enable) begin
            exc_ilegal_csr_inst = 1;
        end
        // Check Level privileges
        else if (csr_address_o[9:8] > privilege_i && (csr_read_enable || csr_write_enable)) begin
            exc_ilegal_csr_inst = 1;
        end
        // No exception is raised
        else begin
            exc_ilegal_csr_inst = 0;
        end
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
        if (!stall) begin
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
        if (reset) begin
            curr_tag <= 0;
        end
        else if (jump_o | raise_exception_o | machine_return_o | interrupt_ack_o) begin
            curr_tag <= curr_tag + 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Privileged Architecture Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (!killed & !reset) begin
        `ifdef XOSVM
            if (exc_inst_access_fault_i) begin
                raise_exception_o = 1;
                exception_code_o  = ILLEGAL_INSTRUCTION;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                exception_code_o  = INSTRUCTION_ACCESS_FAULT;
                $write("[%0d] EXCEPTION - INSTRUCTION ACCESS FAULT: %8h %8h\n", $time, pc_i, instruction_i);
            end
            else
        `endif
            if (exc_ilegal_inst_i | exc_ilegal_csr_inst) begin
                raise_exception_o = 1;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                exception_code_o  = ILLEGAL_INSTRUCTION;
                $write("[%0d] EXCEPTION - ILLEGAL INSTRUCTION: %8h %8h\n", $time, pc_i, instruction_i);
            end 
            else if (exc_misaligned_fetch_i) begin
                raise_exception_o = 1;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                exception_code_o  = INSTRUCTION_ADDRESS_MISALIGNED;
                $write("[%0d] EXCEPTION - INSTRUCTION ADDRESS MISALIGNED: %8h %8h\n", $time, pc_i, instruction_i);
            end 
            else if (instruction_operation_i == ECALL) begin
                raise_exception_o = 1;
                exception_code_o  = ECALL_FROM_MMODE;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                $write("[%0d] EXCEPTION - ECALL_FROM_MMODE: %8h %8h\n", $time, pc_i, instruction_i);
            end 
            else if (instruction_operation_i == EBREAK) begin
                raise_exception_o = 1;
                exception_code_o  = BREAKPOINT;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                $write("[%0d] EXCEPTION - EBREAK: %8h %8h\n", $time, pc_i, instruction_i);
            end
        `ifdef XOSVM
            else if (exc_load_access_fault_i) begin
                raise_exception_o = 1;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                exception_code_o  = LOAD_ACCESS_FAULT;
                $write("[%0d] EXCEPTION - LOAD ACCESS FAULT: %8h %8h\n", $time, pc_i, instruction_i);
            end 
        `endif
            else if (instruction_operation_i == MRET) begin
                raise_exception_o = 0;
                exception_code_o  = NE;
                machine_return_o  = 1;
                interrupt_ack_o   = 0;
                $write("[%0d] MRET: %8h %8h\n", $time, pc_i, instruction_i);
            end 
            else if (interrupt_pending_i) begin
                raise_exception_o = 0;
                exception_code_o  = NE;
                machine_return_o  = 0;
                interrupt_ack_o   = 1;
                $write("[%0d] Interrupt Acked\n", $time);
            end
            else begin
                raise_exception_o = 0;
                exception_code_o  = NE;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
            end
        end
        else begin
            raise_exception_o = 0;
            exception_code_o  = NE;
            machine_return_o  = 0;
            interrupt_ack_o   = 0;
        end
    end

endmodule
