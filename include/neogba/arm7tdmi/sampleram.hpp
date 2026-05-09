#include "neogba/arm7tdmi/memory.hpp"

namespace neogba::arm7tdmi::samples {

class SampleRAM : public IMemory {
private:
  u32 base1{0}, base2{0};
  bool used1{false}, used2{false};

protected:
  bool attached(u32 baseAddr) override;
  bool detached() override;

public:
  inline SampleRAM(u32 nBytes) : IMemory(nBytes, true) {
    memory_bytes = std::make_unique<u8[]>(nBytes);
    std::fill(memory_bytes.get(), memory_bytes.get() + nBytes, 0);
  };
  inline const char* getName() const {
    return "SampleRAM";
  };
  u32 read(u32 addr, MemoryBlockLength len = WORD) const override;
  void write(u32 addr, u32 val, MemoryBlockLength len = WORD) override;
};

} // Namespace neogba::arm7tdmi::samples
