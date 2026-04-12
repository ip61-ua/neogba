#include "neogba/types.hpp"

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

enum OperationModeBits : u32 {
  User = 0b10000,
  Fiq = 0b10001,
  Irq = 0b10010,
  Svc = 0b10011,
  Abt = 0b10111,
  Und = 0b11011,
  Sys = 0b11111
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
  void set(u32 mask, u32* dst);
  void clear(u32 mask, u32* dst);
  bool isSet(u32 mask, u32 dst) const;

public:
  static constexpr u32 MASK_N = 0x80000000, MASK_Z = 0x40000000, MASK_C = 0x20000000,
                       MASK_V = 0x10000000, MASK_I = 0x80, MASK_F = 0x40, MASK_T = 0x20,
                       MASK_M = 0x1F;

  u32 read(int reg) const;
  void write(int reg, u32 val);
  u32 read(enum RegistersIndex idx) const;
  void write(enum RegistersIndex idx, u32 val);

  void setUser();
  void setFiq();
  void setAbt();
  void setIrq();
  void setUnd();
  void setSvc();

  /// Negative or less than
  bool isN() const;
  void setN();
  void clearN();
  /// Zero
  bool isZ() const;
  void setZ();
  void clearZ();
  /// Carry or borrow or extend
  bool isC() const;
  void setC();
  void clearC();
  /// Overflow
  bool isV() const;
  void setV();
  void clearV();
  /// IRQ disable
  bool isI() const;
  void setI();
  void clearI();
  /// FIQ disable
  bool isF() const;
  void setF();
  void clearF();
  /// State bit
  bool isT() const;
  void setT();
  void clearT();
  /// Mode bits
  OperationModeBits getOperationMode();
};

} // namespace neogba::arm7tdmi
