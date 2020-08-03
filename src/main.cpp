#include "allocator.h"
#include "container.h"
#include "factorial.h"
#include "version.h"
#include <iostream>
#include <map>
#include <vector>

/* TODO
 * beautify code
 * beautify output
 * write more tests
 */

int main() {
  std::cout << "Current version: " << version() << std::endl;
  std::cout << std::endl;
  std::map<int, int> base_map;
  for (int i = 0; i < 10; i++) {
    base_map[i] = factorial(i);
  }
  std::cout << "Base std::map:" << std::endl;
  for (std::pair<int, int> map_element : base_map) {
    std::cout << map_element.first << " " << map_element.second << std::endl;
  }
  std::cout << std::endl;
  auto v = std::vector<int, logging_allocator<int, 10>>{};
  for (int i = 0; i < 10; i++) {
    std::cout << "vector size = " << v.size() << std::endl;
    v.emplace_back(factorial(i));
    std::cout << std::endl;
  }

  std::cout << std::endl;
  vector_container<int> container_vector;
  for (int i = 0; i < 10; i++) {
    container_vector.push_back(i);
  }

  auto container_vector_allocator =
      vector_container<int, logging_allocator<int, 10>>{};
  for (int i = 0; i < 10; i++) {
    container_vector_allocator.push_back(i);
  }

  return 0;
}
