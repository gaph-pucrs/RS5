WORK_DIR   ?= ./riscof_work
BRANCHPRED ?= 1
FORWARDING ?= 1
TRIPLET    ?= riscv64-elf

ENV_VARS = TRIPLET=$(TRIPLET) BRANCHPRED=$(BRANCHPRED) FORWARDING=$(FORWARDING)

default: baseline

all: baseline extensions

extensions: arch-test-update
	@$(ENV_VARS) riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR) --no-browser --config=extensions.ini

baseline: arch-test-update
	@$(ENV_VARS) riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR) --no-browser --config=baseline.ini

arch-test-update: riscv-arch-test
	@riscof arch-test --update

riscv-arch-test:
	@riscof arch-test --clone

report: $(WORK_DIR)/report.html
	@xdg-open $^

$(WORK_DIR)/report.html:
	@make

clean:
	@echo "Cleaning..."
	@rm -rf $(WORK_DIR) riscv-arch-test

.PHONY: all default baseline extensions arch-test-update clean
