
#include "rvfi_tools.h"
#include "rvfi_callbacks.h"

// #define STB_DS_IMPLEMENTATION
// #include "stb_ds.h"

// disassemble_info disasm_info = {};

// void init_libopcodes_disassembler() {

// // init_disassemble_info (struct disassemble_info *info, void *stream,
// // 		       fprintf_ftype fprintf_func,
// // 		       fprintf_styled_ftype fprintf_styled_func)
//     init_disassemble_info(&disasm_info, &ss, dis_fprintf);

//     // TODO: Init disasm_info with symtable, probably parsing and ELF file with libbfd

//     // set_default_riscv_dis_options(&disasm_info);  // This inits private_data within the disassemble_info struct
// // parse_riscv_dis_options (const char *opts_in, struct disassemble_info *info)
//     parse_riscv_dis_options(opts_in, &disasm_info)
//     riscv_init_disasm_info(&disasm_info);

//     disasm_info.arch = bfd_arch_riscv;
//     disasm_info.mach = bfd_mach_riscv32;
//     disasm_info.read_memory_func = buffer_read_memory;
//     disasm_info.buffer = input_buffer;
//     disasm_info.buffer_vma = 0;
//     disasm_info.buffer_length = input_buffer_size;

//     // TODO: Init info.section

//     disassemble_init_for_target(&disasm_info);

// }

// TODO: Turn these global variables into a struct, enabling multiple RVFI monitors in a testbench

rv_isa isa;
FILE *tracer_log_file, *profiler_log_file, *symbol_table_file, *symbol_watchlist_file;

int en_tracer, en_profiler, en_checker;

GHashTable *symbol_table_hash_table = NULL;
GArray *symbol_watchlist = NULL;
GArray *counter_stack = NULL;

counter_info_t last_counter_state;  // Counter state as of the last call to a function in the watchlist

#define RVFI_N_COUNTERS 24
rvfi_performance_counter_t rvfi_performance_counters[RVFI_N_COUNTERS];

int rvfi_monitor_init(int enable_tracer, int enable_profiler, int enable_checker, char* tracer_log_file_name, char* profiler_log_file_name, char* symbol_table_file_name, char* symbol_watchlist_file_name) {

    #ifdef RV64
    isa = rv64;
    #else
    isa = rv32;
    #endif

    // symbol_table_hash_table = g_hash_table_new(g_int_hash, g_int_equal);
    symbol_table_hash_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    symbol_watchlist = g_array_new(FALSE, FALSE, sizeof(char*));
    counter_stack = g_array_new(FALSE, FALSE, sizeof(counter_info_t));

    en_tracer = enable_tracer;
    en_profiler = enable_profiler;
    en_checker = enable_checker;

    if (en_tracer) {

        tracer_log_file = fopen(tracer_log_file_name, "w");

        if (tracer_log_file == NULL) {
            printf("[RVFI_MONITOR] Cant open file <%s> in write mode\n", tracer_log_file_name);
            return 1;
        }

        fprintf(tracer_log_file, "Cycle\tPC\tInstruction\tDecoded Instruction\tOperands and result\n");

    }

    if (en_profiler) {

        profiler_log_file = fopen(profiler_log_file_name, "w");

        if (profiler_log_file == NULL) {
            printf("[RVFI_MONITOR] Cant open file <%s> in write mode\n", profiler_log_file_name);
            return 1;
        }

        symbol_watchlist_file = fopen(symbol_watchlist_file_name, "r");

        if (symbol_watchlist_file == NULL) {
            printf("[RVFI_MONITOR] Cant open file <%s> in read mode\n", symbol_watchlist_file_name);
            return 1;
        }

        // Fill out watch symbol_watchlist
        while (1) {

            char* watched_symbol = malloc(100);

            // Parse line containing a single symbol name per line
            if (fscanf(symbol_watchlist_file, "%s", watched_symbol) == EOF)
                break;

            if (watched_symbol[0] != '#') {  // This allows for comments in the watchlist file
                // printf("[RVFI_MONITOR] Adding function <%s> to watchlist>\n", watched_symbol);
                // arrput(symbol_watchlist, watched_symbol);
                g_array_append_val(symbol_watchlist, watched_symbol);
                // printf("%s\n", arrlast(symbol_watchlist));
            }

        }

    }

    // Parse ELF symbols into 2 hash tables, one containing all symbol name and PC and another containing the names of watched symbols
    if (en_tracer || en_profiler) {

        symbol_table_file = fopen(symbol_table_file_name, "r");

        if (symbol_table_file == NULL) {
            printf("[RVFI_MONITOR] Cant open file <%s> in read mode\n", symbol_table_file_name);
            return 1;
        }

        // Fill out symbol PC and name hash table
        // Parse symbol table dump from "nm" where is line follows the form "<pc> <function_name>\n"
        while (1) {

            symbol_info_t* new_symbol = malloc(sizeof(symbol_info_t));
            char symbol_type;
            uint32_t symbol_pc;

            if (fscanf(symbol_table_file, "%x %c %s", &symbol_pc, &symbol_type, new_symbol->function_name) == EOF)
                break;

            // 'T' = function, 't' == label
            if (!(symbol_type == 'T' || symbol_type == 't'))
            // if (symbol_type != 'T')
                continue;

            new_symbol->is_watched = 0;
            new_symbol->is_function = (symbol_type == 'T');
            new_symbol->times_called = 0;
            new_symbol->start_cycles = g_array_new(FALSE, FALSE, sizeof(uint64_t));
            new_symbol->end_cycles = g_array_new(FALSE, FALSE, sizeof(uint64_t));

            // g_hash_table_insert(symbol_table_hash_table, &symbol_pc, new_symbol);
            g_hash_table_insert(symbol_table_hash_table, GINT_TO_POINTER(symbol_pc), new_symbol);

            uint32_t new_pc = symbol_pc;
            symbol_info_t* temp_symbol = g_hash_table_lookup(symbol_table_hash_table, GINT_TO_POINTER(new_pc));
            if (new_symbol == NULL)
                printf("NULL\n");
            else
                // printf("Correctly added key <%d> value <%s> to hash table\n", symbol_pc, temp_symbol->function_name);
                printf("Correctly added key <%d> value <%s> to hash table\n", new_pc, temp_symbol->function_name);

            // Look for the current symbol in the watchlist array, tag it as watched if so
            // Note that this only tags symbols in the given symbol list, if there are symbols in the watchlist but not in the symbol list, NO ERROR OR WARNING WILL BE RETURNED
            if (en_profiler) {

                // for (int i = 0; i < arrlen(symbol_watchlist); i++)
                for (int i = 0; i < symbol_watchlist->len; i++)
                    if (strncmp(g_array_index(symbol_watchlist, char*, i), new_symbol->function_name, 100) == 0) {

                        new_symbol->is_watched = 1;

                        printf("[RVFI_MONITOR] Adding function <%s> to watchlist\n", new_symbol->function_name);

                        free(g_array_index(symbol_watchlist, char*, i));
                        symbol_watchlist = g_array_remove_index_fast(symbol_watchlist, i);  // Overwrite current element (not needed anymore) with last element

                        break;
                    }

            }

        }

        // Loop through hash tablke, print all KV pairs
        void _debug_hash_table_iterator(gpointer key, gpointer value, gpointer user_data);
        g_hash_table_foreach(symbol_table_hash_table, (GHFunc) _debug_hash_table_iterator, NULL);

        // Free watchlist array, we dont needed anymore after the all symbols hash table was tagged in the inner loop above
        if (en_profiler) {
            g_array_free(symbol_watchlist, FALSE);
        }

    }

    // Initialize virtual performance counters
    // NOTE: Add new virtual performance counters here

    rvfi_performance_counters[0] = (rvfi_performance_counter_t) {.name = "Clock cycles", .val = 0, .update = rvfi_tools_perfcount_cb_clock_cycles};
    rvfi_performance_counters[1] = (rvfi_performance_counter_t) {.name = "Instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_insn_retired};
    rvfi_performance_counters[2] = (rvfi_performance_counter_t) {.name = "Compressed instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_cmprss_insn_retired};
    rvfi_performance_counters[3] = (rvfi_performance_counter_t) {.name = "Unidentified instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_unkwown_insn_retired};
    rvfi_performance_counters[4] = (rvfi_performance_counter_t) {.name = "Idle/stall cycles", .val = 0, .update = rvfi_tools_perfcount_cb_stall_cycles};
    rvfi_performance_counters[5] = (rvfi_performance_counter_t) {.name = "Arithmetic operations", .val = 0, .update = rvfi_tools_perfcount_cb_arith};
    rvfi_performance_counters[6] = (rvfi_performance_counter_t) {.name = "Shift/rotate operations", .val = 0, .update = rvfi_tools_perfcount_cb_shift};
    rvfi_performance_counters[7] = (rvfi_performance_counter_t) {.name = "Bitwise operations", .val = 0, .update = rvfi_tools_perfcount_cb_bitwise};
    rvfi_performance_counters[8] = (rvfi_performance_counter_t) {.name = "Multiplication operations", .val = 0, .update = rvfi_tools_perfcount_cb_mult};
    rvfi_performance_counters[9] = (rvfi_performance_counter_t) {.name = "Division operations", .val = 0, .update = rvfi_tools_perfcount_cb_div};
    rvfi_performance_counters[10] = (rvfi_performance_counter_t) {.name = "Forward static jumps", .val = 0, .update = rvfi_tools_perfcount_cb_fwd_static_jumps};
    rvfi_performance_counters[11] = (rvfi_performance_counter_t) {.name = "Backward static jumps", .val = 0, .update = rvfi_tools_perfcount_cb_bwd_static_jumps};
    rvfi_performance_counters[12] = (rvfi_performance_counter_t) {.name = "Forward register jumps", .val = 0, .update = rvfi_tools_perfcount_cb_fwd_reg_jumps};
    rvfi_performance_counters[13] = (rvfi_performance_counter_t) {.name = "Backward register jumps", .val = 0, .update = rvfi_tools_perfcount_cb_bwd_reg_jumps};
    rvfi_performance_counters[14] = (rvfi_performance_counter_t) {.name = "Taken forward branches", .val = 0, .update = rvfi_tools_perfcount_cb_taken_fwd_branches};
    rvfi_performance_counters[15] = (rvfi_performance_counter_t) {.name = "Not-taken forward branches", .val = 0, .update = rvfi_tools_perfcount_cb_not_taken_fwd_branches};
    rvfi_performance_counters[16] = (rvfi_performance_counter_t) {.name = "Taken backward branches", .val = 0, .update = rvfi_tools_perfcount_cb_taken_bwd_branches};
    rvfi_performance_counters[17] = (rvfi_performance_counter_t) {.name = "Not-taken backward branches", .val = 0, .update = rvfi_tools_perfcount_cb_not_taken_bwd_branches};
    rvfi_performance_counters[18] = (rvfi_performance_counter_t) {.name = "Byte loads", .val = 0, .update = rvfi_tools_perfcount_cb_byte_loads};
    rvfi_performance_counters[19] = (rvfi_performance_counter_t) {.name = "Half-word (16 bits) loads", .val = 0, .update = rvfi_tools_perfcount_cb_halfword_loads};
    rvfi_performance_counters[20] = (rvfi_performance_counter_t) {.name = "Word loads", .val = 0, .update = rvfi_tools_perfcount_cb_word_loads};
    rvfi_performance_counters[21] = (rvfi_performance_counter_t) {.name = "Byte stores", .val = 0, .update = rvfi_tools_perfcount_cb_byte_stores};
    rvfi_performance_counters[22] = (rvfi_performance_counter_t) {.name = "Half-word (16 bits) stores", .val = 0, .update = rvfi_tools_perfcount_cb_halfword_stores};
    rvfi_performance_counters[23] = (rvfi_performance_counter_t) {.name = "Word stores", .val = 0, .update = rvfi_tools_perfcount_cb_word_stores};

    fclose(symbol_table_file);
    fclose(symbol_watchlist_file);

    return 0;

}

void rvfi_monitor_step(const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle) {  // TODO: Pass simulation time as argument, print messages with timestamp

    char disassembly_buffer[200];
    rv_decode decoded_instruction;  // rv_decode is defined in the Michael Clark riscv-dis library, this needs to be changed if libopcodes is used in the future

    // FIXME: This call will also need to change if libopcoes is used in the future
    if (en_profiler || en_tracer)
        decoded_instruction = disasm_inst(disassembly_buffer, 200, isa, (uint64_t) rvfi_trace->rvfi_pc_rdata, (rv_inst) rvfi_trace->rvfi_insn);

    if (en_tracer) {

        // "Cycle    PC    Instruction    Decoded Instruction    Operands and result

        fprintf(tracer_log_file, "%0d", current_clock_cycle);
        fprintf(tracer_log_file, "\t%0x", rvfi_trace->rvfi_pc_rdata);
        // fprintf(tracer_log_file, "\t%0x", (rvfi_trace->rvfi_insn & 0x3) ? rvfi_trace->rvfi_insn : rvfi_trace->rvfi_insn & 0xFFFF);

        // Writes the actual disassembled instruction from riscv-dis
        fprintf(tracer_log_file, "\t%s", disassembly_buffer);

        if (decoded_instruction.rs1)
            fprintf(tracer_log_file, " rs1=%s=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rs1_addr], rvfi_trace->rvfi_rs1_rdata);

        if (decoded_instruction.rs2)
            fprintf(tracer_log_file, " rs2=%s=<0x%dx>", rv_ireg_name_sym[rvfi_trace->rvfi_rs2_addr], rvfi_trace->rvfi_rs2_rdata);

        if (decoded_instruction.rd)
            fprintf(tracer_log_file, " rd=%s:=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rd_addr], rvfi_trace->rvfi_rd_wdata);

        if (rvfi_trace->rvfi_mem_rmask | rvfi_trace->rvfi_mem_wmask)
            fprintf(tracer_log_file, " addr <0x%x>", rvfi_trace->rvfi_mem_addr);

        if (rvfi_trace->rvfi_mem_rmask)
            fprintf(tracer_log_file, " data_from_mem <0x%x>", rvfi_trace->rvfi_mem_rdata);

        if (rvfi_trace->rvfi_mem_wmask)
            fprintf(tracer_log_file, " data_to_mem <0x%x>", rvfi_trace->rvfi_mem_wdata);

        // if (rvfi_trace->rvfi_pc_wdata != rvfi_trace->rvfi_pc_rdata + ((rvfi_trace->rvfi_pc_rdata & 0x3) ? 2 : 4)) {
        // if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + (((rvfi_trace->rvfi_pc_rdata & 0x3) == 0x3) ? 4 : 2))) {
        if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + inst_length(rvfi_trace->rvfi_insn))) {
        // if (decoded_instruction.op == rv_op_jal || decoded_instruction.op == rv_op_jalr || decoded_instruction.op == rv_op_j || decoded_instruction.op == rv_op_jr) {

            symbol_info_t* symbol = g_hash_table_lookup(symbol_table_hash_table, GINT_TO_POINTER(rvfi_trace->rvfi_pc_wdata));

            fprintf(tracer_log_file, " target_address <0x%x>", rvfi_trace->rvfi_pc_wdata);

            if (symbol != NULL)
                fprintf(tracer_log_file, " target_symbol <%s>", symbol->function_name);

        }

        fprintf(tracer_log_file, "\n");

    }

    if (en_profiler) {

        // Update virtual performance counter via callback functions
        for (int i = 0; i < RVFI_N_COUNTERS; i++)
           (rvfi_performance_counters[i].update)(&(rvfi_performance_counters[i]), rvfi_trace, current_clock_cycle, decoded_instruction);

        // Signal function entry/exit from symbol watchlist
        uint32_t current_pc = rvfi_trace->rvfi_pc_rdata;
        uint32_t next_pc = rvfi_trace->rvfi_pc_wdata;
        symbol_info_t* current_symbol = g_hash_table_lookup(symbol_table_hash_table, GINT_TO_POINTER(next_pc));

        uint32_t function_call = decoded_instruction.op == rv_op_jal || decoded_instruction.op == rv_op_jalr;

        if (function_call && current_symbol != NULL && current_symbol->is_function && current_symbol->is_watched) {

            printf("[RVFI_MONITOR] About to enter function <%s> at PC <0x%x> from PC <0x%x> at clock cycle <%0d>\n", current_symbol->function_name, next_pc, current_pc, current_clock_cycle);
            fprintf(profiler_log_file, "[RVFI_MONITOR] About to enter function <%s> at PC <0x%x> from PC <0x%x> at clock cycle <%0d>\n", current_symbol->function_name, next_pc, current_pc, current_clock_cycle);

            current_symbol->times_called += 1;
            g_array_append_val(current_symbol->start_cycles, current_clock_cycle);

            // TODO: Print counters now for debug, remove later
            for (int i = 0; i < RVFI_N_COUNTERS; i++)
                printf("[RVFI_MONITOR] \t%s: %d\n", rvfi_performance_counters[i].name, rvfi_performance_counters[i].val);

            last_counter_state.function_name = current_symbol->function_name;
            last_counter_state.start_pc = rvfi_trace->rvfi_pc_wdata;
            last_counter_state.ret_pc = rvfi_trace->rvfi_pc_rdata + inst_length(rvfi_trace->rvfi_insn);  // NOTE: inst_length() comes from the MJC disassembly library, this function must be brought to this source file if migrating to libopcodes
            last_counter_state.counters = malloc(RVFI_N_COUNTERS*sizeof(uint64_t));

            for (int i = 0; i < RVFI_N_COUNTERS; i++)
                last_counter_state.counters[i] = rvfi_performance_counters[i].val;

            counter_stack = g_array_append_val(counter_stack, last_counter_state);

        }

        if (counter_stack->len > 0 && next_pc == last_counter_state.ret_pc) {

            printf("[RVFI_MONITOR] About to return from function <%s> from PC <0x%x> to PC <0x%x> at clock cycle <%0d>\n", last_counter_state.function_name, current_pc, next_pc, current_clock_cycle);
            fprintf(profiler_log_file, "[RVFI_MONITOR] About to return from function <%s> from PC <0x%x> to PC <0x%x> at clock cycle <%0d>\n", last_counter_state.function_name, current_pc, next_pc, current_clock_cycle);

            current_symbol = g_hash_table_lookup(symbol_table_hash_table, GINT_TO_POINTER(last_counter_state.start_pc));

            g_array_append_val(current_symbol->end_cycles, current_clock_cycle);

            // Print out diff between virtual performance counters as they were in the moment of function entry and current state of counters (at function exit)
            for (int i = 0; i < RVFI_N_COUNTERS; i++)
                fprintf(profiler_log_file, "[RVFI_MONITOR] \t%s: %d\n", rvfi_performance_counters[i].name, rvfi_performance_counters[i].val - last_counter_state.counters[i]);

            free(last_counter_state.counters);
            last_counter_state = g_array_index(counter_stack, counter_info_t, counter_stack->len - 1);
            g_array_remove_index(counter_stack, counter_stack->len - 1);

        }

    }

}

void rvfi_monitor_final() {

    if (en_profiler) {

        printf("=============================================================\n");
        printf("[RVFI_MONITOR] Profiling summary\n");
        printf("FunctionName_TimesCalled | Start Cycle | End Cycle | # Cycles\n");
        printf("=============================================================\n");

        void _final_hash_table_iterator(gpointer key, gpointer value, gpointer user_data);

        g_hash_table_foreach(symbol_table_hash_table, (GHFunc) _final_hash_table_iterator, NULL);

    }

    // TODO: Free pointers, doesnt really matter because the simulation should be finished at this point

}

void _final_hash_table_iterator(gpointer key, gpointer value, gpointer user_data) {

    symbol_info_t *current_symbol = (symbol_info_t*) value;

    for (int i = 0; i < current_symbol->times_called; i++)
        printf("%s_%0d\t%d %d %d\n", current_symbol->function_name, i, g_array_index(current_symbol->start_cycles, uint64_t, i),
          g_array_index(current_symbol->end_cycles, uint64_t, i), g_array_index(current_symbol->end_cycles, uint64_t, i) - g_array_index(current_symbol->start_cycles, uint64_t, i));

}

void _debug_hash_table_iterator(gpointer key, gpointer value, gpointer user_data) {

    symbol_info_t *current_symbol = (symbol_info_t*) value;
    printf("Key: <0x%0x> Value: <%s>\n", GPOINTER_TO_INT(key), current_symbol->function_name);

}
