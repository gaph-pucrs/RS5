proc fail {message} {
    puts stderr "ERROR: $message"
    catch {close_project}
    exit 1
}

if {$argc < 3} {
    fail "Usage: synth.tcl <project.xpr> <memimage.coe> <output.dcp>"
}

set project_xpr [file normalize [lindex $argv 0]]
set mem_coe     [file normalize [lindex $argv 1]]
set output      [file normalize [lindex $argv 2]]

if {![file exists $project_xpr]} {
    fail "Project not found: $project_xpr"
}

if {![file exists $mem_coe]} {
    fail "Memory image not found: $mem_coe"
}

file mkdir [file dirname $output]

open_project $project_xpr

# Configure program memory
set bram [get_ips -quiet BRAM]

if {[llength $bram] != 1} {
    fail "Expected exactly one BRAM IP."
}

set_property -dict [list \
    CONFIG.Coe_File $mem_coe \
    CONFIG.Load_Init_File true \
] $bram

reset_target all $bram
generate_target all $bram

update_compile_order -fileset sources_1

puts ""
puts "============================================================"
puts "SYNTHESIS"
puts "============================================================"

# We intentionally run synthesis here.
# Make decides whether this script needs to be called.
reset_run synth_1

launch_runs synth_1
wait_on_run synth_1

set status [get_property STATUS [get_runs synth_1]]

puts "Synthesis status: $status"

if {![string match "*Complete*" $status]} {
    fail "Synthesis failed."
}

open_run synth_1

write_checkpoint -force $output

close_design
close_project

puts ""
puts "Generated: $output"

exit 0
