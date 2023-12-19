#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_06_part1.txt");
  std::string line;

  const size_t num_races = 4;

  if (input_file.is_open()) {
    std::stringstream ss;
    std::vector<std::pair<int, int>> races(num_races);
    size_t idx = 0, i;

    std::getline(input_file, line);
    ss.str(line.substr(line.find("Time:") + 5));
    while (ss >> i) { races[idx++].first = i; }

    std::getline(input_file, line);
    ss.clear();
    ss.str(line.substr(line.find("Distance:") + 9));
    idx = 0;
    while (ss >> i) { races[idx++].second = i; }

    int64_t answer = 1;
    for (auto& [x, y] : races) {
      int winning_races = 0;
      for (int t = 1; t < x; ++t) { winning_races += ((x - t) * t) > y; }
      answer *= winning_races;
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