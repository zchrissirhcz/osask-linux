/*
 * ==================================================
 *
 *       Filename:  bootpack.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  2014年03月01日 星期六 22时03分34秒
 *         Author:  ChrisZZ, zchrissirhcz@163.com
 *        Company:  ZJUT
 *
 * ==================================================
 */
#include <header.h>
#include <fontascii.h>

extern struct KEYBUF keybuf;
/*
   void bootmain(void){
//注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
clear_screen(40);

char *vram;
int xsize, ysize;
struct BOOTINFO *binfo;
binfo=(struct BOOTINFO *)0x0ff0;
init_screen((struct BOOTINFO*)0x0ff0);

draw_window();

init_palette();

vram=(char *)0x0ff0;

char font_A[16]={
0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
};

//putfont8(vram, 20, 50, 50, 'd', font_A);
putfont8(binfo->vram binfo->xsize, 8, 8, COL8_FFFFFF, font_A);
}

   void bootmain(void){
   struct BOOTINFO *binfo = (struct BOOTINFO*) 0x00000ff0;
   extern char hankaku[2048];

   sti();
   init_palette();
   init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
   char s[10];
//sprintf(s, "scrnx=%d", binfo->scrnx);
//putfont8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

char mcursor[256];
int mx, my;
mx = (binfo->scrnx-16)/2;
my = (binfo->scrny-28-16)/2;
init_mouse_cursor8(mcursor, COL8_008484);
putblock8_8(binfo->vram, binfo->scrnx, 16, 16, 60, 60, mcursor, 16);

//sprintf(s, "(%d, %d)", mx, my);
//putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

//	while(1);

init_gdtidt();
init_pic();

outb(PIC0_IMR, 0xf9);
outb(PIC1_IMR, 0xef);

//	int *addr=(int *)(0x0026f800+8*0x21);

//sprintf(*(addr), 0);
//sprintf(*(addr+1), 160);
while(1);

}

   void bootmain(void){
   struct BOOTINFO *binfo = (struct BOOTINFO*) 0x00000ff0;
   char s[40], mcursor[256];
   int mx, my, i, j;

   init_gdtidt();
   init_pic();
   sti();

   outb(PIC0_IMR, 0xf9);
   outb(PIC1_IMR, 0xef);

   init_palette();
   init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

   mx=(binfo->scrnx-16)/2;
   my=(binfo->scrny-28-16)/2;
   init_mouse_cursor8(mcursor, COL8_008484);
   putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
   sprintf(s, "(%d, %d)", mx, my);
   putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

   for(;;){
   io_cli();
   if(keybuf.len==0){
   sti();
   hlt();
   }else{
   i=keybuf.data[keybuf.next_r];
   keybuf.len--;
   keybuf.next_r++;
   if(keybuf.next_r==32){
   keybuf.next_r = 0;
   }
   sti();
   sprintf(s, "%02X", i);
   boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
   putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF,s);
   }
   }



   init_palette();
   init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
   char s[10];
//sprintf(s, "scrnx=%d", binfo->scrnx);
//putfont8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

char mcursor[256];
int mx, my;
mx = (binfo->scrnx-16)/2;
my = (binfo->scrny-28-16)/2;
init_mouse_cursor8(mcursor, COL8_008484);
putblock8_8(binfo->vram, binfo->scrnx, 16, 16, 60, 60, mcursor, 16);

//sprintf(s, "(%d, %d)", mx, my);
//putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

//	while(1);

init_gdtidt();
init_pic();

outb(PIC0_IMR, 0xf9);
outb(PIC1_IMR, 0xef);

//	int *addr=(int *)(0x0026f800+8*0x21);

//sprintf(*(addr), 0);
//sprintf(*(addr+1), 160);
while(1);
}
*/

void bootmain(void){

	extern char hankaku[2048];

	struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
	char s[40], mcursor[256];
	int mx, my, i;

	init_gdtidt();
	init_pic();
	io_sti();

	init_palette();
	init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
	mx=(binfo->scrnx - 16) / 2;
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
//	init_mouse_cursor8(char *mouse, char bg)
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
//	sprintf(s, "(%d, %d)", mx, my);
	sprintf(s, "hithere%d", mx);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

	outb(PIC0_IMR, 0xf9);
	outb(PIC1_IMR, 0xef);

	for(;;){
		io_cli();
		if(keybuf.flag==0){
			io_sti();
			io_hlt();
		}else{
			boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 0, 16, 31, 31);//chriszz添加。刷字符区域为蓝色。
			i=keybuf.data;
			keybuf.flag = 0;
			io_sti();
			sprintf(s, "%x", i);
			boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 0, 31, 15, 31);
			putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
		}
	}
}

