#if !defined(_cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You're not using a cross compiler"
#endif
/* This operating system  will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This kernel needs i386 compatible compiler"
#endif

#include "kernel.h"

#if defined(__cplusplus)
extern "C"
#endif


/* Where everything starts */
void kernel_main(){
  terminal_initialize();
  terminal_writeln("Hello, World!");
  terminal_writeln("NanOS version 0.0.1");
  terminal_writeln(" ");
  prompt();

}
