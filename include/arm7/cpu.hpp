#pragma once
#include <cstdint>

namespace neogba::arm7tdmi {

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

struct Registers {
  u32 r0, r1, r2, r3, r4, r5, r6, r7, pc, cpsr;
  u32 r8, r9, r10, r11, r12;
  u32 r13, r14;
  u32 r8_fiq, r9_fiq, r10_fiq, r11_fiq, r12_fiq;
  u32 r13_fiq, r14_fiq, spsr_fiq;
  u32 r13_svc, r14_svc, spsr_svc;
  u32 r13_abt, r14_abt, spsr_abt;
  u32 r13_irq, r14_irq, spsr_irq;
  u32 r13_und, r14_und, spsr_und;

  u32* user[17] = {&r0, &r1,  &r2,  &r3,  &r4,  &r5,  &r6, &r7,  &r8,
                   &r9, &r10, &r11, &r12, &r13, &r14, &pc, &cpsr};

  u32* fiq[18] = {&r0,     &r1,      &r2,      &r3,      &r4,      &r5,      &r6, &r7,   &r8_fiq,
                  &r9_fiq, &r10_fiq, &r11_fiq, &r12_fiq, &r13_fiq, &r14_fiq, &pc, &cpsr, &spsr_fiq};

  u32* svc[18] = {&r0, &r1,  &r2,  &r3,  &r4,      &r5,      &r6, &r7,   &r8,
                  &r9, &r10, &r11, &r12, &r13_svc, &r14_svc, &pc, &cpsr, &spsr_svc};

  u32* abt[18] = {&r0, &r1,  &r2,  &r3,  &r4,      &r5,      &r6, &r7,   &r8,
                  &r9, &r10, &r11, &r12, &r13_abt, &r14_abt, &pc, &cpsr, &spsr_abt};

  u32* irq[18] = {&r0, &r1,  &r2,  &r3,  &r4,      &r5,      &r6, &r7,   &r8,
                  &r9, &r10, &r11, &r12, &r13_irq, &r14_irq, &pc, &cpsr, &spsr_irq};

  u32* und[18] = {&r0, &r1,  &r2,  &r3,  &r4,      &r5,      &r6, &r7,   &r8,
                  &r9, &r10, &r11, &r12, &r13_und, &r14_und, &pc, &cpsr, &spsr_und};

  u32** current = user;
};

class CPU {
private:
public:
  CPU(const CPU&) = default;
  CPU(CPU&&) = default;
  CPU& operator=(const CPU&) = default;
  CPU& operator=(CPU&&) = default;

  u32 fetchArm();
  u16 fetchThumb();
  void execute();
  void step();
};

} // namespace neogba::arm7tdmi
