#include "neogba/arm7tdmi/registers.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;

void Registers::set(u32 mask, u32* dst) {
  *dst = mask | *dst;
}

void Registers::clear(u32 mask, u32* dst) {
  *dst = ~mask & *dst;
}

bool Registers::isSet(u32 mask, u32 dst) {
  return mask & dst;
}

u32 Registers::read(int reg) {
  return regs[mapCurrent[reg]];
}

void Registers::write(int reg, u32 val) {
  regs[mapCurrent[reg]] = val;
}

u32 Registers::read(enum RegistersIndex idx) {
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

bool Registers::isN() {
  return isSet(MASK_N, read(RegistersIndex::cpsr));
}
void Registers::setN() {
  set(MASK_N, &regs[RegistersIndex::cpsr]);
}
void Registers::clearN() {
  clear(MASK_N, &regs[RegistersIndex::cpsr]);
}
bool Registers::isZ() {
  return isSet(MASK_Z, read(RegistersIndex::cpsr));
}
void Registers::setZ() {
  set(MASK_Z, &regs[RegistersIndex::cpsr]);
}
void Registers::clearZ() {
  clear(MASK_Z, &regs[RegistersIndex::cpsr]);
}
bool Registers::isC() {
  return isSet(MASK_C, read(RegistersIndex::cpsr));
}
void Registers::setC() {
  set(MASK_C, &regs[RegistersIndex::cpsr]);
}
void Registers::clearC() {
  clear(MASK_C, &regs[RegistersIndex::cpsr]);
}
bool Registers::isV() {
  return isSet(MASK_V, read(RegistersIndex::cpsr));
}
void Registers::setV() {
  set(MASK_V, &regs[RegistersIndex::cpsr]);
}
void Registers::clearV() {
  clear(MASK_V, &regs[RegistersIndex::cpsr]);
}
bool Registers::isI() {
  return isSet(MASK_I, read(RegistersIndex::cpsr));
}
void Registers::setI() {
  set(MASK_I, &regs[RegistersIndex::cpsr]);
}
void Registers::clearI() {
  clear(MASK_I, &regs[RegistersIndex::cpsr]);
}
bool Registers::isF() {
  return isSet(MASK_F, read(RegistersIndex::cpsr));
}
void Registers::setF() {
  set(MASK_F, &regs[RegistersIndex::cpsr]);
}
void Registers::clearF() {
  clear(MASK_F, &regs[RegistersIndex::cpsr]);
}
bool Registers::isT() {
  return isSet(MASK_T, read(RegistersIndex::cpsr));
}
void Registers::setT() {
  set(MASK_T, &regs[RegistersIndex::cpsr]);
}
void Registers::clearT() {
  clear(MASK_T, &regs[RegistersIndex::cpsr]);
}

OperationModeBits Registers::getOperationMode() {
  return OperationModeBits(regs[cpsr] & MASK_M);
}
