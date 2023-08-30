# Output file name
TARG     = clock7segm

# MCU name and frequency
MCU      = atmega8
F_CPU    = 11059200

# Source files
SRCS     = $(wildcard *.c)

# Build directory
BUILDDIR = build

OPTIMIZE = -Os -mcall-prologues -fshort-enums -ffunction-sections -fdata-sections -ffreestanding -flto
WARNLEVEL = -Wall -Werror
CFLAGS = $(WARNLEVEL) -lm $(OPTIMIZE) -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS += -MMD -MP -MT $(BUILDDIR)/$(*F).o -MF $(BUILDDIR)/$(*D)/$(*F).d
LDFLAGS = $(WARNLEVEL) -mmcu=$(MCU) -Wl,--gc-sections -Wl,--relax

# Main definitions

PREFIX = avr-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
OD = $(PREFIX)objdump
AR = $(PREFIX)ar
SZ = $(PREFIX)size

AVRDUDE  = avrdude
AD_MCU   = -p $(MCU)
#AD_PROG = -c stk500v2
#AD_PORT = -P avrdoper

AD_CMDLINE = $(AD_MCU) $(AD_PROG) $(AD_PORT) -V -B 0.5

OBJS = $(addprefix $(BUILDDIR)/, $(SRCS:.c=.o))
ELF = $(BUILDDIR)/$(TARG).elf
HEX = flash/$(TARG).hex

all: $(HEX) size

$(ELF): $(OBJS)
	@mkdir -p $(addprefix $(BUILDDIR)/, $(SUBDIRS)) flash
	$(CC) $(LDFLAGS) -o $(ELF) $(OBJS)
	$(OD) -h -S $(ELF) > $(BUILDDIR)/$(TARG).lss

$(HEX): $(ELF)
	$(CP) -O ihex -R .eeprom -R .nwram $(ELF) $(HEX)

size: $(ELF)
	$(SZ) $(ELF)

$(BUILDDIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFINES) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

.PHONY: flash
flash:  $(HEX)
	$(AVRDUDE) $(AD_CMDLINE) -U flash:w:flash/$(TARG).hex:i

.PHONY: fuse
fuse:
	$(AVRDUDE) $(AD_CMDLINE) -U lfuse:w:0xFF:m -U hfuse:w:0xC9:m

# Other dependencies
-include $(OBJS:.o=.d)
