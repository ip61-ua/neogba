#pragma once
#include "neogba/types.hpp"

namespace neogba {

#define ARM7TDMI_REGISTERS_USR                                                                     \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr, spsr
#define ARM7TDMI_REGISTERS_FIQ                                                                     \
  r0, r1, r2, r3, r4, r5, r6, r7, r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, pc, \
      cpsr, spsr_fiq
#define ARM7TDMI_REGISTERS_IRQ                                                                     \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_irq, r14_irq, pc, cpsr, spsr_irq
#define ARM7TDMI_REGISTERS_SVC                                                                     \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_svc, r14_svc, pc, cpsr, spsr_svc
#define ARM7TDMI_REGISTERS_ABT                                                                     \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_abt, r14_abt, pc, cpsr, spsr_abt
#define ARM7TDMI_REGISTERS_UND                                                                     \
  r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_und, r14_und, pc, cpsr, spsr_und

struct arm7tdmi {
  enum cpsr_flag : u32 {
    /// @brief Negative (N)
    N = 1u << 31,
    /// @brief Zero (Z)
    Z = 1u << 30,
    /// @brief Carry (C)
    C = 1u << 29,
    /// @brief Overflow (V)
    V = 1u << 28,
    /// @brief IRQ Disable (I)
    I = 1u << 7,
    /// @brief FIQ Disable (F)
    F = 1u << 6,
    /// @brief Thumb State (T)
    T = 1u << 5,
    /// @brief Mode Bits (M)
    M = 0x1fu
  };

  enum class exception : u32 {
    RESET = /*    */ 0x00000000,
    UNDEFINS = /* */ 0x00000004,
    SWINT = /*    */ 0x00000008,
    PREFETABT = /**/ 0x0000000c,
    DATAABT = /*  */ 0x00000010,
    RESERVED = /* */ 0x00000014,
    IRQ = /*      */ 0x00000018,
    FIQ = /*      */ 0x0000001c
  };

  enum cpsr_mode : u8 {
    USR = 0b10000,
    FIQ = 0b10001,
    IRQ = 0b10010,
    SVC = 0b10011,
    ABT = 0b10111,
    UND = 0b11011,
    SYS = 0b11111,
  };

  enum class registers_preset_idx : u8 {
    USR = 0,
    FIQ = 1,
    IRQ = 2,
    SVC = 3,
    ABT = 4,
    UND = 5,
    SYS = 0,
  };

  enum arm_register : u8 {
    // clang-format off
      r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr, spsr,
      r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, spsr_fiq,
      r13_svc, r14_svc, spsr_svc,
      r13_abt, r14_abt, spsr_abt,
      r13_irq, r14_irq, spsr_irq,
      r13_und, r14_und, spsr_und,
    // clang-format on
  };

  static constexpr u8 N_ACTIVE_REGISTERS = 18, N_REGISTERS = 38;
  static constexpr u8 REGISTERS_PRESET[6][N_ACTIVE_REGISTERS] = {
      {ARM7TDMI_REGISTERS_USR}, {ARM7TDMI_REGISTERS_FIQ}, {ARM7TDMI_REGISTERS_IRQ},
      {ARM7TDMI_REGISTERS_SVC}, {ARM7TDMI_REGISTERS_ABT}, {ARM7TDMI_REGISTERS_UND}};

  u32 registers[N_REGISTERS];
  u8 active_registers[N_ACTIVE_REGISTERS];

  [[nodiscard]] inline u32 read_active_register(u8 reg) const {
    return registers[active_registers[reg]];
  }
  inline void write_active_register(u8 reg, u32 content) {
    registers[active_registers[reg]] = content;
  }

  [[nodiscard]] inline u32 read_pc() const { return registers[pc]; }
  inline void write_pc(u32 new_pc) { registers[pc] = new_pc; }

  [[nodiscard]] inline u32 read_cpsr() const { return registers[cpsr]; }
  inline void write_cpsr(u32 new_cpsr) { registers[cpsr] = new_cpsr; }

  [[nodiscard]] inline bool is_cpsr(u32 mask, u32 bits) const {
    return (registers[cpsr] & mask) == bits;
  }
  inline void clear_cpsr(u32 mask) { registers[cpsr] &= ~mask; }
  void set_cpsr(u32 mask, u32 bits);

  [[nodiscard]] inline bool is_mode(cpsr_mode mode) const { return (registers[cpsr] & M) == mode; }
  void set_mode(cpsr_mode mode, bool update_cpsr = true);

  static u8 get_idx_registers_preset_by_mode(cpsr_mode mode);
  [[nodiscard]] bool ckeck_arm_condition(u32 inst) const;

  void empty_registers();
  void reset();
};

} // namespace neogba
