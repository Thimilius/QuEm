#pragma once

#include "matrix.hpp"

namespace QuEm {
  
  constexpr FloatType ONE_OVER_SQRT2 = static_cast<FloatType>(0.7071067811865475244008443621048490392848359376884740365883398689);

  const Matrix IDENTITY_GATE = Matrix(2, 2, {
    1, 0,
    0, 1,
  });
  
  const Matrix HADAMARD_GATE = Matrix(2, 2, {
    ONE_OVER_SQRT2,  ONE_OVER_SQRT2,
    ONE_OVER_SQRT2, -ONE_OVER_SQRT2,
  });

  const Matrix HADAMARD_GATE_POW_2 = Matrix::Tensor(HADAMARD_GATE, HADAMARD_GATE);

  const Matrix CNOT_GATE = Matrix(4, 4, {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 1,
    0, 0, 1, 0,
  });
  
  const Matrix UF_GATE_1 = Matrix(4, 4, {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  });

  const Matrix UF_GATE_2 = Matrix(4, 4, {
    0, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 1,
    0, 0, 1, 0,
  });

  const Matrix UF_GATE_3 = Matrix(4, 4, {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 1,
    0, 0, 1, 0,
  });
  
  const Matrix UF_GATE_4 = Matrix(4, 4, {
    0, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  });
  
}
