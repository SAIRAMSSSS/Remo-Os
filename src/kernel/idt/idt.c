#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    for(int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    asm volatile("lidt %0" : : "m"(idtp));
}