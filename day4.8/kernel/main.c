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
void bootmain(void){
	//注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
	int i, xsize, ysize;
	char *vram;
	init_palette();

	clear_screen(15);	//由于一进来这里显示的是"my kernel is running"等字符串，这里刷屏为灰色，去除字符串

	vram=(char*)0xa0000;
	xsize=320;
	ysize=200;

	boxfill8(vram, xsize, COL8_008484, 0, 0, xsize-1, ysize-29);
	boxfill8(vram, xsize, COL8_C6C6C6, 0, ysize-28, xsize-1, ysize-28);
	boxfill8(vram, xsize, COL8_FFFFFF, 0, ysize-27, xsize-1, ysize-27);
	boxfill8(vram, xsize, COL8_C6C6C6, 0, ysize-26, xsize-1, ysize-1);

	boxfill8(vram, xsize, COL8_FFFFFF, 3, ysize-24, 59, ysize-24);
	boxfill8(vram, xsize, COL8_FFFFFF, 2, ysize-24, 2, ysize-4);
	boxfill8(vram, xsize, COL8_848484, 3, ysize-4, 59, ysize-4);
	boxfill8(vram, xsize, COL8_848484, 59, ysize-23, 59, ysize-5);
	boxfill8(vram, xsize, COL8_000000, 2, ysize-3, 59, ysize-3);
	boxfill8(vram, xsize, COL8_000000, 60, ysize-24, 60, ysize-3);

	boxfill8(vram, xsize, COL8_848484, xsize-47, ysize-24, xsize-4, ysize-24);
	boxfill8(vram, xsize, COL8_848484, xsize-47, ysize-23, xsize-47, ysize-4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize-47, ysize-3, xsize-4, ysize-3);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize-3, ysize-24, xsize-3, ysize-3);

	for(;;){
		io_halt();
	}
}
