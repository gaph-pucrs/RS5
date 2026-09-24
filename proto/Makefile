SHELL := /bin/bash

BOARD      ?= nexys
APP        ?= coremark
JOBS       ?= 8

VIVADO     ?= vivado
PYTHON     ?= python3
GIT        ?= git
TIO        ?= tio

HW_SERVER  ?= localhost:3121
SERIAL     ?= /dev/ttyUSB1
BAUD       ?= 115200

PROTO_DIR    := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
ROOT_DIR     := $(abspath $(PROTO_DIR)/..)
SCRIPT_DIR   := $(PROTO_DIR)/scripts
FILELIST_DIR := $(SCRIPT_DIR)/filelists
APP_DIR      := $(ROOT_DIR)/app/$(APP)
MEM_INPUT    ?= $(APP_DIR)/$(APP).bin
MEM_COE      ?= $(PROTO_DIR)/memimage.coe

ifeq ($(BOARD),nexys)
PROJECT_XPR         := $(PROTO_DIR)/RS5/RS5.xpr
RTL_FILELIST        := $(FILELIST_DIR)/nexys.f
IP_FILELIST         := $(FILELIST_DIR)/nexys_ips.f
CONSTRAINT_FILELIST := $(FILELIST_DIR)/nexys_constraints.f
IP_DIR              := $(SCRIPT_DIR)/ip/nexys
EXPECTED_PART       := xc7a100tcsg324-1
EXPECTED_TOP        := RS5_FPGA_Platform
else ifeq ($(BOARD),sume)
PROJECT_XPR         := $(PROTO_DIR)/RS5_SUME/RS5.xpr
RTL_FILELIST        := $(FILELIST_DIR)/sume.f
IP_FILELIST         := $(FILELIST_DIR)/sume_ips.f
CONSTRAINT_FILELIST := $(FILELIST_DIR)/sume_constraints.f
IP_DIR              := $(SCRIPT_DIR)/ip/sume
EXPECTED_PART       := xc7vx690tffg1761-3
EXPECTED_TOP        := RS5_FPGA_Platform
else
$(error Invalid BOARD='$(BOARD)'. Use BOARD=nexys or BOARD=sume)
endif

PREPARE_TCL := $(SCRIPT_DIR)/prepare_project.tcl
IP_TCL      := $(SCRIPT_DIR)/ip_manage.tcl
BUILD_TCL   := $(SCRIPT_DIR)/build.tcl
PROGRAM_TCL := $(SCRIPT_DIR)/program.tcl

.NOTPARALLEL:

.PHONY: help info check-common check-vivado \
	submodules app mem sources ips prepare \
	ip-recipes ips-recreate bitstream build program proto uart

help:
	@echo ""
	@echo "RS5 FPGA prototyping"
	@echo ""
	@echo "Usage:"
	@echo "  make <target> BOARD=<nexys|sume> APP=<application>"
	@echo ""
	@echo "Main targets:"
	@echo "  app            Compile the selected application"
	@echo "  mem            Generate memimage.coe"
	@echo "  submodules     Initialize/update Git submodules"
	@echo "  sources        Synchronize RTL/constraints from project filelists"
	@echo "  ips            Check/prepare IPs listed by the selected project"
	@echo "  prepare        submodules + sources + IPs"
	@echo "  bitstream      Complete FPGA build up to the bitstream"
	@echo "  program        Program an existing bitstream"
	@echo "  proto          bitstream + program"
	@echo "  uart           Open serial output"
	@echo ""
	@echo "IP maintenance:"
	@echo "  ip-recipes     Export reproducible IP Tcl recipes"
	@echo "  ips-recreate   Force IP recreation from recipes"
	@echo ""

info:
	@echo "BOARD               = $(BOARD)"
	@echo "APP                 = $(APP)"
	@echo "ROOT_DIR            = $(ROOT_DIR)"
	@echo "PROTO_DIR           = $(PROTO_DIR)"
	@echo "APP_DIR             = $(APP_DIR)"
	@echo "MEM_INPUT           = $(MEM_INPUT)"
	@echo "MEM_COE             = $(MEM_COE)"
	@echo "PROJECT_XPR         = $(PROJECT_XPR)"
	@echo "RTL_FILELIST        = $(RTL_FILELIST)"
	@echo "IP_FILELIST         = $(IP_FILELIST)"
	@echo "CONSTRAINT_FILELIST = $(CONSTRAINT_FILELIST)"
	@echo "EXPECTED_PART       = $(EXPECTED_PART)"
	@echo "EXPECTED_TOP        = $(EXPECTED_TOP)"
	@echo "JOBS                = $(JOBS)"
	@echo "VIVADO              = $(VIVADO)"

check-common:
	@command -v "$(GIT)" >/dev/null 2>&1 || { echo "ERROR: Git not found: $(GIT)"; exit 1; }
	@command -v "$(PYTHON)" >/dev/null 2>&1 || { echo "ERROR: Python not found: $(PYTHON)"; exit 1; }

check-vivado:
	@command -v "$(VIVADO)" >/dev/null 2>&1 || { \
		echo "ERROR: Vivado not found: $(VIVADO)"; \
		echo "Make Vivado available in PATH or set VIVADO=/path/to/vivado"; \
		exit 1; \
	}

submodules: check-common
	@"$(GIT)" -C "$(ROOT_DIR)" submodule update --init --recursive
	@test -f "$(ROOT_DIR)/RingBuffer/rtl/RingBuffer.sv" || { \
		echo "ERROR: RingBuffer submodule is not available."; \
		exit 1; \
	}

app:
	@test -d "$(APP_DIR)" || { echo "ERROR: Application directory not found: $(APP_DIR)"; exit 1; }
	$(MAKE) -C "$(APP_DIR)"

mem: app check-common
	@test -f "$(MEM_INPUT)" || { \
		echo "ERROR: Application binary not found: $(MEM_INPUT)"; \
		echo "Set MEM_INPUT=/path/to/application.bin if this application uses another filename."; \
		exit 1; \
	}
	cd "$(PROTO_DIR)" && "$(PYTHON)" init_mem.py "$(MEM_INPUT)"

sources: submodules check-vivado
	@test -f "$(PREPARE_TCL)" || { echo "ERROR: Missing $(PREPARE_TCL)"; exit 1; }
	@test -f "$(RTL_FILELIST)" || { echo "ERROR: Missing $(RTL_FILELIST)"; exit 1; }
	@test -f "$(CONSTRAINT_FILELIST)" || { echo "ERROR: Missing $(CONSTRAINT_FILELIST)"; exit 1; }
	"$(VIVADO)" -mode batch \
		-source "$(PREPARE_TCL)" \
		-tclargs \
			"$(PROJECT_XPR)" \
			"$(RTL_FILELIST)" \
			"$(CONSTRAINT_FILELIST)" \
			"$(EXPECTED_PART)" \
			"$(EXPECTED_TOP)"

ips: sources check-vivado
	@test -f "$(IP_TCL)" || { echo "ERROR: Missing $(IP_TCL)"; exit 1; }
	@test -f "$(IP_FILELIST)" || { echo "ERROR: Missing $(IP_FILELIST)"; exit 1; }
	"$(VIVADO)" -mode batch \
		-source "$(IP_TCL)" \
		-tclargs "$(PROJECT_XPR)" check "$(IP_FILELIST)" "$(IP_DIR)"

prepare: ips

ip-recipes: sources check-vivado
	@test -f "$(IP_TCL)" || { echo "ERROR: Missing $(IP_TCL)"; exit 1; }
	"$(VIVADO)" -mode batch \
		-source "$(IP_TCL)" \
		-tclargs "$(PROJECT_XPR)" export "$(IP_FILELIST)" "$(IP_DIR)"

ips-recreate: sources check-vivado
	@test -f "$(IP_TCL)" || { echo "ERROR: Missing $(IP_TCL)"; exit 1; }
	"$(VIVADO)" -mode batch \
		-source "$(IP_TCL)" \
		-tclargs "$(PROJECT_XPR)" recreate "$(IP_FILELIST)" "$(IP_DIR)"

bitstream: mem prepare check-vivado
	@test -f "$(BUILD_TCL)" || { echo "ERROR: Missing $(BUILD_TCL)"; exit 1; }
	@test -f "$(MEM_COE)" || { echo "ERROR: Memory initialization file not found: $(MEM_COE)"; exit 1; }
	"$(VIVADO)" -mode batch \
		-source "$(BUILD_TCL)" \
		-tclargs "$(PROJECT_XPR)" "$(MEM_COE)" "$(JOBS)"

build: bitstream

program: check-vivado
	@test -f "$(PROGRAM_TCL)" || { echo "ERROR: Missing $(PROGRAM_TCL)"; exit 1; }
	"$(VIVADO)" -mode batch \
		-source "$(PROGRAM_TCL)" \
		-tclargs "$(PROJECT_XPR)" "$(EXPECTED_PART)" "$(HW_SERVER)"

proto: bitstream
	$(MAKE) --no-print-directory program \
		BOARD="$(BOARD)" APP="$(APP)" \
		VIVADO="$(VIVADO)" HW_SERVER="$(HW_SERVER)"

uart:
	@command -v "$(TIO)" >/dev/null 2>&1 || { echo "ERROR: tio not found: $(TIO)"; exit 1; }
	"$(TIO)" "$(SERIAL)" -b "$(BAUD)" --map ICRNL,INLCRNL
