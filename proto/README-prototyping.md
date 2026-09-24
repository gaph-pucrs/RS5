# RS5 FPGA prototyping files

This package contains the complete set of files added so far for the unified
Makefile-driven FPGA prototyping flow.

Place the contents directly inside `RS5/proto/`.

Expected structure:

```text
proto/
├── Makefile
└── scripts/
    ├── prepare_project.tcl
    ├── ip_manage.tcl
    ├── build.tcl
    ├── program.tcl
    ├── filelists/
    │   ├── fpga_common.f
    │   ├── nexys.f
    │   ├── sume.f
    │   ├── nexys_constraints.f
    │   ├── sume_constraints.f
    │   ├── nexys_ips.f
    │   └── sume_ips.f
    └── ip/
        ├── nexys/
        └── sume/
```

The `ip/nexys` and `ip/sume` directories are intentionally empty initially.
They will receive reproducible Vivado IP recipes exported later.

Current intended flow:

```bash
make proto BOARD=sume APP=coremark
make proto BOARD=nexys APP=coremark
```

Important:
- `rtl/rtl.f` remains the common RS5 RTL filelist.
- Platform filelists complement `sim/rtl.f`.
- No `module load` commands are included; tools must already be available in
  the user's environment.
- The IP-management layer is the next component to refine so it consumes the
  platform-specific `*_ips.f` manifests directly.

## Filelist syntax supported by prepare_project.tcl

The parser currently supports:
- source file paths
- `-f <filelist>` recursive inclusion
- `+incdir+<dir>`
- `-incdir <dir>`
- `-incdir=<dir>`
- `-I<dir>` / `-I <dir>`
- blank lines and `#` / `//` comments

Paths are resolved relative to the filelist where they are written.

## v3 fix

`prepare_project.tcl` no longer calls the invalid no-argument `save_project`
command. Project preparation now finishes with `close_project`.

The same invalid call was also removed from the current `ip_manage.tcl`,
although IP management is still a work in progress and should not yet be run
until its `*_ips.f` manifest support is completed.

## v4 - project-specific IP management

`ip_manage.tcl` now consumes the selected platform's `*_ips.f` manifest.

Normal flow:

1. refresh the Vivado IP catalog;
2. inspect only the IPs expected by the selected platform;
3. recreate a missing IP when a committed recipe exists;
4. upgrade an IP when `UPGRADE_VERSIONS` is available;
5. fail if an expected IP remains locked;
6. regenerate all output products;
7. reset stale/failed OOC synthesis runs;
8. write before/after `report_ip_status` reports;
9. create a Tcl recipe automatically if one does not already exist.

`make ip-recipes BOARD=<board>` force-refreshes the recipes for all expected IPs.

`make ips-recreate BOARD=<board>` force-recreates every expected IP from its
committed recipe.

The build script also refuses to start top-level synthesis while any project IP
is locked and resets failed OOC IP runs before launching `synth_1`.

## v5 - DRAM_Vector_RegBank bootstrap recipe

Added an initial `DRAM_Vector_RegBank.tcl` recipe for both SUME and Nexys.

Configuration:
- Distributed Memory Generator v8.0
- simple dual-port RAM
- depth 32
- data width 8
- default non-registered input/output behavior
- no CE
- zero pipeline stages

This allows `make ips BOARD=sume` or `BOARD=nexys` to create the vector
register-bank memory when it is absent from the XPR.

## v6 - application memory generation fix

The Makefile now follows the native RS5 `init_mem.py` interface.

Instead of passing `app/<name>/<name>.bin`, the `mem` target passes the
application directory:

```bash
cd proto
python3 init_mem.py ../app/coremark
```

Equivalent unified command:

```bash
make mem APP=coremark
```

This matches the existing RS5 FPGA prototyping flow.

## v7 - corrected init_mem.py input

`init_mem.py` opens its positional argument as a binary file. The Makefile
therefore passes the compiled application binary again:

```text
MEM_INPUT ?= $(APP_DIR)/$(APP).bin
```

For CoreMark this resolves to:

```text
app/coremark/coremark.bin
```

The path can be overridden for applications whose binary has a different name:

```bash
make mem APP=<app> MEM_INPUT=/path/to/application.bin
```

## v8 - quieter programming stage

`program.tcl` no longer opens the Vivado `.xpr` just to discover the FPGA part.
The selected board's `EXPECTED_PART` is now passed directly by the Makefile.

This removes project-opening noise during `make program`, including unrelated
board-repository warnings and missing `IPUserFilesDir` warnings. Programming
still validates the expected FPGA family against the detected JTAG chain.

## v9 - BRAM initialization is explicit

The bitstream build no longer assumes that the existing `BRAM.xci` is already
configured to load the application image.

`make bitstream` now passes `proto/memimage.coe` to `build.tcl`. Before top-level
synthesis, the script applies:

```tcl
set_property -dict [list \
    CONFIG.Coe_File $mem_coe \
    CONFIG.Load_Init_File true \
] [get_ips BRAM]
```

It then resets and regenerates the BRAM output products and resets the BRAM OOC
run when present. This makes the generated bitstream explicitly depend on the
`memimage.coe` produced by `make mem`.
