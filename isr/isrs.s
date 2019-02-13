/*
  In just a few pages in this tutorial, we will add our Interrupt
  Service Routines (ISRs) right here!
*/
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

.global isr0_handler
.global isr1_handler
.global isr2_handler
.global isr3_handler
.global isr4_handler
.global isr5_handler
.global isr6_handler
.global isr7_handler
.global isr8_handler
.global isr9_handler
.global isr10_handler
.global isr11_handler
.global isr12_handler
.global isr13_handler
.global isr14_handler
.global isr15_handler
.global isr16_handler
.global isr17_handler
.global isr18_handler
.global isr19_handler
.global isr20_handler
.global isr21_handler
.global isr22_handler
.global isr23_handler
.global isr24_handler
.global isr25_handler
.global isr26_handler
.global isr27_handler
.global isr28_handler
.global isr29_handler
.global isr30_handler
.global isr31_handler

.extern isr0_handler
.extern isr1_handler
.extern isr2_handler
.extern isr3_handler
.extern isr4_handler
.extern isr5_handler
.extern isr6_handler
.extern isr7_handler
.extern isr8_handler
.extern isr9_handler
.extern isr10_handler
.extern isr11_handler
.extern isr12_handler
.extern isr13_handler
.extern isr14_handler
.extern isr15_handler
.extern isr16_handler
.extern isr17_handler
.extern isr18_handler
.extern isr19_handler
.extern isr20_handler
.extern isr21_handler
.extern isr22_handler
.extern isr23_handler
.extern isr24_handler
.extern isr25_handler
.extern isr26_handler
.extern isr27_handler
.extern isr28_handler
.extern isr29_handler
.extern isr30_handler
.extern isr31_handler

#-------------------------------------------------------------------------------

.align 4

#  0: Divide By Zero Exception
isr0:
  pusha
  cld
  call isr0_handler
  popa
  iret

#  1: Debug Exception
isr1:
  pusha
  cld
  call isr1_handler
  popa
  iret

#  2: Non Maskable Interrupt Exception
isr2:
  pusha
  cld
  call isr2_handler
  popa
  iret

#  3: Breakpoint Exception
isr3:
  pusha
  cld
  call isr3_handler
  popa
  iret

#  4: Into Detected Overflow Exception
isr4:
  pusha
  cld
  call isr4_handler
  popa
  iret

#  5: Out of Bounds Exception
isr5:
  pusha
  cld
  call isr5_handler
  popa
  iret

#  6: Invalid Opcode Exception
isr6:
  pusha
  cld
  call isr6_handler
  popa
  iret

#  7: No Coprocessor Exception
isr7:
  pusha
  cld
  call isr7_handler
  popa
  iret

#  8: Double Fault Exception (With Error Code!)
isr8:
  cli
  call isr8_handler
  popa
  iret

#  9: Coprocessor Segment Overrun Exception
isr9:
  pusha
  cld
  call isr9_handler
  popa
  iret

# 10: Bad TSS Exception
isr10:
  pusha
  cld
  call isr10_handler
  popa
  iret

# 11: Segment Not Present Exception
isr11:
  pusha
  cld
  call isr11_handler
  popa
  iret

# 12: Stack Fault Exception
isr12:
  pusha
  cld
  call isr12_handler
  popa
  iret

# 13: General Protection Fault Exception
isr13:
  pusha
  cld
  call isr13_handler
  popa
  iret

# 14: Page Fault Exception
isr14:
  pusha
  cld

  mov %cr2, %eax
  push %eax

  call isr14_handler

  pop %eax

  popa
  iret

# 15: Unknown Interrupt Exception
isr15:
  pusha
  cld
  call isr15_handler
  popa
  iret

# 16: Coprocessor Fault Exception
isr16:
  pusha
  cld
  call isr16_handler
  popa
  iret

# 17: Alignment Check Exception (486+)
isr17:
  pusha
  cld
  call isr17_handler
  popa
  iret

# 18: Machine Check Exception (Pentium/586+)
isr18:
  pusha
  cld
  call isr18_handler
  popa
  iret

# 19: Reserved Exceptions
isr19:
  pusha
  cld
  call isr19_handler
  popa
  iret

# 20: Reserved Exceptions
isr20:
  pusha
  cld
  call isr20_handler
  popa
  iret

# 21: Reserved Exceptions
isr21:
  pusha
  cld
  call isr21_handler
  popa
  iret

# 22: Reserved Exceptions
isr22:
  pusha
  cld
  call isr22_handler
  popa
  iret

# 23: Reserved Exceptions
isr23:
  pusha
  cld
  call isr23_handler
  popa
  iret

# 24: Reserved Exceptions
isr24:
  pusha
  cld
  call isr24_handler
  popa
  iret

# 25: Reserved Exceptions
isr25:
  pusha
  cld
  call isr25_handler
  popa
  iret

# 26: Reserved Exceptions
isr26:
  pusha
  cld
  call isr26_handler
  popa
  iret

# 27: Reserved Exceptions
isr27:
  pusha
  cld
  call isr27_handler
  popa
  iret

# 28: Reserved Exceptions
isr28:
  pusha
  cld
  call isr28_handler
  popa
  iret

# 29: Reserved Exceptions
isr29:
  pusha
  cld
  call isr29_handler
  popa
  iret

# 30: Reserved Exceptions
isr30:
  pusha
  cld
  call isr30_handler
  popa
  iret

# 31: Reserved Exceptions
isr31:
  pusha
  cld
  call isr31_handler
  popa
  iret
