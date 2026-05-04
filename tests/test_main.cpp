#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/arm7tdmi/sampleram.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(BasicTest, HelloWorld) {
  EXPECT_EQ(1, 1);
}

TEST(RegistersTest, RegistersBasicWriteStore) {
  // Arrange
  using namespace neogba;
  using namespace neogba::arm7tdmi;

  Registers r;
  u8 reg1{10};
  auto reg2{RegistersIndex::r10_fiq};
  u32 a{69}, b{0}, c{42};
  u32 result1, result2, result3, result4, result5;

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
  using namespace neogba;
  using namespace neogba::arm7tdmi;
  using namespace neogba::arm7tdmi::samples;

  Registers r;

  // Act
  bool result1{r.isN()};
  r.setN();
  bool result2{r.isN()};
  r.clearN();
  bool result3{r.isN()};
  r.setAbt();
  OperationModeBits result4{r.getOperationMode()};
  r.setFiq();
  OperationModeBits result5{r.getOperationMode()};

  // Assert
  EXPECT_EQ(false, result1);
  EXPECT_EQ(true, result2);
  EXPECT_EQ(false, result3);
  EXPECT_EQ(OperationModeBits::Abt, result4);
  EXPECT_EQ(OperationModeBits::Fiq, result5);
}

TEST(SampleRAMTest, StoreLoadByteOperations) {
  // Arrange
  using namespace neogba;
  using namespace neogba::arm7tdmi;
  using namespace neogba::arm7tdmi::samples;

  const u32 s{256}, base{0x08000000}, addr1{0x08000001}, addr2{0x08000002}, w1{123}, w2{77};

  auto bus{MemoryBus()};
  auto mem{std::make_shared<SampleRAM>(s)};
  auto mode{MemoryBlockLength::BYTE};

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
  using namespace neogba;
  using namespace neogba::arm7tdmi;
  using namespace neogba::arm7tdmi::samples;

  const u32 s{256}, base{0x08000000};
  const u32 addrHalf{0x08000002}, addrWord{0x08000004};
  const u32 valHalf{0xBEEF}, valWord{0xDEADBEEF};
  auto bus{MemoryBus()};
  auto mem{std::make_shared<SampleRAM>(s)};
  auto modeHalf{MemoryBlockLength::HALFWORD};
  auto modeWord{MemoryBlockLength::WORD};

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
  using namespace neogba;
  using namespace neogba::arm7tdmi;
  using namespace neogba::arm7tdmi::samples;

  const u32 s{256}, base{0x08000000};
  const u32 addrWordBase{0x08000008};
  const u32 addrWordUnaligned{0x0800000B}; // Sin alinear -> 0x08000008
  const u32 valWord{0x11223344};           // Sin alinear
  auto bus{MemoryBus()};
  auto mem{std::make_shared<SampleRAM>(s)};

  bus.attachMemory(base, mem);

  // Act
  bus.write(addrWordUnaligned, valWord, MemoryBlockLength::WORD);
  auto rWordAligned{bus.read(addrWordBase, MemoryBlockLength::WORD)};
  auto rWordUnaligned{bus.read(addrWordUnaligned, MemoryBlockLength::WORD)};

  // Comprobación de little endian:
  // [0x08] = 0x44 (Byte menos significativo)
  // [0x09] = 0x33
  // [0x0A] = 0x22
  // [0x0B] = 0x11 (Byte más significativo)
  auto rByte0{bus.read(addrWordBase + 0, MemoryBlockLength::BYTE)};
  auto rByte1{bus.read(addrWordBase + 1, MemoryBlockLength::BYTE)};
  auto rByte2{bus.read(addrWordBase + 2, MemoryBlockLength::BYTE)};
  auto rByte3{bus.read(addrWordBase + 3, MemoryBlockLength::BYTE)};

  // Assert
  EXPECT_EQ(valWord, rWordAligned);
  EXPECT_EQ(valWord, rWordUnaligned);
  EXPECT_EQ(0x44, rByte0);
  EXPECT_EQ(0x33, rByte1);
  EXPECT_EQ(0x22, rByte2);
  EXPECT_EQ(0x11, rByte3);
}

TEST(InstructionADCTest, SimpleAddition) {
  // Arrange
  using namespace neogba;
  using namespace neogba::arm7tdmi;

  Registers fakeRegisters;
  fakeRegisters.write(RegistersIndex::r4, 0x1);
  fakeRegisters.write(RegistersIndex::r2, 0x2);
  fakeRegisters.write(RegistersIndex::r1, 0x69);

  Registers expectedRegisters(fakeRegisters);
  expectedRegisters.write(RegistersIndex::r1, 0x3);

  u32 instruction = 0xe0b21004; // adcs r1, r2, r4 // r1 <- r2 + r4 + c

  auto cpu = Arm7tdmiCPU(fakeRegisters);

  // Act
  cpu.executeArm(instruction);

  // Assert
  Registers finalRegisters = cpu.getRegisters();
  EXPECT_TRUE(expectedRegisters.equals(finalRegisters));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
