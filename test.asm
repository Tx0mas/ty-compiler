section .bss
    buffer resb 16

section .data
    variable db "Hola amigos este string es larguisimo",0

section .text
    global _start

_start:
    mov rax, variable
    push rax

    mov rbx, 0
    mov rsi, [rsp]
_printString:
    cmp byte [rsi+rbx], 0
    je _doneString
    inc rbx
    jmp _printString
_doneString: 
    mov rax, 1
    mov rdi, 1
    pop rsi
    mov rdx, rbx
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
     
    

    
