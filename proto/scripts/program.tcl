proc fail {message} {
    puts stderr "ERROR: $message"
    catch {close_hw_target}
    catch {disconnect_hw_server}
    catch {close_hw_manager}
    exit 1
}

if {$argc < 3} {
    fail "Usage: program.tcl <project.xpr> <expected_part> <hw_server>"
}

set project_xpr   [file normalize [lindex $argv 0]]
set expected_part [lindex $argv 1]
set hw_server     [lindex $argv 2]

if {![file exists $project_xpr]} {
    fail "Project file not found: $project_xpr"
}

if {![regexp {^(xc7[a-z]+[0-9]+t)} $expected_part -> device_prefix]} {
    fail "Could not derive FPGA device name from expected part: $expected_part"
}

set project_dir  [file dirname $project_xpr]
set project_name [file rootname [file tail $project_xpr]]
set bit_dir      [file join $project_dir "${project_name}.runs" impl_1]
set bitfiles     [glob -nocomplain [file join $bit_dir *.bit]]

if {[llength $bitfiles] == 0} {
    fail "No bitstream found in $bit_dir. Run 'make bitstream' first."
}

set bitfile [file normalize [lindex $bitfiles 0]]

puts "============================================================"
puts "RS5 FPGA PROGRAM"
puts "Project   : $project_xpr"
puts "Part      : $expected_part"
puts "Device    : $device_prefix"
puts "Bitstream : $bitfile"
puts "hw_server : $hw_server"
puts "============================================================"

open_hw_manager

if {[catch {connect_hw_server -url $hw_server} err]} {
    fail "Could not connect to hw_server at $hw_server: $err"
}

set targets [get_hw_targets -quiet]

if {[llength $targets] == 0} {
    fail "No JTAG hardware target was found."
}

puts "Detected hardware targets:"
foreach target $targets {
    puts "  $target"
}

set target [lindex $targets 0]
current_hw_target $target

if {[catch {open_hw_target} err]} {
    fail "Could not open hardware target $target: $err"
}

set devices [get_hw_devices -quiet]

puts "Detected JTAG devices:"
foreach dev $devices {
    puts "  $dev"
}

set fpga_devices [get_hw_devices -quiet "${device_prefix}*"]

if {[llength $fpga_devices] == 0} {
    fail "FPGA $device_prefix was not found in the JTAG chain."
}

set fpga [lindex $fpga_devices 0]

current_hw_device $fpga
refresh_hw_device $fpga

set_property PROGRAM.FILE $bitfile $fpga

puts ""
puts "Programming $fpga..."
program_hw_devices $fpga
refresh_hw_device $fpga

puts ""
puts "============================================================"
puts "PROGRAMMING COMPLETE"
puts "Device    : $fpga"
puts "Bitstream : $bitfile"
puts "============================================================"

close_hw_target
disconnect_hw_server
close_hw_manager
exit 0
