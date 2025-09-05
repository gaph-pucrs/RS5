WORK_DIR   ?= .
BRANCHPRED ?= 1
FORWARDING ?= 1
TRIPLET    ?= riscv64-elf

ENV_VARS = TRIPLET=$(TRIPLET) BRANCHPRED=$(BRANCHPRED) FORWARDING=$(FORWARDING)

default: baseline

all: baseline extensions

report-all: report-baseline report-extensions

extensions: arch-test-update
	@$(ENV_VARS) riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)/extensions_work --no-browser --config=extensions.ini

baseline: arch-test-update
	@$(ENV_VARS) riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)/baseline_work --no-browser --config=baseline.ini

arch-test-update: riscv-arch-test
	@riscof arch-test --update

riscv-arch-test:
	@riscof arch-test --clone

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

.PHONY: all default baseline extensions arch-test-update clean
