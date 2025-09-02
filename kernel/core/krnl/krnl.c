// krnl.c

// ==== HEADERS ====
#include <stdint.h>
#include "krnl.h"

// ==== MACRO'S ====
#define VIDEO_MEMORY 0xB8000
#define WIDTH 80
#define HEIGHT 25

// ==== VARIABLES ====
uint16_t *video = (uint16_t *) VIDEO_MEMORY;
uint32_t seed = 12345678;
int cursor_row = 0;
int cursor_col = 0;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// ==== VIDEO CONTROLL ====
void outline(char *msg) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] == '\n') {
            cursor_col = 0;
            cursor_row++;
        } else if (msg[i] == '\b') {
            if (cursor_col > 0) {
                cursor_col--;
                video[cursor_row * WIDTH + cursor_col] = (uint16_t)(' ' | (0x07 << 8));
            } else if (cursor_row > 0) {
                cursor_row--;
                cursor_col = WIDTH - 1;
                video[cursor_row * WIDTH + cursor_col] = (uint16_t)(' ' | (0x07 << 8));
            }
        } else {
            video[cursor_row * WIDTH + cursor_col] = (uint16_t)(msg[i] | (0x07 << 8));
            cursor_col++;
            if (cursor_col >= WIDTH) {
                cursor_col = 0;
                cursor_row++;
            }
        }

        i++;
        if (cursor_row >= HEIGHT) cursor_row = 0;
    }
}
void clearline() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            video[y * WIDTH + x] = (uint16_t)(' ' | (0x07 << 8)); // пробел с цветом
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

// ==== TIME CONTROLL ====
void delay(int count) {
    for (int i = 0; i < count; i++) {
        __asm__ __volatile__("nop");
    }
}

// ==== RANDOM CONTROLL ====
uint32_t rand() {
    seed = (1103515245 * seed + 12345678) & 0x7fffffff;
    return seed;
}

// ==== ANALOGS TO STRING.H ====
// ==== SEE MORE IN krnl.h ====
int strcmp(const char *a, const char *b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}
int strlen(const char *s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}
void strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
}

// ==== KEYBOARD CONTROLL ====
uint8_t get_key() {
    if(inb(0x64) & 0x01) {
        return inb(0x60);
    }
    return 0;
}
void readline(char *buffer, int max_len) {
    int pos = 0;

    while (1) {
        uint8_t key = get_key();
        if (key == 0) continue;

        if (key == 0x1C) {
            buffer[pos] = '\0';
            outline("\n");
            return;
        }

        if (key == 0x0E && pos > 0) {
            pos--;
            outline("\b \b");
            continue;
        }

        char c = scancode_to_ascii(key);
        if (c && pos < max_len - 1) {
            buffer[pos++] = c;
            char s[2] = {c, 0};
            outline(s);
        }
    }
}
char scancode_to_ascii(uint8_t code) {
    switch(code) {
        // == Numbers ==
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';

        // == Characters ==
        case 0x10: return 'q';
        case 0x11: return 'w';
        case 0x12: return 'e';
        case 0x13: return 'r';
        case 0x14: return 't';
        case 0x15: return 'y';
        case 0x16: return 'u';
        case 0x17: return 'i';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x1E: return 'a';
        case 0x1F: return 's';
        case 0x20: return 'd';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x2C: return 'z';
        case 0x2D: return 'x';
        case 0x2E: return 'c';
        case 0x2F: return 'v';
        case 0x30: return 'b';
        case 0x31: return 'n';
        case 0x32: return 'm';

        // == Special Symbols ==
        case 0x39: return ' ';   // Space
        case 0x0E: return '\b';  // Backspace
        case 0x1C: return '\n';  // Enter
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x2B: return '\\';
        case 0x27: return ';';
        case 0x28: return '\'';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';

        default: return 0;
    }
}
void echo(char *msg) {
    outline(msg);
    outline("\n");
}

// == DONT WORKING ==
void shutdown() {
    outline("Shutting down...\n");
    delay(2000000000);
    __asm__ __volatile__ (
        "cli\n\t"
        "movw $0xB004, %ax\n\t"
        "movw $0x604, %dx\n\t"
        "outw %ax, %dx\n\t"
    );
    while(1);
}
// == REBOOT ==
void reboot() {
    outline("Rebooting...\n");
    delay(2000000000);
    __asm__ __volatile__ (
        "cli\n\t"
        "movb $0xFE, %al\n\t"
        "movw $0x64, %dx\n\t"
        "outb %al, %dx\n\t"
    );
    while(1);
}