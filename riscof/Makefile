WORK_DIR ?= ./riscof_work

default: run

run: arch-test-update
	@riscof run --suite=riscv-arch-test/riscv-test-suite --env=riscv-arch-test/riscv-test-suite/env --work-dir=$(WORK_DIR)

arch-test-update: riscv-arch-test
	@riscof arch-test --update

riscv-arch-test:
	@riscof arch-test --clone

clean:
	@echo "Cleaning..."
	@rm -rf $(WORK_DIR) riscv-arch-test

.PHONY: run arch-test-update clean
