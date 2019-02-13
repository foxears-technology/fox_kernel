#include <terminal.h>
#include <system.h>

#include <vga.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	terminal_updatehardcursor();
	terminal_clear();
}

void terminal_clear(void)
{
/*  size_t buffer_size = VGA_HEIGHT * VGA_WIDTH * 2;
  memset(terminal_buffer, vga_entry_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_MAGENTA),buffer_size);
  memset(terminal_buffer+1, 'A',buffer_size);*/
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_reset(void)
{
  terminal_row = 0;
  terminal_column = 0;
	terminal_updatehardcursor();
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
  terminal_clear();
}

void terminal_setcursor(size_t x, size_t y)
{
  if(x < VGA_WIDTH) {
    terminal_column = x;
  }
  if(y < VGA_HEIGHT) {
    terminal_row = y;
  }
	terminal_updatehardcursor();
}

void terminal_updatehardcursor(void)
{
  size_t temp;

  /* The equation for finding the index in a linear
  *  chunk of memory can be represented by:
  *  Index = [(y * width) + x] */
  temp = terminal_row * 80 + terminal_column;

  /* This sends a command to indicies 14 and 15 in the
  *  CRT Control Register of the VGA controller. These
  *  are the high and low bytes of the index that show
  *  where the hardware cursor is to be 'blinking'. To
  *  learn more, you should look up some VGA specific
  *  programming documents. A great start to graphics:
  *  http://www.brackeen.com/home/vga */
  outb(0x3D4, 14);
  outb(0x3D5, temp >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, temp);
}

void terminal_newline(void)
{
  if (++terminal_row == VGA_HEIGHT) {
    terminal_row = VGA_HEIGHT - 1;
    terminal_scroll();
  }
  terminal_column = 0;
}

void terminal_scroll(void)
{
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
		const size_t index_src = y * VGA_WIDTH;
		const size_t index_dst = index_src - VGA_WIDTH;
		memcpy(terminal_buffer + index_dst, terminal_buffer + index_src, VGA_WIDTH*2);
  }
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = VGA_WIDTH * (VGA_HEIGHT - 1) + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	unsigned char uc = c;
  if (uc == '\n') {
    terminal_newline();
  } else {
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);

  	if (++terminal_column == VGA_WIDTH) {
  		terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
		    terminal_row = VGA_HEIGHT - 1;
		    terminal_scroll();
		  }
  	}
  }
	terminal_updatehardcursor();
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
