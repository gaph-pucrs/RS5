
#include "rvfi_tools.h"
#include "rvfi_callbacks.h"

rvfi_monitor_context* rvfi_monitor_init(char* monitor_prefix, unsigned long march, int en_tracer, int en_profiler, int en_checker, char* tracer_log_file_name, char* profiler_log_file_name, char* symbol_table_file_name, char* symbol_watchlist_file_name) {

    rvfi_monitor_context *ctx = malloc(sizeof(rvfi_monitor_context));

    ctx->monitor_prefix = malloc(100);
    strcpy(ctx->monitor_prefix, monitor_prefix);

    ctx->march = march;

    ctx->en_tracer = en_tracer;
    ctx->en_profiler = en_profiler;
    ctx->en_checker = en_checker;

    ctx->tracer_log_file_name = tracer_log_file_name;
    ctx->profiler_log_file_name = profiler_log_file_name;
    ctx->symbol_table_file_name = symbol_table_file_name;
    ctx->symbol_watchlist_file_name = symbol_watchlist_file_name;

    GArray *symbol_watchlist = NULL;
    symbol_watchlist = g_array_new(FALSE, FALSE, sizeof(char*));

    ctx->symbol_table_hash_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    ctx->counter_stack = g_array_new(FALSE, FALSE, sizeof(counter_info_t));

    ctx->n_counters = 0;

    if (ctx->en_tracer) {

        ctx->tracer_log_file = fopen(ctx->tracer_log_file_name, "w");

        if (ctx->tracer_log_file == NULL) {
            printf("[%s] Cant open file <%s> in write mode\n", ctx->monitor_prefix, ctx->tracer_log_file_name);
            exit(1);
        }

        fprintf(ctx->tracer_log_file, "Cycle\tPC\tInstruction\tDecoded Instruction\tOperands and result\n");

    }

    if (ctx->en_profiler) {

        printf("Init ctx->performance_counters\n");
        ctx->performance_counters = g_array_new(FALSE, FALSE, sizeof(rvfi_performance_counter_t));
        printf("Init ctx->performance_counters = %d\n", ctx->performance_counters);
        // ctx->last_counter_state = malloc(sizeof(counter_info_t));
        ctx->last_counter_state.counters = g_array_new(FALSE, FALSE, sizeof(uint64_t));

        ctx->profiler_log_file = fopen(ctx->profiler_log_file_name, "w");

        if (ctx->profiler_log_file == NULL) {
            printf("[%s] Cant open file <%s> in write mode\n", ctx->monitor_prefix, ctx->profiler_log_file_name);
            exit(1);
        }

        ctx->symbol_watchlist_file = fopen(ctx->symbol_watchlist_file_name, "r");

        if (ctx->symbol_watchlist_file == NULL) {
            printf("[%s] Cant open file <%s> in read mode\n", ctx->monitor_prefix, ctx->symbol_watchlist_file_name);
            exit(1);
        }

        // Fill out watch symbol_watchlist
        while (1) {

            char* watched_symbol = malloc(100);

            // Parse line containing a single symbol name per line
            if (fscanf(ctx->symbol_watchlist_file, "%s", watched_symbol) == EOF)
                break;

            // This allows for comments in the watchlist file
            if (watched_symbol[0] != '#') {
                // printf("[%s] Adding function <%s> to watchlist>\n", ctx->monitor_prefix, watched_symbol);
                // arrput(symbol_watchlist, watched_symbol);
                g_array_append_val(symbol_watchlist, watched_symbol);
                // printf("%s\n", arrlast(symbol_watchlist));
            }

        }

    }

    // Parse ELF symbols into 2 hash tables, one containing all symbol name and PC and another containing the names of watched symbols
    if (ctx->en_tracer || ctx->en_profiler) {

        // ctx->symbol_table_file = fopen(ctx->symbol_table_file_name, "r");

        // if (ctx->symbol_table_file == NULL) {
        //     printf("[%s] Cant open file <%s> in read mode\n", ctx->monitor_prefix, ctx->symbol_table_file_name);
        //     exit(1);
        // }

        bfd *abfd;
        char *target = "elf32-littleriscv";
        
        abfd = bfd_openr (ctx->symbol_table_file_name, target);
        if (abfd == NULL) {
            printf("[%s] Cant open file <%s> in read mode\n", ctx->monitor_prefix, ctx->symbol_table_file_name);
            exit(1);
        }
        char* matching;
        if (!bfd_check_format_matches (abfd, bfd_object, &matching)) {
            printf("[%s] Invalid ELF file <%s>\n", ctx->monitor_prefix, ctx->symbol_table_file_name);
            exit(1);
        }

        long syms_size = bfd_get_symtab_upper_bound (abfd);

        asymbol** syms = (asymbol **) xmalloc (syms_size);

        int symcount = get_symtab(abfd, syms);
        asymbol *current;

        // for (int count = 0; count < symcount; count++) {
        //     current = syms[count];
        //     const char *section_name = current->section->name;
            
        //     printf ("%s %s %c",
        //     section_name,
        //     current->name,
        //     (current->flags & BSF_DEBUGGING) ? 'D' : 'F');
        //     // if (current->name)
        //     //   printf(" %s", current->name);
        //     printf("\n");
        // }

        // Fill out symbol PC and name hash table
        for (int count = 0; count < symcount; count++) {

            current = syms[count];

            symbol_info_t* new_symbol = malloc(sizeof(symbol_info_t));
            uint32_t symbol_pc = aout_symbol(current)->addr & 0xffff;

            // if (fscanf(ctx->symbol_table_file, "%x %c %s", &symbol_pc, &symbol_type, new_symbol->function_name) == EOF)
            //     break;

            strcpy(new_symbol->function_name, current->name);

            if (current->flags & BSF_DEBUGGING)
                continue;

            new_symbol->is_watched = 0;
            new_symbol->is_function = true; // TODO: identify if it's a function with bfd flags
            new_symbol->times_called = 0;
            new_symbol->start_cycles = g_array_new(FALSE, FALSE, sizeof(uint64_t));
            new_symbol->end_cycles = g_array_new(FALSE, FALSE, sizeof(uint64_t));

            // g_hash_table_insert(symbol_table_hash_table, &symbol_pc, new_symbol);
            g_hash_table_insert(ctx->symbol_table_hash_table, GINT_TO_POINTER(symbol_pc), new_symbol);

            uint32_t new_pc = symbol_pc;
            symbol_info_t* temp_symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(new_pc));
            if (new_symbol == NULL)
                printf("NULL\n");
            else
                printf("Correctly added key <%d> value <%s> to hash table\n", new_pc, temp_symbol->function_name);

            // Look for the current symbol in the watchlist array, tag it as watched if so
            // Note that this only tags symbols in the given symbol list, if there are symbols in the watchlist but not in the symbol list, NO ERROR OR WARNING WILL BE RETURNED
            if (ctx->en_profiler) {

                // for (int i = 0; i < arrlen(symbol_watchlist); i++)
                for (int i = 0; i < symbol_watchlist->len; i++)
                    if (strncmp(g_array_index(symbol_watchlist, char*, i), new_symbol->function_name, 100) == 0) {

                        new_symbol->is_watched = 1;

                        printf("[%s] Adding function <%s> to watchlist\n", ctx->monitor_prefix, new_symbol->function_name);

                        free(g_array_index(symbol_watchlist, char*, i));
                        symbol_watchlist = g_array_remove_index_fast(symbol_watchlist, i);  // Overwrite current element (not needed anymore) with last element

                        break;
                    }

            }

        }

        // Loop through hash tablke, print all KV pairs
        void _debug_hash_table_iterator(gpointer key, gpointer value, gpointer user_data);
        g_hash_table_foreach(ctx->symbol_table_hash_table, (GHFunc) _debug_hash_table_iterator, NULL);

        // Free watchlist array, we dont needed anymore after the all symbols hash table was tagged in the inner loop above
        if (ctx->en_profiler) {
            g_array_free(symbol_watchlist, FALSE);
        }

    }

    //fclose(ctx->symbol_table_file);
    fclose(ctx->symbol_watchlist_file);

    return ctx;

}

void rvfi_monitor_add_counter(rvfi_monitor_context *ctx, rvfi_performance_counter_t ctr) {

    // printf("Using ctx->performance_counters = %d\n", ctx->performance_counters);
    g_array_append_val(ctx->performance_counters, ctr);
    ctx->n_counters += 1;

}

// Add default virtual performance counters to context
void rvfi_monitor_add_default_performance_counters(rvfi_monitor_context *ctx) {

    // printf("Adding counters\n");
    // printf("Using ctx = %d\n", ctx);

    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Clock cycles", .val = 0, .update = rvfi_tools_perfcount_cb_clock_cycles});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_insn_retired});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Compressed instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_cmprss_insn_retired});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Unidentified instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_unkwown_insn_retired});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Idle/stall cycles", .val = 0, .update = rvfi_tools_perfcount_cb_stall_cycles});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Arithmetic operations", .val = 0, .update = rvfi_tools_perfcount_cb_arith});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Shift/rotate operations", .val = 0, .update = rvfi_tools_perfcount_cb_shift});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Bitwise operations", .val = 0, .update = rvfi_tools_perfcount_cb_bitwise});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Multiplication operations", .val = 0, .update = rvfi_tools_perfcount_cb_mult});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Division operations", .val = 0, .update = rvfi_tools_perfcount_cb_div});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Forward static jumps", .val = 0, .update = rvfi_tools_perfcount_cb_fwd_static_jumps});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Backward static jumps", .val = 0, .update = rvfi_tools_perfcount_cb_bwd_static_jumps});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Forward register jumps", .val = 0, .update = rvfi_tools_perfcount_cb_fwd_reg_jumps});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Backward register jumps", .val = 0, .update = rvfi_tools_perfcount_cb_bwd_reg_jumps});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Taken forward branches", .val = 0, .update = rvfi_tools_perfcount_cb_taken_fwd_branches});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Not-taken forward branches", .val = 0, .update = rvfi_tools_perfcount_cb_not_taken_fwd_branches});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Taken backward branches", .val = 0, .update = rvfi_tools_perfcount_cb_taken_bwd_branches});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Not-taken backward branches", .val = 0, .update = rvfi_tools_perfcount_cb_not_taken_bwd_branches});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Byte loads", .val = 0, .update = rvfi_tools_perfcount_cb_byte_loads});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Half-word (16 bits) loads", .val = 0, .update = rvfi_tools_perfcount_cb_halfword_loads});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Word loads", .val = 0, .update = rvfi_tools_perfcount_cb_word_loads});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Byte stores", .val = 0, .update = rvfi_tools_perfcount_cb_byte_stores});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Half-word (16 bits) stores", .val = 0, .update = rvfi_tools_perfcount_cb_halfword_stores});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Word stores", .val = 0, .update = rvfi_tools_perfcount_cb_word_stores});

    // printf("Finish adding counters\n");

}

void rvfi_monitor_push_counters_to_stack(rvfi_monitor_context *ctx, symbol_info_t *current_symbol, const rvfi_trace_t *rvfi_trace) {

    ctx->last_counter_state.function_name = current_symbol->function_name;
    ctx->last_counter_state.start_pc = rvfi_trace->rvfi_pc_wdata;
    ctx->last_counter_state.ret_pc = rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_insn);
    // ctx->last_counter_state->counters = malloc(RVFI_N_COUNTERS*sizeof(uint64_t));

    g_array_free(ctx->last_counter_state.counters, FALSE);
    ctx->last_counter_state.counters = g_array_sized_new(FALSE, FALSE, sizeof(uint64_t), ctx->n_counters*sizeof(uint64_t));
    // g_array_set_size(ctx->last_counter_state.counters, ctx->n_counters*sizeof(uint64_t));

    for (int i = 0; i < ctx->n_counters; i++) {
        rvfi_performance_counter_t perf_ctr = g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i);
        g_array_append_val(ctx->last_counter_state.counters, perf_ctr.val);
    }

}

void rvfi_monitor_step(rvfi_monitor_context *ctx, const rvfi_trace_t *rvfi_trace, uint64_t current_clock_cycle) {  // TODO: Pass simulation time as argument, print messages with timestamp

    char disassembly_buffer[200];
    const struct riscv_opcode* decoded_instruction;  
    // FIXME: This call will also need to change if libopcoes is used in the future
    if (ctx->en_profiler || ctx->en_tracer)
        decoded_instruction = disasm_inst(disassembly_buffer, 200, (uint64_t) rvfi_trace->rvfi_pc_rdata, rvfi_trace->rvfi_insn);

    if (ctx->en_tracer) {

        // "Cycle    PC    Instruction    Decoded Instruction    Operands and result

        fprintf(ctx->tracer_log_file, "%0d", current_clock_cycle);
        fprintf(ctx->tracer_log_file, "\t%0x", rvfi_trace->rvfi_pc_rdata);

        if (riscv_insn_length(rvfi_trace->rvfi_insn) == 4) 
            fprintf(ctx->tracer_log_file, "\t%08x", rvfi_trace->rvfi_insn);
        else
            fprintf(ctx->tracer_log_file, "\t%04x    ", rvfi_trace->rvfi_insn & 0xFFFF);

        // Writes the actual disassembled instruction from riscv-dis
        fprintf(ctx->tracer_log_file, "\t%s", disassembly_buffer);

        if (rvfi_trace->rvfi_rs1_addr)
            fprintf(ctx->tracer_log_file, " rs1=%s=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rs1_addr], rvfi_trace->rvfi_rs1_rdata);

        if (rvfi_trace->rvfi_rs2_addr)
            fprintf(ctx->tracer_log_file, " rs2=%s=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rs2_addr], rvfi_trace->rvfi_rs2_rdata);

        if (rvfi_trace->rvfi_rd_addr)
            fprintf(ctx->tracer_log_file, " rd=%s:=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rd_addr], rvfi_trace->rvfi_rd_wdata);

        if (rvfi_trace->rvfi_mem_rmask | rvfi_trace->rvfi_mem_wmask)
            fprintf(ctx->tracer_log_file, " addr <0x%x>", rvfi_trace->rvfi_mem_addr);

        if (rvfi_trace->rvfi_mem_rmask)
            fprintf(ctx->tracer_log_file, " data_from_mem <0x%x>", rvfi_trace->rvfi_mem_rdata);

        if (rvfi_trace->rvfi_mem_wmask)
            fprintf(ctx->tracer_log_file, " data_to_mem <0x%x>", rvfi_trace->rvfi_mem_wdata);

        if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_insn))) {

            symbol_info_t* symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(rvfi_trace->rvfi_pc_wdata));

            fprintf(ctx->tracer_log_file, " target_address <0x%x>", rvfi_trace->rvfi_pc_wdata);

            if (symbol != NULL)
                fprintf(ctx->tracer_log_file, " target_symbol <%s>", symbol->function_name);

        }

        fprintf(ctx->tracer_log_file, "\n");

    }

    if (ctx->en_profiler) {

        // Update virtual performance counter via callback functions
        // for (int i = 0; i < RVFI_N_COUNTERS; i++)
        //    (rvfi_performance_counters[i].update)(&(rvfi_performance_counters[i]), rvfi_trace, current_clock_cycle, decoded_instruction);
        for (int i = 0; i < ctx->n_counters; i++) {
            rvfi_performance_counter_t* perf_ctr = &(g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i));
           (perf_ctr->update)(perf_ctr, rvfi_trace, current_clock_cycle, decoded_instruction);
        }

        // Signal function entry/exit from symbol watchlist
        uint32_t current_pc = rvfi_trace->rvfi_pc_rdata;
        uint32_t next_pc = rvfi_trace->rvfi_pc_wdata;
        symbol_info_t* current_symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(next_pc));

        uint32_t function_call = decoded_instruction->match == MATCH_JAL || decoded_instruction->match == MATCH_JALR;

        if (function_call && current_symbol != NULL && current_symbol->is_function && current_symbol->is_watched) {

            printf("[%s] About to enter function <%s> at PC <0x%x> from PC <0x%x> at clock cycle <%0d>\n", ctx->monitor_prefix, current_symbol->function_name, next_pc, current_pc, current_clock_cycle);
            fprintf(ctx->profiler_log_file, "[%s] About to enter function <%s> at PC <0x%x> from PC <0x%x> at clock cycle <%0d>\n", ctx->monitor_prefix, current_symbol->function_name, next_pc, current_pc, current_clock_cycle);

            // TODO: Start VCD dump

            current_symbol->times_called += 1;
            g_array_append_val(current_symbol->start_cycles, current_clock_cycle);

            // TODO: Print counters now for debug, remove later
            // for (int i = 0; i < RVFI_N_COUNTERS; i++)
            //     printf("[%s] \t%s: %d\n", rvfi_performance_counters[i].name, ctx->monitor_prefix, rvfi_performance_counters[i].val);
            for (int i = 0; i < ctx->n_counters; i++) {
                rvfi_performance_counter_t perf_ctr = g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i);
                printf("[%s] \t%s: %d\n", ctx->monitor_prefix, perf_ctr.name, perf_ctr.val);
            }

            // ctx->last_counter_state.function_name = current_symbol->function_name;
            // ctx->last_counter_state.start_pc = rvfi_trace->rvfi_pc_wdata;
            // ctx->last_counter_state.ret_pc = rvfi_trace->rvfi_pc_rdata + inst_length(rvfi_trace->rvfi_insn);  // NOTE: inst_length() comes from the MJC disassembly library, this function must be brought to this source file if migrating to libopcodes
            // ctx->last_counter_state->counters = malloc(RVFI_N_COUNTERS*sizeof(uint64_t));

            rvfi_monitor_push_counters_to_stack(ctx, current_symbol, rvfi_trace);

            // for (int i = 0; i < RVFI_N_COUNTERS; i++)
            //     last_counter_state.counters[i] = rvfi_performance_counters[i].val;

            // counter_stack = g_array_append_val(ctx->counter_stack, last_counter_state);
            g_array_append_val(ctx->counter_stack, ctx->last_counter_state);

        }

        if (ctx->counter_stack->len > 0 && next_pc == ctx->last_counter_state.ret_pc) {

            printf("[%s] About to return from function <%s> from PC <0x%x> to PC <0x%x> at clock cycle <%0d>\n", ctx->monitor_prefix, ctx->last_counter_state.function_name, current_pc, next_pc, current_clock_cycle);
            fprintf(ctx->profiler_log_file, "[%s] About to return from function <%s> from PC <0x%x> to PC <0x%x> at clock cycle <%0d>\n", ctx->monitor_prefix, ctx->last_counter_state.function_name, current_pc, next_pc, current_clock_cycle);

            // TODO: End VCD dump

            current_symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(ctx->last_counter_state.start_pc));

            g_array_append_val(current_symbol->end_cycles, current_clock_cycle);

            // Print out diff between virtual performance counters as they were in the moment of function entry and current state of counters (at function exit)
            // for (int i = 0; i < RVFI_N_COUNTERS; i++)
            //     fprintf(ctx->profiler_log_file, "[%s] \t%s: %d\n", ctx->monitor_prefix, rvfi_performance_counters[i].name, rvfi_performance_counters[i].val - last_counter_state.counters[i]);
            for (int i = 0; i < ctx->n_counters; i++) {
                rvfi_performance_counter_t current_ctr = g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i);
                uint64_t saved_ctr = g_array_index(ctx->last_counter_state.counters, uint64_t, i);
                fprintf(ctx->profiler_log_file, "[%s] \t%s: %d\n", ctx->monitor_prefix, current_ctr.name, current_ctr.val - saved_ctr);
            }

            // TODO: g_array_free(array, TRUE)
            // free(ctx->last_counter_state.counters);
            g_array_free(ctx->last_counter_state.counters, FALSE);
            ctx->last_counter_state = g_array_index(ctx->counter_stack, counter_info_t, ctx->counter_stack->len - 1);
            g_array_remove_index(ctx->counter_stack, ctx->counter_stack->len - 1);

        }

    }

}

void rvfi_monitor_final(rvfi_monitor_context* ctx) {

    if (ctx->en_profiler) {

        printf("=============================================================\n");
        printf("[%s] Profiling summary\n", ctx->monitor_prefix);
        printf("FunctionName_TimesCalled | Start Cycle | End Cycle | # Cycles\n");
        printf("=============================================================\n");

        void _final_hash_table_iterator(gpointer key, gpointer value, gpointer user_data);

        g_hash_table_foreach(ctx->symbol_table_hash_table, (GHFunc) _final_hash_table_iterator, NULL);

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
