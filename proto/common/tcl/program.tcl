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
    error "No hardware targets found."
}

if {[llength $targets] == 1} {
    set target [lindex $targets 0]
} else {
    if {![info exists ::env(HW_TARGET)] || $::env(HW_TARGET) eq ""} {
        puts "Available hardware targets:"
        foreach t $targets {
            puts "  $t"
        }

        error "Multiple hardware targets found. Set HW_TARGET to select one."
    }

    set matches [get_hw_targets "*$::env(HW_TARGET)*"]

    if {[llength $matches] == 0} {
        error "No hardware target matches HW_TARGET='$::env(HW_TARGET)'."
    }

    if {[llength $matches] > 1} {
        error "HW_TARGET='$::env(HW_TARGET)' matches more than one hardware target."
    }

    set target [lindex $matches 0]
}

current_hw_target $target
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