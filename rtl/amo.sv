`include "RS5_pkg.sv"

module amo 
    import RS5_pkg::*;
(
    input  logic         clk,
    input  logic         reset_n,

    input  logic         en_i,

    output logic         atomic_read_o,
    output logic         atomic_write_o,
    output logic         hold_o,

    output logic         atomic_write_reg_o
);

    typedef enum logic[2:0] {
        IDLE    = 3'b001, 
        WAIT    = 3'b010, 
        A_WRITE = 3'b100
    } state_t;
    
    state_t current_state;
    state_t next_state;

    always_comb begin
        unique case (current_state)
            IDLE:    next_state = en_i ? WAIT    : IDLE;
            WAIT:    next_state = en_i ? A_WRITE : WAIT;
            default: next_state = en_i ? IDLE    : current_state;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            current_state <= IDLE;
        else
            current_state <= next_state;
    end

    assign atomic_read_o      = (current_state inside {IDLE, WAIT});
    assign hold_o             = (current_state inside {IDLE, WAIT});
    assign atomic_write_o     = (current_state == A_WRITE);
    assign atomic_write_reg_o = (current_state == A_WRITE);

endmodule
