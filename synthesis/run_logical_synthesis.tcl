set OUT_FILES ./results


###############################################################################
# Setup
###############################################################################
set TOP_MODULE RS5


###############################################################################
# Custom FLOW
###############################################################################
set load_pdk                  1
set tool_config               1
set clock_gating              1
set load_hdl                  1
set elaborate                 1
set synthesis                 1
set save_reports              1
set write_netlist             1
set export_innovus            1
set stop                      0


###############################################################################

if { $load_pdk == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Load the pdk using MMMC"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	# Multi-Mode Multi-Corner (MMMC)

	read_mmmc "scripts/mmmc_tsmc_28_bv.tcl"

}



if { $tool_config == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Configuration of the Genus"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	set_multi_cpu_usage -local_cpu 8
	# set_db super_thread_servers "localhost"

	set_db lp_default_probability 0.5
	# set_db lp_default_toggle_rate [expr 0.5 * double(1000) / ${period_clk}] --RETIRAR

	### Tool effort, default is mediun
	set_db syn_global_effort high
	#set_db syn_generic_effort high
	#set_db syn_map_effort high
	#set_db syn_opt_effort high

	### keep hierarchy
	set_db auto_ungroup none

	### Set PLE (Generates a set of load values, which were obtained from the physical layout..
	# estimator (PLE) or wire-load model, for all the nets in the specified design)
	set_db interconnect_mode ple

	### controls the verbosity of the tool
	set_db information_level 9

	### Avoid proceeding with latche inference
	set_db hdl_error_on_latch true
	# foreach latchInst [all des seqs -level_sensitive] { puts "[vname $latchInst]" }

}


if { $clock_gating == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Control Clock Gating "
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	set_db lp_insert_clock_gating true

}


if { $load_hdl == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Load hdl files"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	read_hdl -define SYNTH -sv "../rtl/RS5_pkg.sv 						\
				 #../rtl/aes/riscv_crypto_sbox_aes_out.sv 	\
				 #../rtl/aes/riscv_crypto_sbox_aes_top.sv 	\
				 #../rtl/aes/riscv_crypto_sbox_inv_mid.sv 	\
				 #../rtl/aes/riscv_crypto_aes_fwd_sbox.sv 	\
				 #../rtl/aes_unit.sv 						\
				 #../rtl/align.sv 	 						\
				 #../rtl/decompresser.sv 					\
				  ../rtl/fetch.sv 							\
 				  ../rtl/decode.sv 							\
 				  ../rtl/div.sv 							\
 				  ../rtl/mul.sv 							\
 				  ../rtl/mulNbits.sv						\
 				  ../rtl/vectorALU.sv						\
 				  ../rtl/vectorCSRs.sv						\
 				  ../rtl/vectorLSU.sv						\
 				  ../rtl/vectorRegbank.sv  					\
 				  ../rtl/vectorUnit.sv						\
 				  ../rtl/execute.sv 						\
				 #../rtl/mmu.sv 							\
 				  ../rtl/retire.sv 							\
 				  ../rtl/regbank.sv 						\
 				  ../rtl/CSRBank.sv 						\
 				  ../rtl/RS5.sv"

}


if { $elaborate == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Elaboration"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	elaborate ${TOP_MODULE}

	# Applying the constraints
	init_design

	### The following example shows how to set max_fanout attribute for all input ports
	# this has already been defined in the constraints file
	# set_db [get_ports -filter direction==in] .max_fanout 1

}



if { $synthesis == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Synthesis - mapping and optimization"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	# init_design
	#syn_generic

	#syn_map

	#syn_opt

	syn_generic -create_floorplan -physical
	syn_map -physical
	syn_opt

}



if { $save_reports == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Write Reports"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	# Reports clock-gating information for the design
	report_clock_gating > ${OUT_FILES}/reports/${TOP_MODULE}_clock_gating.rpt

	# Returns the physical layout estimation (ple) information for the specified design
	report_ple > ${OUT_FILES}/reports/${TOP_MODULE}_ple.rpt

	# Report area
	report_gates > ${OUT_FILES}/reports/${TOP_MODULE}_gates.rpt
	report_area >  ${OUT_FILES}/reports/${TOP_MODULE}_area.rpt

	### report timing and power
	###################################
	set CURRENT_VIEW analysis_view_0p81v_125c_capwst_slowest
	set_analysis_view -setup ${CURRENT_VIEW}  -hold ${CURRENT_VIEW}
	report_timing > ${OUT_FILES}/reports/${TOP_MODULE}_timing_setup_${CURRENT_VIEW}.rpt
	#---
	report_power -unit mW > ${OUT_FILES}/reports/${TOP_MODULE}_power_${CURRENT_VIEW}.rpt

	##################################
	set CURRENT_VIEW analysis_view_0p90v_25c_captyp_nominal
	set_analysis_view -setup ${CURRENT_VIEW}  -hold ${CURRENT_VIEW}
	report_timing > ${OUT_FILES}/reports/${TOP_MODULE}_timing_setup_${CURRENT_VIEW}.rpt
	#---
	report_power -unit mW > ${OUT_FILES}/reports/${TOP_MODULE}_power_${CURRENT_VIEW}.rpt

	# ###################################
	set CURRENT_VIEW analysis_view_0p99v_m40c_capbst_fastest
	set_analysis_view -setup ${CURRENT_VIEW}  -hold ${CURRENT_VIEW}
	report_timing > ${OUT_FILES}/reports/${TOP_MODULE}_timing_setup_${CURRENT_VIEW}.rpt
	#---
	report_power -unit mW > ${OUT_FILES}/reports/${TOP_MODULE}_power_${CURRENT_VIEW}.rpt


	### Report timming -unconstrained amd -verbose
	report timing -lint -verbose > ${OUT_FILES}/reports/${TOP_MODULE}_timing_setup_${CURRENT_VIEW}_verbose.rpt
	report_timing -unconstrained > ${OUT_FILES}/reports/${TOP_MODULE}_timing_setup_${CURRENT_VIEW}_verbose_unconstrained.rpt

}


if { $write_netlist == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Write netlist"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	write_hdl > ${OUT_FILES}/gate_level/${TOP_MODULE}_logic_mapped.v

	## nominal
	set CURRENT_VIEW analysis_view_0p81v_125c_capwst_slowest
	set_analysis_view -setup ${CURRENT_VIEW} -hold ${CURRENT_VIEW}
	write_sdf > ${OUT_FILES}/gate_level/${TOP_MODULE}_${CURRENT_VIEW}.sdf

	## worst setup
	set CURRENT_VIEW analysis_view_0p90v_25c_captyp_nominal
	set_analysis_view -setup ${CURRENT_VIEW} -hold ${CURRENT_VIEW}
	write_sdf > ${OUT_FILES}/gate_level/${TOP_MODULE}_${CURRENT_VIEW}.sdf

	## worst hold
	set CURRENT_VIEW analysis_view_0p99v_m40c_capbst_fastest
	set_analysis_view -setup ${CURRENT_VIEW} -hold ${CURRENT_VIEW}
	write_sdf > ${OUT_FILES}/gate_level/${TOP_MODULE}_${CURRENT_VIEW}.sdf

}


if { $export_innovus == 1 } {
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
puts "Export design to Innovus"
puts "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	### default view
	set_analysis_view -setup analysis_view_0p81v_125c_capwst_slowest  \
    	              -hold  analysis_view_0p99v_m40c_capbst_fastest

	### To generate all files needed to be loaded in an Innovus session, use the following command:

	write_design -innovus -base_name ${OUT_FILES}/physical_synthesis/work/data

	set CURRENT_VIEW analysis_view_0p90v_25c_captyp_nominal
	write_db ${OUT_FILES}/gate_level/${TOP_MODULE}_logic_mapped.db
}


if { $stop == 0 } {

  exit

}
