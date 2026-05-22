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
VERILATOR_INPUT ?= testbench.sv

# Hardware parameters
VENABLE ?= 1
VLEN ?= 128
LLEN ?= 32
BUS_WIDTH ?= 32

VECTOR_PARAMS = -GVENABLEP=$(VENABLE)
VECTOR_PARAMS += -GVLENP=$(VLEN) -GLLENP=$(LLEN) -GBUS_WIDTHP=$(BUS_WIDTH) 

# Verilator configuration for parallel simulation
OBJ_DIR ?= obj_dir
APP_DIR ?= ../app/lmfrnet
APP_NAME = $(notdir $(patsubst %/,%,$(APP_DIR)))

DEBUG_DIR ?= $(OBJ_DIR)/debug/
RESULTS_DIR ?= $(OBJ_DIR)/results/

PATHS = -GRESULTS_DIR=\"$(RESULTS_DIR)\" -GDEBUG_DIR=\"$(DEBUG_DIR)\"
PATHS += -GBIN_FILEP=\"$(APP_DIR)/$(APP_NAME).bin\"

default: run

# Intended to be used with parallel_sim/run.py
parallel_sim:
	@echo
	@echo "-- VERILATE PARALLEL ----------------"
	@echo "APP_NAME = $(APP_NAME)"
	@echo "VENABLE  = $(VENABLE)"
	@echo "VLEN     = $(VLEN)"
	@echo "LLEN     = $(LLEN)"
	@echo "BUS_WIDTH = $(BUS_WIDTH)"
	@echo "-------------------------------------"
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --binary -j 2 --Mdir $(OBJ_DIR) \
		-I../rtl -I../rtl/aes -I../rtl/vector -I../RingBuffer/rtl \
		--timescale 1ns/1ns \
		$(VECTOR_PARAMS) \
		$(PATHS) 

	@echo
	@echo "-- RUN ---------------------"
	@mkdir -p $(DEBUG_DIR)
	@mkdir -p $(RESULTS_DIR)
	@$(OBJ_DIR)/Vparallel_tb

	@echo
	@echo "-- DONE --------------------"

run:
	@echo
	@echo "-- VERILATE ----------------"
	@$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) --binary -j 0 \
			-I../rtl -I../rtl/aes -I../rtl/vector -I../RingBuffer/rtl \
			--timescale 1ns/1ns

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
	rm -rf $(OBJ_DIR) $(DEBUG_DIR) $(RESULTS_DIR)

.PHONY: run clean parallel_sim
