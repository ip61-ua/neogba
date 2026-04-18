#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/constants.hpp"
#include "neogba/utils.hpp"
#include <memory>

namespace neogba::arm7tdmi::samples {

class SampleRAM : public IMemory {
private:
  std::unique_ptr<u8[]> m;

public:
  inline SampleRAM(u32 s = M_createRightMask(K_gbaBlockOffsetMask))
      : m(std::make_unique_for_overwrite<u8[]>(s)) {
    maxSize = s;
    writeState = true;
  };
  inline const char* getName() const override {
    return "SampleRAM";
  };
  u32 read(u32 addr, MemoryBlockLength len = WORD) const override;
  void write(u32 addr, u32 val, MemoryBlockLength len = WORD) override;
};

} // Namespace neogba::arm7tdmi::samples
