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
        push r11                  ; store r11
        push r13                  ; store r13
        push r14                  ; store r14
        mov  r14, rdi             ; move rdi to r14, rdi will be used to pass arg to darker
        imul r8, 2                ; colors are 0 - red, 1 - green, 2 - blue, each 2 bytes
row_loop:
        dec rdx                   ; for loop step
        mov r11, [r14 + 8 * rdx]  ; r11 is address of one row
        add r11, r8               ; add color offset to column start
        mov r13, rcx              ; store decreasing number of columns
column_loop:
        dec r13                   ; for loop step
        mov rdi, [r11]            ; mov value of color to rdi
        call darker               ; call function that change color
        mov [r11], ax             ; move change color from result to array field
        add r11, 6                ; add 6, as 6 is size of struct color
        cmp r13, 0                ; check if column loop iterator is 0
        jne column_loop           ; if not make one more round
        cmp rdx, 0                ; check if row loop iterator is 0
        jne row_loop              ; if not make one more round
        pop r14                   ; restore r14
        pop r13                   ; restore r13
        pop r11                   ; restore r11
        xor rax, rax              ; result is 0, as success
        ret

