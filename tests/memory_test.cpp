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

TEST_F(bus_test, read_empty) { ASSERT_EQ(1, 1); }
