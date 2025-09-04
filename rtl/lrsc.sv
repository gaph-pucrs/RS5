/*!\file lrsc.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 *
 * \brief
 * Atomic memory operations.
 */

module lrsc
(
    input  logic        clk,
    input  logic        reset_n,
    input  logic        stall,

    input  logic        enable_i,
    input  logic [31:0] rs1_data_i,
    input  logic [31:0] data_i,
    input  logic [31:0] reservation_addr_i,
    input  logic [31:0] reservation_data_i,


    output logic        hold_o,
    output logic        write_enable_o, 
    output logic        mem_read_enable_o,
    output logic        mem_write_enable_o,
    output logic        result_o
);

    typedef enum logic [4:0] {
        LOAD     = 5'b00001,
        CMP_ADDR = 5'b00010,
        REGISTER = 5'b00100,
        CMP_DATA = 5'b01000,
        STORE    = 5'b10000
    } state_t;

    state_t current_state;
    state_t next_state;

    logic equal;

    always_comb begin
        unique case (current_state)
            LOAD:     next_state = enable_i ? CMP_ADDR : LOAD;
            CMP_ADDR: next_state = equal    ? REGISTER : STORE;
            REGISTER: next_state = CMP_DATA;
            CMP_DATA: next_state = STORE;
            default:  next_state = LOAD;    /* STORE */
        endcase
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            current_state <= LOAD;
        else if (!stall)
            current_state <= next_state;
    end

    logic [31:0] cmp_opA;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            cmp_opA <= '0;
        end
        else if (!stall) begin
            unique case (current_state)
                LOAD:     cmp_opA <= rs1_data_i;
                REGISTER: cmp_opA <= data_i;
                default: ;
            endcase
        end
    end

    logic [31:0] cmp_opB;
    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            cmp_opB <= '0;
        end
        else if (!stall) begin
            unique case (current_state)
                LOAD:     cmp_opB <= reservation_addr_i;
                REGISTER: cmp_opB <= reservation_data_i;
                default: ;
            endcase
        end
    end

    assign equal = (cmp_opA == cmp_opB);

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            result_o <= '0;
        else if (!stall)
            result_o <= !equal;
    end

    assign hold_o             =  enable_i && (current_state != STORE);
    assign write_enable_o     = (current_state == STORE);
    assign mem_read_enable_o  =  enable_i && (current_state ==  LOAD);
    assign mem_write_enable_o = !result_o && (current_state == STORE);

endmodule
