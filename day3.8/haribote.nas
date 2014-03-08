;haribote.nas
CYLS EQU 0x0ff0
LEDS EQU 0x0ff1
VMODE EQU 0x0ff2
SCRNX EQU 0x0ff4
SCRNY EQU 0x0ff6
VRAM EQU 0x0ff8

	org 0xc400

	mov al, 0x13
	mov ah, 0x00
	int 0x10

	mov byte [VMODE], 8
	mov word [SCRNX], 320
	mov word [SCRNY], 200
	mov dword [VRAM], 0x000a0000

	mov ah, 0x02
	int 0x16
	mov [LEDS], al

	mov si, mymsg		;!!!哦，让我们来显示自己的字符吧！
	call putchar

fin:
	hlt
	jmp fin

putchar:
	;原作者真是无聊，3.8节竟然依然是黑框框。
	;那么我们就来做点修改，显示一些字符吧!
	mov al, [si]
	add si, 1
	cmp al, 0
	je over
	mov ah, 0x0e
	mov bx, 15
	int 0x10
	jmp putchar
over:
	ret

mymsg:
	db 0x0a, 0x0d
	db "========="
	db 0x0a, 0x0d
	db "Hey, man~~~I'm ChrisZZ"
	db 0x0a, 0x0d
	db "my kernel is running"
	db 0x00
