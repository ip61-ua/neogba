#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"

namespace neogba {

template <bool i, bool p, bool u, bool b, bool w, bool l, bool rd_pc = false>
void arm_singletrans_generator(arm7tdmi& cpu, u32 inst) {
  auto base{ISA_ARM_SINGLETRANS_RN::get(inst)}, src_dst{ISA_ARM_SINGLETRANS_RD::get(inst)};

  arm_operand2_result op2{0, 0, 0};

  if constexpr (i) {
    op2 = arm_fsr_operand2_lut.invoke(inst, cpu, inst);
  } else {
    op2.result = ISA_ARM_SINGLETRANS_OFFSET::get(inst);
  }
}

} // namespace neogba
