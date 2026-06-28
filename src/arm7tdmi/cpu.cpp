#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <cstring>

using namespace neogba;

void arm7tdmi::set_mode(cpsr_mode mode, bool update_cpsr) {
  u8 idx_lut = 0; // get_idx_registers_lut_by_mode(mode);

  std::memcpy(active_registers, REGISTERS_LUT[idx_lut], ARM7TDMI_CPU_REGISTERS_ACTIVE);

  if (!update_cpsr)
    return;

  this->registers[cpsr] &= ~ARM7TDMI_CPU_MASK_MODE_BITS;
  this->registers[cpsr] |= mode & ARM7TDMI_CPU_MASK_MODE_BITS;
}

bool arm7tdmi::ckeck_arm_condition(u32 inst) const {
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
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE, ARM7TDMI_CPU_MASK_NEGATIVE);

  case ARM_COND_MI:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE, 0);

  case ARM_COND_VS:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE, ARM7TDMI_CPU_MASK_NEGATIVE);

  case ARM_COND_VC:
    return this->is_cpsr_bits(ARM7TDMI_CPU_MASK_NEGATIVE, 0);

  default:
    return false;
  }
}

void arm7tdmi::empty_registers() { std::memset(this->registers, 0, sizeof(registers)); }

void arm7tdmi::reset() {
  this->empty_registers();
  this->write_cpsr(ARM7TDMI_CPU_MASK_IRQDISABLE | ARM7TDMI_CPU_MASK_FIQDISABLE);
  this->set_mode(ARM7TDMI_CPU_MODE_SVC);
  this->write_pc(ARM7TDMI_CPU_EXCEPTION_RESET);
}
