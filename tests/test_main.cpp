#include "arm7/registers.hpp"
#include <gtest/gtest.h>

TEST(BasicTest, HelloWorld) {
  EXPECT_EQ(1, 1);
}

TEST(RegisterTest, RegisterBasicWriteStore) {
  neogba::arm7tdmi::Registers r;

  r.write(10, 69);
  EXPECT_EQ(69, r.read(10));

  r.setFiq();
  EXPECT_EQ(0, r.read(10));

  r.write(10, 42);
  EXPECT_EQ(42, r.read(10));

  r.setUnd();
  EXPECT_EQ(69, r.read(10));
  EXPECT_EQ(42, r.read(neogba::arm7tdmi::RegistersIndex::r10_fiq));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
