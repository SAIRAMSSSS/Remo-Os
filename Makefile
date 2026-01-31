CC = gcc
AS = nasm
LDFLAGS = -m32 -ffreestanding -O2 -nostdlib -T linker.ld
CFLAGS = -m32 -c -ffreestanding -O2 -Wall -Wextra

SRC_C = $(shell find src -name "*.c")
SRC_ASM = $(shell find src -name "*.asm")
OBJ = $(SRC_C:.c=.o) $(SRC_ASM:.asm=.o)

KERNEL_BIN = remoos.bin
ISO_FILE = remoos.iso

all: $(ISO_FILE)

$(ISO_FILE): $(KERNEL_BIN)
	mkdir -p isodir/boot/grub
	cp $(KERNEL_BIN) isodir/boot/$(KERNEL_BIN)
	cp boot/grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_FILE) isodir
	rm -rf isodir

$(KERNEL_BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ -lgcc

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(AS) -f elf32 $< -o $@

run: $(ISO_FILE)
	qemu-system-i386 -cdrom $(ISO_FILE)

clean:
	rm -f $(OBJ) $(KERNEL_BIN) $(ISO_FILE)