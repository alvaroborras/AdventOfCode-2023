#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_04_part1.txt");
  std::string line;

  if (input_file.is_open()) {
    long long answer = 0;

    while (std::getline(input_file, line)) {
      std::map<int, bool> winner;
      line = line.substr(line.find(":") + 2);
      auto pos = std::find(line.begin(), line.end(), '|');
      std::string first_half(line.begin(), pos);
      std::string second_half(pos + 1, line.end());

      std::stringstream ss1(first_half);
      std::stringstream ss2(second_half);

      int i, count = 0;
      while (ss1 >> i) { winner[i] = true; }
      while (ss2 >> i) { count += winner[i]; }
      answer += count > 0 ? (1LL << (count - 1)) : 0;
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