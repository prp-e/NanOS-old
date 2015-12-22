# NanOS
NanOS is a minimal operating system written in C and Assembly.

## How to use?
First, you need a [GCC Cross Compiler](http://wiki.osdev.org/GCC_Cross-Compiler), then you
can build NanoS manually, or by using a Makefile.

Now, __NanOS__ has its own Makefile, so you need to know make options


1. all :
Assembles `boot.s` and compiles `kernel.c` then, links them using `linker.ld`.
2. image:
Makes a bootable ISO image using `NanOS.bin` file and __GRUB__ boot loader.
3. emulate :
boots NanOS using QEMU.
4. clean :
removes object files from working directory.
