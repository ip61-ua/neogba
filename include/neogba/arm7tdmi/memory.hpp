#include "neogba/types.hpp"

namespace neogba::arm7tdmi {

enum MemoryBlockLength : u8 { WORD = 32, HALFWORD = 16, BYTE = 8 };

class IMemory {
protected:
  u32 maxSize;
  bool writeState;

public:
  virtual ~IMemory() = default;

  inline static u32 getAddrOffset(u32 addr, u32 nOffset) {
    return (nOffset >= 32) ? addr : addr & ((1 << nOffset) - 1);
  }
  inline static u32 getAddrIndex(u32 addr, u32 nOffset) {
    return addr >> nOffset;
  };

  virtual const char* getName() const = 0;
  inline std::size_t getSize() const {
    return maxSize;
  };
  inline bool isReadOnly() const {
    return writeState;
  };

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
