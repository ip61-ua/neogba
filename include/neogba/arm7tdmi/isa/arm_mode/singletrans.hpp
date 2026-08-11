#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp" // lol

namespace neogba {

template <bool i, bool p, bool u, bool b, bool w, bool l, bool rd_pc = false>
void arm_singletrans_generator(arm7tdmi& cpu, u32 inst) {
  const auto r_base{ISA_ARM_SINGLETRANS_RN::get(inst)}, src_dst{ISA_ARM_SINGLETRANS_RD::get(inst)};

  u32 offset;
  if constexpr (i) {
    offset = arm_fsr_operand2_lut.invoke(inst, cpu, inst).result;
  } else {
    offset = ISA_ARM_SINGLETRANS_OFFSET::get(inst);
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

} // namespace neogba
