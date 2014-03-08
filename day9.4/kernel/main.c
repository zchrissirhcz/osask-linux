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

//extern struct KEYBUF keybuf;
extern struct FIFO8 keyfifo;
extern struct FIFO8 mousefifo;

void bootmain(void){

	extern char hankaku[2048];

	struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
	char s[40], mcursor[256];
	unsigned char keybuf[32], mousebuf[128];
	int mx, my, i;
	unsigned int memtotal;
	struct MOUSE_DEC mdec;
	struct MEMMAN *memman = (struct MEMMAN*)MEMMAN_ADDR;

	init_gdtidt();
	init_pic();
	io_sti();

	fifo8_init(&keyfifo, 32, keybuf);
	fifo8_init(&mousefifo, 128, mousebuf);
	outb(PIC0_IMR, 0xf9);
	outb(PIC1_IMR, 0xef);

	init_keyboard();
	enable_mouse(&mdec);
	memtotal = memtest(0x00400000, 0xbfffffff);
	memman_init(memman);
	memman_free(memman, 0x00001000, 0x0009e000);
	memman_free(memman, 0x00400000, memtotal - 0x00400000);

	init_palette();
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
	mx=(binfo->scrnx - 16) / 2;
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
//	init_mouse_cursor8(char *mouse, char bg)
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
//	sprintf(s, "(%d, %d)", mx, my);
	sprintf(s, "(%d,%d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

	sprintf(s, "memory %dMB free: %dKB", memtotal/(1024*1024), memman_total(memman)/1024);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 32, COL8_FFFFFF, s);


//	unsigned char mouse_dbuf[3], mouse_phase;
//	mouse_phase=0;

	for(;;){
		io_cli();
		if(fifo8_status(&keyfifo)+fifo8_status(&mousefifo)==0){
			io_sti();
			io_hlt();
		}else{
			if(fifo8_status(&keyfifo)!=0){
				boxfill8(binfo->vram, binfo->scrnx, COL8_840000, 0, 16, 31, 31);//chriszz添加。刷字符区域为蓝色。
				i=fifo8_get(&keyfifo);
				io_sti();
				sprintf(s, "%x", i);
				boxfill8(binfo->vram, binfo->scrnx, COL8_840000, 0, 16, 31, 31);
				putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
			}
			if(fifo8_status(&mousefifo)!=0){
				//boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 32, 16, 64, 31);//chriszz添加。刷字符区域为蓝色。
				i=fifo8_get(&mousefifo);
				io_sti();
				if(mouse_decode(&mdec, i)!=0){
					sprintf(s, "[lmr %d %d]", mdec.buf[1], mdec.buf[2]);
					switch(mdec.btn){		//用switch替代if语句块。&的做法似乎有问题。
						case 1:s[1]='L';break;
						case 2:s[3]='R';break;
						case 4:s[2]='M';break;
					}
					boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 150, 31);
					putfonts8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);

					boxfill8(binfo->vram, binfo->scrnx, COL8_008484, mx, my, mx+15, my+15);//刷[原]鼠标位置
					mx += mdec.x;
					my += mdec.y;
					if(mx<0) mx=0;
					if(my<0) my=0;
					if(mx>binfo->scrnx-16) mx=binfo->scrnx-16;
					if(my>binfo->scrny-16) my=binfo->scrny-16;
					sprintf(s, "(%d,%d)", mx, my);
					boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 0, 79, 15);
					putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
					putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);//刷[新]鼠标位置
				}
			}
		}
		i=memtest(0x00400000, 0xbfffffff)/(1024 * 1024);
		sprintf(s, "memory %dMB", i);
		putfonts8_asc(binfo->vram, binfo->scrnx, 0, 32, COL8_FFFFFF, s);
	}

}

