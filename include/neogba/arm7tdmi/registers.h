#pragma once
#include "neogba/constants.h"
#include "neogba/types.h"

enum neogba_RegisterAlias {
  r0,
  r1,
  r2,
  r3,
  r4,
  r5,
  r6,
  r7,

  pc,
  cpsr,
  r8,
  r9,
  r10,
  r11,
  r12,
  r13,
  r14,

  r8_fiq,
  r9_fiq,
  r10_fiq,
  r11_fiq,
  r12_fiq,
  r13_fiq,
  r14_fiq,
  spsr_fiq,

  r13_svc,
  r14_svc,
  spsr_svc,

  r13_abt,
  r14_abt,
  spsr_abt,

  r13_irq,
  r14_irq,
  spsr_irq,

  r13_und,
  r14_und,
  spsr_und,
};

const u32 neogba_g_map_user[NEOGBA_K_LENGTH_REGISTERS_IN_MODE] = {
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr};
const u32 neogba_g_map_fiq[NEOGBA_K_LENGTH_REGISTERS_IN_MODE] = {
    r0,     r1,      r2,      r3,      r4,      r5,      r6, r7,   r8_fiq,
    r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, pc, cpsr, spsr_fiq};
const u32 neogba_g_map_svc[NEOGBA_K_LENGTH_REGISTERS_IN_MODE] = {
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_svc, r14_svc, pc, cpsr, spsr_svc};
const u32 neogba_g_map_abt[NEOGBA_K_LENGTH_REGISTERS_IN_MODE] = {
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_abt, r14_abt, pc, cpsr, spsr_abt};
const u32 neogba_g_map_irq[NEOGBA_K_LENGTH_REGISTERS_IN_MODE] = {
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_irq, r14_irq, pc, cpsr, spsr_irq};
const u32 neogba_g_map_und[NEOGBA_K_LENGTH_REGISTERS_IN_MODE] = {
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_und, r14_und, pc, cpsr, spsr_und};

enum neogba_RegisterOperation {
  user = 0b10000,
  fiq = 0b10001,
  irq = 0b10010,
  svc = 0b10011,
  abt = 0b10111,
  und = 0b11011,
  sys = 0b11111
};

enum neogba_RegisterFlagMask {
  N = 1U << 31,
  C = 1U << 29,
  V = 1U << 28,
  Z = 1U << 30,
  F = 1U << 6,
  T = 1U << 5,
  I = 1U << 7
};

struct neogba_Registers {
  u32 regs[NEOGBA_K_TOTAL_REGISTERS];
  const u32* map_current;
};

void neogba_Registers_init(struct neogba_Registers* self);

inline u32 neogba_Registers_read_unrestricted(struct neogba_Registers* self, u8 idx) {
  return self->regs[self->map_current[idx]];
}

inline void neogba_Registers_write_unrestricted(struct neogba_Registers* self, u8 idx, u32 val) {
  self->regs[self->map_current[idx]] = val;
}

inline u32 neogba_Registers_read(struct neogba_Registers* self, enum neogba_RegisterAlias idx) {
  return self->regs[idx];
}

inline void neogba_Registers_write(struct neogba_Registers* self, enum neogba_RegisterAlias idx,
                                   u32 val) {
  self->regs[idx] = val;
}

void neogba_Registers_set_mode(struct neogba_Registers* self, enum neogba_RegisterOperation mode);
enum neogba_RegisterOperation neogba_Registers_get_mode(struct neogba_Registers* self);

bool neogba_Registers_is_flag(struct neogba_Registers* self, enum neogba_RegisterFlagMask flag);
void neogba_Registers_set_flag(struct neogba_Registers* self, enum neogba_RegisterFlagMask flag);
void neogba_Registers_clear_flag(struct neogba_Registers* self, enum neogba_RegisterFlagMask flag);

bool neogba_Registers_equals(struct neogba_Registers* self, struct neogba_Registers* other);
