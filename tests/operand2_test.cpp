#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

struct operand2_test_param {
  u32 inst;
  arm_operand2_result (*caller)(arm7tdmi&, u32 inst);
  u32 expected_result;
  u8 expected_carry_out;
};

namespace {
class operand2_test_fixture : public ::testing::TestWithParam<operand2_test_param> {
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

TEST_P(operand2_test_fixture, arm_fsr_operand2) {
  const auto& params = GetParam();

  auto op2 = params.caller(*cpu.get(), params.inst);

  ASSERT_EQ(params.expected_result, op2.result);
  ASSERT_EQ(params.expected_carry_out, op2.carry_out);
  ASSERT_EQ(params.caller, arm_fsr_operand2_lut.get(params.inst));
}

constexpr static u32 //
    i001{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_I::set_high() | ISA_ARM_FSR_OPERAND2_IMM::set_high(69) |
         ISA_ARM_FSR_OPERAND2_ROTATE::set_high(0)},
    i002{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_I::set_high() | ISA_ARM_FSR_OPERAND2_IMM::set_high(3) |
         ISA_ARM_FSR_OPERAND2_ROTATE::set_high(1)},
    i003{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_I::set_high() | ISA_ARM_FSR_OPERAND2_IMM::set_high(4) |
         ISA_ARM_FSR_OPERAND2_ROTATE::set_high(1)};

INSTANTIATE_TEST_SUITE_P(  //
    operand2_parametrized, //
    operand2_test_fixture, //
    ::testing::Values(     //
        operand2_test_param{i001, arm_fsr_operand2_i1_r1, 69, 0},
        operand2_test_param{i002, arm_fsr_operand2_i1_r0, 0xc0000000, 1},
        operand2_test_param{i003, arm_fsr_operand2_i1_r0, 1, 0}));
