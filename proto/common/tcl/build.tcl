proc fail {message} {
    puts stderr "ERROR: $message"
    catch {close_design}
    exit 1
}

if {$argc < 2} {
    fail "Usage: build.tcl <post_route.dcp> <output.bit>"
}

set input  [file normalize [lindex $argv 0]]
set output [file normalize [lindex $argv 1]]

if {![file exists $input]} {
    fail "Implementation checkpoint not found: $input"
}

file mkdir [file dirname $output]

puts ""
puts "============================================================"
puts "BITSTREAM"
puts "============================================================"

open_checkpoint $input

write_bitstream -force $output

close_design

puts ""
puts "Generated: $output"

exit 0
