# Xosvm

Xosvm is a RISC-V ISA extension for **O**ffset and **L**imit **V**irtual **M**emory.
This extension provides basic virtual memory support for RISC-V using only M-Mode and U-Mode targeted at embedded systems, removing the need to add Sv32 and S-Mode.

## CSRs

Xosvm adds 5 CSRs to control its functionality.

### Machine Virtual Memory Control (mvmctl)

The mvmctl is an 32-bit read/write register containing the operating mode of the Xosvm extension.
When the bit 0 (EN) is set and the execution mode is changed to U-Mode, Xosvm becomes active.

|  FIELD  | 31:1 |  0 |
| ------- | ---- | -- |
| CONTENT |   0  | EN |
|   SIZE  |  31  |  1 |

### Machine Virtual Memory Instruction/Data Offset (mvmio and mvmbo)

The mvmio and mvmbo are 32-bit read/write registers containing the offset of a physical memory page of the Xosvm.
Note that the offset should be aligned to word size.
When Xosvm is enabled (see mvmctl), the virtual memory address is OR-ed with the configured offset.

|  FIELD  |  31:2  | 1:0 |
| ------- | ------ | --- |
| CONTENT | OFFSET |  0  |
|   SIZE  |   30   |  2  |

### Machine Virtual Memory Instruction/Data Size (mvmis and mvmbs)

The mvmis and mvmbs are 32-bit read/write registers containing the size limit of a physical memory page of the Xosvm.
Note that the CSR should be configured to the actual size of a page minus 1.
When Xosvm is enabled (see mvmctl), the virtual memory address is first masked (AND operation) with this CSR content, and only then the offset is applied (see mvmio and mvmbo).
If the virtual memory address has any bit set besides the configured size mask, it will raise an instruction or load/store access fault.

|  FIELD  |    31:0   |
| ------- | --------- |
| CONTENT | SIZE MASK |
|   SIZE  |     32    |
