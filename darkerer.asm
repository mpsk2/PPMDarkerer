	struc point
	.r resd 8
	.g resd 8
	.b resd 8
	endstruc

	global darkerer
	extern printf

	section .text
darkerer:
	push      rdi
	push      rsi
	push      rdx
	mov	  r15, rdi
	mov       rdi, format              ; set 1st printf argument
	mov       rsi, [r15]
	mov       rsi, [rsi]	
	call      printf                   ; calls printf(format, arr)
	pop       rdx
	pop       rsi
	pop       rdi
	ret
message:
	db "Hello, World!", 0
format:
	db "%20ld", 10, 0

