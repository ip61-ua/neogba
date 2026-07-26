#include "neogba/memory/bus.hpp"
#include <gtest/gtest.h>

using namespace neogba;

namespace {

// direcciones de 32.
// tenemos 8 bits más altos -> índice.
// tenemos 32 - 8 bits más bajos -> despl (24).
// esta mem ocupa 2^16 bytes
struct ram_stub : public memory<1 << 15> {};

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

TEST_F(bus_test, read_and_is_null_and_write_empty_memory_should_return_bad_value_or_do_not_allow) {
  u32 addr{0x100'0000};

  ASSERT_EQ(false, bus->write(8, addr, 1));
  ASSERT_EQ(true, bus->is_null(addr));
  ASSERT_EQ(0, bus->read(8, addr));
}

TEST_F(bus_test, attach_memory_should_inform_ram_it_is_attached_now) {
  u32 addr{0x100'0000};

  ASSERT_EQ(nullptr, ram->bus);
  ASSERT_EQ(true, bus->is_null(addr));
  bus->attach(addr, ram.get());

  ASSERT_EQ(false, bus->is_null(addr));
  ASSERT_EQ(bus.get(), ram->bus);
}

TEST_F(bus_test, read_and_write_endianess_in_bounds_should_be_great_when_no_anomal_actions) {
  u32 addr{0x100'0000};
  u32 value{123456};

  bus->attach(addr, ram.get());

  ASSERT_EQ(0, bus->read(8, addr));
  ASSERT_EQ(true, bus->write(32, addr, value));
  ASSERT_EQ(123456, bus->read(32, addr));
  ASSERT_EQ(123456 & 0xff, bus->read(8, addr));
  ASSERT_EQ(123456 & 0xffff, bus->read(16, addr));
  ASSERT_EQ((123456 & 0xff'0000) >> 16, bus->read(8, addr + 2));
}
