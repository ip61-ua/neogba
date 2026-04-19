#pragma once
#include "neogba/types.hpp"

namespace neogba {

inline constexpr u32 M_createRightMask(u32 nOffset) {
  return (nOffset >= 32) ? -1 : ((1u << nOffset) - 1u);
}

} // namespace neogba
