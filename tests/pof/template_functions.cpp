#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

template <bool a = false, bool b = false, bool c = false, bool d = false>
bool superplant(int codigo) {
  return (a << 3 | b << 2 | c << 1 | d) == codigo;
}
using function_type = bool (*)(int);
using lut_type = lut<function_type, 16>;

template <std::size_t I> constexpr function_type expected_function() {
  static_assert(I < 16);

  return &superplant<(I & 0b1000) != 0, (I & 0b0100) != 0, (I & 0b0010) != 0, (I & 0b0001) != 0>;
}

template <std::size_t... I> constexpr lut_type make_lut(std::index_sequence<I...>) {
  lut_type result;

  (result.fill(I, 0, expected_function<I>()), ...);

  return result;
}

TEST(proof_of_concept, template_functions_check_if_runs_match_adhoc) {
  auto mylut{make_lut(std::make_index_sequence<16>{})};

  EXPECT_EQ(true, mylut.invoke(8, 8));
  EXPECT_EQ(false, mylut.invoke(8, 9));
  EXPECT_EQ(superplant<true>, mylut.get(8));
}
