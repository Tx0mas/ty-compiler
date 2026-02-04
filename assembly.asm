DEFAULT REL
section .text
     backN db 10
section .bss
     bufferString resb 64
     buffer resb 16
    newvar resb 8
    string resb 64
    variable resb 8
    algo resb 8
section .text
    global _start
_start:
    mov rax, 1
    push rax
    pop rax
    mov qword[algo], rax
    mov rax, 25
    push rax
    pop rax
    mov qword[variable], rax
    mov rax, 3
    push rax
    mov rax, 3
    push rax
    pop rbx
    pop rax
    mul rbx
    push rax
    mov rax, 3
    push rax
    pop rbx
    pop rax
    mov rdx, 0
    div rbx
    push rax
    pop rax
    mov qword[newvar], rax
    mov rax, "este es "
    mov qword [string+0], rax
    mov rax, "un strin"
    mov qword [string+8], rax
    mov rax, "g largui"
    mov qword [string+16], rax
    mov rax, "simo!!!!"
    mov qword [string+24], rax
    mov byte[string+32],0
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
    mov rax, [newvar]
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
    mov rax, string
    push rax
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
    mov rax, " "
    mov qword [bufferString+0], rax
    mov byte[bufferString+1],0
    push bufferString
    mov rbx, 0
    mov rsi, [rsp]
_printString6:
    cmp byte [rsi+rbx], 0
    je _doneString6
    inc rbx
    jmp _printString6
_doneString6:
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
_printString7:
    cmp byte [rsi+rbx], 0
    je _doneString7
    inc rbx
    jmp _printString7
_doneString7:
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
    mov rax, [variable]
    push rax
    mov rax, 25
    push rax
    pop rbx
    neg rbx
    push rbx
    pop rbx
    pop rdx
    cmp rdx, rbx
    jl _endLabel3
    mov rax, [variable]
    push rax
    pop rax
    cmp rax, 0
    jge _printNumbers4
    mov [buffer], 45
    neg rax
    push rax
    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, 1
    syscall
    pop rax
_printNumbers4:
    mov rbx, 0
    mov [buffer],rbx
    
    
    mov rcx, 8
    mov byte [buffer+rcx], 0
_printLoopNumbers4:
    mov rdx, 0
    mov rbx, 10
    div rbx
    mov rbx, rdx ;;aca posiblemente hay un error
    add rbx, 48
    dec rcx
    mov byte [buffer+rcx],bl
    cmp rax, 0
    je _done4
    jmp _printLoopNumbers4
_done4:
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
    mov rax, [variable]
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    sub rax, rbx
    push rax
    pop rax
    mov qword [variable], rax
    jmp _whileMethod2
_endLabel3:
    mov rax, 60
    mov rdi, 0
    syscall
