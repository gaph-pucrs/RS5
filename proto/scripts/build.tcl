proc fail {message} {
    puts stderr "ERROR: $message"
    catch {close_project}
    exit 1
}

proc reset_bad_ooc_runs {} {
    foreach run [get_runs -quiet *_synth_1] {
        set name [get_property NAME $run]

        if {$name eq "synth_1"} {
            continue
        }

        set status [get_property STATUS $run]
        set status_lc [string tolower $status]

        if {[string match "*error*" $status_lc] ||
            [string match "*fail*" $status_lc]} {
            puts "Resetting failed OOC run: $name ($status)"
            reset_run $run
        }
    }
}

proc configure_bram_init {mem_coe} {
    set bram [get_ips -quiet BRAM]

    if {[llength $bram] == 0} {
        fail "BRAM IP not found."
    }

    if {[llength $bram] != 1} {
        fail "Expected exactly one IP named BRAM, found [llength $bram]."
    }

    puts ""
    puts "---------------- BRAM INITIALIZATION ----------------"
    puts "Memory image: $mem_coe"

    if {[catch {
        set_property -dict [list \
            CONFIG.Coe_File $mem_coe \
            CONFIG.Load_Init_File true \
        ] $bram
    } err]} {
        fail "Could not configure BRAM initialization file: $err"
    }

    set load_init [get_property CONFIG.Load_Init_File $bram]
    set coe_file  [get_property CONFIG.Coe_File $bram]

    puts "Load_Init_File: $load_init"
    puts "Coe_File       : $coe_file"

    set load_init_lc [string tolower $load_init]
    if {$load_init_lc ne "true" && $load_init_lc ne "1"} {
        fail "BRAM CONFIG.Load_Init_File was not set to true."
    }

    puts "Resetting BRAM output products..."
    if {[catch {reset_target all $bram} err]} {
        fail "Could not reset BRAM targets: $err"
    }

    puts "Generating BRAM output products..."
    if {[catch {generate_target all $bram} err]} {
        fail "Could not regenerate BRAM targets: $err"
    }

    set run [get_runs -quiet BRAM_synth_1]
    if {[llength $run] > 0} {
        puts "Resetting BRAM OOC run: BRAM_synth_1"
        catch {reset_run $run}
    }
}

if {$argc < 3} {
    fail "Usage: build.tcl <project.xpr> <memimage.coe> <jobs>"
}

set project_xpr [file normalize [lindex $argv 0]]
set mem_coe     [file normalize [lindex $argv 1]]
set jobs        [lindex $argv 2]

if {![file exists $project_xpr]} {
    fail "Project file not found: $project_xpr"
}

if {![file exists $mem_coe]} {
    fail "Memory initialization file not found: $mem_coe"
}

if {![file isfile $mem_coe]} {
    fail "Memory initialization path is not a file: $mem_coe"
}

set project_dir  [file dirname $project_xpr]
set project_name [file rootname [file tail $project_xpr]]
set reports_dir  [file join $project_dir reports]

file mkdir $reports_dir

puts "============================================================"
puts "RS5 FPGA BUILD"
puts "Project : $project_xpr"
puts "Mem COE : $mem_coe"
puts "Jobs    : $jobs"
puts "============================================================"

open_project $project_xpr

puts "Part : [get_property PART [current_project]]"
puts "Top  : [get_property TOP [get_filesets sources_1]]"

set locked_ips {}
foreach ip [get_ips -quiet] {
    if {[get_property IS_LOCKED $ip]} {
        lappend locked_ips [get_property NAME $ip]
    }
}

if {[llength $locked_ips] > 0} {
    fail "Locked IPs remain before synthesis: [join $locked_ips {, }]. Run 'make ips BOARD=<board>' first."
}

configure_bram_init $mem_coe

reset_bad_ooc_runs

update_compile_order -fileset sources_1

if {[llength [get_runs -quiet impl_1]] > 0} {
    reset_run impl_1
}

if {[llength [get_runs -quiet synth_1]] == 0} {
    fail "synth_1 was not found."
}

reset_run synth_1

puts ""
puts "-------------------- SYNTHESIS --------------------"
launch_runs synth_1 -jobs $jobs
wait_on_run synth_1

set synth_status [get_property STATUS [get_runs synth_1]]
puts "Synthesis status: $synth_status"

if {![string match "*Complete*" $synth_status]} {
    fail "Synthesis did not complete successfully."
}

if {[llength [get_runs -quiet impl_1]] == 0} {
    fail "impl_1 was not found."
}

puts ""
puts "---------------- IMPLEMENTATION -------------------"
launch_runs impl_1 -to_step write_bitstream -jobs $jobs
wait_on_run impl_1

set impl_status [get_property STATUS [get_runs impl_1]]
puts "Implementation status: $impl_status"

if {![string match "*Complete*" $impl_status]} {
    fail "Implementation/bitstream generation did not complete successfully."
}

puts ""
puts "-------------------- REPORTS ----------------------"
open_run impl_1

report_utilization \
    -file [file join $reports_dir utilization.rpt]

report_timing_summary \
    -file [file join $reports_dir timing_summary.rpt]

close_design

set bit_dir [file join $project_dir "${project_name}.runs" impl_1]
set bitfiles [glob -nocomplain [file join $bit_dir *.bit]]

if {[llength $bitfiles] == 0} {
    fail "No .bit file found in $bit_dir"
}

puts ""
puts "============================================================"
puts "BUILD COMPLETE"
puts "Bitstream:"
foreach bit $bitfiles {
    puts "  [file normalize $bit]"
}
puts "Reports:"
puts "  [file normalize [file join $reports_dir utilization.rpt]]"
puts "  [file normalize [file join $reports_dir timing_summary.rpt]]"
puts "============================================================"

close_project
exit 0
