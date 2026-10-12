/**
 * RingBuffer
 * @file RingBuffer.sv
 *
 * @author Angelo Elias Dal Zotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 *
 * @date October 2023
 *
 * @brief RingBuffer module
 */

module RingBuffer
#(
    parameter DATA_SIZE = 32,
    parameter BUFFER_SIZE = 8,            /* Power of 2 */
    parameter ALMOST_FULL_THRESHOLD  = 1, /* 0 for disabled */
    parameter ALMOST_EMPTY_THRESHOLD = 1  /* 0 for disabled */
)
(
    input  logic                     clk_i,
    input  logic                     rst_ni,
    input  logic                     buf_rst_i,

    input  logic                     rx_i,
    output logic                     rx_ack_o,
    input  logic [(DATA_SIZE - 1):0] data_i,

    output logic                     tx_o,
    input  logic                     tx_ack_i,
    output logic [(DATA_SIZE - 1):0] data_o,

    output logic                     almost_full_o,
    output logic                     almost_empty_o
);

    typedef logic [($clog2(BUFFER_SIZE + 1) - 1):0]                     buf_cnt_t;
    typedef logic [((BUFFER_SIZE > 1 ? $clog2(BUFFER_SIZE) : 1) - 1):0] buf_ptr_t; 

    logic full;
    logic empty;

    buf_ptr_t head;
    buf_ptr_t tail;

    buf_ptr_t next_head;
    buf_ptr_t next_tail;

    logic [(DATA_SIZE - 1):0] buffer [(BUFFER_SIZE - 1):0];

    assign rx_ack_o = !full;
    assign tx_o     = !empty;
    assign data_o   = buffer[tail];

    assign next_head = (BUFFER_SIZE > 1 ? (head + 1'b1) : '0);
    assign next_tail = (BUFFER_SIZE > 1 ? (tail + 1'b1) : '0);

    logic can_receive;
    assign can_receive = rx_i && !full;

    logic can_send;
    assign can_send = tx_ack_i && !empty;

    /* Buffer write control */
    always_ff @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni)
            ;
        else if (can_receive)
            buffer[head] <= data_i;
    end

    /* Head control */
    always_ff @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
            head <= '0;
        end
        else begin
            if (buf_rst_i)
                head <= '0;
            else if (can_receive)
                head <= next_head;
        end
    end

    /* Tail control */
    always_ff @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
            tail <= '0;
        end
        else begin
            if (buf_rst_i)
                tail <= '0;
            else if (can_send)
                tail <= next_tail;
        end
    end

    /* Input control: sets full when next_head == tail on an insertion */
    /* Output control: sets empty when next_tail == head on a removal */
    always_ff @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
            full  <= 1'b0;
            empty <= 1'b1;
        end
        else begin
            if (buf_rst_i) begin
                full  <= 1'b0;
                empty <= 1'b1;
            end
            else begin
                if (can_receive) begin
                    if (!can_send)
                        full <= next_head == tail;

                    empty <= 1'b0;
                end

                if (can_send) begin
                    if (!can_receive)
                        empty <= next_tail == head;

                    full <= 1'b0;
                end
            end
        end
    end
    
    if (ALMOST_FULL_THRESHOLD > 0 || ALMOST_EMPTY_THRESHOLD > 0) begin : gen_entry_count_on
        buf_cnt_t entry_count;
        always_ff @(posedge clk_i or negedge rst_ni) begin
            if (!rst_ni) begin
                entry_count <= '0;
            end
            else begin
                if (buf_rst_i) begin
                    entry_count <= '0;
                end
                else begin
                    case ({can_receive, can_send})
                        2'b01: entry_count <= entry_count - 1'b1;
                        2'b10: entry_count <= entry_count + 1'b1;
                        default: ;
                    endcase
                end
            end
        end

        if (ALMOST_FULL_THRESHOLD > 0) begin : gen_almost_full_on
            /* verilator lint_off UNSIGNED */
            assign almost_full_o = (entry_count >= buf_cnt_t'(BUFFER_SIZE - ALMOST_FULL_THRESHOLD));
            /* verilator lint_on UNSIGNED */
        end
        else begin : gen_almost_full_off
            assign almost_full_o = 1'b0;
        end

        if (ALMOST_EMPTY_THRESHOLD > 0) begin : gen_almost_empty_on
            /* verilator lint_off CMPCONST */
            assign almost_empty_o = (entry_count <= buf_cnt_t'(ALMOST_EMPTY_THRESHOLD));
            /* verilator lint_on CMPCONST */
        end
        else begin : gen_almost_empty_off
            assign almost_empty_o = 1'b0;
        end
    end
    else begin : gen_entry_count_off
        assign almost_full_o  = 1'b0;
        assign almost_empty_o = 1'b0;
    end

endmodule
