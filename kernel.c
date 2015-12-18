#if !defined(_cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You're not using a cross compiler"
#endif

#if !defined(__i386__)
#error "This kernel needs i386 compatible compiler"
#endif

enum vga_color {
 COLOR_BLACK = 0,
 COLOR_BLUE = 1,
 COLOR_GREEN = 2,
 COLOR_CYAN = 3,
 COLOR_RED = 4,
 COLOR_MAGENTA = 5,
 COLOR_BROWN = 6,
 COLOR_LIGHT_GREY = 7,
 COLOR_DARK_GREY = 8,
 COLOR_LIGHT_BLUE = 9,
 COLOR_LIGHT_GREEN = 10,
 COLOR_LIGHT_CYAN = 11,
 COLOR_LIGHT_RED = 12,
 COLOR_LIGHT_MAGENTA = 13,
 COLOR_LIGHT_BROWN = 14,
 COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg){
 return fg | bg <<4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
 uint16_t c16 = c;
 uint16_t color16 = color;
 return c16 | color << 8;
}

size_t strlen(const char* str) {
 size_t ret = 0;
 while(str[ret] != 0)
  ret++;
 return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
 terminal_row = 0;
 terminal_column = 0;
 terminal_color = make_color(COLOR_WHITE, COLOR_BLUE);
 terminal_buffer = (uint16_t*) 0xB8000;
 for(size_t y=0; y < VGA_HEIGHT; y++){
  for(size_t x = 0; x < VGA_WIDTH; x++) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color){
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y){
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c){
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if(++terminal_column == VGA_WIDTH){
    terminal_column = 0;
    if(++terminal_row == VGA_HEIGHT){
      terminal_row = 0;
    }
  }
}

void terminal_writestring(const char* data){
  size_t datalen = strlen(data);
  for(size_t i; i < datalen; i++){
    terminal_putchar(data[i]);
  }
}

void terminal_writeln(const char* data){
  size_t datalen = strlen(data);
  for(size_t i; i < datalen; i++){
    terminal_putchar(data[i]);
  }
  size_t minus = VGA_WIDTH - datalen;
  for(size_t j; j < minus; j++){
    terminal_putchar(' ');
  }
}

static inline uint8_t inb(unsigned short port){
 unsigned char value;
 asm volatile("inb %w1, %0" : "=a" (value) : "Nd" (port));
 return value;
}

static inline void outb(unsigned short port, unsigned char value){
 asm volatile("outb %b0, %w1" : : "a" (value), "Nd" (port));
}

unsigned char scancode[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
  '9', '0', '-', '=', '\b',    /* Backspace */
  '\t',            /* Tab */
  'q', 'w', 'e', 'r',    /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    /* Enter key */
    0,            /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',    /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,                /* Right shift */
  '*',
    0,    /* Alt */
  ' ',    /* Space bar */
    0,    /* Caps lock */
    0,    /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,    /* < ... F10 */
    0,    /* 69 - Num lock*/
    0,    /* Scroll Lock */
    0,    /* Home key */
    0,    /* Up Arrow */
    0,    /* Page Up */
  '-',
    0,    /* Left Arrow */
    0,
    0,    /* Right Arrow */
  '+',
    0,    /* 79 - End key*/
    0,    /* Down Arrow */
    0,    /* Page Down */
    0,    /* Insert Key */
    0,    /* Delete Key */
    0,   0,   0,
    0,    /* F11 Key */
    0,    /* F12 Key */
    0,    /* All other keys are undefined */
};

char getScancode(){
char c=0;
do {
if(inb(0x60)!=c)
{
c=inb(0x60);
if(c>0)
return c;
}
}while(1);
}

char getchar()
{
return scancode[getScancode()+1];
}

void update_cursor(int row, int col){
  unsigned short position = (row*80) + col;
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char)(position&0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char )((position>>8)&0xFF));


}

#if defined(__cplusplus)
extern "C"
#endif

void kernel_main(){
  terminal_initialize();
  terminal_writeln("Hello, World!");
  terminal_writeln("NanOS version 0.0.1");
  update_cursor(2, 0);

}
