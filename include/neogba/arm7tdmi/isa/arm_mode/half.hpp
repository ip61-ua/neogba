#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"

namespace neogba::arm_half {

struct half_tflags {
  bool p : 1 {false};
  bool u : 1 {false};
  bool w : 1 {false};
  bool l : 1 {false};
  bool s : 1 {false};
  bool h : 1 {false};

  constexpr auto is_valid() const {
    if (!s && !h)
      return false;

    if (s && !l)
      return false;

    if (!p && w)
      return false;

    return true;
  }
};

template <half_tflags flags, bool immediate> auto half(arm7tdmi& cpu, u32 inst) -> void {
  static_assert(flags.is_valid(), "Invalid Template Flags");

  using namespace neogba::arm_halfreg;

  const auto r_base{RN::get(inst)}, src_dst{RD::get(inst)};

  u32 offset;
  if constexpr (immediate)
    offset = arm_halfimm::OFFSET::get(inst);
  else
    offset = cpu.read_active_register(RM::get(inst));

  const u32 base{cpu.read_active_register(r_base)};
  u32 offsetted_base{base};
  if constexpr (flags.u) {
    offsetted_base += offset;
  } else {
    offsetted_base -= offset;
  }

  u32 addr;
  if constexpr (flags.p) {
    addr = offsetted_base;
  } else {
    addr = base;
  }

  if constexpr (not flags.p or flags.w) {
    cpu.write_active_register(r_base, offsetted_base);
  }

  if constexpr (flags.l) {
    u32 data{};

    // Unsigned Halfword
    if constexpr (not flags.s and flags.h) {
      data = cpu.bus->read(16, addr);
    }

    // Signed Byte
    else if constexpr (flags.s and not flags.h) {
      const auto raw{static_cast<i8>(cpu.bus->read(8, addr))};
      data = static_cast<u32>(static_cast<i32>(raw));
    }

    // Signed Halfword
    else if constexpr (flags.s and flags.h) {
      if (addr & 1u) {
        const auto raw{static_cast<i8>(cpu.bus->read(8, addr))};
        data = static_cast<u32>(static_cast<i32>(raw));
      } else {
        const auto raw{static_cast<i16>(cpu.bus->read(16, addr))};
        data = static_cast<u32>(static_cast<i32>(raw));
      }
    }

    cpu.write_active_register(src_dst, data);
  }

  else {
    // Store
    u32 store_data{cpu.read_active_register(src_dst)};

    const bool is_pc{src_dst == pc};
    if (is_pc) {
      store_data += 4; // PC + 8 + 4 = PC + 12
    }

    cpu.bus->write(16, addr, store_data & 0xFFFFu);
  }
}

}; // namespace neogba::arm_half

namespace neogba::arm_halfreg {
typedef arm_half::half_tflags halfreg_tflags;
template <halfreg_tflags flags> auto halfreg(arm7tdmi& cpu, u32 inst) -> void {
  arm_half::half<flags, false>(cpu, inst);
}
}; // namespace neogba::arm_halfreg

namespace neogba::arm_halfimm {
typedef arm_half::half_tflags halfimm_tflags;
template <halfimm_tflags flags> auto halfimm(arm7tdmi& cpu, u32 inst) -> void {
  arm_half::half<flags, true>(cpu, inst);
}
}; // namespace neogba::arm_halfimm
