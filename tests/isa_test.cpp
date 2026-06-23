#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>

TEST(isa_test, should_change_only_arm_cond_field) {
  u32 ins = -1;
  ASSERT_EQ(isa_get_ARM_COND(ins), 0xf);

  ins = isa_set_ARM_COND(ins, 2);
  ASSERT_EQ(isa_get_ARM_COND(ins), 2);
}

TEST(isa_test, should_extract_right_bits_from_raw_arm_halfimm_instruction) {
  constexpr u32 ins = 0xa13cdbd3;
  ASSERT_EQ(isa_get_ARM_COND(ins), 0xa);
  ASSERT_EQ(isa_is_ARM_HALFIMM_P(ins), true);
  ASSERT_EQ(isa_is_ARM_HALFIMM_U(ins), false);
  ASSERT_EQ(isa_is_ARM_HALFIMM_W(ins), true);
  ASSERT_EQ(isa_is_ARM_HALFIMM_L(ins), true);
  ASSERT_EQ(isa_get_ARM_HALFIMM_RN(ins), 0xc);
  ASSERT_EQ(isa_get_ARM_HALFIMM_RD(ins), 0xd);
  ASSERT_EQ(isa_is_ARM_HALFIMM_S(ins), true);
  ASSERT_EQ(isa_is_ARM_HALFIMM_H(ins), false);
  ASSERT_EQ(isa_get_ARM_HALFIMM_OFFSET(ins), 0xb3);
}
