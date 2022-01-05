print:
	push ax
	push bx
	mov ah, 0x0E
	char:
		mov al, [bx]
		cmp al, 0
		je endc
		int 0x10
		inc bx
		jmp char
	endc:
	pop bx
	pop ax
	ret
