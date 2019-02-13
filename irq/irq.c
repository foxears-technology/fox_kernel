#include <irq.h>

#include <idt.h>
#include <system.h>
#include <terminal.h>

/* These are own ISRs that point to our special IRQ handler
*  instead of the regular 'fault_handler' function */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void)
{
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x00);
  outb(0xA1, 0x00);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install()
{
  irq_remap();

  idt_set_gate(32, (uint32_t)irq0 , 0x08, 0x8E);
  idt_set_gate(33, (uint32_t)irq1 , 0x08, 0x8E);
  idt_set_gate(34, (uint32_t)irq2 , 0x08, 0x8E);
  idt_set_gate(35, (uint32_t)irq3 , 0x08, 0x8E);
  idt_set_gate(36, (uint32_t)irq4 , 0x08, 0x8E);
  idt_set_gate(37, (uint32_t)irq5 , 0x08, 0x8E);
  idt_set_gate(38, (uint32_t)irq6 , 0x08, 0x8E);
  idt_set_gate(39, (uint32_t)irq7 , 0x08, 0x8E);
  idt_set_gate(40, (uint32_t)irq8 , 0x08, 0x8E);
  idt_set_gate(41, (uint32_t)irq9 , 0x08, 0x8E);
  idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
  idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
  idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
  idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
  idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
  idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
}

void irq0_handler(void) {
  terminal_writestring("lolo");
  outb(0x20, 0x20); //EOI
}

void irq1_handler(void) {
  terminal_writestring("lolo");
  outb(0x20, 0x20); //EOI
}

void irq2_handler(void) {
  terminal_writestring("lolo");
  outb(0x20, 0x20); //EOI
}

void irq3_handler(void) {
  outb(0x20, 0x20); //EOI
}

void irq4_handler(void) {
  outb(0x20, 0x20); //EOI
}

void irq5_handler(void) {
  outb(0x20, 0x20); //EOI
}

void irq6_handler(void) {
  outb(0x20, 0x20); //EOI
}

void irq7_handler(void) {
  outb(0x20, 0x20); //EOI
}

void irq8_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq9_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq10_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq11_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq12_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq13_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq14_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}

void irq15_handler(void) {
  outb(0xA0, 0x20);
  outb(0x20, 0x20); //EOI
}
