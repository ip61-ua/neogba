#include "neogba/arm7tdmi/isa/constants.hpp"
#include <gtest/gtest.h>

using namespace neogba;

static constexpr u32 KTEST_INS{0xa17cdbd3u};
static constexpr auto KTEST_COND{0xa};
static constexpr auto KTEST_HALFIMM_P{true};
static constexpr auto KTEST_HALFIMM_U{false};
static constexpr auto KTEST_HALFIMM_W{true};
static constexpr auto KTEST_HALFIMM_L{true};
static constexpr auto KTEST_HALFIMM_RN{0xc};
static constexpr auto KTEST_HALFIMM_RD{0xd};
static constexpr auto KTEST_HALFIMM_S{true};
static constexpr auto KTEST_HALFIMM_H{false};
static constexpr auto KTEST_HALFIMM_OFFSET{0xb3};

TEST(isa_test, should_change_only_arm_cond_field) {
  using namespace arm_cond;

  u32 ins = -1;
  ASSERT_EQ(0xf, COND::get(ins));

  ins = COND::set(ins, 2);
  ASSERT_EQ(2, COND::get(ins));
}

TEST(isa_test, should_right_when_building_and_changing_a_bit_fsr_instrucctions) {
  using namespace arm_fsr;
  auto ins{TEMPLATE}, old{ins}, old_mod{static_cast<u32>(old | S::mask)};

  ins = S::set0(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, S::get(ins));

  ins = S::set1(ins);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, S::get(ins));

  ins = S::set0(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, S::get(ins));

  ins = S::toggle(ins);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, S::get(ins));

  ins = S::toggle(ins);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, S::get(ins));

  ins = S::set(ins, true);
  ASSERT_EQ(old_mod, ins);
  ASSERT_EQ(true, S::get(ins));

  ins = S::set(ins, false);
  ASSERT_EQ(old, ins);
  ASSERT_NE(true, S::get(ins));
}

TEST(isa_test, should_retrieve_right_bits_from_raw_arm_halfimm_instruction) {
  using namespace arm_halfimm;
  using namespace arm_cond;

  const auto ins{KTEST_INS};

  ASSERT_EQ(KTEST_COND, COND::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_P, P::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_U, U::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_W, W::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_L, L::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_RN, RN::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_RD, RD::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_S, S::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_H, H::get(ins));
  ASSERT_EQ(KTEST_HALFIMM_OFFSET, OFFSET::get(ins));
}

TEST(isa_test, should_build_ri_bits_from_raw_arm_halfimm_instruction) {
  using namespace arm_halfimm;
  using namespace arm_cond;

  auto ins{TEMPLATE};

  ins = COND::set(ins, KTEST_COND);
  ins = P::set1(ins);
  ins = U::set0(ins);
  ins = W::toggle(ins);
  ins = L::set(ins, KTEST_HALFIMM_L);
  ins = RN::set(ins, KTEST_HALFIMM_RN);
  ins = RD::set(ins, KTEST_HALFIMM_RD);
  ins = S::set(ins, KTEST_HALFIMM_S);
  ins = H::set0(ins);
  ins = OFFSET::set(ins, KTEST_HALFIMM_OFFSET);

  ASSERT_EQ(KTEST_INS, ins);
}

TEST(isa_test, should_build_ri_bits_from_raw_arm_halfimm_instruction_with_newer_syntax) {
  using namespace arm_halfimm;
  using namespace arm_cond;

  auto ins{TEMPLATE | COND::h(KTEST_COND) | P::H | U::h(false) | W::h(1) | L::h(KTEST_HALFIMM_L) |
           RN::h(KTEST_HALFIMM_RN) | RD::h(KTEST_HALFIMM_RD) | S::h(KTEST_HALFIMM_S) |
           OFFSET::h(KTEST_HALFIMM_OFFSET)};

  ASSERT_EQ(KTEST_INS, ins);
}

TEST(isa_test, should_return_same_when_building_its_refered_to_the_same_range_of_bits) {
  using namespace arm_multiplylong;

  auto i{arm_multiplylong::TEMPLATE};
  auto v{0xa};

  i = arm_multiplylong::RM::set(i, 0xa);
  ASSERT_EQ(v, arm_multiply::RM::get(i));
  ASSERT_EQ(v, arm_multiplylong::RM::get(i));
  ASSERT_EQ(v, arm_singleswap::RM::get(i));
  ASSERT_EQ(v, arm_branchexchange::RN::get(i));
  ASSERT_EQ(v, arm_halfreg::RM::get(i));
}
