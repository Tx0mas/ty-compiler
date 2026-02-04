section .text
     backN db 10
section .bss
     bufferString resb 64
     buffer resb 16
    algo resb 8
section .text
    global _start
_start:
    mov rax, 2
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    mul rbx
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    mov rdx, 0
    div rbx
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    sub rax, rbx
    push rax
    mov rax, 6
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    mov rdx, 0
    div rbx
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    mov qword[algo], rax
    mov rax, [algo]
    push rax
   pop rax
_printNumbers1:
   mov rbx, 0
   mov [buffer],rbx
   
   
   mov rcx, 8
   mov byte [buffer+rcx], 0
_printLoopNumbers1:
   mov rdx, 0
   mov rbx, 10
   div rbx
   mov rbx, rdx ;;aca posiblemente hay un error
   add rbx, 48
   dec rcx
   mov byte [buffer+rcx],bl
   cmp rax, 0
   je _done1
   jmp _printLoopNumbers1
_done1:
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
   
   mov rax, 1
   mov rdi, 1
   mov rsi, backN
   mov rdx, 1
   syscall
    mov rax, 60
    mov rdi, 0
    syscall
