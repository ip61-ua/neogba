#pragma once
#include "neogba/arm7tdmi/cpu.hpp"

namespace neogba::arm_swint {

inline auto swint(arm7tdmi& cpu, u32) {
  auto prev_cpsr{cpu.read_cpsr()};
  auto prev_pc{cpu.read_pc()};
  cpu.set_mode(arm7tdmi::MODE_SVC);
  cpu.write_raw_register(pc, 0x08);
  cpu.write_raw_register(spsr_svc, prev_cpsr);
  cpu.write_raw_register(r14_svc, prev_pc);
};

} // namespace neogba::arm_swint
