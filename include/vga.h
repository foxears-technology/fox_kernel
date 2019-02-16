#ifndef __VGA_H
#define __VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH (80)
#define VGA_HEIGHT (25)
#define VGA_LENGTH (VGA_HEIGHT * VGA_WIDTH)

static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline unsigned short vga_entry(unsigned char uc, unsigned char color) {
	return (unsigned short) uc | (unsigned short) color << 8;
}

#endif /* __VGA_H */
