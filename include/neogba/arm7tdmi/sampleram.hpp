#include "neogba/arm7tdmi/memory.hpp"

namespace neogba::arm7::samples {

class SampleRAM : public IMemory {
private:
  u32 base1{0}, base2{0};
  bool used1{false}, used2{false};

protected:
  bool attached(u32 base_addr) override;
  bool detached() override;

public:
  inline SampleRAM(u32 n_bytes) : IMemory(n_bytes, false) {
    memory_bytes_ = std::make_unique<u8[]>(n_bytes);
    std::fill(memory_bytes_.get(), memory_bytes_.get() + n_bytes, 0);
  };
  inline const char* getName() const {
    return "SampleRAM";
  };
  u32 read(u32 addr, BlockLength len = word) const override;
  void write(u32 addr, u32 val, BlockLength len = word) override;
};

} // namespace neogba::arm7::samples
