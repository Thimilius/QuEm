#include <format>
#include <map>

#include "constants.hpp"
#include "matrix.hpp"
#include "qubit.hpp" 

using namespace QuEm;

constexpr uint64_t DISTRIBUTION_SAMPLES = 1000000;

void PrintMeasurement(const std::string &header, const MeasureResult &result) {
  std::cout << header << " Measurement: " << result.state << std::endl;
}

void PrintDistribution(const std::string &header, const std::map<uint64_t, uint64_t> &distributions) {
  std::cout << header << " Distribution (" << DISTRIBUTION_SAMPLES << "):" << std::endl;
  for (auto [key, value] : distributions) {
    std::cout << "\t" << key << ": " << value << std::endl;
  }
}

void RandomNumberGeneratorOneQubit() {
  Qubit x = Qubit(1, 0);
  x = HADAMARD_GATE * x;
  MeasureResult result = x.Measure();
  
  PrintMeasurement("Random number generator (one qubit)", result);
}

void RandomNumberGeneratorOneQubitDistribution() {
  std::map<uint64_t, uint64_t> distributions;
  for (uint64_t i = 0; i < DISTRIBUTION_SAMPLES; ++i) {
    Qubit x = Qubit(1, 0);
    x = HADAMARD_GATE * x;
    MeasureResult result = x.Measure();
    distributions[result.state]++;
  }

  PrintDistribution("One Qubit", distributions);
}

void RandomNumberGeneratorTwoQubit() {
  Qubit x = Qubit({ 1, 0, 0, 0 });

  Matrix hadamard_transform = Matrix::Tensor(HADAMARD_GATE, HADAMARD_GATE);
  x = hadamard_transform * x;
  MeasureResult result = x.Measure();
  
  PrintMeasurement("Random number generator (two qubits)", result);
}

void RandomNumberGeneratorTwoQubitDistribution() {
  Matrix hadamard_transform = Matrix::Tensor(HADAMARD_GATE, HADAMARD_GATE);
  
  std::map<uint64_t, uint64_t> distributions;
  for (uint64_t i = 0; i < DISTRIBUTION_SAMPLES; ++i) {
    Qubit x = Qubit({ 1, 0, 0, 0 });
    x = hadamard_transform * x;
    MeasureResult result = x.Measure();
    distributions[result.state]++;
  }

  PrintDistribution("Two Qubits", distributions);
}

void RandomNumberGeneratorNQubit(uint64_t n) {
  uint64_t power_of_two = static_cast<uint64_t>(1) << n;
  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, 0);
  amplitudes[0] = 1;
  Qubit x = Qubit(amplitudes);

  Matrix hadamard_transform = HADAMARD_GATE;
  for (uint64_t i = 1; i < n; i++) {
    hadamard_transform = Matrix::Tensor(hadamard_transform, HADAMARD_GATE); 
  }
  
  x = hadamard_transform * x;
  MeasureResult result = x.Measure();
  
  PrintMeasurement(std::format("Random number generator ({} qubits)", n), result);
}

void RandomNumberGeneratorNQubitDistribution(uint64_t n) {
  uint64_t power_of_two = static_cast<uint64_t>(1) << n;
  std::vector<Complex> amplitudes;
  amplitudes.resize(power_of_two, 0);
  amplitudes[0] = 1;

  Matrix hadamard_transform = HADAMARD_GATE;
  for (uint64_t i = 1; i < n; i++) {
    hadamard_transform = Matrix::Tensor(hadamard_transform, HADAMARD_GATE); 
  }

  std::map<uint64_t, uint64_t> distributions;
  for (uint64_t i = 0; i < DISTRIBUTION_SAMPLES; ++i) {
    Qubit x = Qubit(amplitudes);
    x = hadamard_transform * x;
    MeasureResult result = x.Measure();
    distributions[result.state]++;
  }
  
  PrintDistribution(std::format("{} Qubits", n), distributions);
}

void DeutschAlgorithm(const Matrix &uf) {
  Qubit x = Qubit(1, 0);
  Qubit y = Qubit(0, 1);
  Qubit q = Qubit::Tensor(x, y);

  q = HADAMARD_GATE_POW_2 * q;
  q = uf * q;
  q = HADAMARD_GATE_POW_2 * q;

  MeasureResult result = q.Measure(1);

  if (result.state == 0) {
    std::cout << "The function is constant!" << std::endl;
  } else if (result.state == 1) {
    std::cout << "The function is balanced!" << std::endl;
  } else {
    std::cout << "Something went horribly wrong!" << std::endl;
  }
}

void Bell() {
  // Generate Phi+ bell state. 
  Qubit q = Qubit({ 1, 0, 0, 0 });

  q = Matrix::Tensor(HADAMARD_GATE, IDENTITY_GATE) * q;
  q = CNOT_GATE * q;

  MeasureResult result = q.Measure();
  PrintMeasurement("Bell", result);
}

void BellEntanglement() {
  Qubit q = Qubit({ 1, 0, 0, 0 });

  q = Matrix::Tensor(HADAMARD_GATE, IDENTITY_GATE) * q;
  q = CNOT_GATE * q;

  MeasureResult result = q.Measure(1);
  if (result.state == 0) {
    assert(q.Measure(0).state == 0);
  } else if (result.state == 1) {
    assert(q.Measure(0).state == 1);
  } else {
    assert(false);
  }
}

void PrintHelp() {
  std::cout << "Commands:" << std::endl;
  std::cout << "  random (optional: number of qubits)" << std::endl;
  std::cout << "  distribution (optional: number of qubits)" << std::endl;
  std::cout << "  deutsch (function 1-4)" << std::endl;
  std::cout << "  bell" << std::endl;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    if (std::strcmp(argv[1], "random") == 0) {
      if (argc > 2) {
        uint64_t n = std::strtoull(argv[2], nullptr, 10);
        if (n != 0) {
          RandomNumberGeneratorNQubit(n);
        }
      } else {
        RandomNumberGeneratorOneQubit();
        RandomNumberGeneratorTwoQubit();
        RandomNumberGeneratorNQubit(8);  
      }
    } else if (std::strcmp(argv[1], "distribution") == 0) {
      if (argc > 2) {
        uint64_t n = std::strtoull(argv[2], nullptr, 10);
        if (n != 0) {
          RandomNumberGeneratorNQubitDistribution(n);
        }
      } else {
        RandomNumberGeneratorOneQubitDistribution();
        RandomNumberGeneratorTwoQubitDistribution();
        RandomNumberGeneratorNQubitDistribution(4);
      }
    } else if (std::strcmp(argv[1], "deutsch") == 0 && argc > 2) {
      uint64_t f = std::strtoull(argv[2], nullptr, 10);

      Matrix function = UF_GATE_1;
      switch (f) {
        case 1: function = UF_GATE_1; break;
        case 2: function = UF_GATE_2; break;
        case 3: function = UF_GATE_3; break;
        case 4: function = UF_GATE_4; break;
        default: return 0;
      }
      
      DeutschAlgorithm(function);
    } else if (std::strcmp(argv[1], "bell") == 0) {
      Bell();
      BellEntanglement();
    }else {
      PrintHelp();
    }
  } else {
    PrintHelp();
  }
  
  return 0;
}
