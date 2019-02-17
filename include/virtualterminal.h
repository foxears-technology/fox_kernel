#ifndef __VIRTUALTERMINAL_H
#define __VIRTUALTERMINAL_H

#include <stddef.h>
#include <stdint.h>

#define VIRTUALTERMINALS_LENGTH (3)

extern void virtualterminal_initialize(void);

extern void virtualterminal_clear(size_t vterm);
extern void virtualterminal_clearline(size_t vterm, size_t row);
extern void virtualterminal_reset(size_t vterm);

extern size_t virtualterminal_getindex(size_t vterm);
extern void virtualterminal_setcursor(size_t vterm, size_t x, size_t y);
extern void virtualterminal_updatehardcursor(size_t vterm);
extern void virtualterminal_setcolor(size_t vterm, uint8_t color);

extern void virtualterminal_swapbuffer(size_t oldvterm);

extern void virtualterminal_inccurrent(void);
extern void virtualterminal_deccurrent(void);
extern void virtualterminal_setcurrent(size_t vterm);

extern void virtualterminal_newline(size_t vterm);
extern void virtualterminal_scroll(size_t vterm);

extern void virtualterminal_putchar(size_t vterm, char c);
extern void virtualterminal_write(size_t vterm, const char* data, size_t size);
extern void virtualterminal_writestring(size_t vterm, const char* data);

#endif /* __VIRTUALTERMINAL_H */
