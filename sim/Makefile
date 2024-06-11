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

run:
	@echo
	@echo "-- VERILATE ----------------"
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --binary -j 0 -I../rtl -I../rtl/aes --timescale 1ns/1ns

	@echo
	@echo "-- RUN ---------------------"
	@rm -rf debug
	@mkdir -p debug
	@obj_dir/Vtestbench

	@echo
	@echo "-- DONE --------------------"

lint:
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --lint-only -I../rtl -I../rtl/aes --timing

clean:
	@echo
	@echo "-- CLEAN -------------------"
	rm -rf obj_dir debug

.PHONY: run clean
