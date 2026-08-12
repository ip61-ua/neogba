#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa/constants.hpp"
#include <gtest/gtest.h>

using namespace neogba;

namespace {

struct ram_stub
    : public memory<1 << 15, [](std::size_t addr) -> auto { return addr & 0xffff; }, true> {
  inline memory_bus* get_bus() { return bus; }
};

class cpu_basic_lifecycle_test : public ::testing::Test {
protected:
  std::unique_ptr<memory_bus> bus;
  std::unique_ptr<ram_stub> ram;
  std::unique_ptr<arm7tdmi> cpu;

  static constexpr u32 RAM_BASE_ADDR = 0x0300'0000;

  void SetUp() override {
    bus = std::make_unique<memory_bus>();
    ram = std::make_unique<ram_stub>();

    bus->attach(RAM_BASE_ADDR, ram.get());
    cpu = std::make_unique<arm7tdmi>();
    cpu->bus = bus.get();
    cpu->reset();
  }

  void TearDown() override {}
};

} // namespace

TEST_F(cpu_basic_lifecycle_test, fetches_decodes_and_executes_sequential_arm_instructions) {
  using namespace neogba::arm_fsr;
  using namespace neogba::arm_cond;

  constexpr u32 i0 = TEMPLATE | COND::set_high(cond_enum::AL) | OPCODE::set_high(opcode_enum::MOV) |
                     RD::set_high(r1) | I::set_high() | arm_operand2::IMM::set_high(42u),
                i1 = TEMPLATE | COND::set_high(cond_enum::AL) | OPCODE::set_high(opcode_enum::MOV) |
                     RD::set_high(r2) | I::set_high() | arm_operand2::IMM::set_high(69u);

  ASSERT_TRUE(bus->write(32, RAM_BASE_ADDR, i0));
  ASSERT_TRUE(bus->write(32, RAM_BASE_ADDR + 4, i1));
  cpu->write_raw_register(pc, RAM_BASE_ADDR);

  cpu->step();
  EXPECT_EQ(cpu->read_active_register(r1), 42u);
  EXPECT_EQ(cpu->read_raw_register(pc), RAM_BASE_ADDR + 4);

  cpu->step();
  EXPECT_EQ(cpu->read_active_register(r2), 69u);
  EXPECT_EQ(cpu->read_raw_register(pc), RAM_BASE_ADDR + 8);
}
