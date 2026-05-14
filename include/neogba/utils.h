#pragma once

#define NEOGBA_UTILS_SET_BIT_MASK(dst, mask) (dst |= mask)
#define NEOGBA_UTILS_CLEAR_BIT_MASK(dst, mask) (dst &= ~mask)
#define NEOGBA_UTILS_IS_SET_MASK(mask, val) ((mask & val) != 0)
#define NEOGBA_UTILS_BIT_TO_BOOL(content, bit) ((content & (1U << bit)) != 0)
#define NEOGBA_UTILS_EXTRACT_LSHIFT_MASK(content, nbits_lshift, mask)                              \
  ((content >> nbits_lshift) & mask)
#define NEOGBA_UTILS_CREATE_RIGHT_MASK(n_offset) ((n_offset >= 32) ? -1 : ((1U << n_offset) - 1U))
