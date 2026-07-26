#pragma once
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"

namespace neogba {

class memory_bus;

class imemory {
  memory_bus* bus{nullptr};

public:
  virtual u32 read(u8 size, u32 addr) const = 0;
  virtual bool write(u8 size, u32 addr, u32 contents) = 0;
  virtual void reset() = 0;
  virtual std::size_t length() const = 0;

  inline void attach(memory_bus* bus_attached) { bus = bus_attached; }
  inline void deattach() { bus = nullptr; }
};

template <std::size_t bytes_length,
          std::size_t (*normalizer)(std::size_t addr) = [](std::size_t addr) -> auto {
            return addr & 0xffff;
          }>
struct memory : imemory {
  lut<u8, bytes_length, normalizer> bytes;

  virtual u32 read(u8 size, u32 addr) const override { int_read<size>(addr); }
  virtual bool write(u8 size, u32 addr, u32 contents) override {
    return int_write<size>(addr, contents);
  }

  virtual void reset() override { int_reset(); }
  constexpr std::size_t length() const final override { return bytes_length; }

protected:
  void int_reset() { bytes.fill(u8{}); };

  constexpr bool is_offset_exceeded(u32 offset) const { return offset >= bytes_length; }

  template <u8 size_requested> constexpr u32 int_read(u32 offset) const {
    if constexpr (size_requested == 8) {
      return static_cast<u32>(bytes.get(offset));

    } else if constexpr (size_requested == 16) {
      return (static_cast<u32>(bytes.get(offset + 1)) << 8) | static_cast<u32>(bytes.get(offset));

    } else {
      return (static_cast<u32>(bytes.get(offset + 3)) << 24) |
             (static_cast<u32>(bytes.get(offset + 2)) << 16) |
             (static_cast<u32>(bytes.get(offset + 1)) << 8) | static_cast<u32>(bytes.get(offset));
    }
  }

  template <u8 size_requested, bool check_bounds = false> bool int_write(u32 offset, u32 contents) {
    if constexpr (size_requested == 8) {

      bytes.fill(offset, contents);

    } else if constexpr (size_requested == 16) {

      if constexpr (check_bounds)
        if (is_offset_exceeded(offset + 1))
          return false;

      bytes.fill(offset, contents);
      bytes.fill(offset + 1, contents >> 8);

    } else {

      if constexpr (check_bounds)
        if (is_offset_exceeded(offset + 3))
          return false;

      bytes.fill(offset, contents);
      bytes.fill(offset + 1, contents >> 8);
      bytes.fill(offset + 2, contents >> 16);
      bytes.fill(offset + 3, contents >> 24);
    }

    return true;
  }
};

} // namespace neogba
