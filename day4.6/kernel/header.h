#ifndef header
#define header
#include <x86.h>


#define io_halt() asm("hlt")
#define write_mem8(addr,data8)   (*(volatile char *)(addr))=(char)data8

#define io_cli() asm("cli")	//!!!本次添加部分
#define io_sti() asm("sti")//!!!本次添加部分


extern void clear_screen(char color) ; //color=15 pure white color=40 red
extern void color_screen(char color) ;

extern void init_palette(void);
extern void set_palette(int start, int end, unsigned char *rgb);

#endif
