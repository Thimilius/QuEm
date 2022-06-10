#pragma once

#include <vector>
#include <random>

#include "types.hpp"

namespace QuEm {

  struct MeasureResult {
    bool success = false;
    size_t state = 0;
  };
  
  class Qubit {
  public:
    Qubit(Complex a, Complex b);
    Qubit(std::vector<Complex> data);
  public:
    const std::vector<Complex> &GetData() const { return m_data; }
    std::vector<Complex> &GetData() { return m_data; }
    void SetData(std::vector<Complex> &&data) { m_data = data; }
    size_t GetSize() const { return m_data.size(); }

    MeasureResult Measure();
    MeasureResult Measure(size_t bit);
  public:
    static Qubit Tensor(const Qubit &a, const Qubit &b);
  private:
    bool IsValid() const;
    void Collapse(size_t entry);
  private:
    std::vector<Complex> m_data;
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
