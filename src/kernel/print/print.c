#include "print.h"

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* video_mem = (struct Char*) 0xB8000;
uint8_t current_color = 0x07;
int cursor_x = 0;
int cursor_y = 0;

void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void update_cursor(int x, int y) {
    uint16_t pos = y * 80 + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void print_clear() {
    for (int i = 0; i < 80 * 25; i++) {
        video_mem[i] = (struct Char) {' ', current_color};
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor(cursor_x, cursor_y);
}

void kprint_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            video_mem[cursor_y * 80 + cursor_x] = (struct Char) {' ', current_color};
        }
    } else {
        video_mem[cursor_y * 80 + cursor_x] = (struct Char) {c, current_color};
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= 25) {
        print_clear();
    }

    update_cursor(cursor_x, cursor_y);
}

void kprint(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        kprint_char(str[i]);
    }
}

void print_set_color(uint8_t color) {
    current_color = color;
}