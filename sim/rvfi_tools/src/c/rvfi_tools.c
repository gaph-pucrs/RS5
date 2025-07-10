
#include "rvfi_tools.h"
#include "rvfi_callbacks.h"

rvfi_monitor_context* rvfi_monitor_init(char* monitor_prefix, char* elf_file_name, char* watchlist_file_name, char* output_dir, char* time_unit_suffix, unsigned long march, int max_retire, int en_tracer, int en_profiler, int en_checker) {

    printf("Initializing monitor [%s]\n", monitor_prefix);

    rvfi_monitor_context *ctx = malloc(sizeof(rvfi_monitor_context));

    ctx->monitor_prefix = malloc(100);
    strcpy(ctx->monitor_prefix, monitor_prefix);

    ctx->time_unit_suffix = time_unit_suffix;
    ctx->march = march;
    ctx->max_retire = max_retire;

    ctx->en_tracer = en_tracer;
    ctx->en_profiler = en_profiler;
    ctx->en_checker = en_checker;

    ctx->tracer_log_file_name = malloc(200);
    ctx->profiler_log_file_name = malloc(200);
    ctx->profiler_call_graph_file_name = malloc(200);
    // ctx->profiler_elf_file_name = malloc(200);
    // ctx->symbol_watchlist_file_name = malloc(200);

    ctx->output_dir = output_dir;

    snprintf(ctx->tracer_log_file_name, 200, "%s/%s_tracer_log.txt", output_dir, monitor_prefix);
    snprintf(ctx->profiler_log_file_name, 200, "%s/%s_profiler_log.txt", output_dir, monitor_prefix);
    snprintf(ctx->profiler_call_graph_file_name, 200, "%s/%s_profiler_call_graph.txt", output_dir, monitor_prefix);
    ctx->profiler_elf_file_name = elf_file_name;
    // snprintf(ctx->symbol_watchlist_file_name, 200, "%s_profiler_watchlist.txt", monitor_prefix);
    ctx->symbol_watchlist_file_name = watchlist_file_name;

    int has_watchlist = ctx->symbol_watchlist_file_name[0] != '\0';

    GArray *symbol_watchlist = NULL;
    symbol_watchlist = g_array_new(FALSE, FALSE, sizeof(char*));

    ctx->symbol_table_hash_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    ctx->counter_stack = g_ptr_array_new();

    call_info_t* dummy_info = malloc(sizeof(call_info_t));
    dummy_info->start_cycle = 0;
    dummy_info->end_cycle = 0;
    // dummy_info->function_name = "Root";
    dummy_info->function_name = "call_graph_root_node_dummy";
    // sprintf(dummy_info->function_name, "%s_call_graph_root_node", ctx->monitor_prefix);

    ctx->current_call_node = g_node_new(dummy_info);

    ctx->n_counters = 0;

    if (ctx->en_tracer) {

        ctx->tracer_log_file = fopen(ctx->tracer_log_file_name, "w");

        if (ctx->tracer_log_file == NULL) {
            printf("[%s] Cant open file <%s> in write mode\n", ctx->monitor_prefix, ctx->tracer_log_file_name);
            exit(1);
        }

        fprintf(ctx->tracer_log_file, "#    Time   Cycle   Order        PC      Insn  Decoded Instruction                     rd   rd data   rs1  rs1 data  rs2  rs2 data  to mem    from mem      addr    symbol\n");

    }

    if (ctx->en_profiler) {

        ctx->performance_counters = g_array_new(FALSE, FALSE, sizeof(rvfi_performance_counter_t));

        ctx->profiler_log_file = fopen(ctx->profiler_log_file_name, "w");

        if (ctx->profiler_log_file == NULL) {
            printf("[%s] Cant open file <%s> in write mode\n", ctx->monitor_prefix, ctx->profiler_log_file_name);
            exit(1);
        }

        ctx->profiler_call_graph_file = fopen(ctx->profiler_call_graph_file_name, "w");

        if (ctx->profiler_call_graph_file == NULL) {
            printf("[%s] Cant open file <%s> in write mode\n", ctx->monitor_prefix, ctx->profiler_call_graph_file_name);
            exit(1);
        }

        if (has_watchlist) {

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

    }

    // Parse ELF symbols into a hash table
    if (ctx->en_tracer || ctx->en_profiler) {

        bfd *abfd;
        char *target = "elf32-littleriscv";

        abfd = bfd_openr (ctx->profiler_elf_file_name, target);
        if (abfd == NULL) {
            printf("[%s] Cant open file <%s> in read mode\n", ctx->monitor_prefix, ctx->profiler_elf_file_name);
            exit(1);
        }
        char* matching;
        if (!bfd_check_format_matches (abfd, bfd_object, &matching)) {
            printf("[%s] Invalid ELF file <%s>\n", ctx->monitor_prefix, ctx->profiler_elf_file_name);
            exit(1);
        }

        long syms_size = bfd_get_symtab_upper_bound (abfd);

        asymbol** syms = (asymbol **) xmalloc (syms_size);

        int symcount = get_symtab(abfd, syms);
        asymbol *current;

        // Init disassembly info and opcode hashtable
        stream_state ss = {};

        disassemble_info disasm_info = {};
        init_disassemble_info(&disasm_info, &ss, NULL, dis_fprintf_styled);
        disasm_info.arch = bfd_arch_riscv;
        disasm_info.mach = bfd_mach_riscv32;
        disasm_info.read_memory_func = buffer_read_memory;
        disasm_info.print_address_func = print_address;

        ctx->disasm_info = disasm_info;

        init_hashtable();

        // Fill out symbol PC and name hash table
        for (int count = 0; count < symcount; count++) {

            current = syms[count];

            symbol_info_t* new_symbol = malloc(sizeof(symbol_info_t));
            uint32_t symbol_pc = aout_symbol(current)->addr & 0xffff;

            strcpy(new_symbol->function_name, current->name);

            if (!(current->flags & BSF_FUNCTION)) {
                free(new_symbol);
                continue;
            }

            // new_symbol->is_watched = 0;
            new_symbol->is_watched = has_watchlist ? 0 : 1;
            new_symbol->is_function = 1;
            new_symbol->times_called = 0;

            g_hash_table_insert(ctx->symbol_table_hash_table, GINT_TO_POINTER(symbol_pc), new_symbol);

            // Look for the current symbol in the watchlist array, tag it as watched if so
            // Note that this only tags symbols in the given symbol list, if there are symbols in the watchlist but not in the symbol list, NO ERROR OR WARNING WILL BE RETURNED
            // if (ctx->en_profiler) {
            if (ctx->en_profiler && has_watchlist) {

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

        // Loop through hash table, print all KV pairs
        printf("[%s] Parsed symbol table:\n", ctx->monitor_prefix);
        g_hash_table_foreach(ctx->symbol_table_hash_table, (GHFunc) _debug_hash_table_iterator, ctx);

        if (has_watchlist) {

            // If symbol_watchlist is not empty by now, print warning for each function still on the watchlist
            if (symbol_watchlist->len) {
                for (int i = 0; i < symbol_watchlist->len; i++) {
                    printf("[%s] WARNING: Symbol name <%s> given in the watchlist was not found in the symbol table\n", ctx->monitor_prefix, g_array_index(symbol_watchlist, char*, i));
                    free(g_array_index(symbol_watchlist, char*, i));
                }
            }

            // Free watchlist array, we dont needed anymore after the all symbols hash table was tagged in the inner loop above
            if (ctx->en_profiler) {
                g_array_free(symbol_watchlist, TRUE);
            }

            fclose(ctx->symbol_watchlist_file);

        }

    }

    return ctx;

}

void rvfi_monitor_add_counter(rvfi_monitor_context *ctx, rvfi_performance_counter_t ctr) {

    g_array_append_val(ctx->performance_counters, ctr);
    ctx->n_counters += 1;

}

// Add default virtual performance counters to context
void rvfi_monitor_add_default_performance_counters(rvfi_monitor_context *ctx) {

    printf("[%s] Adding default performance counters\n", ctx->monitor_prefix);

    void* clock_cycles_ctx = malloc(sizeof(uint64_t));
    *((uint64_t*) clock_cycles_ctx) = 0;

    void* idle_stall_cycles_ctx = malloc(sizeof(uint64_t));
    *((uint64_t*) idle_stall_cycles_ctx) = 0;

    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Clock cycles", .val = 0, .update = rvfi_tools_perfcount_cb_clock_cycles, .local_ctx = clock_cycles_ctx});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_insn_retired, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Compressed instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_cmprss_insn_retired, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Unknown instructions retired", .val = 0, .update = rvfi_tools_perfcount_cb_unknown_insn_retired, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Idle/stall cycles", .val = 0, .update = rvfi_tools_perfcount_cb_stall_cycles, .local_ctx = idle_stall_cycles_ctx});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Arithmetic operations", .val = 0, .update = rvfi_tools_perfcount_cb_arith, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Shift/rotate operations", .val = 0, .update = rvfi_tools_perfcount_cb_shift, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Bitwise operations", .val = 0, .update = rvfi_tools_perfcount_cb_bitwise, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Multiplication operations", .val = 0, .update = rvfi_tools_perfcount_cb_mult, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Division operations", .val = 0, .update = rvfi_tools_perfcount_cb_div, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Total jumps", .val = 0, .update = rvfi_tools_perfcount_cb_total_jumps, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Forward static jumps", .val = 0, .update = rvfi_tools_perfcount_cb_fwd_static_jumps, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Backward static jumps", .val = 0, .update = rvfi_tools_perfcount_cb_bwd_static_jumps, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Forward register jumps", .val = 0, .update = rvfi_tools_perfcount_cb_fwd_reg_jumps, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Backward register jumps", .val = 0, .update = rvfi_tools_perfcount_cb_bwd_reg_jumps, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Misaligned jumps", .val = 0, .update = rvfi_tools_perfcount_cb_misaligned_jumps, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Total branches", .val = 0, .update = rvfi_tools_perfcount_cb_total_branches, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Taken forward branches", .val = 0, .update = rvfi_tools_perfcount_cb_taken_fwd_branches, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Not-taken forward branches", .val = 0, .update = rvfi_tools_perfcount_cb_not_taken_fwd_branches, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Taken backward branches", .val = 0, .update = rvfi_tools_perfcount_cb_taken_bwd_branches, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Not-taken backward branches", .val = 0, .update = rvfi_tools_perfcount_cb_not_taken_bwd_branches, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Misaligned branches", .val = 0, .update = rvfi_tools_perfcount_cb_misaligned_branches, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Total loads", .val = 0, .update = rvfi_tools_perfcount_cb_total_loads, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Byte loads", .val = 0, .update = rvfi_tools_perfcount_cb_byte_loads, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Half-word (16 bits) loads", .val = 0, .update = rvfi_tools_perfcount_cb_halfword_loads, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Word loads", .val = 0, .update = rvfi_tools_perfcount_cb_word_loads, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Misaligned loads", .val = 0, .update = rvfi_tools_perfcount_cb_misaligned_loads, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Total stores", .val = 0, .update = rvfi_tools_perfcount_cb_total_stores, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Byte stores", .val = 0, .update = rvfi_tools_perfcount_cb_byte_stores, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Half-word (16 bits) stores", .val = 0, .update = rvfi_tools_perfcount_cb_halfword_stores, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Word stores", .val = 0, .update = rvfi_tools_perfcount_cb_word_stores, .local_ctx = NULL});
    rvfi_monitor_add_counter(ctx, (rvfi_performance_counter_t) {.name = "Misaligned stores", .val = 0, .update = rvfi_tools_perfcount_cb_misaligned_stores, .local_ctx = NULL});

}

void rvfi_monitor_push_counters_to_stack(rvfi_monitor_context *ctx, symbol_info_t *current_symbol, const rvfi_trace_t *rvfi_trace) {

    counter_info_t* current_counter_state = malloc(sizeof(counter_info_t));

    current_counter_state->function_name = current_symbol->function_name;
    current_counter_state->start_pc = rvfi_trace->rvfi_pc_wdata;
    current_counter_state->ret_pc =rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_insn);
    current_counter_state->counters = g_array_sized_new(FALSE, FALSE, sizeof(uint64_t), ctx->n_counters*sizeof(uint64_t));

    for (int i = 0; i < ctx->n_counters; i++) {
        rvfi_performance_counter_t perf_ctr = g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i);
        g_array_append_val(current_counter_state->counters, perf_ctr.val);
    }

    // g_array_append_val(ctx->counter_stack, *current_counter_state);
    g_ptr_array_add(ctx->counter_stack, current_counter_state);
    // ctx->counter_stack_top = current_counter_state;
    // printf("Pushed ctx->counter_stack_top = <%p>\n", ctx->counter_stack_top);
    // printf("ctx->counter_stack->len = <%d>\n", ctx->counter_stack->len);

}

void rvfi_monitor_step(rvfi_monitor_context *ctx, const rvfi_trace_t* rvfi_traces, uint64_t current_clock_cycle, char* time_string, double time_float) {

    for (int insn = 0; insn < ctx->max_retire; insn++) {

        char disassembly_buffer[200];
        const struct riscv_opcode* decoded_instruction;

        const rvfi_trace_t* rvfi_trace = &rvfi_traces[insn];

        // Skip current trace in no valid instruction has been retired this cycle
        if (!(rvfi_trace->rvfi_valid))
            continue;

        // Disassemble valid instruction with GCC/Binutils backend
        if (ctx->en_profiler || ctx->en_tracer)
            decoded_instruction = disasm_inst(disassembly_buffer, 200, &ctx->disasm_info, (uint64_t) rvfi_trace->rvfi_pc_rdata, rvfi_trace->rvfi_insn);

        // Write out current instruction information (PC, operands, jump symbol, ...) to tracer log file
        if (ctx->en_tracer) {

            // #    Time   Cycle   Order        PC      Insn  Decoded Instruction                     rd   rd data   rs1  rs1 data  rs2  rs2 data  to mem    from mem      addr    symbol

            fprintf(ctx->tracer_log_file, "%8s", time_string);
            fprintf(ctx->tracer_log_file, "%8d", current_clock_cycle);
            fprintf(ctx->tracer_log_file, "%8d", rvfi_trace->rvfi_order);
            fprintf(ctx->tracer_log_file, "  %8x", rvfi_trace->rvfi_pc_rdata);

            if (riscv_insn_length(rvfi_trace->rvfi_insn) == 4)
                fprintf(ctx->tracer_log_file, "  %08x", rvfi_trace->rvfi_insn);
            else
                fprintf(ctx->tracer_log_file, "      %04x", rvfi_trace->rvfi_insn & 0xFFFF);

            // Writes the actual disassembled instruction from riscv-dis
            fprintf(ctx->tracer_log_file, "  %-36s", disassembly_buffer);

            if (rvfi_trace->rvfi_rd_addr)
                // fprintf(ctx->tracer_log_file, " rd=%s:=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rd_addr], rvfi_trace->rvfi_rd_wdata);
                fprintf(ctx->tracer_log_file, "  %-3s  %-8x", rv_ireg_name_sym[rvfi_trace->rvfi_rd_addr], rvfi_trace->rvfi_rd_wdata);
            else
                fprintf(ctx->tracer_log_file, "               ");

            if (rvfi_trace->rvfi_rs1_addr)
                // fprintf(ctx->tracer_log_file, " rs1=%s=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rs1_addr], rvfi_trace->rvfi_rs1_rdata);
                fprintf(ctx->tracer_log_file, "  %-3s  %-8x", rv_ireg_name_sym[rvfi_trace->rvfi_rs1_addr], rvfi_trace->rvfi_rs1_rdata);
            else
                fprintf(ctx->tracer_log_file, "               ");

            if (rvfi_trace->rvfi_rs2_addr)
                // fprintf(ctx->tracer_log_file, " rs2=%s=<0x%x>", rv_ireg_name_sym[rvfi_trace->rvfi_rs2_addr], rvfi_trace->rvfi_rs2_rdata);
                fprintf(ctx->tracer_log_file, "  %-3s  %-8x", rv_ireg_name_sym[rvfi_trace->rvfi_rs2_addr], rvfi_trace->rvfi_rs2_rdata);
            else
                fprintf(ctx->tracer_log_file, "               ");

            if (rvfi_trace->rvfi_mem_rmask)
                fprintf(ctx->tracer_log_file, "  %8x", rvfi_trace->rvfi_mem_rdata);
            else
                fprintf(ctx->tracer_log_file, "          ");

            if (rvfi_trace->rvfi_mem_wmask)
                // fprintf(ctx->tracer_log_file, " data_to_mem <0x%x>", rvfi_trace->rvfi_mem_wdata);
                fprintf(ctx->tracer_log_file, "  %8x", rvfi_trace->rvfi_mem_wdata);
            else
                fprintf(ctx->tracer_log_file, "          ");

            if ((rvfi_trace->rvfi_mem_rmask | rvfi_trace->rvfi_mem_wmask) || rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_insn)))
                // fprintf(ctx->tracer_log_file, " addr <0x%x>", rvfi_trace->rvfi_mem_addr);

                if (rvfi_trace->rvfi_mem_rmask | rvfi_trace->rvfi_mem_wmask)
                    fprintf(ctx->tracer_log_file, "  %8x", rvfi_trace->rvfi_mem_addr);
                else
                    fprintf(ctx->tracer_log_file, "  %8x", rvfi_trace->rvfi_pc_wdata);

            else
                fprintf(ctx->tracer_log_file, "          ");


            if (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_insn))) {

                symbol_info_t* symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(rvfi_trace->rvfi_pc_wdata));

                // fprintf(ctx->tracer_log_file, " target_address <0x%x>", rvfi_trace->rvfi_pc_wdata);

                if (symbol != NULL)
                    // fprintf(ctx->tracer_log_file, " target_symbol <%s>", symbol->function_name);
                    fprintf(ctx->tracer_log_file, "  %s", symbol->function_name);

            }

            fprintf(ctx->tracer_log_file, "\n");

        }

        // Examine current instruction with respect to performance counters and function entry/exit events
        if (ctx->en_profiler) {

            // Update virtual performance counter via callback functions
            for (int i = 0; i < ctx->n_counters; i++) {
                rvfi_performance_counter_t* perf_ctr = &(g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i));
                (perf_ctr->update)(perf_ctr, rvfi_trace, current_clock_cycle, decoded_instruction, perf_ctr->local_ctx);
            }

            // Signal function entry/exit from symbol watchlist
            uint32_t current_pc = rvfi_trace->rvfi_pc_rdata;
            uint32_t next_pc = rvfi_trace->rvfi_pc_wdata;
            symbol_info_t* current_symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(next_pc));

            // TODO: (op->pinfo & INSN_TYPE) == INSN_JSR
            // int function_call = strcmp(decoded_instruction->name, "jal") == 0 || strcmp(decoded_instruction->name, "jalr") == 0;
            // int function_call = (op->pinfo & INSN_TYPE) == INSN_JSR;
            int function_call = (decoded_instruction->pinfo & INSN_JSR);
            // uint32_t control_flow_change = (rvfi_trace->rvfi_pc_wdata != (rvfi_trace->rvfi_pc_rdata + riscv_insn_length(rvfi_trace->rvfi_insn)));

            // Detect function entry event
            if (function_call && current_symbol != NULL && current_symbol->is_function && current_symbol->is_watched) {
            // if (control_flow_change && current_symbol != NULL && current_symbol->is_function && current_symbol->is_watched) {

                printf("[%s] About to start call <%s_%d> to PC <0x%x> from PC <0x%x> at clock cycle <%0d> simulation time <%s>\n", ctx->monitor_prefix, current_symbol->function_name, current_symbol->times_called, next_pc, current_pc, current_clock_cycle, time_string);
                fprintf(ctx->profiler_log_file, "[%s] About to start call <%s_%d> to PC <0x%x> from PC <0x%x> at clock cycle <%0d> simulation time <%s>\n", ctx->monitor_prefix, current_symbol->function_name, current_symbol->times_called, next_pc, current_pc, current_clock_cycle, time_string);

                // Print counters at function entry, might be useful for debug
                // for (int i = 0; i < ctx->n_counters; i++) {
                //     rvfi_performance_counter_t perf_ctr = g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i);
                //     printf("[%s] \t%s: %d\n", ctx->monitor_prefix, perf_ctr.name, perf_ctr.val);
                // }

                call_info_t* new_call_node_data = malloc(sizeof(call_info_t));
                GNode* new_call_node = g_node_new(new_call_node_data);

                new_call_node_data->function_name = current_symbol->function_name;
                new_call_node_data->call_id = current_symbol->times_called;
                new_call_node_data->start_cycle = current_clock_cycle;
                new_call_node_data->end_cycle = 0;
                new_call_node_data->start_time = time_float;
                // strncpy(new_call_node_data->start_time_string, time_string, 100);

                current_symbol->times_called += 1;

                // printf("New node function name: <%s>\n", ((call_info_t*) new_call_node->data)->function_name);

                g_node_insert(ctx->current_call_node, -1, new_call_node);
                ctx->current_call_node = new_call_node;

                rvfi_monitor_push_counters_to_stack(ctx, current_symbol, rvfi_trace);

            }

            // Detect function return event
            // if (ctx->counter_stack->len > 0 && next_pc == counter_stack_top->ret_pc) {
            if (ctx->counter_stack->len > 0) {

                counter_info_t* counter_stack_top = g_ptr_array_index(ctx->counter_stack, ctx->counter_stack->len - 1);

                if (next_pc == counter_stack_top->ret_pc) {

                    current_symbol = g_hash_table_lookup(ctx->symbol_table_hash_table, GINT_TO_POINTER(counter_stack_top->start_pc));

                    printf("[%s] About to return from call <%s_%d> from PC <0x%x> to PC <0x%x> at clock cycle <%0d> simulation time <%s>\n", ctx->monitor_prefix, counter_stack_top->function_name, ((call_info_t*) ctx->current_call_node->data)->call_id, current_pc, next_pc, current_clock_cycle, time_string);
                    fprintf(ctx->profiler_log_file, "[%s] About to return from call <%s_%d> from PC <0x%x> to PC <0x%x> at clock cycle <%0d> simulation time <%s>\n", ctx->monitor_prefix, counter_stack_top->function_name, ((call_info_t*) ctx->current_call_node->data)->call_id, current_pc, next_pc, current_clock_cycle, time_string);

                    // Print out diff between virtual performance counters as they were in the moment of function entry and current state of counters (at function exit)
                    for (int i = 0; i < ctx->n_counters; i++) {
                        rvfi_performance_counter_t current_ctr = g_array_index(ctx->performance_counters, rvfi_performance_counter_t, i);
                        uint64_t saved_ctr = g_array_index(counter_stack_top->counters, uint64_t, i);
                        fprintf(ctx->profiler_log_file, "[%s]   %s: %d\n", ctx->monitor_prefix, current_ctr.name, current_ctr.val - saved_ctr);
                    }

                    // Recover parent call graph node and set it as the current node
                    printf("Prev call graph node <%s_%d>\n", ((call_info_t*) ctx->current_call_node->data)->function_name, ((call_info_t*) ctx->current_call_node->data)->call_id);
                    ((call_info_t*) ctx->current_call_node->data)->end_cycle = current_clock_cycle;
                    ((call_info_t*) ctx->current_call_node->data)->end_time = time_float;
                    // strncpy(((call_info_t*) ctx->current_call_node->data)->end_time_string, time_string, 100);
                    ctx->current_call_node = ctx->current_call_node->parent;
                    printf("Updated call graph node <%s_%d>\n", ((call_info_t*) ctx->current_call_node->data)->function_name, ((call_info_t*) ctx->current_call_node->data)->call_id);

                    // Pop last counter state off the stack
                    g_ptr_array_remove_index(ctx->counter_stack, ctx->counter_stack->len - 1);
                    g_array_free(counter_stack_top->counters, TRUE);
                    free(counter_stack_top);
                    // printf("ctx->counter_stack->len = <%d>\n", ctx->counter_stack->len);
                    // printf("Current ctx->counter_stack_top before free = <%p>\n", ctx->counter_stack_top);

                    // if (ctx->counter_stack->len)
                    //     counter_stack_top = &g_array_index(ctx->counter_stack, counter_info_t, ctx->counter_stack->len - 1);

                }

            }

        }

    }

}

void rvfi_monitor_final(rvfi_monitor_context* ctx) {

    if (ctx->en_profiler) {

        fprintf(ctx->profiler_call_graph_file, "###################################################################################\n");
        fprintf(ctx->profiler_call_graph_file, "# [%s] Call graph for ELF: <%s>\n", ctx->monitor_prefix, ctx->profiler_elf_file_name);
        fprintf(ctx->profiler_call_graph_file, "# FunctionName_TimesCalled:                <Start Time, End Time, Total Time>\n");
        fprintf(ctx->profiler_call_graph_file, "###################################################################################\n");

        // void _final_hash_table_iterator(gpointer key, gpointer value, gpointer user_data);
        // g_hash_table_foreach(ctx->symbol_table_hash_table, (GHFunc) _final_hash_table_iterator, NULL);

        GNode* root_node = ctx->current_call_node;
        call_info_t* root_info;
        root_info = (call_info_t*) root_node->data;

        // TODO: Rewind tree back to root node in case simulation was stopped (e.g. with errors or signal from terminal) before a natural exit point was reached
        if (strcmp(root_info->function_name, "call_graph_root_node_dummy"))
            printf("[%s] ERROR: Unexpected call graph root node named %s\n", ctx->monitor_prefix, root_info->function_name);

        GNode* first_child_node = root_node->children;
        rvfi_monitor_print_call_graph(ctx, first_child_node, 0);

    }

    // TODO: Free pointers, doesnt really matter because the simulation should be finished at this point

}

void rvfi_monitor_print_call_graph(rvfi_monitor_context* ctx, GNode* call_node, int indent_level) {

    call_info_t* call_info;
    call_info = (call_info_t*) call_node->data;
    char indent_string[indent_level+1];

    for (int i = 0; i < indent_level; i++)
        indent_string[i] = '-';
    indent_string[indent_level] = '\0';

    char* name_and_call_id;
    asprintf(&name_and_call_id, "%s%s_%d:", indent_string, call_info->function_name, call_info->call_id);

    // fprintf(ctx->profiler_call_graph_file, "|%s%s_%d: Start Time <%.3f%s> End Time <%.3f%s> Total Time <%.3f%s>\n",
    fprintf(ctx->profiler_call_graph_file, "|%-40s <%.3f%s, %.3f%s, %.3f%s>\n",
        // indent_string, call_info->function_name, call_info->call_id, call_info->start_time, ctx->time_unit_suffix, call_info->end_time, ctx->time_unit_suffix, call_info->end_time - call_info->start_time, ctx->time_unit_suffix);
        name_and_call_id, call_info->start_time, ctx->time_unit_suffix, call_info->end_time, ctx->time_unit_suffix, call_info->end_time - call_info->start_time, ctx->time_unit_suffix);

    free(name_and_call_id);

    // Depth-first
    if (call_node->children != NULL)
        rvfi_monitor_print_call_graph(ctx, call_node->children, indent_level + 1);

    if (call_node->next != NULL)
        rvfi_monitor_print_call_graph(ctx, call_node->next, indent_level);

}

// void _final_hash_table_iterator(gpointer key, gpointer value, gpointer user_data) {

//     symbol_info_t *current_symbol = (symbol_info_t*) value;

//     for (int i = 0; i < current_symbol->times_called; i++)
//         printf("%s_%0d\t%d %d %d\n", current_symbol->function_name, i, g_array_index(current_symbol->start_cycles, uint64_t, i),
//           g_array_index(current_symbol->end_cycles, uint64_t, i), g_array_index(current_symbol->end_cycles, uint64_t, i) - g_array_index(current_symbol->start_cycles, uint64_t, i));

// }

void _debug_hash_table_iterator(gpointer key, gpointer value, gpointer user_data) {

    symbol_info_t *current_symbol = (symbol_info_t*) value;
    rvfi_monitor_context* ctx = (rvfi_monitor_context*) user_data;
    printf("[%s]   Key: <0x%0x> Value: <%s>\n", ctx->monitor_prefix, GPOINTER_TO_INT(key), current_symbol->function_name);

}
