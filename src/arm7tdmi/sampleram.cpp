#include "neogba/arm7tdmi/sampleram.hpp"
#include "neogba/arm7tdmi/memory.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;
using namespace neogba::arm7tdmi::samples;

u32 SampleRAM::read(u32 addr, MemoryBlockLength len) const {
  addr &= (maxSize - 1);

  if (len == BYTE)
    return m[addr];

  return 0;
}

void SampleRAM::write(u32 addr, u32 val, MemoryBlockLength len) {
  addr &= (maxSize - 1);

  if (len == BYTE)
    m[addr] = val;
};
