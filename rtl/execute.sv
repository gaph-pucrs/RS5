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
    input   logic [31:0]        pc_i,
    input   logic [31:0]        first_operand_i,
    input   logic [31:0]        second_operand_i,
    input   logic [31:0]        third_operand_i,
    input   iType_e             instruction_operation_i,
    input   logic  [2:0]        tag_i,

`ifdef BRANCH_PREDICTION
    input   logic               predicted_branch_i,
    output  logic               predicted_branch_o,
`endif

    output  iType_e             instruction_operation_o,
    output  logic [31:0]        instruction_o,
    output  logic [31:0]        pc_o,
    output  logic [31:0]        result_o [1:0],
    output  logic  [2:0]        tag_o,
    output  logic               jump_o,
    output  logic               write_enable_o,
    output  logic [31:0]        mem_read_address_o,
    output  logic  [3:0]        mem_write_enable_o,
    output  logic               mem_read_o,

    output  logic               csr_read_enable_o,
    output  logic               csr_write_enable_o,
    output  csrOperation_e      csr_operation_o,
    output  logic [11:0]        csr_address_o,
    output  logic [31:0]        csr_data_o,
    input   logic [31:0]        csr_data_read_i,

    input   privilegeLevel_e    privilege_i,

`ifdef XOSVM
    input   logic               exc_inst_access_fault_i,
    output  logic               exc_inst_access_fault_o,
`endif
    input   logic               exc_ilegal_inst_i,
    input   logic               exc_misaligned_fetch_i,
    output  logic               exc_ilegal_inst_o,
    output  logic               exc_misaligned_fetch_o
);
    
    logic        jump_int;
    logic        write_enable_regbank_branch_unit, write_enable_regbank_memory_unit;
    logic        csr_exception;
    logic  [3:0] mem_write_enable_int;
    logic [31:0] results_int [7:0];

    operationType_e execution_unit_operation;
    executionUnit_e execution_unit_selector;

    assign execution_unit_selector  = executionUnit_e'(instruction_operation_i[5:3]);
    assign execution_unit_operation = operationType_e'(instruction_operation_i[2:0]);

//////////////////////////////////////////////////////////////////////////////
// Instantiation of execution units
//////////////////////////////////////////////////////////////////////////////

    adderUnit adder1 (
        .first_operand_i    (first_operand_i),
        .second_operand_i   (second_operand_i),
        .operation_i        (execution_unit_operation),
        .result_o           (results_int[0])
    );

    logicUnit logical1 (
        .first_operand_i    (first_operand_i),
        .second_operand_i   (second_operand_i),
        .operation_i        (execution_unit_operation),
        .result_o           (results_int[1])
    );
    
    shiftUnit shift1 (
        .first_operand_i    (first_operand_i),
        .second_operand_i   (second_operand_i[4:0]),
        .operation_i        (execution_unit_operation),
        .result_o           (results_int[2])
    );
    
    branchUnit branch1 (
        .first_operand_i    (first_operand_i),
        .second_operand_i   (second_operand_i),
        .offset_i           (third_operand_i),
        .pc_i               (pc_i),
        .operation_i        (execution_unit_operation),
        .result_o           (results_int[4]),
        .result_jal_o       (results_int[3]),
        .jump_o             (jump_int),
        .write_enable_o     (write_enable_regbank_branch_unit)
    );

    LSUnit memory1 (
        .first_operand_i     (first_operand_i),
        .second_operand_i    (second_operand_i),
        .data_i              (third_operand_i),
        .operation_i         (execution_unit_operation),
        .enable_i            (execution_unit_selector == MEMORY_UNIT),
        .read_address_o      (mem_read_address_o),
        .read_o              (mem_read_o),
        .write_address_o     (results_int[7]),
        .write_data_o        (results_int[6]),
        .write_enable_o      (mem_write_enable_int),
        .write_enable_regBank(write_enable_regbank_memory_unit)
    );
    
    csrUnit CSRaccess (
        .first_operand_i    (first_operand_i),
        .instruction_i      (instruction_i),
        .operation_i        (execution_unit_operation),
        .privilege_i        (privilege_i),
        .read_enable_o      (csr_read_enable_o),
        .write_enable_o     (csr_write_enable_o),
        .operation_o        (csr_operation_o),
        .address_o          (csr_address_o),
        .data_o             (csr_data_o),
        .exception_o        (csr_exception)
    );
    
    assign results_int[5] = second_operand_i; // BYPASS

//////////////////////////////////////////////////////////////////////////////
// Demux
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin 
        if (!stall) begin
            if (execution_unit_selector == ADDER_UNIT) begin
                result_o[0] <= results_int[0];
            end
            else if (execution_unit_selector == LOGICAL_UNIT) begin
                result_o[0] <= results_int[1];
            end
            else if (execution_unit_selector == SHIFTER_UNIT) begin
                result_o[0] <= results_int[2];
            end
            else if (execution_unit_selector == BRANCH_UNIT) begin
                result_o[0] <= results_int[3];
            end
            else if (execution_unit_selector == MEMORY_UNIT) begin
                result_o[0] <= results_int[6];
            end
            else if (execution_unit_selector == CSR_UNIT) begin
                result_o[0] <= csr_data_read_i;
            end
            else begin
                result_o[0] <= results_int[5];
            end
        end
    end

    always_ff @(posedge clk) begin
        if (!stall) begin
            if (execution_unit_selector == BRANCH_UNIT) begin
                result_o[1] <= results_int[4];
            end
            else if (execution_unit_selector == MEMORY_UNIT) begin
                result_o[1] <= results_int[7];
            end
            else begin 
                result_o[1] <= '0;
            end
        end
    end  
    
    always_ff @(posedge clk) begin
        if (!stall) begin
            if (execution_unit_selector == BRANCH_UNIT) begin
                jump_o <= jump_int;
            end
            else begin
                jump_o <= '0;
            end
        end
    end  

    always_ff @(posedge clk) begin
        if (!stall) begin
            if (execution_unit_selector == MEMORY_UNIT) begin
                mem_write_enable_o <= mem_write_enable_int;
            end
            else begin
                mem_write_enable_o <= '0;
            end
        end
    end  

    always_ff @(posedge clk) begin
        if (!stall) begin
            if (execution_unit_selector == BRANCH_UNIT) begin
                write_enable_o <= write_enable_regbank_branch_unit;
            end
            else if (execution_unit_selector == MEMORY_UNIT) begin
                write_enable_o <= write_enable_regbank_memory_unit;
            end
            else begin
                write_enable_o <= 1;
            end
        end
    end 

    logic exc_ilegal_csr_inst;
    assign  exc_ilegal_csr_inst = csr_exception == 1 && execution_unit_selector == CSR_UNIT;

    always_ff @(posedge clk) begin
        if (!stall) begin
            tag_o                   <= tag_i;
            instruction_operation_o <= instruction_operation_i;
            instruction_o           <= instruction_i;
            pc_o                    <= pc_i;
            exc_ilegal_inst_o       <= exc_ilegal_inst_i | exc_ilegal_csr_inst;
            exc_misaligned_fetch_o  <= exc_misaligned_fetch_i;
        `ifdef XOSVM
            exc_inst_access_fault_o <= exc_inst_access_fault_i;
        `endif
        `ifdef BRANCH_PREDICTION
            predicted_branch_o      <= predicted_branch_i;
        `endif
        end
    end

endmodule
