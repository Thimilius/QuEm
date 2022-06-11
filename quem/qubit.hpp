#pragma once

#include <vector>
#include <random>

#include "types.hpp"

namespace QuEm {

  struct MeasureResult {
    bool success = false;
    uint64_t state = 0;
  };
  
  class Qubit {
  public:
    Qubit(Complex a, Complex b);
    Qubit(std::vector<Complex> amplitudes);
  public:
    const std::vector<Complex> &GetAmplitudes() const { return m_amplitudes; }
    std::vector<Complex> &GetAmplitudes() { return m_amplitudes; }
    void SetAmplitudes(std::vector<Complex> &&amplitudes) { m_amplitudes = amplitudes; }
    uint64_t GetSize() const { return m_amplitudes.size(); }

    MeasureResult Measure();
    MeasureResult Measure(uint64_t bit);
  public:
    static Qubit Tensor(const Qubit &a, const Qubit &b);
  private:
    bool IsValid() const;
    void Collapse(uint64_t state);
  private:
    std::vector<Complex> m_amplitudes;
  private:
    inline static std::random_device s_random_device = std::random_device();
    inline static std::mt19937 s_random_engine = std::mt19937(s_random_device());
    inline static std::uniform_real_distribution<FloatType> s_random_distribution = std::uniform_real_distribution(
      static_cast<FloatType>(0.0),
      static_cast<FloatType>(1.0)
    );

    static constexpr FloatType ERROR_TOLERANCE = static_cast<FloatType>(0.000000000000001);
  };
  
}
