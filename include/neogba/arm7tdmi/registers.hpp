#pragma once
#include "neogba/types.hpp"

namespace neogba::arm7tdmi {

enum RegistersIndex : u8 {
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

enum OperationModeBits : u32 {
  User = 0b10000,
  Fiq = 0b10001,
  Irq = 0b10010,
  Svc = 0b10011,
  Abt = 0b10111,
  Und = 0b11011,
  Sys = 0b11111
};

struct Registers {
public:
  static constexpr u32 mapUser[17]{r0, r1,  r2,  r3,  r4,  r5,  r6, r7,  r8,
                                   r9, r10, r11, r12, r13, r14, pc, cpsr},
      mapFiq[18]{r0,     r1,      r2,      r3,      r4,      r5,      r6, r7,   r8_fiq,
                 r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, pc, cpsr, spsr_fiq},
      mapSvc[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                 r9, r10, r11, r12, r13_svc, r14_svc, pc, cpsr, spsr_svc},
      mapAbt[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                 r9, r10, r11, r12, r13_abt, r14_abt, pc, cpsr, spsr_abt},
      mapIrq[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                 r9, r10, r11, r12, r13_irq, r14_irq, pc, cpsr, spsr_irq},
      mapUnd[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                 r9, r10, r11, r12, r13_und, r14_und, pc, cpsr, spsr_und};

  static constexpr u32 MASK_N{0x80000000}, MASK_Z{0x40000000}, MASK_C{0x20000000},
      MASK_V{0x10000000}, MASK_I{0x80}, MASK_F{0x40}, MASK_T{0x20}, MASK_M{0x1F};

private:
  u32 regs[37];
  const u32* mapCurrent = mapUser;

  inline void set(u32 mask, u32* dst) {
    *dst = mask | *dst;
  }
  inline void clear(u32 mask, u32* dst) {
    *dst = ~mask & *dst;
  }
  inline bool isSet(u32 mask, u32 dst) const {
    return mask & dst;
  }

public:
  inline u32 read(int reg) const {
    return regs[mapCurrent[reg]];
  }

  inline void write(int reg, u32 val) {
    regs[mapCurrent[reg]] = val;
  }

  inline u32 read(enum RegistersIndex idx) const {
    return regs[idx];
  }

  inline void write(enum RegistersIndex idx, u32 val) {
    regs[idx] = val;
  }

  void setUser();
  void setFiq();
  void setAbt();
  void setIrq();
  void setUnd();
  void setSvc();

  inline bool isN() const {
    return isSet(MASK_N, read(RegistersIndex::cpsr));
  }
  inline void setN() {
    set(MASK_N, &regs[RegistersIndex::cpsr]);
  }
  inline void clearN() {
    clear(MASK_N, &regs[RegistersIndex::cpsr]);
  }
  inline bool isZ() const {
    return isSet(MASK_Z, read(RegistersIndex::cpsr));
  }
  inline void setZ() {
    set(MASK_Z, &regs[RegistersIndex::cpsr]);
  }
  inline void clearZ() {
    clear(MASK_Z, &regs[RegistersIndex::cpsr]);
  }
  inline bool isC() const {
    return isSet(MASK_C, read(RegistersIndex::cpsr));
  }
  inline void setC() {
    set(MASK_C, &regs[RegistersIndex::cpsr]);
  }
  inline void clearC() {
    clear(MASK_C, &regs[RegistersIndex::cpsr]);
  }
  inline bool isV() const {
    return isSet(MASK_V, read(RegistersIndex::cpsr));
  }
  inline void setV() {
    set(MASK_V, &regs[RegistersIndex::cpsr]);
  }
  inline void clearV() {
    clear(MASK_V, &regs[RegistersIndex::cpsr]);
  }
  inline bool isI() const {
    return isSet(MASK_I, read(RegistersIndex::cpsr));
  }
  inline void setI() {
    set(MASK_I, &regs[RegistersIndex::cpsr]);
  }
  inline void clearI() {
    clear(MASK_I, &regs[RegistersIndex::cpsr]);
  }
  inline bool isF() const {
    return isSet(MASK_F, read(RegistersIndex::cpsr));
  }
  inline void setF() {
    set(MASK_F, &regs[RegistersIndex::cpsr]);
  }
  inline void clearF() {
    clear(MASK_F, &regs[RegistersIndex::cpsr]);
  }
  inline bool isT() const {
    return isSet(MASK_T, read(RegistersIndex::cpsr));
  }
  inline void setT() {
    set(MASK_T, &regs[RegistersIndex::cpsr]);
  }
  inline void clearT() {
    clear(MASK_T, &regs[RegistersIndex::cpsr]);
  }

  inline OperationModeBits getOperationMode() {
    return OperationModeBits(regs[cpsr] & MASK_M);
  }
};

} // namespace neogba::arm7tdmi
