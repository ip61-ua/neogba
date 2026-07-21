#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include "neogba/structs/lut.hpp"
#include <utility>

namespace neogba {

/**
 * @brief Result of decoding and evaluating ARM operand2 field .
 *
 * Stores the computed operand2 value together with the carry information
 * required by ARM data-processing instructions.
 *
 * @see arm_operand2_generator
 */
struct arm_operand2_result {
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
template <bool i, bool rotate_zero = false, bool bit4 = false, bool special_zero_shift = false,
          arm_shift_type shift_type = arm_shift_type::LSL>
[[nodiscard]] arm_operand2_result arm_operand2_generator(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>((cpu.read_cpsr() & arm7tdmi::C) >> arm7tdmi::C_SHIFT)};
  auto carry_in{carry_out};
  u32 result;

  if constexpr (i) {
    auto imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};

    if constexpr (rotate_zero)
      result = imm;
    else {
      auto rotate{2u * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst)};
      carry_out = (imm >> (rotate - 1)) & 1;
      result = (imm >> rotate) | (imm << (32 - rotate));
    }
  } else {

    auto rm_idx{ISA_ARM_FSR_OPERAND2_RM::get(inst)};
    auto rm{cpu.read_active_register(rm_idx)};
    // auto shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    // auto four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    constexpr bool is_special_case{!bit4 && special_zero_shift};

    if constexpr (is_special_case) {
      if constexpr (shift_type == arm_shift_type::LSL) {
        result = rm;

      } else if constexpr (shift_type == arm_shift_type::LSR) {
        // shift_amount = 32; // LSR #0 = LSR #32
        result = 0;
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == arm_shift_type::ASR) {
        // shift_amount = 32; //  ASR #0
        result = static_cast<u32>(static_cast<i32>(rm) >> 31);
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == arm_shift_type::ROR) {
        // RRX: Rotate 1 bit and include Cin.
        result = ((cpu.read_cpsr() & arm7tdmi::C) << (31 - arm7tdmi::C_SHIFT)) | (rm >> 1);
        carry_out = rm & 1;
      }
    } else {

      // esto no importa al caso especial complemente, por lo que lo podemos atrasar hasta aquí.
      u32 shift_amount;
      if constexpr (bit4) {
        shift_amount = cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff;
      } else {
        shift_amount = ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);
      }

      // Esto posiblemente dé para otra lut y utilizar karnaugh para simplificar saltos ifs, pero de
      // momento hay que tener algo funcando, pero me ha jodido el carry. Creo que es una idea muy
      // certera.
      if constexpr (shift_type == arm_shift_type::LSL) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          carry_out = (rm >> (32 - shift_amount)) & 1;
          result = rm << shift_amount;
        } else if (shift_amount == 32) {
          carry_out = rm & 1;
          result = 0;
        } else {
          carry_out = 0;
          result = 0;
        }

      } else if constexpr (shift_type == arm_shift_type::LSR) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          result = rm >> shift_amount;
          carry_out = (rm >> (shift_amount - 1)) & 1;
        } else if (shift_amount == 32) {
          result = 0;
          carry_out = (rm >> 31) & 1;
        } else {
          result = 0;
          carry_out = 0;
        }

      } else if constexpr (shift_type == arm_shift_type::ASR) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          result = static_cast<u32>(static_cast<i32>(rm) >> shift_amount);
          carry_out = (rm >> (shift_amount - 1)) & 1;
        } else { // shift_amount >= 32
          result = static_cast<u32>(static_cast<i32>(rm) >> 31);
          carry_out = (rm >> 31) & 1;
        }

      } else if constexpr (shift_type == arm_shift_type::ROR) {
        if (shift_amount == 0) {
          result = rm;
        } else {
          auto masked_shift{shift_amount & 0x1f};
          if (masked_shift == 0) {
            result = rm;
            carry_out = (rm >> 31) & 1;
          } else {
            result = (rm >> masked_shift) | (rm << (32 - masked_shift));
            carry_out = (rm >> (masked_shift - 1)) & 1;
          }
        }
      }
    }
  }

  return {result, carry_out, carry_in};
}

inline constexpr auto arm_fsr_operand2_i0_40_z1_LSL{
    arm_operand2_generator<false, false, false, true, arm_shift_type::LSL>};
inline constexpr auto arm_fsr_operand2_i0_40_z1_LSR{
    arm_operand2_generator<false, false, false, true, arm_shift_type::LSR>};
inline constexpr auto arm_fsr_operand2_i0_40_z1_ASR{
    arm_operand2_generator<false, false, false, true, arm_shift_type::ASR>};
inline constexpr auto arm_fsr_operand2_i0_40_z1_ROR{
    arm_operand2_generator<false, false, false, true, arm_shift_type::ROR>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_LSL{
    arm_operand2_generator<false, false, false, false, arm_shift_type::LSL>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_LSR{
    arm_operand2_generator<false, false, false, false, arm_shift_type::LSR>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_ASR{
    arm_operand2_generator<false, false, false, false, arm_shift_type::ASR>};
inline constexpr auto arm_fsr_operand2_i0_40_z0_ROR{
    arm_operand2_generator<false, false, false, false, arm_shift_type::ROR>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_LSL{
    arm_operand2_generator<false, false, true, false, arm_shift_type::LSL>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_LSR{
    arm_operand2_generator<false, false, true, false, arm_shift_type::LSR>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_ASR{
    arm_operand2_generator<false, false, true, false, arm_shift_type::ASR>};
inline constexpr auto arm_fsr_operand2_i0_41_z0_ROR{
    arm_operand2_generator<false, false, true, false, arm_shift_type::ROR>};
inline constexpr auto arm_fsr_operand2_i1_r1{arm_operand2_generator<true, true>};
inline constexpr auto arm_fsr_operand2_i1_r0{arm_operand2_generator<true, false>};

/**
 * @brief Compile-time lookup table for operand2 evaluators.
 *
 * Maps the operand2 encoding of an ARM data-processing instruction to the corresponding specialized
 * operand2 instantiation.
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
inline constexpr auto arm_fsr_operand2_lut = []() consteval {
  lut<arm_operand2_result (*)(arm7tdmi&, u32), 14,
      +[](std::size_t idx) -> std::size_t {
        auto i{static_cast<bool>(ISA_ARM_FSR_I::get_raw(idx))};
        auto b4{static_cast<bool>(ISA_ARM_FSR_OPERAND2_4::get_raw(idx))};
        auto t0{static_cast<bool>(ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x1)};
        auto t1{static_cast<bool>((ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x2) >> 1)};
        auto s_not_0{(ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(idx)) != 0};
        auto r_not_0{(ISA_ARM_FSR_OPERAND2_ROTATE::get(idx)) != 0};

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

/**
 * @brief Executes a compile-time specialized ARM data-processing instruction.
 *
 * This template generates the implementation of an ARM Flexible Second Operand (FSR)
 * data-processing instruction. The selected opcode and execution behaviour could be entirely
 * resolved at compile time using template parameters, allowing the compiler to remove unused
 * branches and optimize the generated code for each instruction variant.
 *
 * Depending on the template arguments, the generated implementation may update the CPSR flags,
 * write the result to the program counter, or implement flag-only instructions such as CMP or TST.
 *
 * @tparam opcode Data-processing opcode to execute.
 * @tparam s Whether the instruction updates the CPSR condition flags.
 * @tparam rd_pc Whether the destination register is R15 (PC).
 *
 * @param cpu ARM7TDMI CPU state to execute the instruction on.
 * @param inst Raw 32-bit ARM instruction.
 *
 * @note All instruction-specific decisions are resolved at compile time using `if constexpr`, so
 * the generated machine code contains only the logic required for the selected instruction variant
 * with least branches at execution-time.
 *
 * @warning Setting `rd_pc` when `opcode` is one of (`TST`, `TEQ`, `CMP`, `CMN`) is not a documented
 * behaviour in ARM. Because these opcodes only write side effects (by updating CPSR) and ignore
 * destination `rd` field. According, it is illegal to write that on assembly (`rd` contains trash).
 *
 * @warning If the instruction `opcode` is one of (`TST`, `TEQ`, `CMP`, `CMN`), then the flag S is
 * implicitly set. If else, it means it's another instruction type. This fucntion is not
 * responsible for handling that!
 *
 * @todo Testing this function.
 * @todo Ensure correct handling when r15 is involved as source or as destination.
 *
 * @see arm_operand2_generator
 * @see arm_operand2_lut
 * @see arm_fsr_opcode
 * @see arm7tdmi
 */
template <arm_fsr_opcode opcode, bool s = false, bool rd_pc = false>
void arm_fsr_generator(arm7tdmi& cpu, u32 inst) {

  // Meta template variables
  constexpr auto is_logical{opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::EOR ||
                            opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                            opcode == arm_fsr_opcode::ORR || opcode == arm_fsr_opcode::MOV ||
                            opcode == arm_fsr_opcode::BIC || opcode == arm_fsr_opcode::MVN};
  constexpr auto can_write_rd{!(opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                                opcode == arm_fsr_opcode::CMP || opcode == arm_fsr_opcode::CMN)};
  constexpr auto is_inverted_sub{opcode == arm_fsr_opcode::RSB || opcode == arm_fsr_opcode::RSC};

  // Retrieve values
  u8 rd_idx;
  u32 op1;
  u64 res;
  auto rn_idx{ISA_ARM_FSR_RN::get(inst)};

  if constexpr (rd_pc)
    rd_idx = 0xfu;
  else
    rd_idx = ISA_ARM_FSR_RD::get(inst);

  if constexpr (opcode != arm_fsr_opcode::MOV && opcode != arm_fsr_opcode::MVN)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_fsr_operand2_lut.invoke(inst, cpu, inst)};

  if constexpr (is_inverted_sub)
    std::swap(op1, op2.result);

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST)
    res = op1 & op2.result;
  else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP ||
                     opcode == arm_fsr_opcode::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (opcode == arm_fsr_opcode::SBC || opcode == arm_fsr_opcode::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (opcode == arm_fsr_opcode::ORR)
    res = op1 | op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MOV)
    res = op2.result;
  else if constexpr (opcode == arm_fsr_opcode::BIC)
    res = op1 & ~op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MVN)
    res = ~op2.result;

  // write back the result
  auto res32{static_cast<u32>(res)};
  if constexpr (can_write_rd)
    cpu.write_active_register(rd_idx, res32);

  // Side effects
  if constexpr (s) {
    if constexpr (rd_pc) {
      cpu.write_cpsr(cpu.read_spsr());

    } else {

      // common
      auto z{static_cast<u32>(res32 == 0) << arm7tdmi::Z_SHIFT}; // (res32 == 0) -> true -> 0x0...01
      u32 n{res32 & 0x80000000}; // N ya está en el bit 31 -> 0 movimientos

      if constexpr (is_logical) {
        auto c{static_cast<u32>(op2.carry_out << arm7tdmi::C_SHIFT)}; // op2.carry_out es 0 o 1.

        // meter V aquí = !necesario -> no está afectado.
        // set_cpsr(mask, values) sobrescribe solo estos `mask`
        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C, z | n | c);
      } else {

        // another meta template info
        constexpr auto is_sum{opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::ADC ||
                              opcode == arm_fsr_opcode::CMN};

        auto c{static_cast<u32>(res >> 32)}; // (res >> 32) & 1 es 1 o 0.
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        c = (c & 1) << arm7tdmi::C_SHIFT; // Mover lo necesario!
        v = (v & (op1 ^ res32) & 0x80000000) >>
            (31 - arm7tdmi::V_SHIFT); // Mover lo justo al bit V.

        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | c | v);
      }
    }
  }
}

inline constexpr auto arm_AND_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::AND>};
inline constexpr auto arm_EOR_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::EOR>};
inline constexpr auto arm_SUB_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::SUB>};
inline constexpr auto arm_RSB_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSB>};
inline constexpr auto arm_ADD_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADD>};
inline constexpr auto arm_ADC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADC>};
inline constexpr auto arm_SBC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::SBC>};
inline constexpr auto arm_RSC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSC>};
inline constexpr auto arm_ORR_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::ORR>};
inline constexpr auto arm_MOV_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::MOV>};
inline constexpr auto arm_BIC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::BIC>};
inline constexpr auto arm_MVN_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::MVN>};
inline constexpr auto arm_AND_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::AND, true>};
inline constexpr auto arm_EOR_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::EOR, true>};
inline constexpr auto arm_SUB_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::SUB, true>};
inline constexpr auto arm_RSB_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSB, true>};
inline constexpr auto arm_ADD_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADD, true>};
inline constexpr auto arm_ADC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADC, true>};
inline constexpr auto arm_SBC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::SBC, true>};
inline constexpr auto arm_RSC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSC, true>};
inline constexpr auto arm_ORR_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::ORR, true>};
inline constexpr auto arm_MOV_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::MOV, true>};
inline constexpr auto arm_BIC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::BIC, true>};
inline constexpr auto arm_MVN_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::MVN, true>};
inline constexpr auto arm_AND_S_RdPC{arm_fsr_generator<arm_fsr_opcode::AND, true, true>};
inline constexpr auto arm_EOR_S_RdPC{arm_fsr_generator<arm_fsr_opcode::EOR, true, true>};
inline constexpr auto arm_SUB_S_RdPC{arm_fsr_generator<arm_fsr_opcode::SUB, true, true>};
inline constexpr auto arm_RSB_S_RdPC{arm_fsr_generator<arm_fsr_opcode::RSB, true, true>};
inline constexpr auto arm_ADD_S_RdPC{arm_fsr_generator<arm_fsr_opcode::ADD, true, true>};
inline constexpr auto arm_ADC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::ADC, true, true>};
inline constexpr auto arm_SBC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::SBC, true, true>};
inline constexpr auto arm_RSC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::RSC, true, true>};
inline constexpr auto arm_ORR_S_RdPC{arm_fsr_generator<arm_fsr_opcode::ORR, true, true>};
inline constexpr auto arm_MOV_S_RdPC{arm_fsr_generator<arm_fsr_opcode::MOV, true, true>};
inline constexpr auto arm_BIC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::BIC, true, true>};
inline constexpr auto arm_MVN_S_RdPC{arm_fsr_generator<arm_fsr_opcode::MVN, true, true>};
inline constexpr auto arm_AND_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::AND, false, true>};
inline constexpr auto arm_EOR_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::EOR, false, true>};
inline constexpr auto arm_SUB_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::SUB, false, true>};
inline constexpr auto arm_RSB_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::RSB, false, true>};
inline constexpr auto arm_ADD_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::ADD, false, true>};
inline constexpr auto arm_ADC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::ADC, false, true>};
inline constexpr auto arm_SBC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::SBC, false, true>};
inline constexpr auto arm_RSC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::RSC, false, true>};
inline constexpr auto arm_ORR_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::ORR, false, true>};
inline constexpr auto arm_MOV_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::MOV, false, true>};
inline constexpr auto arm_BIC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::BIC, false, true>};
inline constexpr auto arm_MVN_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::MVN, false, true>};

inline constexpr auto arm_TST_notRdPC{arm_fsr_generator<arm_fsr_opcode::TST, true>};
inline constexpr auto arm_TEQ_notRdPC{arm_fsr_generator<arm_fsr_opcode::TEQ, true>};
inline constexpr auto arm_CMP_notRdPC{arm_fsr_generator<arm_fsr_opcode::CMP, true>};
inline constexpr auto arm_CMN_notRdPC{arm_fsr_generator<arm_fsr_opcode::CMN, true>};
inline constexpr auto arm_TST_RdPC{arm_fsr_generator<arm_fsr_opcode::TST, true, true>};
inline constexpr auto arm_TEQ_RdPC{arm_fsr_generator<arm_fsr_opcode::TEQ, true, true>};
inline constexpr auto arm_CMP_RdPC{arm_fsr_generator<arm_fsr_opcode::CMP, true, true>};
inline constexpr auto arm_CMN_RdPC{arm_fsr_generator<arm_fsr_opcode::CMN, true, true>};

} // namespace neogba
