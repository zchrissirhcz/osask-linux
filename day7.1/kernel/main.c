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
*/
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
/*
	int *addr=(int *)(0x0026f800+8*0x21);
*/
	//sprintf(*(addr), 0);
	//sprintf(*(addr+1), 160);
	while(1);
}
