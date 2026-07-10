#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"

namespace neogba {

struct arm_operand2_result {
  u32 shift_amount, operable_operand2;
};

arm_operand2_result arm_operand2_compute_i1_rotate0(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i1_rotatenot0(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_LSL(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_LSR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_ASR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_ROR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shifta0_LSL(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shifta0_LSR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shifta0_ASR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_40_shifta0_ROR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_41_LSL(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_41_LSR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_41_ASR(arm7tdmi& cpu, u32 inst);
arm_operand2_result arm_operand2_compute_i0_41_ROR(arm7tdmi& cpu, u32 inst);
// arm_operand2_result arm_operand2_compute(arm7tdmi* cpu, u32 inst);

static constexpr auto arm_operand2_lut = []() consteval {
  lut<arm_operand2_result (*)(arm7tdmi&, u32), 2, arm_operand2_result,
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

  table.fill(0b0000, arm_operand2_compute_i0_40_shifta0_LSL);
  table.fill(0b0001, arm_operand2_compute_i0_40_shifta0_LSL);
  table.fill(0b0010, arm_operand2_compute_i0_40_shifta0_LSL);
  table.fill(0b0011, arm_operand2_compute_i0_40_shifta0_LSL);
  table.fill(0b0100, arm_operand2_compute_i0_40_shiftanot0_LSL);
  table.fill(0b0101, arm_operand2_compute_i0_40_shiftanot0_LSR);
  table.fill(0b0110, arm_operand2_compute_i0_40_shiftanot0_ASR);
  table.fill(0b0111, arm_operand2_compute_i0_40_shiftanot0_ROR);
  table.fill(0b1000, arm_operand2_compute_i0_41_LSL);
  table.fill(0b1001, arm_operand2_compute_i0_41_LSR);
  table.fill(0b1010, arm_operand2_compute_i0_41_ASR);
  table.fill(0b1011, arm_operand2_compute_i0_41_ROR);
  table.fill(0b1100, arm_operand2_compute_i1_rotate0);
  table.fill(0b1101, arm_operand2_compute_i1_rotatenot0);
  table.fill_missing(arm_operand2_compute_i1_rotatenot0);

  return table;
}();

void arm_AND(arm7tdmi& cpu, u32 inst);
// void arm_EOR(arm7tdmi* cpu, u32 inst);
// void arm_SUB(arm7tdmi* cpu, u32 inst);
// void arm_RSB(arm7tdmi* cpu, u32 inst);
// void arm_ADD(arm7tdmi* cpu, u32 inst);
// void arm_ADC(arm7tdmi* cpu, u32 inst);
// void arm_SBC(arm7tdmi* cpu, u32 inst);
// void arm_RSC(arm7tdmi* cpu, u32 inst);
// void arm_TST(arm7tdmi* cpu, u32 inst);
// void arm_TEQ(arm7tdmi* cpu, u32 inst);
// void arm_CMP(arm7tdmi* cpu, u32 inst);
// void arm_CMN(arm7tdmi* cpu, u32 inst);
// void arm_ORR(arm7tdmi* cpu, u32 inst);
// void arm_MOV(arm7tdmi* cpu, u32 inst);
// void arm_BIC(arm7tdmi* cpu, u32 inst);
// void arm_MVN(arm7tdmi* cpu, u32 inst);
} // namespace neogba
