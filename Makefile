SHELL := /bin/bash
CC = i686-elf-gcc
ASM = nasm -felf32
LINKER = i686-elf-ld
LINKER_FLAGS = -shared -Bsymbolic
LINKER_INPUT = linker.ld kernel.o boot.o
FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra


all:
	@echo "Welcome to NanOS build unit"
	@echo "Make sure you made i686-elf cross compiler"
	@echo "And Installed nasm"
	$(CC) -c kernel.c -o kernel.o $(FLAGS)
	$(ASM) boot.s -o boot.o
	$(LINKER)  $(LINKER_INPUT) -o NanOS.bin $(LINKER_FLAGS)
	@echo "NanOS successfully compiled and linked"

image:
	mv NanOS.bin cdiso/boot/NanOS.bin
	grub-mkrescue -o NanOS.iso cdiso
	@echo "Bootable ISO image successfully created."

emulate:
	@echo "Make sure you installed QEMU"
	qemu-system-i386 -cdrom NanOS.iso

clean:
	rm -rvf *.o
	@echo "All object files removed!"
	rm -rvf NanOS.iso
	@echo "Bootable image removed!"
