proc fail {message} {
    puts stderr "ERROR: $message"
    catch {close_design}
    exit 1
}

if {$argc < 2} {
    fail "Usage: reports.tcl <post_route.dcp> <report_dir>"
}

set input      [file normalize [lindex $argv 0]]
set report_dir [file normalize [lindex $argv 1]]

if {![file exists $input]} {
    fail "Implementation checkpoint not found: $input"
}

file mkdir $report_dir

puts ""
puts "============================================================"
puts "REPORT GENERATION"
puts "============================================================"

open_checkpoint $input

report_timing_summary \
    -file [file join $report_dir timing_summary.rpt]

report_utilization \
    -file [file join $report_dir utilization.rpt]

report_power \
    -file [file join $report_dir power.rpt]

close_design

puts ""
puts "Generated:"
puts "  [file join $report_dir timing_summary.rpt]"
puts "  [file join $report_dir utilization.rpt]"
puts "  [file join $report_dir power.rpt]"

exit 0
