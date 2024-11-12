
# XM-Sim Command File
# TOOL:	xmsim(64)	23.03-s003
#
#
# You can restore this configuration with:
#
#      xrun -f sim.xrun -access +rwc -input vmacc.tcl
#

set tcl_prompt1 {puts -nonewline "xcelium> "}
set tcl_prompt2 {puts -nonewline "> "}
set vlog_format %h
set vhdl_format %v
set real_precision 6
set display_unit auto
set time_unit module
set heap_garbage_size -200
set heap_garbage_time 0
set assert_report_level note
set assert_stop_level error
set autoscope yes
set assert_1164_warnings yes
set pack_assert_off {}
set severity_pack_assert_off {note warning}
set assert_output_stop_level failed
set tcl_debug_level 0
set relax_path_name 1
set vhdl_vcdmap XX01ZX01X
set intovf_severity_level ERROR
set probe_screen_format 0
set rangecnst_severity_level ERROR
set textio_severity_level ERROR
set vital_timing_checks_on 1
set vlog_code_show_force 0
set assert_count_attempts 1
set tcl_all64 false
set tcl_runerror_exit false
set assert_report_incompletes 0
set show_force 1
set force_reset_by_reinvoke 0
set tcl_relaxed_literal 0
set probe_exclude_patterns {}
set probe_packed_limit 4k
set probe_unpacked_limit 16k
set assert_internal_msg no
set svseed 1
set assert_reporting_mode 0
set vcd_compact_mode 0
alias . run
alias indago verisium
alias quit exit
database -open -shm -into waves.shm waves -default
probe -create -database waves testbench.dut.execute1.v_gen_on.vector.vectorALU1.accumulate_counter testbench.dut.execute1.v_gen_on.vector.vectorALU1.accumulate_instruction testbench.dut.execute1.v_gen_on.vector.vectorALU1.adder_carry testbench.dut.execute1.v_gen_on.vector.vectorALU1.clk testbench.dut.execute1.v_gen_on.vector.vectorALU1.current_state testbench.dut.execute1.v_gen_on.vector.vectorALU1.cycle_count testbench.dut.execute1.v_gen_on.vector.vectorALU1.cycle_count_r testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_enable testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_enable_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_enable_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_enable_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_result_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_result_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_result_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.div_signed testbench.dut.execute1.v_gen_on.vector.vectorALU1.ended_acc testbench.dut.execute1.v_gen_on.vector.vectorALU1.equal_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.equal_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.equal_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.first_operand testbench.dut.execute1.v_gen_on.vector.vectorALU1.first_operand_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.first_operand_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.first_operand_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.greater_than_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.greater_than_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.greater_than_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.greater_than_signed_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.greater_than_signed_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.greater_than_signed_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_accumulation_o testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_div testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_div_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_div_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_div_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_mult testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_mult_int testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_o testbench.dut.execute1.v_gen_on.vector.vectorALU1.hold_widening_o testbench.dut.execute1.v_gen_on.vector.vectorALU1.mask_instruction testbench.dut.execute1.v_gen_on.vector.vectorALU1.mask_sew8 testbench.dut.execute1.v_gen_on.vector.vectorALU1.mask_sew16 testbench.dut.execute1.v_gen_on.vector.vectorALU1.mask_sew32 testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_enable testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_low testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_op_a_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_op_a_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_op_b_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_op_b_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_result_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_result_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_result_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.mult_signed_mode testbench.dut.execute1.v_gen_on.vector.vectorALU1.rem_result_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.rem_result_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.rem_result_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.reset_n testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_add testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_add_bytes testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_and testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_comparison_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_comparison_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_comparison_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_div testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_mask_o testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_max testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_maxu testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_merge testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_min testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_minu testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_mult testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_mult_r testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_o testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_or testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redand testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redmax testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redmaxu testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redmin testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redminu testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redor testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redsum testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_redxor testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_rem testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_sll testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_sra testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_srl testbench.dut.execute1.v_gen_on.vector.vectorALU1.result_xor testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand_reductions_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand_reductions_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.second_operand_reductions_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.subtraend testbench.dut.execute1.v_gen_on.vector.vectorALU1.subtraend_8b testbench.dut.execute1.v_gen_on.vector.vectorALU1.subtraend_16b testbench.dut.execute1.v_gen_on.vector.vectorALU1.subtraend_32b testbench.dut.execute1.v_gen_on.vector.vectorALU1.subtraend_neg testbench.dut.execute1.v_gen_on.vector.vectorALU1.summand_1 testbench.dut.execute1.v_gen_on.vector.vectorALU1.summand_2 testbench.dut.execute1.v_gen_on.vector.vectorALU1.summand_2_int testbench.dut.execute1.v_gen_on.vector.vectorALU1.vector_operation_i testbench.dut.execute1.v_gen_on.vector.vectorALU1.vl testbench.dut.execute1.v_gen_on.vector.vectorALU1.vlmul testbench.dut.execute1.v_gen_on.vector.vectorALU1.vm testbench.dut.execute1.v_gen_on.vector.vectorALU1.vsew testbench.dut.execute1.v_gen_on.vector.vectorALU1.widening_counter testbench.dut.execute1.v_gen_on.vector.vectorALU1.widening_instruction
probe -create -database waves testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.clk testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.enable testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.reset_n testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.result testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.v0_mask testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.vd_addr testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.vs1_addr testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.vs1_data testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.vs2_addr testbench.dut.execute1.v_gen_on.vector.vectorRegbank1.vs2_data
probe -create -database waves testbench.dut.execute1.v_gen_on.vector.vl_curr_reg

simvision -input vmacc.tcl.svcf
