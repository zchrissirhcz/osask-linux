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

#define PORT_KEYDAT 0x0060
#define PORT_KEYSTA 0x0064
#define PORT_KEYCMD 0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE 0x60
#define KBC_MODE 0x47

#define KEYCMD_SENDTO_MOUSE	0xd4
#define MOUSECMD_ENABLE 0xf4

#define EFLAGS_AC_BIT 0x00040000
#define CR0_CACHE_DISABLE 0x60000000

#define MEMMAN_FREES 4090
#define MEMMAN_ADDR 0x003c0000

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

struct KEYBUF{
	unsigned char data[32];
	int next_r, next_w, len;
};

struct FIFO8{
	unsigned char *buf;
	int p, q, size, free, flags;
};

struct MOUSE_DEC{
	unsigned char buf[3], phase;
	int x, y, btn;
};


struct FREEINFO{
	unsigned int addr, size;
};

struct MEMMAN{
	int frees, maxfrees, lostsize, losts;
	struct FREEINFO free[MEMMAN_FREES];
};

extern void clear_screen(char color) ; //color=15 pure white color=40 red
extern void color_screen(char color) ;

extern void init_palette(void);
extern void set_palette(int start, int end, unsigned char *rgb);

extern void boxfill8(char* vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
//extern void init_screen(struct BOOTINFO* binfo);
extern void init_screen8(char *vram, int x, int y);
extern void putfont8(char* vram, int xsize, int x, int y, char c, char *font);
//extern void draw_window();
extern void putfonts8_asc(char* vram, int xsize, int x, int y, char c, char *s);
extern void puts8(char *vram ,int xsize,int x,int y,char color,char *font);
extern void printdebug(int i,int x);
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
extern void asm_inthandler2c();
extern void xtoa(unsigned int value,char *buf);

extern void fifo8_init(struct FIFO8* fifo, int size, unsigned char *buf);
extern int fifo8_put(struct FIFO8* fifo, char data);
extern int fifo8_get(struct FIFO8* fifo);
extern int fifo8_status(struct FIFO8* fifo);

extern void wait_KBC_sendready(void);
extern void init_keyboard(void);
extern void enable_mouse(struct MOUSE_DEC *mdec);
extern int mouse_decode(struct MOUSE_DEC *mdec, unsigned char dat);
extern void inthandler2c(int *esp);

extern unsigned int memtest(unsigned int start, unsigned int end);
extern unsigned int memtest_sub(unsigned int start, unsigned int end);

extern void memman_init(struct MEMMAN *man);
extern unsigned int memman_total(struct MEMMAN *man);
extern unsigned int memman_alloc(struct MEMMAN *man, unsigned int size);
extern int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size);

#endif
