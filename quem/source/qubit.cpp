#include "qupch.hpp"

#include "qubit.hpp"

#include "utils.hpp"

namespace QuEm {

  Qubit::Qubit(Complex a, Complex b) : m_data({ a, b }) { }

  Qubit::Qubit(std::vector<Complex> data) : m_data(std::move(data)) { }

  MeasureResult Qubit::Measure() {
    MeasureResult result = { };
    
    if (!IsValid()) {
      return result;
    }

    FloatType random = s_random_distribution(s_random_engine);
    for (size_t i = 0; i < m_data.size(); i++) {
      random -= std::norm(m_data[i]);
      if (random <= 0) {
        result.success = true;
        result.state = i;
        return result;
      }
    }
    
    return result;
  }

  Qubit Qubit::Tensor(const Qubit &a, const Qubit &b) {
    size_t a_size = a.GetSize();
    size_t b_size = b.GetSize();
    
    std::vector<Complex> data;
    data.resize(a_size * b_size);
    for (size_t i = 0; i < a_size; ++i) {
      for (size_t j = 0; j < b_size; ++j) {
        data[i * b_size + j] = a.m_data[i] * b.m_data[j];
      }
    }
    
    Qubit result(data);
    return result;
  }

  bool Qubit::IsValid() const {
    if (!IsPowerOfTwo(m_data.size())) {
      return false;
    }
    FloatType sum = 0;
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
