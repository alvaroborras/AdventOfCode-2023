#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "time_utils.h"

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_01_part1.txt");
  std::string line;

  const std::string digits = "0123456789";
  int answer = 0;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      auto firstDigitPos = line.find_first_of(digits);
      auto lastDigitPos = line.find_last_of(digits);
      if (firstDigitPos != std::string::npos && lastDigitPos != std::string::npos)
        answer += 10 * (int)(line[firstDigitPos] - '0') + (int)(line[lastDigitPos] - '0');
    }
    input_file.close();

    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}