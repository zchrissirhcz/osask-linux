#ifndef header
#define header
#include <x86.h>


#define io_halt() asm("hlt")
#define write_mem8(addr,data8)   (*(volatile char *)(addr))=(char)data8

extern void clear_screen(char color) ; //color=15 pure white color=40 red
extern void color_screen(char color) ;

#endif
