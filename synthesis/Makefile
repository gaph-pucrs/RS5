# RS5 logical synthesis (Cadence Genus)
#
#   make          # run run_logical_synthesis.tcl inside work/
#   make clean    # remove work/ (results/ is kept)
#
# Genus must already be in PATH. Reports, netlists and the Innovus export
# go to results/; Genus temp files (logs, cmd history, fv/) stay in work/.

SYNTH_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
WORK_DIR  := $(SYNTH_DIR)/work

.PHONY: synth clean

synth:
	mkdir -p $(WORK_DIR)
	cd $(WORK_DIR) && genus -f $(SYNTH_DIR)/run_logical_synthesis.tcl -execute "set SYNTH_DIR $(SYNTH_DIR)"

clean:
	rm -rf $(WORK_DIR)
