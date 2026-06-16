#include "neogba/types.hpp"

#define K_CPU_TOTAL_REGISTERS 36
#define K_CPU_ORDER_REGISTERS                                                  \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr,   \
      r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, spsr_fiq,   \
      r13_svc, r14_svc, spsr_svc, /* */ r13_abt, r14_abt, spsr_abt,            \
      /* */ r13_irq, r14_irq, spsr_irq, /* */ r13_und, r14_und, spsr_und

#define K_CPU_MASK_NEGATIVE /*     */ (1u << 31)
#define K_CPU_MASK_ZERO /*         */ (1u << 30)
#define K_CPU_MASK_CARRY /*        */ (1u << 29)
#define K_CPU_MASK_OVERFLOW /*     */ (1u << 28)
#define K_CPU_MASK_IRQ_DISABLE /*  */ (1u << 7)
#define K_CPU_MASK_FIQ_DISABLE /*  */ (1u << 6)
#define K_CPU_MASK_STATE_BIT /*    */ (1u << 5)
#define K_CPU_MASK_MODE_BITS /*    */ ((1u << 5) - 1)

#define K_CPU_MODE_USR 0b10000
#define K_CPU_MODE_FIQ 0b10001
#define K_CPU_MODE_IRQ 0b10010
#define K_CPU_MODE_SVC 0b10011
#define K_CPU_MODE_ABT 0b10111
#define K_CPU_MODE_UND 0b11011
#define K_CPU_MODE_SYS 0b11111

enum Register { K_CPU_ORDER_REGISTERS };

struct CPU {
  u32 registers[K_CPU_TOTAL_REGISTERS];
};
