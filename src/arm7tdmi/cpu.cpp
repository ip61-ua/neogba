#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <cstring>

u32 ARM7TDMI_CPU::read_active_register(u8 reg) const {
  return this->registers[this->active_registers[reg]];
}

void ARM7TDMI_CPU::write_active_register(u8 reg, u32 content) {
  this->registers[this->active_registers[reg]] = content;
}

bool ARM7TDMI_CPU::is_cpsr_bits(u32 mask, u32 bits) const {
  return (this->registers[cpsr] & mask) == bits;
}

void ARM7TDMI_CPU::clear_cpsr_bits(u32 mask) { this->registers[cpsr] &= ~mask; }

void ARM7TDMI_CPU::set_cpsr_bits(u32 mask, u32 bits) {
  this->registers[cpsr] &= ~mask;
  this->registers[cpsr] |= bits;
}

bool ARM7TDMI_CPU::is_mode(u8 mode) const {
  return (this->registers[cpsr] & ARM7TDMI_CPU_MASK_MODE_BITS) == mode;
}

u8 ARM7TDMI_CPU::get_idx_registers_lut_by_mode(u8 mode) {
  u8 idx_lut = 0;

  switch (mode) {
  case ARM7TDMI_CPU_MODE_USR:
  case ARM7TDMI_CPU_MODE_SYS:
    break;
  case ARM7TDMI_CPU_MODE_FIQ:
    idx_lut = 1;
    break;
  case ARM7TDMI_CPU_MODE_IRQ:
    idx_lut = 2;
    break;
  case ARM7TDMI_CPU_MODE_SVC:
    idx_lut = 3;
    break;
  case ARM7TDMI_CPU_MODE_ABT:
    idx_lut = 4;
    break;
  case ARM7TDMI_CPU_MODE_UND:
    idx_lut = 5;
    break;
  default:
    break;
  }
  return idx_lut;
}

void ARM7TDMI_CPU::set_mode(u8 mode, bool update_cpsr) {
  u8 idx_lut = get_idx_registers_lut_by_mode(mode);

  std::memcpy(active_registers, REGISTERS_LUT[idx_lut],
              ARM7TDMI_CPU_REGISTERS_ACTIVE);

  if (!update_cpsr)
    return;

  this->registers[cpsr] &= ~ARM7TDMI_CPU_MASK_MODE_BITS;
  this->registers[cpsr] |= mode & ARM7TDMI_CPU_MASK_MODE_BITS;
}

bool ARM7TDMI_CPU::ckeck_arm_condition(u32 inst) const {
  auto cond = isa_get_ARM_COND(inst);

  switch (cond) {

  case ARM_COND_EQ:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_ZERO, ARM7TDMI_CPU_MASK_ZERO);

  case ARM_COND_NE:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_ZERO, 0);

  case ARM_COND_HSCS:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_CARRY, ARM7TDMI_CPU_MASK_CARRY);

  case ARM_COND_LOCC:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_CARRY, 0);

  case ARM_COND_PL:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE,
                              ARM7TDMI_CPU_MASK_NEGATIVE);

  case ARM_COND_MI:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE, 0);

  case ARM_COND_VS:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE,
                              ARM7TDMI_CPU_MASK_NEGATIVE);

  case ARM_COND_VC:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE, 0);

  default:
    return false;
  }
}

void ARM7TDMI_CPU::empty_registers() {
  std::memset(this->registers, 0, sizeof(registers));
}

void ARM7TDMI_CPU::reset() {
  this->empty_registers();
  this->write_cpsr(ARM7TDMI_CPU_MASK_IRQDISABLE | ARM7TDMI_CPU_MASK_FIQDISABLE);
  this->set_mode(ARM7TDMI_CPU_MODE_SVC);
  this->write_pc(ARM7TDMI_CPU_EXCEPTION_RESET);
}
