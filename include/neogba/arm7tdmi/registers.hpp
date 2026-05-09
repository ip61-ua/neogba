#pragma once
#include "neogba/types.hpp"

namespace neogba::arm7 {

struct Registers {
  enum IndexAlias : u8 {
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

  enum OperationMode : u32 {
    user = 0b10000,
    fiq = 0b10001,
    irq = 0b10010,
    svc = 0b10011,
    abt = 0b10111,
    und = 0b11011,
    sys = 0b11111
  };

  enum FlagMask : u32 {
    N = 1U << 31,
    C = 1U << 29,
    V = 1U << 28,
    Z = 1U << 30,
    F = 1U << 6,
    T = 1U << 5,
    I = 1U << 7
  };

  static constexpr u32 TOTAL_REGISTERS{37}, MASK_MODE{0x1F},
      MAP_USER[17]{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr},
      MAP_FIQ[18]{r0,     r1,      r2,      r3,      r4,      r5,      r6, r7,   r8_fiq,
                  r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, pc, cpsr, spsr_fiq},
      MAP_SVC[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                  r9, r10, r11, r12, r13_svc, r14_svc, pc, cpsr, spsr_svc},
      MAP_ABT[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                  r9, r10, r11, r12, r13_abt, r14_abt, pc, cpsr, spsr_abt},
      MAP_IRQ[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                  r9, r10, r11, r12, r13_irq, r14_irq, pc, cpsr, spsr_irq},
      MAP_UND[18]{r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                  r9, r10, r11, r12, r13_und, r14_und, pc, cpsr, spsr_und};

private:
  u32 regs_[TOTAL_REGISTERS]{};
  const u32* map_current_ = MAP_USER;

public:
  Registers() = default;
  Registers(Registers const& registers) = default;

  [[nodiscard]] inline u32 read(u8 reg) const {
    return regs_[map_current_[reg]];
  }
  inline void write(u8 reg, u32 val) {
    regs_[map_current_[reg]] = val;
  }

  [[nodiscard]] inline u32 read(IndexAlias idx) const {
    return regs_[idx];
  }
  inline void write(IndexAlias idx, u32 val) {
    regs_[idx] = val;
  }

  void setOperationMode(OperationMode mode);
  [[nodiscard]] OperationMode getOperationMode() const;

  [[nodiscard]] bool isFlag(FlagMask flag) const;
  void setFlag(FlagMask flag);
  void clearFlag(FlagMask flag);

  [[nodiscard]] bool equals(Registers const& other) const;
  [[nodiscard]] inline bool operator==(Registers const& other) const {
    return equals(other);
  }
};
} // namespace neogba::arm7
