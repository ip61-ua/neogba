#pragma once
#include "neogba/arm7tdmi/cpu.hpp"

namespace neogba::arm_undefined {

inline auto undefined(arm7tdmi&, u32) -> void {};

} // namespace neogba::arm_undefined
