database -open -shm -into waves.shm waves -default
probe -create -database waves -all -memories -depth all testbench.dut testbench.u_rvfi_monitor
run
exit
