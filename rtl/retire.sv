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

`include "RS5_pkg.sv"

module retire
    import RS5_pkg::*;
#(
    parameter atomic_e AMOEXT = AMO_A
)
(
    /* Not used without zalrsc */
    /* verilator lint_off UNUSEDSIGNAL */
    input   logic           clk,
    input   logic           reset_n,
    /* verilator lint_on UNUSEDSIGNAL */

    input   iType_e         instruction_operation_i,
    input   logic [31:0]    result_i,
    input   logic [31:0]    mem_data_i,

    output  logic [31:0]    reservation_data_o,
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

            // LW, LR_W
            default: memory_data = mem_data_i;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Assign to Register Bank Write Back
//////////////////////////////////////////////////////////////////////////////

    always_comb begin
        unique case (instruction_operation_i)
            LB,LBU,LH,LHU,LW,LR_W: regbank_data_o = memory_data;
            default:               regbank_data_o = result_i;
        endcase         
    end

////////////////////////////////////////////////////////////////////////////////
// LR/SC registers
////////////////////////////////////////////////////////////////////////////////

    if (AMOEXT inside {AMO_A, AMO_ZALRSC}) begin : gen_zalrsc_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                reservation_data_o <= '0;
            end
            else begin
                unique case (instruction_operation_i)
                    LR_W:    reservation_data_o <= mem_data_i;
                    SC_W:    reservation_data_o <= '0;
                    default: ;
                endcase
            end
        end
    end
    else begin : gen_zalrsc_off
        assign reservation_data_o = '0;
    end

endmodule
