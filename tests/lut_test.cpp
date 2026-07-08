
#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

TEST(lut_test, fill_recursive_and_ensure_how_many_stored) {
  lut<1 << 8, int> my_lut;

  u8 mascara = 0b0010011, id_base = 0b1100110;
  int a = 42;

  auto n = my_lut.fill(id_base, mascara, a);

  ASSERT_EQ(8, n);
  ASSERT_EQ(8, my_lut.count_stored(a));
}

TEST(lut_test, fill_recursive_and_ensure_whats_stored) {
  lut<1 << 8, int> my_lut;

  u8 mascara = 0b0010011, id_base = 0b1100110;
  int a = 42;

  auto n = my_lut.fill(id_base, mascara, a);

  ASSERT_EQ(8, n);

  for (auto b :
       {0b1100110, 0b1100111, 0b1100101, 0b1100100, 0b1110111, 0b1110101, 0b1110110, 0b1110100})
    ASSERT_EQ(a, my_lut.get(b));
}
