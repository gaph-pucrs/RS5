module vectorLSU
    import RS5_pkg::*;
#(
    parameter int VLEN  = 64,
    parameter int VLENB = 8
) (
    input  logic            clk,
    input  logic            reset_n,

    input  logic [31:0]     instruction_i,
    input  logic [31:0]     base_address_i,
    input  logic [31:0]     stride_i,
    input  logic [VLEN-1:0] write_data_i,

    input  vector_states_e  current_state,
    input  logic [ 4:0]     cycle_count,

    input  iType_e          instruction_operation_i,
    input  vew_e            vsew,
    input  vlmul_e          vlmul,

    output logic            hold_o,

    output logic [31:0]     mem_address_o,
    output logic            mem_read_enable_o,
    output logic [ 3:0]     mem_write_enable_o,
    output logic [31:0]     mem_write_data_o,
    input  logic [31:0]     mem_read_data_i,

    output logic [VLEN-1:0] read_data_o
);

    vector_lsu_states_e state, next_state;

    logic [$bits(VLENB)-1:0] elementsProcessed, elementsProcessed_r, totalElementsProcessed, totalElementsProcessed_r;
    logic [$bits(VLENB)-1:0] elementsPerRegister;

    assign hold_o = (state inside {VLSU_FIRST_CYCLE, VLSU_EXEC});

//////////////////////////////////////////////////////////////////////////////
// Decoding
//////////////////////////////////////////////////////////////////////////////

    logic [2:0] nf;
    logic       mew;
    logic [4:0] lumop;
    vew_lsu_e   width;
    addrModes_e addrMode;

    assign nf       = instruction_i[31:29];
    assign mew      = instruction_i[28];
    assign lumop    = instruction_i[24:20];
    assign width    = vew_lsu_e'(instruction_i[14:12]);
    assign addrMode = addrModes_e'(instruction_i[27:26]);

    always_comb
        if (width == LSU_EW8)
            elementsPerRegister = VLENB;
        else if (width == LSU_EW16)
            elementsPerRegister = VLENB >> 1;
        else
            elementsPerRegister = VLENB >> 2;

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state <= VLSU_IDLE;
        end
        else begin
            state <= next_state;
        end
    end

    always_comb begin
        unique case (state)
            VLSU_IDLE:
                if (instruction_operation_i inside {VLOAD, VSTORE} && current_state == V_IDLE)
                    next_state = VLSU_FIRST_CYCLE;
                else
                    next_state = VLSU_IDLE;

            VLSU_FIRST_CYCLE:
                    next_state = VLSU_EXEC;

            VLSU_EXEC:
                if (
                        (totalElementsProcessed < VLENB   && width == LSU_EW8)
                    ||  (totalElementsProcessed < VLENB/2 && width == LSU_EW16)
                    ||  (totalElementsProcessed < VLENB/4 && width == LSU_EW32)
                )
                    next_state = VLSU_EXEC;
                else
                    next_state = VLSU_END;

            VLSU_END:
                next_state = VLSU_IDLE;

            default:
                next_state = VLSU_IDLE;
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 1 - Address Control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] address;
    logic [31:0] address_r;
    logic [31:0] offset;

    assign address = base_address_i + offset;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            offset <= '0;
        end
        else if (state == VLSU_IDLE) begin
            offset <= '0;
        end
        else if (addrMode == UNIT_STRIDED) begin
            if (state == VLSU_FIRST_CYCLE) begin
                unique case(base_address_i[1:0])
                    2'b11:      offset <= offset + 32'h1;
                    2'b10:      offset <= offset + 32'h2;
                    2'b01:      offset <= offset + 32'h3;
                    default:    offset <= offset + 32'h4;
                endcase
            end
            else begin
                offset <= offset + 32'h4;
            end
        end else if (addrMode == STRIDED) begin
            offset <= offset + stride_i;
        end
        else begin
            offset <= offset;
        end
    end

    always @(posedge clk) begin
        address_r <= address;
    end

//////////////////////////////////////////////////////////////////////////////
// Element Count Control
//////////////////////////////////////////////////////////////////////////////

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            elementsProcessed_r     <= '0;
            totalElementsProcessed  <= '0;
            totalElementsProcessed_r<= '0;
        end
        else if (state == VLSU_IDLE) begin
            elementsProcessed_r     <= '0;
            totalElementsProcessed  <= '0;
            totalElementsProcessed_r<= '0;
        end
        else begin
            elementsProcessed_r     <= elementsProcessed;
            totalElementsProcessed  <= totalElementsProcessed + elementsProcessed;
            totalElementsProcessed_r<= totalElementsProcessed;
        end
    end

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            if (width == LSU_EW8) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1:0])
                        2'b11:      elementsProcessed = 1;
                        2'b10:      elementsProcessed = 2;
                        2'b01:      elementsProcessed = 3;
                        default:    elementsProcessed = 4;
                    endcase
                end
                else begin
                    elementsProcessed = 4;
                end
            end
            else if (width == LSU_EW16) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1])
                        1'b1:       elementsProcessed = 1;
                        default:    elementsProcessed = 2;
                    endcase
                end
                else begin
                    elementsProcessed = 2;
                end
            end
            else begin
                elementsProcessed = 1;
            end
        end
        else begin
            elementsProcessed = 1;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Output Control
//////////////////////////////////////////////////////////////////////////////

    assign mem_address_o      = address;
    assign mem_read_enable_o  = 1'b1;
    assign mem_write_data_o   = '0;
    assign mem_write_enable_o = (instruction_operation_i == VSTORE)
                                ? '1
                                : '0;

//////////////////////////////////////////////////////////////////////////////
// STAGE 2 - Read Data Control
//////////////////////////////////////////////////////////////////////////////

    logic [ 7:0] read_data_8b  [3:0];
    logic [15:0] read_data_16b [1:0];

    always_comb begin
        case (address_r[1:0])
            2'b11: begin
                read_data_8b[0] = mem_read_data_i[31:24];
            end
            2'b10: begin
                read_data_8b[0] = mem_read_data_i[23:16];
                read_data_8b[1] = mem_read_data_i[31:24];
            end
            2'b01: begin
                read_data_8b[0] = mem_read_data_i[15: 8];
                read_data_8b[1] = mem_read_data_i[23:16];
                read_data_8b[2] = mem_read_data_i[31:24];
            end
            default: begin
                read_data_8b[0] = mem_read_data_i[ 7: 0];
                read_data_8b[1] = mem_read_data_i[15: 8];
                read_data_8b[2] = mem_read_data_i[23:16];
                read_data_8b[3] = mem_read_data_i[31:24];
            end
        endcase
    end

    always_comb begin
        read_data_16b[1] = mem_read_data_i[31:16];
        case (address_r[1])
            1'b1:
                read_data_16b[0] = mem_read_data_i[31:16];
            default:
                read_data_16b[0] = mem_read_data_i[15:0];
        endcase
    end

    always_ff @(posedge clk) begin
        if (state == VLSU_EXEC) begin
            if (width == LSU_EW8) begin
                read_data_o[(8*(totalElementsProcessed_r+1))-1-:8] <= read_data_8b[0];
                if (elementsProcessed_r > 1)
                    read_data_o[(8*(totalElementsProcessed_r+2))-1-:8] <= read_data_8b[1];
                if (elementsProcessed_r > 2)
                    read_data_o[(8*(totalElementsProcessed_r+3))-1-:8] <= read_data_8b[2];
                if (elementsProcessed_r > 3)
                    read_data_o[(8*(totalElementsProcessed_r+4))-1-:8] <= read_data_8b[3];
            end
            else if (width == LSU_EW16) begin
                read_data_o[(16*(totalElementsProcessed_r+1))-1-:16] <= read_data_16b[0];
                if (elementsProcessed_r > 1)
                    read_data_o[(16*(totalElementsProcessed_r+2))-1-:16] <= read_data_16b[1];
            end
            else begin
                read_data_o[(32*(totalElementsProcessed_r+1))-1-:32] <= mem_read_data_i;
            end
        end
        else if (state == VLSU_IDLE) begin
            read_data_o <= '0;
        end
    end

endmodule