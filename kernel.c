#include <idt.h>
#include <terminal.h>
#include <vga.h>

int kernel_main()
{
  terminal_initialize();

  idt_install();
  terminal_writestring("IDT installed\n");

  terminal_writestring("Hello World!\n");
  terminal_newline();
  terminal_writestring("You are welcome");

  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BROWN));
  terminal_setcursor(10,10);
  terminal_writestring(" Fox_Kernel ");
  terminal_setcursor(7,12);
  terminal_writestring(" v0.0.1 C edition \n");

  while(1) {
    asm volatile ("hlt");
  }
  return 0;
}
