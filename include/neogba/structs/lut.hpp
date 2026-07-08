#include "neogba/types.hpp"
#include <array>

template <std::size_t max_lenght, typename store_t = void*, typename idx_t = neogba::u8,
          typename return_t = void>
class lut {
  std::array<store_t, max_lenght> storage;

public:
  virtual std::size_t norm_idx(idx_t idx) const;

  store_t get(idx_t idx) const;
  return_t run(idx_t idx, ...) const;

  void put(idx_t idx, store_t what);
  void fill(idx_t idx_base, store_t what, idx_t mask);

  void erase(idx_t idx);

  bool is_empty() const;
  bool is_empty(idx_t idx) const;

  std::size_t length() const;
  std::size_t count_stored(store_t what) const;
};
