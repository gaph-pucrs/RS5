module amo
(
    input  logic        clk,
    input  logic        reset_n,
    input  logic        stall,

    input  logic        enable_i,
    input  logic [31:0] data_i,
    input  logic [31:0] amo_result_i,

    output logic        hold_o,
    output logic        write_enable_o,
    output logic        mem_read_enable_o,
    output logic        mem_write_enable_o,
    output logic [31:0] opA_o
);

    typedef enum logic [3:0] {
        LOAD     = 4'b0001,
        WAIT     = 4'b0010,
        MODIFY   = 4'b0100,
        STORE    = 4'b1000
    } state_t;

    state_t current_state;
    state_t next_state;

    always_comb begin
        unique case (current_state)
            LOAD:     next_state = enable_i ? WAIT : LOAD;
            WAIT:     next_state = MODIFY;
            MODIFY:   next_state = STORE;
            default:  next_state = LOAD; /* STORE */
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            current_state <= LOAD;
        else if (!stall)
            current_state <= next_state;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            opA_o <= '0;
        end
        else if (!stall) begin
            unique case (current_state)
                WAIT:    opA_o <= data_i;
                MODIFY:  opA_o <= amo_result_i;
                default: ;
            endcase
        end
    end

    assign hold_o             = (current_state !=  STORE) && enable_i;
    assign write_enable_o     = (current_state ==   LOAD) && enable_i;
    assign mem_read_enable_o  = (current_state ==   LOAD) && enable_i;
    assign mem_write_enable_o = (current_state ==  STORE);

endmodule
