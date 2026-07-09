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
  ASSERT_EQ(LUT_RESULT_LENGTH_EXAMPLE, my_lut.count_stored(LUT_DATA_EXAMPLE));
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
  using handler_test = void (*)(int);
  lut<handler_test, 1 << 8> my_lut;

  class FunctionMock {
  public:
    MOCK_METHOD(void, execute, (int a));
  };

  static FunctionMock* mock_bridge = nullptr;
  FunctionMock mock_instance;
  mock_bridge = &mock_instance;

  EXPECT_CALL(mock_instance, execute(2)).Times(1);
  EXPECT_CALL(mock_instance, execute(9)).Times(1);

  auto important_operation = [](int a) -> void {
    if (mock_bridge) {
      mock_bridge->execute(a);
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
  ASSERT_NE(important_operation, my_lut.get(0b0010100));
  ASSERT_NE(important_operation, my_lut.get(0b0000000));

  my_lut.run(0b1110100, 2);
  my_lut.run(0b1110101, 9);

  mock_bridge = nullptr;
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

TEST(lut_test, fill_get_with_custom_norm_idx_and_ensure_whats_stored) {
  lut<long, 1 << 2, void, [](std::size_t idx) -> std::size_t { return 0b11 & idx; }> my_lut;
  std::array<long, 1 << 2> arr;

  arr[0b00] = LUT_DATA_EXAMPLE;
  arr[0b01] = LUT_DATA_EXAMPLE;
  arr[0b10] = LUT_DATA_EXAMPLE;
  arr[0b11] = LUT_DATA_EXAMPLE;

  my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, LUT_DATA_EXAMPLE);

  ASSERT_EQ(arr, my_lut.get_wrapper());
  ASSERT_EQ(LUT_DATA_EXAMPLE, my_lut.get(LUT_BASE_EXAMPLE));
}

TEST(lut_test, fill_get_with_custom_norm_idx_and_ensure_whats_stored_2) {
  lut<u16, 1 << 4, void,
      [](std::size_t idx) -> std::size_t {
        return (((idx & 0b1110000) >> 3) | ((idx & 0b10) >> 1));
      }>
      my_lut;

  std::array<u16, 1 << 4> arr;

  // arr[0b1100110] = LUT_DATA_EXAMPLE;
  // arr[0b1100111] = LUT_DATA_EXAMPLE;
  // arr[0b1100101] = LUT_DATA_EXAMPLE;
  // arr[0b1100100] = LUT_DATA_EXAMPLE;
  // arr[0b1110111] = LUT_DATA_EXAMPLE;
  // arr[0b1110101] = LUT_DATA_EXAMPLE;
  // arr[0b1110110] = LUT_DATA_EXAMPLE;
  // arr[0b1110100] = LUT_DATA_EXAMPLE;

  ASSERT_EQ(0b1101, my_lut.norm_idx(0b1100110));
  arr[0b1101] = LUT_DATA_EXAMPLE;
  // arr[0b1101] = LUT_DATA_EXAMPLE;
  arr[0b1100] = LUT_DATA_EXAMPLE;
  // arr[0b1100] = LUT_DATA_EXAMPLE;
  // arr[0b1111] = LUT_DATA_EXAMPLE;
  arr[0b1110] = LUT_DATA_EXAMPLE;
  arr[0b1111] = LUT_DATA_EXAMPLE;
  // arr[0b1110] = LUT_DATA_EXAMPLE;

  my_lut.fill(LUT_BASE_EXAMPLE, LUT_MASK_EXAMPLE, LUT_DATA_EXAMPLE);

  ASSERT_EQ(arr, my_lut.get_wrapper());
}

TEST(lut_test, fill_and_execution_with_references_params) {
  using handler_test = int (*)(int& a);

  lut<handler_test, 1 << 8, int> my_lut;

  int a{7};
  auto important_operation = [](int& a) -> int { return a++; };

  my_lut.fill(LUT_BASE_EXAMPLE, important_operation);

  auto a1 = my_lut.run(LUT_BASE_EXAMPLE, a);
  ASSERT_EQ(7, a1);
  ASSERT_EQ(8, a);
}
