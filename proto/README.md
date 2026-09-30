# RS5 FPGA Prototyping

FPGA prototyping is organized per platform. Each supported board has its
own Vivado project, top-level RTL file and Makefile, while sharing the
common FPGA automation scripts.

Currently supported platforms:

- Digilent Nexys A7
- NetFPGA SUME

Two FPGA prototyping flows are available:

1. **Automated flow** — uses the platform Makefile and is recommended for
   normal development.
2. **Manual Vivado flow** — performs the FPGA flow directly through Vivado
   and is useful for debugging, inspecting intermediate stages or developing
   the automation itself.

Both flows use the same RTL sources, constraints, Vivado projects and IPs.

---

## Directory structure

```text
proto/
├── README.md
├── init_mem.py
├── memimage.coe
├── Peripherals.sv
├── UART_RX_CTRL.sv
├── UART_TX_CTRL.vhd
├── Debouncer.vhd
│
├── scripts/
│   ├── synth.tcl
│   ├── impl.tcl
│   ├── build.tcl
│   ├── program.tcl
│   ├── prepare_project.tcl
│   ├── ip_manage.tcl
│   │
│   ├── filelists/
│   │   ├── fpga_common.f
│   │   ├── nexys.f
│   │   ├── nexys_constraints.f
│   │   ├── nexys_ips.f
│   │   ├── sume.f
│   │   ├── sume_constraints.f
│   │   └── sume_ips.f
│   │
│   └── ip/
│       ├── nexys/
│       └── sume/
│
├── RS5_NEXYS/
│   ├── Makefile
│   ├── RS5.xpr
│   └── RS5_FPGA_Platform_NEXYS.sv
│
└── RS5_SUME/
    ├── Makefile
    ├── RS5.xpr
    └── RS5_FPGA_Platform_SUME.sv
```

Platform-specific files are kept inside their corresponding directories,
while common RTL and automation scripts are shared.

## Requirements

- Xilinx Vivado
- GNU Make
- Python 3
- Git
- RISC-V toolchain
- `tio` for UART monitoring

# Automated flow

The automated flow is controlled by a Makefile inside each platform
directory.

The Makefile is responsible for determining when a stage must be rebuilt,
while the Tcl scripts execute the corresponding Vivado operation.

The intended separation is:

```text
GNU Make
   |
   | decides what must be rebuilt
   v
Tcl scripts
   |
   | execute the requested FPGA stage
   v
Vivado
```

---

## Selecting a platform

### NetFPGA SUME

```bash
cd proto/RS5_SUME
```

### Nexys A7

```bash
cd proto/RS5_NEXYS
```

All following Make commands are executed from the selected platform
directory.

---

## Building the FPGA

The default application is:

```text
coremark
```

Therefore:

```bash
make
```

is equivalent to:

```bash
make APP=coremark
```

and performs the complete build up to the FPGA bitstream.

A different application can be selected with `APP`:

```bash
make APP=hello
```

or:

```bash
make bit APP=hello
```

---

## Build dependency chain

The FPGA build follows the dependency chain:

```text
application binary
       |
       v
  memimage.coe
       |
       v
post_synth.dcp
       |
       v
post_route.dcp
       |
       v
    RS5.bit
```

The generated FPGA files are stored under:

```text
build/
```

For example:

```text
build/
├── post_synth.dcp
├── post_route.dcp
└── RS5.bit
```

GNU Make uses these files and their dependencies to determine whether a
stage needs to be executed again.

If nothing relevant has changed, a second:

```bash
make bit APP=hello
```

should not repeat synthesis, implementation or bitstream generation.

---

## Application build

To explicitly compile the selected application:

```bash
make app APP=hello
```

The application is built from:

```text
app/<application>/
```

For example:

```text
app/coremark/
app/hello/
```

### Application source changes

If the source code of an application is modified, explicitly rebuild the
application before rebuilding the FPGA:

```bash
make app APP=hello
make bit APP=hello
```

This ensures that the application binary used to generate `memimage.coe`
contains the latest software changes.

---

## BRAM initialization

The selected application binary is converted into:

```text
proto/memimage.coe
```

using:

```text
proto/init_mem.py
```

To generate the memory image explicitly:

```bash
make mem APP=coremark
```

The automated flow configures the BRAM initialization during synthesis.

---

## Project and IP preparation

Before synthesis, the Vivado project and required IPs can be prepared with:

```bash
make prepare
```

This stage uses:

```text
scripts/prepare_project.tcl
scripts/ip_manage.tcl
```

The project preparation script handles:

- RTL sources
- include directories
- constraints
- FPGA part validation
- top-module configuration

The IP management script handles the IPs required by the selected platform.

Project preparation is automatically executed when synthesis needs to be
rebuilt, so running `make prepare` manually is normally unnecessary.

---

## Synthesis

To run only the required stages up to synthesis:

```bash
make synth APP=hello
```

The synthesis stage generates:

```text
build/post_synth.dcp
```

The corresponding shared script is:

```text
scripts/synth.tcl
```

---

## Implementation

To run the required stages up to implementation:

```bash
make impl APP=hello
```

Implementation uses the synthesis checkpoint and generates:

```text
build/post_route.dcp
```

The corresponding shared script is:

```text
scripts/impl.tcl
```

This stage performs the main implementation operations, including placement
and routing.

Generated reports may also be written to the build directory.

---

## Bitstream generation

To generate the FPGA bitstream:

```bash
make bit APP=hello
```

The generated bitstream is:

```text
build/RS5.bit
```

The corresponding shared script is:

```text
scripts/build.tcl
```

The default Make target is the bitstream build, so:

```bash
make APP=hello
```

and:

```bash
make bit APP=hello
```

perform the same final build target.

---

## FPGA programming

To build the bitstream if necessary and program the FPGA:

```bash
make flash APP=hello
```

Programming is performed by:

```text
scripts/program.tcl
```

Each platform Makefile defines the expected FPGA device.

For example, the SUME configuration uses values equivalent to:

```makefile
EXPECTED_PART   := xc7vx690tffg1761-3
EXPECTED_TOP    := RS5_FPGA_Platform
EXPECTED_DEVICE := xc7vx690t
```

The Nexys A7 uses its corresponding Artix-7 part and programming device.

The distinction is intentional:

- `EXPECTED_PART` identifies the FPGA part used by the Vivado project.
- `EXPECTED_TOP` identifies the HDL top module.
- `EXPECTED_DEVICE` identifies the FPGA in the JTAG chain during
  programming.

This is particularly important on boards such as the NetFPGA SUME, where
multiple programmable devices may appear in the JTAG chain.

The default hardware server is:

```text
localhost:3121
```

It can be overridden:

```bash
make flash APP=hello HW_SERVER=localhost:3121
```

---

## Serial monitoring

UART output can be monitored in a separate terminal with:

```bash
make monitor
```

The default baud rate is:

```text
115200
```

A serial device can be specified explicitly:

```bash
make monitor SERIAL=/dev/ttyUSB0
```

or:

```bash
make monitor SERIAL=/dev/ttyUSB1
```

When available, a persistent device path under:

```text
/dev/serial/by-id/
```

can also be used.

For example:

```bash
make monitor SERIAL=/dev/serial/by-id/usb-Digilent_Digilent_USB_Device_<id>-if01-port0
```

The actual device depends on the board and host environment.

To exit `tio`, press:

```text
Ctrl+T
Q
```

---

## Cleaning generated files

To remove the generated FPGA build products:

```bash
make clean
```

This removes files generated by the automation without deleting platform
sources, constraints, Tcl scripts, IP definitions or the Vivado project.

After cleaning, the next build starts again from the FPGA build stages.

---

## Available Make targets

Run:

```bash
make help
```

to display the available commands.

Main targets:

```text
make            complete FPGA build (same as make bit)
make app        compile the selected application
make mem        generate proto/memimage.coe
make prepare    prepare the Vivado project and required IPs
make synth      generate build/post_synth.dcp
make impl       generate build/post_route.dcp
make bit        generate build/RS5.bit
make flash      build if necessary and program the FPGA
make monitor    open the UART serial monitor
make clean      remove generated FPGA build products
make help       display the available commands
```

Examples:

```bash
make
make app APP=hello
make mem APP=hello
make synth APP=hello
make impl APP=hello
make bit APP=hello
make flash APP=hello
make monitor
make clean
```

---

## Platform Makefile variables

Some useful variables can be overridden directly from the command line.

### Application

```bash
make APP=hello
```

Default:

```text
coremark
```

### Vivado executable

```bash
make VIVADO=vivado
```

### Python executable

```bash
make PYTHON=python3
```

### Serial device

```bash
make monitor SERIAL=/dev/ttyUSB0
```

### Baud rate

```bash
make monitor BAUD=115200
```

### Hardware server

```bash
make flash HW_SERVER=localhost:3121
```

Platform-specific configuration such as the FPGA part, top module and JTAG
device is defined directly in the respective Makefile.

---

## Shared memory image

The file:

```text
proto/memimage.coe
```

is shared between the FPGA platforms.

This means that builds for different boards use the same BRAM initialization
file.

When switching between platforms while also switching applications, avoid
running conflicting builds simultaneously.

If a platform was previously built using another memory image and there is
any doubt about the current build state, clean the platform before
rebuilding:

```bash
make clean
make bit APP=<application>
```

---

# Manual Vivado flow

The FPGA flow can also be performed manually without using the platform
Makefile.

This is useful for:

- inspecting the Vivado project;
- debugging synthesis or implementation;
- inspecting individual IPs;
- modifying constraints;
- analyzing reports;
- developing or debugging the automation scripts.

The manual and automated flows use the same design.

---

## 1. Build the application

From the RS5 repository root, compile the desired application.

For CoreMark:

```bash
make -C app/coremark
```

For another application:

```bash
make -C app/<application>
```

The resulting binary is expected inside the corresponding application
directory.

For example:

```text
app/coremark/coremark.bin
```

---

## 2. Generate the BRAM initialization file

Enter the `proto` directory:

```bash
cd proto
```

Generate `memimage.coe` from the application binary:

```bash
python3 init_mem.py ../app/coremark/coremark.bin
```

This generates or updates:

```text
proto/memimage.coe
```

For another application:

```bash
python3 init_mem.py ../app/<application>/<application>.bin
```

---

## 3. Open the Vivado project

For Nexys A7:

```text
proto/RS5_NEXYS/RS5.xpr
```

For NetFPGA SUME:

```text
proto/RS5_SUME/RS5.xpr
```

The project can be opened using the Vivado GUI.

---

## 4. Verify project sources and constraints

Ensure that the correct platform top-level file is present.

For Nexys A7:

```text
RS5_NEXYS/RS5_FPGA_Platform_NEXYS.sv
```

For NetFPGA SUME:

```text
RS5_SUME/RS5_FPGA_Platform_SUME.sv
```

Also verify that the correct platform constraints are included.

The top-level filename and module name may differ. The Vivado project top
must correspond to the actual SystemVerilog module declaration.

---

## 5. Update the BRAM initialization

Ensure that the BRAM IP uses:

```text
proto/memimage.coe
```

as its initialization file.

Whenever `memimage.coe` changes, regenerate the BRAM output products before
running synthesis so that the new application is included in the FPGA
image.

In the Vivado GUI this can be done through the BRAM IP options, including
resetting/regenerating output products when required.

---

## 6. Verify the required IPs

Check that the platform-specific IPs are available and generated.

The automated flow stores IP manifests under:

```text
scripts/filelists/
```

and IP creation recipes under:

```text
scripts/ip/
```

These files can be used as a reference when manually restoring or checking
the Vivado project.

---

## 7. Run synthesis

Run synthesis from Vivado.

Verify that synthesis completes successfully before proceeding.

The automated equivalent is:

```bash
make synth APP=<application>
```

---

## 8. Run implementation

Run implementation through routing.

The automated equivalent is:

```bash
make impl APP=<application>
```

Review timing and utilization reports when required.

---

## 9. Generate the bitstream

Generate the FPGA bitstream from Vivado.

The automated equivalent is:

```bash
make bit APP=<application>
```

---

## 10. Program the FPGA

Open the Vivado Hardware Manager.

Connect to the hardware server and open the target board.

Select the correct FPGA in the JTAG chain and program it using the generated
bitstream.

The automated equivalent is:

```bash
make flash APP=<application>
```

When using the NetFPGA SUME, ensure that the Virtex-7 FPGA is selected
instead of another programmable device in the JTAG chain.

---

## 11. Monitor UART output

Serial output uses 115200 baud.

For example:

```bash
tio /dev/ttyUSB1 -b 115200 --map ICRNL,INLCRNL
```

The serial device may vary between systems.

Available serial interfaces can be inspected with:

```bash
ls -l /dev/ttyUSB*
```

or:

```bash
ls -l /dev/serial/by-id/
```

The automated equivalent is:

```bash
make monitor
```

---

# Relationship between manual and automated flows

The Makefile automation performs the same main FPGA operations documented in
the manual flow.

```text
Manual operation                 Automated target
-----------------------------------------------------------
Build application               make app
Generate memimage.coe           make mem
Prepare project and IPs         make prepare
Run synthesis                   make synth
Run implementation              make impl
Generate bitstream              make bit
Program FPGA                    make flash
Open serial terminal            make monitor
```

---

# Automation scripts

The common automation scripts are stored under:

```text
proto/scripts/
```

Their main responsibilities are:

```text
prepare_project.tcl
    Prepare and validate project sources, constraints, FPGA part and top.

ip_manage.tcl
    Check and prepare platform-specific Vivado IPs.

synth.tcl
    Run synthesis and generate post_synth.dcp.

impl.tcl
    Open the synthesis checkpoint, run implementation and generate
    post_route.dcp.

build.tcl
    Open the routed checkpoint and generate the FPGA bitstream.

program.tcl
    Connect to Vivado Hardware Manager, select the expected FPGA device
    and program the generated bitstream.
```

The scripts are shared between the supported FPGA platforms whenever
possible.

---

# Filelists

Source organization is defined under:

```text
proto/scripts/filelists/
```

Common FPGA sources can be shared through:

```text
fpga_common.f
```

while each platform has its own filelists.

For example:

```text
nexys.f
nexys_constraints.f
nexys_ips.f

sume.f
sume_constraints.f
sume_ips.f
```

This allows the same automation scripts to support different FPGA platforms
without hardcoding their source files.

---

# IP maintenance

Platform-specific IP information is stored under:

```text
proto/scripts/ip/
```

For example:

```text
scripts/ip/
├── nexys/
└── sume/
```

The corresponding IP manifests are located under:

```text
scripts/filelists/
```

IP verification and preparation are handled by:

```text
scripts/ip_manage.tcl
```

during:

```bash
make prepare
```

and automatically before a synthesis rebuild when required.

---

# Generated files

FPGA build products are stored inside the platform's:

```text
build/
```

directory.

Typical files include:

```text
post_synth.dcp
post_route.dcp
RS5.bit
timing_summary.rpt
utilization.rpt
```

Vivado logs, journals, checkpoints, bitstreams and reports are generated
artifacts and should not be treated as source files.

Generated `*.rpt` reports are intentionally ignored by Git.

Use:

```bash
make clean
```

to remove generated platform build products.