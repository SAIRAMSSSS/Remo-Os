#include "keyboard.h"
#include "../ascci.h"
#include "../../kernel/print/print.h"

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void keyboard_handler() {
    uint8_t scancode = inb(0x60);
    if (!(scancode & 0x80)) {
        if (kbd_us[scancode] != 0) {
            kprint_char(kbd_us[scancode]);
        }
    }
}