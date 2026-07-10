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
        return ISA_ARM_FSR_I::get_raw(idx) | (((idx)&ISA_ARM_FSR_OPERAND2::mask) << 1);
      }>
      table{};
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
