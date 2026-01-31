[bits 32]
section .text
global _start
extern kernel_main

ALIGN 4
section .multiboot
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002 + 0x00)

section .text
_start:
    cli
    mov esp, stack_space
    call kernel_main
    hlt

section .bss
resb 8192
stack_space: