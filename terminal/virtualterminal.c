#include <virtualterminal.h>

#include <system.h>
#include <vga.h>

/*
  #TODO  provide virtual buffer and dont force cpy on VGA_MEMORY
  only cpy during swap between vterm
*/

/*
provide multiple terminals
*/

/*
should have keyboard shortcut + dynamic mem allocation
*/

/*
0: main view + splash
1: kernel logger
2: interrupt print
...
*/

#define VIRTUALTERMINALS_LENGTH (3)

struct virtualterminal
{
  size_t row;
  size_t column;
  uint8_t color;
  uint16_t buffer[VGA_LENGTH];
};

struct virtualterminal virtualterminals[VIRTUALTERMINALS_LENGTH];

static size_t virtualterminal_current = 0;

void virtualterminal_initialize(void)
{
  for(size_t i=0; i<VIRTUALTERMINALS_LENGTH; i++) {
    virtualterminals[i].row = 0;
    virtualterminals[i].column = 0;
    virtualterminals[i].color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    virtualterminal_updatehardcursor(i);
    virtualterminal_clear(i);
  }
}

void virtualterminal_clear(size_t vterm)
{
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
		virtualterminal_clearline(vterm, y);
  }
}

void virtualterminal_clearline(size_t vterm, size_t row)
{
  for (size_t x = 0; x < VGA_WIDTH; x++) {
    const size_t index = row * VGA_WIDTH + x;
    virtualterminals[vterm].buffer[index] = vga_entry(' ', virtualterminals[vterm].color);
  }
}

void virtualterminal_reset(size_t vterm)
{
  virtualterminals[vterm].row = 0;
  virtualterminals[vterm].column = 0;
	virtualterminal_setcolor(vterm, vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
  virtualterminal_updatehardcursor(vterm);
  virtualterminal_clear(vterm);
}

size_t virtualterminal_getindex(size_t vterm)
{
  const size_t index =
    virtualterminals[vterm].row * VGA_WIDTH +
    virtualterminals[vterm].column;

  return index;
}

void virtualterminal_setcursor(size_t vterm, size_t x, size_t y)
{
  if(x < VGA_WIDTH) {
    virtualterminals[vterm].column = x;
  }
  if(y < VGA_HEIGHT) {
    virtualterminals[vterm].row = y;
  }
	virtualterminal_updatehardcursor(vterm);
}

void virtualterminal_updatehardcursor(size_t vterm)
{
  if(vterm == virtualterminal_current) {
    const size_t index = virtualterminal_getindex(vterm);

    outb(0x3D4, 14);
    outb(0x3D5, index >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, index);
  }
}

void virtualterminal_setcolor(size_t vterm, uint8_t color)
{
  virtualterminals[vterm].color = color;
}

void virtualterminal_display(size_t vterm)
{
  if(vterm == virtualterminal_current) {
    memcpy(
      VGA_MEMORY,
      virtualterminals[vterm].buffer,
      VGA_LENGTH * 2
    );
  }
}

void virtualterminal_inccurrent(void)
{
  if(++virtualterminal_current >= VIRTUALTERMINALS_LENGTH) {
    virtualterminal_current = VIRTUALTERMINALS_LENGTH - 1;
  }
  virtualterminal_display(virtualterminal_current);
  virtualterminal_updatehardcursor(virtualterminal_current);
}

void virtualterminal_deccurrent(void)
{
  if(--virtualterminal_current == (size_t)-1) {
    virtualterminal_current = 0;
  }
  virtualterminal_display(virtualterminal_current);
  virtualterminal_updatehardcursor(virtualterminal_current);
}

void virtualterminal_setcurrent(size_t vterm)
{
  if(vterm < VIRTUALTERMINALS_LENGTH) {
    virtualterminal_current = vterm;
    virtualterminal_updatehardcursor(vterm);
  }
}

void virtualterminal_newline(size_t vterm)
{
  if (++virtualterminals[vterm].row == VGA_HEIGHT) {
    virtualterminals[vterm].row = VGA_HEIGHT - 1;
    virtualterminal_scroll(vterm);
  }
  virtualterminals[vterm].column = 0;
  virtualterminal_updatehardcursor(vterm);
}

void virtualterminal_scroll(size_t vterm)
{
  memcpy(
    virtualterminals[vterm].buffer,
    virtualterminals[vterm].buffer + VGA_WIDTH,
    (VGA_HEIGHT - 1) * VGA_WIDTH * 2
  );

  virtualterminal_clearline(vterm, VGA_HEIGHT - 1);
}

void virtualterminal_putentryat(size_t vterm, unsigned char c)
{
	const size_t index = virtualterminal_getindex(vterm);

	virtualterminals[vterm].buffer[index] = vga_entry(c, virtualterminals[vterm].color);
}

void virtualterminal_putchar(size_t vterm, char c)
{
	unsigned char uc = c;
  if (uc == '\n') {
    virtualterminal_newline(vterm);
  } else {
    virtualterminal_putentryat(
      vterm, uc
    );

  	if (++virtualterminals[vterm].column == VGA_WIDTH) {
  		virtualterminals[vterm].column = 0;
			if (++virtualterminals[vterm].row == VGA_HEIGHT) {
		    virtualterminals[vterm].row = VGA_HEIGHT - 1;
		    virtualterminal_scroll(vterm);
		  }
  	}
		virtualterminal_updatehardcursor(vterm);
  }
}

void virtualterminal_write(size_t vterm, const char* data, size_t size)
{
  for (size_t i = 0; i < size; i++)
		virtualterminal_putchar(vterm, data[i]);
}

void virtualterminal_writestring(size_t vterm, const char* data)
{
  virtualterminal_write(vterm, data, strlen(data));
}
