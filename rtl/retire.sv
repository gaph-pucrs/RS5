/*!\file retire.sv
 * RS5 VERSION - 1.1.0 - Pipeline Simplified and Core Renamed
 *
 * Distribution:  July 2023
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
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

    /* Registered input from mem_access */
    input   wb_ctrl_t       ctrl_i,
    input   logic [31:0]    result_i,

    /* Memory interface */
    input   logic [31:0]    mem_data_i,

    /* Regbank interface */
    output  logic [31:0]    regbank_data_o,

    /* Registered output to execute */
    output  logic [31:0]    reservation_data_o
);

    logic [31:0]    memory_data;

//////////////////////////////////////////////////////////////////////////////
// Memory Signal Generation
//////////////////////////////////////////////////////////////////////////////

    logic [7:0]  byte_data;
    logic        byte_sign;
    logic [15:0] half_data;
    logic        half_sign;

    always_comb begin
        case (result_i[1:0])
            2'b11:   byte_data = mem_data_i[31:24];
            2'b10:   byte_data = mem_data_i[23:16];
            2'b01:   byte_data = mem_data_i[15:8];
            default: byte_data = mem_data_i[7:0];
        endcase
        byte_sign = ctrl_i.is_unsigned ? 1'b0 : byte_data[7];

        half_data = result_i[1] ? mem_data_i[31:16] : mem_data_i[15:0];
        half_sign = ctrl_i.is_unsigned ? 1'b0 : half_data[15];
    end

    always_comb begin
        unique case (1'b1)
            ctrl_i.is_byte: memory_data = {{24{byte_sign}}, byte_data};
            ctrl_i.is_half: memory_data = {{16{half_sign}}, half_data};
            default:        memory_data = mem_data_i;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Assign to Register Bank Write Back
//////////////////////////////////////////////////////////////////////////////

    assign regbank_data_o = (ctrl_i.is_load || ctrl_i.is_lr) ? memory_data : result_i;

////////////////////////////////////////////////////////////////////////////////
// LR/SC registers
////////////////////////////////////////////////////////////////////////////////

    if (AMOEXT inside {AMO_A, AMO_ZALRSC}) begin : gen_zalrsc_on
        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                reservation_data_o <= '0;
            end
            else if (ctrl_i.rd_we) begin    /* Avoid writing on MMU exceptions */
                unique case (1'b1)
                    ctrl_i.is_lr: reservation_data_o <= mem_data_i;
                    ctrl_i.is_sc: reservation_data_o <= '0;
                    default: ;
                endcase
            end
        end
    end
    else begin : gen_zalrsc_off
        assign reservation_data_o = '0;
    end

endmodule
