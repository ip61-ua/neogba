#include "neogba/arm7tdmi/cpu.hpp"
#include <cstring>
#include <gtest/gtest.h>
#include <memory>

namespace {
class cpu_test : public ::testing::Test {
protected:
  std::unique_ptr<ARM7TDMI_CPU> cpu;

  cpu_test() {}

  virtual ~cpu_test() {}

  void SetUp() override {
    cpu = std::make_unique<ARM7TDMI_CPU>();
    cpu->empty_registers();
  }

  void TearDown() override {}
};

} // namespace

TEST_F(
    cpu_test,
    set_mode_write_and_read_register_should_be_right_when_setting_usr_writting_and_reading) {

  cpu->set_mode(ARM7TDMI_CPU_MODE_USR, false);
  u32 expected[ARM7TDMI_CPU_REGISTERS_TOTAL_REAL];
  std::memset(expected, 0, sizeof(expected));

  for (auto a : (u32[]){r0, r2, r6, r7, r8, r12, r13, pc, cpsr}) {
    expected[a] = a;
  }

  for (auto a : (u32[]){r0, r2, r6, r7, r8, r12, r13, pc, cpsr}) {
    cpu->write_active_register(a, a);
  }

  for (auto i = 0; i < ARM7TDMI_CPU_REGISTERS_TOTAL; i++) {
    std::cout << i << " " << expected[i] << " " << cpu->registers[i] << "\n";

    ASSERT_EQ(expected[i], cpu->registers[i]);
  }
}
