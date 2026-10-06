VERILATOR=verilator

VERILATOR_FLAGS =
# Generate C++ in executable form
VERILATOR_FLAGS += --cc --exe
# Warn abount lint issues; may not want this on less solid designs
VERILATOR_FLAGS += -Wall
VERILATOR_FLAGS += -Wno-WIDTHTRUNC
# Top-level parameter overrides (only applied when passed via command line)
ifeq ($(origin VENABLE),command line)
VERILATOR_FLAGS += -GVEnable=$(VENABLE)
endif
ifeq ($(origin VLEN),command line)
VERILATOR_FLAGS += -GVLEN=$(VLEN)
endif
ifeq ($(origin BIN_FILE_PATH),command line)
VERILATOR_FLAGS += -DBIN_FILE_PATH=\"$(BIN_FILE_PATH)\"
endif
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
	@rm -rf obj_dir
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
	rm -rf obj_dir debug results

.PHONY: run clean
