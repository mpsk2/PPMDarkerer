	global darker
	section .text
darker:
	mov	rcx, 0
	mov	rdx, 255
	mov	rax, rdi            ; result initially holds arg
	add	rax, rsi            ; add second arguemnt to return value
	cmp	rax, rcx            ; is result lower than 0?
	cmovl   rax, rcx            ; if yes, set it to 0
	cmp	rdx, rax            ; is result higher than 255?
	cmovl   rax, rdx            ; if yes, set it to 255
	ret                         ; return arg
