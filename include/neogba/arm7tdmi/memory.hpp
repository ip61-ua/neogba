#pragma once
#include "neogba/constants.hpp"
#include "neogba/types.hpp"
#include "neogba/utils.hpp"
#include <memory>
#include <vector>

namespace neogba::arm7 {

struct MemoryBusProperties {
  u32 n_bits_offset_, n_bits_index_;
  u32 mask_offset_, mask_index_;
  u32 n_max_offset_, n_max_index_;

  MemoryBusProperties(u32 n_bits_offset = 0)
      : n_bits_offset_(n_bits_offset), n_bits_index_(K_BLOCK_BIT_SIZE - n_bits_offset),
        mask_offset_(createRightMask(n_bits_offset)),
        mask_index_(createRightMask(K_BLOCK_BIT_SIZE) - mask_offset_), n_max_offset_(mask_offset_),
        n_max_index_(mask_index_ >> n_bits_offset) {};

  [[nodiscard]] inline u32 getAddrOffset(u32 addr) const {
    return addr & mask_offset_;
  }
  [[nodiscard]] inline u32 getAddrIndex(u32 addr) const {
    return addr >> n_bits_offset_;
  }

  [[nodiscard]] inline bool equals(MemoryBusProperties o) const {
    return operator==(o);
  }

  [[nodiscard]] inline bool operator==(MemoryBusProperties const& o) const = default;
};

class IMemory {
protected:
  u32 n_bytes_;
  bool read_only_;
  MemoryBusProperties bus_properties_;
  std::unique_ptr<u8[]> memory_bytes_;

public:
  IMemory(u32 n_bytes = 0, bool read_only = true,
          MemoryBusProperties bus_properties = MemoryBusProperties())
      : n_bytes_(n_bytes), read_only_(read_only), bus_properties_(bus_properties),
        memory_bytes_(nullptr) {};

  virtual ~IMemory() = default;

  inline const char* getName() const {
    return nullptr;
  }
  inline std::size_t getSize() const {
    return n_bytes_;
  }
  inline bool isReadOnly() const {
    return read_only_;
  }
  inline MemoryBusProperties getProperties() const {
    return bus_properties_;
  }
  inline const u8* getMemoryBytes() const {
    return memory_bytes_.get();
  }
  virtual u32 read(u32 addr, BlockLength len = word) const = 0;
  virtual void write(u32 addr, u32 val, BlockLength len = word) = 0;

protected:
  virtual bool attached(u32 base_addr) = 0;
  virtual bool detached() {
    return true;
  }

  friend class MemoryBus;
};

class MemoryBus {
protected:
  MemoryBusProperties properties_;
  std::vector<std::shared_ptr<IMemory>> memory_map_;

public:
  MemoryBus(u32 offsetBitSize = K_BLOCK_INDEX_MASK)
      : properties_(offsetBitSize), memory_map_(properties_.n_max_index_) {}

  inline bool isFreeIndex(u32 index) const {
    return index < properties_.n_max_index_ && memory_map_[index] == nullptr;
  }

  inline MemoryBusProperties getProperties() const {
    return properties_;
  }

  bool attachMemory(u32 addr, std::shared_ptr<IMemory> memory);
  bool detachMemory(u32 addr);
  u32 read(u32 addr, BlockLength len = word) const;
  bool write(u32 addr, u32 val, BlockLength len = word);
};

} // namespace neogba::arm7
