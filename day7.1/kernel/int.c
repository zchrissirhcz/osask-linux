#include <header.h>

#define PORT_KEYDAT 0x0060

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
	char data, s[4];
	outb(PIC0_OCW2, 0X61);
	data = inb(PORT_KEYDAT);

	sprintf(s, "%02X", data);
	boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 16, 15, 31);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
	return;
}
