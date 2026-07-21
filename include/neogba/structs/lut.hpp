#include "neogba/types.hpp"
#include <array>
#include <bit>
#include <cstddef>
#include <cstdio>

namespace neogba {

/**
 * @brief Compile-time lookup table (lut) with bit-pattern expansion utilities.
 *
 * Stores values indexed by an instruction encoding and provides facilities to populate the table
 * using masks, ranges or custom index normalization.
 *
 * The table is intended for decoder generation, where a single entry often represents multiple
 * instruction encodings differing only in don't-care bits.
 *
 * Can be used for Karnaugh-map reduction also by modifying normalizer function.
 *
 * @note It's recomended to set maximum storage length as n given 1 << n.
 *
 * @tparam store_t Stored element type.
 * @tparam max_length Number of entries in the table.
 * @tparam normalizer Compile-time function used to normalize lookup indices.
 */
template <typename store_t, std::size_t max_length,
          std::size_t (*normalizer)(std::size_t idx) =
              +[](std::size_t idx) -> std::size_t { return idx; }>
class lut {
protected:
  // inline constexpr std::size_t compute_max_mask(std::size_t n) {
  //   static_assert(max_length > 1, "You should not use LUT to store less than 2 elements!");
  //   // static_assert(max_length < sizeof(std::size_t), "Too many items");

  //   std::size_t mask{0x0};
  //   auto is_not_powered_2{false};

  //   for (std::size_t i{0}; i < sizeof(std::size_t); ++i) {
  //     n <<= 1;
  //     auto is_one_bit{n & 0x1};
  //     auto is_more_than_one{(n << 1) != 0};

  //     if (is_more_than_one || is_not_powered_2) {
  //       mask |= 1 << i;
  //       if (is_one_bit) {
  //         is_not_powered_2 = true;
  //       }
  //       continue;
  //     }

  //     if (is_one_bit)
  //       break;
  //   }

  //   return mask;
  // };

  const std::size_t MAX_MASK{std::bit_ceil(max_length) - 1};
  std::array<store_t, max_length> storage{};
  constexpr std::size_t fill_recursive(std::size_t base, std::size_t mask, store_t what, bool high,
                                       std::size_t bit = 0) {
    // caso base
    std::size_t shifted{mask >> bit};
    if (shifted == 0)
      return 0;

    // caso recursivo no fork
    bool is_mask_one{(shifted & 0x1u) == 1};
    std::size_t a_bit_mask{1u << bit++};
    if (!is_mask_one)
      return fill_recursive(base, mask, what, high, bit);

    // caso recursivo branch
    bool is_base_zero{((base) & (a_bit_mask)) == 0};
    u8 count{0};

    if (!(high ^ is_base_zero)) {
      count = 1;
      base ^= a_bit_mask;
      put_raw(base, what);
    }

    return count + fill_recursive(base, mask, what, true, bit) +
           fill_recursive(base, mask, what, false, bit);
  }

public:
  constexpr std::size_t norm_idx(std::size_t idx) const { return normalizer(idx) & MAX_MASK; }

  constexpr std::array<store_t, max_length> data() const { return storage; }
  constexpr store_t get(std::size_t idx) const { return storage[norm_idx(idx)]; }

  template <typename... Args>
    requires std::invocable<store_t, Args...>
  constexpr decltype(auto) invoke(std::size_t idx, Args&&... params) const {
    return get(idx)(std::forward<Args>(params)...);
  }

  constexpr void put_raw(std::size_t raw_idx, store_t what) { storage[raw_idx] = what; }

  constexpr void fill(store_t what) { storage.fill(what); }
  constexpr void fill(std::size_t idx, store_t what) { storage[norm_idx(idx)] = what; }

  /**
   * @brief Fills every combination selected by a bit mask.
   *
   * Starting from a base index, every bit enabled in `mask` is treated as a don't-care bit,
   * generating all possible index combinations.
   *
   * The base index itself is included.
   *
   * @return Number of table entries written.
   */
  constexpr std::size_t fill(std::size_t idx_base, std::size_t mask, store_t what) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};
    put_raw(b, what);
    return 1 + fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }

  /**
   * @brief Same as fill(), excluding the base index.
   *
   * @return Number of table entries written.
   */
  constexpr std::size_t fill_except(std::size_t idx_base, std::size_t mask, store_t what) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};
    return fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }

  /**
   * @brief Fills a half-open index range.
   *
   * Writes the specified value to every entry in [from, to).
   *
   * @return Number of entries written.
   */
  constexpr std::size_t fill_range(std::size_t from, std::size_t to, store_t what) {
    std::size_t f{norm_idx(from)}, t{norm_idx(to)}, n{};
    for (auto i{f}; i < t; ++i) {
      put_raw(i, what);
      n++;
    }
    return n;
  }

  /**
   * @brief Fills every default-initialized entry.
   *
   * Entries already containing a value are left unchanged.
   *
   * @return Number of entries written.
   */
  constexpr std::size_t fill_missing(store_t what) {
    std::size_t n{};
    for (std::size_t i{0}; i < max_length; ++i) {
      if (storage[i] == store_t{}) {
        put_raw(i, what);
        n++;
      }
    }
    return n;
  }

  constexpr std::size_t length() const { return max_length; };
  constexpr std::size_t count_stored(store_t what) const {
    std::size_t n{};
    for (const auto& elem : storage)
      if (elem == what)
        n++;
    return n;
  }
};

} // namespace neogba
