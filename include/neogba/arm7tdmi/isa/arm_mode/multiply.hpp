#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"

namespace neogba::arm_multiply {

struct multiply_tflags {
  bool a : 1 {false};
  bool s : 1 {false};

  inline constexpr auto is_valid() const { return true; }
};

template <multiply_tflags flags> auto multiply(arm7tdmi& cpu, u32 inst) -> void {
  static_assert(flags.is_valid(), "Invalid Template Flags");

  auto rd{RD::get(inst)};
  auto rm{RM::get(inst)};
  auto rs{RS::get(inst)};

  auto rm_content{cpu.read_active_register(rm)};
  auto rs_content{cpu.read_active_register(rs)};

  auto rd_content{rm_content * rs_content};

  if constexpr (flags.a) {
    auto rn{RN::get(inst)};

    auto rn_content{cpu.read_active_register(rn)};

    rd_content += rn_content;
  }

  cpu.write_active_register(rd, rd_content);

  if constexpr (flags.s) {
    auto n{static_cast<bool>((rd_content >> 31) & 0x1u)};
    auto z{rd_content == 0};
    auto c{(rd_content >> 30) == 2};

    // cpu.set_cpsr(arm7tdmi::N | arm7tdmi::Z | arm7tdmi::C);
  }
}

} // namespace neogba::arm_multiply
