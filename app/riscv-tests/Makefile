#remove unreferenced functions
CFLAGS_STRIP = -fdata-sections -ffunction-sections
LDFLAGS_STRIP = --gc-sections

GCC_RISCV = riscv64-elf-gcc -march=rv32imac_zicsr -mabi=ilp32 -O2 -c -nostdinc -fno-builtin -I ./../../hf_risc_test/include $(CFLAGS_STRIP) -DDEBUG_PORT -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -mno-relax
AS_RISCV = riscv64-elf-as -march=rv32imac_zicsr -mabi=ilp32
LD_RISCV = riscv64-elf-ld -melf32lriscv
DUMP_RISCV = riscv64-elf-objdump #-Mno-aliases
READ_RISCV = riscv64-elf-readelf
OBJ_RISCV = riscv64-elf-objcopy
SIZE_RISCV = riscv64-elf-size

TEST_OBJS = $(addsuffix .o,$(basename $(wildcard tests/*.S)))

all: $(TEST_OBJS)
	$(GCC_RISCV) -o test.o test.S
	$(LD_RISCV) -Trs5.ld -Map test.map -N -o test.axf \
		test.o $(TEST_OBJS)
	$(DUMP_RISCV) --disassemble --reloc test.axf > test.lst
	$(DUMP_RISCV) -h test.axf > test.sec
	$(DUMP_RISCV) -s test.axf > test.cnt
	$(OBJ_RISCV) -O binary test.axf test.bin
	$(SIZE_RISCV) test.axf
	hexdump -v -e '4/1 "%02x" "\n"' test.bin > test.hex

%.o: %.S tests/riscv_test.h tests/test_macros.h
	$(GCC_RISCV) -o $@ -DTEST_FUNC_NAME=$(notdir $(basename $<)) \
		-DTEST_FUNC_TXT='"$(notdir $(basename $<))"' -DTEST_FUNC_RET=$(notdir $(basename $<))_ret $<

clean:
	-rm -rf *.o *.axf *.map *.lst *.sec *.cnt *.hex *.bin *~
	-rm -rf tests/*.o
