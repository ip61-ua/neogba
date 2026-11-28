#pragma once
#include "neogba/fields.hpp"
#include "neogba/memory/bus.hpp"
#include <array>

namespace neogba {

enum arm7tdmi_register : u8 {
  // clang-format off
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr, //
    r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, spsr_fiq,//
    r13_svc, r14_svc, spsr_svc, //
    r13_abt, r14_abt, spsr_abt, //
    r13_irq, r14_irq, spsr_irq, //
    r13_und, r14_und, spsr_und  //
  // clang-format on
};

struct arm7tdmi {
  /** @brief Negative (N) */
  using N = field_bin<31>;
  // static constexpr u32 N_SHIFT{31}, N{1u << N_SHIFT};

  /** @brief Zero (Z) */
  using Z = field_bin<30>;
  // static constexpr u32 Z_SHIFT{30}, Z{1u << Z_SHIFT};

  /** @brief Carry (C) */
  using C = field_bin<29>;
  // static constexpr u32 C_SHIFT{29}, C{1u << C_SHIFT};

  /** @brief Overflow (V) */
  using V = field_bin<28>;
  // static constexpr u32 V_SHIFT{28}, V{1u << V_SHIFT};

  /** @brief IRQ Disable (I) */
  using I = field_bin<7>;
  // static constexpr u32 I_SHIFT{7}, I{1u << I_SHIFT};

  /** @brief FIQ Disable (F) */
  using F = field_bin<6>;
  // static constexpr u32 F_SHIFT{6}, F{1u << F_SHIFT};

  /** @brief Thumb State (T) */
  using T = field_bin<5>;
  // static constexpr u32 T_SHIFT{5}, T{1u << T_SHIFT};

  /** @brief Mode Bits (M) */
  using M = field<u32, u8, 0, 0x1fu>;
  // static constexpr u32 M{0x1fu};

  struct exceptions {
    inline static constexpr u32 reset /*     */ {0x00000000u};
    inline static constexpr u32 undefins /*  */ {0x00000004u};
    inline static constexpr u32 swint /*     */ {0x00000008u};
    inline static constexpr u32 prefetabt /* */ {0x0000000cu};
    inline static constexpr u32 dataabt /*   */ {0x00000010u};
    inline static constexpr u32 reserved /*  */ {0x00000014u};
    inline static constexpr u32 irq /*       */ {0x00000018u};
    inline static constexpr u32 fiq /*       */ {0x0000001cu};

  private:
    exceptions(const exceptions&) = delete;
    exceptions(exceptions&&) = delete;
    exceptions& operator=(const exceptions&) = delete;
    exceptions& operator=(exceptions&&) = delete;
  };

  struct modes {
    inline static constexpr u8 usr{0b10000u};
    inline static constexpr u8 fiq{0b10001u};
    inline static constexpr u8 irq{0b10010u};
    inline static constexpr u8 svc{0b10011u};
    inline static constexpr u8 abt{0b10111u};
    inline static constexpr u8 und{0b11011u};
    inline static constexpr u8 sys{0b11111u};

  private:
    modes(const modes&) = delete;
    modes(modes&&) = delete;
    modes& operator=(const modes&) = delete;
    modes& operator=(modes&&) = delete;
  };

  struct registers_preset {
    inline static constexpr u8 usr{0};
    inline static constexpr u8 fiq{1};
    inline static constexpr u8 irq{2};
    inline static constexpr u8 svc{3};
    inline static constexpr u8 abt{4};
    inline static constexpr u8 und{5};
    inline static constexpr u8 sys{0};

  private:
    registers_preset(const registers_preset&) = delete;
    registers_preset(registers_preset&&) = delete;
    registers_preset& operator=(const registers_preset&) = delete;
    registers_preset& operator=(registers_preset&&) = delete;
  };

  static constexpr u8 N_ACTIVE_REGISTERS{18}, N_REGISTERS{37};
  static constexpr u8 spsr{17};

  static constexpr std::array<u8, N_ACTIVE_REGISTERS> REGISTERS_USR{
      {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr}},
      REGISTERS_FIQ{{r0, r1, r2, r3, r4, r5, r6, r7, r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq,
                     r13_fiq, r14_fiq, pc, cpsr, spsr_fiq}},
      REGISTERS_IRQ{{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_irq, r14_irq, pc,
                     cpsr, spsr_irq}},
      REGISTERS_SVC{{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_svc, r14_svc, pc,
                     cpsr, spsr_svc}},
      REGISTERS_ABT{{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_abt, r14_abt, pc,
                     cpsr, spsr_abt}},
      REGISTERS_UND{{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13_und, r14_und, pc,
                     cpsr, spsr_und}};

  static constexpr std::array<std::array<u8, N_ACTIVE_REGISTERS>, 6> REGISTERS_PRESET{
      {{REGISTERS_USR},
       {REGISTERS_FIQ},
       {REGISTERS_IRQ},
       {REGISTERS_SVC},
       {REGISTERS_ABT},
       {REGISTERS_UND}}};

  std::array<u32, N_REGISTERS> registers;
  std::array<u8, N_ACTIVE_REGISTERS> active_registers;

  u32 instruction_size{32}, instruction_incrementator{4};

  void (*execute)(arm7tdmi& cpu, u32 inst){nullptr};

  memory_bus* bus{nullptr};

  inline auto set_bus(memory_bus* busptr) { bus = busptr; }

  [[nodiscard]] inline auto read_raw_register(u8 reg) const -> u32 { return registers[reg]; }
  inline auto write_raw_register(u8 reg, u32 value) { registers[reg] = value; }

  [[nodiscard]] inline auto read_pc() const -> u32 {
    return registers[pc] + (instruction_incrementator << 1);
  }
  inline auto write_pc(u32 new_pc) { registers[pc] = new_pc & ~(instruction_incrementator - 1); }

  [[nodiscard]] inline auto read_active_register(u8 reg) const -> u32 {
    return reg == pc ? read_pc() : registers[active_registers[reg]];
  }
  inline auto write_active_register(u8 reg, u32 value) {
    if (reg == pc)
      write_pc(value);
    else
      registers[active_registers[reg]] = value;
  }

  [[nodiscard]] inline auto read_relative_register(u8 reg, u8 bank_preset) const -> u32 {
    return reg == pc ? read_pc() : registers[REGISTERS_PRESET[bank_preset][reg]];
  }
  inline auto write_relative_register(u8 reg, u32 value, u8 bank_preset) {
    if (reg == pc)
      write_pc(value);
    else
      registers[REGISTERS_PRESET[bank_preset][reg]] = value;
  }

  [[nodiscard]] inline auto read_cpsr() const { return registers[cpsr]; }
  inline auto write_cpsr(u32 new_cpsr) { registers[cpsr] = new_cpsr; }
  [[nodiscard]] inline auto is_cpsr(u32 mask, u32 bits) const {
    return (registers[cpsr] & mask) == bits;
  }
  inline auto clear_cpsr(u32 mask) { registers[cpsr] &= ~mask; }
  inline auto set_cpsr(u32 mask, u32 bits) { registers[cpsr] = (registers[cpsr] & ~mask) | bits; }

  [[nodiscard]] inline auto read_spsr() const { return read_active_register(spsr); }
  inline auto write_spsr(u32 new_spsr) { write_active_register(spsr, new_spsr); }

  [[nodiscard]] inline auto is_mode(u8 mode) const { return M::h(registers[cpsr]) == mode; }
  auto set_mode(u8 mode, bool update_cpsr = true) -> void;

  inline auto ensure_mode() { set_mode(read_cpsr(), false); }

  inline auto restore_cpsr() {
    write_cpsr(read_spsr());
    ensure_mode();
  }

  [[nodiscard]] inline static auto get_idx_registers_preset_by_mode(u8 mode) -> u8 {
    return ((mode & 0b11) + ((mode & 0b1100) >> 2)) % 6;
  }

  [[nodiscard]] auto ckeck_arm_condition(u32 instruction) const -> bool;

  auto empty_registers() -> void;

  auto reset() -> void;

  auto set_arm_mode() -> void;
  auto set_thumb_mode() -> void;
  auto step() -> void;
};

} // namespace neogba
