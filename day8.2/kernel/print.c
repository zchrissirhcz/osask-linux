#include<header.h>
#include <font.h>

extern char hankaku[2048] ;

void printdebug(int i,int x){
	char font[30];
	sprintf(font,"Debug:var=%x" ,i);
	puts8((char *)VRAM ,320,x,150,1,font);

}

void puts8(char *vram ,int xsize,int x,int y,char color,char *font){
	while(*font){
		if(*font=='\n'){
			x=0;
			y=y+16;
		}else{  
			putfont8((char *)vram ,xsize,x,y,color,(char *)(hankaku+(*font)*16));
			x+=8;
			if(x>312){
				x=0;
				y+=16;
				if(y>183){
					x=0;
					y=0;
				}
			}    
		}
		font++;
	}
}

void itoa(int value,char *buf){
	char tmp_buf[10] = {0};
	char *tbp = tmp_buf;
	if((value >> 31) & 0x1){ // neg num 
		*buf++ = '-';
		value = ~value + 1; 
	}

	do{
		*tbp++ = ('0' + (char)(value % 10));
		value /= 10;
	}while(value);
	while(tmp_buf != tbp--)
		*buf++ = *tbp;
	*buf='\0';
}

/*
//实现可变参数的打印，主要是为了观察打印的变量。
void sprintf(char *str,char *format ,...){

int *var=(int *)(&format)+1; //得到第一个可变参数的地址
char buffer[10];
char *buf=buffer;
while(*format){
if(*format!='%'){
 *str++=*format++;
 continue;
 }
 else{
 format++;
 switch (*format){
 case 'd':itoa(*var,buf);while(*buf){*str++=*buf++;};var++;break;
 case 'x':break;
 case 's':break;
 }
 format++;
 }
 }
 *str='\0';
 }
 */
//实现可变参数的打印，主要是为了观察打印的变量。
void sprintf(char *str,char *format ,...)
{

	int *var=(int *)(&format)+1; //得到第一个可变参数的地址
	char buffer[10];
	char *buf=buffer;
	while(*format)
	{
		if(*format!='%')
		{
			*str++=*format++;
			continue;
		}
		else
		{
			format++;
			switch (*format)
			{
				case 'd':
					itoa(*var,buf);
					while(*buf){*str++=*buf++;};
					break;
				case 'x':
					xtoa(*var,buf);
					while(*buf){*str++=*buf++;};
					break;
				case 's':
					buf=(char*)(*var);
					while(*buf){*str++=*buf++;};
					break;
			}
			buf=buffer;
			var++;
			format++;
		}

	}
	*str='\0';

}

static  inline char fourbtoc(int value){
	if(value >= 10)
		value = value - 10 + 65;
	else
		value = value + 48;
	return value;
}

void xtoa(unsigned int value,char *buf){
	char tmp_buf[30] = {0};
	char *tbp = tmp_buf;

	*buf++='0';
	*buf++='x';
	do{
		// *tbp++ = ('0' + (char)(value % 16));//得到低位数字
		*tbp++=fourbtoc(value&0x0000000f);

		//*tbp++ = ((value % 16)>9)?('A' + (char)(value % 16-10)):('0' + (char)(value % 16));//得到低位数字
		value >>= 4;
	}while(value);

	while(tmp_buf != tbp){
		tbp--;
		*buf++ = *tbp;
	}
	*buf='\0';
}



