###############################################################################
# synth.tcl -- Genus 21.1 physical synthesis of the RS5 core (repro package).
# Copy of the synthesis script of the paper's campaign (RS5 synthesis flow + SDC export).
# Repro changes (none affects the netlist):
#   * constraints.sdc / mmmc.tcl are read from this directory; the library files of the
#     MMMC views come from scripts/config/pdk.env (environment variables, see pdk.env.example);
#   * report_congestion/report_utilization attempts, write_design -innovus and the
#     optional post-synthesis SDF were removed (not used by the flow).
#
# The SDC is scripts/constraints.sdc of RS5 with only `set period_clock` changed
# (PERIOD, ns). RTL_ROOT is the RTL folder (rtl_base, rtl_comb or rtl_ser); the file list is
# every .sv of that folder, RingBuffer/RingBuffer.sv last. PARAMS is appended to the elaborate
# -parameters list.
#
# Required: OUT_DIR RTL_ROOT PERIOD; environment LIB_*, QRC_*, LEF_* (scripts/config/pdk.env)
# Optional: EFFORT (syn_global_effort, default high), OPT_EFFORT, PARAMS
#           (list of {name value}), NCPU (default 8)
# Outputs:  $OUT_DIR/gate_level/RS5_logic_mapped.v, RS5.sdc, reports/*.rpt
###############################################################################
if {![info exists TOP_MODULE]} {set TOP_MODULE RS5}
if {![info exists VLEN]}       {set VLEN 64}
if {![info exists LLEN]}       {set LLEN 32}
if {![info exists BUS_WIDTH]}  {set BUS_WIDTH 32}
if {![info exists EFFORT]}     {set EFFORT high}
if {![info exists PARAMS]}     {set PARAMS {}}
if {![info exists NCPU]}       {set NCPU 8}

set SCRIPT_DIR [file dirname [file normalize [info script]]]
set R $OUT_DIR/reports
file mkdir $R $OUT_DIR/gate_level $OUT_DIR/scripts

# ---- constraints: identical to scripts/constraints.sdc except the period ---
set fi [open $SCRIPT_DIR/constraints.sdc r]; set sdc [read $fi]; close $fi
set n [regsub -line {^set period_clock [0-9.]+;} $sdc "set period_clock $PERIOD;" sdc]
if {$n != 1} {error "period_clock line not found in constraints.sdc"}
set fo [open $OUT_DIR/scripts/constraints.sdc w]; puts -nonewline $fo $sdc; close $fo

set fi [open $SCRIPT_DIR/mmmc.tcl r]; set mmmc [read $fi]; close $fi
set n [regsub -line {^set CONSTRAINTS_PATH .*$} $mmmc "set CONSTRAINTS_PATH $OUT_DIR/scripts" mmmc]
if {$n != 1} {error "CONSTRAINTS_PATH line not found in mmmc"}
set fo [open $OUT_DIR/scripts/mmmc.tcl w]; puts -nonewline $fo $mmmc; close $fo

read_mmmc $OUT_DIR/scripts/mmmc.tcl

# ---- tool configuration (same as original) --------------------------------
set_multi_cpu_usage -local_cpu $NCPU
set_db lp_default_probability 0.5
set_db syn_global_effort $EFFORT
if {[info exists OPT_EFFORT]} { set_db syn_opt_effort $OPT_EFFORT }
set_db auto_ungroup none
set_db interconnect_mode ple
set_db information_level 9
set_db hdl_error_on_latch true
set_db lp_insert_clock_gating true

# ---- HDL -------------------------------------------------------------------
set files [list $RTL_ROOT/RS5_pkg.sv]
foreach f [lsort [concat [glob -nocomplain $RTL_ROOT/aes/*.sv] \
                         [glob -nocomplain $RTL_ROOT/vector/*.sv] \
                         [glob -nocomplain $RTL_ROOT/*.sv]]] {
    if {[file tail $f] ne "RS5_pkg.sv"} { lappend files $f }
}
lappend files $RTL_ROOT/RingBuffer/RingBuffer.sv
set fo [open $OUT_DIR/filelist.txt w]; puts $fo [join $files \n]; close $fo
read_hdl -define SYNTH -sv $files

set elab_params [concat [list [list VLEN $VLEN] [list LLEN $LLEN] [list BUS_WIDTH $BUS_WIDTH]] $PARAMS]
puts "ELAB_PARAMS: $elab_params"
elaborate $TOP_MODULE -parameters $elab_params
init_design

# ---- synthesis (same as original) ------------------------------------------
syn_generic -create_floorplan -physical
syn_map -physical
syn_opt

# ---- reports -----------------------------------------------------------------
report_clock_gating > $R/${TOP_MODULE}_clock_gating.rpt
report_ple          > $R/${TOP_MODULE}_ple.rpt
report_qor          > $R/${TOP_MODULE}_qor.rpt
report_gates        > $R/${TOP_MODULE}_gates.rpt
report_area         > $R/${TOP_MODULE}_area.rpt
if {[catch {report_area -depth 3 > $R/${TOP_MODULE}_area_depth3.rpt} e]} { puts "report_area -depth failed: $e" }
if {[catch {report_gates -instance_hier [vfind / -inst execute1] > $R/${TOP_MODULE}_gates_execute.rpt} e]} {}

foreach v {analysis_view_0p81v_125c_capwst_slowest analysis_view_0p90v_25c_captyp_nominal analysis_view_0p99v_m40c_capbst_fastest} {
    set_analysis_view -setup $v -hold $v
    report_timing          > $R/${TOP_MODULE}_timing_setup_${v}.rpt
    report_power -unit mW  > $R/${TOP_MODULE}_power_${v}.rpt
    if {$v eq "analysis_view_0p81v_125c_capwst_slowest"} {
        report_timing -max_paths 10 -nworst 1 -path_type full > $R/${TOP_MODULE}_timing10_${v}.rpt
    }
    if {$v eq "analysis_view_0p90v_25c_captyp_nominal"} {
        if {[catch {report_power -by_hierarchy -levels 4 -unit mW > $R/${TOP_MODULE}_power_hier_${v}.rpt} e]} {
            if {[catch {report_power -levels 4 -unit mW > $R/${TOP_MODULE}_power_hier_${v}.rpt} e2]} { puts "power hier failed: $e / $e2" }
        }
    }
}
# ---- netlist / db ------------------------------------------------------------
set_analysis_view -setup analysis_view_0p81v_125c_capwst_slowest -hold analysis_view_0p99v_m40c_capbst_fastest
write_hdl > $OUT_DIR/gate_level/${TOP_MODULE}_logic_mapped.v
write_db $OUT_DIR/gate_level/${TOP_MODULE}_logic_mapped.db

# ---- paper2 additions ------------------------------------------------------------
# SDC of the slow view (same constraint mode for all views) for Innovus
if {[catch {write_sdc -view analysis_view_0p81v_125c_capwst_slowest > $OUT_DIR/gate_level/${TOP_MODULE}.sdc} e]} {
    puts "PAPER2_WRITE_SDC_FAILED: $e"
} else { puts "PAPER2_WRITE_SDC_OK" }
puts "VERIFY_SYNTH_DONE"
exit
