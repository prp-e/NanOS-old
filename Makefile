CC = i686-elf-gcc
ASM = nasm -felf32
LINKER = i686-elf-ld
FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra


all:
	@echo "Welcome to NanOS build unit"
	@echo "Make sure you made i686-elf cross compiler"
	@echo "And Installed nasm"
	$(CC) -c kernel.c -o kernel.o $(FLAGS)
	$(ASM) boot.s -o boot.o
	$(LINKER) linker.ld kernel.o boot.o -o NanOS.bin -shared -Bsymbolic
	@echo "NanOS successfully compiled and liked"

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
