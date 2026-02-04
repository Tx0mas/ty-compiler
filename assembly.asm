section .text
     backN db 10
section .bss
     bufferString resb 64
     buffer resb 16
    algo resb 8
section .text
    global _start
_start:
    mov rax, 1
    push rax
    pop rax
    mov qword[algo], rax
_whileMethod1:
    mov rax, [algo]
    push rax
    mov rax, 10
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    je _endLabel1
    _ifMethod2:
    mov rax, [algo]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    jne _endLabel2
    mov rax, "Printeo "
    mov qword [bufferString+0], rax
    mov rax, "el numer"
    mov qword [bufferString+8], rax
    mov rax, "o 2"
    mov qword [bufferString+16], rax
    mov byte[bufferString+19],0
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
    jmp _endIf1
_endLabel2:
    _ifMethod3:
    mov rax, [algo]
    push rax
    mov rax, 3
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    jne _endLabel3
    mov rax, "Printeo "
    mov qword [bufferString+0], rax
    mov rax, "el numer"
    mov qword [bufferString+8], rax
    mov rax, "o 3"
    mov qword [bufferString+16], rax
    mov byte[bufferString+19],0
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
    mov rax, [algo]
    push rax
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
    jmp _endIf1
_endLabel3:
    mov rax, "Printeo "
    mov qword [bufferString+0], rax
    mov rax, "otro"
    mov qword [bufferString+8], rax
    mov byte[bufferString+12],0
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
    mov rax, [algo]
    push rax
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
_endIf1:
_endIf2:
    mov rax, [algo]
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    mov qword[algo], rax
    jmp _whileMethod1
_endLabel1:
_whileMethod2:
    mov rax, [algo]
    push rax
    mov rax, 20
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    je _endLabel4
    _ifMethod5:
    mov rax, [algo]
    push rax
    mov rax, 11
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    jne _endLabel5
    mov rax, "Printeo "
    mov qword [bufferString+0], rax
    mov rax, "el numer"
    mov qword [bufferString+8], rax
    mov rax, "o 11"
    mov qword [bufferString+16], rax
    mov byte[bufferString+20],0
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
    mov rax, [algo]
    push rax
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
    jmp _endIf3
_endLabel5:
    _ifMethod6:
    mov rax, [algo]
    push rax
    mov rax, 12
    push rax
    pop rbx
    pop rdx
    cmp rbx, rdx
    jne _endLabel6
    mov rax, "Printeo "
    mov qword [bufferString+0], rax
    mov rax, "el numer"
    mov qword [bufferString+8], rax
    mov rax, "o 12"
    mov qword [bufferString+16], rax
    mov byte[bufferString+20],0
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
    mov rax, [algo]
    push rax
    pop rax
_printNumbers5:
    mov rbx, 0
    mov [buffer],rbx
    
    
    mov rcx, 8
    mov byte [buffer+rcx], 0
_printLoopNumbers5:
    mov rdx, 0
    mov rbx, 10
    div rbx
    mov rbx, rdx ;;aca posiblemente hay un error
    add rbx, 48
    dec rcx
    mov byte [buffer+rcx],bl
    cmp rax, 0
    je _done5
    jmp _printLoopNumbers5
_done5:
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
    jmp _endIf3
_endLabel6:
    mov rax, "Printeo "
    mov qword [bufferString+0], rax
    mov rax, "otro"
    mov qword [bufferString+8], rax
    mov byte[bufferString+12],0
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
    mov rax, [algo]
    push rax
    pop rax
_printNumbers6:
    mov rbx, 0
    mov [buffer],rbx
    
    
    mov rcx, 8
    mov byte [buffer+rcx], 0
_printLoopNumbers6:
    mov rdx, 0
    mov rbx, 10
    div rbx
    mov rbx, rdx ;;aca posiblemente hay un error
    add rbx, 48
    dec rcx
    mov byte [buffer+rcx],bl
    cmp rax, 0
    je _done6
    jmp _printLoopNumbers6
_done6:
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
_endIf3:
_endIf4:
    mov rax, [algo]
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    mov qword[algo], rax
    jmp _whileMethod2
_endLabel4:
    mov rax, 60
    mov rdi, 0
    syscall
