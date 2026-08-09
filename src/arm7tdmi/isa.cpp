#include "neogba/arm7tdmi/isa/arm_mode/table.hpp"
#include "neogba/arm7tdmi/isa/include.hpp"

namespace neogba {

void execute_arm(arm7tdmi& cpu, u32 inst) { arm_mode_lut.invoke(inst, cpu, inst); }

} // namespace neogba
