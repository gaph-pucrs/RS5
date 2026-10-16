#remove unreferenced functions
CFLAGS_STRIP = -fdata-sections -ffunction-sections
LDFLAGS_STRIP = -Wl,--gc-sections

TRIPLET = riscv64-elf
CC = $(TRIPLET)-gcc
CFLAGS = -IbareOS/include -Itinycrypt/include -O2 -fno-builtin -march=rv32i_zkne -mabi=ilp32 -mbranch-cost=7 -DAES_RISCV_ASM -DTC_AES_128 $(CFLAGS_STRIP)
AS = $(TRIPLET)-as
ASFLAGS = -march=rv32i_zicsr_zkne -mabi=ilp32
CPP = $(TRIPLET)-g++
CCFLAGS = $(CFLAGS)
LD = $(TRIPLET)-gcc
#LD = $(TRIPLET)-ld
LDFLAGS = $(LDFLAGS_STRIP) -nostdlib -march=rv32i_zkne -mabi=ilp32 -Triscv.ld
OBJCOPY = $(TRIPLET)-objcopy
OBJDUMP = $(TRIPLET)-objdump

PROGNAME = aes128_nist_enc_test

BIN_FILES = $(addsuffix .bin, $(PROGNAME))
LST_FILES = $(addsuffix .lst, $(PROGNAME))

BARE_OS = bareOS/crt0.o \
	bareOS/arch.o \
	bareOS/libos.o \
	bareOS/malloc.o \
	bareOS/softmul.o

TINYCRYPT = $(patsubst %.c,%.o,$(wildcard tinycrypt/*.c))

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

%.elf: $(BARE_OS) $(TINYCRYPT) %.o
	$(LD) -o $@ $+ $(LDFLAGS)

clean :
	rm -f $(BIN_FILES) $(LST_FILES) $(BARE_OS) $(wildcard *~) $(wildcard *.o)
