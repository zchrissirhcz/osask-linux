;haribote.nas
	org 0xc400

	mov al, 0x13
	mov ah, 0x00
	int 0x10

fin:
	hlt
	jmp fin

