; Print the ASCII table
data segment
	x dw 0
	y dw 0
	z dw 0
	sx db "00000", 0
	sy db "00000", 0
	sz db "00000", 0
data ends
code segment
assume cs:code, ds:data
main:
	mov ax, data
	mov ds, ax
	mov di, offset sx
	call input
	mov di, offset sy
	call input
	
	mov si, offset sx; SI->"123"
	call atoi; AX = 123	
	mov [x], ax
	mov si, offset sy; SI->"456"
	call atoi; AX = 456
	mov [y], ax
	
	mov ax, [x]
	add ax, [y]
	mov [z], ax
	mov dx, [x]
	cmp ax, dx
	jb overflow	; 判断溢出
	mov dx, [y]
	cmp ax, dx
	jb overflow
	jmp normal
overflow:
	mov ah, 2
	mov dl, '1'
	int 21h
normal:
	mov ax, [z]
	mov di, offset sz
	call itoa;	把ax转化为字符串存入di
	mov di, offset sz
	call output
	
	mov ah, 4Ch
	int 21h

atoi:				; 输入si十六进制字符串，返回ax
	mov ax, 0
	mov bh, 0
atoi_next:
	mov bl, [si]
	cmp bl, 0
	je atoi_done
	mov cx, 16
	mul cx;			乘积为dx:ax，其中dx为0
	cmp bl, 'A'
	jb atoi_dec
	sub bl, 'A'
	add bl, 10
	jmp atoi_add
atoi_dec:
	sub bl, '0'
atoi_add:
	add ax, bx
	inc si
	jmp atoi_next
atoi_done:
	ret

itoa:				; 输入ax整数，返回di字符串
	mov cx, 0; 	位数
	mov si, 16; 除数
itoa_next:
	mov dx, 0; 	被除数的高16位
	div si; 		ax = 商，dx = 余数
	push dx
	inc cx
	cmp ax, 0
	jnz itoa_next
itoa_pop:
	pop dx
	cmp dl, 10
	jb itoa_dec
	add dl, 'A' - 10
	jmp itoa_mov
itoa_dec:
	add dl, '0'
itoa_mov:
	mov [di], dl
	inc di
	dec cx
	jnz itoa_pop
	mov byte ptr [di], 0
	ret
	
input:
	mov ah, 1
	int 21h
	cmp al, 0Dh
	je input_done
	mov [di], al
	inc di
	jmp input
input_done:
	mov byte ptr [di], 0
	mov ah,2
	mov dl,0Dh
	int 21h
	mov ah,2
	mov dl,0Ah
	int 21h
	ret
	
output:			; 输入di字符串，输出到屏幕
	mov ah, 2
	mov dl, [di]
	cmp dl, 0
	je output_done
	int 21h
	inc di
	jmp output
output_done:
	mov ah, 2
	mov dl, 0Dh
	int 21h
	mov ah, 2
	mov dl, 0Ah
	int 21h
	ret
	
code ends
end main