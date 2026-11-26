/*!\file vectorReductionTree.sv
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
module vectorReductionTree
    import RS5_pkg::*;
#(
    parameter int      SEW                   = 8,
    parameter int      VLEN                  = 64,
    parameter int      ELEMENTS_PER_REG      = 8,
    parameter red_op_e RED_OP                = RED_SUM
) (
    input  logic [ELEMENTS_PER_REG-1:0][SEW-1:0] first_operand,
    input  logic [SEW-1:0]                       second_operand,

    input  logic [$bits(VLEN)-1:0]               vl,
    input  logic                                 vm,
    /* Mask of the elements of this pass */
    input  logic [ELEMENTS_PER_REG-1:0]          mask,

    output logic [SEW-1:0]                       result_o
);

    localparam STAGES = $clog2(ELEMENTS_PER_REG);

    // *********************************
    //  SINGLE-CYCLE
    // *********************************
    logic [ELEMENTS_PER_REG-1:0][SEW-1:0] result [STAGES:0];

    assign result_o = {result[STAGES][0]};

    always_comb begin
        // First Level
        for (int i = 0; i < ELEMENTS_PER_REG; i++) begin
            if (i == 0) begin
                if ((vm || mask[0]) && i < vl) begin
                    if (RED_OP == RED_MINU) begin
                        result[0][i] = (first_operand[0] > second_operand)
                                        ? second_operand
                                        : first_operand[0];
                    end
                    else if (RED_OP == RED_AND) begin
                        result[0][i] = first_operand[0] & second_operand;
                    end
                    else if (RED_OP == RED_XOR) begin
                        result[0][i] = first_operand[0] ^ second_operand;
                    end
                    else begin
                        result[0][i] = first_operand[0] + second_operand;
                    end
                end
                else begin
                    result[0][i] = second_operand;
                end
            end
            else begin
                if ((vm || mask[i]) && i < vl) begin
                    result[0][i] = first_operand[i];
                end
                else begin
                    if (RED_OP inside {RED_AND, RED_MINU}) begin
                        result[0][i] = '1;
                    end
                    else begin
                        result[0][i] = '0;
                    end
                end
            end
        end

        // Other Levels
        for (int i = 0; i < STAGES; i++) begin
            for (int j = 0; j < ELEMENTS_PER_REG/(2**(i+1)); j++) begin
                if (RED_OP == RED_MINU) begin
                    result[i+1][j] = (result[i][2*j] > result[i][2*j+1])
                                        ? result[i][2*j+1]
                                        : result[i][2*j];
                end
                else if (RED_OP == RED_AND) begin
                    result[i+1][j] = result[i][2*j] & result[i][2*j+1];
                end
                else if (RED_OP == RED_XOR) begin
                    result[i+1][j] = result[i][2*j] ^ result[i][2*j+1];
                end
                else begin
                    result[i+1][j] = result[i][2*j] + result[i][2*j+1];
                end
            end
        end
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
