/*
 * ==================================================
 *
 *       Filename:  fifo.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  2014年03月06日 星期四 18时42分55秒
 *         Author:  ChrisZZ, zchrissirhcz@163.com
 *        Company:  ZJUT
 *
 * ==================================================
 */
#include <header.h>
#define FLAGS_OVERRUN 0x0001

void fifo8_init(struct FIFO8* fifo, int size, char *buf){
	fifo->size = size;
	fifo->buf = buf;
	fifo->free = size;
	fifo->flags = 0;
	fifo->p = 0;
	fifo->q = 0;
	return;
}

int fifo8_put(struct FIFO8* fifo, char data){
	if(fifo->free==0){
		fifo->flags |= FLAGS_OVERRUN;
		return -1;
	}
	fifo->buf[fifo->p] = data;
	fifo->p++;
	if(fifo->p == fifo->size){
		fifo->p=0;
	}
	fifo->free--;
	return 0;
}
