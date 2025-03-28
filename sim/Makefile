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

RVFI_TRACER_ENABLE?=1
RVFI_PROFILER_ENABLE?=1
RVFI_TRACER_LOG_FILE?=rvfi_tracer_log.txt
RVFI_PROFILER_LOG_FILE?=rvfi_profiler_log.txt
RVFI_PROFILER_SYMBOL_LIST_FILE?=rvfi_profiler_symbol_table.txt
RVFI_PROFILER_WATCHLIST_FILE?=rvfi_profiler_watchlist.txt

# PLUSARGS=""

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

rvfi_tools_lib:
	make -C rvfi_tools rvfi_tools.so

# Internally xrun uses gcc 9.3
xrun_rvfi_tools: rvfi_tools_lib
# LD_LIBRARY_PATH=rvfi_tools/build/usr/local/x86_64-pc-linux-gnu/riscv64-unknown-linux-gnu/lib/ xrun -sv -sv_lib rvfi_tools/build/rvfi_tools/rvfi_tools.so -timescale 1ns/1ps -define RVFI -F ../rtl/rtl.f -F tb.f -F rvfi_tools/src/sv/rvfi_tools.f -incdir ../rtl -top testbench -access r -input scripts/cadence/xmsim_probe.tcl
	export LD_LIBRARY_PATH=rvfi_tools/build/usr/local/x86_64-pc-linux-gnu/riscv64-unknown-linux-gnu/lib/
	xrun -sv -sv_lib rvfi_tools/build/rvfi_tools/rvfi_tools.so -timescale 1ns/1ps -define RVFI -F ../rtl/rtl.f -F tb.f -F rvfi_tools/src/sv/rvfi_tools.f -incdir ../rtl -top testbench -access r -input scripts/cadence/xmsim_probe.tcl

xrun:
	xrun -sv -timescale 1ns/1ps ../rtl/rtl.f -F tb.f -incdir ../rtl -top testbench -access r -input scripts/cadence/xmsim_probe.tcl

clean:
	@echo
	@echo "-- CLEAN -------------------"
	rm -rf obj_dir debug
	rm -rf rvfi_tools.so
	rm -rf waves.shm
	rm -rf xcelium.d
	rm -rf .bpad
	rm -rf *.err
	rm -rf sigusrdump.out
	rm -rf xrun.*

.PHONY: run clean
.ONESHELL: xrun_rvfi_tools
