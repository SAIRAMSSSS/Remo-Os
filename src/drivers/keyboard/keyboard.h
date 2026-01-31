#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void keyboard_init();
void keyboard_handler();
uint8_t inb(uint16_t port);

#endif