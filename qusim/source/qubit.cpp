#include "qupch.hpp"

#include "qubit.hpp"

#include "utils.hpp"

namespace QuSim {

  Qubit::Qubit(Complex a, Complex b) : m_data({ a, b }) { }

  Qubit::Qubit(const std::vector<Complex> &data) : m_data(data) { }

  MeasureResult Qubit::Measure() {
    MeasureResult result = { };
    
    if (!IsValid()) {
      return result;
    }

    double random = s_random_distribution(s_random_engine);
    for (size_t i = 0; i < m_data.size(); i++) {
      random -= std::norm(m_data[i]);
      if (random <= 0) {
        result.success = true;
        result.qubit = i;
        return result;
      }
    }
    
    return result;
  }
  
  bool Qubit::IsValid() const {
    if (!IsPowerOfTwo(m_data.size())) {
      return false;
    }
    double sum = 0;
    for (const Complex &complex : m_data) {
      sum += std::norm(complex);
    }
    bool is_in_tolerance = std::fabs(sum - 1) < ERROR_TOLERANCE;
    return is_in_tolerance;
  }
  
  int Qubit::Collapse(int entry) {
    for (Complex &complex : m_data) {
      complex = 0;
    }
    m_data[entry] = 1;
    
    return entry;
  }

}
