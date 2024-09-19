#remove unreferenced functions
CFLAGS_STRIP = -fdata-sections -ffunction-sections
LDFLAGS_STRIP = --gc-sections

GCC_RISCV = riscv64-elf-gcc -march=rv32ima_zicsr -mabi=ilp32 -O2 -c -nostdinc -fno-builtin $(CFLAGS_STRIP) -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -mno-relax
AS_RISCV = riscv64-elf-as -march=rv32ima_zicsr -mabi=ilp32
LD_RISCV = riscv64-elf-ld -melf32lriscv
DUMP_RISCV = riscv64-elf-objdump
READ_RISCV = riscv64-elf-readelf
OBJ_RISCV = riscv64-elf-objcopy
SIZE_RISCV = riscv64-elf-size

all: test.S
	$(GCC_RISCV) -o test.o test.S
	$(LD_RISCV) -Trs5.ld -Map test.map -N -o test.elf \
		test.o $(TEST_OBJS)
	$(DUMP_RISCV) --disassemble --reloc test.elf > test.lst
	$(DUMP_RISCV) -h test.elf > test.sec
	$(DUMP_RISCV) -s test.elf > test.cnt
	$(OBJ_RISCV) -O binary test.elf test.bin
	$(SIZE_RISCV) test.elf
	hexdump -v -e '4/1 "%02x" "\n"' test.bin > test.hex

clean:
	-rm -rf *.o *.elf *.map *.lst *.sec *.cnt *.hex *.bin *~
	-rm -rf tests/*.o
