`include "RS5_pkg.sv"

module lrsc 
    import RS5_pkg::*;
(
    input  logic         clk,
    input  logic         reset_n,

    input  logic         en_i,
    input  iType_e       instruction_operation_i,

    input  logic [31:0]  lrsc_data,
    input  logic [31:0]  lrsc_address,

    output logic         atomic_read_o,
    output logic         atomic_write_o,
    output logic         hold_o,

    output logic         atomic_write_reg_o,

    output logic         result_o
);

    logic [31:0] reservation_set_address;
    logic [31:0] reservation_set_content;

    typedef enum logic[3:0] {
        IDLE  = 4'b0001, 
        WAIT  = 4'b0010,
        SC_OP = 4'b0100,
        LR_OP = 4'b1000
    } state_t;

    state_t current_state;
    state_t next_state;

    always_comb begin
        unique case (current_state)
            IDLE: 
                next_state = en_i ? WAIT : IDLE;
            WAIT:
                next_state = en_i ? ((instruction_operation_i == SC) ? SC_OP : LR_OP) : WAIT;
            default: 
                next_state = en_i ? IDLE : current_state;
        endcase
    end

    assign hold_o = !(current_state inside {SC_OP, LR_OP});

    logic reservation_success;
    assign reservation_success = (reservation_set_address == lrsc_address) && (reservation_set_content == lrsc_data);

    assign atomic_read_o      = (current_state inside {IDLE, WAIT});
    assign atomic_write_reg_o = (current_state inside {SC_OP, LR_OP});
    assign result_o           = (current_state == SC_OP) && !reservation_success;
    assign atomic_write_o     = (current_state == SC_OP) &&  reservation_success;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            reservation_set_address <= '0;
            reservation_set_content <= '0;
        end
        else begin
            case (current_state)
                LR_OP: begin
                    reservation_set_address <= lrsc_address;
                    reservation_set_content <= lrsc_data;
                end
                SC_OP: begin
                    reservation_set_address <= '0;
                    reservation_set_content <= '0;
                end
                default: ;
            endcase
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            current_state <= IDLE;
        else
            current_state <= next_state;
    end

endmodule
