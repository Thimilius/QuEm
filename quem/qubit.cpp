#include "qubit.hpp"

#include "utils.hpp"

namespace QuEm {

  Qubit::Qubit(Complex a, Complex b) : m_amplitudes({ a, b }) { }

  Qubit::Qubit(std::vector<Complex> amplitudes) : m_amplitudes(std::move(amplitudes)) { }

  MeasureResult Qubit::Measure() {
    return Measure(-1);
  }

  MeasureResult Qubit::Measure(uint64_t bit) {
    MeasureResult result = { };
    
    if (!IsValid()) {
      return result;
    }

    FloatType random = s_random_distribution(s_random_engine);
    for (uint64_t state = 0; state < m_amplitudes.size(); state++) {
      random -= std::norm(m_amplitudes[state]);
      if (random <= 0) {
        Collapse(state);
        result.success = true;
        result.state = bit == static_cast<uint64_t>(-1) ? state : GetBit(state, bit);
        return result;
      }
    }
    
    return result;
  }

  Qubit Qubit::Tensor(const Qubit &a, const Qubit &b) {
    uint64_t a_size = a.GetSize();
    uint64_t b_size = b.GetSize();
    
    std::vector<Complex> data;
    data.resize(a_size * b_size);
    for (uint64_t i = 0; i < a_size; ++i) {
      for (uint64_t j = 0; j < b_size; ++j) {
        data[i * b_size + j] = a.m_amplitudes[i] * b.m_amplitudes[j];
      }
    }
    
    Qubit result(data);
    return result;
  }

  bool Qubit::IsValid() const {
    if (!IsPowerOfTwo(m_amplitudes.size())) {
      return false;
    }
    FloatType sum = 0;
    for (const Complex &amplitude : m_amplitudes) {
      sum += std::norm(amplitude);
    }
    bool is_in_tolerance = std::fabs(sum - 1) < ERROR_TOLERANCE;
    return is_in_tolerance;
  }
  
  void Qubit::Collapse(uint64_t state) {
    for (Complex &amplitude : m_amplitudes) {
      amplitude = 0;
    }
    m_amplitudes[state] = 1;
  }

}
