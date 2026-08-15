#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/singletrans.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/table.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include "neogba/memory/bus.hpp"
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

namespace {
using namespace arm_singletrans;

struct singletrans_test_param {
  singletrans_tflags flags;

  u8 rd;
  u8 rn;
  u16 offset;

  void (*caller)(arm7tdmi&, u32 inst);

  u32 expected_rd_contents{0};
  u32 expected_rn_contents{0};
  u32 expected_last_write{0};
  u32 expected_last_read{0};
  u32 expected_ram_addr_contents{0};
};

class arm_singletrans_fixture : public cpu_test_fixture<singletrans_test_param> {
public:
  using ram_stub = memory<1 << 15, [](std::size_t addr) -> auto { return addr & 0xffff; }, true>;

  std::unique_ptr<memory_bus> bus;
  std::unique_ptr<ram_stub> ram;

  auto SetUp() -> void override {
    bus = std::make_unique<memory_bus>();
    ram = std::make_unique<ram_stub>();
    bus->attach(0, ram.get());

    ram->write(32, 0, 0xccaa'ff00);
    ram->write(32, 4, 0x1122'ff44);
    ram->write(32, 8, 0x1808'ff88);
    ram->write(32, 12, 0xf212'1122);
    ram->write(32, 16, 0xf616'1166);
    ram->write(32, 20, 0xf020'2200);
    ram->write(32, 24, 0xf424'2244);
    ram->write(32, 28, 0xf828'2288);
    ram->write(32, 32, 0xff32'3322);

    cpu = std::make_unique<arm7tdmi>();

    cpu->set_bus(bus.get());
    cpu->empty_registers();
    cpu->reset();
    cpu->set_mode(arm7tdmi::MODE_USR);

    cpu->write_raw_register(r0, 1);
    cpu->write_raw_register(r1, 0xcafecafe);
    cpu->write_raw_register(r2, 32);
    cpu->write_raw_register(r3, 0xface0011);
    cpu->write_raw_register(r4, 11);
    cpu->write_raw_register(r5, 0xcaca);
    cpu->write_raw_register(r6, 6);
    cpu->write_raw_register(r7, 0x21426977);
  }
};

TEST_P(arm_singletrans_fixture, arm_singletrans_test) {
  // Arrange
  const auto& params = GetParam();

  u32 inst{arm_singletrans::TEMPLATE |             //
           arm_singletrans::I::h(params.flags.i) | //
           P::h(params.flags.p) |                  //
           U::h(params.flags.u) |                  //
           W::h(params.flags.w) |                  //
           L::h(params.flags.l) |                  //
           RN::h(params.rn) |                      //
           RD::h(params.rd) |                      //
           arm_singletrans::OFFSET::h(params.offset)};

  // Act
  params.caller(*cpu.get(), inst);

  // Assert
  ASSERT_EQ(params.expected_rd_contents, cpu->read_active_register(params.rd));
  ASSERT_EQ(params.expected_rn_contents, cpu->read_active_register(params.rn));

  ASSERT_EQ(params.expected_last_read, bus->get_last_read());
  ASSERT_EQ(params.expected_last_write, bus->get_last_write());

  const auto addr_to_check{params.flags.l ? params.expected_last_read : params.expected_last_write};
  ASSERT_EQ(params.expected_ram_addr_contents, bus->read(32, addr_to_check));

  //  ASSERT_EQ(params.caller, arm_mode_lut.get(inst));
}

constexpr singletrans_tflags c0{.i = 1, .p = 0, .u = 1, .b = 0, .w = 0, .l = 0},
    c1{.i = 1, .p = 1, .u = 1, .b = 0, .w = 0, .l = 0},
    c2{.i = 0, .p = 1, .u = 0, .b = 0, .w = 0, .l = 1},
    c3{.i = 0, .p = 1, .u = 0, .b = 1, .w = 1, .l = 1};

INSTANTIATE_TEST_SUITE_P(     //
    singletrans_parametrized, //
    arm_singletrans_fixture,  //
    ::testing::Values(

        // Caso 0: c0 y is_pc
        singletrans_test_param{
            .flags = c0,
            .rd = pc,
            .rn = r2,
            .offset = r0,
            .caller = &singletrans<c0>,
            .expected_rd_contents = 8,
            .expected_rn_contents = 33, // Post-index  base + offset
            .expected_last_write = 32,  // base
            .expected_last_read = static_cast<u32>(-1),
            .expected_ram_addr_contents = 12,
        },

        // Caso 1: c1 y not is_pc
        singletrans_test_param{
            .flags = c1,
            .rd = r1,
            .rn = r0,
            .offset = r4,
            .caller = &singletrans<c1>,
            .expected_rd_contents = 0xcafecafe,
            .expected_rn_contents = 1, // Pre-index w/o wb
            .expected_last_write = 12, // base + offset
            .expected_last_read = static_cast<u32>(-1),
            .expected_ram_addr_contents = 0xcafecafe,
        },

        // Caso 2: c2 y not is_pc
        singletrans_test_param{
            .flags = c2,
            .rd = r1,
            .rn = r2,
            .offset = 4,
            .caller = &singletrans<c2>,
            .expected_rd_contents = 0xf828'2288,
            .expected_rn_contents = 32, // Pre-index w/o wb
            .expected_last_write = static_cast<u32>(-1),
            .expected_last_read = 28, // base - offset
            .expected_ram_addr_contents = 0xf828'2288,
        },

        // Caso 3: c3 y is_pc
        singletrans_test_param{
            .flags = c3,
            .rd = pc,
            .rn = r2,
            .offset = 4,
            .caller = &singletrans<c3>,
            .expected_rd_contents = 144,
            .expected_rn_contents = 28, // wb base - offset
            .expected_last_write = static_cast<u32>(-1),
            .expected_last_read = 28, // base - offset
            .expected_ram_addr_contents = 0xf828'2288,
        }

        ));

}; // namespace
