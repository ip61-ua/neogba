#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include "neogba/arm7tdmi/isa/include.hpp"
#include <functional>

using namespace neogba;

void arm7tdmi::set_mode(u8 mode, bool update_cpsr) {
  u8 idx_lut = this->get_idx_registers_preset_by_mode(mode);

  this->active_registers = this->REGISTERS_PRESET[idx_lut];

  if (!update_cpsr)
    return;

  this->set_cpsr(M, mode);
}

bool arm7tdmi::ckeck_arm_condition(u32 instruction) const {
  using namespace arm_cond;
  auto cond = static_cast<cond_enum>(COND::get(instruction)); // lol

  switch (cond) {
  case cond_enum::EQ:
    return this->is_cpsr(Z, Z);
  case cond_enum::NE:
    return this->is_cpsr(Z, 0);
  case cond_enum::HSCS:
    return this->is_cpsr(C, C);
  case cond_enum::LOCC:
    return this->is_cpsr(C, 0);
  case cond_enum::MI:
    return this->is_cpsr(N, N);
  case cond_enum::PL:
    return this->is_cpsr(N, 0);
  case cond_enum::VS:
    return this->is_cpsr(V, V);
  case cond_enum::VC:
    return this->is_cpsr(V, 0);
  case cond_enum::HI:
    return this->is_cpsr(C | Z, C);
  case cond_enum::LS:
    return this->is_cpsr(C, 0) || this->is_cpsr(Z, Z);
  case cond_enum::GE:
    return this->is_cpsr(N, N) == this->is_cpsr(V, V);
  case cond_enum::LT:
    return this->is_cpsr(N, N) != this->is_cpsr(V, V);
  case cond_enum::GT:
    return this->is_cpsr(Z, 0) && (this->is_cpsr(N, N) == this->is_cpsr(V, V));
  case cond_enum::LE:
    return this->is_cpsr(Z, Z) || (this->is_cpsr(N, N) != this->is_cpsr(V, V));
  case cond_enum::AL:
    return true;
  case cond_enum::NV:
  default:
    return false;
  };
};

void arm7tdmi::empty_registers() { this->registers.fill(0); }

void arm7tdmi::reset() {
  this->empty_registers();
  this->write_cpsr(I | F);
  this->set_mode(MODE_SVC);
  this->set_arm_mode();
  this->write_raw_register(pc, EXCEPTION_RESET);
}

void arm7tdmi::set_arm_mode() {
  this->instruction_size = 32;
  this->instruction_incrementator = 4;
  this->execute = execute_arm;
  this->clear_cpsr(T);
}

void arm7tdmi::set_thumb_mode() {
  this->instruction_size = 16;
  this->instruction_incrementator = 2;
  this->execute = execute_thumb;
  this->set_cpsr(T, T);
}

void arm7tdmi::step() {
  auto current_pc{this->read_raw_register(pc)};

  auto inst{this->bus->read(this->instruction_size, current_pc)};
  this->write_pc(current_pc + this->instruction_incrementator);

  std::invoke(this->execute, *this, inst);
}
