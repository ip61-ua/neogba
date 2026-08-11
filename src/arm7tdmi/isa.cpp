#include "neogba/arm7tdmi/isa/arm_mode/table.hpp"
#include "neogba/arm7tdmi/isa/include.hpp"

namespace neogba {

void execute_arm(arm7tdmi& cpu, u32 inst) {
  if (cpu.ckeck_arm_condition(inst)) {
    arm_mode_lut.invoke(inst, cpu, inst);
  }
}

void execute_thumb(arm7tdmi& cpu, u32 inst) {
  // lol
}

} // namespace neogba
