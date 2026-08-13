#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

struct supertemplate_flags {
  bool a : 1 {false};
  bool b : 1 {false};
  bool c : 1 {false};
  bool d : 1 {false};
  bool experiment : 1 {false};
};

template <supertemplate_flags tflags> bool superplant(int codigo) {
  if constexpr (tflags.experiment)
    return false;
  else
    return (tflags.a << 3 | tflags.b << 2 | tflags.c << 1 | tflags.d) == codigo;
}
using function_type = bool (*)(int);
using lut_type = lut<function_type, 16>;

template <std::size_t I> constexpr function_type expected_function() {
  static_assert(I < 16);

  return &superplant<supertemplate_flags{.a = (I & 0b1000) != 0,
                                         .b = (I & 0b0100) != 0,
                                         .c = (I & 0b0010) != 0,
                                         .d = (I & 0b0001) != 0}>;
}

template <std::size_t... I> constexpr lut_type make_lut(std::index_sequence<I...>) {
  lut_type result;

  (result.fill(I, 0, expected_function<I>()), ...);

  return result;
}

TEST(proof_of_concept, template_functions_check_if_runs_match_adhoc) {
  auto mylut{make_lut(std::make_index_sequence<16>())};

  EXPECT_EQ(true, mylut.invoke(8, 8));
  EXPECT_EQ(false, mylut.invoke(8, 9));
  EXPECT_NE(mylut.get(11), mylut.get(10));
  EXPECT_EQ(superplant<{true}>, mylut.get(8));
  EXPECT_EQ(superplant<supertemplate_flags{.a = true}>, superplant<{.a = true}>);
  EXPECT_EQ(superplant<supertemplate_flags{true}>, superplant<{.a = true}>);
  EXPECT_EQ((superplant<{true}>), (superplant<{.a = true, .b = false}>));
  EXPECT_EQ((superplant<{.a = true}>), (superplant<{.a = true, .b = false}>));
}
