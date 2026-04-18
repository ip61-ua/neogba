#include "neogba/types.hpp"

namespace neogba::arm7tdmi {

enum MemoryBlockLength : u8 { WORD = 32, HALFWORD = 16, BYTE = 8 };

class IMemory {

public:
  virtual ~IMemory() = default;
  virtual const char* getName() const = 0;
  virtual std::size_t getSize() const = 0;
  virtual bool isReadOnly() const = 0;
  virtual u32 read(u32 addr, MemoryBlockLength len = WORD) const = 0;
  virtual void write(u32 addr, u32 val, MemoryBlockLength len = WORD) = 0;
  friend class MemoryBus;
};

class MemoryBus {
protected:
  u8 offsetBitSize;
  u32 maxSizePerBlock;
  u32 maxSizeLength;
  IMemory** memoryMap;

public:
  MemoryBus(const u8 offsetBitSize = 24)
      : offsetBitSize(offsetBitSize), maxSizePerBlock(1 << offsetBitSize),
        maxSizeLength(1 << (32 - offsetBitSize)), memoryMap(new IMemory*[maxSizeLength]()) {};
  inline ~MemoryBus() {
    delete[] memoryMap;
    memoryMap = nullptr;
  };
  inline u32 getIndexFromAddr(u32 addr) const {
    return addr >> offsetBitSize;
  }
  inline bool isFreeIndex(u32 index) const {
    return index < maxSizeLength && memoryMap[index] != nullptr;
  };
  bool attachMemory(u32 addr, IMemory* memory);
  bool detachMemory(u32 addr);
  u32 read(u32 addr, MemoryBlockLength len = WORD) const;
  bool write(u32 addr, u32 val, MemoryBlockLength len = WORD);
};

} // namespace neogba::arm7tdmi
