#pragma once

#include <vector>
#include <complex>
#include <random>

namespace QuEm {

  using Complex = std::complex<double>;

  constexpr double ONE_OVER_SQRT2 = 0.7071067811865475244008443621048490392848359376884740365883398689;
  constexpr double ONE_HALF = 0.5;
  
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
    inline static std::uniform_real_distribution<double> s_random_distribution = std::uniform_real_distribution(0.0, 1.0);

    static constexpr double ERROR_TOLERANCE = 0.000000000000001;
  };
  
}
