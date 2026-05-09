#pragma once
#include "neogba/types.hpp"

namespace neogba {

inline void setBitMask(u32& dst, u32 mask) {
  dst |= mask;
}

inline void clearBitMask(u32& dst, u32 mask) {
  dst &= ~mask;
}

[[nodiscard]] inline bool isSetMask(u32 mask, u32 val) {
  return (mask & val) != 0;
}

inline constexpr bool bitToBool(u32 content, u8 bit) {
  return (content & (1U << bit)) != 0;
}

template <typename T> inline constexpr T extractLShiftMask(u32 content, u8 nbits_lshift, u32 mask) {
  return static_cast<T>((content >> nbits_lshift) & mask);
}

inline constexpr u32 createRightMask(u32 nOffset) {
  return (nOffset >= 32) ? -1 : ((1U << nOffset) - 1U);
}

} // namespace neogba
