#ifndef __TERMINAL_H
#define __TERMINAL_H

#include <stddef.h>
#include <stdint.h>

extern void terminal_initialize(void);

extern void terminal_clear(void);
extern void terminal_clearline(size_t row);
extern void terminal_reset(void);

extern void terminal_setcursor(size_t x, size_t y);
extern void terminal_updatehardcursor(void);
extern void terminal_setcolor(uint8_t color);

extern void terminal_newline(void);
extern void terminal_scroll(void);

extern void terminal_putchar(char c);
extern void terminal_write(const char* data, size_t size);
extern void terminal_writestring(const char* data);

#endif /* __TERMINAL_H */
