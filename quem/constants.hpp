#pragma once

#include "matrix.hpp"

namespace QuEm {
  
  constexpr FloatType ONE_OVER_SQRT2 = static_cast<FloatType>(0.7071067811865475244008443621048490392848359376884740365883398689);
  
  const Matrix HADAMARD_TRANSFORM = Matrix(2, 2, {
    ONE_OVER_SQRT2,  ONE_OVER_SQRT2,
    ONE_OVER_SQRT2, -ONE_OVER_SQRT2,
  });
  
}
