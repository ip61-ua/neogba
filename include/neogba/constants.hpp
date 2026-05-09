#pragma once

namespace neogba {

const auto K_BLOCK_BIT_SIZE{32}, K_BLOCK_INDEX_MASK{8},
    K_GBABLOCKOFFSETMASK{K_BLOCK_BIT_SIZE - K_BLOCK_INDEX_MASK};

} // namespace neogba
