#include <idt.h>
#include <terminal.h>
#include <virtualterminal.h>
#include <vga.h>

int kernel_main()
{
  virtualterminal_initialize();
  terminal_initialize();

  idt_install();
  virtualterminal_writestring(0, "IDT installed\n");
  virtualterminal_display(0);

  virtualterminal_writestring(0, "Hello World!\n");
  virtualterminal_newline(0);
  virtualterminal_writestring(0, "You are welcome");
  virtualterminal_display(0);

  virtualterminal_setcolor(0, vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BROWN));
  virtualterminal_setcursor(0, 10,10);
  virtualterminal_writestring(0, " Fox_Kernel ");
  virtualterminal_setcursor(0, 7,12);
  virtualterminal_writestring(0, " v0.0.1 C edition \n");
  virtualterminal_display(0);

  while(1) {
    asm volatile ("hlt");
  }
  return 0;
}
