TRIPLET = riscv64-elf
CC = $(TRIPLET)-gcc
CFLAGS = -O2 -fno-builtin -march=rv3i2m_zicsr -mabi=ilp32 -nostdinc -mbranch-cost=7
AS = $(TRIPLET)-as
ASFLAGS = -march=rv32im_zicsr -mabi=ilp32
CPP = $(TRIPLET)-g++
CCFLAGS = $(CFLAGS)
LD = $(TRIPLET)-gcc
LDFLAGS = -nostdlib -march=rv32im -mabi=ilp32 -Triscv.ld
OBJCOPY = $(TRIPLET)-objcopy
OBJDUMP = $(TRIPLET)-objdump

PROGNAME = mult

BIN_FILES = $(addsuffix .bin, $(PROGNAME))
LST_FILES = $(addsuffix .lst, $(PROGNAME))

all : $(BIN_FILES) $(LST_FILES)

%.bin : %.elf
	$(OBJCOPY) -O binary $< $@

%.lst : %.elf
	$(OBJDUMP) -d $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CPP) $(CCFLAGS) -o $@ -c $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.elf: %.o
	$(LD) -o $@ $+ $(LDFLAGS)

clean :
	rm -f $(BIN_FILES) $(LST_FILES)  $(wildcard *~) $(wildcard *.o) 
