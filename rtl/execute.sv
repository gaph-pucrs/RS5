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
    
    logic           jump;
    logic           csr_exception;
    logic  [3:0]    mem_write_enable;
    logic [31:0]    mem_write_data;
    logic [31:0]    result_alu;

    executionUnit_e execution_unit_selector;

    assign execution_unit_selector  = executionUnit_e'(instruction_operation_i[5:3]);

//////////////////////////////////////////////////////////////////////////////
// Instantiation of ALU
//////////////////////////////////////////////////////////////////////////////

    ALU alu1 (
        .opA_i      (first_operand_i),
        .opB_i      (second_operand_i),
        .opC_i      (third_operand_i),
        .opD_i      (pc_i),
        .operation_i(instruction_operation_i),
        .result_o   (result_alu),
        .jump_o     (jump)
    );

//////////////////////////////////////////////////////////////////////////////
// Load/Store signals
//////////////////////////////////////////////////////////////////////////////

    assign mem_read_address_o = result_alu;
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
        if (instruction_operation_i == SB) begin
            unique case (result_alu[1:0])
                2'b11:   mem_write_enable = 4'b1000;
                2'b10:   mem_write_enable = 4'b0100;
                2'b01:   mem_write_enable = 4'b0010;
                default: mem_write_enable = 4'b0001;
            endcase
        end
        else if (instruction_operation_i == SH) begin
            mem_write_enable = (result_alu[1]) 
                                ? 4'b1100 
                                : 4'b0011;
        end 
        else if (instruction_operation_i == SW) begin
            mem_write_enable = 4'b1111;
        end
        else begin
            mem_write_enable = 4'b0;
        end
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
// Demux and Outputs
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin 
        if (!stall) begin
            if (execution_unit_selector inside {ADDER_UNIT, LOGICAL_UNIT, SHIFTER_UNIT, MEMORY_UNIT}) begin
                result_o[0] <= result_alu;
            end
            else if (execution_unit_selector == BRANCH_UNIT) begin
                result_o[0] <= pc_i + 4;
            end
            else if (execution_unit_selector == CSR_UNIT) begin
                result_o[0] <= csr_data_read_i;
            end
            else begin
                result_o[0] <= second_operand_i;
            end
        end
    end

    always_ff @(posedge clk) begin
        if (!stall) begin
            if (execution_unit_selector == MEMORY_UNIT) begin
                result_o[1] <= mem_write_data;
            end
            else begin
                result_o[1] <= result_alu;
            end
        end
    end 

    always_ff @(posedge clk) begin
        if (!stall) begin
            if (instruction_operation_i inside {SB, SH, SW, BEQ, BNE, BLT, BLTU, BGE, BGEU}) begin
                write_enable_o <= 1'b0;
            end
            else begin
                write_enable_o <= 1'b1;
            end
        end
    end  

    always_ff @(posedge clk) begin
        if (!stall) begin
            tag_o                   <= tag_i;
            instruction_operation_o <= instruction_operation_i;
            instruction_o           <= instruction_i;
            jump_o                  <= jump;
            mem_write_enable_o      <= mem_write_enable;
            pc_o                    <= pc_i;
            exception_o             <= exception_i | csr_exception;
        `ifdef BRANCH_PREDICTION
            predicted_branch_o      <= predicted_branch_i;
        `endif
        end
    end

endmodule
