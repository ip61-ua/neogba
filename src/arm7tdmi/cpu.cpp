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
  auto cond = static_cast<arm_cond>(ISA_ARM_COND::get(instruction)); // lol

  switch (cond) {
  case arm_cond::EQ:
    return this->is_cpsr(Z, Z);
  case arm_cond::NE:
    return this->is_cpsr(Z, 0);
  case arm_cond::HSCS:
    return this->is_cpsr(C, C);
  case arm_cond::LOCC:
    return this->is_cpsr(C, 0);
  case arm_cond::MI:
    return this->is_cpsr(N, N);
  case arm_cond::PL:
    return this->is_cpsr(N, 0);
  case arm_cond::VS:
    return this->is_cpsr(V, V);
  case arm_cond::VC:
    return this->is_cpsr(V, 0);
  case arm_cond::HI:
    return this->is_cpsr(C | Z, C);
  case arm_cond::LS:
    return this->is_cpsr(C, 0) || this->is_cpsr(Z, Z);
  case arm_cond::GE:
    return this->is_cpsr(N, N) == this->is_cpsr(V, V);
  case arm_cond::LT:
    return this->is_cpsr(N, N) != this->is_cpsr(V, V);
  case arm_cond::GT:
    return this->is_cpsr(Z, 0) && (this->is_cpsr(N, N) == this->is_cpsr(V, V));
  case arm_cond::LE:
    return this->is_cpsr(Z, Z) || (this->is_cpsr(N, N) != this->is_cpsr(V, V));
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
