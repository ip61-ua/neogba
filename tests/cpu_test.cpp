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
    // ASSERT_EQ(0, std::memcmp(expected, cpu->registers,
    //                          ARM7TDMI_CPU_REGISTERS_TOTAL * sizeof(u32)));

    for (auto i = 0; i < ARM7TDMI_CPU_REGISTERS_TOTAL; i++) {
      std::cout << i << " " << expected[i] << " " << cpu->registers[i] << "\n";

      ASSERT_EQ(expected[i], cpu->registers[i]);
    }
  }
};

} // namespace

TEST_F(cpu_test, write_lut_by_mode_should_be_fine_when_usr) {
  u32 expected[ARM7TDMI_CPU_REGISTERS_TOTAL_REAL];
  std::memset(expected, 0, sizeof(expected));

  u8 i = 0, j = 0;

  for (auto a : (u32[]){ARM7TDMI_CPU_REGISTERS_FIQ})
    expected[a] = ++i;

  cpu->set_mode(ARM7TDMI_CPU_MODE_FIQ, false);
  // auto activ = cpu->REGISTERS_LUT[cpu->get_idx_registers_lut_by_mode(
  //     ARM7TDMI_CPU_MODE_USR)];

  for (auto b : (u32[]){ARM7TDMI_CPU_REGISTERS_USR}) {
    cpu->write_active_register(b, ++j);
    ASSERT_EQ(j, cpu->read_active_register(b));
  }

  equals_registers(expected);
}

// crear aquí uno tal que escriba en modo 1, cambie a modo 2, escriba, y
// compare.
