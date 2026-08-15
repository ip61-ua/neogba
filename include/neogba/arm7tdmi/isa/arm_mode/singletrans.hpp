#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"

namespace neogba::arm_singletrans {

struct singletrans_tflags {
  bool i : 1 {false};
  bool p : 1 {false};
  bool u : 1 {false};
  bool b : 1 {false};
  bool w : 1 {false};
  bool l : 1 {false};
};

template <singletrans_tflags flags> void singletrans(arm7tdmi& cpu, u32 inst) {
  const auto r_base{RN::get(inst)}, src_dst{RD::get(inst)};

  u32 offset;
  if constexpr (flags.i) {
    offset = arm_operand2::operand2_table.invoke(I::set0(inst), cpu, inst).result;
  } else {
    offset = OFFSET::get(inst);
  }

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

  constexpr u32 n_bits{flags.b ? 8 : 32};
  const bool is_pc{src_dst == pc};

  // write
  u32 store_data;
  if constexpr (not flags.l) {
    store_data = cpu.read_active_register(src_dst);
    if (is_pc) {
      store_data += 4; // PC + 8 + 4 = 12!
    }
  }

  // wb
  if constexpr (not flags.p or flags.w) {
    cpu.write_active_register(r_base, offsetted_base);
  }

  // load
  if constexpr (flags.l) {
    u32 data{cpu.bus->read(n_bits, addr)};

    if constexpr (not flags.b) { // LDR (Word)
      data = std::rotr(data, (addr & 3) * 8);
    }

    if (is_pc) {
      cpu.write_pc(data);
    } else {
      cpu.write_active_register(src_dst, data);
    }
  }

  // write
  if constexpr (not flags.l) {
    cpu.bus->write(n_bits, addr, store_data);
  }
}

} // namespace neogba::arm_singletrans
