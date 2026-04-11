#include "arm7/registers.hpp"

neogba::u32 neogba::arm7tdmi::Registers::read(int reg) const {
  return regs[mapCurrent[reg]];
}

void neogba::arm7tdmi::Registers::write(int reg, u32 val) {
  regs[mapCurrent[reg]] = val;
}

neogba::u32 neogba::arm7tdmi::Registers::read(enum RegistersIndex idx) const {
  return regs[idx];
}

void neogba::arm7tdmi::Registers::write(enum RegistersIndex idx, u32 val) {
  regs[idx] = val;
}

void neogba::arm7tdmi::Registers::setUser() {
  mapCurrent = mapUser;
}
void neogba::arm7tdmi::Registers::setFiq() {
  mapCurrent = mapFiq;
}
void neogba::arm7tdmi::Registers::setAbt() {
  mapCurrent = mapAbt;
}
void neogba::arm7tdmi::Registers::setIrq() {
  mapCurrent = mapIrq;
}
void neogba::arm7tdmi::Registers::setUnd() {
  mapCurrent = mapUnd;
}
void neogba::arm7tdmi::Registers::setSvc() {
  mapCurrent = mapSvc;
}
