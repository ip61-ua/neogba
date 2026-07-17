#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"

namespace neogba {

struct arm_operand2_result {
  u8 carry_out; // 1 or 0
  u32 operable_operand2;
};

template <bool i, bool rotate_zero = false, bool bit4 = false, bool shift_zero = 0,
          arm_shift_type shift_type = LSL>
arm_operand2_result arm_operand2_generator(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>(cpu.is_cpsr(arm7tdmi::C, arm7tdmi::C))};
  u32 result;

  if constexpr (i) {
    auto imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};

    if constexpr (rotate_zero) {
      auto rotate{2u * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst)};
      carry_out = (imm >> (rotate - 1)) & 1;
      result = (imm >> rotate) | (imm << (32 - rotate));
    } else {
      result = imm;
    }
  } else {

    auto rm_idx{ISA_ARM_FSR_OPERAND2_RM::get(inst)};
    auto rm{cpu.read_active_register(rm_idx)};
    // auto shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    // auto four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    constexpr bool is_special_case{!bit4 && shift_zero};

    if constexpr (is_special_case) {
      if constexpr (shift_type == LSL) {
        result = rm;

      } else if constexpr (shift_type == LSR) {
        // shift_amount = 32; // LSR #0 = LSR #32
        result = 0;
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == ASR) {
        // shift_amount = 32; //  ASR #0
        result = static_cast<u32>(static_cast<i32>(rm) >> 31);
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == ROR) {
        // RRX: Rotate 1 bit and include Cin.
        result = ((cpu.read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1);
        carry_out = rm & 1;
      }
    } else {

      u32 shift_amount;
      if constexpr (bit4) {
        shift_amount = cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff;
      } else {
        shift_amount = ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);
      }

      // Esto posiblemente dé para otra lut y utilizar karnaugh para simplificar saltos ifs, pero de
      // momento hay que tener algo funcando, pero me ha jodido el carry. Creo que es una idea muy
      // certera.
      if constexpr (shift_type == LSL) {
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

      } else if constexpr (shift_type == LSR) {
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

      } else if constexpr (shift_type == ASR) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          result = static_cast<u32>(static_cast<i32>(rm) >> shift_amount);
          carry_out = (rm >> (shift_amount - 1)) & 1;
        } else { // shift_amount >= 32
          result = static_cast<u32>(static_cast<i32>(rm) >> 31);
          carry_out = (rm >> 31) & 1;
        }

      } else if constexpr (shift_type == ROR) {
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

  return {carry_out, result};
}

inline constexpr auto arm_operand2_lut = []() consteval {
  constexpr auto

      arm_operand2_compute_i1_rotate0{arm_operand2_generator<true, true>},
      arm_operand2_compute_i1_rotatenot0{arm_operand2_generator<true, false>},
      arm_operand2_compute_i0_40_sant0_LSL{arm_operand2_generator<false, false, false, false, LSL>},
      arm_operand2_compute_i0_40_sant0_LSR{arm_operand2_generator<false, false, false, false, LSR>},
      arm_operand2_compute_i0_40_sant0_ASR{arm_operand2_generator<false, false, false, false, ASR>},
      arm_operand2_compute_i0_40_sant0_ROR{arm_operand2_generator<false, false, false, false, ROR>},
      arm_operand2_compute_i0_40_sa0_LSL{arm_operand2_generator<false, false, false, true, LSL>},
      arm_operand2_compute_i0_40_sa0_LSR{arm_operand2_generator<false, false, false, true, LSR>},
      arm_operand2_compute_i0_40_sa0_ASR{arm_operand2_generator<false, false, false, true, ASR>},
      arm_operand2_compute_i0_40_sa0_ROR{arm_operand2_generator<false, false, false, true, ROR>},
      arm_operand2_compute_i0_41_LSL{arm_operand2_generator<false, false, true, false, LSL>},
      arm_operand2_compute_i0_41_LSR{arm_operand2_generator<false, false, true, false, LSR>},
      arm_operand2_compute_i0_41_ASR{arm_operand2_generator<false, false, true, false, ASR>},
      arm_operand2_compute_i0_41_ROR{arm_operand2_generator<false, false, true, false, ROR>};

  lut<arm_operand2_result (*)(arm7tdmi&, u32), 1 << 4, arm_operand2_result,
      +[](std::size_t idx) -> std::size_t {
        bool i = ISA_ARM_FSR_I::get_raw(idx);
        bool b4 = ISA_ARM_FSR_OPERAND2_4::get_raw(idx);
        bool t1 = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x1;
        bool t0 = (ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x2) >> 1;
        bool s_not_0 = (ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(idx)) != 0;
        bool r_not_0 = (ISA_ARM_FSR_OPERAND2_ROTATE::get(idx)) != 0;

        u8 n3 = i | b4;
        u8 n2 = i | (!b4 & s_not_0);
        u8 n1 = !i & t1;
        u8 n0 = ((r_not_0) & (i)) | (t0 & !i);

        return (n3 << 3) | (n2 << 2) | (n1 << 1) | n0;
      }>
      table;

  table.put_raw(0b0000, arm_operand2_compute_i0_40_sa0_LSL);
  table.put_raw(0b0001, arm_operand2_compute_i0_40_sa0_LSR);
  table.put_raw(0b0010, arm_operand2_compute_i0_40_sa0_ASR);
  table.put_raw(0b0011, arm_operand2_compute_i0_40_sa0_ROR);
  table.put_raw(0b0100, arm_operand2_compute_i0_40_sant0_LSL);
  table.put_raw(0b0101, arm_operand2_compute_i0_40_sant0_LSR);
  table.put_raw(0b0110, arm_operand2_compute_i0_40_sant0_ASR);
  table.put_raw(0b0111, arm_operand2_compute_i0_40_sant0_ROR);
  table.put_raw(0b1000, arm_operand2_compute_i0_41_LSL);
  table.put_raw(0b1001, arm_operand2_compute_i0_41_LSR);
  table.put_raw(0b1010, arm_operand2_compute_i0_41_ASR);
  table.put_raw(0b1011, arm_operand2_compute_i0_41_ROR);
  table.put_raw(0b1100, arm_operand2_compute_i1_rotate0);
  table.put_raw(0b1101, arm_operand2_compute_i1_rotatenot0);
  table.fill_missing(arm_operand2_compute_i1_rotatenot0);

  return table;
}();

void arm_AND(arm7tdmi& cpu, u32 inst);
void arm_EOR(arm7tdmi& cpu, u32 inst);
void arm_SUB(arm7tdmi& cpu, u32 inst);
void arm_RSB(arm7tdmi& cpu, u32 inst);
void arm_ADD(arm7tdmi& cpu, u32 inst);
void arm_ADC(arm7tdmi& cpu, u32 inst);
void arm_SBC(arm7tdmi& cpu, u32 inst);
void arm_RSC(arm7tdmi& cpu, u32 inst);
void arm_TST(arm7tdmi& cpu, u32 inst);
void arm_TEQ(arm7tdmi& cpu, u32 inst);
void arm_CMP(arm7tdmi& cpu, u32 inst);
void arm_CMN(arm7tdmi& cpu, u32 inst);
void arm_ORR(arm7tdmi& cpu, u32 inst);
void arm_MOV(arm7tdmi& cpu, u32 inst);
void arm_BIC(arm7tdmi& cpu, u32 inst);
void arm_MVN(arm7tdmi& cpu, u32 inst);
} // namespace neogba
