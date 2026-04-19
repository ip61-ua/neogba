#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/arm7tdmi/sampleram.hpp"
#include <gtest/gtest.h>

TEST(BasicTest, HelloWorld) {
  EXPECT_EQ(1, 1);
}

TEST(RegistersTest, RegistersBasicWriteStore) {
  // Arrange
  neogba::arm7tdmi::Registers r;
  neogba::u8 reg1{10};
  auto reg2{neogba::arm7tdmi::RegistersIndex::r10_fiq};
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

TEST(RegistersTest, RegistersBitOperationsAndGetOperationMode) {
  // Arrange
  neogba::arm7tdmi::Registers r;

  // Act
  bool result1{r.isN()};
  r.setN();
  bool result2{r.isN()};
  r.clearN();
  bool result3{r.isN()};
  r.setAbt();
  neogba::arm7tdmi::OperationModeBits result4{r.getOperationMode()};
  r.setFiq();
  neogba::arm7tdmi::OperationModeBits result5{r.getOperationMode()};

  // Assert
  EXPECT_EQ(false, result1);
  EXPECT_EQ(true, result2);
  EXPECT_EQ(false, result3);
  EXPECT_EQ(neogba::arm7tdmi::OperationModeBits::Abt, result4);
  EXPECT_EQ(neogba::arm7tdmi::OperationModeBits::Fiq, result5);
}

TEST(SampleRAMTest, StoreLoadByteOperations) {
  // Arrange
  const neogba::u32 s{256}, base{0x08000000}, addr1{0x08000001}, addr2{0x08000002}, w1{123}, w2{77};

  auto bus{neogba::arm7tdmi::MemoryBus()};
  auto* mem{new neogba::arm7tdmi::samples::SampleRAM(s)};
  auto mode{neogba::arm7tdmi::MemoryBlockLength::BYTE};

  // Act
  auto success{bus.attachMemory(base, mem)};
  auto name{mem->getName()};
  auto writable{mem->isReadOnly()};
  auto maxSize{mem->getSize()};
  auto properties{mem->getProperties()};
  auto r0{mem->read(addr2, mode)};
  auto r0f{bus.read(addr2, mode)};
  auto r1a{mem->read(addr1, mode)};
  auto r1af{bus.read(addr1, mode)};
  mem->write(addr1, w1, mode);
  auto r1{mem->read(addr1, mode)};
  auto r1f{bus.read(addr1, mode)};
  auto r2p{bus.write(addr2, w2, mode)};
  auto r2{mem->read(addr2, mode)};
  auto r2f{bus.read(addr2, mode)};

  // Assert
  EXPECT_EQ(true, success);
  EXPECT_EQ("SampleRAM", name);
  EXPECT_EQ(false, writable);
  EXPECT_EQ(s, maxSize);
  EXPECT_EQ(bus.getProperties(), properties);
  EXPECT_EQ(0x0, r0);
  EXPECT_EQ(0x0, r0f);
  EXPECT_EQ(0x0, r1a);
  EXPECT_EQ(0x0, r1af);
  EXPECT_EQ(w1, r1);
  EXPECT_EQ(w1, r1f);
  EXPECT_EQ(true, r2p);
  EXPECT_EQ(w2, r2);
  EXPECT_EQ(w2, r2f);
}

TEST(SampleRAMTest, StoreLoadMultiByteOperations) {
  // Arrange
  const neogba::u32 s{256}, base{0x08000000};
  const neogba::u32 addrHalf{0x08000002}, addrWord{0x08000004};
  const neogba::u32 valHalf{0xBEEF}, valWord{0xDEADBEEF};
  auto bus{neogba::arm7tdmi::MemoryBus()};
  auto* mem{new neogba::arm7tdmi::samples::SampleRAM(s)};
  auto modeHalf{neogba::arm7tdmi::MemoryBlockLength::HALFWORD};
  auto modeWord{neogba::arm7tdmi::MemoryBlockLength::WORD};

  // Act
  bus.attachMemory(base, mem);
  auto wHalfSuccess{bus.write(addrHalf, valHalf, modeHalf)};
  auto rHalf{bus.read(addrHalf, modeHalf)};
  auto wWordSuccess{bus.write(addrWord, valWord, modeWord)};
  auto rWord{bus.read(addrWord, modeWord)};

  // Assert
  EXPECT_EQ(true, wHalfSuccess);
  EXPECT_EQ(valHalf, rHalf);

  EXPECT_EQ(true, wWordSuccess);
  EXPECT_EQ(valWord, rWord);
}

TEST(SampleRAMTest, AlignmentAndLittleEndianValidation) {
  // Arrange
  const neogba::u32 s{256}, base{0x08000000};
  const neogba::u32 addrWordBase{0x08000008};
  const neogba::u32 addrWordUnaligned{0x0800000B}; // Sin alinear -> 0x08000008
  const neogba::u32 valWord{0x11223344};           // Sin alinear
  auto bus{neogba::arm7tdmi::MemoryBus()};
  auto* mem{new neogba::arm7tdmi::samples::SampleRAM(s)};

  bus.attachMemory(base, mem);

  // Act
  bus.write(addrWordUnaligned, valWord, neogba::arm7tdmi::MemoryBlockLength::WORD);
  auto rWordAligned{bus.read(addrWordBase, neogba::arm7tdmi::MemoryBlockLength::WORD)};
  auto rWordUnaligned{bus.read(addrWordUnaligned, neogba::arm7tdmi::MemoryBlockLength::WORD)};

  // Comprobación de little endian:
  // [0x08] = 0x44 (Byte menos significativo)
  // [0x09] = 0x33
  // [0x0A] = 0x22
  // [0x0B] = 0x11 (Byte más significativo)
  auto rByte0{bus.read(addrWordBase + 0, neogba::arm7tdmi::MemoryBlockLength::BYTE)};
  auto rByte1{bus.read(addrWordBase + 1, neogba::arm7tdmi::MemoryBlockLength::BYTE)};
  auto rByte2{bus.read(addrWordBase + 2, neogba::arm7tdmi::MemoryBlockLength::BYTE)};
  auto rByte3{bus.read(addrWordBase + 3, neogba::arm7tdmi::MemoryBlockLength::BYTE)};

  // Assert
  EXPECT_EQ(valWord, rWordAligned);
  EXPECT_EQ(valWord, rWordUnaligned);
  EXPECT_EQ(0x44, rByte0);
  EXPECT_EQ(0x33, rByte1);
  EXPECT_EQ(0x22, rByte2);
  EXPECT_EQ(0x11, rByte3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
