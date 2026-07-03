#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

class cpu_arm_fixture : ::testing::Test {
protected:
  std::unique_ptr<arm7tdmi> cpu;

  cpu_arm_fixture() {}

  virtual ~cpu_arm_fixture() {}

  void SetUp() override {
    cpu = std::make_unique<arm7tdmi>();
    cpu->empty_registers();
  }

  void TearDown() override {}
};

TEST(cpu_arm_fixture, arm_and_simple_testing_not_filling_operand2) {
  auto inst = ISA_ARM_FSR_TEMPLATE;
}
