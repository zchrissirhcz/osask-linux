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

#define VRAM (0xa0000-0x280000)
#define ADR_BOOTINFO 0x00000FF0

#define PIC0_ICW1	0x0020
#define PIC0_OCW2	0x0020
#define PIC0_IMR	0x0021
#define PIC0_ICW2	0x0021
#define PIC0_ICW3	0x0021
#define PIC0_ICW4	0x0021
#define PIC1_ICW1	0x00a0
#define PIC1_OCW2	0x00a0
#define PIC1_IMR	0x00a1
#define PIC1_ICW2	0x00a1
#define PIC1_ICW3	0x00a1
#define PIC1_ICW4	0x00a1


#define ADR_IDT			0x0026f800
#define LIMIT_IDT		0x000007ff
#define ADR_GDT			0x00270000
#define LIMIT_GDT		0x0000ffff
#define ADR_BOTPAK		0x00280000
#define LIMIT_BOTPAK	0x0007ffff
#define AR_DATA32_RW	0x4092
#define AR_CODE32_ER	0x409a
#define AR_INTGATE32	0x008e

/*
struct BOOTINFO{
	char cylinder, led, color_mode;
	char reserved;
	short xsize, ysize;
	char *vram;
};
*/
struct BOOTINFO{
	char cyls, leds, vmode, reserve;
	short scrnx, scrny;
	char *vram;
};

struct SEGMENT_DESCRIPTOR{
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_high, base_high;
};

struct GATE_DESCRIPTOR{
	short offset_low, selector;

	char dw_count, access_right;
	short offset_high;
};


extern void clear_screen(char color) ; //color=15 pure white color=40 red
extern void color_screen(char color) ;

extern void init_palette(void);
extern void set_palette(int start, int end, unsigned char *rgb);

extern void boxfill8(char* vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
//extern void init_screen(struct BOOTINFO* binfo);
extern void init_screen(char *vram, int x, int y);
extern void putfont8(char* vram, int xsize, int x, int y, char c, char *font);
//extern void draw_window();
extern void putfonts8_asc(char* vram, int xsize, int x, int y, char c, char *s);
extern void itoa(int value,char *buf);
extern void sprintf(char *str,char *format ,...);
extern void init_mouse_cursor8(char *mouse, char bg);
extern void putblock8_8(char *vram,int xsize,int pxsize,int pysize,int px0,int py0,char *buf,int bxsize);//显示鼠标,display_mouse

extern void init_gdtidt(void);
extern void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int  base, int ar);
extern void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);

extern void init_pic(void);
extern void inthandler21(int *esp);
extern void load_gdtr(int limit, int addr);
extern void load_idtr(int limit, int addr);   

extern void asm_inthandler21();
#endif
