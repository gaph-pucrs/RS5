`include "RS5_pkg.sv"

module atomic 
    import RS5_pkg::*;
(
    input  logic         clk,
    input  logic         reset_n,
    input  iType_e       instruction_operation_i,

    output logic         atomic_read_o,
    output logic         atomic_write_o,
    output logic         hold_o
);


    enum logic[1:0] {LOAD_RS1, WRITE_RS1} atomic_state, atomic_next_state;

    always_comb begin
        unique case (atomic_state)
            LOAD_RS1:
                atomic_next_state = instruction_operation_i == ATOMIC_AMO ? WRITE_RS1 : LOAD_RS1;
            WRITE_RS1:
                atomic_next_state = LOAD_RS1;
        endcase
    end

    always_comb begin
        atomic_read_o  = 1'b0;
        atomic_write_o = 1'b0;
        hold_o         = 1'b0;

        unique case (atomic_state)
            LOAD_RS1: begin
                if (instruction_operation_i == ATOMIC_AMO) begin
                    atomic_read_o = 1'b1;
                    hold_o        = 1'b1;
                end
            end
            WRITE_RS1: begin
                atomic_write_o = 1'b1;
            end
        endcase
    end


    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            atomic_state <= LOAD_RS1;
        end
        else begin
            atomic_state <= atomic_next_state;
        end
    end




endmodule
