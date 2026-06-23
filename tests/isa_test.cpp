#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>

TEST(IsaTest, ShouldExtractRightBitsFromRaw) {
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
