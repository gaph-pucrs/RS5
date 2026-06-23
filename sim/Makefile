VERILATOR=verilator

VERILATOR_FLAGS =
# Generate C++ in executable form
VERILATOR_FLAGS += --cc --exe
# Warn abount lint issues; may not want this on less solid designs
VERILATOR_FLAGS += -Wall
# Make waveforms
#VERILATOR_FLAGS += --trace
# Check SystemVerilog assertions
#VERILATOR_FLAGS += --assert
# Generate coverage analysis
#VERILATOR_FLAGS += --coverage
# Run Verilator in debug mode
#VERILATOR_FLAGS += --debug
# Add this trace to get a backtrace in gdb
#VERILATOR_FLAGS += --gdbbt

# Input files for Verilator
VERILATOR_INPUT = testbench.sv

default: run

CORNER ?= worst

xrun_genus_netlist_gui:
	xrun -sv -gui -timescale 1ns/1ps -F synth.f -top testbench -define SYNTH -sdf_cmd_file sdf/sdf_cmd_$(CORNER).cmd -access r -input restore.tcl

xrun_genus_netlist:
	xrun -sv -timescale 1ns/1ps -F synth.f -top testbench -define SYNTH -sdf_cmd_file sdf/sdf_cmd_$(CORNER).cmd -access r -input xmsim_probe.tcl

run:
	@echo
	@echo "-- VERILATE ----------------"
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --binary -j 0 -I../rtl -I../rtl/aes -I../rtl/vector -I../RingBuffer/rtl --timescale 1ns/1ns

	@echo
	@echo "-- RUN ---------------------"
	@rm -rf debug
	@rm -rf results
	@mkdir -p debug
	@mkdir -p results
	@obj_dir/Vtestbench

	@echo
	@echo "-- DONE --------------------"

lint:
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --lint-only -I../rtl -I../rtl/aes --timing

clean:
	@echo
	@echo "-- CLEAN -------------------"
	rm -rf obj_dir debug results/* xcelium.d/ xrun* waves.shm .simvision simvision*

.PHONY: run clean
