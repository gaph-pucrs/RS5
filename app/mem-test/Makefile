RED  =\033[0;31m
NC   =\033[0m # No Color

TARGET   ?= $(notdir $(CURDIR))
MEM_SIZE ?= 65536
ARCH     ?= rv32im_zicsr

CC 		= riscv64-elf-gcc
OBJDUMP = riscv64-elf-objdump
OBJCOPY = riscv64-elf-objcopy

SRCDIR  = src
INCDIR  = $(SRCDIR)/include
HEADERS = $(wildcard $(INCDIR)/*.h)

CFLAGS  = -march=$(ARCH) -mabi=ilp32 -Os -Wall -std=c23 -I$(INCDIR)
LDFLAGS = -march=$(ARCH) -mabi=ilp32 -nostdlib -Wl,--section-start=".init"=0

CCSRC = $(wildcard $(SRCDIR)/*.c)
CCOBJ = $(patsubst %.c, %.o, $(CCSRC))

ASSRC = $(wildcard $(SRCDIR)/*.S)
ASOBJ = $(patsubst %.S,%.o, $(ASSRC))

all: $(TARGET).bin $(TARGET).lst

$(TARGET).bin: $(TARGET).elf
	@printf "${RED}Generating %s...${NC}\n" "$@"
	@$(OBJCOPY) $< $@ -O binary

$(TARGET).lst: $(TARGET).elf
	@printf "${RED}Generating %s...${NC}\n" "$@"
	@$(OBJDUMP) -S $< > $@

$(TARGET).elf: $(CCOBJ) $(ASOBJ)
	@printf "${RED}Linking %s...${NC}\n" "$@"
	@$(CC) $(CCOBJ) $(ASOBJ) -Wl,-Map=$(TARGET).map -N -o $@ $(LDFLAGS)

%.o: %.S
	@printf "${RED}Assemblying %s...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS) -march=$(ARCH) -DMEM_SIZE=$(MEM_SIZE)

%.o: %.c $(HEADERS)
	@printf "${RED}Compiling %s...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@printf "Cleaning up\n"
	@rm -rf src/*.o
	@rm -rf *.bin
	@rm -rf *.map
	@rm -rf *.lst
	@rm -rf *.elf

.PHONY: clean
