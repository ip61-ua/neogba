#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"

namespace neogba {

template <bool i, bool p, bool u, bool b, bool w, bool l, bool rd_pc = false>
void arm_singletrans_generator(arm7tdmi& cpu, u32 inst) {
  const auto r_base{ISA_ARM_SINGLETRANS_RN::get(inst)}, src_dst{ISA_ARM_SINGLETRANS_RD::get(inst)};

  constexpr u32 offset{i ? arm_fsr_operand2_lut.invoke(inst, cpu, inst).result
                         : ISA_ARM_SINGLETRANS_OFFSET::get(inst)};

  const u32 base{cpu.read_active_register(r_base)};
  constexpr u32 offsetted_base{u ? base + offset : base - offset};
  constexpr u32 addr{p ? offsetted_base : base};
  constexpr u32 n_bits{b ? 8 : 32};

  if constexpr (!p || w) {
    cpu.write_active_register(r_base, offsetted_base);
  }

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
  } else {
    u32 data = cpu.read_active_register(src_dst);
    if constexpr (rd_pc) {
      data += 4; // 8 + 4 -> 12!
    }

    cpu.bus->write(n_bits, addr, data);
  }
}

} // namespace neogba
