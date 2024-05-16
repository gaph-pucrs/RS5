vlog ../rtl/aes/*.sv
vlog ../rtl/*.sv
vlog *.sv
vsim work.testbench
run -all
