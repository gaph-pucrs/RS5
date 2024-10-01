`include "RS5_pkg.sv"

module atomic 
    import RS5_pkg::*;
(
    input  logic         clk,
    input  logic         reset_n,
    //input  iType_e       instruction_operation_i,
    input  iTypeAtomic_e atomic_operation_i,

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

    enum logic[2:0] {IDLE, WAIT_AMO, WAIT_LRSC, WRITE_AMO, LRSC} atomic_state, atomic_next_state;

    always_comb begin
        unique case (atomic_state)
            IDLE: begin
                if (atomic_operation_i != ANOP && atomic_operation_i != LR && atomic_operation_i != SC) begin
                    atomic_next_state = WAIT_AMO;
                end
                else if(atomic_operation_i != ANOP) begin
                    atomic_next_state = WAIT_LRSC;
                end 
                else begin
                    atomic_next_state = IDLE;
                end
            end
            WAIT_AMO:
                atomic_next_state = WRITE_AMO;
            WAIT_LRSC:
                atomic_next_state = LRSC;
            default: 
                atomic_next_state = IDLE;
            // WRITE_AMO:
            //     atomic_next_state = IDLE;
            // LRSC:
            //     atomic_next_state = IDLE;
        endcase
    end

    always_comb begin
        atomic_read_o  = 1'b0;
        atomic_write_o = 1'b0;
        hold_o         = 1'b0;
        atomic_write_reg_o  = 1'b0;
        result_o = '0;

        unique case (atomic_state)
            IDLE: begin
                if (atomic_operation_i != ANOP) begin
                    atomic_read_o = 1'b1;
                    hold_o        = 1'b1;
                end
            end
            WAIT_AMO: begin
                hold_o        = 1'b1;
                atomic_read_o = 1'b1;
            end
            WAIT_LRSC: begin
                hold_o        = 1'b1;
                atomic_read_o = 1'b1;
            end
            WRITE_AMO: begin
                atomic_write_o = 1'b1;
                atomic_write_reg_o = 1'b1;
            end
            LRSC: begin
                atomic_write_reg_o = 1'b1;
                if (atomic_operation_i == SC) begin
                    if (reservation_set_address == lrsc_address && reservation_set_content == lrsc_data) begin
                        result_o = 0;
                        atomic_write_o = 1'b1;
                    end 
                    else begin
                        result_o = 1;
                    end
                end
            end
            default: ;
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            reservation_set_address <= '0;
            reservation_set_content <= '0;
        end
        else begin
            if(atomic_state == LRSC) begin
                if (atomic_operation_i == LR) begin
                    reservation_set_address <= lrsc_address;
                    reservation_set_content <= lrsc_data;
                end
                else if (atomic_operation_i == SC) begin
                    reservation_set_address <= '0;
                    reservation_set_content <= '0;
                end
            end
        end
    end


    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            atomic_state <= IDLE;
        end
        else begin
            atomic_state <= atomic_next_state;
        end
    end




endmodule
