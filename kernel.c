#include <idt.h>
#include <terminal.h>
#include <virtualterminal.h>
#include <vga.h>

int kernel_main()
{
  virtualterminal_initialize();
  virtualterminal_writestring(1, "virtual terminals initialized\n");

  idt_install();
  virtualterminal_writestring(1, "IDT installed\n");

  virtualterminal_writestring(0, "Hello World!\n");
  virtualterminal_newline(0);
  virtualterminal_writestring(0, "You are welcome");


  virtualterminal_setcolor(0, vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BROWN));

  virtualterminal_setcursor(0, 10,9);
  virtualterminal_writestring(0, "                  ");
  virtualterminal_setcursor(0, 10,10);
  virtualterminal_writestring(0, "    Fox_Kernel    ");
  virtualterminal_setcursor(0, 10,11);
  virtualterminal_writestring(0, "                  ");
  virtualterminal_setcursor(0, 10,12);
  virtualterminal_writestring(0, " v0.0.1 C edition ");
  virtualterminal_setcursor(0, 10,13);
  virtualterminal_writestring(0, "                  ");
  virtualterminal_newline(0);

  while(1) {
    asm volatile ("hlt");
  }
  return 0;
}
