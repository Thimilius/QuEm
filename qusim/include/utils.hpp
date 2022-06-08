#pragma once

namespace QuSim {

  inline bool IsPowerOfTwo(size_t x) {
    return x != 0 && (x & x - 1) == 0;
  }
  
}
