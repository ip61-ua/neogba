#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/blocktrans.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/half.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/singleswap.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/singletrans.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/undefined.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include <type_traits>

namespace neogba {

inline constexpr auto arm_mode_lut = []() consteval {
  using fn_ptr = void (*)(arm7tdmi&, u32);

  lut<fn_ptr, 1 << 12,
      [](std::size_t idx) -> std::size_t {
        return ((0x0ff00000 & idx) >> (20 - 4)) | ((0xf0u & idx) >> 4);
      }>
      table;

  table.fill(arm_undefined::undefined);

  {
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      (([&]() {
         using namespace arm_fsr;
         constexpr auto opcode{static_cast<opcode_enum>(Is & 0xfu)};
         constexpr auto s{((Is >> 4) & 1u) != 0};
         constexpr auto tflags{fsr_tflags{.opcode = opcode, .s = s}};

         if constexpr (tflags.is_valid())
           table.fill(TEMPLATE | OPCODE::h(opcode) | S::h(s), IGNORED, &fsr<tflags>);
       }()),
       ...);
    }(std::make_index_sequence<1 << 5>{});
  }

  {
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      (([&]() {
         using namespace arm_singletrans;
         constexpr auto i{(Is & (0x1u << 5)) != 0}, //
             p{(Is & (0x1u << 4)) != 0},            //
             u{(Is & (0x1u << 3)) != 0},            //
             b{(Is & (0x1u << 2)) != 0},            //
             w{(Is & (0x1u << 1)) != 0},            //
             l{(Is & 0x1u) != 0};
         constexpr auto tflags{singletrans_tflags{i, p, u, b, w, l}};

         if constexpr (tflags.is_valid())
           table.fill(TEMPLATE | I::h(i) | P::h(p) | U::h(u) | B::h(b) | W::h(w) | L::h(l), IGNORED,
                      &singletrans<tflags>);
       }()),
       ...);
    }(std::make_index_sequence<1 << 6>{});
  }

  {
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      (([&]() {
         // Primero se llena con bits[7..4] con any number
         // Y luego con cero
         using namespace arm_blocktrans;
         constexpr auto zeros_4_to_7{(Is & (0x1u << 5)) != 0}, //
             p{(Is & (0x1u << 4)) != 0},                       //
             u{(Is & (0x1u << 3)) != 0},                       //
             s{(Is & (0x1u << 2)) != 0},                       //
             w{(Is & (0x1u << 1)) != 0},                       //
             l{(Is & 0x1u) != 0};                              //
         constexpr auto tflags{blocktrans_tflags{p, u, s, w, l, zeros_4_to_7}};

         if constexpr (tflags.is_valid())
           table.fill(TEMPLATE | P::h(p) | U::h(u) | S::h(s) | W::h(w) | L::h(l),
                      IGNORED | (zeros_4_to_7 ? 0 : REGLIST_7_4::H), &blocktrans<tflags>);
       }()),
       ...);
    }(std::make_index_sequence<1 << 6>{});
  }

  {
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      (([&]() {
         using namespace arm_singleswap;

         constexpr auto b{Is == 1};
         constexpr auto tflags{singleswap_tflags{b}};

         if constexpr (tflags.is_valid())
           table.fill(TEMPLATE | B::h(b), IGNORED, &singleswap<tflags>);
       }()),
       ...);
    }(std::make_index_sequence<1 << 1>{});
  }

  {
    [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      (([&]() {
         using namespace arm_halfreg;

         constexpr auto is_immediate{(Is & (0x1u << 6)) != 0};

         using t_flags =
             std::conditional_t<is_immediate, arm_halfimm::halfimm_tflags, halfreg_tflags>;

         constexpr auto p{(Is & (0x1u << 5)) != 0}, //
             u{(Is & (0x1u << 4)) != 0},            //
             w{(Is & (0x1u << 3)) != 0},            //
             l{(Is & (0x1u << 2)) != 0},            //
             s{(Is & (0x1u << 1)) != 0},            //
             h{(Is & 0x1u) != 0};                   //
         constexpr auto tflags{t_flags{p, u, l, w, s, h}};

         if constexpr (tflags.is_valid())
           table.fill(is_immediate
                          ? arm_halfimm::TEMPLATE
                          : TEMPLATE //
                                | P::h(p) | U::h(u) | L::h(l) | W::h(w) | S::h(s) | H::h(h),
                      is_immediate ? arm_halfimm::IGNORED : IGNORED,
                      is_immediate ? &arm_halfimm::halfimm<tflags> : &halfreg<tflags>);
       }()),
       ...);
    }(std::make_index_sequence<1 << 7>{});
  }

  return table;
}();
} // namespace neogba
