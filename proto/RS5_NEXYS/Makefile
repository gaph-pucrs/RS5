SHELL := /bin/bash

# ---------------------------------------------------------------------
# User configuration
# ---------------------------------------------------------------------

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
COMMON_DIR   := $(PROTO_DIR)/common

PROJECT_XPR := $(PLATFORM_DIR)/RS5.xpr

RTL_FILELIST      := $(PLATFORM_DIR)/filelists/nexys.f
CONSTRAINT_FILELIST   := $(PLATFORM_DIR)/filelists/constraints.f
IP_MANIFEST   := $(PLATFORM_DIR)/filelists/ips.f
IP_DIR        := $(PLATFORM_DIR)/ips

APP_DIR   := $(ROOT_DIR)/app/$(APP)

MEM_INPUT := $(APP_DIR)/$(APP).bin
MEM_COE   := $(PLATFORM_DIR)/memimage.coe


REPORT_DIR := $(PLATFORM_DIR)/reports


# ---------------------------------------------------------------------
# Nexys A7 configuration
# ---------------------------------------------------------------------

EXPECTED_PART := xc7a100tcsg324-1
HW_TARGET ?=
EXPECTED_TOP  := RS5_FPGA_Platform
EXPECTED_DEVICE := xc7a100t


export HW_TARGET

# ---------------------------------------------------------------------
# Vivado scripts
# ---------------------------------------------------------------------

PREPARE_TCL := $(COMMON_DIR)/tcl/prepare_project.tcl
IP_TCL      := $(COMMON_DIR)/tcl/ip_manage.tcl

SYNTH_TCL   := $(COMMON_DIR)/tcl/synth.tcl
IMPL_TCL    := $(COMMON_DIR)/tcl/impl.tcl
REPORT_TCL	:= $(COMMON_DIR)/tcl/reports.tcl
BUILD_TCL   := $(COMMON_DIR)/tcl/build.tcl

PROGRAM_TCL := $(COMMON_DIR)/tcl/program.tcl


# ---------------------------------------------------------------------
# Generated files
# ---------------------------------------------------------------------

SYNTH_DCP := $(REPORT_DIR)/post_synth.dcp
ROUTE_DCP := $(REPORT_DIR)/post_route.dcp
BITSTREAM := $(REPORT_DIR)/RS5.bit


MEM_STAMP := $(REPORT_DIR)/.mem-$(APP)

TIMING_RPT := $(REPORT_DIR)/timing_summary.rpt
UTIL_RPT   := $(REPORT_DIR)/utilization.rpt
POWER_RPT  := $(REPORT_DIR)/power.rpt

REPORT_STAMP := $(REPORT_DIR)/.reports

# ---------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------

RTL_SOURCES := $(shell find "$(ROOT_DIR)/rtl" \
	-type f \( \
	-name '*.sv' -o \
	-name '*.v' -o \
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
	$(COMMON_DIR)/rtl/Peripherals.sv \
	$(COMMON_DIR)/rtl/UART_RX_CTRL.sv \
	$(COMMON_DIR)/rtl/UART_TX_CTRL.vhd \
	$(COMMON_DIR)/rtl/Debouncer.vhd \
	$(PLATFORM_DIR)/RS5_FPGA_Platform_NEXYS.sv


XDC_SOURCES := $(shell find "$(PLATFORM_DIR)" \
	-type f -name '*.xdc' 2>/dev/null)


IP_RECIPES := $(wildcard $(IP_DIR)/*.tcl)


SOURCES := \
	$(RTL_SOURCES) \
	$(XDC_SOURCES) \
	$(IP_RECIPES) \
	$(RTL_FILELIST) \
	$(IP_MANIFEST) \
	$(CONSTRAINT_FILELIST)



# ---------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------

.DEFAULT_GOAL := impl


.PHONY: all help app mem prepare synth impl reports bit flash monitor clean


all: bit



help:
	@echo "RS5 Nexys A7 FPGA Automation"
	@echo ""
	@echo "Usage:"
	@echo "  make [target] APP=<application>"
	@echo ""
	@echo "Targets:"
	@echo "  all       Build bitstream"
	@echo "  app       Compile application"
	@echo "  mem       Generate memimage.coe"
	@echo "  prepare   Prepare Vivado project/IPs"
	@echo "  synth     Run synthesis"
	@echo "  impl      Run implementation"
	@echo "  bit       Generate bitstream"
	@echo "  flash     Program FPGA"
	@echo "  monitor   Open UART monitor"
	@echo "  clean     Remove generated files"
	@echo ""
	@echo "Examples:"
	@echo "  make"
	@echo "  make bit APP=hello"
	@echo "  make flash APP=coremark"



# ---------------------------------------------------------------------
# Application
# ---------------------------------------------------------------------

app:
	$(MAKE) -C "$(APP_DIR)"



# ---------------------------------------------------------------------
# Memory image
# ---------------------------------------------------------------------



$(MEM_INPUT):
	$(MAKE) -C "$(APP_DIR)"


$(MEM_STAMP): $(MEM_INPUT) $(COMMON_DIR)/init_mem.py
	@mkdir -p "$(REPORT_DIR)"
	@rm -f "$(REPORT_DIR)"/.mem-*
	@"$(PYTHON)" "$(COMMON_DIR)/init_mem.py" "$(MEM_INPUT)" "$(MEM_COE)"
	@touch "$@"


mem: $(MEM_STAMP)



# ---------------------------------------------------------------------
# Vivado preparation
# ---------------------------------------------------------------------

prepare:

	"$(GIT)" -C "$(ROOT_DIR)" submodule update --init --recursive

	"$(VIVADO)" \
	-mode batch \
	-source "$(PREPARE_TCL)" \
	-tclargs \
	"$(PROJECT_XPR)" \
	"$(RTL_FILELIST)" \
	"$(CONSTRAINT_FILELIST)" \
	"$(EXPECTED_PART)" \
	"$(EXPECTED_TOP)"


	"$(VIVADO)" \
	-mode batch \
	-source "$(IP_TCL)" \
	-tclargs \
	"$(PROJECT_XPR)" \
	check \
	"$(IP_MANIFEST)" \
	"$(IP_DIR)"



# ---------------------------------------------------------------------
# FPGA flow
# ---------------------------------------------------------------------

$(SYNTH_DCP): $(MEM_STAMP) $(SOURCES)

	@mkdir -p "$(REPORT_DIR)"

	$(MAKE) prepare

	"$(VIVADO)" \
	-mode batch \
	-source "$(SYNTH_TCL)" \
	-tclargs \
	"$(PROJECT_XPR)" \
	"$(MEM_COE)" \
	"$(SYNTH_DCP)"


synth: $(SYNTH_DCP)



$(ROUTE_DCP): $(SYNTH_DCP)

	"$(VIVADO)" \
	-mode batch \
	-source "$(IMPL_TCL)" \
	-tclargs \
	"$(SYNTH_DCP)" \
	"$(ROUTE_DCP)"

$(REPORT_STAMP): $(ROUTE_DCP) $(REPORT_TCL)

	"$(VIVADO)" \
	-mode batch \
	-source "$(REPORT_TCL)" \
	-tclargs \
	"$(ROUTE_DCP)" \
	"$(REPORT_DIR)"

	@touch "$@"


reports: $(REPORT_STAMP)

impl: $(REPORT_STAMP)

$(BITSTREAM): $(ROUTE_DCP) $(REPORT_STAMP)

	"$(VIVADO)" \
	-mode batch \
	-source "$(BUILD_TCL)" \
	-tclargs \
	"$(ROUTE_DCP)" \
	"$(BITSTREAM)"


bit: $(BITSTREAM)



# ---------------------------------------------------------------------
# Programming
# ---------------------------------------------------------------------

flash: $(BITSTREAM)

	"$(VIVADO)" \
	-mode batch \
	-source "$(PROGRAM_TCL)" \
	-tclargs \
	"$(BITSTREAM)" \
	"$(HW_SERVER)" \
	"$(EXPECTED_DEVICE)"



# ---------------------------------------------------------------------
# UART
# ---------------------------------------------------------------------

monitor:

	"$(TIO)" "$(SERIAL)" \
	-b "$(BAUD)" \
	--map ICRNL,INLCRNL



# ---------------------------------------------------------------------
# Cleanup
# ---------------------------------------------------------------------

clean:

	rm -rf "$(REPORT_DIR)"

	rm -rf "$(PLATFORM_DIR)/.Xil"

	rm -f "$(PLATFORM_DIR)"/*.jou
	rm -f "$(PLATFORM_DIR)"/*.log
