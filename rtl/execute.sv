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
    input   logic               stall,

    input   logic [31:0]        instruction_i,
    input   logic [31:0]        pc_i,               // Operand from Operand Fetch stage
    input   logic [31:0]        first_operand_i,    //              ||
    input   logic [31:0]        second_operand_i,   //              ||
    input   logic [31:0]        third_operand_i,    //              ||
    input   iType_e             instruction_operation_i,
    input   logic [2:0]         tag_i,              // Instruction tag

`ifdef BRANCH_PREDICTION
    input   logic               predicted_branch_i,
    output  logic               predicted_branch_o,
`endif

    output  iType_e             instruction_operation_o,
    output  logic [31:0]        instruction_o,
    output  logic [31:0]        pc_o,
    output  logic [31:0]        result_o [1:0],     // Results array
    output  logic [2:0]         tag_o,              // Instruction tag
    output  logic               jump_o,             // Signal that indicates a branch taken
    output  logic               write_enable_o,     // Write enable to regbank
    output  logic [3:0]         mem_write_enable_o, // Signal that indicates the write memory operation to retire

    output  logic [31:0]        mem_read_address_o, // Memory Read Address
    output  logic               mem_read_o,         // Allows memory read

    output  logic               csr_read_enable_o,
    output  logic               csr_write_enable_o,
    output  csrOperation_e      csr_operation_o,
    output  logic [11:0]        csr_address_o,
    output  logic [31:0]        csr_data_o,
    input   logic [31:0]        csr_data_read_i,

    input   privilegeLevel_e    privilege_i,

    input   logic               exception_i,
    output  logic               exception_o
);
    
    logic [31:0]    result [1:0];
    logic           write_enable;
    logic  [3:0]    mem_write_enable;
    logic [31:0]    mem_write_data;
    logic           csr_exception;

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

    always_comb begin
        unique case (instruction_operation_i)
            BEQ:            jump = equal;
            BNE:            jump = ~equal;
            BLT:            jump = less_than;
            BLTU:           jump = less_than_unsigned;
            BGE:            jump = greater_equal;
            BGEU:           jump = greater_equal_unsigned;
            JAL, JALR:      jump = 1'b1;
            default:        jump = 1'b0;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    assign mem_read_address_o = sum_result;
    assign mem_read_o         = instruction_operation_i inside {LB, LBU, LH, LHU, LW};

    always_comb begin
        unique case (instruction_operation_i)
            SB:         mem_write_data = {4{third_operand_i[7:0]}};
            SH:         mem_write_data = {2{third_operand_i[15:0]}};
            SW:         mem_write_data = third_operand_i;
            default:    mem_write_data = '0;
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

    assign csr_read_enable_o = csr_read_enable & !csr_exception;
    assign csr_write_enable_o = csr_write_enable & !csr_exception;

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
            csr_exception = 1;
        end
        // Check Level privileges
        else if (csr_address_o[9:8] < privilege_i && (csr_read_enable || csr_write_enable)) begin
            csr_exception = 1;
        end
        // No exception is raised
        else begin
            csr_exception = 0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Demux
//////////////////////////////////////////////////////////////////////////////

    always_comb begin 
        unique case (instruction_operation_i)
            CSRRW, CSRRS, CSRRC,
            CSRRWI,CSRRSI,CSRRCI:   result[0] = csr_data_read_i;
            JAL,JALR,SUB:           result[0] = sum2_result;
            SLT:                    result[0] = {31'b0, less_than};
            SLTU:                   result[0] = {31'b0, less_than_unsigned};
            XOR:                    result[0] = xor_result;
            OR:                     result[0] = or_result;
            AND:                    result[0] = and_result;
            SLL:                    result[0] = sll_result;
            SRL:                    result[0] = srl_result;
            SRA:                    result[0] = sra_result;
            LUI:                    result[0] = second_operand_i;
            default:                result[0] = sum_result;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            SB,SH,SW:   result[1] = mem_write_data;
            JALR:       result[1] = {sum_result[31:1], 1'b0};
            JAL:        result[1] = sum_result;
            default:    result[1] = sum2_result;
        endcase
    end

    always_comb begin
        unique case (instruction_operation_i)
            SB,SH,SW,
            BEQ,BNE,
            BLT,BLTU,
            BGE,BGEU:  write_enable = 1'b0;
            default:   write_enable = 1'b1;
        endcase
    end 

//////////////////////////////////////////////////////////////////////////////
// Output Registers
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (!stall) begin
            pc_o                    <= pc_i;
            instruction_o           <= instruction_i;
            instruction_operation_o <= instruction_operation_i;
            result_o                <= result;             
            jump_o                  <= jump;
            write_enable_o          <= write_enable;
            mem_write_enable_o      <= mem_write_enable;
            tag_o                   <= tag_i;
            exception_o             <= exception_i | csr_exception;
        `ifdef BRANCH_PREDICTION
            predicted_branch_o      <= predicted_branch_i;
        `endif
        end
    end

endmodule
