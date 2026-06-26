#include "neogba/arm7tdmi/cpu.hpp"
#include <cstring>

u8 ARM7TDMI_CPU::convert_mode_register(u8 idx) {
  auto idx_adapted = idx;

  if (this->is_mode(ARM7TDMI_CPU_MODE_USR) ||
      this->is_mode(ARM7TDMI_CPU_MODE_SYS) || idx == cpsr || idx == pc)
    return idx_adapted;

  if (this->is_mode(ARM7TDMI_CPU_MODE_FIQ) && idx >= 8)
    return r8_fiq + idx_adapted - 8;

  if (idx < 13)
    return idx_adapted;

  if (this->is_mode(ARM7TDMI_CPU_MODE_SVC))
    return r13_svc + idx_adapted;

  if (this->is_mode(ARM7TDMI_CPU_MODE_ABT))
    return r13_abt + idx_adapted;

  if (this->is_mode(ARM7TDMI_CPU_MODE_IRQ))
    return r13_irq + idx_adapted;

  if (this->is_mode(ARM7TDMI_CPU_MODE_UND))
    return r13_und + idx_adapted;

  return -1;
}

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

void ARM7TDMI_CPU::set_mode(u8 mode) {
  this->registers[cpsr] &= ~ARM7TDMI_CPU_MASK_MODE_BITS;
  this->registers[cpsr] |= mode & ARM7TDMI_CPU_MASK_MODE_BITS;
}

void ARM7TDMI_CPU::reset() {
  std::memset(this->registers, 0, sizeof(registers));

  this->registers[cpsr] = ARM7TDMI_CPU_MODE_SVC | ARM7TDMI_CPU_MASK_IRQDISABLE |
                          ARM7TDMI_CPU_MASK_FIQDISABLE;

  this->registers[pc] = ARM7TDMI_CPU_EXCEPTION_RESET;
}
