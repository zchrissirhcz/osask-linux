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
#include<header.h>
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
	struct BOOTINFO *binfo = (struct BOOTINFO*) 0x0ff0;
	static char font_A[16]={
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
	};
	
	init_palette();
	init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
	putfont8(binfo->vram, binfo->scrnx, 10, 10, COL8_FFFFFF, font_A);

	while(1);
}
