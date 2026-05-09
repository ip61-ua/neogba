#include "neogba/arm7tdmi/sampleram.hpp"
#include "neogba/arm7tdmi/memory.hpp"

using namespace neogba;
using namespace neogba::arm7;
using namespace neogba::arm7::samples;

bool SampleRAM::attached(u32 base_addr) {
  if (!used1) {
    base1 = base_addr;
    used1 = true;
    return true;
  }

  if (!used2) {
    base2 = base_addr;
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

u32 SampleRAM::read(u32 addr, BlockLength len) const {
  auto offset = bus_properties_.getAddrOffset(addr);

  if (offset + len / 8 > n_bytes_)
    return 0;

  /*
  addr         = 0x FF 12 23 43
  nBytes       = 0x 01 00 00 00
  nBytes - 1   = 0x 00 FF FF FF
  addr & mask  = 0x 00 12 23 43
 */

  auto& m = memory_bytes_;

  switch (len) {
  case byte: {
    return m[offset];
  }

  case halfword: {
    offset = offset & ~0b01;
    return (m[offset + 1] << 8) | m[offset];
  }

  case word: {
    offset = offset & ~0b11;
    return (m[offset + 3] << 24) | (m[offset + 2] << 16) | (m[offset + 1] << 8) | m[offset];
  }
  }

  return 0;
}

void SampleRAM::write(u32 addr, u32 val, BlockLength len) {
  auto offset = bus_properties_.getAddrOffset(addr);

  if (offset + len / 8 > n_bytes_)
    return;

  auto& m = memory_bytes_;

  switch (len) {

  case byte:
    m[offset] = val;
    break;

  case halfword:
    offset = offset & ~0b01;
    m[offset] = val;
    m[offset + 1] = val >> 8;
    break;

  case word:
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
