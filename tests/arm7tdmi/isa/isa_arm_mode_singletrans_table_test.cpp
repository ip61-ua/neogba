#include "neogba/arm7tdmi/isa/arm_mode/singletrans.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/table.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include "neogba/memory/bus.hpp"
#include "neogba/test/fixtures/dummy_cpu.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;
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

constexpr singletrans_tflags c0{.i = 1, .p = 0, .u = 1, .b = 0, .w = 0, .l = 0},
    c1{.i = 1, .p = 1, .u = 1, .b = 0, .w = 0, .l = 0},
    c2{.i = 0, .p = 1, .u = 0, .b = 0, .w = 0, .l = 1},
    c3{.i = 0, .p = 1, .u = 0, .b = 1, .w = 1, .l = 1};

TEST_P(arm_singletrans_fixture, arm_singletrans_test) {
  // Arrange
  const auto& params = GetParam();

  u32 inst{arm_singletrans::TEMPLATE |             //
           arm_singletrans::I::h(params.flags.i) | //
           P::h(params.flags.p) |                  //
           U::h(params.flags.u) |                  //
           B::h(params.flags.b) |                  //
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

  ASSERT_EQ(params.caller, arm_mode_lut.get(inst));
}

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
