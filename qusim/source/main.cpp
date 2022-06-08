#include "qupch.hpp"

#include <format>
#include <iostream>
#include <map>

#include "qubit.hpp" 

using namespace QuSim;

constexpr size_t DISTRIBUTION_SAMPLES = 1000000;

void PrintDistribution(const std::string &header, const std::map<size_t, size_t> &distributions) {
  std::cout << header << " Distribution (" << DISTRIBUTION_SAMPLES << "):" << std::endl;
  for (auto [key, value] : distributions) {
    std::cout << "\t" << key << ": " << value << std::endl;
  }
}

void TestRandomNumberGeneratorOneQubit() {
  Qubit qubit = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);
  MeasureResult result = qubit.Measure();

  std::cout << "One Qubit Measurement: " << result.qubit << std::endl;
}

void TestRandomNumberGeneratorTwoQubit() {
  Qubit qubit = Qubit({ ONE_HALF, ONE_HALF, ONE_HALF, ONE_HALF });
  MeasureResult result = qubit.Measure();

  std::cout << "Two Qubit Measurement: " << result.qubit << std::endl;
}

void TestRandomNumberGeneratorNQubit(size_t n) {
  size_t power_of_two = static_cast<size_t>(std::pow(2, n));
  double amplitude = 1.0 / std::sqrt(static_cast<double>(power_of_two));

  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, amplitude);
  
  Qubit qubit = Qubit(amplitudes);
  MeasureResult result = qubit.Measure();

  std::cout << "N (" << n << ") Qubit Measurement: " << result.qubit << std::endl;
}

void TestRandomNumberGeneratorTwoQubitDistribution() {
  std::map<size_t, size_t> distributions;
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; i++) {
    Qubit qubit = Qubit({ ONE_HALF, ONE_HALF, ONE_HALF, ONE_HALF });
    MeasureResult result = qubit.Measure();
    distributions[result.qubit]++;
  }

  PrintDistribution("Two Qubit", distributions);
}

void TestRandomNumberGeneratorNQubitDistribution(size_t n) {
  std::map<size_t, size_t> distributions;

  size_t power_of_two = static_cast<size_t>(std::pow(2, n));
  double amplitude = 1.0 / std::sqrt(static_cast<double>(power_of_two));
  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, amplitude);
  
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; i++) {
    Qubit qubit = Qubit(amplitudes);
    MeasureResult result = qubit.Measure();
    distributions[result.qubit]++;
  }

  PrintDistribution(std::format("N ({}) Qubit", n), distributions);
}

int main() {
  TestRandomNumberGeneratorOneQubit();
  TestRandomNumberGeneratorTwoQubit();
  TestRandomNumberGeneratorTwoQubitDistribution();
  TestRandomNumberGeneratorNQubit(8);
  TestRandomNumberGeneratorNQubitDistribution(8);
  
  return 0;
}
