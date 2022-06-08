#include "qupch.hpp"

#include "qubit.hpp" 

using namespace QuEm;

constexpr size_t DISTRIBUTION_SAMPLES = 1000000;

void PrintMeasurement(const std::string &header, const MeasureResult &result) {
  std::cout << header << " Measurement: " << result.state << std::endl;
}

void PrintDistribution(const std::string &header, const std::map<size_t, size_t> &distributions) {
  std::cout << header << " Distribution (" << DISTRIBUTION_SAMPLES << "):" << std::endl;
  for (auto [key, value] : distributions) {
    std::cout << "\t" << key << ": " << value << std::endl;
  }
}

void TestRandomNumberGeneratorOneQubit() {
  Qubit qubit = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);
  MeasureResult result = qubit.Measure();
  PrintMeasurement("One Qubit", result);
}

void TestRandomNumberGeneratorTwoQubit() {
  Qubit qubit = Qubit({ ONE_HALF, ONE_HALF, ONE_HALF, ONE_HALF });
  MeasureResult result = qubit.Measure();
  PrintMeasurement("Two Qubit", result);
}

void TestRandomNumberGeneratorNQubit(size_t n) {
  size_t power_of_two = static_cast<size_t>(std::pow(2, n));
  FloatType amplitude = static_cast<FloatType>(1.0) / std::sqrt(static_cast<FloatType>(power_of_two));

  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, amplitude);
  
  Qubit qubit = Qubit(amplitudes);
  MeasureResult result = qubit.Measure();
  PrintMeasurement(std::format("N ({}) Qubit", n), result);
}

void TestRandomNumberGeneratorTwoQubitDistribution() {
  std::map<size_t, size_t> distributions;
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; i++) {
    Qubit qubit = Qubit({ ONE_HALF, ONE_HALF, ONE_HALF, ONE_HALF });
    MeasureResult result = qubit.Measure();
    distributions[result.state]++;
  }

  PrintDistribution("Two Qubit", distributions);
}

void TestRandomNumberGeneratorNQubitDistribution(size_t n) {
  std::map<size_t, size_t> distributions;

  size_t power_of_two = static_cast<size_t>(std::pow(2, n));
  FloatType amplitude = static_cast<FloatType>(1.0) / std::sqrt(static_cast<FloatType>(power_of_two));
  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, amplitude);
  
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; i++) {
    Qubit qubit = Qubit(amplitudes);
    MeasureResult result = qubit.Measure();
    distributions[result.state]++;
  }

  PrintDistribution(std::format("N ({}) Qubit", n), distributions);
}

void TestTensor() {
  Qubit qubit_a = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);
  Qubit qubit_b = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);

  Qubit combined_qubit = Qubit::Tensor(qubit_a, qubit_b);
  MeasureResult result = combined_qubit.Measure();
  PrintMeasurement("Tensor Qubit", result);
}

int main() {
  TestRandomNumberGeneratorOneQubit();
  TestRandomNumberGeneratorTwoQubit();
  TestRandomNumberGeneratorTwoQubitDistribution();
  TestRandomNumberGeneratorNQubit(8);
  TestRandomNumberGeneratorNQubitDistribution(8);
  TestTensor();
  
  return 0;
}
