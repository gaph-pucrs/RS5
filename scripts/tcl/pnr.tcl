###############################################################################
# pnr.tcl -- minimal Innovus 21.1 (stylus) place & route flow for the RS5 core (repro package;
# the paper's campaign script, with library files and cell names taken from scripts/config/pdk.env)
# TSMC 28 nm HPC+ (tcbn28hpcplusbwp30p140), same 3 MMMC corners as the Genus flow:
# 0.81 V/125 C/RC worst (setup), 0.90 V/25 C/RC typical, 0.99 V/-40 C/RC best (hold).
#
# Required (set via -execute): SYN_DIR (Genus run dir) OUT_DIR
# Environment (scripts/config/pdk.env): LIB_SS/TT/FF, QRC_WORST/TYP/BEST, LEF_TECH, LEF_CELLS,
#   ENDCAP_LEFT/RIGHT, WELLTAP_CELL, TIE_CELLS, FILLER_CELLS, CTS_BUF/INV/ICG_CELLS,
#   CLK_BUF_PATTERNS, ICG_PATTERN
# Optional: NCPU (4) UTIL (0.68 core row utilization) MARGIN (core-to-die, um)
#           TOP (RS5) HOLD_TGT (0.0 ns) SETUP_TGT (0.0 ns) EXTRACT_EFFORT (medium)
# Physical choices:
#   rows: site core; square core; routing M2..M6 (as lab SoC flow)
#   end caps, well taps every 20 um (offset 6 um)
#   core rings M5(V)/M6(H) 1.5 um; stripes M5 vertical + M6 horizontal 0.5 um
#   every ~25 um; M1 follow-pins; tie-high/tie-low cells; fillers
###############################################################################
if {![info exists TOP]}            {set TOP RS5}
if {![info exists NCPU]}           {set NCPU 4}
if {![info exists UTIL]}           {set UTIL 0.68}
if {![info exists MARGIN]}         {set MARGIN 6.0}
if {![info exists HOLD_TGT]}       {set HOLD_TGT 0.02}
if {![info exists SETUP_TGT]}      {set SETUP_TGT 0.0}
if {![info exists EXTRACT_EFFORT]} {set EXTRACT_EFFORT medium}

set R  $OUT_DIR/reports
set D  $OUT_DIR/outputs
file mkdir $R $D $OUT_DIR/db

set LEFS [list $::env(LEF_TECH) $::env(LEF_CELLS)]

# ---- inputs from Genus ---------------------------------------------------------
set NETLIST $SYN_DIR/gate_level/${TOP}_logic_mapped.v
set SDC     $SYN_DIR/gate_level/${TOP}.sdc
if {![file exists $SDC] || [file size $SDC] == 0} {
    puts "PAPER2_PNR: Genus SDC missing, using constraints copy $SYN_DIR/scripts/constraints.sdc"
    set SDC $SYN_DIR/scripts/constraints.sdc
}
# Genus uniquifies the top module name with its parameters: take it from the netlist
# (the last module written by write_hdl is the top).
set fi [open $NETLIST r]; set txt [read $fi]; close $fi
set TOPCELL [lindex [regexp -all -inline {\nmodule\s+([^\s(]+)} "\n$txt"] end]
unset txt
puts "PAPER2_PNR inputs: netlist=$NETLIST sdc=$SDC top_cell=$TOPCELL"

# ---- MMMC (same corners as tcl/mmmc.tcl) ---------------------------------------
set fo [open $OUT_DIR/mmmc.tcl w]
puts $fo "
create_library_set -name libset_0p81v_125c -timing {$::env(LIB_SS)}
create_library_set -name libset_0p90v_25c  -timing {$::env(LIB_TT)}
create_library_set -name libset_0p99v_m40c -timing {$::env(LIB_FF)}
create_opcond -name opcond_0p81v_125c -process 1.0 -voltage 0.81 -temperature 125.0
create_opcond -name opcond_0p90v_25c  -process 1.0 -voltage 0.90 -temperature  25.0
create_opcond -name opcond_0p99v_m40c -process 1.0 -voltage 0.99 -temperature -40.0
create_timing_condition -name timing_cond_0p81v_125c -opcond opcond_0p81v_125c -library_sets {libset_0p81v_125c}
create_timing_condition -name timing_cond_0p90v_25c  -opcond opcond_0p90v_25c  -library_sets {libset_0p90v_25c}
create_timing_condition -name timing_cond_0p99v_m40c -opcond opcond_0p99v_m40c -library_sets {libset_0p99v_m40c}
create_rc_corner -name rc_corner_125c_capwst -temperature 125.0 -qrc_tech {$::env(QRC_WORST)}
create_rc_corner -name rc_corner_25c_captyp  -temperature  25.0 -qrc_tech {$::env(QRC_TYP)}
create_rc_corner -name rc_corner_m40c_capbst -temperature -40.0 -qrc_tech {$::env(QRC_BEST)}
create_delay_corner -name delay_corner_0p81v_125c_capwst -timing_condition timing_cond_0p81v_125c -rc_corner rc_corner_125c_capwst
create_delay_corner -name delay_corner_0p90v_25c_captyp  -timing_condition timing_cond_0p90v_25c  -rc_corner rc_corner_25c_captyp
create_delay_corner -name delay_corner_0p99v_m40c_capbst -timing_condition timing_cond_0p99v_m40c -rc_corner rc_corner_m40c_capbst
create_constraint_mode -name constraints_default -sdc_files {$SDC}
create_analysis_view -name analysis_view_0p81v_125c_capwst_slowest -constraint_mode constraints_default -delay_corner delay_corner_0p81v_125c_capwst
create_analysis_view -name analysis_view_0p90v_25c_captyp_nominal  -constraint_mode constraints_default -delay_corner delay_corner_0p90v_25c_captyp
create_analysis_view -name analysis_view_0p99v_m40c_capbst_fastest -constraint_mode constraints_default -delay_corner delay_corner_0p99v_m40c_capbst
set_analysis_view -setup {analysis_view_0p81v_125c_capwst_slowest analysis_view_0p90v_25c_captyp_nominal} \\
                  -hold  {analysis_view_0p99v_m40c_capbst_fastest analysis_view_0p90v_25c_captyp_nominal} \\
                  -leakage analysis_view_0p90v_25c_captyp_nominal -dynamic analysis_view_0p90v_25c_captyp_nominal
"
close $fo
set VSS_VIEW analysis_view_0p81v_125c_capwst_slowest
set VTT_VIEW analysis_view_0p90v_25c_captyp_nominal
set VFF_VIEW analysis_view_0p99v_m40c_capbst_fastest

proc stamp {tag} {
    global OUT_DIR
    set fo [open $OUT_DIR/stages.txt a]; puts $fo "[clock format [clock seconds] -format %Y-%m-%dT%H:%M:%S] $tag"; close $fo
    puts "PAPER2_PNR_STAGE $tag"
}
proc p2try {script} {
    # non-essential command: log failure and continue
    if {[catch {uplevel 1 $script} e]} { puts "PAPER2_PNR_WARN failed: [string range $script 0 80] -> $e" }
}

# ---- init ------------------------------------------------------------------------
set_multi_cpu_usage -local_cpu $NCPU
set_db init_power_nets  {VDD}
set_db init_ground_nets {VSS}
read_mmmc $OUT_DIR/mmmc.tcl
read_physical -lef $LEFS
read_netlist $NETLIST -top $TOPCELL
init_design
stamp init

set_db design_process_node 28
set_db design_top_routing_layer M6
set_db design_bottom_routing_layer M2
set_db timing_analysis_type ocv
set_db timing_analysis_cppr both
set_db opt_setup_target_slack $SETUP_TGT
set_db opt_hold_target_slack  $HOLD_TGT
set_db place_global_place_io_pins true
set_db add_fillers_no_single_site_gap true
# the library has no 1-site filler: legalize with gaps of 0 or >= 2 sites
if {![info exists INST_GAP]} {set INST_GAP 2}
if {$INST_GAP > 0} { set_db place_detail_legalization_inst_gap $INST_GAP }

connect_global_net VDD -type pg_pin -pin_base_name VDD -inst_base_name *
connect_global_net VSS -type pg_pin -pin_base_name VSS -inst_base_name *
connect_global_net VDD -type tie_hi -inst_base_name *
connect_global_net VSS -type tie_lo -inst_base_name *

p2try {check_design -type place -out_file $R/check_design_place.rpt}
p2try {report_analysis_coverage > $R/analysis_coverage_init.rpt}
p2try {check_timing_library_consistency > $R/check_lib_consistency.rpt}
p2try {check_timing -verbose > $R/check_timing_init.rpt}
p2try {time_design -pre_place -report_dir $R/td_preplace -report_prefix preplace}

# ---- floorplan -------------------------------------------------------------------
create_floorplan -site core -core_density_size 1.0 $UTIL $MARGIN $MARGIN $MARGIN $MARGIN -flip s
add_endcaps -start_row_cap $::env(ENDCAP_LEFT) -end_row_cap $::env(ENDCAP_RIGHT) -prefix ENDCAP
add_well_taps -cell $::env(WELLTAP_CELL) -cell_interval 20.0 -in_row_offset 6.0 -prefix WELLTAP
p2try {check_well_taps -max_distance 20.0 -cells $::env(WELLTAP_CELL) > $R/check_well_taps.rpt}

# power: rings M6 (H) / M5 (V), stripes M5/M6, M1 follow-pins
add_rings -type core_rings -follow core -nets {VDD VSS} \
    -layer  {top M6 bottom M6 left M5 right M5} \
    -width  {top 1.5 bottom 1.5 left 1.5 right 1.5} \
    -spacing {top 0.5 bottom 0.5 left 0.5 right 0.5} \
    -offset {top 0.5 bottom 0.5 left 0.5 right 0.5}
# power-via generation: skip/adjust vias that would violate DRC against std-cell geometry
if {![info exists PG_VIA_DRC]} {set PG_VIA_DRC 1}
if {$PG_VIA_DRC} {
    set_db generate_special_via_enable_check_drc true
    set_db generate_special_via_respect_stdcell_geometry true
}
# follow-pins first, then stripes (add_stripes drops the via stacks down to M1 itself)
route_special -nets {VDD VSS} -connect {core_pin} -core_pin_target {first_after_row_end} \
    -allow_layer_change 1 -allow_jogging 0
add_stripes -layer M5 -direction vertical   -nets {VDD VSS} -width 0.5 -spacing 0.5 \
    -set_to_set_distance 25.0 -start_offset 10.0 -stop_offset 10.0 -merge_stripes_value 2.0
add_stripes -layer M6 -direction horizontal -nets {VDD VSS} -width 0.5 -spacing 0.5 \
    -set_to_set_distance 25.0 -start_offset 10.0 -stop_offset 10.0 -merge_stripes_value 2.0
p2try {check_floorplan -out_file $R/check_floorplan.rpt}
p2try {check_connectivity -type special -out_file $R/check_connectivity_pg_floorplan.rpt}
write_def -floorplan $D/${TOP}_floorplan.def
stamp floorplan

# ---- placement ------------------------------------------------------------------
place_opt_design -report_dir $R/place_opt
set_db add_tieoffs_cells $::env(TIE_CELLS)
set_db add_tieoffs_max_fanout 10
set_db add_tieoffs_max_distance 20
add_tieoffs -prefix TIEOFF
place_detail
check_place $R/check_place.rpt
write_db $OUT_DIR/db/${TOP}_place.db
stamp place

# ---- CTS -------------------------------------------------------------------------
set_db cts_buffer_cells   $::env(CTS_BUF_CELLS)
set_db cts_inverter_cells $::env(CTS_INV_CELLS)
set_db cts_clock_gating_cells $::env(CTS_ICG_CELLS)
create_route_type -name rt_clk -top_preferred_layer M6 -bottom_preferred_layer M3 -preferred_routing_layer_effort high
set_db cts_route_type_trunk rt_clk
set_db cts_route_type_leaf  rt_clk
set_db cts_target_max_transition_time 0.15
p2try {time_design -pre_cts -report_dir $R/td_prects -report_prefix prects}
create_clock_tree_spec -out_file $OUT_DIR/ccopt_spec.tcl
ccopt_design -report_dir $R/ccopt
opt_design -post_cts -hold -report_dir $R/postcts_hold -report_prefix postcts_hold
p2try {report_clock_trees > $R/clock_trees_postcts.rpt}
p2try {report_skew_groups > $R/skew_groups_postcts.rpt}
p2try {time_design -post_cts -report_dir $R/td_postcts -report_prefix postcts}
p2try {time_design -post_cts -hold -report_dir $R/td_postcts_hold -report_prefix postcts_hold}
write_db $OUT_DIR/db/${TOP}_cts.db
stamp cts

# ---- route -----------------------------------------------------------------------
set_db route_design_with_timing_driven true
set_db route_design_with_si_driven true
set_db route_design_detail_fix_antenna true
set_db route_design_antenna_diode_insertion false
route_design
set_db extract_rc_engine post_route
set_db extract_rc_effort_level $EXTRACT_EFFORT
set_db delaycal_enable_si true
opt_design -post_route -setup -hold -report_dir $R/postroute_opt -report_prefix postroute_opt
# second incremental pass: hold/setup re-checked on the ECO-routed result of the first pass
opt_design -post_route -setup -hold -report_dir $R/postroute_opt2 -report_prefix postroute_opt2
stamp route_opt

# ---- fillers + final ECO route ----------------------------------------------------
add_fillers -base_cells $::env(FILLER_CELLS) -prefix FILLER
p2try {check_filler -out_file $R/check_filler.rpt}
route_eco
p2try {route_eco -fix_drc}
stamp fillers

# ---- extraction + final timing ------------------------------------------------------
extract_rc
time_design -post_route -report_dir $R/td_final_setup -report_prefix final
time_design -post_route -hold -report_dir $R/td_final_hold -report_prefix final_hold
report_timing -late  -view $VSS_VIEW -max_paths 10 -path_type full_clock > $R/timing_setup_ss_rcworst.rpt
report_timing -late  -view $VTT_VIEW -max_paths 5  -path_type full_clock > $R/timing_setup_tt_typical.rpt
report_timing -early -view $VFF_VIEW -max_paths 10 -path_type full_clock > $R/timing_hold_ff_rcbest.rpt
report_timing -early -view $VTT_VIEW -max_paths 5  -path_type full_clock > $R/timing_hold_tt_typical.rpt
p2try {report_timing_summary -checks setup > $R/timing_summary_setup.rpt}
p2try {report_timing_summary -checks hold > $R/timing_summary_hold.rpt}
p2try {report_constraint -all_violators > $R/constraint_violators.rpt}
p2try {report_clock_trees > $R/clock_trees_final.rpt}
p2try {report_skew_groups > $R/skew_groups_final.rpt}
p2try {report_area > $R/area.rpt}
p2try {report_area -include_physical > $R/area_with_physical.rpt}
p2try {report_gate_count -out_file $R/gate_count.rpt}
p2try {report_summary -out_dir $R/summary}
stamp timing

# vectorless power at the typical corner (reference only; real power comes from the SDF simulation)
p2try {report_power -view $VTT_VIEW -out_file $R/power_vectorless_tt.rpt}
p2try {report_power -view $VTT_VIEW -hierarchy 3 -out_file $R/power_vectorless_tt_hier.rpt}
stamp power

# ---- checks ----------------------------------------------------------------------
p2try {check_connectivity -type all -error 100000 -warning 100000 -out_file $R/check_connectivity.rpt}
p2try {check_drc -limit 100000 -out_file $R/check_drc.rpt}
p2try {check_process_antenna -out_file $R/check_antenna.rpt}
p2try {check_place $R/check_place_final.rpt}
stamp checks

# ---- numbers for the summary (computed here from the database) ------------------
set std_area 0.0; set n_std 0; set n_phys 0; set phys_area 0.0; set n_clk 0; set clk_area 0.0
foreach i [get_db insts] {
    set a [get_db $i .area]
    if {[get_db $i .is_physical]} { incr n_phys; set phys_area [expr {$phys_area + $a}] } else {
        incr n_std; set std_area [expr {$std_area + $a}]
    }
}
# clock buffers/inverters = instances matching CLK_BUF_PATTERNS (CTS inserts only these; Genus
# inserts the clock-gating cells, ICG_PATTERN)
set terms {}
foreach pat $::env(CLK_BUF_PATTERNS) { lappend terms ".base_cell.name == $pat" }
set cb [get_db insts -if [join $terms " || "]]
set n_clk [llength $cb]
foreach i $cb { set clk_area [expr {$clk_area + [get_db $i .area]}] }
set n_icg [llength [get_db insts -if ".base_cell.name == $::env(ICG_PATTERN)"]]
set core [get_db current_design .core_bbox]
set die  [get_db current_design .bbox]
set cx [expr {[lindex $core 0 2] - [lindex $core 0 0]}]; set cy [expr {[lindex $core 0 3] - [lindex $core 0 1]}]
set dx [expr {[lindex $die 0 2] - [lindex $die 0 0]}];   set dy [expr {[lindex $die 0 3] - [lindex $die 0 1]}]
set fo [open $R/pnr_numbers.txt w]
puts $fo "die_w_um $dx"
puts $fo "die_h_um $dy"
puts $fo "die_area_um2 [expr {$dx*$dy}]"
puts $fo "core_w_um $cx"
puts $fo "core_h_um $cy"
puts $fo "core_area_um2 [expr {$cx*$cy}]"
puts $fo "std_cells $n_std"
puts $fo "std_cell_area_um2 $std_area"
puts $fo "phys_cells $n_phys"
puts $fo "phys_cell_area_um2 $phys_area"
puts $fo "clock_buf_inv_cells $n_clk"
puts $fo "clock_buf_inv_area_um2 $clk_area"
puts $fo "clock_gates $n_icg"
puts $fo "std_util_core [expr {$std_area/($cx*$cy)}]"
close $fo

# ---- outputs ---------------------------------------------------------------------
set PHYS [concat $::env(FILLER_CELLS) $::env(ENDCAP_LEFT) $::env(ENDCAP_RIGHT) $::env(WELLTAP_CELL)]
write_netlist $D/${TOP}_postroute.v -exclude_leaf_cells -exclude_insts_of_cells $PHYS
p2try {write_netlist $D/${TOP}_postroute_pg.v -include_pg -include_phys_insts -exclude_leaf_cells}
p2try {write_sdc $D/${TOP}_postroute.sdc}
write_parasitics -rc_corner rc_corner_25c_captyp  -spef_file $D/${TOP}_typical.spef
write_parasitics -rc_corner rc_corner_125c_capwst -spef_file $D/${TOP}_rcworst.spef
write_parasitics -rc_corner rc_corner_m40c_capbst -spef_file $D/${TOP}_rcbest.spef
write_sdf $D/${TOP}_typ.sdf -view $VTT_VIEW -target_application verilog -recompute_delaycal
write_sdf $D/${TOP}_ss.sdf  -view $VSS_VIEW -target_application verilog -recompute_delaycal
write_sdf $D/${TOP}_ff.sdf  -view $VFF_VIEW -target_application verilog -recompute_delaycal
write_def -routing $D/${TOP}.def
write_db $OUT_DIR/db/${TOP}_final.db
stamp outputs

puts "PAPER2_PNR_DONE"
exit
