/*!\file retire.sv
 * RS5 VERSION - 1.0.0 - Public Release
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
 * Retire is the last stage of the RS5 processor core.
 *
 * \detailed
 * Retire is the last stage of the RS5 processor core and is reponsible for closing the loops.
 * First compares the instruction tag with the internal tag, if they do not match then the 
 * instruction is killed and no operation is performed, otherwise it sends the data received 
 * for the given output, they are: 
 * 1) Register bank - data and write enable
 * 2) Branch - jump target
 * 3) Memory write - memory signals (Data, address and operation enable)
 * 4) Manage Exceptions and Interrupts and Privilege Switch.
 */

module retire
    import RS5_pkg::*;
(
    input   logic           write_enable_i,
    input   iType_e         instruction_operation_i,
    input   logic [31:0]    result_i,
    input   logic [31:0]    mem_data_i,

    output  logic           regbank_write_enable_o,
    output  logic [31:0]    regbank_data_o
);

    logic [31:0]    memory_data;

//////////////////////////////////////////////////////////////////////////////
// Memory Signal Generation
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_operation_i)
            LB, LBU: case (result_i[1:0])
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

            LH, LHU: case (result_i[1])
                        1'b1:   begin 
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
                    
            default: memory_data = mem_data_i;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Assign to Register Bank Write Back
//////////////////////////////////////////////////////////////////////////////

    assign regbank_data_o = (instruction_operation_i inside {LB,LBU,LH,LHU,LW}) 
                            ? memory_data 
                            : result_i;
    
    assign regbank_write_enable_o = write_enable_i;

endmodule
