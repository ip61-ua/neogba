#include "neogba/arm7tdmi/registers.hpp"
#include <gtest/gtest.h>

TEST(BasicTest, HelloWorld) {
  EXPECT_EQ(1, 1);
}

TEST(RegistersTest, RegisterBasicWriteStore) {
  // Arrange
  neogba::arm7tdmi::Registers r;
  neogba::u8 reg1 = 10;
  neogba::arm7tdmi::RegistersIndex reg2 = neogba::arm7tdmi::RegistersIndex::r10_fiq;
  neogba::u32 a{69}, b{0}, c{42};
  neogba::u32 result1, result2, result3, result4, result5;

  // Act
  r.write(reg1, a);
  result1 = r.read(reg1);
  r.setFiq();
  result2 = r.read(reg1);
  r.write(reg1, c);
  result3 = r.read(reg1);
  r.setUnd();
  result4 = r.read(reg2);
  result5 = r.read(reg1);

  // Assert
  EXPECT_EQ(a, result1);
  EXPECT_EQ(b, result2);
  EXPECT_EQ(c, result3);
  EXPECT_EQ(c, result4);
  EXPECT_EQ(a, result5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
