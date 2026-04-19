#include "neogba/arm7tdmi/sampleram.hpp"
#include "neogba/arm7tdmi/memory.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;
using namespace neogba::arm7tdmi::samples;

bool SampleRAM::attached(u32 baseAddr) {
  if (!used1) {
    base1 = baseAddr;
    used1 = true;
    return true;
  }

  if (!used2) {
    base2 = baseAddr;
    used2 = true;
    return true;
  }

  return false;
}

bool SampleRAM::detached() {
  used1 = used2 = false;
  base1 = base2 = 0;
  return true;
}

u32 SampleRAM::read(u32 addr, MemoryBlockLength len) const {
  auto offset = busProperties.getAddrOffset(addr);

  if (offset + len / 8 > nBytes)
    return 0;

  /*
  addr         = 0x FF 12 23 43
  nBytes       = 0x 01 00 00 00
  nBytes - 1   = 0x 00 FF FF FF
  addr & mask  = 0x 00 12 23 43
 */

  auto& m = memoryBytes;

  switch (len) {
  case BYTE: {
    return m[offset];
  }

  case HALFWORD: {
    offset = offset & ~0b01;
    return (m[offset + 1] << 8) | m[offset];
  }

  case WORD: {
    offset = offset & ~0b11;
    return (m[offset + 3] << 24) | (m[offset + 2] << 16) | (m[offset + 1] << 8) | m[offset];
  }
  }

  return 0;
}

void SampleRAM::write(u32 addr, u32 val, MemoryBlockLength len) {
  auto offset = busProperties.getAddrOffset(addr);

  if (offset + len / 8 > nBytes)
    return;

  auto& m = memoryBytes;

  switch (len) {

  case BYTE:
    m[offset] = val;
    break;

  case HALFWORD:
    offset = offset & ~0b01;
    m[offset] = val;
    m[offset + 1] = val >> 8;
    break;

  case WORD:
    offset = offset & ~0b11;
    m[offset] = val;
    m[offset + 1] = val >> 8;
    m[offset + 2] = val >> 16;
    m[offset + 3] = val >> 24;
    break;

  default:
    break;
  }
};
