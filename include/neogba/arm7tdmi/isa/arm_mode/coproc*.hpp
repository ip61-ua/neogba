#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/undefined.hpp"

namespace neogba::arm_coproctrans {
// struct coproctrans_tflags {
//   bool p : 1 {false};
//   bool u : 1 {false};
//   bool n : 1 {false};
//   bool w : 1 {false};
//   bool l : 1 {false};
//   constexpr auto is_valid() const { return true; }
// };
// template <coproctrans_tflags flags>
inline auto coproctrans{arm_undefined::undefined};
} // namespace neogba::arm_coproctrans

namespace neogba::arm_coprocop {
// struct coprocop_tflags {
//   u8 cpopc : 4 {};
//   constexpr auto is_valid() const { return true; }
// };
// template <coprocop_tflags flags>
inline auto coprocop{arm_undefined::undefined};
} // namespace neogba::arm_coprocop

namespace neogba::arm_coprocregtrans {
// struct coprocregtrans_tflags {
//   u8 cpopc : 4 {};
//   constexpr auto is_valid() const { return true; }
// };
// template <coprocregtrans_tflags flags>
inline auto coprocregtrans{arm_undefined::undefined};
} // namespace neogba::arm_coprocregtrans
