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
    input  logic [VLEN-1:0] indexed_offsets_i,
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

    vector_lsu_states_e next_state, state, state_r;

    logic [$bits(VLENB)-1:0] elementsProcessed, nextTotalElementsProcessed, elementsProcessed_r;
    logic [$bits(VLENB)-1:0] totalElementsProcessed, totalElementsProcessed_r;
    logic [$bits(VLENB)-1:0] elementsPerRegister;
    logic [3:0]              reg_count;

    assign hold_o = (instruction_operation_i == VSTORE)
                    ? (state inside {VLSU_FIRST_CYCLE, VLSU_EXEC})
                    : ((state == VLSU_FIRST_CYCLE && state_r == VLSU_IDLE) || (state_r inside {VLSU_FIRST_CYCLE, VLSU_EXEC}));

//////////////////////////////////////////////////////////////////////////////
// Decoding
//////////////////////////////////////////////////////////////////////////////

    logic [2:0] nf;
    logic       mew;
    logic [4:0] lumop;
    vew_e       width;
    addrModes_e addrMode;
    vlmul_e     vlmul_effective;

    assign nf       = instruction_i[31:29];
    assign mew      = instruction_i[28];
    assign lumop    = instruction_i[24:20];
    assign addrMode = addrModes_e'(instruction_i[27:26]);
    //assign vlmul_effective = (width/sew)*lmul;

    always_comb
        unique case (instruction_i[14:12])
                3'b000:  width = EW8;
                3'b101:  width = EW16;
                3'b111:  width = EW64;
                default: width = EW32;
        endcase

    assign elementsPerRegister = VLENB >> width;

//////////////////////////////////////////////////////////////////////////////
// FSM
//////////////////////////////////////////////////////////////////////////////

    logic next_cycle_is_last;
    logic indexed_wait_update_index_reg;
    assign indexed_wait_update_index_reg = (state == VLSU_FIRST_CYCLE && addrMode inside {INDEXED_ORDERED, INDEXED_UNORDERED} && hold_o != 1'b1);

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
                    if (indexed_wait_update_index_reg)
                        next_state = VLSU_FIRST_CYCLE;
                    else
                        next_state = VLSU_EXEC;

            VLSU_EXEC:
                if (next_cycle_is_last)
                    next_state = VLSU_LAST_CYCLE;
                else
                    next_state = VLSU_EXEC;

            VLSU_LAST_CYCLE:
                if (
                    (vlmul == LMUL_1  && reg_count < 1)
                ||  (vlmul == LMUL_2  && reg_count < 2)
                ||  (vlmul == LMUL_4  && reg_count < 4)
                ||  (vlmul == LMUL_8  && reg_count < 8)
                )
                    next_state = VLSU_FIRST_CYCLE;
                else
                    next_state = VLSU_IDLE;

            default:
                next_state = VLSU_IDLE;
        endcase
    end

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            unique case(width)
                EW8:     next_cycle_is_last = ((elementsPerRegister - nextTotalElementsProcessed) <= 4);
                EW16:    next_cycle_is_last = ((elementsPerRegister - nextTotalElementsProcessed) <= 2);
                default: next_cycle_is_last = ((elementsPerRegister - nextTotalElementsProcessed) <= 1);
            endcase
        end
        else begin
            next_cycle_is_last = (nextTotalElementsProcessed >= elementsPerRegister);
        end
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 1 - Address Control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] address;
    logic [31:0] offset;
    logic [31:0] offset_strided;
    logic [31:0] offset_indexed;

    assign offset = (addrMode inside {UNIT_STRIDED, STRIDED})
                    ? offset_strided
                    : offset_indexed;

    assign address = base_address_i + offset;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            offset_strided <= '0;
        end
        else if (state == VLSU_IDLE) begin
            offset_strided <= '0;
        end
        else if (addrMode == UNIT_STRIDED) begin
            if (state == VLSU_LAST_CYCLE)
                offset_strided <= offset_strided;
            else
                offset_strided <= offset_strided + 32'h4;
        end else if (addrMode == STRIDED) begin
            if (state == VLSU_LAST_CYCLE)
                offset_strided <= offset_strided;
            else
                offset_strided <= offset_strided + stride_i;
        end
        else begin
            offset_strided <= offset_strided;
        end
    end

    always_comb begin
        unique case(width)
                EW8:     offset_indexed = {24'h0, indexed_offsets_i[( 8*(totalElementsProcessed+1))-1-:8 ]};
                EW16:    offset_indexed = {16'h0, indexed_offsets_i[(16*(totalElementsProcessed+1))-1-:16]};
                default: offset_indexed = indexed_offsets_i[(32*(totalElementsProcessed+1))-1-:32];
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Element Count Control
//////////////////////////////////////////////////////////////////////////////

    always_comb
        if (state inside {VLSU_IDLE, VLSU_LAST_CYCLE})
            nextTotalElementsProcessed = '0;
        else
            nextTotalElementsProcessed = totalElementsProcessed + elementsProcessed;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            totalElementsProcessed  <= '0;
        end
        else begin
            if (!indexed_wait_update_index_reg)
                totalElementsProcessed  <= nextTotalElementsProcessed;
        end
    end

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            if (width == EW8) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1:0])
                        2'b11:      elementsProcessed = 1;
                        2'b10:      elementsProcessed = 2;
                        2'b01:      elementsProcessed = 3;
                        default:    elementsProcessed = 4;
                    endcase
                end
                else if (state == VLSU_LAST_CYCLE) begin
                    unique case(base_address_i[1:0])
                        2'b11:      elementsProcessed = 3;
                        2'b10:      elementsProcessed = 2;
                        2'b01:      elementsProcessed = 1;
                        default:    elementsProcessed = 4;
                    endcase
                end
                else begin
                    elementsProcessed = 4;
                end
            end
            else if (width == EW16) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1])
                        1'b1:       elementsProcessed = 1;
                        default:    elementsProcessed = 2;
                    endcase
                end
                else if(state == VLSU_LAST_CYCLE) begin
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

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            reg_count <= '0;
        else if (next_state == V_IDLE)
            reg_count <= '0;
        else if (next_state == VLSU_LAST_CYCLE)
            reg_count <= reg_count + 1;
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 1 - Write Enable Control
//////////////////////////////////////////////////////////////////////////////

    logic [3:0] mem_write_enable;
    logic [4:0] shift_amount;

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            if (width == EW8) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1:0])
                        2'b11:   begin mem_write_enable = 4'b1000; shift_amount = 24; end
                        2'b10:   begin mem_write_enable = 4'b1100; shift_amount = 16; end
                        2'b01:   begin mem_write_enable = 4'b1110; shift_amount = 8; end
                        default: begin mem_write_enable = 4'b1111; shift_amount = 0; end
                    endcase
                end
                else if (state == VLSU_LAST_CYCLE) begin
                    shift_amount = 0;
                    unique case(base_address_i[1:0])
                        2'b11:   mem_write_enable = 4'b0111;
                        2'b10:   mem_write_enable = 4'b0011;
                        2'b01:   mem_write_enable = 4'b0001;
                        default: mem_write_enable = 4'b1111;
                    endcase
                end
                else begin
                    shift_amount = 0;
                    mem_write_enable = 4'b1111;
                end
            end
            else if (width == EW16) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1])
                        1'b1:    begin mem_write_enable = 4'b1100; shift_amount = 16; end
                        default: begin mem_write_enable = 4'b1111; shift_amount = 0; end
                    endcase
                end
                else if(state == VLSU_LAST_CYCLE) begin
                    shift_amount = 0;
                    unique case(base_address_i[1])
                        1'b1:       mem_write_enable = 4'b0011;
                        default:    mem_write_enable = 4'b1111;
                    endcase
                end
                else begin
                    shift_amount     = 0;
                    mem_write_enable = 4'b1111;
                end
            end
            else begin
                shift_amount = 0;
                if(state inside {VLSU_IDLE}) begin
                    mem_write_enable = 4'b0000;
                end
                else begin
                    mem_write_enable = 4'b1111;
                end
            end
        end
        else begin
            shift_amount = 0;
            if (width == EW8) begin
                unique case(address[1:0])
                    2'b11:   mem_write_enable = 4'b1000;
                    2'b10:   mem_write_enable = 4'b0100;
                    2'b01:   mem_write_enable = 4'b0010;
                    default: mem_write_enable = 4'b0001;
                endcase
            end
            else if (width == EW16) begin
                unique case(address[1])
                    1'b1:       mem_write_enable = 4'b1100;
                    default:    mem_write_enable = 4'b0011;
                endcase
            end
            else begin
                shift_amount = 0;
                mem_write_enable = 4'b1111;
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 1 - Write Data Control
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] write_data;

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            unique case (width)
                EW8: begin
                    write_data[ 7: 0] = write_data_i[(8*(totalElementsProcessed+1))-1-:8];
                    write_data[15: 8] = write_data_i[(8*(totalElementsProcessed+2))-1-:8];
                    write_data[23:16] = write_data_i[(8*(totalElementsProcessed+3))-1-:8];
                    write_data[31:24] = write_data_i[(8*(totalElementsProcessed+4))-1-:8];
                end
                EW16: begin
                    write_data[15: 0] = write_data_i[(16*(totalElementsProcessed+1))-1-:16];
                    write_data[31:16] = write_data_i[(16*(totalElementsProcessed+2))-1-:16];
                end
                default: begin
                    write_data[31: 0] = write_data_i[(32*(totalElementsProcessed+1))-1-:32];
                end
            endcase
        end
        else begin
            unique case (width)
                EW8:     write_data = {4{write_data_i[( 8*(totalElementsProcessed+1))-1-:8]}};
                EW16:    write_data = {2{write_data_i[(16*(totalElementsProcessed+1))-1-:16]}};
                default: write_data =    write_data_i[(32*(totalElementsProcessed+1))-1-:32];
            endcase
        end
    end


//////////////////////////////////////////////////////////////////////////////
// Temporal barrier
//////////////////////////////////////////////////////////////////////////////

    logic [31:0] address_r;

    always @(posedge clk) begin
        address_r <= address;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state_r <= VLSU_IDLE;
        end
        else begin
            state_r <= state;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            totalElementsProcessed_r <= '0;
            elementsProcessed_r      <= '0;
        end
        else if (state == VLSU_IDLE) begin
            totalElementsProcessed_r <= '0;
            elementsProcessed_r      <= '0;
        end
        else begin
            elementsProcessed_r      <= elementsProcessed;
            totalElementsProcessed_r <= totalElementsProcessed;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 2 - Read Data Control
//////////////////////////////////////////////////////////////////////////////

    logic [ 7:0]     read_data_8b  [3:0];
    logic [15:0]     read_data_16b [1:0];
    logic [VLEN-1:0] read_data;

    always_comb begin
        if (addrMode != UNIT_STRIDED || (addrMode == UNIT_STRIDED && state_r == VLSU_FIRST_CYCLE)) begin
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
        else begin
            read_data_8b[0] = mem_read_data_i[ 7: 0];
            read_data_8b[1] = mem_read_data_i[15: 8];
            read_data_8b[2] = mem_read_data_i[23:16];
            read_data_8b[3] = mem_read_data_i[31:24];
        end
    end

    assign read_data_16b[1] = mem_read_data_i[31:16];

    always_comb begin
        if (addrMode != UNIT_STRIDED || (addrMode == UNIT_STRIDED && state_r == VLSU_FIRST_CYCLE)) begin
            case (address_r[1])
                1'b1:
                    read_data_16b[0] = mem_read_data_i[31:16];
                default:
                    read_data_16b[0] = mem_read_data_i[15:0];
            endcase
        end
        else begin
            read_data_16b[0] = mem_read_data_i[15:0];
        end
    end

    always_comb begin
        unique case (width)
            EW8: begin
                read_data[(8*(totalElementsProcessed_r+1))-1-:8] = read_data_8b[0];
                if (elementsProcessed_r > 1)
                    read_data[(8*(totalElementsProcessed_r+2))-1-:8] = read_data_8b[1];
                if (elementsProcessed_r > 2)
                    read_data[(8*(totalElementsProcessed_r+3))-1-:8] = read_data_8b[2];
                if (elementsProcessed_r > 3)
                    read_data[(8*(totalElementsProcessed_r+4))-1-:8] = read_data_8b[3];
            end
            EW16: begin
                read_data[(16*(totalElementsProcessed_r+1))-1-:16] = read_data_16b[0];
                if (elementsProcessed_r > 1)
                    read_data[(16*(totalElementsProcessed_r+2))-1-:16] = read_data_16b[1];
            end
            default: begin
                read_data[(32*(totalElementsProcessed_r+1))-1-:32] = mem_read_data_i;
            end
        endcase
    end

    always @(posedge clk) begin
        if (state_r != VLSU_IDLE)
            read_data_o <= read_data;
        else
            read_data_o <= '0;
    end

//////////////////////////////////////////////////////////////////////////////
// Output Control
//////////////////////////////////////////////////////////////////////////////

    assign mem_address_o      = address;
    assign mem_read_enable_o  = 1'b1;
    assign mem_write_data_o   = write_data << shift_amount;

    always_comb begin
        if (instruction_operation_i == VSTORE) begin
            if (addrMode == UNIT_STRIDED)
                mem_write_enable_o = (state inside{VLSU_FIRST_CYCLE, VLSU_EXEC, VLSU_LAST_CYCLE})
                                    ? mem_write_enable
                                    : '0;
            else
                mem_write_enable_o = (state inside{VLSU_FIRST_CYCLE, VLSU_EXEC})
                                    ? mem_write_enable
                                    : '0;
        end
        else begin
            mem_write_enable_o = '0;
        end
    end

endmodule