#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_15_part1.txt");

  const uint32_t MOD = 256;

  if (input_file.is_open()) {
    std::string line;
    uint64_t sum = 0;
    uint32_t current = 0;
    char c;
    while (std::getline(input_file, line)) {
      std::stringstream ss(line);
      while (ss >> c) {
        if (c == ',') {
          sum += current;
          current = 0;
        } else {
          current += c;
          current = (current * 17) % MOD;
        }
      }
      input_file.close();

      sum += current;
      std::cout << "Answer: " << sum << std::endl;

      auto end = std::chrono::high_resolution_clock::now();
      auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
      std::cout << "Execution time: " << format_duration(diff) << "\n";
    }
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}