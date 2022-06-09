#include <map>

#include "constants.hpp"
#include "matrix.hpp"
#include "qubit.hpp" 

using namespace QuEm;

constexpr bool TEST_DISTRIBUTION = false;
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

void TestQubitTensor() {
  Qubit qubit_a = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);
  Qubit qubit_b = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);

  Qubit combined_qubit = Qubit::Tensor(qubit_a, qubit_b);
  MeasureResult result = combined_qubit.Measure();
  PrintMeasurement("Tensor Qubit", result);
}

void TestQubitMatrixTransformation() {
  Matrix transformation = Matrix(2, 2, {
    0, 1,
    1, 0,
  });

  Qubit qubit = Qubit(1, 0);
  Qubit transformed_qubit = transformation * qubit;
  MeasureResult result = transformed_qubit.Measure();

  assert(result.state == 1);
}

void TestMatrixTensor() {
  Matrix matrix = Matrix(2, 2, {
    1, 0,
    0, 1,
  });

  Matrix tensor_matrix = Matrix::Tensor(matrix, matrix);
  tensor_matrix.Print();
}

void RandomNumberGeneratorOneQubit() {
  Qubit x = Qubit(1, 0);
  x = HADAMARD_TRANSFORM * x;
  MeasureResult result = x.Measure();
  
  PrintMeasurement("Random number generator (one qubit)", result);
}

void RandomNumberGeneratorOneQubitDistribution() {
  std::map<size_t, size_t> distributions;
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; ++i) {
    Qubit x = Qubit(1, 0);
    x = HADAMARD_TRANSFORM * x;
    MeasureResult result = x.Measure();
    distributions[result.state]++;
  }

  PrintDistribution("One Qubit", distributions);
}

void RandomNumberGeneratorTwoQubit() {
  Qubit x = Qubit({ 1, 0, 0, 0 });

  Matrix hadamard_transform = Matrix::Tensor(HADAMARD_TRANSFORM, HADAMARD_TRANSFORM);
  x = hadamard_transform * x;
  MeasureResult result = x.Measure();
  
  PrintMeasurement("Random number generator (two qubits)", result);
}

void RandomNumberGeneratorTwoQubitDistribution() {
  Matrix hadamard_transform = Matrix::Tensor(HADAMARD_TRANSFORM, HADAMARD_TRANSFORM);
  
  std::map<size_t, size_t> distributions;
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; ++i) {
    Qubit x = Qubit({ 1, 0, 0, 0 });
    x = hadamard_transform * x;
    MeasureResult result = x.Measure();
    distributions[result.state]++;
  }

  PrintDistribution("Two Qubit", distributions);
}

void RandomNumberGeneratorNQubit(size_t n) {
  size_t power_of_two = static_cast<size_t>(1) << n;
  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, 0);
  amplitudes[0] = 1;
  Qubit x = Qubit(amplitudes);

  Matrix hadamard_transform = HADAMARD_TRANSFORM;
  for (size_t i = 1; i < n; i++) {
    hadamard_transform = Matrix::Tensor(hadamard_transform, HADAMARD_TRANSFORM); 
  }
  
  x = hadamard_transform * x;
  MeasureResult result = x.Measure();
  
  PrintMeasurement("Random number generator (n qubits)", result);
}

void RandomNumberGeneratorNQubitDistribution(size_t n) {
  size_t power_of_two = static_cast<size_t>(1) << n;
  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, 0);
  amplitudes[0] = 1;

  Matrix hadamard_transform = HADAMARD_TRANSFORM;
  for (size_t i = 1; i < n; i++) {
    hadamard_transform = Matrix::Tensor(hadamard_transform, HADAMARD_TRANSFORM); 
  }

  std::map<size_t, size_t> distributions;
  for (size_t i = 0; i < DISTRIBUTION_SAMPLES; ++i) {
    Qubit x = Qubit(amplitudes);
    x = hadamard_transform * x;
    MeasureResult result = x.Measure();
    distributions[result.state]++;
  }
  
  PrintDistribution("N Qubit", distributions);
}

int main() {
  TestQubitTensor();
  TestQubitMatrixTransformation();
  TestMatrixTensor();

  RandomNumberGeneratorOneQubit();
  RandomNumberGeneratorTwoQubit();
  RandomNumberGeneratorNQubit(8);

  if constexpr (TEST_DISTRIBUTION) {
    RandomNumberGeneratorOneQubitDistribution();
    RandomNumberGeneratorTwoQubitDistribution();
    RandomNumberGeneratorNQubitDistribution(4);  
  }
  
  return 0;
}
