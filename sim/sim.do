vlog ../rtl/aes/*.sv
vlog ../rtl/*.sv
vlog *.sv
vsim -voptargs=+acc work.testbench
do wave_simple.do
run -all
