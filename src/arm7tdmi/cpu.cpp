#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"

using namespace neogba;

void arm7tdmi::set_mode(u8 mode, bool update_cpsr) {
  u8 idx_lut = get_idx_registers_preset_by_mode(mode);

  active_registers = REGISTERS_PRESET[idx_lut];

  if (!update_cpsr)
    return;

  set_cpsr(M, mode);
}

bool arm7tdmi::ckeck_arm_condition(u32 instruction) const {
  auto cond = static_cast<arm_cond>(ISA_ARM_COND::get(instruction)); // lol

  switch (cond) {
  case arm_cond::EQ:
    return is_cpsr(Z, Z);
  case arm_cond::NE:
    return is_cpsr(Z, 0);
  case arm_cond::HSCS:
    return is_cpsr(C, C);
  case arm_cond::LOCC:
    return is_cpsr(C, 0);
  case arm_cond::MI:
    return is_cpsr(N, N);
  case arm_cond::PL:
    return is_cpsr(N, 0);
  case arm_cond::VS:
    return is_cpsr(V, V);
  case arm_cond::VC:
    return is_cpsr(V, 0);
  case arm_cond::HI:
    return is_cpsr(C | Z, C);
  case arm_cond::LS:
    return is_cpsr(C, 0) || is_cpsr(Z, Z);
  case arm_cond::GE:
    return is_cpsr(N, N) == is_cpsr(V, V);
  case arm_cond::LT:
    return is_cpsr(N, N) != is_cpsr(V, V);
  case arm_cond::GT:
    return is_cpsr(Z, 0) && (is_cpsr(N, N) == is_cpsr(V, V));
  case arm_cond::LE:
    return is_cpsr(Z, Z) || (is_cpsr(N, N) != is_cpsr(V, V));
  case arm_cond::AL:
    return true;
  case arm_cond::NV:
  default:
    return false;
  };
};

void arm7tdmi::empty_registers() { this->registers.fill(0); }

void arm7tdmi::reset() {
  this->empty_registers();
  this->write_cpsr(I | F);
  this->set_mode(MODE_SVC);
  this->write_pc(EXCEPTION_RESET);
}
