[bits 32]
global read_keypress_bios

read_keypress_bios:
    mov ah, 0x00
    int 0x16
    ret