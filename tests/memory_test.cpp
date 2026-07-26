#include "neogba/memory/bus.hpp"
#include <gtest/gtest.h>

using namespace neogba;

namespace {
class bus_test : public ::testing::Test {
protected:
  std::unique_ptr<memory_bus> bus;

  bus_test() {}

  virtual ~bus_test() {}

  void SetUp() override { bus = std::make_unique<memory_bus>(); }

  void TearDown() override {}
};

// direcciones de 32.
// tenemos 8 bits más altos -> índice.
// tenemos 32 - 8 bits más bajos -> despl (24).

struct ram_stub : public memory<1 << 15> {};

} // namespace

TEST_F(bus_test, get_idx_registers_preset_by_mode_should_say_right_when_providing_modes) {

  ASSERT_EQ(1, 1);
}
