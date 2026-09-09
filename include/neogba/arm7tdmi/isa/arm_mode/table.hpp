#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/singletrans.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/undefined.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"

namespace neogba {

inline constexpr auto arm_mode_lut = []() consteval {
  using fn_ptr = void (*)(arm7tdmi&, u32);

  lut<fn_ptr, 1 << 12,
      [](std::size_t idx) -> std::size_t {
        return ((0x0ff00000 & idx) >> (20 - 4)) | ((0xf0u & idx) >> 4);
      }>
      table;

  table.fill(arm_undefined::undefined);

  [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    (([&]() {
       using namespace arm_fsr;
       constexpr auto opcode{static_cast<opcode_enum>(Is & 0xFu)};
       constexpr bool s{static_cast<bool>((Is >> 4) & 1u)};

       if constexpr (!(not s and (opcode == opcode_enum::TST or opcode == opcode_enum::TEQ or
                                  opcode == opcode_enum::CMP or opcode == opcode_enum::CMN))) {

         table.fill(TEMPLATE | OPCODE::h(opcode) | S::h(s), IGNORED,
                    &fsr<fsr_tflags{.opcode = opcode, .s = s}>);
       }
     }()),
     ...);
  }(std::make_index_sequence<32>{});

  [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    (([&]() {
       using namespace arm_singletrans;
       constexpr u32 tflags{0x3fu & Is};
       constexpr auto i{(tflags & (0x1u << 5)) != 0}, //
           p{(tflags & (0x1u << 4)) != 0},            //
           u{(tflags & (0x1u << 3)) != 0},            //
           b{(tflags & (0x1u << 2)) != 0},            //
           w{(tflags & (0x1u << 1)) != 0},            //
           l{(tflags & 0x1u) != 0};

       table.fill(TEMPLATE | I::h(i) | P::h(p) | U::h(u) | B::h(b) | W::h(w) | L::h(l), IGNORED,
                  &singletrans<singletrans_tflags{i, p, u, b, w, l}>);
     }()),
     ...);
  }(std::make_index_sequence<64>{});

  return table;
}();
} // namespace neogba
