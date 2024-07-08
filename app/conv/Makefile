#remove unreferenced functions
CFLAGS_STRIP = -fdata-sections -ffunction-sections -fdata-sections -ffunction-sections

#-mrvv-vector-bits=zvl
GCC_RISCV = riscv64-elf-gcc -march=rv32im_zicsr_zve32x_zvl256b -mabi=ilp32 -O2 -mrvv-vector-bits=zvl $(CFLAGS_STRIP) -DDEBUG_PORT -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -mno-relax -DPRINTF_DISABLE_SUPPORT_FLOAT=1
DUMP_RISCV = riscv64-elf-objdump #-Mno-aliases
READ_RISCV = riscv64-elf-readelf
OBJ_RISCV = riscv64-elf-objcopy
SIZE_RISCV = riscv64-elf-size

TEST_OBJS   = $(addsuffix .o,$(basename $(wildcard lib/*.S)))
TEST_C_OBJS = $(addsuffix .o,$(basename $(wildcard lib/*.c ./*.c)))

all: $(TEST_OBJS) $(TEST_C_OBJS)
	$(GCC_RISCV) -c test.S -o test.o
	$(GCC_RISCV) -Trs5.ld -Wl,-Map,test.map,-N -o test.axf \
		test.o $(TEST_OBJS) $(TEST_C_OBJS) -Wl,--gc-sections -lc -lgcc
	$(DUMP_RISCV) --disassemble --reloc test.axf > test.lst
	$(DUMP_RISCV) -h test.axf > test.sec
	$(DUMP_RISCV) -s test.axf > test.cnt
	$(OBJ_RISCV) -O binary test.axf test.bin
	$(SIZE_RISCV) test.axf
	hexdump -v -e '4/1 "%02x" "\n"' test.bin > test.hex

%.o: %.S
	$(GCC_RISCV) -c -o $@ -DTEST_FUNC_NAME=$(notdir $(basename $<)) \
		-DTEST_FUNC_TXT='"$(notdir $(basename $<))"' -DTEST_FUNC_RET=$(notdir $(basename $<))_ret $<

%.o: %.c
	$(GCC_RISCV) -c -o $@ -DTEST_FUNC_NAME=$(notdir $(basename $<)) \
		-DTEST_FUNC_TXT='"$(notdir $(basename $<))"' -DTEST_FUNC_RET=$(notdir $(basename $<))_ret $<

clean:
	-rm -rf *.o *.axf *.map *.lst *.sec *.cnt *.hex *.bin *~
	-rm -rf lib/*.o
