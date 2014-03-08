#include<header.h>

void clear_screen(char color) //15:pure white
{
	int i;
	for(i=0xa0000;i<0xaffff;i++)
	{
		write_mem8(i,color);  //if we write 15 ,all pixels color will be white,15 mens pure white ,so the screen changes into white

	}
}

void color_screen(char color) //15:pure white
{
	int i;
	color=color;
	for(i=0xa0000;i<0xaffff;i++)
	{
		write_mem8(i,i&0x0f);  //if we write 15 ,all pixels color will be white,15 mens pure white ,so the screen changes into white

	}
}

void set_palette(int start, int end, unsigned char* rgb){
	int i, eflags;
	eflags = read_eflags();	//替代作者的io_load_eflags()
	io_cli();
	outb(0x03c8, start);	//替代作者的io_out8()
	for(i=start; i<=end; i++){
		outb(0x03c9,rgb[0]/4);
		outb(0x03c9,rgb[1]/4);
		outb(0x03c9,rgb[2]/4);
		rgb+=3;
	}
	write_eflags(eflags);	//替代作者的io_store_eflags(eflags)
	return;
}


void init_palette(void){
	//16种color，每个color三个字节。
	static unsigned char table_rgb[16*3]=
	{
		0x00,0x00,0x00,   /*0:black*/
		0xff,0x00,0x00,   /*1:light red*/ 
		0x00,0xff,0x00,   /*2:light green*/   
		0xff,0xff,0x00,   /*3:light yellow*/

		0x00,0x00,0xff,   /*4:light blue*/
		0xff,0x00,0xff,   /*5:light purper*/ 
		0x00,0xff,0xff,   /*6:light blue*/
		0xff,0xff,0xff,   /*7:white*/

		0xc6,0xc6,0xc6,   /*8:light gray*/
		0x84,0x00,0x00,   /*9:dark red*/
		0x00,0x84,0x00,   /*10:dark green*/ 
		0x84,0x84,0x00,   /*11:dark yellow*/

		0x00,0x00,0x84,   /*12:dark 青*/
		0x84,0x00,0x84,   /*13:dark purper*/
		0x00,0x84,0x84,   /*14:light blue*/
		0x84,0x84,0x84,   /*15:dark gray*/
	};  
	set_palette(0,15,table_rgb);
	return;
}
