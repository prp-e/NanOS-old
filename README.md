# NanOS
NanOS is a minimal operating system written in C and Assembly.

## How to use?
First, you need a [GCC Cross Compiler](http://wiki.osdev.org/GCC_Cross-Compiler), then you
can build NanoS manually, or by using a Makefile.

### For building bootloader :

* AT&T Syntax (known as boot-alt.s):

```bash
 i686-elf-as -o boot-alt.o boot-alt.s
```

* Intel Syntax (known as boot.s):

```bash
 nasm -felf32 -o boot.o boot.s
```
### For building the kernel :

Just type this:

```bash
  i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
```

### For linking :
```bash
  i686-elf-ld linker.ld kernel.o boot.o -o NanOS.bin -shared -Bsymbolic
```
Now, you can make a bootable image using `grub-mkrescue` or `mkisofs`, and
test it using __QEMU__ or __Virtual Box__.
