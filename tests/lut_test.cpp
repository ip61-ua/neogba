#include "neogba/structs/lut.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace neogba;

constexpr u8 LUT_MASK_EXAMPLE{0b0010011}, LUT_BASE_EXAMPLE{0b1100110};
constexpr int LUT_DATA_EXAMPLE{42};
constexpr auto LUT_RESULT_LENGTH_EXAMPLE{8};

TEST(lut_test, fill_recursive_and_ensure_how_many_stored_with_count_stored) {
  lut<int, 1 << 8> my_lut;

  auto n = my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, LUT_DATA_EXAMPLE);

  ASSERT_EQ(LUT_RESULT_LENGTH_EXAMPLE, n);
}

TEST(lut_test, fill_recursive_and_ensure_whats_stored_get_wrapper) {
  lut<int, 1 << 8> my_lut;
  std::array<int, 1 << 8> arr;

  arr[0b1100110] = LUT_DATA_EXAMPLE;
  arr[0b1100111] = LUT_DATA_EXAMPLE;
  arr[0b1100101] = LUT_DATA_EXAMPLE;
  arr[0b1100100] = LUT_DATA_EXAMPLE;
  arr[0b1110111] = LUT_DATA_EXAMPLE;
  arr[0b1110101] = LUT_DATA_EXAMPLE;
  arr[0b1110110] = LUT_DATA_EXAMPLE;
  arr[0b1110100] = LUT_DATA_EXAMPLE;

  my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, LUT_DATA_EXAMPLE);

  ASSERT_EQ(arr, my_lut.get_wrapper());
}

TEST(lut_test, fill_recursive_and_ensure_whats_stored_by_get) {
  lut<int, 1 << 8> my_lut;

  my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, LUT_DATA_EXAMPLE);

  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1100110));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1100111));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1100101));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1100100));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1110111));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1110101));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1110110));
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(0b1110100));
  ASSERT_EQ(0, my_lut.get(1));
  ASSERT_EQ(0, my_lut.get(2));
}

TEST(lut_test, fill_recursive_and_execution_by_running_lambdas) {
  using handler_test = void (*)(bool a, int b);

  lut<handler_test, 1 << 8> my_lut;

  static int a1{};
  static int b1{};

  auto important_operation = [](bool a, int b) -> void {
    if (a) {
      a1 = b;
    } else {
      b1 = b;
    }
  };

  my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, important_operation);

  ASSERT_EQ(important_operation, my_lut.get(0b1100110));
  ASSERT_EQ(important_operation, my_lut.get(0b1100111));
  ASSERT_EQ(important_operation, my_lut.get(0b1100101));
  ASSERT_EQ(important_operation, my_lut.get(0b1100100));
  ASSERT_EQ(important_operation, my_lut.get(0b1110111));
  ASSERT_EQ(important_operation, my_lut.get(0b1110101));
  ASSERT_EQ(important_operation, my_lut.get(0b1110110));
  ASSERT_EQ(important_operation, my_lut.get(0b1110100));

  my_lut.run(0b1110100, true, 2);
  my_lut.run(0b1110101, false, 9);
  ASSERT_EQ(2, a1);
  ASSERT_EQ(9, b1);
}

TEST(lut_test, fill_recursive_and_execution_by_running_lambdas_returning_values_and_no_vargs) {
  using handler_test = int (*)();

  lut<handler_test, 1 << 8, int> my_lut;

  auto important_operation = []() -> int { return 42; };

  my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, important_operation);

  auto a1 = my_lut.run(0b1110100);
  auto b1 = my_lut.run(0b1110101);
  ASSERT_EQ(42, a1);
  ASSERT_EQ(42, b1);
}
