/*!\file retire.sv
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
 * Retire is the last stage of the PUC-RS5 processor core.
 *
 * \detailed
 * Retire is the last stage of the PUC-RS5 processor core and is reponsible for closing the loops.
 * First compares the instruction tag with the internal tag, if they do not match then the 
 * instruction is killed and no operation is performed, otherwise it sends the data received 
 * for the given output, they are: 
 * 1) Register bank - data and write enable
 * 2) Branch - jump target
 * 3) Memory write - memory signals (Data, address and operation enable)
 * 4) Manage Exceptions and Interrupts and Privilege Switch.
 */

module retire
    import my_pkg::*;
(
    input   logic           clk,
    input   logic           reset,
    
    input   logic [31:0]    instruction_i,
    input   logic [31:0]    pc_i,
    input   logic [31:0]    results_i [1:0],            // Results array
    input   logic [2:0]     tag_i,                      // Instruction tag to be compared with retire tag
    input   logic [3:0]     mem_write_enable_i,         // Write enable memory
    input   logic           write_enable_i,             // Write enable from Execute(based on instruction_i type)
    input   logic           jump_i,                     // Jump signal from branch unit 
    input   iType_e         instruction_operation_i,
    input   logic           exception_i,

`ifdef BRANCH_PREDICTION
    input   logic           predicted_branch_i,
`endif

    output  logic           regbank_write_enable_o,     // Write Enable to Register Bank
    output  logic [31:0]    regbank_data_o,             // WriteBack data to Register Bank
    output  logic [31:0]    jump_target_o,              // Branch target to fetch Unit
    output  logic           jump_o,                     // Jump signal to Fetch Unit
    output  logic           killed_o,

    output  logic [31:0]    mem_write_address_o,        // Memory mem_write_enable_o address
    output  logic [3:0]     mem_write_enable_o,         // Memory mem_write_enable_o enable
    output  logic [31:0]    mem_data_o,                 // Memory data to be written
    input   logic [31:0]    mem_data_i,                 // Data from memory

    output  logic [2:0]     current_retire_tag_o,
    output  exceptionCode_e exception_code_o,
    output  logic           raise_exception_o,
    output  logic           machine_return_o,
    output  logic           interrupt_ack_o,
    input   logic           interrupt_pending_i
);

    logic [31:0] memory_data;
    logic [2:0] curr_tag;
    logic killed;
    executionUnit_e execution_unit_selection;

    assign current_retire_tag_o = curr_tag;
    assign execution_unit_selection = executionUnit_e'(instruction_operation_i[5:3]);

//////////////////////////////////////////////////////////////////////////////
// Assign to Register Bank Write Back
//////////////////////////////////////////////////////////////////////////////

    assign regbank_data_o = (execution_unit_selection == MEMORY_UNIT) 
                            ? memory_data 
                            : results_i[0];

//////////////////////////////////////////////////////////////////////////////
// Killed signal generation
//////////////////////////////////////////////////////////////////////////////
    assign killed_o = killed;
    
    always_comb begin
        if (curr_tag != tag_i) begin
            killed = 1;
        end
        else begin
            killed = 0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// TAG control based on signals Jump and Killed
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk) begin
        if (reset) begin
            curr_tag <= 0;
        end
        else if (!killed && (jump_o || raise_exception_o || machine_return_o || interrupt_ack_o)) begin
            curr_tag <= curr_tag + 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// RegBank Write Enable Generation
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (killed) begin
            regbank_write_enable_o = 0;
        end 
        else begin
            regbank_write_enable_o = write_enable_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// PC Flow control signal generation
//////////////////////////////////////////////////////////////////////////////
`ifdef BRANCH_PREDICTION
    always_comb begin
        // If should have jumped and predicted not jump then jump
        if (jump_i && !predicted_branch_i && !killed) begin
            jump_o          = 1;
            jump_target_o   = results_i[1];
        end
        // If should not have jumped and predicted jump then return
        else if (!jump_i && predicted_branch_i && !killed) begin
            jump_o          = 1;
            jump_target_o   = pc_i;
        end
        // Predicted Right or not a Jump
        else begin
            jump_o          = 0;
            jump_target_o   = '0;
        end
    end
`else
    always_comb begin
        if (jump_i && !killed) begin
            jump_o        = 1;
            jump_target_o = results_i[1];
        end 
        else begin
            jump_o        = '0;
            jump_target_o = '0;
        end
    end
`endif

//////////////////////////////////////////////////////////////////////////////
// Memory Signal Generation
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (instruction_operation_i == LB || instruction_operation_i == LBU) begin
            case (results_i[1][1:0])
                2'b11:   begin 
                            memory_data[7:0]  = mem_data_i[31:24]; 
                            memory_data[31:8] = (mem_data_i[31] && instruction_operation_i == LB) 
                                                ? '1 
                                                : '0;
                        end
                2'b10:   begin 
                            memory_data[7:0]  = mem_data_i[23:16]; 
                            memory_data[31:8] = (mem_data_i[23] && instruction_operation_i == LB) 
                                                ? '1 
                                                : '0; 
                        end
                2'b01:   begin 
                            memory_data[7:0]  = mem_data_i[15:8];
                            memory_data[31:8] = (mem_data_i[15] && instruction_operation_i == LB) 
                                                ? '1 
                                                : '0; 
                        end
                default: begin 
                            memory_data[7:0]  = mem_data_i[7:0]; 
                            memory_data[31:8] = (mem_data_i[7] && instruction_operation_i == LB) 
                                                ? '1 
                                                : '0; 
                        end
            endcase
        end
        else if (instruction_operation_i == LH || instruction_operation_i == LHU) begin
            case (results_i[1][1])
                1'b1:    begin 
                            memory_data[15:0]  = mem_data_i[31:16]; 
                            memory_data[31:16] = (mem_data_i[31] && instruction_operation_i == LH) 
                                                ? '1 
                                                : '0; 
                        end
                default: begin  
                            memory_data[15:0]  = mem_data_i[15:0]; 
                            memory_data[31:16] = (mem_data_i[15] && instruction_operation_i == LH) 
                                                ? '1 
                                                : '0; 
                        end
            endcase

        end 
        else begin
            memory_data = mem_data_i;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Memory mem_write_enable_o control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (mem_write_enable_i != '0 && !killed) begin
            mem_write_enable_o  = mem_write_enable_i;
            mem_write_address_o = results_i[1];
            mem_data_o          = results_i[0];
        end 
        else begin
            mem_write_enable_o  = '0;
            mem_write_address_o = '0;
            mem_data_o          = '0;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Privileged Architecture Control
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        if (!killed) begin
            if (exception_i) begin
                raise_exception_o = 1;
                exception_code_o  = ILLEGAL_INSTRUCTION;
                machine_return_o  = 0;
                interrupt_ack_o   = 0;
                $write("[%0d] EXCEPTION - ILLEGAL INSTRUCTION: %8h %8h\n", $time, pc_i, instruction_i);
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
