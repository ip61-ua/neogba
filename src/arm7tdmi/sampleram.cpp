#include "neogba/arm7tdmi/sampleram.hpp"
#include "neogba/arm7tdmi/memory.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;
using namespace neogba::arm7tdmi::samples;

bool SampleRAM::attached(u32 baseAddr) {
  if (!used1) {
    base1 = baseAddr;
    return true;
  }

  if (!used2) {
    base2 = baseAddr;
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
  addr &= (nBytes - 1);

  if (len == BYTE)
    return memoryBytes[addr];

  return 0;
}

void SampleRAM::write(u32 addr, u32 val, MemoryBlockLength len) {
  addr &= (nBytes - 1);

  if (len == BYTE)
    memoryBytes[addr] = val;
};
