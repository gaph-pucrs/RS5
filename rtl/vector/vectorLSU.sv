/*!\file vectorLSU.sv
 *
 * Willian Nunes    <willian.nunes@edu.pucrs.br>
 * Angelo Dal Zotto <angelo.dalzotto@edu.pucrs.br>
 * Marcos Sartori   <marcos.sartori@acad.pucrs.br>
 * Ney Calazans     <ney.calazans@ufsc.br>
 * Fernando Moraes  <fernando.moraes@pucrs.br>
 * GAPH - Hardware Design Support Group
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul <https://pucrs.br/>
 */

`include "../RS5_pkg.sv"

/* verilator lint_off WIDTHTRUNC */
module vectorLSU
    import RS5_pkg::*;
#(
    parameter int VLEN      = 64,
    parameter int VLENB     = 8,
    parameter int BUS_WIDTH = 32

) (
    input  logic                      clk,
    input  logic                      reset_n,

    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [31:0]               instruction_i,
    /* verilator lint_on UNUSEDSIGNAL */
    input  logic [31:0]               base_address_i,
    input  logic [31:0]               stride_i,
    input  logic [VLEN-1:0]           indexed_offsets_i,
    input  logic [VLEN-1:0]           write_data_i,

    input  vector_states_e            current_state,
    input  logic                      hazard_detected_i,

    input  iType_e                    instruction_operation_i,
    input  logic                      whole_reg_load_store,
    input  vlmul_e                    vlmul,

    /* verilator lint_off UNUSEDSIGNAL */
    input  logic [3:0]                cycle_count_r,
    /* verilator lint_on UNUSEDSIGNAL */
    input  logic[$bits(VLEN)-1:0]     vl,
    input  logic[$bits(VLEN)-1:0]     vl_curr_reg,
    input  logic                      vm,
    input  logic [7:0][ VLENB   -1:0] mask_sew8,
    input  logic [7:0][(VLENB/2)-1:0] mask_sew16,
    input  logic [7:0][(VLENB/4)-1:0] mask_sew32,

    output logic                      hold_o,

    output logic [31:0]               mem_address_o,
    output logic                      mem_read_enable_o,
    output logic [BUS_WIDTH/8-1:0]    mem_write_enable_o,
    output logic [BUS_WIDTH  -1:0]    mem_write_data_o,
    input  logic [BUS_WIDTH  -1:0]    mem_read_data_i,

    output logic [VLEN-1:0]           read_data_o
);

    vector_lsu_states_e      next_state, state;

    logic                    vector_process_done;

    logic [$bits(VLENB)-1:0] elementsPerRegister;
    logic [$bits(VLENB)-1:0] elementsProcessedCycle, nextElementsProcessedRegister;
    logic [$bits(VLENB)-1:0] elementsProcessedRegister;
    logic [$bits(VLEN)-1:0]  elementsProcessedTotal;
    logic [3:0]              reg_count;

//////////////////////////////////////////////////////////////////////////////
// Decoding
//////////////////////////////////////////////////////////////////////////////

    // logic [2:0] nf;
    // logic       mew;
    // logic [4:0] lumop;
    //vlmul_e     vlmul_effective;

    vew_e       width;
    addrModes_e addrMode;

    // assign nf       = instruction_i[31:29];
    // assign mew      = instruction_i[28];
    // assign lumop    = instruction_i[24:20];
    // assign vlmul_effective = (width/sew)*lmul;

    assign addrMode = addrModes_e'(instruction_i[27:26]);

    always_comb
        unique case (instruction_i[14:12])
                3'b000:  width = EW8;
                3'b101:  width = EW16;
                3'b111:  width = EW64;
                default: width = EW32;
        endcase

    assign elementsPerRegister = VLENB >> width;

//////////////////////////////////////////////////////////////////////////////
// Cycle Control
//////////////////////////////////////////////////////////////////////////////

    localparam ELEMENTS_PER_ACCESS_EW8  = BUS_WIDTH/8;
    localparam ELEMENTS_PER_ACCESS_EW16 = BUS_WIDTH/16;
    localparam ELEMENTS_PER_ACCESS_EW32 = BUS_WIDTH/32;

    logic next_cycle_is_last;
    logic indexed_wait_update_index_reg;

    assign indexed_wait_update_index_reg = (state == VLSU_FIRST_CYCLE && addrMode inside {INDEXED_ORDERED, INDEXED_UNORDERED} && hold_o != 1'b1);

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            unique case(width)
                EW8:     next_cycle_is_last = ((elementsPerRegister - nextElementsProcessedRegister) <= ELEMENTS_PER_ACCESS_EW8);
                EW16:    next_cycle_is_last = ((elementsPerRegister - nextElementsProcessedRegister) <= ELEMENTS_PER_ACCESS_EW16);
                default: next_cycle_is_last = ((elementsPerRegister - nextElementsProcessedRegister) <= ELEMENTS_PER_ACCESS_EW32);
            endcase
        end
        else begin
            next_cycle_is_last = (nextElementsProcessedRegister >= elementsPerRegister);
        end
    end

    assign vector_process_done = (elementsProcessedTotal >= vl && !whole_reg_load_store);

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
                if (instruction_operation_i inside {VLOAD, VSTORE} && current_state == V_IDLE && !hazard_detected_i)
                    next_state = VLSU_FIRST_CYCLE;
                else
                    next_state = VLSU_IDLE;

            VLSU_FIRST_CYCLE:
                    if (indexed_wait_update_index_reg)
                        next_state = VLSU_FIRST_CYCLE;
                    else if (next_cycle_is_last || vector_process_done)
                        next_state = VLSU_LAST_CYCLE;
                    else
                        next_state = VLSU_EXEC;

            VLSU_EXEC:
                if (next_cycle_is_last || vector_process_done)
                    next_state = VLSU_LAST_CYCLE;
                else
                    next_state = VLSU_EXEC;

            VLSU_LAST_CYCLE:
                    next_state = VLSU_DELAY;

            VLSU_DELAY:
                if ((
                    (vlmul inside {LMUL_1, LMUL_1_2, LMUL_1_4, LMUL_1_8}  && reg_count < 1)
                ||  (vlmul == LMUL_2  && reg_count < 2)
                ||  (vlmul == LMUL_4  && reg_count < 4)
                ||  (vlmul == LMUL_8  && reg_count < 8)
                ) && !vector_process_done)
                    if (base_address_i[1:0] == 2'b00 && addrMode == UNIT_STRIDED && (ELEMENTS_PER_ACCESS_EW8 == VLEN/8 || ELEMENTS_PER_ACCESS_EW16 == VLEN/16 || ELEMENTS_PER_ACCESS_EW32 == VLEN/32)) begin
                        next_state = VLSU_LAST_CYCLE;
                    end
                    else begin
                        next_state = VLSU_FIRST_CYCLE;
                    end
                else
                    next_state = VLSU_IDLE;

            default:
                next_state = VLSU_IDLE;
        endcase
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
        else if (addrMode == UNIT_STRIDED && state != VLSU_DELAY) begin
            if (base_address_i[1:0] == 2'b00 && (ELEMENTS_PER_ACCESS_EW8 == VLEN/8 || ELEMENTS_PER_ACCESS_EW16 == VLEN/16 || ELEMENTS_PER_ACCESS_EW32 == VLEN/32)) begin
                if (state == VLSU_LAST_CYCLE) begin
                    offset_strided <= offset_strided + 32'(ELEMENTS_PER_ACCESS_EW8);
                end
            end
            else begin
                unique case(width)
                    EW8:     offset_strided <= offset_strided + elementsProcessedCycle;
                    EW16:    offset_strided <= offset_strided + (elementsProcessedCycle << 1);
                    default: offset_strided <= offset_strided + 32'(ELEMENTS_PER_ACCESS_EW8);
                endcase
            end
        end
        else if (addrMode == STRIDED) begin
            if (!(state inside {VLSU_LAST_CYCLE, VLSU_DELAY}))
                offset_strided <= offset_strided + stride_i;
        end
    end

    always_comb begin
        unique case(width)
            EW8:     offset_indexed = {24'h0, indexed_offsets_i[( 8*elementsProcessedRegister)+:8 ]};
            EW16:    offset_indexed = {16'h0, indexed_offsets_i[(16*elementsProcessedRegister)+:16]};
            default: offset_indexed =         indexed_offsets_i[(32*elementsProcessedRegister)+:32];
        endcase
    end

//////////////////////////////////////////////////////////////////////////////
// Element Count Control
//////////////////////////////////////////////////////////////////////////////

    always_comb
        if (state inside {VLSU_IDLE, VLSU_LAST_CYCLE, VLSU_DELAY})
            nextElementsProcessedRegister = '0;
        else
            nextElementsProcessedRegister = elementsProcessedRegister + elementsProcessedCycle;

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            elementsProcessedRegister <= '0;
        else if (!indexed_wait_update_index_reg)
            elementsProcessedRegister <= nextElementsProcessedRegister;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            elementsProcessedTotal <= 0;
        else if (state == VLSU_IDLE)
            elementsProcessedTotal <= 0;
        else if (!indexed_wait_update_index_reg && state != VLSU_DELAY)
            elementsProcessedTotal <= elementsProcessedTotal + elementsProcessedCycle;
    end

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            if (state == VLSU_FIRST_CYCLE && base_address_i[1:0] == 2'b00
                && (ELEMENTS_PER_ACCESS_EW8 == VLEN/8 || ELEMENTS_PER_ACCESS_EW16 == VLEN/16 || ELEMENTS_PER_ACCESS_EW32 == VLEN/32)) begin
                elementsProcessedCycle = '0;
            end
            else if (width == EW8) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1:0])
                        2'b11:      elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW8-3;
                        2'b10:      elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW8-2;
                        2'b01:      elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW8-1;
                        default:    elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW8;
                    endcase
                end
                else if (state == VLSU_LAST_CYCLE) begin
                    unique case(base_address_i[1:0])
                        2'b11:      elementsProcessedCycle = 3;
                        2'b10:      elementsProcessedCycle = 2;
                        2'b01:      elementsProcessedCycle = 1;
                        default:    elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW8;
                    endcase
                end
                else begin
                    elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW8;
                end
            end
            else if (width == EW16) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    unique case(base_address_i[1])
                        1'b1:       elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW16-1;
                        default:    elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW16;
                    endcase
                end
                else if (state == VLSU_LAST_CYCLE) begin
                    unique case(base_address_i[1])
                        1'b1:       elementsProcessedCycle = 1;
                        default:    elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW16;
                    endcase
                end
                else begin
                    elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW16;
                end
            end
            else begin
                elementsProcessedCycle = ELEMENTS_PER_ACCESS_EW32;
            end
        end
        else begin
            elementsProcessedCycle = 1;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            reg_count <= '0;
        else if (next_state == VLSU_IDLE)
            reg_count <= '0;
        else if (next_state == VLSU_DELAY)
            reg_count <= reg_count + 1;
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 1 - Write Enable Control
//////////////////////////////////////////////////////////////////////////////

    logic [BUS_WIDTH/8-1:0] mem_write_enable;
    logic [4:0] shift_amount;

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            if (width == EW8) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    for (int i = 0, int j = 0; i < ELEMENTS_PER_ACCESS_EW8; i++)
                        if (i >= base_address_i[1:0] && j < vl_curr_reg) begin
                            mem_write_enable[i] = (vm | mask_sew8[cycle_count_r][j]);
                            j++;
                        end
                        else begin
                            mem_write_enable[i] = 1'b0;
                        end

                    unique case(base_address_i[1:0])
                        2'b11:   shift_amount = 24;
                        2'b10:   shift_amount = 16;
                        2'b01:   shift_amount = 8;
                        default: shift_amount = 0;
                    endcase
                end
                else if (state == VLSU_LAST_CYCLE) begin
                    shift_amount = 0;
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++)
                        if ((i < base_address_i[1:0] || base_address_i[1:0] == 0) && (elementsProcessedRegister + i) < vl_curr_reg)
                            mem_write_enable[i] = (vm | mask_sew8[cycle_count_r][elementsProcessedRegister + i]);
                        else
                            mem_write_enable[i] = 1'b0;
                end
                else begin
                    shift_amount = 0;
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++)
                        mem_write_enable[i] = (vm | mask_sew8[cycle_count_r][elementsProcessedRegister+i]) && ((elementsProcessedRegister + i) < vl_curr_reg);
                end
            end
            else if (width == EW16) begin
                if(state == VLSU_FIRST_CYCLE) begin
                    for (int i = 0, int j = 0; i < ELEMENTS_PER_ACCESS_EW16; i++)
                        if (i >= base_address_i[1] && j < vl_curr_reg) begin
                            mem_write_enable[(2*i)+:2] = (vm | mask_sew16[cycle_count_r][j])
                                                        ? 2'b11
                                                        : 2'b00;
                            j++;
                        end
                        else begin
                            mem_write_enable[(2*i)+:2] = 2'b00;
                        end

                    unique case(base_address_i[1])
                        1'b1:    shift_amount = 16;
                        default: shift_amount = 0;
                    endcase
                end
                else if(state == VLSU_LAST_CYCLE) begin
                    shift_amount = 0;
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16; i++)
                        if ((i < base_address_i[1] || base_address_i[1] == 0) && (elementsProcessedRegister + i) < vl_curr_reg)
                            mem_write_enable[(2*i)+:2] = (vm | mask_sew16[cycle_count_r][elementsProcessedRegister + i])
                                                        ? 2'b11
                                                        : 2'b00;
                        else
                            mem_write_enable[(2*i)+:2] = 2'b00;
                end
                else begin
                    shift_amount = 0;
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16; i++)
                        mem_write_enable[(2*i)+:2] = (vm | mask_sew16[cycle_count_r][elementsProcessedRegister+i]) && ((elementsProcessedRegister + i) < vl_curr_reg)
                                                    ? 2'b11
                                                    : 2'b00;
                end
            end
            else begin
                shift_amount = 0;
                if(state == VLSU_IDLE) begin
                    mem_write_enable = '0;
                end
                else begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW32; i++)
                        mem_write_enable[(4*i)+:4] = (vm | mask_sew32[cycle_count_r][elementsProcessedRegister+i]) && ((elementsProcessedRegister + i) < vl_curr_reg)
                                                    ? 4'b1111
                                                    : 4'b0000;
                end
            end
        end
        else begin
            shift_amount = 0;

            if ((width == EW8) && (vm | mask_sew8[cycle_count_r][elementsProcessedRegister]) && (elementsProcessedRegister < vl_curr_reg)) begin
                unique case(address[1:0])
                    2'b11:   mem_write_enable = {'0, 4'b1000};
                    2'b10:   mem_write_enable = {'0, 4'b0100};
                    2'b01:   mem_write_enable = {'0, 4'b0010};
                    default: mem_write_enable = {'0, 4'b0001};
                endcase
            end
            else if ((width == EW16) && (vm | mask_sew16[cycle_count_r][elementsProcessedRegister]) && (elementsProcessedRegister < vl_curr_reg)) begin
                unique case(address[1])
                    1'b1:       mem_write_enable = {'0, 4'b1100};
                    default:    mem_write_enable = {'0, 4'b0011};
                endcase
            end
            else if ((width == EW32) && (vm | mask_sew32[cycle_count_r][elementsProcessedRegister]) && (elementsProcessedRegister < vl_curr_reg)) begin
                mem_write_enable = {'0, 4'b1111};
            end
            else begin
                mem_write_enable = '0;
            end
        end
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 1 - Write Data Control
//////////////////////////////////////////////////////////////////////////////

    logic [BUS_WIDTH-1:0] write_data;

    always_comb begin
        if (addrMode == UNIT_STRIDED) begin
            unique case (width)
                EW8: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++)
                        write_data[(8*i)+:8] = write_data_i[(8*(elementsProcessedRegister+i))+:8];
                end
                EW16: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16; i++)
                        write_data[(16*i)+:16] = write_data_i[(16*(elementsProcessedRegister+i))+:16];
                end
                default: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW32; i++)
                        write_data[(32*i)+:32] = write_data_i[(32*(elementsProcessedRegister+i))+:32];
                end
            endcase
        end
        else begin
            unique case (width)
                EW8:     write_data = {'0, {4{write_data_i[( 8*elementsProcessedRegister)+:8 ]}}};
                EW16:    write_data = {'0, {2{write_data_i[(16*elementsProcessedRegister)+:16]}}};
                default: write_data = {'0,    write_data_i[(32*elementsProcessedRegister)+:32]};
            endcase
        end
    end

//////////////////////////////////////////////////////////////////////////////
// Temporal barrier
//////////////////////////////////////////////////////////////////////////////

    addrModes_e              addrMode_r;
    logic [1:0]              address_r;
    logic [1:0]              address_2r;
    vector_lsu_states_e      state_r;
    vector_lsu_states_e      state_2r;
    logic [$bits(VLENB)-1:0] elementsProcessedCycle_r;
    logic [$bits(VLENB)-1:0] elementsProcessedCycle_2r;
    logic [$bits(VLENB)-1:0] elementsProcessedRegister_r;
    logic [$bits(VLENB)-1:0] elementsProcessedRegister_2r;

    always @(posedge clk) begin
        address_r  <= address[1:0];
        address_2r <= address_r;
        addrMode_r <= addrMode;
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state_r  <= VLSU_IDLE;
            state_2r <= VLSU_IDLE;
        end
        else begin
            state_r  <= state;
            state_2r <= state_r;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            elementsProcessedCycle_r    <= '0;
            elementsProcessedRegister_r <= '0;
        end
        else if (state == VLSU_IDLE) begin
            elementsProcessedCycle_r    <= '0;
            elementsProcessedRegister_r <= '0;
        end
        else begin
            elementsProcessedCycle_r    <= elementsProcessedCycle;
            elementsProcessedRegister_r <= elementsProcessedRegister;
        end
    end

    always_ff @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            elementsProcessedCycle_2r    <= '0;
            elementsProcessedRegister_2r <= '0;
        end
        else begin
            elementsProcessedCycle_2r    <= elementsProcessedCycle_r;
            elementsProcessedRegister_2r <= elementsProcessedRegister_r;
        end
    end

//////////////////////////////////////////////////////////////////////////////
// STAGE 2 - Read Data Control
//////////////////////////////////////////////////////////////////////////////

    logic [ELEMENTS_PER_ACCESS_EW8 -1:0][ 7:0] read_data_8b;
    logic [ELEMENTS_PER_ACCESS_EW16-1:0][15:0] read_data_16b;
    logic [ELEMENTS_PER_ACCESS_EW32-1:0][31:0] read_data_32b;
    logic [VLEN-1:0]  read_data;

    always_comb begin
        if (addrMode_r != UNIT_STRIDED || (addrMode_r == UNIT_STRIDED && state_2r == VLSU_FIRST_CYCLE)) begin
            case (address_2r[1:0])
                2'b11: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++) begin
                        read_data_8b[i] = mem_read_data_i[24+(8*i)+:8];
                    end
                end
                2'b10: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++) begin
                        read_data_8b[i] = mem_read_data_i[16+(8*i)+:8];
                    end
                end
                2'b01: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++) begin
                        read_data_8b[i] = mem_read_data_i[8+(8*i)+:8];
                    end
                end
                default: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++) begin
                        read_data_8b[i] = mem_read_data_i[(8*i)+:8];
                    end
                end
            endcase
        end
        else begin
            for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8; i++) begin
                read_data_8b[i]  = mem_read_data_i[(8*i)+:8];
            end
        end
    end

    always_comb begin
        if (addrMode_r != UNIT_STRIDED || (addrMode_r == UNIT_STRIDED && state_2r == VLSU_FIRST_CYCLE)) begin
            case (address_2r[1])
                1'b1:
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16; i++) begin
                        read_data_16b[i] = mem_read_data_i[16+(16*i)+:16];
                    end
                default: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16; i++) begin
                        read_data_16b[i] = mem_read_data_i[(16*i)+:16];
                    end
                end
            endcase
        end
        else begin
            for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16; i++) begin
                read_data_16b[i] = mem_read_data_i[(16*i)+:16];
            end
        end
    end

    always_comb begin
        for (int i = 0; i < ELEMENTS_PER_ACCESS_EW32; i++)
            read_data_32b[i] = mem_read_data_i[(32*i)+:32];
    end

    always_comb begin
        if (state_2r != VLSU_IDLE) begin
            unique case (width)
                EW8: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW8;  i++) begin
                        if (elementsProcessedCycle_2r > i) begin
                            read_data[(8*(elementsProcessedRegister_2r+i))+:8] = read_data_8b[i];
                        end
                    end
                end
                EW16: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW16;  i++) begin
                        if (elementsProcessedCycle_2r > i) begin
                            read_data[(16*(elementsProcessedRegister_2r+i))+:16] = read_data_16b[i];
                        end
                    end
                end
                default: begin
                    for (int i = 0; i < ELEMENTS_PER_ACCESS_EW32;  i++) begin
                        if (elementsProcessedCycle_2r > i) begin
                            read_data[(32*(elementsProcessedRegister_2r+i))+:32] = read_data_32b[i];
                        end
                    end
                end
            endcase
        end
        else begin
            read_data = '0;
        end
    end

    always @(posedge clk) begin
        if (state_2r != VLSU_IDLE)
            read_data_o <= read_data;
        else
            read_data_o <= '0;
    end
    //assign read_data_o = read_data;

//////////////////////////////////////////////////////////////////////////////
// Output Control
//////////////////////////////////////////////////////////////////////////////

    assign hold_o = (instruction_operation_i == VSTORE)
                    ? (state inside {VLSU_FIRST_CYCLE, VLSU_EXEC, VLSU_LAST_CYCLE})
                    : ((state == VLSU_FIRST_CYCLE && state_r == VLSU_IDLE) || (state_r inside {VLSU_FIRST_CYCLE, VLSU_EXEC, VLSU_LAST_CYCLE}));

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
/* verilator lint_on WIDTHTRUNC */