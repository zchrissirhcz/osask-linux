/*
 * ==================================================
 *
 *       Filename:  mouse.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  2014年03月07日 星期五 09时51分45秒
 *         Author:  ChrisZZ, zchrissirhcz@163.com
 *        Company:  ZJUT
 *
 * ==================================================
 */
#include <header.h>
void wait_KBC_sendready(void){
	for(;;){
		if((inb(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY)==0){
			break;
		}
	}
	return;
}

void init_keyboard(void){
	wait_KBC_sendready();
	outb(PORT_KEYCMD, KEYCMD_WRITE_MODE);
	wait_KBC_sendready();
	outb(PORT_KEYDAT, KBC_MODE);
	return;
}

void enable_mouse(void){
	wait_KBC_sendready();
	outb(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	wait_KBC_sendready();
	outb(PORT_KEYDAT, MOUSECMD_ENABLE);
	return;
}
