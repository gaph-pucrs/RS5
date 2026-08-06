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

VERILATOR_SIM_FLAGS  = -I../rtl -I../rtl/aes -I../rtl/vector -I../RingBuffer/rtl --timescale 1ns/1ns
# -GVEnable=1 passes a 32-bit literal to a bit parameter; suppress the benign width warning
VERILATOR_CONV_FLAGS = $(VERILATOR_FLAGS) -Wno-WIDTHTRUNC

compile-%:
	@echo "-- COMPILE $* ---"
	@$(MAKE) -C ../app/$* clean all VLEN=$(VLEN) VEn=$(VEn)

run-%:
	@echo
	@echo "-- VERILATE $* (VLEN=$(VLEN)) --"
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --binary -j 0 $(VERILATOR_SIM_FLAGS) \
		-Wno-WIDTHTRUNC -GVEnable=$(VEn) -GVLEN=$(VLEN) -GBIN_FILE='"../app/$*/$*.bin"'
	@echo
	@echo "-- RUN $* (VLEN=$(VLEN)) -------"
	@rm -rf debug results
	@mkdir -p debug results
	@obj_dir/Vtestbench
	@echo
	@echo "-- DONE $* (VLEN=$(VLEN)) ------"

config:
	echo $(VEn) $(VLEN)

.PHONY: run clean
