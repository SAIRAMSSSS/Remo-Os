#include "console.h"
#include "../kernel/print/print.h"

void console_init() {
    print_set_color(0x0F);
    kprint("RemoOS Console Initialized\n");
    kprint("> ");
}