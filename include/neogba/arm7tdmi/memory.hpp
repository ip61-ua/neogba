#pragma once
#include "neogba/constants.hpp"
#include "neogba/types.hpp"
#include "neogba/utils.hpp"
#include <memory>

namespace neogba::arm7tdmi {

enum MemoryBlockLength : u8 { WORD = 32, HALFWORD = 16, BYTE = 8 };

struct MemoryBusProperties {
private:
  u32 nBitsOffset, nBitsIndex;
  u32 maskOffset, maskIndex;
  u32 nMaxOffset, nMaxIndex;

public:
  MemoryBusProperties(u32 nBitsOffset = 0)
      : nBitsOffset(nBitsOffset), nBitsIndex(K_blockBitSize - nBitsOffset),
        maskOffset(M_createRightMask(nBitsOffset)),
        maskIndex(M_createRightMask(K_blockBitSize) - maskOffset), nMaxOffset(maskOffset),
        nMaxIndex(maskIndex >> nBitsOffset) {};

  inline u32 getMaskOffset() const {
    return maskOffset;
  };
  inline u32 getMaskIndex() const {
    return maskIndex;
  };
  inline u32 getNBitsOffset() const {
    return nBitsOffset;
  };
  inline u32 getNBitsIndex() const {
    return nBitsIndex;
  };
  inline u32 getNMaxOffset() const {
    return nMaxOffset;
  };
  inline u32 getNMaxIndex() const {
    return nMaxIndex;
  };
  inline u32 getAddrOffset(u32 addr) const {
    return addr & maskOffset;
  }
  inline u32 getAddrIndex(u32 addr) const {
    return addr >> nBitsOffset;
  }

  inline bool operator==(MemoryBusProperties o) const {
    return nBitsOffset == o.nBitsOffset && nBitsIndex == o.nBitsIndex &&
           maskOffset == o.maskOffset && maskIndex == o.maskIndex && nMaxOffset == o.nMaxOffset &&
           nMaxIndex == o.nMaxIndex;
  };
};

class IMemory {
protected:
  u32 maxSize;
  bool writeState;
  MemoryBusProperties busProperties;

public:
  virtual ~IMemory() = default;
  inline const char* getName() const {
    return nullptr;
  };
  inline std::size_t getSize() const {
    return maxSize;
  };
  inline bool isReadOnly() const {
    return !writeState;
  };
  inline MemoryBusProperties getProperties() const {
    return busProperties;
  }
  virtual u32 read(u32 addr, MemoryBlockLength len = WORD) const = 0;
  virtual void write(u32 addr, u32 val, MemoryBlockLength len = WORD) = 0;

  friend class MemoryBus;
};

class MemoryBus {
protected:
  const MemoryBusProperties properties;
  std::unique_ptr<IMemory*[]> memoryMap;

public:
  MemoryBus(const u32 offsetBitSize = K_gbaBlockOffsetMask)
      : properties(offsetBitSize),
        memoryMap(std::make_unique<IMemory*[]>(properties.getNMaxIndex())) {};

  inline bool isFreeIndex(u32 index) const {
    return index < properties.getNMaxIndex() && memoryMap[index] == nullptr;
  };
  inline MemoryBusProperties getProperties() const {
    return properties;
  }
  bool attachMemory(u32 addr, IMemory* memory);
  bool detachMemory(u32 addr);
  u32 read(u32 addr, MemoryBlockLength len = WORD) const;
  bool write(u32 addr, u32 val, MemoryBlockLength len = WORD);
};

} // namespace neogba::arm7tdmi
