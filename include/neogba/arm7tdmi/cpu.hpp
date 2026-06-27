#pragma once
#include "neogba/types.hpp"

#define ARM7TDMI_CPU_REGISTERS_TOTAL 36
#define ARM7TDMI_CPU_REGISTERS_TOTAL_REAL ARM7TDMI_CPU_REGISTERS_TOTAL + 1
#define ARM7TDMI_CPU_REGISTERS_ACTIVE 18
#define ARM7TDMI_CPU_REGISTERS_ORDER                                           \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr,   \
      r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, spsr_fiq,   \
      /* */ r13_svc, r14_svc, spsr_svc, /* */ r13_abt, r14_abt, spsr_abt,      \
      /* */ r13_irq, r14_irq, spsr_irq, /* */ r13_und, r14_und, spsr_und,      \
      /* */ spsr__bad

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

enum ARM7TDMI_CPU_Register : u8 { ARM7TDMI_CPU_REGISTERS_ORDER };

#define ARM7TDMI_CPU_REGISTERS_USR                                             \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr
#define ARM7TDMI_CPU_REGISTERS_USR_REAL ARM7TDMI_CPU_REGISTERS_USR, spsr__bad

#define ARM7TDMI_CPU_REGISTERS_FIQ                                             \
  r0, r1, r2, r3, r4, r5, r6, r7, r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq,   \
      r13_fiq, r14_fiq, pc, cpsr
#define ARM7TDMI_CPU_REGISTERS_FIQ_REAL ARM7TDMI_CPU_REGISTERS_FIQ, spsr_fiq

#define ARM7TDMI_CPU_REGISTERS_IRQ                                             \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_irq, r14_irq, pc, \
      cpsr
#define ARM7TDMI_CPU_REGISTERS_IRQ_REAL ARM7TDMI_CPU_REGISTERS_IRQ, spsr_irq

#define ARM7TDMI_CPU_REGISTERS_SVC                                             \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_svc, r14_svc, pc, \
      cpsr
#define ARM7TDMI_CPU_REGISTERS_SVC_REAL ARM7TDMI_CPU_REGISTERS_SVC, spsr_svc

#define ARM7TDMI_CPU_REGISTERS_ABT                                             \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_abt, r14_abt, pc, \
      cpsr
#define ARM7TDMI_CPU_REGISTERS_ABT_REAL ARM7TDMI_CPU_REGISTERS_ABT, spsr_abt
#define ARM7TDMI_CPU_REGISTERS_UND                                             \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_abt, r14_und, pc, \
      cpsr
#define ARM7TDMI_CPU_REGISTERS_UND_REAL ARM7TDMI_CPU_REGISTERS_UND, spsr_und

#define ARM7TDMI_CPU_REGISTERS_CREATE_STUB(                                    \
    expected, r0_, r1_, r2_, r3_, r4_, r5_, r6_, r7_, r8_, r9_, r10_, r11_,    \
    r12_, r13_, r14_, pc_, cpsr_, r8_fiq_, r9_fiq_, r10_fiq_, r11_fiq_,        \
    r12_fiq_, r13_fiq_, r14_fiq_, spsr_fiq_, r13_svc_, r14_svc_, spsr_svc_,    \
    r13_abt_, r14_abt_, spsr_abt_, r13_irq_, r14_irq_, spsr_irq_, r13_und_,    \
    r14_und_, spsr_und_, spsr__bad_)                                           \
  expected[r0] = r0_;                                                          \
  expected[r1] = r1_;                                                          \
  expected[r2] = r2_;                                                          \
  expected[r3] = r3_;                                                          \
  expected[r4] = r4_;                                                          \
  expected[r5] = r5_;                                                          \
  expected[r6] = r6_;                                                          \
  expected[r7] = r7_;                                                          \
  expected[r8] = r8_;                                                          \
  expected[r9] = r9_;                                                          \
  expected[r10] = r10_;                                                        \
  expected[r11] = r11_;                                                        \
  expected[r12] = r12_;                                                        \
  expected[r13] = r13_;                                                        \
  expected[r14] = r14_;                                                        \
  expected[pc] = pc_;                                                          \
  expected[cpsr] = cpsr_;                                                      \
  expected[r8_fiq] = r8_fiq_;                                                  \
  expected[r9_fiq] = r9_fiq_;                                                  \
  expected[r10_fiq] = r10_fiq_;                                                \
  expected[r11_fiq] = r11_fiq_;                                                \
  expected[r12_fiq] = r12_fiq_;                                                \
  expected[r13_fiq] = r13_fiq_;                                                \
  expected[r14_fiq] = r14_fiq_;                                                \
  expected[spsr_fiq] = spsr_fiq_;                                              \
  expected[r13_svc] = r13_svc_;                                                \
  expected[r14_svc] = r14_svc_;                                                \
  expected[spsr_svc] = spsr_svc_;                                              \
  expected[r13_abt] = r13_abt_;                                                \
  expected[r14_abt] = r14_abt_;                                                \
  expected[spsr_abt] = spsr_abt_;                                              \
  expected[r13_irq] = r13_irq_;                                                \
  expected[r14_irq] = r14_irq_;                                                \
  expected[spsr_irq] = spsr_irq_;                                              \
  expected[r13_und] = r13_und_;                                                \
  expected[r14_und] = r14_und_;                                                \
  expected[spsr_und] = spsr_und_;                                              \
  expected[spsr__bad] = spsr__bad_;

struct ARM7TDMI_CPU {
  u32 registers[ARM7TDMI_CPU_REGISTERS_TOTAL_REAL];
  u8 active_registers[ARM7TDMI_CPU_REGISTERS_ACTIVE];
  static constexpr u8 REGISTERS_LUT[6][ARM7TDMI_CPU_REGISTERS_ACTIVE] = {
      {ARM7TDMI_CPU_REGISTERS_USR_REAL}, {ARM7TDMI_CPU_REGISTERS_FIQ_REAL},
      {ARM7TDMI_CPU_REGISTERS_IRQ_REAL}, {ARM7TDMI_CPU_REGISTERS_SVC_REAL},
      {ARM7TDMI_CPU_REGISTERS_ABT_REAL}, {ARM7TDMI_CPU_REGISTERS_UND_REAL}};

  [[nodiscard]] u32 read_active_register(u8 reg) const;
  void write_active_register(u8 reg, u32 content);

  [[nodiscard]] inline u32 read_pc() const { return this->registers[pc]; }
  inline void write_pc(u32 new_pc) { this->registers[pc] = new_pc; }

  [[nodiscard]] inline u32 read_cpsr() const { return this->registers[cpsr]; }
  inline void write_cpsr(u32 new_cpsr) { this->registers[cpsr] = new_cpsr; }

  [[nodiscard]] inline u32 read_spsr() const {
    return this->registers[active_registers[17]];
  }
  inline void write_spsr(u32 new_spsr) {
    this->registers[active_registers[17]] = new_spsr;
  }

  [[nodiscard]] bool is_cpsr_bits(u32 mask, u32 bits) const;
  void clear_cpsr_bits(u32 mask);
  void set_cpsr_bits(u32 mask, u32 bits);

  [[nodiscard]] bool is_mode(u8 mode) const;
  static u8 get_idx_registers_lut_by_mode(u8 mode);
  void set_mode(u8 mode, bool update_cpsr = true);

  void empty_registers();
  void reset();
};
