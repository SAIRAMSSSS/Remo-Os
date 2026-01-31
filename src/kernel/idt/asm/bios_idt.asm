[bits 32]
global load_idt_bios

load_idt_bios:
    mov eax, [esp + 4]
    lidt [eax]
    ret