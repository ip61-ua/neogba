#pragma once
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"

namespace neogba {

class memory_bus;

struct imemory {
protected:
  memory_bus* bus{nullptr};

public:
  virtual u32 read(u8 size, u32 addr) const = 0;
  virtual bool write(u8 size, u32 addr, u32 contents) = 0;
  virtual void reset() = 0;
  constexpr virtual std::size_t length() const = 0;

  inline void attach(memory_bus* bus_attached) { bus = bus_attached; }
  inline void deattach() { bus = nullptr; }

  virtual ~imemory() = default;
};

template <std::size_t bytes_length,
          std::size_t (*normalizer)(std::size_t addr) = [](std::size_t addr) -> auto {
            return addr & 0xffff;
          },
          bool check_bounds = false>
struct memory : imemory {
private:
  lut<u8, bytes_length, normalizer> bytes;

public:
  lut<u8, bytes_length, normalizer>& data() { return bytes; }

  virtual ~memory() = default;
  virtual u32 read(u8 size, u32 addr) const override {

    switch (size) {
    case 8:
      return int_read<8>(addr);
    case 16:
      return int_read<16>(addr);
    default:
      return int_read<32>(addr);
    }
  }

  virtual bool write(u8 size, u32 addr, u32 contents) override {
    switch (size) {
    case 8:
      return int_write<8>(addr, contents);
    case 16:
      return int_write<16>(addr, contents);
    default:
      return int_write<32>(addr, contents);
    }
  }

  virtual void reset() override { int_reset(); }
  constexpr std::size_t length() const final override { return bytes_length; }

protected:
  void int_reset() { bytes.fill(u8{}); };

  constexpr bool is_offset_exceeded(u32 addr) const { return normalizer(addr) >= bytes_length; }

  template <u8 size_requested> constexpr u32 int_read(u32 addr) const {
    if constexpr (check_bounds)
      if (is_offset_exceeded(addr))
        return 0;

    if constexpr (size_requested == 8) {
      return static_cast<u32>(bytes.get(addr));

    } else if constexpr (size_requested == 16) {
      if constexpr (check_bounds)
        if (is_offset_exceeded(addr + 1))
          return 0;

      return (static_cast<u32>(bytes.get(addr + 1)) << 8) | static_cast<u32>(bytes.get(addr));

    } else {
      if constexpr (check_bounds)
        if (is_offset_exceeded(addr + 2))
          return 0;

      return (static_cast<u32>(bytes.get(addr + 3)) << 24) |
             (static_cast<u32>(bytes.get(addr + 2)) << 16) |
             (static_cast<u32>(bytes.get(addr + 1)) << 8) | static_cast<u32>(bytes.get(addr));
    }
  }

  template <u8 size_requested> bool int_write(u32 addr, u32 contents) {
    if constexpr (check_bounds)
      if (is_offset_exceeded(addr))
        return false;

    if constexpr (size_requested == 8) {
      bytes.fill(addr, contents);

    } else if constexpr (size_requested == 16) {
      if constexpr (check_bounds)
        if (is_offset_exceeded(addr + 1))
          return false;

      bytes.fill(addr, contents);
      bytes.fill(addr + 1, contents >> 8);

    } else {
      if constexpr (check_bounds)
        if (is_offset_exceeded(addr + 3))
          return false;

      bytes.fill(addr, contents);
      bytes.fill(addr + 1, contents >> 8);
      bytes.fill(addr + 2, contents >> 16);
      bytes.fill(addr + 3, contents >> 24);
    }

    return true;
  }
};

} // namespace neogba
