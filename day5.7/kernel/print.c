#include<header.h>
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
