vlog ../rtl/aes/*.sv
vlog ../rtl/*.sv -suppress 12003
vlog *.sv
vsim work.tb_top
run -all
