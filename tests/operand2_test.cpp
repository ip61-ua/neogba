#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

namespace {
class operand2_test_fixture : public ::testing::Test {
protected:
  std::unique_ptr<arm7tdmi> cpu;

  operand2_test_fixture() {}

  virtual ~operand2_test_fixture() {}

  void SetUp() override {
    cpu = std::make_unique<arm7tdmi>();
    cpu->empty_registers();
    cpu->write_active_register(r1, 0x1);
    cpu->write_active_register(r2, 0x2);
    cpu->write_active_register(r3, -1);
    cpu->write_active_register(r4, -60);
    cpu->write_active_register(r5, 777);
    cpu->write_active_register(r6, 999);
    cpu->write_active_register(r7, 1 << 7);
    cpu->write_active_register(r8, 1 << 8);
    cpu->write_active_register(r9, (1 << 9) - 1);
    cpu->write_active_register(r10, (1 << 10) - 1);
    cpu->write_active_register(r11, 42);
    cpu->set_mode(arm7tdmi::MODE_USR);
  }

  void TearDown() override {}
};
} // namespace

TEST_F(operand2_test_fixture, arm_fsr_operand2_i1_r1_should_return_with_no_rotation) {
  static auto inst001{ISA_ARM_FSR_TEMPLATE};

  inst001 = ISA_ARM_FSR_I::set1(inst001);
  inst001 = ISA_ARM_FSR_OPERAND2_IMM::set(inst001, 69);
  inst001 = ISA_ARM_FSR_OPERAND2_ROTATE::set(inst001, 0);

  auto op2 = arm_fsr_operand2_i1_r1(*cpu.get(), inst001);

  ASSERT_EQ(69, op2.result);
};

TEST_F(operand2_test_fixture, arm_fsr_operand2_i1_r0_should_return_with_rotated) {
  static auto inst002{ISA_ARM_FSR_TEMPLATE};

  constexpr u32 imm_val = 0x3;
  constexpr u32 rotate_val = 1;

  inst002 = ISA_ARM_FSR_I::set1(inst002);
  inst002 = ISA_ARM_FSR_OPERAND2_IMM::set(inst002, imm_val);
  inst002 = ISA_ARM_FSR_OPERAND2_ROTATE::set(inst002, rotate_val);

  auto op2 = arm_fsr_operand2_i1_r0(*cpu, inst002);

  // result: (32 bits) (0x03 >> 2) -> 0xC0000000
  // carry: bit[rotate - 1] == 1 de 0x03 -> 1
  constexpr u32 expected_result = 0xC0000000;
  constexpr u8 expected_carry = 1;

  EXPECT_EQ(op2.result, expected_result);
  EXPECT_EQ(op2.carry_out, expected_carry);
};

TEST_F(operand2_test_fixture, arm_fsr_operand2_i1_r0_should_return_with_rotated_and_no_carry) {
  static auto inst003{ISA_ARM_FSR_TEMPLATE};

  constexpr u32 imm_val = 0x4;
  constexpr u32 rotate_val = 1;

  inst003 = ISA_ARM_FSR_I::set1(inst003);
  inst003 = ISA_ARM_FSR_OPERAND2_IMM::set(inst003, imm_val);
  inst003 = ISA_ARM_FSR_OPERAND2_ROTATE::set(inst003, rotate_val);

  auto op2 = arm_fsr_operand2_i1_r0(*cpu, inst003);

  constexpr u32 expected_result = 0x00000001;
  constexpr u8 expected_carry = 0;

  EXPECT_EQ(op2.result, expected_result);
  EXPECT_EQ(op2.carry_out, expected_carry);
};
