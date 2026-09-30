proc fail {message} {
    puts stderr "ERROR: $message"

    catch {close_hw_target}
    catch {disconnect_hw_server}
    catch {close_hw_manager}

    exit 1
}


# ---------------------------------------------------------------------
# Arguments
# ---------------------------------------------------------------------

if {$argc < 3} {
    fail "Usage: program.tcl <bitstream.bit> <hw_server> <device>"
}


set bitstream [file normalize [lindex $argv 0]]
set hw_server [lindex $argv 1]
set expected_device [string tolower [lindex $argv 2]]


if {![file exists $bitstream]} {
    fail "Bitstream not found: $bitstream"
}


puts ""
puts "============================================================"
puts "FPGA PROGRAMMING"
puts "============================================================"
puts "Bitstream       : $bitstream"
puts "HW server       : $hw_server"
puts "Expected device : $expected_device"
puts ""


# ---------------------------------------------------------------------
# Hardware manager
# ---------------------------------------------------------------------

open_hw_manager


if {[catch {
    connect_hw_server -url $hw_server
} result]} {
    fail "Could not connect to hw_server: $result"
}



# ---------------------------------------------------------------------
# Hardware target
# ---------------------------------------------------------------------

set targets [get_hw_targets]


if {[llength $targets] == 0} {
    fail "No hardware targets found."
}


puts "Available hardware targets:"

foreach target $targets {
    puts "  $target"
}


# Use first available target
set target [lindex $targets 0]


puts ""
puts "Opening hardware target:"
puts "  $target"


open_hw_target $target



# ---------------------------------------------------------------------
# FPGA device selection
# ---------------------------------------------------------------------

set devices [get_hw_devices]


if {[llength $devices] == 0} {
    fail "No FPGA devices found."
}


puts ""
puts "Available devices:"


foreach device $devices {
    puts "  $device"
}



set fpga ""


foreach device $devices {

    set device_name [string tolower $device]

    if {[string match "*$expected_device*" $device_name]} {

        set fpga $device
        break
    }
}



if {$fpga eq ""} {

    fail "Expected FPGA device '$expected_device' not found."

}



puts ""
puts "Selected FPGA:"
puts "  $fpga"



# ---------------------------------------------------------------------
# Program FPGA
# ---------------------------------------------------------------------

puts ""
puts "Programming FPGA..."


set_property PROGRAM.FILE $bitstream $fpga


if {[catch {

    program_hw_devices $fpga

} result]} {

    fail "FPGA programming failed: $result"

}



refresh_hw_device $fpga



puts ""
puts "============================================================"
puts "PROGRAMMING COMPLETED SUCCESSFULLY"
puts "============================================================"
puts ""



# ---------------------------------------------------------------------
# Cleanup
# ---------------------------------------------------------------------

close_hw_target

disconnect_hw_server

close_hw_manager


exit 0