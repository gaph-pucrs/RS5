/*!\file retire.sv
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
 * Retire is the last stage of the RS5 processor core.
 *
 * \detailed
 * Retire is the last stage of the RS5 processor core and is reponsible for closing the loops.
 * It performs the write-back on the register bank. It also receives the data read from memory
 * and process it based on instruction format then it decides which data should be sent to the
 * register bank, either the data from memory or the data from execute unit.
 * 
 */

module retire
    import RS5_pkg::*;
(
    input   iType_e         instruction_operation_i,
    input   logic [31:0]    result_i,
`ifdef HARDWARE_MULTIPLICATION
    input   logic [63:0]    mul_result_i,
/* verilator lint_off UNUSEDSIGNAL */ 
    input   logic [63:0]    mulh_result_i, 
    input   logic [63:0]    mulhsu_result_i,
/* verilator lint_on UNUSEDSIGNAL */
`endif
    input   logic [31:0]    mem_data_i,

    output  logic [31:0]    regbank_data_o
);

    logic [31:0]    memory_data;

//////////////////////////////////////////////////////////////////////////////
// Memory Signal Generation
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_operation_i)
            LB: begin
                case (result_i[1:0])
                    2'b11: begin 
                        memory_data[31:8] = {24{mem_data_i[31]}};
                        memory_data[7:0]  = mem_data_i[31:24]; 
                    end
                    2'b10: begin 
                        memory_data[31:8] = {24{mem_data_i[23]}};
                        memory_data[7:0]  = mem_data_i[23:16]; 
                    end
                    2'b01: begin 
                        memory_data[31:8] = {24{mem_data_i[15]}};
                        memory_data[7:0]  = mem_data_i[15:8];
                    end
                    default: begin 
                        memory_data[31:8] = {24{mem_data_i[7]}};
                        memory_data[7:0]  = mem_data_i[7:0]; 
                    end
                endcase
            end
            
            LBU: begin
                memory_data[31:8] = '0;
                case (result_i[1:0])
                    2'b11:   memory_data[7:0]  = mem_data_i[31:24]; 
                    2'b10:   memory_data[7:0]  = mem_data_i[23:16]; 
                    2'b01:   memory_data[7:0]  = mem_data_i[15:8];
                    default: memory_data[7:0]  = mem_data_i[7:0]; 
                endcase
            end

            LH: begin
                case (result_i[1])
                    1'b1: begin 
                        memory_data[31:16] = {16{mem_data_i[31]}};
                        memory_data[15:0]  = mem_data_i[31:16]; 
                    end
                    default: begin  
                        memory_data[31:16] = {16{mem_data_i[15]}};
                        memory_data[15:0]  = mem_data_i[15:0]; 
                    end
                endcase
            end

            LHU: begin
                memory_data[31:16] = '0; 
                case (result_i[1])
                    1'b1:    memory_data[15:0] = mem_data_i[31:16]; 
                    default: memory_data[15:0] = mem_data_i[15:0]; 
                endcase
            end

            default: memory_data = mem_data_i;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Assign to Register Bank Write Back
//////////////////////////////////////////////////////////////////////////////

`ifdef HARDWARE_MULTIPLICATION
    always_comb begin
        unique case (instruction_operation_i)
            LB,LBU,LH,LHU,LW:   regbank_data_o = memory_data;
            MUL:                regbank_data_o = mul_result_i[31:0]; 
            MULHU:              regbank_data_o = mul_result_i[63:32]; 
            MULH:               regbank_data_o = mulh_result_i[63:32]; 
            MULHSU:             regbank_data_o = mulhsu_result_i[63:32]; 
            default:            regbank_data_o = result_i;
        endcase         
    end
`else
    assign regbank_data_o = (instruction_operation_i inside {LB,LBU,LH,LHU,LW}) 
                            ? memory_data 
                            : result_i;
`endif

endmodule
