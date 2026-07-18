#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

namespace {
class cpu_arm_fixture : public ::testing::Test {
protected:
  std::unique_ptr<arm7tdmi> cpu;

  cpu_arm_fixture() {}

  virtual ~cpu_arm_fixture() {}

  void SetUp() override {
    cpu = std::make_unique<arm7tdmi>();
    cpu->empty_registers();
    cpu->set_mode(arm7tdmi::MODE_USR);
  }

  void TearDown() override {}
};
} // namespace

TEST_F(cpu_arm_fixture, arm_and_simple_testing_not_filling_operand2) {
  auto inst{ISA_ARM_FSR_TEMPLATE};

  inst = ISA_ARM_FSR_RN::set(inst, r2);
  inst = ISA_ARM_FSR_RD::set(inst, r5);
  inst = ISA_ARM_FSR_OPERAND2_RM::set(inst, r12);
  inst = ISA_ARM_FSR_I::set0(inst);

  cpu->write_raw_register(r2, 0xffu);
  cpu->write_raw_register(r12, 0xf0u);

  arm_AND(*cpu.get(), inst);

  ASSERT_EQ(0xf0u, cpu->read_raw_register(r5));
};
