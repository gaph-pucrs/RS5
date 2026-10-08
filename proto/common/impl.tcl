proc fail {message} {
    puts stderr "ERROR: $message"
    catch {close_design}
    exit 1
}

if {$argc < 2} {
    fail "Usage: impl.tcl <post_synth.dcp> <post_route.dcp>"
}

set input  [file normalize [lindex $argv 0]]
set output [file normalize [lindex $argv 1]]

if {![file exists $input]} {
    fail "Synthesis checkpoint not found: $input"
}

file mkdir [file dirname $output]

puts ""
puts "============================================================"
puts "IMPLEMENTATION"
puts "============================================================"

open_checkpoint $input

opt_design
place_design
phys_opt_design
route_design

write_checkpoint -force $output

set report_dir [file dirname $output]

report_timing_summary \
    -file [file join $report_dir timing_summary.rpt]

report_utilization \
    -file [file join $report_dir utilization.rpt]

close_design

puts ""
puts "Generated: $output"

exit 0
