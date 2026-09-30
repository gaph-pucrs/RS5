SHELL := /bin/bash

APP       ?= coremark
VIVADO    ?= vivado
PYTHON    ?= python3
GIT       ?= git
TIO       ?= tio

HW_SERVER ?= localhost:3121
SERIAL    ?= /dev/ttyUSB1
BAUD      ?= 115200

# ---------------------------------------------------------------------
# Directories
# ---------------------------------------------------------------------

PLATFORM_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PROTO_DIR    := $(abspath $(PLATFORM_DIR)/..)
ROOT_DIR     := $(abspath $(PROTO_DIR)/..)

SCRIPTS_DIR  := $(PROTO_DIR)/scripts
FILELIST_DIR := $(SCRIPTS_DIR)/filelists

APP_DIR      := $(ROOT_DIR)/app/$(APP)
MEM_INPUT    := $(APP_DIR)/$(APP).bin
MEM_COE      := $(PROTO_DIR)/memimage.coe

BUILD_DIR    := $(PLATFORM_DIR)/build

# ---------------------------------------------------------------------
# Platform configuration
# ---------------------------------------------------------------------

RTL_FILELIST        := $(FILELIST_DIR)/sume.f
IP_FILELIST         := $(FILELIST_DIR)/sume_ips.f
CONSTRAINT_FILELIST := $(FILELIST_DIR)/sume_constraints.f

IP_DIR := $(SCRIPTS_DIR)/ip/sume

PROJECT_XPR := $(PLATFORM_DIR)/RS5.xpr

EXPECTED_PART := xc7vx690tffg1761-3
EXPECTED_TOP  := RS5_FPGA_Platform
EXPECTED_DEVICE := xc7vx690t

# ---------------------------------------------------------------------
# Scripts
# ---------------------------------------------------------------------

PREPARE_TCL := $(SCRIPTS_DIR)/prepare_project.tcl
IP_TCL      := $(SCRIPTS_DIR)/ip_manage.tcl

SYNTH_TCL   := $(SCRIPTS_DIR)/synth.tcl
IMPL_TCL    := $(SCRIPTS_DIR)/impl.tcl
BUILD_TCL   := $(SCRIPTS_DIR)/build.tcl
PROGRAM_TCL := $(SCRIPTS_DIR)/program.tcl

# ---------------------------------------------------------------------
# Generated files
# ---------------------------------------------------------------------

SYNTH_DCP := $(BUILD_DIR)/post_synth.dcp
ROUTE_DCP := $(BUILD_DIR)/post_route.dcp
BITSTREAM := $(BUILD_DIR)/RS5.bit

MEM_STAMP := $(BUILD_DIR)/.mem-$(APP)

# ---------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------

RTL_SOURCES := $(shell find "$(ROOT_DIR)/rtl" \
	-type f \( \
	-name '*.sv' -o \
	-name '*.v'  -o \
	-name '*.vhd' -o \
	-name '*.vh' -o \
	-name '*.svh' \
	\) 2>/dev/null)

RTL_SOURCES += $(shell find "$(ROOT_DIR)/RingBuffer/rtl" \
	-type f \( \
	-name '*.sv' -o \
	-name '*.v' \
	\) 2>/dev/null)

RTL_SOURCES += \
	$(PROTO_DIR)/Peripherals.sv \
	$(PROTO_DIR)/UART_RX_CTRL.sv \
	$(PROTO_DIR)/UART_TX_CTRL.vhd \
	$(PROTO_DIR)/Debouncer.vhd \
	$(PLATFORM_DIR)/RS5_FPGA_Platform_SUME.sv

CONSTRAINTS := $(shell find "$(PLATFORM_DIR)" \
	-type f -name '*.xdc' 2>/dev/null)

IP_RECIPES := $(wildcard $(IP_DIR)/*.tcl)

SOURCES := \
	$(RTL_SOURCES) \
	$(CONSTRAINTS) \
	$(IP_RECIPES) \
	$(RTL_FILELIST) \
	$(IP_FILELIST) \
	$(CONSTRAINT_FILELIST)

# ---------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------

.DEFAULT_GOAL := all

.PHONY: all app mem synth impl bit flash monitor clean prepare

all: bit

app:
	$(MAKE) -C "$(APP_DIR)"

mem: $(MEM_STAMP)

synth: $(SYNTH_DCP)

impl: $(ROUTE_DCP)

bit: $(BITSTREAM)

# ---------------------------------------------------------------------
# Application / memory
# ---------------------------------------------------------------------

$(MEM_INPUT):
	$(MAKE) -C "$(APP_DIR)"

$(MEM_STAMP): $(MEM_INPUT) $(PROTO_DIR)/init_mem.py
	@mkdir -p "$(BUILD_DIR)"
	@rm -f "$(BUILD_DIR)"/.mem-*
	cd "$(PROTO_DIR)" && "$(PYTHON)" init_mem.py "$(MEM_INPUT)"
	@touch "$@"

# ---------------------------------------------------------------------
# Project / IP preparation
# ---------------------------------------------------------------------

prepare:
	"$(GIT)" -C "$(ROOT_DIR)" submodule update --init --recursive

	"$(VIVADO)" -mode batch \
		-source "$(PREPARE_TCL)" \
		-tclargs \
		"$(PROJECT_XPR)" \
		"$(RTL_FILELIST)" \
		"$(CONSTRAINT_FILELIST)" \
		"$(EXPECTED_PART)" \
		"$(EXPECTED_TOP)"

	"$(VIVADO)" -mode batch \
		-source "$(IP_TCL)" \
		-tclargs \
		"$(PROJECT_XPR)" \
		check \
		"$(IP_FILELIST)" \
		"$(IP_DIR)"

# ---------------------------------------------------------------------
# FPGA flow
# ---------------------------------------------------------------------

$(SYNTH_DCP): $(MEM_STAMP) $(SOURCES)
	@mkdir -p "$(BUILD_DIR)"

	$(MAKE) prepare

	"$(VIVADO)" -mode batch \
		-source "$(SYNTH_TCL)" \
		-tclargs \
		"$(PROJECT_XPR)" \
		"$(MEM_COE)" \
		"$(SYNTH_DCP)" \
		-log "$(BUILD_DIR)/synth.log" \
		-journal "$(BUILD_DIR)/synth.jou"

$(ROUTE_DCP): $(SYNTH_DCP)
	"$(VIVADO)" -mode batch \
		-source "$(IMPL_TCL)" \
		-tclargs \
		"$(SYNTH_DCP)" \
		"$(ROUTE_DCP)" \
		-log "$(BUILD_DIR)/impl.log" \
		-journal "$(BUILD_DIR)/impl.jou"

$(BITSTREAM): $(ROUTE_DCP)
	"$(VIVADO)" -mode batch \
		-source "$(BUILD_TCL)" \
		-tclargs \
		"$(ROUTE_DCP)" \
		"$(BITSTREAM)" \
		-log "$(BUILD_DIR)/bit.log" \
		-journal "$(BUILD_DIR)/bit.jou"

# ---------------------------------------------------------------------
# FPGA programming
# ---------------------------------------------------------------------

flash: $(BITSTREAM)
	"$(VIVADO)" -mode batch \
		-source "$(PROGRAM_TCL)" \
		-tclargs \
		"$(BITSTREAM)" \
		"$(HW_SERVER)" \
		"$(EXPECTED_DEVICE)"

monitor:
	"$(TIO)" "$(SERIAL)" \
		-b "$(BAUD)" \
		--map ICRNL,INLCRNL

# ---------------------------------------------------------------------
# Cleanup
# ---------------------------------------------------------------------

clean:
	rm -rf "$(BUILD_DIR)"
	rm -rf "$(PLATFORM_DIR)/.Xil"
	rm -f "$(PLATFORM_DIR)"/vivado*.jou
	rm -f "$(PLATFORM_DIR)"/vivado*.log

# ---------------------------------------------------------------------
# Help
# ---------------------------------------------------------------------

help:
	@echo "RS5 SUME FPGA Automation"
	@echo ""
	@echo "Usage:"
	@echo "  make [target] [APP=<application>]"
	@echo ""
	@echo "Targets:"
	@echo "  all       Build the FPGA bitstream (default)"
	@echo "  app       Build the selected application"
	@echo "  mem       Generate memimage.coe"
	@echo "  prepare   Prepare Vivado project and IPs"
	@echo "  synth     Run synthesis"
	@echo "  impl      Run implementation"
	@echo "  bit       Generate the FPGA bitstream"
	@echo "  flash     Generate and program the FPGA bitstream"
	@echo "  monitor   Open the serial monitor"
	@echo "  clean     Remove generated build files"
	@echo "  help      Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  APP        Application to build (default: coremark)"
	@echo "  SERIAL     Serial device (default: /dev/ttyUSB1)"
	@echo "  BAUD       Serial baud rate (default: 115200)"
	@echo "  HW_SERVER  Vivado hardware server (default: localhost:3121)"
	@echo ""
	@echo "Examples:"
	@echo "  make"
	@echo "  make bit APP=hello"
	@echo "  make flash APP=coremark"
	@echo "  make monitor"
	@echo "  make monitor SERIAL=/dev/ttyUSB0"
	@echo "  make clean"
