#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"

namespace neogba::arm_operand2 {
/**
 * @brief Result of decoding and evaluating ARM operand2 field .
 *
 * Stores the computed operand2 value together with the carry information
 * required by ARM data-processing instructions.
 *
 * @see arm_operand2_generator
 */
struct op2_output {
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

/**
 * @brief Evaluates ARM operand2 using compile-time specialization.
 *
 * Computes the value of operand2 for an ARM data-processing instruction and returns the resulting
 * value together with the carry information required by the instruction semantics.
 *
 * The operand2 addressing mode is selected entirely at compile time through the template
 * parameters, allowing the compiler to eliminate unused branches and generate a specialized
 * implementation for each encoding variant.
 *
 * Supported variants include:
 * - Immediate operands.
 * - Register operands.
 * - Immediate and register-controlled shifts.
 * - LSL, LSR, ASR, ROR and the RRX special cases.
 *
 * @tparam i Treats operand2 as an rotated immediate (`true`) or shifted register (`false`).
 * @tparam rotate_zero Whether the immediate rotation field is non-zero. Ignored if `i` is `false`.
 * @tparam bit4 Shift is a register (`true`) or 5 bit immediate (`false`). Ignored `i` is `true`.
 * @tparam shift_zero Whether the encoded immediate shift amount is zero. Ignored if `i` is `true`.
 * @tparam shift_type Shift operation applied to the register operand. Ignored if `i` is `true`.
 *
 * @param cpu ARM7TDMI CPU state.
 * @param inst Raw 32-bit ARM instruction.
 *
 * @return Evaluated operand2 together with its carry information.
 *
 * @see arm_shift_type
 * @see arm7tdmi
 */
template <bool i, bool rotate_zero = false, bool bit4 = false, bool shift_zero = false,
          shift_enum shift_type = shift_enum::LSL>
[[nodiscard]] op2_output generator(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>((cpu.read_cpsr() & arm7tdmi::C) >> arm7tdmi::C_SHIFT)};
  auto carry_in{carry_out};
  u32 result;

  if constexpr (i) {
    auto imm{IMM::get(inst)};

    if constexpr (rotate_zero)
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

    constexpr bool is_special_case{!bit4 && shift_zero};

    if constexpr (is_special_case) {
      if constexpr (shift_type == shift_enum::LSL) {
        result = rm;

      } else if constexpr (shift_type == shift_enum::LSR) {
        // shift_amount = 32; // LSR #0 = LSR #32
        result = 0;
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == shift_enum::ASR) {
        // shift_amount = 32; //  ASR #0
        result = static_cast<u32>(static_cast<i32>(rm) >> 31);
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == shift_enum::ROR) {
        // RRX: Rotate 1 bit and include Cin.
        result = (carry_in << 31) | (rm >> 1);
        carry_out = rm & 1;
      }
    } else {

      // esto no importa al caso especial complemente, por lo que lo podemos atrasar hasta aquí.
      u32 shift_amount;
      if constexpr (bit4) {
        shift_amount = cpu.read_active_register(RS::get(inst)) & 0xff;
        if (shift_amount == 0)
          return {rm, carry_out, carry_in};
      } else {
        shift_amount = SHIFT_AMOU::get(inst);
        // este jamás será cero porque ya lo fue y tiene 5 bits!
      }

      // aunque esto sea un if, lo cierto es que es común a todos y adelantamos la salida.
      if constexpr (shift_type == shift_enum::LSL) {
        if constexpr (bit4) {
          if (shift_amount > 32)
            return {0, 0, carry_in};

          else if (shift_amount == 32)
            return {0, static_cast<u8>(rm & 1), carry_in};
        }

        carry_out = (rm >> (32 - shift_amount)) & 1;
        result = rm << shift_amount;

      } else if constexpr (shift_type == shift_enum::LSR) {
        if constexpr (bit4) {
          if (shift_amount > 32)
            return {0, 0, carry_in};

          else if (shift_amount == 32)
            return {0, static_cast<u8>((rm >> 31) & 1), carry_in};
        }

        result = rm >> shift_amount;
        carry_out = (rm >> (shift_amount - 1)) & 1;

      } else if constexpr (shift_type == shift_enum::ASR) {
        if constexpr (bit4) {
          if (shift_amount >= 32)
            return {static_cast<u32>(static_cast<i32>(rm) >> 31), static_cast<u8>((rm >> 31) & 1),
                    carry_in};
        }

        result = static_cast<u32>(static_cast<i32>(rm) >> shift_amount);
        carry_out = (rm >> (shift_amount - 1)) & 1;

      } else if constexpr (shift_type == shift_enum::ROR) {

        auto masked_shift{shift_amount & 0x1f};
        if constexpr (bit4) {
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

inline constexpr auto arm_fsr_operand2_i0_40_z1_LSL{
    generator<false, false, false, true, shift_enum::LSL>};
inline constexpr auto arm_fsr_operand2_i0_40_z1_LSR{
    generator<false, false, false, true, shift_enum::LSR>};
inline constexpr auto arm_fsr_operand2_i0_40_z1_ASR{
    generator<false, false, false, true, shift_enum::ASR>};
inline constexpr auto arm_fsr_operand2_i0_40_z1_ROR{
    generator<false, false, false, true, shift_enum::ROR>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_LSL{
    generator<false, false, false, false, shift_enum::LSL>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_LSR{
    generator<false, false, false, false, shift_enum::LSR>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_ASR{
    generator<false, false, false, false, shift_enum::ASR>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_ROR{
    generator<false, false, false, false, shift_enum::ROR>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_LSL{
    generator<false, false, true, false, shift_enum::LSL>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_LSR{
    generator<false, false, true, false, shift_enum::LSR>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_ASR{
    generator<false, false, true, false, shift_enum::ASR>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_ROR{
    generator<false, false, true, false, shift_enum::ROR>};
inline constexpr auto arm_fsr_operand2_i1_r1{generator<true, true>};
inline constexpr auto arm_fsr_operand2_i1_r0{generator<true, false>};

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
inline constexpr auto table = []() consteval {
  lut<op2_output (*)(arm7tdmi&, u32), 1 << 4,
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

  table.put_raw(0b0000, arm_fsr_operand2_i0_40_z1_LSL);
  table.put_raw(0b0001, arm_fsr_operand2_i0_40_z1_LSR);
  table.put_raw(0b0010, arm_fsr_operand2_i0_40_z1_ASR);
  table.put_raw(0b0011, arm_fsr_operand2_i0_40_z1_ROR);
  table.put_raw(0b0100, arm_fsr_operand2_i0_40_z0_LSL);
  table.put_raw(0b0101, arm_fsr_operand2_i0_40_z0_LSR);
  table.put_raw(0b0110, arm_fsr_operand2_i0_40_z0_ASR);
  table.put_raw(0b0111, arm_fsr_operand2_i0_40_z0_ROR);
  table.put_raw(0b1000, arm_fsr_operand2_i0_41_z0_LSL);
  table.put_raw(0b1001, arm_fsr_operand2_i0_41_z0_LSR);
  table.put_raw(0b1010, arm_fsr_operand2_i0_41_z0_ASR);
  table.put_raw(0b1011, arm_fsr_operand2_i0_41_z0_ROR);
  table.put_raw(0b1100, arm_fsr_operand2_i1_r1);
  table.put_raw(0b1101, arm_fsr_operand2_i1_r0);

  return table;
}();
} // namespace neogba::arm_operand2
