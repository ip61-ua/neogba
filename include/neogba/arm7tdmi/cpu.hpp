#pragma once
#include "neogba/types.hpp"

namespace neogba {

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

  enum class cpsr_mode : u8 {
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

  enum arm7tdmi_register : u8 {
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
      {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr, spsr},
      {r0, r1, r2, r3, r4, r5, r6, r7, r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq,
       pc, cpsr, spsr_fiq},
      {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_irq, r14_irq, pc, cpsr, spsr_irq},
      {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_svc, r14_svc, pc, cpsr, spsr_svc},
      {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_abt, r14_abt, pc, cpsr, spsr_abt},
      {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_und, r14_und, pc, cpsr,
       spsr_und}};

  u32 registers[N_REGISTERS];
  u8 active_registers[N_ACTIVE_REGISTERS];

  [[nodiscard]] u32 read_active_register(u8 reg) const;
  void write_active_register(u8 reg, u32 content);

  [[nodiscard]] inline u32 read_pc() const { return this->registers[pc]; }
  inline void write_pc(u32 new_pc) { this->registers[pc] = new_pc; }

  [[nodiscard]] inline u32 read_cpsr() const { return this->registers[cpsr]; }
  inline void write_cpsr(u32 new_cpsr) { this->registers[cpsr] = new_cpsr; }

  [[nodiscard]] bool is_cpsr_bits(u32 mask, u32 bits) const;
  void clear_cpsr_bits(u32 mask);
  void set_cpsr_bits(u32 mask, u32 bits);

  [[nodiscard]] bool is_mode(cpsr_mode mode) const;
  static u8 get_idx_registers_lut_by_mode(cpsr_mode mode);
  void set_mode(cpsr_mode mode, bool update_cpsr = true);

  [[nodiscard]] bool ckeck_arm_condition(u32 inst) const;

  void empty_registers();
  void reset();
};

} // namespace neogba
