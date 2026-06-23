#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>

static constexpr u32 K_TEST_HALFIMM_INS = 0xa17cdbd3u;
static constexpr auto K_TEST_HALFIMM_INS_COND = 0xa;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_P = true;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_U = false;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_W = true;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_L = true;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_RN = 0xc;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_RD = 0xd;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_S = true;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_H = false;
static constexpr auto K_TEST_HALFIMM_INS_HALFIMM_OFFSET = 0xb3;

TEST(isa_test, should_change_only_arm_cond_field) {
  u32 ins = -1;
  ASSERT_EQ(0xf, isa_get_ARM_COND(ins));

  ins = isa_set_ARM_COND(ins, 2);
  ASSERT_EQ(2, isa_get_ARM_COND(ins));
}

TEST(isa_test,
     should_right_when_building_and_changing_a_bit_fsr_instrucctions) {
  u32 ins = ARM_FSR_TEMPLATE;
  auto old = ins, old_mod = (u32)(old | ISA_GET_MASK(ARM_FSR_S));

  ins = isa_set0_ARM_FSR_S(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, isa_is_ARM_FSR_S(ins));

  ins = isa_set1_ARM_FSR_S(ins);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, isa_is_ARM_FSR_S(ins));

  ins = isa_set0_ARM_FSR_S(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, isa_is_ARM_FSR_S(ins));

  ins = isa_toggle_ARM_FSR_S(ins);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, isa_is_ARM_FSR_S(ins));

  ins = isa_toggle_ARM_FSR_S(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, isa_is_ARM_FSR_S(ins));

  ins = isa_set_ARM_FSR_S(ins, true);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, isa_is_ARM_FSR_S(ins));

  ins = isa_set_ARM_FSR_S(ins, false);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, isa_is_ARM_FSR_S(ins));
}

TEST(isa_test, should_retrieve_right_bits_from_raw_arm_halfimm_instruction) {
  const auto ins = K_TEST_HALFIMM_INS;

  ASSERT_EQ(K_TEST_HALFIMM_INS_COND, isa_get_ARM_COND(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_P, isa_is_ARM_HALFIMM_P(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_U, isa_is_ARM_HALFIMM_U(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_W, isa_is_ARM_HALFIMM_W(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_L, isa_is_ARM_HALFIMM_L(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_RN, isa_get_ARM_HALFIMM_RN(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_RD, isa_get_ARM_HALFIMM_RD(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_S, isa_is_ARM_HALFIMM_S(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_H, isa_is_ARM_HALFIMM_H(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_OFFSET, isa_get_ARM_HALFIMM_OFFSET(ins));
}

TEST(isa_test, should_build_ri_bits_from_raw_arm_halfimm_instruction) {
  auto ins = ARM_HALFIMM_TEMPLATE;

  ins = isa_set_ARM_COND(ins, K_TEST_HALFIMM_INS_COND);
  ins = isa_set1_ARM_HALFIMM_P(ins);
  ins = isa_set0_ARM_HALFIMM_U(ins);
  ins = isa_toggle_ARM_HALFIMM_W(ins);
  ins = isa_set_ARM_HALFIMM_L(ins, K_TEST_HALFIMM_INS_HALFIMM_L);
  ins = isa_set_ARM_HALFIMM_RN(ins, K_TEST_HALFIMM_INS_HALFIMM_RN);
  ins = isa_set_ARM_HALFIMM_RD(ins, K_TEST_HALFIMM_INS_HALFIMM_RD);
  ins = isa_set_ARM_HALFIMM_S(ins, K_TEST_HALFIMM_INS_HALFIMM_S);
  ins = isa_set0_ARM_HALFIMM_H(ins);
  ins = isa_set_ARM_HALFIMM_OFFSET(ins, K_TEST_HALFIMM_INS_HALFIMM_OFFSET);

  ASSERT_EQ(K_TEST_HALFIMM_INS, ins);
}

TEST(isa_test,
     should_return_same_when_building_its_refered_to_the_same_range_of_bits) {

  auto i = ARM_LONG_TEMPLATE;
  auto v = 0xa;

  i = isa_set_ARM_LONG_RM(i, 0xa);
  ASSERT_EQ(v, isa_get_ARM_MULTIPLY_RM(i));
  ASSERT_EQ(v, isa_get_ARM_LONG_RM(i));
  ASSERT_EQ(v, isa_get_ARM_SWAP_RM(i));
  ASSERT_EQ(v, isa_get_ARM_EXCHANGE_RN(i));
  ASSERT_EQ(v, isa_get_ARM_HALFREG_RM(i));
}
