#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stddef.h>
#include <stdint.h>

extern void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);
extern void* memset(void* bufptr, int value, size_t size);

extern size_t strlen(const char* str);

//extern unsigned char inportb (size_t _port);
extern void outb (uint16_t port, uint8_t val);

#endif /* __SYSTEM_H */
