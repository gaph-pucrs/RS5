# Optional monitors: vsim -c -do "set LOCKSTEP 1; set DEBUG 1; do sim.do"
set defines {}
foreach {flag default} {DEBUG 0 LOCKSTEP 0 PROFILING 1} {
    if {![info exists $flag]} { set $flag $default }
    if {[set $flag]} { lappend defines +define+$flag }
}
vlog ../RingBuffer/rtl/RingBuffer.sv
vlog ../rtl/aes/*.sv
vlog ../rtl/vector/*.sv
vlog ../rtl/*.sv
vlog {*}$defines *.sv
