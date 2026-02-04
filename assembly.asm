section .text
     backN db 10
section .bss
     bufferString resb 64
     buffer resb 16
    ashe resb 8
    algo resb 8
section .text
    global _start
_start:
    mov rax, 1
    push rax
    pop rax
    mov qword[algo], rax
    mov rax, 50
    push rax
    pop rax
    mov qword[ashe], rax
_whileMethod1:
    mov rax, [algo]
    push rax
    mov rax, 50
    push rax
    pop rbx
    pop rdx
    cmp rdx, rbx
    jg _endLabel1
    _ifMethod2:
    mov rax, [algo]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    mov rdx, 0
    div rbx
    push rdx
    mov rax, 0
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    jne _endLabel2
    mov rax, [algo]
    push rax
    pop rax
    cmp rax, 0
    jge _printNumbers1
    mov [buffer], 45
    neg rax
    push rax
    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, 1
    syscall
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
    mov rax, "Es par"
    mov qword [bufferString+0], rax
    mov byte[bufferString+6],0
    push bufferString
    mov rbx, 0
    mov rsi, [rsp]
_printString1:
    cmp byte [rsi+rbx], 0
    je _doneString1
    inc rbx
    jmp _printString1
_doneString1:
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
    jmp _endIf1
_endLabel2:
    mov rax, [algo]
    push rax
    pop rax
    cmp rax, 0
    jge _printNumbers2
    mov [buffer], 45
    neg rax
    push rax
    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, 1
    syscall
    pop rax
_printNumbers2:
    mov rbx, 0
    mov [buffer],rbx
    
    
    mov rcx, 8
    mov byte [buffer+rcx], 0
_printLoopNumbers2:
    mov rdx, 0
    mov rbx, 10
    div rbx
    mov rbx, rdx ;;aca posiblemente hay un error
    add rbx, 48
    dec rcx
    mov byte [buffer+rcx],bl
    cmp rax, 0
    je _done2
    jmp _printLoopNumbers2
_done2:
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
    mov rax, "Es impar"
    mov qword [bufferString+0], rax
    mov byte[bufferString+8],0
    push bufferString
    mov rbx, 0
    mov rsi, [rsp]
_printString2:
    cmp byte [rsi+rbx], 0
    je _doneString2
    inc rbx
    jmp _printString2
_doneString2:
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
_endIf1:
    mov rax, [algo]
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    mov qword [algo], rax
    jmp _whileMethod1
_endLabel1:
    mov rax, " "
    mov qword [bufferString+0], rax
    mov byte[bufferString+1],0
    push bufferString
    mov rbx, 0
    mov rsi, [rsp]
_printString3:
    cmp byte [rsi+rbx], 0
    je _doneString3
    inc rbx
    jmp _printString3
_doneString3:
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
    mov rax, " "
    mov qword [bufferString+0], rax
    mov byte[bufferString+1],0
    push bufferString
    mov rbx, 0
    mov rsi, [rsp]
_printString4:
    cmp byte [rsi+rbx], 0
    je _doneString4
    inc rbx
    jmp _printString4
_doneString4:
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
    mov rax, " "
    mov qword [bufferString+0], rax
    mov byte[bufferString+1],0
    push bufferString
    mov rbx, 0
    mov rsi, [rsp]
_printString5:
    cmp byte [rsi+rbx], 0
    je _doneString5
    inc rbx
    jmp _printString5
_doneString5:
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
_whileMethod2:
    mov rax, [ashe]
    push rax
    mov rax, 2
    push rax
    pop rbx
    neg rbx
    push rbx
    pop rbx
    pop rdx
    cmp rdx, rbx
    jl _endLabel3
    mov rax, [ashe]
    push rax
    pop rax
    cmp rax, 0
    jge _printNumbers3
    mov [buffer], 45
    neg rax
    push rax
    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, 1
    syscall
    pop rax
_printNumbers3:
    mov rbx, 0
    mov [buffer],rbx
    
    
    mov rcx, 8
    mov byte [buffer+rcx], 0
_printLoopNumbers3:
    mov rdx, 0
    mov rbx, 10
    div rbx
    mov rbx, rdx ;;aca posiblemente hay un error
    add rbx, 48
    dec rcx
    mov byte [buffer+rcx],bl
    cmp rax, 0
    je _done3
    jmp _printLoopNumbers3
_done3:
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
    mov rax, [ashe]
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    sub rax, rbx
    push rax
    pop rax
    mov qword [ashe], rax
    jmp _whileMethod2
_endLabel3:
    mov rax, 60
    mov rdi, 0
    syscall
