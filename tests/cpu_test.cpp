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

  void equals_registers(u32 expected[]) {
    ASSERT_EQ(0, std::memcmp(expected, cpu->registers,
                             ARM7TDMI_CPU_REGISTERS_TOTAL * sizeof(u32)));

    // for (auto i = 0; i < ARM7TDMI_CPU_REGISTERS_TOTAL; i++) {
    //    std::cout << i << " " << expected[i] << " " << cpu->registers[i] <<
    //    "\n";

    //   ASSERT_EQ(expected[i], cpu->registers[i]);
    // }
  }
};

} // namespace

TEST_F(
    cpu_test,
    write_read_active_registers_set_is_mode_get_idx_registers_lut_by_mode_should_be_fine_when_changing_modes) {
  u32 expected[ARM7TDMI_CPU_REGISTERS_TOTAL_REAL + 1];
  // std::memset(expected, 0, sizeof(expected));

  ARM7TDMI_CPU_REGISTERS_CREATE_STUB(
      expected, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115,
      116, 117, 118, 119, 26, 27, 28, 29, 30, 31, 32, (u32)-34, 65, 66,
      (u32)-68, 82, 83, (u32)-85, 48, 49, (u32)-51, 99, 100, (u32)-102,
      (u32)-119);

  u32 j = 0;
  for (auto mode : (u32[]){ARM7TDMI_CPU_MODE_USR, ARM7TDMI_CPU_MODE_FIQ,
                           ARM7TDMI_CPU_MODE_IRQ, ARM7TDMI_CPU_MODE_SVC,
                           ARM7TDMI_CPU_MODE_ABT, ARM7TDMI_CPU_MODE_UND,
                           ARM7TDMI_CPU_MODE_SYS}) {

    cpu->set_mode(mode, true);
    ASSERT_TRUE(cpu->is_mode(mode));

    for (auto b : (u32[]){ARM7TDMI_CPU_REGISTERS_USR}) {
      cpu->write_active_register(b, ++j);
    }

    if (mode == ARM7TDMI_CPU_MODE_USR || mode == ARM7TDMI_CPU_MODE_SYS)
      continue;

    cpu->write_spsr(-j);

    auto activ = cpu->REGISTERS_LUT[cpu->get_idx_registers_lut_by_mode(mode)];
    ASSERT_EQ(expected[activ[ARM7TDMI_CPU_ACTIVE_SPSR]], cpu->read_spsr());
  }

  ASSERT_EQ(expected[pc], cpu->read_pc());
  ASSERT_EQ(expected[cpsr], cpu->read_cpsr());

  cpu->set_mode(ARM7TDMI_CPU_MODE_FIQ, false);
  ASSERT_EQ(expected[r8_fiq], cpu->read_active_register(r8));
  ASSERT_EQ(expected[r8_fiq], cpu->registers[r8_fiq]);

  equals_registers(expected);

  cpu->write_cpsr(777);
  ASSERT_EQ(777, cpu->read_active_register(cpsr));
  cpu->write_active_register(cpsr, 42);
  ASSERT_EQ(42, cpu->registers[cpsr]);
}
