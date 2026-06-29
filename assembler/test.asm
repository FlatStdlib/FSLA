section .data
    foo db "Gay", 10, 0

section .text
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel foo]
    mov rdx, 4
    syscall

    lea rsi, foo
    mov rsi, foo
    
    nop
    mov rax, 60
    mov rdi, 0
    syscall