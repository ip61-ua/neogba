#pragma once
#include "neogba/memory/bus.hpp"
#include <array>

namespace neogba {

enum arm7tdmi_register : u8 {

  // clang-format off
    r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, pc, cpsr,
    /**/
    r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq, r13_fiq, r14_fiq, spsr_fiq,
    /**/
    r13_svc, r14_svc, spsr_svc,
    /**/ 
    r13_abt, r14_abt, spsr_abt,
    /**/ 
    r13_irq, r14_irq, spsr_irq,
    /**/ 
    r13_und, r14_und, spsr_und
  // clang-format on

};

struct arm7tdmi {
  static constexpr u32

      /** @brief Negative (N) */
      N_SHIFT{31},
      N{1u << N_SHIFT},

      /** @brief Zero (Z) */
      Z_SHIFT{30}, Z{1u << Z_SHIFT},

      /** @brief Carry (C) */
      C_SHIFT{29}, C{1u << C_SHIFT},

      /** @brief Overflow (V) */
      V_SHIFT{28}, V{1u << V_SHIFT},

      /** @brief IRQ Disable (I) */
      I_SHIFT{7}, I{1u << I_SHIFT},

      /** @brief FIQ Disable (F) */
      F_SHIFT{6}, F{1u << F_SHIFT},

      /** @brief Thumb State (T) */
      T_SHIFT{5}, T{1u << T_SHIFT},

      /** @brief Mode Bits (M) */
      M{0x1fu};

  static constexpr u32 EXCEPTION_RESET /*   */ {0x00000000}, EXCEPTION_UNDEFINS /*  */ {0x00000004},
      EXCEPTION_SWINT /*   */ {0x00000008}, EXCEPTION_PREFETABT /* */ {0x0000000c},
      EXCEPTION_DATAABT /* */ {0x00000010}, EXCEPTION_RESERVED /*  */ {0x00000014},
      EXCEPTION_IRQ /*     */ {0x00000018}, EXCEPTION_FIQ /*       */ {0x0000001c};

  static constexpr u8 MODE_USR{0b10000}, MODE_FIQ{0b10001}, MODE_IRQ{0b10010}, MODE_SVC{0b10011},
      MODE_ABT{0b10111}, MODE_UND{0b11011}, MODE_SYS{0b11111};

  static constexpr u8 REGISTERS_PRESET_USR{0}, REGISTERS_PRESET_FIQ{1}, REGISTERS_PRESET_IRQ{2},
      REGISTERS_PRESET_SVC{3}, REGISTERS_PRESET_ABT{4}, REGISTERS_PRESET_UND{5},
      REGISTERS_PRESET_SYS{0};

  static constexpr u8 N_ACTIVE_REGISTERS = 18, N_REGISTERS = 37;
  static constexpr u8 spsr = 17;

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

  inline void set_bus(memory_bus* busptr) { bus = busptr; }

  [[nodiscard]] inline u32 read_raw_register(u8 reg) const { return registers[reg]; }
  inline void write_raw_register(u8 reg, u32 value) { registers[reg] = value; }

  [[nodiscard]] inline u32 read_active_register(u8 reg) const {
    return reg == pc ? read_pc() : registers[active_registers[reg]];
  }
  inline void write_active_register(u8 reg, u32 value) {
    if (reg == pc)
      write_pc(value);
    else
      registers[active_registers[reg]] = value;
  }

  [[nodiscard]] inline u32 read_relative_register(u8 reg, u8 bank_preset) const {
    return reg == pc ? read_pc() : registers[REGISTERS_PRESET[bank_preset][reg]];
  }
  inline void write_relative_register(u8 reg, u32 value, u8 bank_preset) {
    if (reg == pc)
      write_pc(value);
    else
      registers[REGISTERS_PRESET[bank_preset][reg]] = value;
  }

  [[nodiscard]] inline u32 read_pc() const {
    return registers[pc] + (instruction_incrementator << 1);
  }
  inline void write_pc(u32 new_pc) { registers[pc] = new_pc & ~(instruction_incrementator - 1); }

  [[nodiscard]] inline u32 read_cpsr() const { return registers[cpsr]; }
  inline void write_cpsr(u32 new_cpsr) { registers[cpsr] = new_cpsr; }
  [[nodiscard]] inline bool is_cpsr(u32 mask, u32 bits) const {
    return (registers[cpsr] & mask) == bits;
  }
  inline void clear_cpsr(u32 mask) { registers[cpsr] &= ~mask; }
  inline void set_cpsr(u32 mask, u32 bits) { registers[cpsr] = (registers[cpsr] & ~mask) | bits; }

  [[nodiscard]] inline u32 read_spsr() const { return read_active_register(spsr); }
  inline void write_spsr(u32 new_spsr) { write_active_register(spsr, new_spsr); }

  [[nodiscard]] inline bool is_mode(u8 mode) const { return (registers[cpsr] & M) == mode; }
  void set_mode(u8 mode, bool update_cpsr = true);

  inline void ensure_mode() { set_mode(read_cpsr(), false); }

  inline void restore_cpsr() {
    write_cpsr(read_spsr());
    ensure_mode();
  }

  [[nodiscard]] inline static u8 get_idx_registers_preset_by_mode(u8 mode) {
    return ((mode & 0b11) + ((mode & 0b1100) >> 2)) % 6;
  }

  [[nodiscard]] bool ckeck_arm_condition(u32 instruction) const;

  void empty_registers();

  void reset();

  void set_arm_mode();
  void set_thumb_mode();
  void step();
};

} // namespace neogba
