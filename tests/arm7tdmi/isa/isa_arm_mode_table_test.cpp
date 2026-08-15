#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/table.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

namespace {

template <typename T> class cpu_test_fixture : public ::testing::TestWithParam<T> {
protected:
  std::unique_ptr<arm7tdmi> cpu;

  cpu_test_fixture() {}
  virtual ~cpu_test_fixture() {}

  void SetUp() override {
    cpu = std::make_unique<arm7tdmi>();
    cpu->empty_registers();
    cpu->reset();
    cpu->set_mode(arm7tdmi::MODE_USR);
  }

  void TearDown() override {}
};

} // namespace

namespace {
using namespace arm_fsr;

struct fsr_test_param {
  u8 mode;
  bool s{true};
  arm_fsr::opcode_enum opcode;
  void (*caller)(arm7tdmi&, u32 inst);

  u8 rd;
  u8 rn;
  u8 rm;

  u32 initial_rd;
  u32 initial_rn{0};
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

using arm_fsr_fixture = cpu_test_fixture<fsr_test_param>;

TEST_P(arm_fsr_fixture, arm_fsr_fsr) {
  using namespace arm_operand2;
  const auto& params = GetParam();

  u32 inst{TEMPLATE};

  // "Ensamblar" la receta.
  if (params.s)
    inst = S::set1(inst);

  inst = OPCODE::set(inst, static_cast<u8>(params.opcode));
  inst = I::set0(inst);
  inst = RD::set(inst, params.rd);
  inst = RN::set(inst, params.rn);
  inst = RM::set(inst, params.rm);

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

  if (params.rd == pc)
    ASSERT_EQ(params.expected_rd, cpu->read_raw_register(pc));
  else
    ASSERT_EQ(params.expected_rd, cpu->read_active_register(params.rd));

  ASSERT_EQ(params.caller, arm_mode_lut.get(inst));
}

INSTANTIATE_TEST_SUITE_P( //
    fsr_parametrized,     //
    arm_fsr_fixture,      //
    ::testing::Values(
        // Caso 0
        fsr_test_param{.mode = arm7tdmi::MODE_FIQ,
                       .s = true,
                       .opcode = opcode_enum::MOV,
                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::MOV, .s = true}>,
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
                       .expected_rd = 0x80000000},

        // Caso 1
        fsr_test_param{.mode = arm7tdmi::MODE_FIQ,
                       .s = false,
                       .opcode = opcode_enum::RSB,
                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::RSB}>,
                       .rd = pc,
                       .rn = r6,
                       .rm = r9,

                       .initial_rd = 0x4,
                       .initial_rn = 777,
                       .initial_rm = 0x80000000,

                       .initial_c = true,
                       .initial_z = true,
                       .initial_v = true,
                       .initial_n = false,

                       // CMP 100, 100 -> restar = 0 (Z=1, N=0, C=1, V=0)
                       .expected_c = true,
                       .expected_z = true,
                       .expected_v = true,
                       .expected_n = false,
                       .expected_rd = 0x7ffffcf4}, // 0x7ffffcf7

        // Caso 2
        // rd_pc=false, !is_not_move=false, is_inverted=false, can_write_rd=false, s=true
        fsr_test_param{.mode = arm7tdmi::MODE_USR,
                       .s = true,
                       .opcode = opcode_enum::CMP,
                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::CMP, .s = true}>,
                       .rd = r4,
                       .rn = r2,
                       .rm = r3,

                       .initial_rd = 0x12345678,
                       .initial_rn = 100,
                       .initial_rm = 100,

                       .initial_c = false,
                       .initial_z = false,
                       .initial_v = false,
                       .initial_n = false,

                       .expected_c = true,
                       .expected_z = true,
                       .expected_v = false,
                       .expected_n = false,
                       .expected_rd = 0x12345678},

        // Caso 3
        // rd_pc=false, !is_not_move=false, is_inverted=false, can_write_rd=true, s=true,
        // !is_sum=true is_logical=false
        fsr_test_param{.mode = arm7tdmi::MODE_SYS,
                       .s = true,
                       .opcode = opcode_enum::ADD,
                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::ADD, .s = true}>,
                       .rd = r0,
                       .rn = r1,
                       .rm = r2,

                       .initial_rd = 0x0,
                       .initial_rn = 0xffffffff, // op1 (-1)
                       .initial_rm = 0x00000001, // op2 (1)

                       .initial_c = false,
                       .initial_z = false,
                       .initial_v = false,
                       .initial_n = false,

                       // 0xffffffff + 1 = 0x00000000 con Carry
                       .expected_c = true,
                       .expected_z = true,
                       .expected_v = false,
                       .expected_n = false,
                       .expected_rd = 0x00000000},

        // Caso 4
        // s = true, rd_pc = true, can_write_rd = true -> CPSR = SPSR
        fsr_test_param{.mode = arm7tdmi::MODE_FIQ,
                       .s = true,
                       .opcode = opcode_enum::MOV,
                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::MOV, .s = true}>,
                       .rd = pc,
                       .rn = r0,
                       .rm = r1,

                       .initial_rd = 0x0,
                       .initial_rm = 0x08000000,

                       .check_full_cpsr = true,
                       .expected_rd = 0x08000000,
                       .expected_cpsr = 0x10,

                       .initial_spsr = 0x10},

        // Caso 5
        // not is_sum = true, s = true, can_write_rd = true
        fsr_test_param{.mode = arm7tdmi::MODE_USR,
                       .s = true,
                       .opcode = opcode_enum::SUB,
                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::SUB, .s = true}>,
                       .rd = r0,
                       .rn = r1,
                       .rm = r2,

                       .initial_rd = 0x0,
                       .initial_rn = 10,
                       .initial_rm = 20, // 10 - 20 = -10 (0xfffffff6)

                       .expected_c = false,
                       .expected_z = false,
                       .expected_v = false,
                       .expected_n = true,
                       .expected_rd = 0xfffffff6},

        // Caso 6
        // is_logical = true, can_write_rd = false, s = true
        fsr_test_param{.mode = arm7tdmi::MODE_USR,
                       .s = true,
                       .opcode = opcode_enum::TST,

                       .caller = &fsr<fsr_tflags{.opcode = opcode_enum::TST, .s = true}>,
                       .rd = r0,
                       .rn = r1,
                       .rm = r2,

                       .initial_rd = 0x1234,
                       .initial_rn = 0b1010,
                       .initial_rm = 0b0101,

                       .expected_c = false,
                       .expected_z = true,
                       .expected_v = false,
                       .expected_n = false,
                       .expected_rd = 0x1234}

        ));
} // namespace
