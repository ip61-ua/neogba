#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/constants.hpp"
#include "neogba/utils.hpp"
#include <vector>

namespace neogba::arm7tdmi::samples {

class SampleRAM : public IMemory {
private:
  std::vector<u32>* m;

public:
  inline SampleRAM(u32 s = M_createRightMask(K_gbaBlockOffsetMask))
      : m(new std::vector<u32>(s, 0)) {
    maxSize = s;
    writeState = true;
  };
  inline ~SampleRAM() {
    delete m;
    m = nullptr;
  };
  inline const char* getName() const override {
    return "SampleRAM";
  };
  u32 read(u32 addr, MemoryBlockLength len = WORD) const override;
  void write(u32 addr, u32 val, MemoryBlockLength len = WORD) override;
};

} // Namespace neogba::arm7tdmi::samples
