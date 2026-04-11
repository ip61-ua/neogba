#include "types.hpp"

namespace neogba::arm7tdmi {

enum RegistersIndex : u8 {
  r0,
  r1,
  r2,
  r3,
  r4,
  r5,
  r6,
  r7,
  pc,
  cpsr,
  r8,
  r9,
  r10,
  r11,
  r12,
  r13,
  r14,
  r8_fiq,
  r9_fiq,
  r10_fiq,
  r11_fiq,
  r12_fiq,
  r13_fiq,
  r14_fiq,
  spsr_fiq,
  r13_svc,
  r14_svc,
  spsr_svc,
  r13_abt,
  r14_abt,
  spsr_abt,
  r13_irq,
  r14_irq,
  spsr_irq,
  r13_und,
  r14_und,
  spsr_und,
};

struct Registers {
public:
  static constexpr u8 mapUser[17] = {r0, r1,  r2,  r3,  r4,  r5,  r6, r7,  r8,
                                     r9, r10, r11, r12, r13, r14, pc, cpsr},
                      mapFiq[18] = {r0,      r1,      r2,      r3,     r4,      r5,
                                    r6,      r7,      r8_fiq,  r9_fiq, r10_fiq, r11_fiq,
                                    r12_fiq, r13_fiq, r14_fiq, pc,     cpsr,    spsr_fiq},
                      mapSvc[18] = {r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                                    r9, r10, r11, r12, r13_svc, r14_svc, pc, cpsr, spsr_svc},
                      mapAbt[18] = {r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                                    r9, r10, r11, r12, r13_abt, r14_abt, pc, cpsr, spsr_abt},
                      mapIrq[18] = {r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                                    r9, r10, r11, r12, r13_irq, r14_irq, pc, cpsr, spsr_irq},
                      mapUnd[18] = {r0, r1,  r2,  r3,  r4,      r5,      r6, r7,   r8,
                                    r9, r10, r11, r12, r13_und, r14_und, pc, cpsr, spsr_und};

private:
  u32 regs[37];
  const u8* mapCurrent = mapUser;

public:
  u32 read(int reg) const {
    return regs[mapCurrent[reg]];
  }
  void write(int reg, u32 val) {
    regs[mapCurrent[reg]] = val;
  }
  u32 read(enum RegistersIndex idx) const {
    return regs[idx];
  }
  void write(enum RegistersIndex idx, u32 val) {
    regs[idx] = val;
  }

  void setUser() {
    mapCurrent = mapUser;
  }
  void setFiq() {
    mapCurrent = mapFiq;
  }
  void setAbt() {
    mapCurrent = mapAbt;
  }
  void setIrq() {
    mapCurrent = mapIrq;
  }
  void setUnd() {
    mapCurrent = mapUnd;
  }
  void setSvc() {
    mapCurrent = mapSvc;
  }
};

} // namespace neogba::arm7tdmi
