#include "neogba/arm7tdmi/cpu.hpp"
#include <gtest/gtest.h>

namespace neogba {

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
} // namespace neogba
