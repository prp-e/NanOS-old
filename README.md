#Tinix
Tinix is a minimal operating system written in C and Assembly.

## How to use?
First, you need a [GCC Cross Compiler](http://wiki.osdev.org/GCC_Cross-Compiler), then you
can build Tinix manually, or by using a Makefile.

###For building bootloader :

* AT&T Syntax (known as boot-alt.s):

```bash
 i686-elf-as -o boot-alt.o boot-alt.s
```

* Intel Syntax (known as boot.s):

```bash
 nasm -felf32 -o boot.o boot.s
```
