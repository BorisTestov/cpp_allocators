#include "allocator.h"
#include "container.h"
#include "factorial.h"
#include "version.h"
#include <iostream>
#include <map>
#include <vector>

/* TODO
 * write more tests
 */

int main() {
  std::cout << "Current version: " << version() << std::endl;
    {
        std::cout << std::endl;
        std::cout << "Base std::map:" << std::endl;
        std::map<int, int> base_map;
        for (int i = 0; i < 10; i++) {
            base_map[i] = factorial(i);
        }
        for (auto &[key, value] : base_map) {
            std::cout << key << " " << value << std::endl;
        }
    }
    {
        std::cout << std::endl;
        std::cout << "std::map with new allocator:" << std::endl;
        std::map<int, std::size_t, std::less<int>, logging_allocator<int, 10>>
                logging_map;
        for (int i = 0; i < 10; i++) {
            logging_map[i] = factorial(i);
        }
        for (auto &[key, value] : logging_map) {
            std::cout << key << " " << value << std::endl;
        }
    }
    {
        std::cout << std::endl;
        std::cout << "Self-written vector:" << std::endl;
        vector_container<int> mvec;
        for (int i = 0; i < 10; ++i) {
            mvec.push_back(i);
        }

        for (auto &i : mvec) {
            std::cout << i << std::endl;
        }
    }
    {
        std::cout << std::endl;
        std::cout << "Self-written vector with new allocator:" << std::endl;
        vector_container<int> mvec = vector_container<int, logging_allocator<int, 10>>();
        for (int i = 0; i < 10; ++i) {
            mvec.push_back(i);
        }
        for (auto &i : mvec) {
            std::cout << i << std::endl;
        }
    }
  return 0;
}
