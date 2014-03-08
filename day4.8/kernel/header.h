#ifndef header
#define header
#include <x86.h>


#define io_halt() asm("hlt")
#define write_mem8(addr,data8)   (*(volatile char *)(addr))=(char)data8

#define io_cli() asm("cli")
#define io_sti() asm("sti")

#define COL8_000000 0
#define COL8_FF0000 1 
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15



extern void clear_screen(char color) ; //color=15 pure white color=40 red
extern void color_screen(char color) ;

extern void init_palette(void);
extern void set_palette(int start, int end, unsigned char *rgb);

extern void boxfill8(char* vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

#endif
