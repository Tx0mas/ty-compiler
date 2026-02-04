section .bss
    buffer resb 16

section .data
    variable db 123

section .text
    global _start

_start:
    mov rax, [variable]
    push rax

    pop rax
_printNumbers:
    mov rbx, 0
    mov [buffer],rbx


    mov rcx, 8
    mov byte [buffer+rcx], 0
_printLoopNumbers:
    mov rdx, 0
    mov rbx, 10
    div rbx
    mov rbx, rdx ;;aca posiblemente hay un error
    add rbx, 48
    dec rcx
    mov byte [buffer+rcx],bl
    cmp rax, 0
    je _done
    jmp _printLoopNumbers
_done:
    mov rax, buffer
    add rax, rcx
    push rax

    mov rax, 8
    sub rax, rcx
    mov rbx, rax

    mov rax, 1
    mov rdi, 1
    pop rsi
    mov rdx, rbx
    syscall


    mov rax, 60
    mov rdi, 0
    syscall

    

    
