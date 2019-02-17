#include <terminal.h>
#include <system.h>

#include <vga.h>

static struct terminal
{
  size_t row;
  size_t column;
  uint8_t color;
  uint16_t* buffer;
} terminal;

void terminal_initialize(void)
{
	terminal.row = 0;
	terminal.column = 0;
	terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	terminal.buffer = VGA_MEMORY;
	terminal_updatehardcursor();
	terminal_clear();
}

void terminal_clear(void)
{
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
		terminal_clearline(y);
  }
}

void terminal_clearline(size_t row)
{
  for (size_t x = 0; x < VGA_WIDTH; x++) {
    const size_t index = row * VGA_WIDTH + x;
    terminal.buffer[index] = vga_entry(' ', terminal.color);
  }
}

void terminal_reset(void)
{
  terminal.row = 0;
  terminal.column = 0;
	terminal_updatehardcursor();
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
  terminal_clear();
}

void terminal_setcursor(size_t x, size_t y)
{
  if(x < VGA_WIDTH) {
    terminal.column = x;
  }
  if(y < VGA_HEIGHT) {
    terminal.row = y;
  }
	terminal_updatehardcursor();
}

void terminal_updatehardcursor(void)
{
  const size_t index = terminal.row * VGA_WIDTH + terminal.column;

  /* This sends a command to indicies 14 and 15 in the
  *  CRT Control Register of the VGA controller. These
  *  are the high and low bytes of the index that show
  *  where the hardware cursor is to be 'blinking'. To
  *  learn more, you should look up some VGA specific
  *  programming documents. A great start to graphics:
  *  http://www.brackeen.com/home/vga */
  outb(0x3D4, 14);
  outb(0x3D5, index >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, index);
}

void terminal_newline(void)
{
  if (++terminal.row == VGA_HEIGHT) {
    terminal.row = VGA_HEIGHT - 1;
    terminal_scroll();
  }
  terminal.column = 0;
	terminal_updatehardcursor();
}

void terminal_scroll(void)
{
	memcpy(terminal.buffer, terminal.buffer + VGA_WIDTH, (VGA_HEIGHT - 1) * VGA_WIDTH * 2);

	terminal_clearline(VGA_HEIGHT - 1);
}

void terminal_setcolor(uint8_t color)
{
	terminal.color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal.buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	unsigned char uc = c;
  if (uc == '\n') {
    terminal_newline();
  } else {
    terminal_putentryat(uc, terminal.color, terminal.column, terminal.row);

  	if (++terminal.column == VGA_WIDTH) {
  		terminal.column = 0;
			if (++terminal.row == VGA_HEIGHT) {
		    terminal.row = VGA_HEIGHT - 1;
		    terminal_scroll();
		  }
  	}
		terminal_updatehardcursor();
  }
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}
