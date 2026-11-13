WORK_DIR     ?= .
BRANCHPRED   ?= 1
FORWARDING   ?= 1
DUALPORT_MEM ?= 1
DELAY_CYCLES ?= 0
RSP_DELAY_CYCLES ?= 0
RANDOM_DELAY ?= 0
SEED         ?= 1
IMEM_LATENCY ?=
TRIPLET      ?= riscv64-elf

ENV_VARS = \
	TRIPLET=$(TRIPLET)\
	BRANCHPRED=$(BRANCHPRED)\
	FORWARDING=$(FORWARDING)\
	DUALPORT_MEM=$(DUALPORT_MEM)\
	DELAY_CYCLES=$(DELAY_CYCLES) \
	RSP_DELAY_CYCLES=$(RSP_DELAY_CYCLES) \
	RANDOM_DELAY=$(RANDOM_DELAY) \
	SEED=$(SEED) \
	IMEM_LATENCY=$(IMEM_LATENCY)

default: baseline

all: baseline extensions

report-all: report-baseline report-extensions

extensions: arch-test-update
	@$(ENV_VARS) riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)/extensions_work --no-browser --config=extensions.ini

baseline: arch-test-update
	@$(ENV_VARS) riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)/baseline_work --no-browser --config=baseline.ini

arch-test-update: riscv-arch-test
	@riscof arch-test --update --get-version 3.9.1

riscv-arch-test:
	@riscof arch-test --clone --get-version 3.9.1

lockstep-baseline:
	@./lockstep.py $(WORK_DIR)/baseline_work/rv32i_m/*/src/*.S

lockstep-extensions:
	@./lockstep.py $(WORK_DIR)/extensions_work/rv32i_m/*/src/*.S

report-baseline: $(WORK_DIR)/baseline_work/report.html
	@xdg-open $^

report-extensions: $(WORK_DIR)/extensions_work/report.html
	@xdg-open $^

$(WORK_DIR)/baseline_work/report.html:
	@make baseline

$(WORK_DIR)/extensions_work/report.html:
	@make extensions

clean:
	@echo "Cleaning..."
	@rm -rf $(WORK_DIR)/baseline_work $(WORK_DIR)/extensions_work riscv-arch-test

.PHONY: all default baseline extensions arch-test-update lockstep-baseline lockstep-extensions clean
