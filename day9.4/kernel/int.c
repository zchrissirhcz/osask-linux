#include <header.h>



struct KEYBUF keybuf;
struct FIFO8 keyfifo;
struct FIFO8 mousefifo;

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
///	struct BOOTINFO *binfo = (struct BOOTINFO*)ADR_BOOTINFO;
//	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_000084, "");
///	boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 0, 16, 31, 31);
	unsigned char data;
////char s[4];
	outb(PIC0_OCW2, 0x61);
	data = inb(PORT_KEYDAT);
	/*
	if(keybuf.len<32){
		keybuf.data[keybuf.next_w] = data;
		keybuf.len++;
		keybuf.next_w++;
		if(keybuf.next_w==32){
			keybuf.next_w=0;
		}
	}*/
	fifo8_put(&keyfifo, data);

//	sprintf(s, "%x", data);
//	boxfill8(binfo->vram, binfo->scrnx, COL8_000084, 0, 16, 15, 31);
//	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
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
void inthandler2c(int *esp){
	unsigned char data;
	outb(PIC1_OCW2, 0x64);
	outb(PIC0_OCW2, 0X62);
	data = inb(PORT_KEYDAT);
	fifo8_put(&mousefifo, data);
	return;
	/*
	boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32*8-1, 15);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 2C (IRQ-12): PS/2 mouse");
	for(;;){
		io_hlt();
	}
	*/
}
