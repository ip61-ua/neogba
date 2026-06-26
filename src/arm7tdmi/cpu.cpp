#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <cstring>

bool ARM7TDMI_CPU::is_cpsr_bits(u32 bits) {
  return (this->registers[cpsr] & bits) == bits;
}

void ARM7TDMI_CPU::clear_cpsr_bits(u32 bits) { this->registers[cpsr] &= ~bits; }

void ARM7TDMI_CPU::set_cpsr_bits(u32 bits) {
  this->registers[cpsr] &= ~bits;
  this->registers[cpsr] |= bits;
}

bool ARM7TDMI_CPU::is_mode(u8 mode) {
  return (this->registers[cpsr] & ARM7TDMI_CPU_MASK_MODE_BITS) == mode;
}

void ARM7TDMI_CPU::set_mode(u8 mode, bool update_active_registers) {
  this->registers[cpsr] &= ~ARM7TDMI_CPU_MASK_MODE_BITS;
  this->registers[cpsr] |= mode & ARM7TDMI_CPU_MASK_MODE_BITS;

  if (!update_active_registers)
    return;

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

  std::memcpy(active_registers, REGISTERS_LUT[idx_lut],
              ARM7TDMI_CPU_REGISTERS_ACTIVE);
}

void ARM7TDMI_CPU::reset() {
  std::memset(this->registers, 0, sizeof(registers));

  this->registers[cpsr] = ARM7TDMI_CPU_MODE_SVC | ARM7TDMI_CPU_MASK_IRQDISABLE |
                          ARM7TDMI_CPU_MASK_FIQDISABLE;

  this->registers[pc] = ARM7TDMI_CPU_EXCEPTION_RESET;
}
