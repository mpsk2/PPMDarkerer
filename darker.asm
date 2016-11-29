	global darker
	extern printf
	section .text
darker:
	; function takes 2 arguments
	; first is the base value, which is 16 bits value
	; second is the change value, which is 16 bits value
	; should return max(0, min(255, first_arg + second_arg))
	push    r12
	xor     rax, rax
	mov     ax,  di         ; move first argument to result
	add     ax,  si         ; add first second arguemnt to result
	mov     r12w, 0         ; 
	cmp     ax, r12w        ; is result lower than 0?
	cmovl   ax, r12w        ; if yes, set result to 0
	mov     r12w, 255       ; move 0 to register
	cmp     r12w, ax        ; is 255 lower than result
	cmovl   ax, r12w        ; if yes set result to 255
	pop     r12
	ret                     ; return result