#include "neogba/arm7tdmi/cpu.hpp"
#include <cstring>

u8 ARMTDMI7_CPU::convert_mode_register(u8 idx) {
  auto idx_adapted = idx;

  if (this->is_mode(ARM7TDMI_CPU_MODE_USR) ||
      this->is_mode(ARM7TDMI_CPU_MODE_SYS) || idx == cpsr || idx == pc)
    return idx_adapted;

  if (this->is_mode(ARM7TDMI_CPU_MODE_FIQ) && idx >= 8)
    return r8_fiq + idx_adapted;

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

bool ARMTDMI7_CPU::is_thumb() {
  return (this->registers[cpsr] & ARM7TDMI_CPU_MASK_THUMB_BIT) != 0;
}

bool ARMTDMI7_CPU::is_mode(u8 mode) {
  return (this->registers[cpsr] & ARM7TDMI_CPU_MASK_MODE_BITS) == mode;
}

void ARMTDMI7_CPU::reset() {
  std::memset(this->registers, 0, sizeof(registers));

  this->registers[cpsr] = ARM7TDMI_CPU_MODE_SVC | ARM7TDMI_CPU_MASK_IRQDISABLE |
                          ARM7TDMI_CPU_MASK_FIQDISABLE;

  this->registers[pc] = ARM7TDMI_CPU_EXCEPTION_RESET;
}
