code segment
assume CS:code
main:
	mov ax, 0b800h;
	mov es, ax
;	mov si, 25
;	mov sp, 160
;	mov bp, 14

	mov cx, 256
	mov sp, 0	; the x row
	mov bp, 0	; the y column

again:
	mov bh, 160
	mov ax, sp
	mul bh
	mov di, ax
	mov bh, 14
	mov ax, bp
	mul bh
	add di, ax	; the offset address, 160*x + 14*y

	mov bh, 25
	mov ax, bp
	mul bh
	mov si, ax
	add si, sp	; the character, 25*y + x

	mov ax, si
	mov ah, 17h
	mov es:[di], ax
	add di, 2
	mov al, ' '
	mov es:[di], ax
	add di, 2
	mov ax, si
	mov bh, 16
	div bh
	mov bh, ah
	cmp al, 10
	jb dec1
	add al, 'A'-10
	mov ah, 17h
	mov es:[di], ax
	jmp num2
next_again:
	jmp again
dec1:
	add al, '0'
	mov ah, 17h
	mov es:[di], ax
num2:
	add di, 2
	mov al, bh
	cmp al, 10
	jb dec2
	add al, 'A'-10
	mov ah, 17h
	mov es:[di], ax
	jmp h
dec2:
	add al, '0'
	mov ah, 17h
	mov es:[di], ax
h:
	add di, 2
	mov al, 'h'
	mov es:[di], ax
	add di, 2
	mov al, ' '
	mov es:[di], ax
	add di, 2
	mov es:[di], ax

	inc sp
	mov dx, 25
	sub dx, sp
	jnz next_row
	mov sp, 0
	inc bp
next_row:
	sub cx, 1
	jnz next_again

	mov ah, 0
	int 16h;	press a key
	mov ah, 4ch
	int 21h
code ends
end main