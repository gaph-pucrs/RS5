vlog ../RingBuffer/rtl/RingBuffer.sv
vlog ../rtl/aes/*.sv
vlog ../rtl/vector/*.sv
vlog ../rtl/*.sv
vlog *.sv
vsim -voptargs=+acc work.testbench
do wave.do
# run -all
