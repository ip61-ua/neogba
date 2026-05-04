#include "neogba/arm7tdmi/registers.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;

Registers::Registers() {
  for (u8 i = 0; i < totalRegisters; ++i)
    regs[i] = 0;
}

Registers::Registers(Registers const& registers) {
  for (u8 i = 0; i < totalRegisters; ++i)
    regs[i] = registers.regs[i];
}

void Registers::setUser() {
  mapCurrent = mapUser;
  clear(MASK_M, &regs[RegistersIndex::cpsr]);
  set(OperationModeBits::User, &regs[RegistersIndex::cpsr]);
}
void Registers::setFiq() {
  mapCurrent = mapFiq;
  clear(MASK_M, &regs[RegistersIndex::cpsr]);
  set(OperationModeBits::Fiq, &regs[RegistersIndex::cpsr]);
}
void Registers::setAbt() {
  mapCurrent = mapAbt;
  clear(MASK_M, &regs[RegistersIndex::cpsr]);
  set(OperationModeBits::Abt, &regs[RegistersIndex::cpsr]);
}
void Registers::setIrq() {
  mapCurrent = mapIrq;
  clear(MASK_M, &regs[RegistersIndex::cpsr]);
  set(OperationModeBits::Irq, &regs[RegistersIndex::cpsr]);
}
void Registers::setUnd() {
  mapCurrent = mapUnd;
  clear(MASK_M, &regs[RegistersIndex::cpsr]);
  set(OperationModeBits::Und, &regs[RegistersIndex::cpsr]);
}
void Registers::setSvc() {
  mapCurrent = mapSvc;
  clear(MASK_M, &regs[RegistersIndex::cpsr]);
  set(OperationModeBits::Svc, &regs[RegistersIndex::cpsr]);
}

bool Registers::equals(Registers const& other) const {
  for (u8 i = 0; i < totalRegisters; ++i)
    if (other.regs[i] != regs[i])
      return false;

  return true;
}
