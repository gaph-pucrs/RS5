WORK_DIR   ?= ./riscof_work
BRANCHPRED ?= 1
FORWARDING ?= 1

all: baseline extensions

default: baseline

extensions: arch-test-update
	@riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)

baseline: arch-test-update
	@riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)

arch-test-update: riscv-arch-test
	@riscof arch-test --update

riscv-arch-test:
	@riscof arch-test --clone

clean:
	@echo "Cleaning..."
	@rm -rf $(WORK_DIR) riscv-arch-test

.PHONY: all default baseline extensions arch-test-update clean
