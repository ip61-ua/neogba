#include "neogba/arm7tdmi/registers.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;

void Registers::set(u32 mask, u32* dst) {
  *dst = mask | *dst;
}

void Registers::clear(u32 mask, u32* dst) {
  *dst = ~mask & *dst;
}

constexpr bool Registers::isSet(u32 mask, u32 dst) const {
  return mask & dst;
}

constexpr u32 Registers::read(int reg) const {
  return regs[mapCurrent[reg]];
}

void Registers::write(int reg, u32 val) {
  regs[mapCurrent[reg]] = val;
}

constexpr u32 Registers::read(enum RegistersIndex idx) const {
  return regs[idx];
}

void Registers::write(enum RegistersIndex idx, u32 val) {
  regs[idx] = val;
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

constexpr bool Registers::isN() const {
  return isSet(MASK_N, read(RegistersIndex::cpsr));
}
void Registers::setN() {}
void Registers::clearN() {}
constexpr bool Registers::isZ() const {
  return isSet(MASK_Z, read(RegistersIndex::cpsr));
}
void Registers::setZ() {}
void Registers::clearZ() {}
constexpr bool Registers::isC() const {
  return isSet(MASK_C, read(RegistersIndex::cpsr));
}
void Registers::setC() {}
void Registers::clearC() {}
constexpr bool Registers::isV() const {
  return isSet(MASK_V, read(RegistersIndex::cpsr));
}
void Registers::setV() {}
void Registers::clearV() {}
constexpr bool Registers::isI() const {
  return isSet(MASK_I, read(RegistersIndex::cpsr));
}
void Registers::setI() {}
void Registers::clearI() {}
constexpr bool Registers::isF() const {
  return isSet(MASK_F, read(RegistersIndex::cpsr));
}
void Registers::setF() {}
void Registers::clearF() {}
constexpr bool Registers::isT() const {
  return isSet(MASK_T, read(RegistersIndex::cpsr));
}
void Registers::setT() {}
void Registers::clearT() {}

constexpr OperationModeBits Registers::getOperationMode() const {
  return OperationModeBits(regs[cpsr] & MASK_M);
}
