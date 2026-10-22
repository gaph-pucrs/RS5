do compile.do
# Optional overrides: vsim -c -do "set BIN_FILE path/to/app.bin; do sim.do"
set params {}
if {[info exists BIN_FILE]} { lappend params -GBIN_FILE="$BIN_FILE" }
vsim -voptargs=+acc {*}$params work.testbench
do wave.do
# run -all
