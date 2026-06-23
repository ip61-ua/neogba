#pragma once
#include "neogba/types.hpp"

#define ARM7TDMI_CPU_TOTAL_REGISTERS 36
#define ARM7TDMI_CPU_ORDER_REGISTERS                                           \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr,   \
      r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, spsr_fiq,   \
      /* */ r13_svc, r14_svc, spsr_svc, /* */ r13_abt, r14_abt, spsr_abt,      \
      /* */ r13_irq, r14_irq, spsr_irq, /* */ r13_und, r14_und, spsr_und

#define ARM7TDMI_CPU_MASK_NEGATIVE /*  */ (1u << 31)
#define ARM7TDMI_CPU_MASK_ZERO /*      */ (1u << 30)
#define ARM7TDMI_CPU_MASK_CARRY /*     */ (1u << 29)
#define ARM7TDMI_CPU_MASK_OVERFLOW /*  */ (1u << 28)
#define ARM7TDMI_CPU_MASK_IRQDISABLE /**/ (1u << 7)
#define ARM7TDMI_CPU_MASK_FIQDISABLE /**/ (1u << 6)
#define ARM7TDMI_CPU_MASK_THUMB_BIT /* */ (1u << 5)
#define ARM7TDMI_CPU_MASK_MODE_BITS /* */ ((1u << 5) - 1)

#define ARM7TDMI_CPU_MODE_USR 0b10000
#define ARM7TDMI_CPU_MODE_FIQ 0b10001
#define ARM7TDMI_CPU_MODE_IRQ 0b10010
#define ARM7TDMI_CPU_MODE_SVC 0b10011
#define ARM7TDMI_CPU_MODE_ABT 0b10111
#define ARM7TDMI_CPU_MODE_UND 0b11011
#define ARM7TDMI_CPU_MODE_SYS 0b11111

#define ARM7TDMI_CPU_EXCEPTION_RESET /*    */ 0x00000000
#define ARM7TDMI_CPU_EXCEPTION_UNDEFINS /* */ 0x00000004
#define ARM7TDMI_CPU_EXCEPTION_SWINT /*    */ 0x00000008
#define ARM7TDMI_CPU_EXCEPTION_PREFETABT /**/ 0x0000000c
#define ARM7TDMI_CPU_EXCEPTION_DATAABT /*  */ 0x00000010
#define ARM7TDMI_CPU_EXCEPTION_RESERVED /* */ 0x00000014
#define ARM7TDMI_CPU_EXCEPTION_IRQ /*      */ 0x00000018
#define ARM7TDMI_CPU_EXCEPTION_FIQ /*      */ 0x0000001c

enum Register { ARM7TDMI_CPU_ORDER_REGISTERS };

struct ARMTDMI7_CPU {
  u32 registers[ARM7TDMI_CPU_TOTAL_REGISTERS];

  u8 convert_mode_register(u8 idx);
  bool is_thumb();
  bool is_mode(u8 mode);

  void reset();
};
