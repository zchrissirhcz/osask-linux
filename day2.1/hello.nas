;hello.nas
	org 0x7c00;跳转到内存地址0x7c00处

fat12:
	;设定fat12格式
	jmp entry
	db 0x90
	db "chris_zz";	8bytes
	dw 512
	db 1
	dw 1
	db 2
	dw 224
	dw 2880
	db 0xf0
	dw 9
	dw 18
	dw 2
	dd 0
	dd 2880
	db 0,0,0x29
	dd 0xffffffff
	db "My First OS"
	db "FAT12   "

entry:
	;程序主要部分
	mov ax, 0
	mov ss, ax
	mov ds, ax
	mov es, ax

	mov sp, 0x7c00

	mov si, msg

putloop:
	;循环显示字符
	;通过0x10中断，显示一个字符
	mov al, [si]
	add si, 1
	cmp al, 0
	je fin
	mov ah, 0x0e
	mov bx, 10
	int 0x10
	jmp putloop

fin:
	;当需要显示的信息都显示完毕，那么进入死循环
	hlt
	jmp fin

msg:
	;设定需要显示的字符
	db 0x0a, 0x0a
	db "============="
	db 0x0a
	db 0x0d
	db "Nice day ~~~"
	db 0x0a
	db 0x0d
	db "This is my first 0S"
	db 0x0a
	db 0x0d
	db "copyright GPL"
	db 0x0a
	db 0x0d
	db "AUTHOR: ChrisZZ"
	db 0x0a
	db 0x0d
	db "blog:http://chriszz.sinaapp.com"
	db 0x0a
	db 0x0d
	db 0

endpart:
	times 510-($-$$) db 0
	db 0x55, 0xaa
