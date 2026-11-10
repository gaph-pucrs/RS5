# Xosvm

Xosvm is a RISC-V ISA extension for **O**ffset and **S**ize **V**irtual **M**emory.
This extension provides basic virtual memory support for RISC-V using only M-Mode and U-Mode targeted at embedded systems, removing the need to add Sv32 and S-Mode.

Each task lives in one contiguous page, split in three regions:

| Region | Addresses | Fetch | Load | Store |
| ------ | --------- | ----- | ---- | ----- |
| Executable | `address < mvmx` | yes | yes | no |
| Read-only | `mvmx <= address < mvmw` | no | yes | no |
| Writable | `address >= mvmw` | no | yes | yes |

Violations raise an instruction, load, or store/AMO access fault. Stores, store-conditionals and AMOs always report a store/AMO access fault.

## CSRs

Xosvm adds 5 CSRs to control its functionality.

### Machine Virtual Memory Control (mvmctl)

The mvmctl is a 32-bit read/write register containing the operating mode of the Xosvm extension.
When the bit 0 (EN) is set and the execution mode is changed to U-Mode, Xosvm becomes active.

|  FIELD  | 31:1 |  0 |
| ------- | ---- | -- |
| CONTENT |   0  | EN |
|   SIZE  |  31  |  1 |

### Machine Virtual Memory Offset (mvmo)

The mvmo is a 32-bit read/write register containing the physical base address of a memory page of the Xosvm.
When Xosvm is enabled (see mvmctl), the configured offset is added to the virtual memory address.

### Machine Virtual Memory Size (mvms)

The mvms is a 32-bit read/write register containing the size in bytes of a memory page of the Xosvm.
The page size does not need to be a power of 2.
Accessing a virtual memory address greater than or equal to the configured size raises an instruction, load, or store/AMO access fault.

### Machine Virtual Memory Executable Limit (mvmx)

The mvmx is a 32-bit read/write register containing the first virtual address that cannot be fetched.
Fetching from `address >= mvmx` raises an instruction access fault when the instruction is executed. Prefetching past the limit does not trap.

### Machine Virtual Memory Writable Base (mvmw)

The mvmw is a 32-bit read/write register containing the first virtual address that can be written.
Storing to `address < mvmw` raises a store/AMO access fault.
