#include <isr.h>

#include <idt.h>
#include <stdint.h>
#include <terminal.h>

/* These are function prototypes for all of the exception
*  handlers: The first 32 entries in the IDT are reserved
*  by Intel, and are designed to service exceptions! */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* This is a very repetitive function... it's not hard, it's
*  just annoying. As you can see, we set the first 32 entries
*  in the IDT to the first 32 ISRs. We can't use a for loop
*  for this, because there is no way to get the function names
*  that correspond to that given entry. We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */
void isr_install()
{
  idt_set_gate( 0, (uint32_t)isr0 , 0x08, 0x8E);
  idt_set_gate( 1, (uint32_t)isr1 , 0x08, 0x8E);
  idt_set_gate( 2, (uint32_t)isr2 , 0x08, 0x8E);
  idt_set_gate( 3, (uint32_t)isr3 , 0x08, 0x8E);
  idt_set_gate( 4, (uint32_t)isr4 , 0x08, 0x8E);
  idt_set_gate( 5, (uint32_t)isr5 , 0x08, 0x8E);
  idt_set_gate( 6, (uint32_t)isr6 , 0x08, 0x8E);
  idt_set_gate( 7, (uint32_t)isr7 , 0x08, 0x8E);
  idt_set_gate( 8, (uint32_t)isr8 , 0x08, 0x8E);
  idt_set_gate( 9, (uint32_t)isr9 , 0x08, 0x8E);
  idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
static const char *exception_messages[] =
{
  "Division By Zero Exception",
  "Debug Exception",
  "Non Maskable Interrupt Exception",
  "Breakpoint Exception",
  "Into Detected Overflow Exception",
  "Out of Bounds Exception",
  "Invalid Opcode Exception",
  "No Coprocessor Exception",
  "Double Fault Exception",
  "Coprocessor Segment Overrun Exception",
  "Bad TSS Exception",
  "Segment Not Present Exception",
  "Stack Fault Exception",
  "General Protection Fault Exception",
  "Page Fault Exception",
  "Unknown Interrupt Exception",
  "Coprocessor Fault Exception",
  "Alignment Check Exception (486+)",
  "Machine Check Exception (Pentium/586+)",
  "Reserved 19",
  "Reserved 20",
  "Reserved 21",
  "Reserved 22",
  "Reserved 23",
  "Reserved 24",
  "Reserved 25",
  "Reserved 26",
  "Reserved 27",
  "Reserved 28",
  "Reserved 29",
  "Reserved 30",
  "Reserved 31"
};

void isr0_handler(void) {
  terminal_writestring(exception_messages[0]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr1_handler(void) {
  terminal_writestring(exception_messages[1]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr2_handler(void) {
  terminal_writestring(exception_messages[2]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr3_handler(void) {
  terminal_writestring(exception_messages[3]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr4_handler(void) {
  terminal_writestring(exception_messages[4]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr5_handler(void) {
  terminal_writestring(exception_messages[5]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr6_handler(void) {
  terminal_writestring(exception_messages[6]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr7_handler(void) {
  terminal_writestring(exception_messages[7]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr8_handler(void) {
  terminal_writestring(exception_messages[8]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr9_handler(void) {
  terminal_writestring(exception_messages[9]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr10_handler(void) {
  terminal_writestring(exception_messages[10]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr11_handler(void) {
  terminal_writestring(exception_messages[11]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr12_handler(void) {
  terminal_writestring(exception_messages[12]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr13_handler(void) {
  terminal_writestring(exception_messages[13]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr14_handler(unsigned long cr2) {
  terminal_writestring(exception_messages[14]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr15_handler(void) {
  terminal_writestring(exception_messages[15]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr16_handler(void) {
  terminal_writestring(exception_messages[16]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr17_handler(void) {
  terminal_writestring(exception_messages[17]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr18_handler(void) {
  terminal_writestring(exception_messages[18]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr19_handler(void) {
  terminal_writestring(exception_messages[19]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr20_handler(void) {
  terminal_writestring(exception_messages[20]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr21_handler(void) {
  terminal_writestring(exception_messages[21]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr22_handler(void) {
  terminal_writestring(exception_messages[22]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr23_handler(void) {
  terminal_writestring(exception_messages[23]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr24_handler(void) {
  terminal_writestring(exception_messages[24]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr25_handler(void) {
  terminal_writestring(exception_messages[25]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr26_handler(void) {
  terminal_writestring(exception_messages[26]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr27_handler(void) {
  terminal_writestring(exception_messages[27]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr28_handler(void) {
  terminal_writestring(exception_messages[28]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr29_handler(void) {
  terminal_writestring(exception_messages[29]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr30_handler(void) {
  terminal_writestring(exception_messages[30]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}

void isr31_handler(void) {
  terminal_writestring(exception_messages[31]);
  terminal_writestring(" Exception. System Halted!\n");
  asm volatile ("cli");
  asm volatile ("hlt");
}
