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
  u8 initial_carry{0};
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

    cpu->write_active_register(r9, 0xffffffff);
    cpu->write_active_register(r7, 0x00000022);
    cpu->write_active_register(r7, 0x00000022);
    cpu->write_active_register(r1, 3);
    cpu->write_active_register(r2, 32);
    cpu->write_active_register(r3, 33);
  }

  void TearDown() override {}
};
} // namespace

TEST_P(operand2_test_fixture, arm_fsr_operand2) {
  const auto& params = GetParam();
  if (params.initial_carry)
    cpu->set_cpsr(arm7tdmi::C, arm7tdmi::C);

  auto op2 = params.caller(*cpu.get(), params.inst);

  ASSERT_EQ(params.expected_result, op2.result);
  ASSERT_EQ(params.expected_carry_out, op2.carry_out);
  ASSERT_EQ(cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C), static_cast<bool>(op2.carry_in));
  ASSERT_EQ(params.caller, arm_fsr_operand2_lut.get(params.inst));
}

constexpr static u32 //
    i000{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_I::set_high() | ISA_ARM_FSR_OPERAND2_IMM::set_high(69)},
    i001{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_I::set_high() |
         ISA_ARM_FSR_OPERAND2_IMM::set_high(255) | ISA_ARM_FSR_OPERAND2_ROTATE::set_high(2)},

    i002{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSL))},
    i003{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSR))},
    i004{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ASR))},
    i005{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ROR))},

    i006{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r8) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ROR))},

    i007{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::set_high(1) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSL))},
    i008{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::set_high(1) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSR))},
    i009{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::set_high(3) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ASR))},
    i010{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::set_high(1) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ROR))},

    i011{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r2) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ROR))},
    i012{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r1) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ROR))},

    i013{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r3) | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ASR))},
    i014{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r1) | ISA_ARM_FSR_OPERAND2_RM::set_high(r9) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::ASR))},

    i015{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r3) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSR))},
    i016{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r2) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSR))},
    i017{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r1) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSR))},

    i018{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r3) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSL))},
    i019{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r2) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSL))},
    i020{ISA_ARM_FSR_TEMPLATE | ISA_ARM_FSR_OPERAND2_4::set_high() |
         ISA_ARM_FSR_OPERAND2_RS::set_high(r1) | ISA_ARM_FSR_OPERAND2_RM::set_high(r7) |
         ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::set_high(static_cast<u8>(arm_shift_type::LSL))};

INSTANTIATE_TEST_SUITE_P(  //
    operand2_parametrized, //
    operand2_test_fixture, //
    ::testing::Values(
        // 0. i | r
        operand2_test_param{i000, arm_fsr_operand2_i1_r1, 69, 1, 1}, //
        // 1. i | -r
        operand2_test_param{i001, arm_fsr_operand2_i1_r0, std::rotr(static_cast<u8>(255), 4), 0, 0},

        // 2. -i | -bit4 | z | LSL
        operand2_test_param{i002, arm_fsr_operand2_i0_40_z1_LSL, 0xffffffff, 0, 0},
        // 3. -i | -bit4 | z | LSR
        operand2_test_param{i003, arm_fsr_operand2_i0_40_z1_LSR, 0, 1, 0},
        // 4. -i | -bit4 | z | ASR
        operand2_test_param{i004, arm_fsr_operand2_i0_40_z1_ASR, 0xffffffff, 1, 0},
        // 5. -i | -bit4 | z | ROR
        operand2_test_param{i005, arm_fsr_operand2_i0_40_z1_ROR, 0x7fffffff, 1, 0},

        // 6. -i | bit4 | any | any | [rs] = 0
        operand2_test_param{i006, arm_fsr_operand2_i0_41_z0_ROR, 0x22, 0, 0},

        // 7. -i | -bit4 | -z | lsl.
        operand2_test_param{i007, arm_fsr_operand2_i0_40_z0_LSL, 0x22 << 1, 0, 1},
        // 8. -i | -bit4 | -z | lsr.
        operand2_test_param{i008, arm_fsr_operand2_i0_40_z0_LSR, 0x22 >> 1, 0, 1},
        // 9. -i | -bit4 | -z | asr.
        operand2_test_param{i009, arm_fsr_operand2_i0_40_z0_ASR, 0xffffffff, 1, 0},
        // 10. -i | -bit4 | -z | ror.
        operand2_test_param{i010, arm_fsr_operand2_i0_40_z0_ROR,
                            std::rotr(static_cast<u32>(0x22), 1), 0, 1},

        // 11. -i | bit4 | any | ror | [rs] != 0 | masked == 0
        operand2_test_param{i011, arm_fsr_operand2_i0_41_z0_ROR, 0x22, 0, 0},
        // 12. -i | bit4 | any | ror | [rs] != 0 | masked != 0
        operand2_test_param{i012, arm_fsr_operand2_i0_41_z0_ROR,
                            std::rotr(static_cast<u32>(0x22), 3), 0, 0},

        // 13. -i | bit4 | any | asr | [rs] != 0 | [rs] >= 32
        operand2_test_param{i013, arm_fsr_operand2_i0_41_z0_ASR, 0xffffffff, 1, 0},
        // 14. -i | bit4 | any | asr | [rs] != 0 | [rs] < 32
        operand2_test_param{i014, arm_fsr_operand2_i0_41_z0_ASR, 0xffffffff, 1, 0},

        // 15. -i | bit4 | any | lsr | [rs] != 0 | [rs] > 32
        operand2_test_param{i015, arm_fsr_operand2_i0_41_z0_LSR, 0, 0, 0},
        // 16. -i | bit4 | any | lsr | [rs] != 0 | [rs] == 32
        operand2_test_param{i016, arm_fsr_operand2_i0_41_z0_LSR, 0, 0, 0},
        // 17. -i | bit4 | any | lsr | [rs] != 0 | [rs] < 32
        operand2_test_param{i017, arm_fsr_operand2_i0_41_z0_LSR, 0x22 >> 3, 0, 0},

        // 18. -i | bit4 | any | lsl | [rs] != 0 | [rs] > 32
        operand2_test_param{i018, arm_fsr_operand2_i0_41_z0_LSL, 0, 0, 0},
        // 19. -i | bit4 | any | lsl | [rs] != 0 | [rs] == 32
        operand2_test_param{i019, arm_fsr_operand2_i0_41_z0_LSL, 0, 0, 0},
        // 20. -i | bit4 | any | lsl | [rs] != 0 | [rs] < 32
        operand2_test_param{i020, arm_fsr_operand2_i0_41_z0_LSL, 0x22 << 3, 0, 0}));
