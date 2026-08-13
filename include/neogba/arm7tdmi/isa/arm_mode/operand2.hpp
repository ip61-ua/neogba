#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include <cstddef>

namespace neogba::arm_operand2 {

struct operand2_output {
  /** Computed Operand2 value that can be used as operand. */
  u32 result;

  /**
   * Carry produced while evaluating operand2.
   *
   * This is also known as shift barrel carry.
   *
   * The value is used as the C flag by logical instructions when the
   * instruction updates the CPSR.
   */
  u8 carry_out;

  /**
   * CPSR C flag BEFORE operand2 evaluation.
   *
   * The value is used for arithmetic opertations additions with carry and substractions. Ignoring
   * `carry_out`.
   */
  u8 carry_in;
};

struct operand2_tflags {
  bool i : 1 {false};
  bool rotate_zero : 1 {false};
  bool bit4 : 1 {false};
  bool shift_zero : 1 {false};
  shift_enum shift_type : 2 {shift_enum::LSL};
};

template <operand2_tflags flags> [[nodiscard]] operand2_output operand2(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>((cpu.read_cpsr() & arm7tdmi::C) >> arm7tdmi::C_SHIFT)};
  auto carry_in{carry_out};
  u32 result;

  if constexpr (flags.i) {
    auto imm{IMM::get(inst)};

    if constexpr (flags.rotate_zero)
      result = imm;
    else {
      auto rotate{2u * ROTATE::get(inst)};
      result = std::rotr(imm, rotate);
      carry_out = (result >> 31) & 1;
    }
  } else {

    auto rm_idx{RM::get(inst)};
    auto rm{cpu.read_active_register(rm_idx)};
    // auto shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    // auto four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    constexpr bool is_special_case{!flags.bit4 && flags.shift_zero};

    if constexpr (is_special_case) {
      if constexpr (flags.shift_type == shift_enum::LSL) {
        result = rm;

      } else if constexpr (flags.shift_type == shift_enum::LSR) {
        // shift_amount = 32; // LSR #0 = LSR #32
        result = 0;
        carry_out = (rm >> 31) & 1;

      } else if constexpr (flags.shift_type == shift_enum::ASR) {
        // shift_amount = 32; //  ASR #0
        result = static_cast<u32>(static_cast<i32>(rm) >> 31);
        carry_out = (rm >> 31) & 1;

      } else if constexpr (flags.shift_type == shift_enum::ROR) {
        // RRX: Rotate 1 bit and include Cin.
        result = (carry_in << 31) | (rm >> 1);
        carry_out = rm & 1;
      }
    } else {

      // esto no importa al caso especial complemente, por lo que lo podemos atrasar hasta aquí.
      u32 shift_amount;
      if constexpr (flags.bit4) {
        shift_amount = cpu.read_active_register(RS::get(inst)) & 0xff;
        if (shift_amount == 0)
          return {rm, carry_out, carry_in};
      } else {
        shift_amount = SHIFT_AMOU::get(inst);
        // este jamás será cero porque ya lo fue y tiene 5 bits!
      }

      // aunque esto sea un if, lo cierto es que es común a todos y adelantamos la salida.
      if constexpr (flags.shift_type == shift_enum::LSL) {
        if constexpr (flags.bit4) {
          if (shift_amount > 32)
            return {0, 0, carry_in};

          else if (shift_amount == 32)
            return {0, static_cast<u8>(rm & 1), carry_in};
        }

        carry_out = (rm >> (32 - shift_amount)) & 1;
        result = rm << shift_amount;

      } else if constexpr (flags.shift_type == shift_enum::LSR) {
        if constexpr (flags.bit4) {
          if (shift_amount > 32)
            return {0, 0, carry_in};

          else if (shift_amount == 32)
            return {0, static_cast<u8>((rm >> 31) & 1), carry_in};
        }

        result = rm >> shift_amount;
        carry_out = (rm >> (shift_amount - 1)) & 1;

      } else if constexpr (flags.shift_type == shift_enum::ASR) {
        if constexpr (flags.bit4) {
          if (shift_amount >= 32)
            return {static_cast<u32>(static_cast<i32>(rm) >> 31), static_cast<u8>((rm >> 31) & 1),
                    carry_in};
        }

        result = static_cast<u32>(static_cast<i32>(rm) >> shift_amount);
        carry_out = (rm >> (shift_amount - 1)) & 1;

      } else if constexpr (flags.shift_type == shift_enum::ROR) {

        auto masked_shift{shift_amount & 0x1f};
        if constexpr (flags.bit4) {
          if (masked_shift == 0)
            return {rm, static_cast<u8>((rm >> 31) & 1), carry_in};
        }
        result = std::rotr(rm, masked_shift);
        carry_out = (rm >> (masked_shift - 1)) & 1;
      }
    }
  }

  return {result, carry_out, carry_in};
}

/**
 * @brief Compile-time lookup table for operand2 evaluators.
 *
 * Maps the operand2 encoding of an ARM data-processing instruction to the corresponding
 * specialized operand2 instantiation.
 *
 * The lut index is minimized using a Karnaugh-map reduction of the operand2 encoding bits,
 * reducing the number of required specializations to 14 cases.
 *
 * The table is generated during compilation and contains pointers to specialized functions
 * without requiring any runtime initialization.
 *
 * It is auto evaluated lambda that fills lut properly.
 *
 * @todo Testing all cases.
 *
 * @see lut
 * @see arm_operand2_generator
 * @see arm7tdmi
 */
inline constexpr auto operand2_table = []() consteval {
  lut<operand2_output (*)(arm7tdmi&, u32), 1 << 4,
      +[](std::size_t idx) -> std::size_t {
        auto i{static_cast<bool>(arm_fsr::I::get_raw(idx))};
        auto b4{static_cast<bool>(B4::get_raw(idx))};
        auto t0{static_cast<bool>(SHIFT_TYPE::get(idx) & 0x1)};
        auto t1{static_cast<bool>((SHIFT_TYPE::get(idx) & 0x2) >> 1)};
        auto s_not_0{(SHIFT_AMOU::get(idx)) != 0};
        auto r_not_0{(ROTATE::get(idx)) != 0};

        auto n3{static_cast<u8>(i | b4)};
        auto n2{static_cast<u8>(i | (!b4 & s_not_0))};
        auto n1{static_cast<u8>(!i & t1)};
        auto n0{static_cast<u8>(((r_not_0) & (i)) | (t0 & !i))};

        return (n3 << 3) | (n2 << 2) | (n1 << 1) | n0;
      }>
      table;

  [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    ((table.put_raw(Is, &operand2<operand2_tflags{.i = false,
                                                  .bit4 = false,
                                                  .shift_zero = true,
                                                  .shift_type = static_cast<shift_enum>(Is)}>)),
     ...);
  }(std::make_index_sequence<4>{});

  [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    ((table.put_raw(4 + Is, &operand2<operand2_tflags{.i = false,
                                                      .bit4 = false,
                                                      .shift_zero = false,
                                                      .shift_type = static_cast<shift_enum>(Is)}>)),
     ...);
  }(std::make_index_sequence<4>{});

  [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    ((table.put_raw(8 + Is, &operand2<operand2_tflags{.i = false,
                                                      .bit4 = true,
                                                      .shift_zero = false,
                                                      .shift_type = static_cast<shift_enum>(Is)}>)),
     ...);
  }(std::make_index_sequence<4>{});

  [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    ((table.put_raw(
          12 + Is,
          &operand2<operand2_tflags{.i = true, .rotate_zero = static_cast<bool>(0b1 & ~Is)}>),
      ...));
  }(std::make_index_sequence<2>{});

  return table;
}();
} // namespace neogba::arm_operand2
