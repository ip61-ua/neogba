#pragma once
#include <cstdint>

#define ARM_INSTRUCTION_IS(alias) [[nodiscard]] constexpr static bool is(u32 alias)
#define ARM_INSTRUCTION_EXTRACT(alias, type) [[nodiscard]] constexpr static type extract(u32 alias)
#define ARM_INSTRUCTION_TOASM [[nodiscard]] std::string toAsm() const
#define BIT_TO_BOOL(content, bit) (((content) & (1U << (bit))) != 0)
#define EXTRACT_BIT_MASK(content, type, nbit, mask)                                                \
  static_cast<type>(((content) >> (nbit)) & (mask))

namespace neogba {

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef float f32;
typedef double f64;

} // namespace neogba
