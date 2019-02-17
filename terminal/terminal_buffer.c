#include <terminal_buffer.h>

#include <vga.h>
#include <virtualterminal.h>

static uint16_t buffers[VIRTUALTERMINALS_LENGTH][VGA_LENGTH];

uint16_t* get_buffer_ptr(size_t buffer)
{
  return buffers[buffer];
}
