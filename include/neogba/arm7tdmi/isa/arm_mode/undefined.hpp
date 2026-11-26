#pragma once
#include "neogba/arm7tdmi/cpu.hpp"

namespace neogba::arm_undefined {

inline auto undefined(arm7tdmi& cpu, u32) {
  auto prev_cpsr{cpu.read_cpsr()};
  cpu.write_raw_register(spsr_und, prev_cpsr);
  cpu.set_mode(arm7tdmi::MODE_UND);
  cpu.set_cpsr(arm7tdmi::F, arm7tdmi::F);

  auto prev_pc{cpu.read_pc()};
  cpu.write_raw_register(pc, 0x04);
  cpu.write_raw_register(r14_svc, prev_pc); // improtanye debe ser justo el de antes
};

} // namespace neogba::arm_undefined
