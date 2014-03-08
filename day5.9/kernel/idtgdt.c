#include <idtgdt.h>
#include <x86.h>
#include <header.h>

/*
void init_dgtidt(void){
	struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *)0x00270000;
	struct GATE_DESCRIPTOR *idt= (struct GATE_DESCRIPTOR*)0x0026f800;
	int i;

	//gdt initialize
	for(i=0; i<8192; i++){
		set_segmdesc(gdt+i, 0, 0, 0);
	}
	set_segmdesc(gdt+1, 0xffffffff, 0x00000000, 0x4092);
	set_segmdesc(gdt+2, 0x0007ffff, 0x00280000, 0x409a);
	load_gdtr(0xffff, 0x00270000);
	
	//idt initialize
	for(i=0; i<256; i++){
		set_gatedesc(idt+i, 0, 0, 0);
	}
	load_idtr(0x7ff, 0x0026f800);

	return;
}
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int  base, int ar){
	if(limit>0xfffff){
		ar |= 0x8000;
		limit /= 0x1000;
	}
	sd->limit_low = limit&0xffff;
	sd->base_low = base & 0xffff;
	sd->base_mid = (base>>16)&0xff;
	sd->access_right = ar&0xff;
	sd->limit_high = ((limit>>16) & 0x0f)|((ar>>8)&0xf0);
	sd->base_high = (base >> 24) & 0xff;
	return;
}

void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar){
	gd->offset_low = offset & 0xffff;
	gd->selector = selector;
	gd->dw_count = (ar>>8)&0xff;
	gd->access_right = ar & 0xff;
	gd->offset_high = (offset >> 16) & 0xffff;
	return;
}
*/
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int  base, int ar){
	if(limit>0xfffff){
		ar |= 0x8000;
		limit /= 0x1000;
	}
	sd->limit_low = limit&0xffff;
	sd->base_low = base & 0xffff;
	sd->base_mid = (base>>16)&0xff;
	sd->access_right = ar&0xff;
	sd->limit_high = ((limit>>16) & 0x0f)|((ar>>8)&0xf0);
	sd->base_high = (base >> 24) & 0xff;
	return;
}

void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar){
	gd->offset_low = offset & 0xffff;
	gd->selector = selector;
	gd->dw_count = (ar>>8)&0xff;
	gd->access_right = ar & 0xff;
	gd->offset_high = (offset >> 16) & 0xffff;
	return;
}

void init_dgtidt(void){
	struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *)0x00270000;
	struct GATE_DESCRIPTOR *idt= (struct GATE_DESCRIPTOR*)0x0026f800;
	int i;

	//gdt initialize
	for(i=0; i<8192; i++){
		set_segmdesc(gdt+i, 0, 0, 0);
	}
	set_segmdesc(gdt+1, 0x0007ffff, 0x00000000, 0x409a);
	set_segmdesc(gdt+2, 0x7ffff, 	0x280000, 	0x409a);
	set_segmdesc(gdt+3, 0xffffffff, 0x00000, 0x4092);
	
	char gdtinfor[6]={0xff,0xff,0x00,0x00,0x27,0x00};
	lgdt((void*)gdtinfor);
	//load_gdtr(0xffff, 0x00270000);

	
	//idt initialize
	for(i=0; i<256; i++){
		set_gatedesc(idt+i, 0, 0, 0);
	}

	char idtinfor[6]={0xff,0x07,0x00,0xf8,0x26,0x00};
	lidt((void*)idtinfor);
	//load_idtr(0x7ff, 0x0026f800);

	return;
}

