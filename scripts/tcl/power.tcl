# power.tcl -- post-route average power from simulation activity, Genus 21.1 power engine
# (repro copy of the paper's campaign script; library files from scripts/config/pdk.env).
# Genus annotates 100 % of the Xcelium SAIF, which is a flat list of full-path INSTANCE blocks
# that Innovus does not map.
# Required: environment LIB_TT, QRC_TYP, LEF_TECH, LEF_CELLS; PNR (P&R run dir: outputs/RS5_postroute.v, outputs/RS5_postroute.sdc,
#           outputs/RS5_typical.spef), OUT_DIR, STIM = list of {name saif_file}
# View: typical corner (0.90 V, 25 C) / RC typical only. Clock = post-route SDC (propagated).
proc P2_try {cmd} { if {[catch {uplevel 1 $cmd} e]} { puts "P2_FAIL: $cmd -> $e"; return 0 }; return 1 }
file mkdir $OUT_DIR
set fo [open $OUT_DIR/mmmc_power.tcl w]
puts $fo "create_library_set -name libset_tt -timing {$::env(LIB_TT)}
create_opcond -name opcond_tt -voltage 0.90 -temperature 25.0
create_timing_condition -name tc_tt -opcond opcond_tt -library_sets {libset_tt}
create_rc_corner -name rc_typ -temperature 25.0 -qrc_tech {$::env(QRC_TYP)}
create_delay_corner -name dc_tt -timing_condition tc_tt -rc_corner rc_typ
create_constraint_mode -name cm -sdc_files {$PNR/outputs/RS5_postroute.sdc}
create_analysis_view -name view_tt -constraint_mode cm -delay_corner dc_tt
set_analysis_view -setup {view_tt} -hold {view_tt}"
close $fo
read_mmmc $OUT_DIR/mmmc_power.tcl
read_physical -lef [list $::env(LEF_TECH) $::env(LEF_CELLS)]
read_netlist $PNR/outputs/RS5_postroute.v
init_design
P2_try {read_spef -rc_corner rc_typ $PNR/outputs/RS5_typical.spef}
set_db lp_default_probability 0.5
report_power -unit mW > $OUT_DIR/power_vectorless.rpt
foreach s $STIM {
    lassign $s name saif
    if {![P2_try {read_stimulus -file $saif -dut_instance testbench.dut -format saif}]} continue
    report_power -unit mW > $OUT_DIR/power_${name}.rpt
    P2_try {report_power -by_hierarchy -levels 3 -unit mW > $OUT_DIR/power_${name}_hier.rpt}
}
puts POWER_GENUS_POSTROUTE_DONE
exit
