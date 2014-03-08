#include <header.h>

#define PORT_KEYDAT 0x0060


struct KEYBUF keybuf;

void init_pic(void){
	outb(PIC0_IMR, 0xff);
	outb(PIC1_IMR, 0xff);

	outb(PIC0_ICW1, 0x11);
	outb(PIC0_ICW2, 0x20);
	outb(PIC0_ICW3, 1<<2);
	outb(PIC0_ICW4, 0x01);

	outb(PIC1_ICW1, 0x11);
	outb(PIC1_ICW2, 0x28);
	outb(PIC1_ICW3, 2);
	outb(PIC1_ICW4, 0x01);

	outb(PIC0_IMR, 0xfb);
	outb(PIC1_IMR, 0xff);

	return;
}


void inthandler21(int *esp){
	struct BOOTINFO *binfo = (struct BOOTINFO*)ADR_BOOTINFO;
//	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_000084, "");
	boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 0, 16, 31, 31);
	unsigned char data;
	char s[4];
	outb(PIC0_OCW2, 0x61);
	data = inb(PORT_KEYDAT);

	sprintf(s, "%x", data);
//	boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 0, 16, 15, 31);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
	return;
}

/*
void inthandler21(int *esp){
	char data;
	outb(PIC0_OCW2, 0x61);
	data = inb(PORT_KEYDAT);
	if(keybuf.next<32){
		keybuf.data[keybuf.next] = data;
		keybuf.next++;
	}
	return;
}
*/
/*
void inthandler21(int *esp){
	char data;
	outb(PIC0_OCW2, 0x61);
	data = inb(PORT_KEYDAT);
	if(keybuf.len < 32){
		keybuf.data[keybuf.next_w] = data;
		keybuf.len++;
		keybuf.next_w++;
		if(keybuf.next_w==32){
			keybuf.next_w = 0;
		}
	}
	return;
}
*/
