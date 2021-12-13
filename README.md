# PUCRS-RV

### Description 

PUCRS-RV is a processor that implements the RISC-V 32 bits integer Module (RV32I). It was written in a Hardware Description Language(HDL) called SystemVerilog.

This project was designed at the Embedded Systems Group (GSE) of the polytechnic school, PUCRS, Brazil.

The processor is a 5 stage pipeline, synchronized to the rising edge of clock. The stages are:

- Fetch: Contains the Program Counter(PC) Logic, that indexes the Instruction memory.
- Decoder: Decodes the instruction, extracting it's type, format, operantion and register addresses.
- Operand Fetch: Fetches the operands in the register Bank and performs data hazards detections. When a hazard is detected, it insert bubbles until the conflict has been solved.
- Execute: Performs the given operation on the received operands. It has 6 units where each one is responsible for one kind of operation, such as shift operantions are performed in "Shift Unit" or memory instructions are performed by "Memory Unit".
- Retire: Make the retirement of the instructions, it can be a write-back in register bank, or performing a write in data memory or performing a branch.

<img src="RISCV_block.png" alt="block diagram">
> PUCRS-RV BLOCK DIAGRAM.

## Requirements

To perform code compilation the RISC-V toolchain is needed. The toolchain has a compiler that performs the compilation of the applications codes (located in [a link](https://github.com/Willian-Nunes/pucrs-rv/tree/master/app)) that are written in C language to a binary, this binary is the entry of the processor simulation.

To install the Toolchain a guide and a script are provided inside the folder [a link](https://github.com/Willian-Nunes/pucrs-rv/tree/master/tools/riscv-toolchain).


