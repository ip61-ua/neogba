#include "neogba/arm7tdmi/memory.hpp"
#include <vector>

namespace neogba::arm7tdmi::samples {

class SampleRAM : IMemory {
private:
  std::vector<u32>* m;

public:
  inline SampleRAM(u32 s) : m(new std::vector<u32>(s)) {
    maxSize = s;
    writeState = true;
  };
  inline ~SampleRAM() {
    delete m;
    m = nullptr;
  };
  inline const char* getName() const {
    return "SampleRAM";
  };
  u32 read(u32 addr, MemoryBlockLength len = WORD) const;
  void write(u32 addr, u32 val, MemoryBlockLength len = WORD);
};

} // Namespace neogba::arm7tdmi::samples
