#ifndef __IDT_H
#define __IDT_H

#include <stdint.h>

extern void idt_set_gate(unsigned char num, uint32_t base, uint16_t sel, uint8_t flags);
extern void idt_install(void);

#endif /* __IDT_H */
