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
  case COND_EQ:
    return is_cpsr(Z, Z);
  case COND_NE:
    return is_cpsr(Z, 0);
  case COND_HSCS:
    return is_cpsr(C, C);
  case COND_LOCC:
    return is_cpsr(C, 0);
  case COND_MI:
    return is_cpsr(N, N);
  case COND_PL:
    return is_cpsr(N, 0);
  case COND_VS:
    return is_cpsr(V, V);
  case COND_VC:
    return is_cpsr(V, 0);
  case COND_HI:
    return is_cpsr(C | Z, C);
  case COND_LS:
    return is_cpsr(C, 0) || is_cpsr(Z, Z);
  case COND_GE:
    return is_cpsr(N, N) == is_cpsr(V, V);
  case COND_LT:
    return is_cpsr(N, N) != is_cpsr(V, V);
  case COND_GT:
    return is_cpsr(Z, 0) && (is_cpsr(N, N) == is_cpsr(V, V));
  case COND_LE:
    return is_cpsr(Z, Z) || (is_cpsr(N, N) != is_cpsr(V, V));
  case COND_AL:
    return true;
  case COND_NV:
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
