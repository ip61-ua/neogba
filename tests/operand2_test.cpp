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
    cpu->set_mode(arm7tdmi::MODE_USR);
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
  }

  void TearDown() override {}
};
} // namespace

TEST_F(operand2_test_fixture, arm_fsr_operand2_i1_r1_should_return_with_no_rotation) {
  static auto inst001{ISA_ARM_FSR_TEMPLATE};

  inst001 = ISA_ARM_FSR_I::set1(inst001);
  inst001 = ISA_ARM_FSR_OPERAND2_IMM::set(inst001, 69);
  inst001 = ISA_ARM_FSR_OPERAND2_ROTATE::set(inst001, 0);

  constexpr auto caller{arm_fsr_operand2_i1_r1};

  auto op2 = caller(*cpu.get(), inst001);

  ASSERT_EQ(69, op2.result);
  ASSERT_EQ(0, op2.carry_out);
  ASSERT_EQ(caller, arm_fsr_operand2_lut.get(inst001));
};

TEST_F(operand2_test_fixture, arm_fsr_operand2_i1_r0_should_return_with_rotated) {
  static auto inst002{ISA_ARM_FSR_TEMPLATE};

  inst002 = ISA_ARM_FSR_I::set1(inst002);
  inst002 = ISA_ARM_FSR_OPERAND2_IMM::set(inst002, 3);
  inst002 = ISA_ARM_FSR_OPERAND2_ROTATE::set(inst002, 1);

  constexpr auto caller{arm_fsr_operand2_i1_r0};

  auto op2 = caller(*cpu, inst002);

  // result: (32 bits) (0x03 >> 2) -> 0xC0000000
  // carry: bit[rotate - 1] == 1 de 0x03 -> 1
  ASSERT_EQ(0xc0000000, op2.result);
  ASSERT_EQ(1, op2.carry_out);
  ASSERT_EQ(caller, arm_fsr_operand2_lut.get(inst002));
};

TEST_F(operand2_test_fixture, arm_fsr_operand2_i1_r0_should_return_with_rotated_and_no_carry) {
  static auto inst003{ISA_ARM_FSR_TEMPLATE};

  inst003 = ISA_ARM_FSR_I::set1(inst003);
  inst003 = ISA_ARM_FSR_OPERAND2_IMM::set(inst003, 4);
  inst003 = ISA_ARM_FSR_OPERAND2_ROTATE::set(inst003, 1);

  constexpr auto caller{arm_fsr_operand2_i1_r0};

  auto op2 = caller(*cpu, inst003);

  ASSERT_EQ(1, op2.result);
  ASSERT_EQ(0, op2.carry_out);
  ASSERT_EQ(caller, arm_fsr_operand2_lut.get(inst003));
};

TEST_F(operand2_test_fixture,
       arm_fsr_operand2_i0_40_z1_lsl_should_return_rm_without_modifying_carry) {
  static auto inst004{ISA_ARM_FSR_TEMPLATE};

  inst004 = ISA_ARM_FSR_I::set0(inst004);
  inst004 = ISA_ARM_FSR_OPERAND2_4::set0(inst004);
  inst004 = ISA_ARM_FSR_OPERAND2_RM::set(inst004, r5);
  inst004 = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set(
      inst004, static_cast<ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::ret_t>(arm_shift_type::LSL));

  cpu->write_cpsr(arm7tdmi::C);

  constexpr auto caller{arm_fsr_operand2_i0_40_z1_LSL};

  auto op2 = caller(*cpu, inst004);

  ASSERT_EQ(777, op2.result);
  ASSERT_EQ(1, op2.carry_out);
  ASSERT_EQ(caller, arm_fsr_operand2_lut.get(inst004));
}

TEST_F(operand2_test_fixture, arm_fsr_operand2_i0_40_z1_lsr_should_behave_as_lsr32) {
  static auto inst005{ISA_ARM_FSR_TEMPLATE};

  inst005 = ISA_ARM_FSR_I::set0(inst005);
  inst005 = ISA_ARM_FSR_OPERAND2_4::set0(inst005);
  inst005 = ISA_ARM_FSR_OPERAND2_RM::set(inst005, r1);
  inst005 = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set(
      inst005, static_cast<ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::ret_t>(arm_shift_type::LSR));

  constexpr auto caller{arm_fsr_operand2_i0_40_z1_LSR};

  auto op2 = caller(*cpu, inst005);

  ASSERT_EQ(0, op2.result);
  ASSERT_EQ(0, op2.carry_out);
  ASSERT_EQ(caller, arm_fsr_operand2_lut.get(inst005));
}

TEST_F(operand2_test_fixture, arm_fsr_operand2_i0_40_z1_asr_should_sign_extend) {
  static auto inst006{ISA_ARM_FSR_TEMPLATE};

  inst006 = ISA_ARM_FSR_I::set0(inst006);
  inst006 = ISA_ARM_FSR_OPERAND2_4::set0(inst006);
  inst006 = ISA_ARM_FSR_OPERAND2_RM::set(inst006, r4);
  inst006 = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set(
      inst006, static_cast<ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::ret_t>(arm_shift_type::ASR));

  constexpr auto caller{arm_fsr_operand2_i0_40_z1_ASR};

  auto op2 = caller(*cpu, inst006);

  ASSERT_EQ(0xffffffff, op2.result);
  ASSERT_EQ(1, op2.carry_out);
  ASSERT_EQ(caller, arm_fsr_operand2_lut.get(inst006));
}
