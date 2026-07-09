#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"

namespace neogba {

struct arm_operand2_result {
  u32 shift_amount, operable_operand2;
};

static constexpr auto arm_operand2_compute_i_lut = []() consteval {
  lut<arm_operand2_result (*)(arm7tdmi*, u32), 2, arm_operand2_result,
      +[](std::size_t idx) -> std::size_t {
        return ISA_ARM_FSR_I::get_raw(idx) | (((idx)&ISA_ARM_FSR_OPERAND2::mask) << 1);
      }>
      table{};
  table.fill(0, [](arm7tdmi*, u32) -> arm_operand2_result { return {}; });
  table.fill(1, [](arm7tdmi*, u32) -> arm_operand2_result { return {}; });
  return table;
}();

arm_operand2_result arm_operand2_compute(arm7tdmi* cpu, u32 inst);

void arm_AND(arm7tdmi* cpu, u32 inst);
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
