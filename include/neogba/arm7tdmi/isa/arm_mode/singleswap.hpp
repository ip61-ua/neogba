#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"

namespace neogba::arm_singleswap {

struct singleswap_tflags {
  bool b : 1 {false};
};

template <singleswap_tflags flags> auto singleswap(arm7tdmi& cpu, u32 inst) -> void {
  const auto rd{RD::get(inst)}, //
      rn{RN::get(inst)},        //
      rm{RM::get(inst)};

  constexpr auto n_bits{flags.b ? 8 : 32};

  const u32 rn_contents{cpu.read_active_register(rn)}, //
      rm_contents{cpu.read_active_register(rm)},       //
      temp{cpu.bus->read(n_bits, rn_contents)};

  // rd <- mem[rn]
  cpu.write_active_register(rd, temp);

  // mem[rn] <- rm
  cpu.bus->write(n_bits, rn_contents, rm_contents);
};
} // namespace neogba::arm_singleswap
