	global darker
	extern printf
	section .text
darker:
	; function takes 2 arguments
	; first is the base value, which is 16 bits value
	; second is the change value, which is 16 bits value
	; should return max(0, min(255, first_arg + second_arg))
	mov     ax, di        ; move first argument to result
	add     ax, si        ; add first second arguemnt to result
	mov     cx, 0         ; 
	cmp     ax, cx        ; is result lower than 0?
	cmovl   ax, cx        ; if yes, set result to 0
	mov     cx, 255       ; move 0 to register
	cmp     cx, ax        ; is 255 lower than result
	cmovl   ax, cx        ; if yes set result to 255
	ret                   ; return result