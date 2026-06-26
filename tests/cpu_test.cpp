#include "neogba/arm7tdmi/cpu.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace {
class cpu_test : public ::testing::Test {
protected:
  std::unique_ptr<ARM7TDMI_CPU> cpu;

  cpu_test() {}

  virtual ~cpu_test() {}

  void SetUp() override { cpu = std::make_unique<ARM7TDMI_CPU>(); }

  void TearDown() override {}

  virtual inline void assert_convert(u32 expected, u32 input) {
    ASSERT_EQ((u32)expected, (u32)cpu->convert_mode_register(input));
  }

  virtual inline void assert_convert5(u32 mode, u32 e0, u32 i0, u32 e1, u32 i1,
                                      u32 e2, u32 i2, u32 e3, u32 i3, u32 e4,
                                      u32 i4, u32 e5, u32 i5) {
    cpu->set_mode(mode);
    ASSERT_EQ(mode, cpu->registers[cpsr]);

    ASSERT_EQ((u32)e0, (u32)cpu->convert_mode_register(i0));
    ASSERT_EQ((u32)e1, (u32)cpu->convert_mode_register(i1));
    ASSERT_EQ((u32)e2, (u32)cpu->convert_mode_register(i2));
    ASSERT_EQ((u32)e3, (u32)cpu->convert_mode_register(i3));
    ASSERT_EQ((u32)e4, (u32)cpu->convert_mode_register(i4));
    ASSERT_EQ((u32)e5, (u32)cpu->convert_mode_register(i5));
  }
};

} // namespace

TEST_F(cpu_test, convert_mode_register_should_right_when_mode_is_usr) {
  assert_convert5(ARM7TDMI_CPU_MODE_USR, r13, r13, r2, r2, r8, r8, pc, pc, cpsr,
                  cpsr, spsr_irq, spsr_irq);
}

TEST_F(cpu_test, convert_mode_register_should_right_when_mode_is_sys) {
  assert_convert5(ARM7TDMI_CPU_MODE_SYS, r13, r13, r2, r2, r8, r8, pc, pc,
                  spsr_fiq, spsr_fiq, cpsr, cpsr);
}

TEST_F(cpu_test, convert_mode_register_should_right_when_mode_is_fiq) {
  assert_convert5(ARM7TDMI_CPU_MODE_FIQ, r13_fiq, r13, r2, r2, r8_fiq, r8, r8,
                  r8, r7, r7, spsr_fiq, spsr_fiq);
}

TEST_F(cpu_test, convert_mode_register_should_right_when_mode_is_svc) {
  assert_convert5(ARM7TDMI_CPU_MODE_SVC, r13_svc, r13, r14_svc, r14, r8, r8,
                  r12, r12, spsr_svc, spsr_svc, spsr_abt, spsr_abt);
}

TEST_F(cpu_test, convert_mode_register_should_right_when_mode_is_abt) {
  assert_convert5(ARM7TDMI_CPU_MODE_ABT, r13_abt, r13, r14_abt, r14, r8, r8,
                  r12, r12, spsr_svc, spsr_svc, r14, r14);
}

TEST_F(cpu_test, convert_mode_register_should_right_when_mode_is_irq) {
  assert_convert5(ARM7TDMI_CPU_MODE_IRQ, r13_irq, r13, r14_irq, r14, r8, r8,
                  r12, r12, spsr_irq, spsr_irq, r13, r13);
}
