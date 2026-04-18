#include "neogba/arm7tdmi/sampleram.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;
using namespace neogba::arm7tdmi::samples;

u32 SampleRAM::read(u32 addr, MemoryBlockLength len) const {
  auto offset = busProperties.getAddrOffset(addr);

  return m->at(offset);
};

void SampleRAM::write(u32 addr, u32 val, MemoryBlockLength len) {

};
