#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"

namespace neogba::arm_blocktrans {

struct blocktrans_tflags {
  bool p : 1 {false};
  bool u : 1 {false};
  bool s : 1 {false};
  bool w : 1 {false};
  bool l : 1 {false};
  bool zeros_4_to_7 : 1 {false};
};

template <blocktrans_tflags flags> void blocktrans(arm7tdmi& cpu, u32 inst) {
  const auto rn{RN::get(inst)};
  auto base{cpu.read_active_register(rn)};

  auto registerlist{REGLIST::get(inst)};

  bool is_empty_list;
  if constexpr (flags.zeros_4_to_7)
    is_empty_list = registerlist == 0;
  else
    is_empty_list = false;

  u32 num_regs{static_cast<u32>(std::popcount(registerlist))};
  if constexpr (flags.zeros_4_to_7) {
    if (is_empty_list) {
      num_regs = 16;
      registerlist = 1 << 15;
    }
  }

  const auto total_size{num_regs * 4}, wb_addr{flags.u ? (base + total_size) : (base - total_size)},
      first_reg{static_cast<u32>(std::countr_zero(registerlist))};
  auto start_addr{base};

  if constexpr (flags.u) {
    if constexpr (flags.p) {
      start_addr += 4;
    }
  } else {
    if constexpr (flags.p) {
      start_addr = base - total_size;
    } else {
      start_addr = base - total_size + 4;
    }
  }

  auto current_addr{start_addr};

  const auto is_restore_cpsr{flags.s && flags.l && (registerlist & (1 << 15))},
      is_user_bank{flags.s && !is_restore_cpsr};

  for (auto reg{0}; reg < 16; ++reg) {
    if ((registerlist & (1u << reg)) == 0)
      continue;

    if constexpr (flags.l) {
      const u32 data{cpu.bus->read(32, current_addr)};

      if (is_user_bank)
        cpu.write_relative_register(reg, data, arm7tdmi::REGISTERS_PRESET_USR);
      else if (reg == 15)
        cpu.write_pc(data);
      else
        cpu.write_active_register(reg, data);

    } else {

      // STORE (STM)
      u32 data;
      if (is_user_bank)
        data = cpu.read_relative_register(reg, arm7tdmi::REGISTERS_PRESET_USR);
      else if (reg == 15)
        data = cpu.read_pc() + 4;
      else if constexpr (flags.w)
        data = (reg == rn) ? ((reg == first_reg) ? base : wb_addr) : cpu.read_active_register(reg);
      else
        data = cpu.read_active_register(reg);

      cpu.bus->write(32, current_addr, data);
    }

    current_addr += 4;
  }

  if (is_restore_cpsr)
    cpu.restore_cpsr();

  // Write-Back (WB)
  if constexpr (flags.w) {
    if constexpr (flags.l) {
      if ((registerlist & (1u << rn)) == 0) {
        cpu.write_active_register(rn, wb_addr);
      }
    } else {
      cpu.write_active_register(rn, wb_addr);
    }
  }
}

} // namespace neogba::arm_blocktrans
