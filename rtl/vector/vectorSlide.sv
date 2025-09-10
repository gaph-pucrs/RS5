/*!\file vectorSlide.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 */

`include "../RS5_pkg.sv"

/* verilator lint_off WIDTHEXPAND */
/* verilator lint_off WIDTHTRUNC */
module vectorSlide
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64
) (
    input  logic                        clk,
    input  logic                        reset_n,

    input  iTypeVector_e                vector_operation_i,
    input  logic [VLEN-1:0]             first_operand,
    input  logic [31:0]                 second_operand,
    input  logic [31:0]                 scalar_operand,
    input  logic [3:0]                  cycle_count,
    input  vew_e                        vsew,
    input  vlmul_e                      vlmul,
    input  logic[$bits(VLEN)-1:0]       vl,
    input  logic[$bits(VLEN)-1:0]       vl_next,

    output logic [VLEN-1:0]             result_o
);

    logic [VLEN-1:0] result_slide1up;
    logic [VLEN-1:0] result_slide1down;

    // *********************************
    // Slide Down
    // *********************************
    always_comb begin
        unique case (vsew)
            EW8: begin
                for (int i = 0; i < (VLEN/8); i++) begin
                    if (i < (vl-1)) begin
                        result_slide1down[(8*i)+:8] = first_operand[(8*(i+1))+:8];
                    end
                    else if (i == (vl-1)) begin // last element
                        if ( vl_next == 0
                         || (vlmul == LMUL_1 && cycle_count == 1)
                         || (vlmul == LMUL_2 && cycle_count == 2)
                         || (vlmul == LMUL_4 && cycle_count == 4)
                         || (vlmul == LMUL_8 && cycle_count == 8)
                         ) begin
                            result_slide1down[(8*i)+:8] = scalar_operand[7:0];
                         end
                         else begin
                            result_slide1down[(8*i)+:8] = second_operand[7:0];
                         end
                    end
                    else begin // tail
                        result_slide1down[(8*i)+:8] = first_operand[(8*i)+:8];
                    end
                end
            end
            EW16: begin
                for (int i = 0; i < (VLEN/16); i++) begin
                    if (i < (vl-1)) begin
                        result_slide1down[(16*i)+:16] = first_operand[(16*(i+1))+:16];
                    end
                    else if (i == (vl-1)) begin // last element
                        if ( vl_next == 0
                         || (vlmul == LMUL_1 && cycle_count == 1)
                         || (vlmul == LMUL_2 && cycle_count == 2)
                         || (vlmul == LMUL_4 && cycle_count == 4)
                         || (vlmul == LMUL_8 && cycle_count == 8)) begin
                            result_slide1down[(16*i)+:16] = scalar_operand[15:0];
                         end
                         else begin
                            result_slide1down[(16*i)+:16] = second_operand[15:0];
                         end
                    end
                    else begin // tail
                        result_slide1down[(16*i)+:16] = first_operand[(16*i)+:16];
                    end
                end
            end
            default: begin
                for (int i = 0; i < (VLEN/32); i++) begin
                    if (i < (vl-1)) begin
                        result_slide1down[(32*i)+:32] = first_operand[(32*(i+1))+:32];
                    end
                    else if (i == (vl-1)) begin // last element
                        if ( vl_next == 0
                         || (vlmul == LMUL_1 && cycle_count == 1)
                         || (vlmul == LMUL_2 && cycle_count == 2)
                         || (vlmul == LMUL_4 && cycle_count == 4)
                         || (vlmul == LMUL_8 && cycle_count == 8)) begin
                            result_slide1down[(32*i)+:32] = scalar_operand;
                         end
                         else begin
                            result_slide1down[(32*i)+:32] = second_operand[31:0];
                         end
                    end
                    else begin // tail
                        result_slide1down[(32*i)+:32] = first_operand[(32*i)+:32];
                    end
                end
            end
        endcase
    end

    // *********************************
    // Slide Up
    // *********************************
    logic [31:0] last_operand_r;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            last_operand_r <= '0;
        else
            last_operand_r <= first_operand[VLEN-1-:32];
    end

    always_comb begin
        unique case (vsew)
            EW8: begin
                for (int i = 0; i < (VLEN/8); i++) begin
                    if (i == 0) begin // first element
                        if (cycle_count == 1) begin
                            result_slide1up[(8*i)+:8] = scalar_operand[7:0];
                        end
                        else begin
                            result_slide1up[(8*i)+:8] = last_operand_r[7:0];
                        end
                    end
                    else if (i < vl) begin
                        result_slide1up[(8*i)+:8] = first_operand[(8*(i-1))+:8];
                    end
                    else begin // tail
                        result_slide1up[(8*i)+:8] = first_operand[(8*i)+:8];
                    end
                end
            end
            EW16: begin
                for (int i = 0; i < (VLEN/16); i++) begin
                    if (i == 0) begin // first element
                        if (cycle_count == 1) begin
                            result_slide1up[(16*i)+:16] = scalar_operand[15:0];
                        end
                        else begin
                            result_slide1up[(16*i)+:16] = last_operand_r[15:0];
                        end
                    end
                    else if (i < vl) begin
                        result_slide1up[(16*i)+:16] = first_operand[(16*(i-1))+:16];
                    end
                    else begin // tail
                        result_slide1up[(16*i)+:16] = first_operand[(16*i)+:16];
                    end
                end
            end
            default: begin
                for (int i = 0; i < (VLEN/32); i++) begin
                    if (i == 0) begin // first element
                        if (cycle_count == 1) begin
                            result_slide1up[(32*i)+:32] = scalar_operand[31:0];
                        end
                        else begin
                            result_slide1up[(32*i)+:32] = last_operand_r[31:0];
                        end
                    end
                    else if (i < vl) begin
                        result_slide1up[(32*i)+:32] = first_operand[(32*(i-1))+:32];
                    end
                    else begin // tail
                        result_slide1up[(32*i)+:32] = first_operand[(32*i)+:32];
                    end
                end
            end
        endcase
    end

    // *********************************
    // Result Demux
    // *********************************
    always_ff @(posedge clk) begin
        if (vector_operation_i == VSLIDE1DOWN)
            result_o <= result_slide1down;
        else
            result_o <= result_slide1up;
    end

endmodule