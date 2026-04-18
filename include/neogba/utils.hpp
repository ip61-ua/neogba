#pragma once
#include "neogba/constants.hpp"
#include "neogba/types.hpp"

namespace neogba {

inline constexpr u32 M_createRightMask(u32 nOffset) {
  return (nOffset >= 32) ? K_mask32 : ((1 << nOffset) - 1);
}

inline constexpr u32 M_rotr32(u32 value, u32 shift) {
  if (shift == 0)
    return value;
  return (value >> shift) | (value << (32 - shift));
}

inline constexpr u8 extractByte(u32 word, u32 byteOffset) {
  return (word >> (byteOffset * 8)) & 0xFF;
}

inline constexpr void insertByte(u32& word, u32 byteOffset, u8 val) {
  u32 shift = byteOffset * 8;
  word &= ~(0xFF << shift);
  word |= (val << shift);
}

} // namespace neogba
