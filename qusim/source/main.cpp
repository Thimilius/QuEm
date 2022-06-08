#include "qupch.hpp"

#include <iostream>

#include "qubit.hpp" 

using namespace QuSim;

void TestRandomNumberGenerator() {
  Qubit qubit = Qubit(ONE_OVER_SQRT2, ONE_OVER_SQRT2);

  MeasureResult result = qubit.Measure();

  std::cout << "Measurement was successful: " << result.success << ", with result: " << result.qubit << std::endl;   
}

int main() {
  TestRandomNumberGenerator();
  
  return 0;
}
