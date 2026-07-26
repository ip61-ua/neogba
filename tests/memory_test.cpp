#include "neogba/memory/bus.hpp"
#include <gtest/gtest.h>

using namespace neogba;

namespace {

// direcciones de 32.
// tenemos 8 bits más altos -> índice.
// tenemos 32 - 8 bits más bajos -> despl (24).
// esta mem ocupa 2^16 bytes
struct ram_stub
    : public memory<1 << 15, [](std::size_t addr) -> auto { return addr & 0xffff; }, true> {

  inline memory_bus* get_bus() { return bus; };
};

class bus_test : public ::testing::Test {
protected:
  std::unique_ptr<memory_bus> bus;
  std::unique_ptr<ram_stub> ram;

  bus_test() {}

  virtual ~bus_test() {}

  void SetUp() override {
    bus = std::make_unique<memory_bus>();
    ram = std::make_unique<ram_stub>();
  }

  void TearDown() override {}
};

} // namespace

TEST_F(bus_test, length_should_tell_truth_about_its_size) {
  ASSERT_EQ(ram->data().length(), ram->length());
}

TEST_F(bus_test, read_and_is_null_and_write_empty_memory_should_return_bad_value_or_do_not_allow) {
  u32 addr{0x100'0000};

  ASSERT_EQ(false, bus->write(8, addr, 1));
  ASSERT_EQ(true, bus->is_null(addr));
  ASSERT_EQ(0, bus->read(8, addr));
}

TEST_F(bus_test, attach_memory_should_inform_ram_it_is_attached_now) {
  u32 addr{0x100'0000};

  ASSERT_EQ(nullptr, ram->get_bus());
  ASSERT_EQ(true, bus->is_null(addr));
  bus->attach(addr, ram.get());

  ASSERT_EQ(false, bus->is_null(addr));
  ASSERT_EQ(bus.get(), ram->get_bus());
}

TEST_F(bus_test, read_and_write_endianess_in_bounds_should_be_great_when_no_anomal_actions) {
  u32 addr{0x100'0000};
  u32 value{123456};

  bus->attach(addr, ram.get());

  ASSERT_EQ(0, bus->read(8, addr));
  ASSERT_EQ(true, bus->write(32, addr, value));
  ASSERT_EQ(value, bus->read(32, addr));
  ASSERT_EQ(value & 0xff, bus->read(8, addr));
  ASSERT_EQ(value & 0xffff, bus->read(16, addr));
  ASSERT_EQ((value & 0xff'0000) >> 16, bus->read(8, addr + 2));
}

TEST_F(bus_test, read_and_write_out_of_bounds_should_be_resilient) {
  u32 addr{0x100'0000};
  u32 fake_addr{addr + (1 << 15)};
  u32 value{123456};

  bus->attach(addr, ram.get());

  ASSERT_EQ(true, bus->write(32, addr, value));
  ASSERT_EQ(123456, bus->read(32, addr));

  ASSERT_EQ(false, bus->write(32, fake_addr, value));
  ASSERT_EQ(0, bus->read(32, fake_addr));

  ASSERT_EQ(false, bus->write(32, addr - 1, value));
  ASSERT_EQ(0, bus->read(32, addr - 1));
}

TEST_F(bus_test, read_write_should_behave_equal_when_mirrorring_memories) {
  u32 addr{0x100'0000};
  u32 addr2{0xf00'0000};
  u32 fake_addr{addr + (1 << 15)};
  u32 value{123456};

  bus->attach(addr, ram.get());
  bus->attach(addr2, ram.get());

  ASSERT_EQ(true, bus->write(32, addr, value));
  ASSERT_EQ(123456, bus->read(32, addr));
  ASSERT_EQ(123456, bus->read(32, addr2));
  ASSERT_EQ(true, bus->write(32, addr, 777));
  ASSERT_EQ(777, bus->read(32, addr));

  ASSERT_EQ(false, bus->write(32, fake_addr, value));
  ASSERT_EQ(0, bus->read(32, fake_addr));
  ASSERT_EQ(false, bus->write(32, addr - 1, value));
  ASSERT_EQ(0, bus->read(32, addr - 1));

  fake_addr = addr2 + (1 << 15);

  ASSERT_EQ(false, bus->write(32, fake_addr, value));
  ASSERT_EQ(0, bus->read(32, fake_addr));
  ASSERT_EQ(false, bus->write(32, addr - 1, value));
  ASSERT_EQ(0, bus->read(32, addr - 1));
}

TEST_F(bus_test, dettach_good_should_behave_equal_when_mirrorring_memories) {
  u32 addr{0x100'0000};
  u32 addr2{0xf00'0000};

  ASSERT_EQ(0, std::ranges::count(bus->data(), ram.get()));
  bus->attach(addr, ram.get());
  ASSERT_EQ(1, bus->data().count_stored(ram.get()));
  bus->attach(addr2, ram.get());
  ASSERT_EQ(2, std::ranges::count(bus->data(), ram.get()));

  bus->deattach(addr2);
  ASSERT_EQ(bus->is_null(addr), bus->is_null(addr2));
  ASSERT_EQ(true, bus->is_null(addr2));
  ASSERT_EQ(nullptr, ram->get_bus());
  ASSERT_EQ(0, bus->data().count_stored(ram.get()));
}
