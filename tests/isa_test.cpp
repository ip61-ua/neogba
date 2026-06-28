#include "neogba/arm7tdmi/isa.hpp"
#include <gtest/gtest.h>

using namespace neogba;

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
  ASSERT_EQ(0xf, ISA_ARM_COND::get(ins));

  ins = ISA_ARM_COND::set(ins, 2);
  ASSERT_EQ(2, ISA_ARM_COND::get(ins));
}

TEST(isa_test,
     should_right_when_building_and_changing_a_bit_fsr_instrucctions) {
  u32 ins = ISA_ARM_FSR_TEMPLATE;
  auto old = ins, old_mod = (u32)(old | ISA_ARM_FSR_S::mask);

  ins = ISA_ARM_FSR_S::set0(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, ISA_ARM_FSR_S::get(ins));

  ins = ISA_ARM_FSR_S::set1(ins);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, ISA_ARM_FSR_S::get(ins));

  ins = ISA_ARM_FSR_S::set0(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, ISA_ARM_FSR_S::get(ins));

  ins = ISA_ARM_FSR_S::toggle(ins);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, ISA_ARM_FSR_S::get(ins));

  ins = ISA_ARM_FSR_S::toggle(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, ISA_ARM_FSR_S::get(ins));

  ins = ISA_ARM_FSR_S::set(ins, true);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, ISA_ARM_FSR_S::get(ins));

  ins = ISA_ARM_FSR_S::set(ins, false);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, ISA_ARM_FSR_S::get(ins));
}

TEST(isa_test, should_retrieve_right_bits_from_raw_arm_halfimm_instruction) {
  const auto ins = K_TEST_HALFIMM_INS;

  ASSERT_EQ(K_TEST_HALFIMM_INS_COND, ISA_ARM_COND::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_P, ISA_ARM_HALFIMM_P::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_U, ISA_ARM_HALFIMM_U::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_W, ISA_ARM_HALFIMM_W::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_L, ISA_ARM_HALFIMM_L::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_RN, ISA_ARM_HALFIMM_RN::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_RD, ISA_ARM_HALFIMM_RD::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_S, ISA_ARM_HALFIMM_S::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_H, ISA_ARM_HALFIMM_H::get(ins));
  ASSERT_EQ(K_TEST_HALFIMM_INS_HALFIMM_OFFSET,
            ISA_ARM_HALFIMM_OFFSET::get(ins));
}

TEST(isa_test, should_build_ri_bits_from_raw_arm_halfimm_instruction) {
  auto ins = ISA_ARM_HALFIMM_TEMPLATE;

  ins = ISA_ARM_COND::set(ins, K_TEST_HALFIMM_INS_COND);
  ins = ISA_ARM_HALFIMM_P::set1(ins);
  ins = ISA_ARM_HALFIMM_U::set0(ins);
  ins = ISA_ARM_HALFIMM_W::toggle(ins);
  ins = ISA_ARM_HALFIMM_L::set(ins, K_TEST_HALFIMM_INS_HALFIMM_L);
  ins = ISA_ARM_HALFIMM_RN::set(ins, K_TEST_HALFIMM_INS_HALFIMM_RN);
  ins = ISA_ARM_HALFIMM_RD::set(ins, K_TEST_HALFIMM_INS_HALFIMM_RD);
  ins = ISA_ARM_HALFIMM_S::set(ins, K_TEST_HALFIMM_INS_HALFIMM_S);
  ins = ISA_ARM_HALFIMM_H::set0(ins);
  ins = ISA_ARM_HALFIMM_OFFSET::set(ins, K_TEST_HALFIMM_INS_HALFIMM_OFFSET);

  ASSERT_EQ(K_TEST_HALFIMM_INS, ins);
}

TEST(isa_test,
     should_return_same_when_building_its_refered_to_the_same_range_of_bits) {

  auto i = ISA_ARM_LONG_TEMPLATE;
  auto v = 0xa;

  i = ISA_ARM_LONG_RM::set(i, 0xa);
  ASSERT_EQ(v, ISA_ARM_MULTIPLY_RM::get(i));
  ASSERT_EQ(v, ISA_ARM_LONG_RM::get(i));
  ASSERT_EQ(v, ISA_ARM_SWAP_RM::get(i));
  ASSERT_EQ(v, ISA_ARM_EXCHANGE_RN::get(i));
  ASSERT_EQ(v, ISA_ARM_HALFREG_RM::get(i));
}
