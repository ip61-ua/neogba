#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include "neogba/arm7tdmi/isa/include.hpp"
#include <functional>

using namespace neogba;

void arm7tdmi::set_mode(u8 mode, bool update_cpsr) {
  u8 idx_lut = get_idx_registers_preset_by_mode(mode);

  active_registers = register_presets::all[idx_lut];

  if (!update_cpsr)
    return;

  set_cpsr(M::mask, mode);
}

bool arm7tdmi::ckeck_arm_condition(u32 instruction) const {
  using namespace arm_cond;
  auto cond = static_cast<cond_enum>(COND::get(instruction));

  switch (cond) {
  case cond_enum::EQ:
    return is_cpsr(Z::mask, Z::H);
  case cond_enum::NE:
    return is_cpsr(Z::mask, 0);
  case cond_enum::HSCS:
    return is_cpsr(C::mask, C::H);
  case cond_enum::LOCC:
    return is_cpsr(C::mask, 0);
  case cond_enum::MI:
    return is_cpsr(N::mask, N::H);
  case cond_enum::PL:
    return is_cpsr(N::mask, 0);
  case cond_enum::VS:
    return is_cpsr(V::mask, V::H);
  case cond_enum::VC:
    return is_cpsr(V::mask, 0);
  case cond_enum::HI:
    return is_cpsr(C::mask | Z::mask, C::H);
  case cond_enum::LS:
    return is_cpsr(C::mask, 0) || is_cpsr(Z::mask, Z::H);
  case cond_enum::GE:
    return is_cpsr(N::mask, N::H) == is_cpsr(V::mask, V::H);
  case cond_enum::LT:
    return is_cpsr(N::mask, N::H) != is_cpsr(V::mask, V::H);
  case cond_enum::GT:
    return is_cpsr(Z::mask, 0) && (is_cpsr(N::mask, N::H) == is_cpsr(V::mask, V::H));
  case cond_enum::LE:
    return is_cpsr(Z::mask, Z::H) || (is_cpsr(N::mask, N::H) != is_cpsr(V::mask, V::H));
  case cond_enum::AL:
    return true;
  case cond_enum::NV:
  default:
    return false;
  };
};

void arm7tdmi::empty_registers() { registers.fill(0); }

void arm7tdmi::reset() {
  empty_registers();
  write_cpsr(I::H | F::H);
  set_mode(modes::svc);
  set_arm_mode();
  write_raw_register(pc, exceptions::reset);
}

void arm7tdmi::set_arm_mode() {
  instruction_size = 32;
  instruction_incrementator = 4;
  execute = execute_arm;
  clear_cpsr(T::H);
}

void arm7tdmi::set_thumb_mode() {
  instruction_size = 16;
  instruction_incrementator = 2;
  execute = execute_thumb;
  set_cpsr(T::mask, T::H);
}

void arm7tdmi::step() {
  auto current_pc{read_raw_register(pc)};

  auto inst{bus->read(instruction_size, current_pc)};
  write_pc(current_pc + instruction_incrementator);

  std::invoke(execute, *this, inst);
}
