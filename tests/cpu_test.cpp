#include "neogba/arm7tdmi/cpu.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace {
class cpu_test : public ::testing::Test {
  std::unique_ptr<ARM7TDMI_CPU> cpu;

  cpu_test() {}

  virtual ~cpu_test() {}

  virtual void SetUp() { cpu = std::make_unique<ARM7TDMI_CPU>(); }

  virtual void TearDown() {}
};

} // namespace

static ARM7TDMI_CPU cpu;

TEST(cpu_test, convert_mode_register_should_same_when_mode_is_usr) {
  cpu.set_mode(ARM7TDMI_CPU_MODE_USR);

  ASSERT_EQ(ARM7TDMI_CPU_MODE_USR, cpu.registers[cpsr]);
  ASSERT_EQ(r13, cpu.convert_mode_register(r13));
  ASSERT_EQ(r2, cpu.convert_mode_register(r2));
  ASSERT_EQ(r8, cpu.convert_mode_register(r8));
  ASSERT_EQ(pc, cpu.convert_mode_register(pc));
  ASSERT_EQ(cpsr, cpu.convert_mode_register(cpsr));
}

TEST(cpu_test, convert_mode_register_should_same_when_mode_is_sys) {
  cpu.set_mode(ARM7TDMI_CPU_MODE_SYS);

  ASSERT_EQ(r13, cpu.convert_mode_register(r13));
  ASSERT_EQ(r2, cpu.convert_mode_register(r2));
  ASSERT_EQ(r8, cpu.convert_mode_register(r8));
  ASSERT_EQ(pc, cpu.convert_mode_register(pc));
  ASSERT_EQ(cpsr, cpu.convert_mode_register(cpsr));
}

TEST(cpu_test, convert_mode_register_should_same_when_mode_is_fiq) {
  cpu.set_mode(ARM7TDMI_CPU_MODE_FIQ);

  ASSERT_EQ((u32)r13_fiq, (u32)cpu.convert_mode_register(r13));
  ASSERT_EQ((u32)r2, (u32)cpu.convert_mode_register(r2));
  ASSERT_EQ((u32)r8_fiq, (u32)cpu.convert_mode_register(r8));
  ASSERT_EQ((u32)pc, (u32)cpu.convert_mode_register(pc));
  ASSERT_EQ((u32)cpsr, (u32)cpu.convert_mode_register(cpsr));
}
