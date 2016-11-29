	global darkerer
	extern printf
	extern darker

	section .text
darkerer:
        ; we assume we know the implementation of darker
        ; rsi will never be changed by darker
        ; rdi is pointer to matrix
        ; rsi is change value - 16 bits
        ; rdx is number of rows
        ; rcx is number of columns
        ; r8 is color changed
        push r10
        push r11
        push r12
        push r13
        push r14
        mov  r14, rdi
        mov  r12, rdx
row_loop:
        dec r12
        mov r11, [r14 + 8*r12]
        mov r10, 2
        imul r10, r8
        add r11, r10
        mov r13, rcx
column_loop:
        dec r13
        mov rdi, [r11]
        call darker
        mov [r11], ax
        add r11, 6
        cmp r13, 0
        jne column_loop
        cmp r12, 0
        jne row_loop
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        ret

