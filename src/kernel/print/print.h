#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include <stddef.h>

void print_clear();
void kprint(char* str);
void kprint_char(char c);
void print_set_color(uint8_t color);
void update_cursor(int x, int y);

#endif