#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>

TEST(IsaTest, ShouldExtractRightBits) {
  constexpr u32 ins = 0xa13cdbd3;
  ASSERT_EQ(arm_get_cond(ins), 0xa);
  ASSERT_EQ(arm_half_data_trans_imm_is_p(ins), true);
  ASSERT_EQ(arm_half_data_trans_imm_is_u(ins), false);
  ASSERT_EQ(arm_half_data_trans_imm_is_w(ins), true);
  ASSERT_EQ(arm_half_data_trans_imm_is_l(ins), true);
  ASSERT_EQ(arm_half_data_trans_imm_get_rn(ins), 0xc);
  ASSERT_EQ(arm_half_data_trans_imm_get_rd(ins), 0xd);
  ASSERT_EQ(arm_half_data_trans_imm_is_s(ins), true);
  ASSERT_EQ(arm_half_data_trans_imm_is_h(ins), false);
  ASSERT_EQ(arm_half_data_trans_imm_get_offset(ins), 0xb3);
}
