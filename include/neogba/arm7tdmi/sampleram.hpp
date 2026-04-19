#include "neogba/arm7tdmi/memory.hpp"

namespace neogba::arm7tdmi::samples {

class SampleRAM : public IMemory {
public:
  inline SampleRAM(u32 nBytes) {
    this->nBytes = nBytes;
    writeState = true;
    memoryBytes = std::make_unique<u8[]>(nBytes);
  };
  inline const char* getName() const {
    return "SampleRAM";
  };
  u32 read(u32 addr, MemoryBlockLength len = WORD) const override;
  void write(u32 addr, u32 val, MemoryBlockLength len = WORD) override;
};

} // Namespace neogba::arm7tdmi::samples
