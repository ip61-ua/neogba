#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

struct fsr_test_param {
  u8 mode;
  bool s{true};
  arm_fsr_opcode opcode;
  void (*caller)(arm7tdmi&, u32 inst);

  u8 rd;
  u8 rn;
  u8 rm;

  u32 initial_rd;
  u32 initial_rn;
  u32 initial_rm;

  bool initial_c{false};
  bool initial_z{false};
  bool initial_v{false};
  bool initial_n{false};

  bool check_full_cpsr{false};
  bool expected_c{false};
  bool expected_z{false};
  bool expected_v{false};
  bool expected_n{false};

  u32 expected_rd;

  u32 expected_cpsr{0};
  u32 initial_spsr{0};
};

namespace {

class fsr_test_fixture : public ::testing::TestWithParam<fsr_test_param> {
protected:
  std::unique_ptr<arm7tdmi> cpu;

  fsr_test_fixture() {}
  virtual ~fsr_test_fixture() {}

  void SetUp() override {
    cpu = std::make_unique<arm7tdmi>();
    cpu->empty_registers();
    cpu->set_mode(arm7tdmi::MODE_USR);
  }

  void TearDown() override {}
};

} // namespace

TEST_P(fsr_test_fixture, arm_fsr_fsr) {
  const auto& params = GetParam();

  u32 inst{ISA_ARM_FSR_TEMPLATE};

  // "Ensamblar" la receta.
  if (params.s)
    inst = ISA_ARM_FSR_S::set1(inst);

  inst = ISA_ARM_FSR_OPCODE::set(inst, static_cast<u8>(params.opcode));
  inst = ISA_ARM_FSR_I::set0(inst);
  inst = ISA_ARM_FSR_RD::set(inst, params.rd);
  inst = ISA_ARM_FSR_RN::set(inst, params.rn);
  inst = ISA_ARM_FSR_OPERAND2_RM::set(inst, params.rm);

  // Preparar ingredientes la CPU

  cpu->empty_registers();
  cpu->set_mode(params.mode);
  cpu->write_active_register(params.rd, params.initial_rd);
  cpu->write_active_register(params.rn, params.initial_rn);
  cpu->write_active_register(params.rm, params.initial_rm);

  if (!params.check_full_cpsr) {
    if (params.initial_c)
      cpu->set_cpsr(arm7tdmi::C, arm7tdmi::C);

    if (params.initial_z)
      cpu->set_cpsr(arm7tdmi::Z, arm7tdmi::Z);

    if (params.initial_v)
      cpu->set_cpsr(arm7tdmi::V, arm7tdmi::V);

    if (params.initial_n)
      cpu->set_cpsr(arm7tdmi::N, arm7tdmi::N);
  } else {
    cpu->write_spsr(params.initial_spsr);
  }

  // Ejecutar
  params.caller(*cpu.get(), inst);

  // Ver cambios

  if (!params.check_full_cpsr) {
    ASSERT_EQ(params.expected_c, cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C));
    ASSERT_EQ(params.expected_n, cpu->is_cpsr(arm7tdmi::N, arm7tdmi::N));
    ASSERT_EQ(params.expected_z, cpu->is_cpsr(arm7tdmi::Z, arm7tdmi::Z));
    ASSERT_EQ(params.expected_v, cpu->is_cpsr(arm7tdmi::V, arm7tdmi::V));
  } else {
    ASSERT_EQ(params.expected_cpsr, cpu->read_cpsr());
  }

  ASSERT_EQ(params.expected_rd, cpu->read_active_register(params.rd));
  ASSERT_EQ(params.caller, arm_lut.get(inst));
}

INSTANTIATE_TEST_SUITE_P( //
    fsr_parametrized,     //
    fsr_test_fixture,     //
    ::testing::Values(
        //

        fsr_test_param{.mode = arm7tdmi::MODE_FIQ,
                       .s = true,
                       .opcode = arm_fsr_opcode::MOV,
                       .caller = arm_MOV_S_notRdPC,
                       .rd = r4,
                       .rn = r6,
                       .rm = r9,

                       .initial_rd = 0xffffffff,
                       .initial_rn = 777,
                       .initial_rm = 0x80000000,

                       .initial_c = true,
                       .initial_z = true,
                       .initial_v = true,
                       .initial_n = false,

                       .expected_c = true,
                       .expected_z = false,
                       .expected_v = true,
                       .expected_n = true,
                       .expected_rd = 0x80000000}

        ));
