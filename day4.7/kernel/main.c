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
	int i;
	char *p;
	init_palette();

	clear_screen(15);	//由于一进来这里显示的是"my kernel is running"等字符串，这里刷屏为灰色，去除字符串

	p=(char*)0xa0000;
	boxfill8(p, 320, 1, 20, 20, 120, 120);
	boxfill8(p, 320, 2, 70, 50, 170, 150);
	boxfill8(p, 320, 4, 120, 80, 220, 180);

	for(;;){
		io_halt();
	}
}
