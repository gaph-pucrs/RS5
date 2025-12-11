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
    parameter int      SEW              = 8,
    parameter int      VLEN             = 64,
    parameter int      ELEMENTS_PER_REG = 8,
    parameter red_op_e RED_OP           = RED_SUM,
    parameter bit      MULTI_CYCLE      = 1'b0
) (
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic                                 clk,
    input  logic                                 reset_n,
    /* verilator lint_on UNUSEDSIGNAL  */
    input  logic [ELEMENTS_PER_REG-1:0][SEW-1:0] first_operand,
    input  logic [SEW-1:0]                       second_operand,

    input  logic [$bits(VLEN)-1:0]               vl,
    input  logic                                 vm,
    input  logic [7:0][ELEMENTS_PER_REG-1:0]     mask,
    input  logic [3:0]                           cycle_count_r,

    input  logic [9:0]                           cycle,

    output logic [SEW-1:0]                       result_o
);

    localparam STAGES = $clog2(ELEMENTS_PER_REG);

    // *********************************
    //  SINGLE-CYCLE
    // *********************************
    if (MULTI_CYCLE == 1'b0) begin : multi_cycle_reduction_off
        logic [ELEMENTS_PER_REG-1:0][SEW-1:0] result [STAGES:0];

        assign result_o = {result[STAGES][0]};

        always_comb begin
            // First Level
            for (int i = 0; i < ELEMENTS_PER_REG; i++) begin
                if (i == 0) begin
                    if ((vm || mask[cycle_count_r][0]) && i < vl) begin
                        if (RED_OP == RED_MAX) begin
                            result[0][i] = ($signed(first_operand[0]) > $signed(second_operand))
                                            ? first_operand[0]
                                            : second_operand;
                        end
                        else if (RED_OP == RED_MAXU) begin
                            result[0][i] = (first_operand[0] > second_operand)
                                            ? first_operand[0]
                                            : second_operand;
                        end
                        else if (RED_OP == RED_MIN) begin
                            result[0][i] = ($signed(first_operand[0]) > $signed(second_operand))
                                            ? second_operand
                                            : first_operand[0];
                        end
                        else if (RED_OP == RED_MINU) begin
                            result[0][i] = (first_operand[0] > second_operand)
                                            ? second_operand
                                            : first_operand[0];
                        end
                        else if (RED_OP == RED_AND) begin
                            result[0][i] = first_operand[0] & second_operand;
                        end
                        else if (RED_OP == RED_OR) begin
                            result[0][i] = first_operand[0] | second_operand;
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
                    if ((vm || mask[cycle_count_r][i]) && i < vl) begin
                        result[0][i] = first_operand[i];
                    end
                    else begin
                        if (RED_OP == RED_MIN) begin
                            result[0][i][SEW-2:0] =  '1;
                            result[0][i][SEW-1]   = 1'b0;
                        end
                        else if (RED_OP == RED_MAX) begin
                            result[0][i][SEW-2:0] =  '0;
                            result[0][i][SEW-1]   = 1'b1;
                        end
                        else if (RED_OP inside {RED_AND, RED_MINU}) begin
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
                    if (RED_OP == RED_MAX) begin
                        result[i+1][j] = ($signed(result[i][2*j]) > $signed(result[i][2*j+1]))
                                            ? result[i][2*j]
                                            : result[i][2*j+1];
                    end
                    else if (RED_OP == RED_MAXU) begin
                        result[i+1][j] = (result[i][2*j] > result[i][2*j+1])
                                            ? result[i][2*j]
                                            : result[i][2*j+1];
                    end
                    else if (RED_OP == RED_MIN) begin
                        result[i+1][j] = ($signed(result[i][2*j]) > $signed(result[i][2*j+1]))
                                            ? result[i][2*j+1]
                                            : result[i][2*j];
                    end
                    else if (RED_OP == RED_MINU) begin
                        result[i+1][j] = (result[i][2*j] > result[i][2*j+1])
                                            ? result[i][2*j+1]
                                            : result[i][2*j];
                    end
                    else if (RED_OP == RED_AND) begin
                        result[i+1][j] = result[i][2*j] & result[i][2*j+1];
                    end
                    else if (RED_OP == RED_OR) begin
                        result[i+1][j] = result[i][2*j] | result[i][2*j+1];
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
    end
    // *********************************
    //  MULTI-CYCLE
    // *********************************
    else begin  : multi_cycle_reduction_on

        logic [(ELEMENTS_PER_REG  )-1:0][SEW-1:0] operand;
        logic [(ELEMENTS_PER_REG/2)-1:0][SEW-1:0] result;

        assign result_o = {operand[0]};

        always_comb begin
            for (int j = 0, int k = 0; k < (ELEMENTS_PER_REG/2); j+=2, k++) begin
                if (RED_OP == RED_MAX) begin
                    result[k] = ($signed(operand[j]) > $signed(operand[j+1]))
                                        ? operand[j]
                                        : operand[j+1];
                end
                else if (RED_OP == RED_MAXU) begin
                    result[k] = (operand[j] > operand[j+1])
                                        ? operand[j]
                                        : operand[j+1];
                end
                else if (RED_OP == RED_MIN) begin
                    result[k] = ($signed(operand[j]) > $signed(operand[j+1]))
                                        ? operand[j+1]
                                        : operand[j];
                end
                else if (RED_OP == RED_MINU) begin
                    result[k] = (operand[j] > operand[j+1])
                                        ? operand[j+1]
                                        : operand[j];
                end
                else if (RED_OP == RED_AND) begin
                    result[k] = operand[j] & operand[j+1];
                end
                else if (RED_OP == RED_OR) begin
                    result[k] = operand[j] | operand[j+1];
                end
                else if (RED_OP == RED_XOR) begin
                    result[k] = operand[j] ^ operand[j+1];
                end
                else begin
                    result[k] = operand[j] + operand[j+1];
                end
            end
        end

        always_ff @(posedge clk or negedge reset_n) begin
            if (!reset_n) begin
                operand <= '{default: '0};
            end
            else if (cycle == '0) begin // First Level
                for (int i = 0; i < ELEMENTS_PER_REG; i++) begin
                    if (i == 0) begin
                        if ((vm || mask[cycle_count_r][0]) && i < vl) begin
                            if (RED_OP == RED_MAX) begin
                               operand[i] <= ($signed(first_operand[0]) > $signed(second_operand))
                                                ? first_operand[0]
                                                : second_operand;
                            end
                            else if (RED_OP == RED_MAXU) begin
                               operand[i] <= (first_operand[0] > second_operand)
                                                ? first_operand[0]
                                                : second_operand;
                            end
                            else if (RED_OP == RED_MIN) begin
                               operand[i] <= ($signed(first_operand[0]) > $signed(second_operand))
                                                ? second_operand
                                                : first_operand[0];
                            end
                            else if (RED_OP == RED_MINU) begin
                               operand[i] <= (first_operand[0] > second_operand)
                                                ? second_operand
                                                : first_operand[0];
                            end
                            else if (RED_OP == RED_AND) begin
                               operand[i] <= first_operand[0] & second_operand;
                            end
                            else if (RED_OP == RED_OR) begin
                               operand[i] <= first_operand[0] | second_operand;
                            end
                            else if (RED_OP == RED_XOR) begin
                               operand[i] <= first_operand[0] ^ second_operand;
                            end
                            else begin
                               operand[i] <= first_operand[0] + second_operand;
                            end
                        end
                        else begin
                           operand[i] <= second_operand;
                        end
                    end
                    else begin
                        if ((vm || mask[cycle_count_r][i]) && i < vl) begin
                           operand[i] <= first_operand[i];
                        end
                        else begin
                            if (RED_OP == RED_MIN) begin
                               operand[i][SEW-2:0] <=  '1;
                               operand[i][SEW-1]   <= 1'b0;
                            end
                            else if (RED_OP == RED_MAX) begin
                               operand[i][SEW-2:0] <=  '0;
                               operand[i][SEW-1]   <= 1'b1;
                            end
                            else if (RED_OP inside {RED_AND, RED_MINU}) begin
                               operand[i] <= '1;
                            end
                            else begin
                               operand[i] <= '0;
                            end
                        end
                    end
                end
            end
            else begin
                for (int i = 0; i < ELEMENTS_PER_REG; i++) begin
                    if (i < (ELEMENTS_PER_REG/2)) begin
                        operand[i] <= result[i];
                    end
                    else begin
                        if (RED_OP == RED_MIN) begin
                            operand[i][SEW-2:0] <=  '1;
                            operand[i][SEW-1]   <= 1'b0;
                        end
                        else if (RED_OP == RED_MAX) begin
                            operand[i][SEW-2:0] <=  '0;
                            operand[i][SEW-1]   <= 1'b1;
                        end
                        else if (RED_OP inside {RED_AND, RED_MINU}) begin
                            operand[i] <= '1;
                        end
                        else begin
                            operand[i] <= '0;
                        end
                    end
                end
            end
        end
    end

endmodule
/* verilator lint_on WIDTHEXPAND */
/* verilator lint_on WIDTHTRUNC  */
