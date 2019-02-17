AS = i686-elf-as
CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -lgcc -Xassembler --32
LFLAGS = -ffreestanding -O2 -nostdlib -lgcc

INCLUDE_DIR = ./include/
IFLAGS = $(foreach d, $(INCLUDE_DIR), -I$d)

DIR_GDT = ./gdt/
DIR_IDT = ./idt/
DIR_IRQ = ./irq/
DIR_ISR = ./isr/
DIR_KEYBOARD = ./keyboard/
DIR_UTILITY = ./utility/
DIR_TERMINAL = ./terminal/
DIR_TIMER = ./timer/

LINKER_FILE = $(DIR_UTILITY)linker.ld

OBJ = \
	$(DIR_UTILITY)boot.o \
	$(DIR_IDT)idt.o \
	$(DIR_IDT)idt_load.o \
	$(DIR_IRQ)irq.o \
	$(DIR_IRQ)irqs.o \
	$(DIR_ISR)isr.o \
	$(DIR_ISR)isrs.o \
	$(DIR_KEYBOARD)keyboard.o \
	$(DIR_UTILITY)system.o \
	$(DIR_TERMINAL)terminal_buffer.o \
	$(DIR_TERMINAL)virtualterminal.o \
	kernel.o \

OBJ_LINK_LIST := $(OBJ)
INTERNAL_OBJS := $(OBJ)

QEMU = qemu-system-i386
QEMU_FLAGS = -kernel

BIN_NAME = kernel.bin

all: $(BIN_NAME)

$(BIN_NAME): $(OBJ_LINK_LIST)
	$(CC) -T $(LINKER_FILE) -o $(BIN_NAME) $(LFLAGS) $(OBJ_LINK_LIST)

%.o: %.c
	$(CC)$(IFLAGS) -c $< -o $@ $(CFLAGS)

%.o: %.s
	$(AS) $< -o $@

clean:
	rm $(BIN_NAME) $(INTERNAL_OBJS)

run:
	$(QEMU) $(QEMU_FLAGS) $(BIN_NAME)
