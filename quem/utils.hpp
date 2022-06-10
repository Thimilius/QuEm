#pragma once

namespace QuEm {

  inline bool IsPowerOfTwo(size_t x) {
    return x != 0 && (x & x - 1) == 0;
  }

  inline size_t GetBit(size_t number, size_t bit) {
    return 1 & (number >> bit);
  }
  
}
