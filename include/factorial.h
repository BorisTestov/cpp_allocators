#include <stdexcept>

int factorial(int base) {
  if (base < 0) {
    throw std::invalid_argument(
        "Factorial can't be computed from negative value!");
  }
  int result = 1;
  for (int i = 1; i <= base; i++) {
    result *= i;
  }
  return result;
}
