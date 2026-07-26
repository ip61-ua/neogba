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
  u32 addr{0x1000000};

  ASSERT_EQ(false, bus->write(8, addr, 1));
  ASSERT_EQ(true, bus->is_null(addr));
  ASSERT_EQ(0, bus->read(8, addr));
}

TEST_F(bus_test, attach_memory_should_inform_ram_it_is_attached_now) {
  u32 addr{0x1000000};

  ASSERT_EQ(nullptr, ram->bus);
  bus->attach(addr, ram.get());

  ASSERT_EQ(bus.get(), ram->bus);
}
