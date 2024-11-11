module lrsc
(
    input  logic        clk,
    input  logic        reset_n,
    input  logic        stall,

    input  logic        enable_i,
    input  logic        eq_result_i,
    input  logic [31:0] rs1_data_i,
    input  logic [31:0] data_i,
    input  logic [31:0] reservation_addr_i,
    input  logic [31:0] reservation_data_i,


    output logic        hold_o,
    output logic        mem_read_enable_o,
    output logic        mem_write_enable_o,
    output logic        result_o,
    output logic [31:0] cmp_opA_o,
    output logic [31:0] cmp_opB_o
);

    typedef enum logic [3:0] {
        LOAD     = 4'b0001,
        CMP_ADDR = 4'b0010,
        CMP_DATA = 4'b0100,
        STORE    = 4'b1000
    } state_t;

    state_t current_state;
    state_t next_state;

    always_comb begin
        unique case (current_state)
            LOAD:     next_state = enable_i    ? CMP_ADDR : LOAD;
            CMP_ADDR: next_state = eq_result_i ? CMP_DATA : STORE;
            CMP_DATA: next_state = STORE;
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
            cmp_opA_o <= '0;
        end
        else if (!stall) begin
            unique case (current_state)
                LOAD:     cmp_opA_o <= rs1_data_i;
                CMP_ADDR: cmp_opA_o <= data_i;
                default: ;
            endcase
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            cmp_opB_o <= '0;
        end
        else if (!stall) begin
            unique case (current_state)
                LOAD:     cmp_opB_o <= reservation_addr_i;
                CMP_ADDR: cmp_opB_o <= reservation_data_i;
                default: ;
            endcase
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            result_o <= '0;
        else if (!stall)
            result_o <= !eq_result_i;
    end

    assign hold_o             =  enable_i && (current_state != STORE);
    assign mem_read_enable_o  =  enable_i && (current_state ==  LOAD);
    assign mem_write_enable_o = !result_o && (current_state == STORE);

endmodule
