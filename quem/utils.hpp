#pragma once

namespace QuEm {

  inline bool IsPowerOfTwo(uint64_t x) {
    return x != 0 && (x & x - 1) == 0;
  }

  inline uint64_t GetBit(uint64_t number, uint64_t bit) {
    return 1 & (number >> bit);
  }
  
}
