#pragma once

#include <vector>
#include <complex>
#include <random>

namespace QuEm {

  using FloatType = double;
  using Complex = std::complex<FloatType>;

  constexpr FloatType ONE_OVER_SQRT2 = static_cast<FloatType>(0.7071067811865475244008443621048490392848359376884740365883398689);
  constexpr FloatType ONE_HALF = 0.5;
  
  struct MeasureResult {
    bool success = false;
    size_t qubit = 0;
  };
  
  class Qubit {
  public:
    Qubit(Complex a, Complex b);
    Qubit(const std::vector<Complex> &data);
  public:
    const std::vector<Complex> &GetData() const { return m_data; }
    size_t GetSize() const { return m_data.size(); }

    MeasureResult Measure();
  private:
    bool IsValid() const;
    int Collapse(int entry);
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
