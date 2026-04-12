#include "neogba/types.hpp"

namespace neogba::arm7tdmi {

enum MemoryBlockLength : u8 { WORD = 32, HALFWORD = 16, BYTE = 8 };

class IMemory {

public:
  virtual const char* getName() const = 0;
  virtual std::size_t getSize() const = 0;
  virtual bool isReadOnly() const = 0;
  virtual u32 read(u32 addr, MemoryBlockLength len = WORD) const = 0;
  virtual void write(u32 addr, u32 val, MemoryBlockLength len = WORD) = 0;
  friend class MemoryBus;
};

class MemoryBus {
private:
  u8 offsetBitSize;
  u32 maxSizePerBlock;
  IMemory** memoryMap;

public:
  MemoryBus(const u8 offsetBitSize = 24)
      : offsetBitSize(offsetBitSize), maxSizePerBlock(1 << offsetBitSize),
        memoryMap(new IMemory*[32 - offsetBitSize]) {};
  inline ~MemoryBus() {
    if (memoryMap != nullptr)
      delete[] memoryMap;
    memoryMap = nullptr;
  };
  bool attachMemory(u32 addr, IMemory* memory);
  bool detachMemory(u32 addr);
  u32 read(u32 addr, MemoryBlockLength len = WORD) const;
  bool write(u32 addr, u32 val, MemoryBlockLength len = WORD);
};

} // namespace neogba::arm7tdmi
