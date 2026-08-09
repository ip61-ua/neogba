#pragma once
#include "neogba/arm7tdmi/cpu.hpp"

namespace neogba {

void execute_arm(arm7tdmi& cpu, u32 inst);
void execute_thumb(arm7tdmi& cpu, u32 inst);

} // namespace neogba
