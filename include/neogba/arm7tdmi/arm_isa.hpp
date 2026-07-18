#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"

namespace neogba {

struct arm_operand2_result {
  u8 carry_out; // 1 or 0
  u32 result;
};

template <bool i, bool rotate_zero = false, bool bit4 = false, bool shift_zero = 0,
          arm_shift_type shift_type = arm_shift_type::LSL>
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
        result = ((cpu.read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1);
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

  return {carry_out, result};
}

inline constexpr auto arm_operand2_lut = []() consteval {
  lut<arm_operand2_result (*)(arm7tdmi&, u32), 14, arm_operand2_result,
      +[](std::size_t idx) -> std::size_t {
        auto i{static_cast<bool>(ISA_ARM_FSR_I::get_raw(idx))};
        auto b4{static_cast<bool>(ISA_ARM_FSR_OPERAND2_4::get_raw(idx))};
        auto t1{static_cast<bool>(ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x1)};
        auto t0{static_cast<bool>((ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x2) >> 1)};
        auto s_not_0{(ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(idx)) != 0};
        auto r_not_0{(ISA_ARM_FSR_OPERAND2_ROTATE::get(idx)) != 0};

        auto n3{static_cast<u8>(i | b4)};
        auto n2{static_cast<u8>(i | (!b4 & s_not_0))};
        auto n1{static_cast<u8>(!i & t1)};
        auto n0{static_cast<u8>(((r_not_0) & (i)) | (t0 & !i))};

        return (n3 << 3) | (n2 << 2) | (n1 << 1) | n0;
      }>
      table;

  table.put_raw(0b0000, arm_operand2_generator<false, false, false, true, arm_shift_type::LSL>);
  table.put_raw(0b0001, arm_operand2_generator<false, false, false, true, arm_shift_type::LSR>);
  table.put_raw(0b0010, arm_operand2_generator<false, false, false, true, arm_shift_type::ASR>);
  table.put_raw(0b0011, arm_operand2_generator<false, false, false, true, arm_shift_type::ROR>);
  table.put_raw(0b0100, arm_operand2_generator<false, false, false, false, arm_shift_type::LSL>);
  table.put_raw(0b0101, arm_operand2_generator<false, false, false, false, arm_shift_type::LSR>);
  table.put_raw(0b0110, arm_operand2_generator<false, false, false, false, arm_shift_type::ASR>);
  table.put_raw(0b0111, arm_operand2_generator<false, false, false, false, arm_shift_type::ROR>);
  table.put_raw(0b1000, arm_operand2_generator<false, false, true, false, arm_shift_type::LSL>);
  table.put_raw(0b1001, arm_operand2_generator<false, false, true, false, arm_shift_type::LSR>);
  table.put_raw(0b1010, arm_operand2_generator<false, false, true, false, arm_shift_type::ASR>);
  table.put_raw(0b1011, arm_operand2_generator<false, false, true, false, arm_shift_type::ROR>);
  table.put_raw(0b1100, arm_operand2_generator<true, true>);
  table.put_raw(0b1101, arm_operand2_generator<true, false>);

  return table;
}();

template <bool s, arm_fsr_opcode opcode> void arm_fsr_generator(arm7tdmi& cpu, u32 inst) {
  // Meta template variables
  constexpr auto is_logical{opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::EOR ||
                            opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                            opcode == arm_fsr_opcode::ORR || opcode == arm_fsr_opcode::MOV ||
                            opcode == arm_fsr_opcode::BIC || opcode == arm_fsr_opcode::MVN};
  constexpr auto can_write_rd{!(opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                                opcode == arm_fsr_opcode::CMP || opcode == arm_fsr_opcode::CMN)};

  // Retrieve values
  auto rn_idx{ISA_ARM_FSR_RN::get(inst)};
  auto rd_idx{ISA_ARM_FSR_RD::get(inst)};

  u32 c_in = (cpu.read_cpsr() & arm7tdmi::C) ? 1 : 0;
  u32 op1;
  if constexpr (opcode != arm_fsr_opcode::MOV && opcode != arm_fsr_opcode::MVN)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_operand2_lut.run(inst, cpu, inst)};
  u32 res{};

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST) {
    res = op1 & op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ) {
    res = op1 ^ op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP) {
    res = op1 - op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::RSB) {
    res = op2.result - op1;
  } else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN) {
    res = op1 + op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::ADC) {
    res = op1 + op2.result + op2.carry_out;
  } else if constexpr (opcode == arm_fsr_opcode::SBC) {
    res = op1 - op2.result + op2.carry_out - 1;
  } else if constexpr (opcode == arm_fsr_opcode::RSC) {
    res = op2.result - op1 + op2.carry_out - 1;
  } else if constexpr (opcode == arm_fsr_opcode::ORR) {
    res = op1 | op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::MOV) {
    res = op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::BIC) {
    res = op1 & ~op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::MVN) {
    res = ~op2.result;
  }

  // write back the result
  if constexpr (can_write_rd) {
    cpu.write_active_register(rd_idx, res);
  }

  // Side effects
  if constexpr (s) {
    auto z{res == 0 ? arm7tdmi::Z : 0};
    auto n{(res & 0x80000000) != 0 ? arm7tdmi::N : 0};
    auto v{rd_idx == pc ? 0 /* update logic */ : cpu.read_cpsr() & arm7tdmi::V};

    cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | v);
  }
}

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
