#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"

namespace neogba::arm_singletrans {

template <bool i = false, bool p = false, bool u = false, bool b = false, bool w = false,
          bool l = false, bool rd_pc = false>
void generator(arm7tdmi& cpu, u32 inst) {
  const auto r_base{RN::get(inst)}, src_dst{RD::get(inst)};

  u32 offset;
  if constexpr (i) {
    offset = arm_operand2::table.invoke(inst, cpu, inst).result;
  } else {
    offset = OFFSET::get(inst);
  }

  const u32 base{cpu.read_active_register(r_base)};
  u32 offsetted_base;
  if constexpr (u) {
    offsetted_base = base + offset;
  } else {
    offsetted_base = base - offset;
  }

  u32 addr;
  if constexpr (p) {
    addr = offsetted_base;
  } else {
    addr = base;
  }

  constexpr u32 n_bits{b ? 8 : 32};

  // write
  u32 store_data;
  if constexpr (!l) {
    store_data = cpu.read_active_register(src_dst);
    if constexpr (rd_pc) {
      store_data += 4; // PC + 8 + 4 = 12!
    }
  }

  // wb
  if constexpr (!p || w) {
    cpu.write_active_register(r_base, offsetted_base);
  }

  // load
  if constexpr (l) {
    u32 data{cpu.bus->read(n_bits, addr)};

    if constexpr (!b) { // LDR (Word)
      data = std::rotr(data, (addr & 3) * 8);
    }

    if constexpr (rd_pc) {
      cpu.write_pc(data);
    } else {
      cpu.write_active_register(src_dst, data);
    }
  }

  // write
  if constexpr (!l) {
    cpu.bus->write(n_bits, addr, store_data);
  }
}

inline constexpr auto

    arm_singletrans_i0_p0_u0_b0_w0_l0_rdpc0{generator<>},
    arm_singletrans_i1_p0_u0_b0_w0_l0_rdpc0{generator<true>},
    arm_singletrans_i0_p1_u0_b0_w0_l0_rdpc0{generator<false, true>};

} // namespace neogba::arm_singletrans
