#include "print/print.h"
#include "idt/idt.h"
#include "../console/console.h"

void kernel_main() {
    idt_init();
    // Console: console_init();

    print_clear();
    print_set_color(0x0F);
    kprint("RemoOS Kernel Loaded\n");
    
    while(1) {
        asm volatile("hlt");
    }
}