#include <idt.h>

#include <irq.h>
#include <isr.h>
#include <system.h>

struct idt_entry
{
  uint16_t base_lo;
  uint16_t sel;        /* Our kernel segment goes here! */
  uint8_t always0;     /* This will ALWAYS be set to 0! */
  uint8_t flags;       /* Set using the above table! */
  uint16_t base_hi;
} __attribute__((packed));

static struct idt_entry idt[256];

extern void idt_load();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt[num].base_lo = (uint16_t) (base & 0xFFFF);
  idt[num].base_hi = (uint16_t) ((base >> 16) & 0xFFFF);

  idt[num].sel = sel;

  idt[num].always0 = 0;

  idt[num].flags = flags;
}

void idt_install(void)
{
  /* Clear out the entire IDT, initializing it to zeros */
  memset(&idt, 0, sizeof(struct idt_entry) * 256);

  /* Add any new ISRs to the IDT here using idt_set_gate */
  isr_install();
  irq_install();

  /* Points the processor's internal register to the new IDT */
	uint32_t idt_address;
	uint32_t idt_ptr[2];

	idt_address = (uint32_t)idt ;
	idt_ptr[0] = (sizeof (struct idt_entry) * 256) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	idt_load(idt_ptr);
}
