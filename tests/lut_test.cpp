
#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

TEST(lut_test, fill_recursive) {
  lut<1 << 8, int> my_lut;

  u8 mascara = 0b0010011, id_base = 0b1100110;
  int a = 42;

  auto n = my_lut.fill(id_base, mascara, a);

  ASSERT_EQ(8, n);
  ASSERT_EQ(8, my_lut.count_stored(a));
}
